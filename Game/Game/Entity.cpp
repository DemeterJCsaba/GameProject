#include"Entity.h"

Entity::Entity(const string fileName){
	ifstream entityLoad(fileName);
	if (!entityLoad.good()) {
		printf("bad file\n");
		return;
		//trow exeption
	}
	printf("good file\n");
	int version = -1;
	bool oneMesh = false;
	string line, key, value, folder;
	while (getline(entityLoad, line)) {
		istringstream getFile(line);
		getFile >> key >> value;
		if (key == "MD5Version") {
			version = stoi(value);
		}
		if (key == "Folder") {
			folder = value;
		}
		else if (key == "Mesh") {
			if (!oneMesh) {
				oneMesh = true;
				loadMesh(version, value, folder);
			}
		}
		else if (key == "Anim") {
			string state;
			while (getline(entityLoad, line)) {
				istringstream getAnim(line);
				getAnim >> key >> state >> value;
				if (key == "anim") {
					loadAnim(version, state, value, folder);
				}
			}
		}
	}
	entityLoad.close();
	//write();
}

void Entity::write() {
	printf("write out\n");
	for (Mesh *m : m_Mesh) {
		printf("Mesh:\n\tVertexes(%d):\n",m->m_Vertexes.size());
		for (Vertex *v : m->m_Vertexes) {
			printf("\t\t%f (%f %f) %f %f\n",v->m_Index, v->m_TextureCord.x, v->m_TextureCord.y,v->m_StartWeight, v->m_CountWeight);
		}
		printf("\tTris(%d):\n", m->m_Tris.size());
		for (Tri *t : m->m_Tris) {
			printf("\t\t%f (%f %f %f)\n",t->m_Index,t->m_Pos.x,t->m_Pos.y,t->m_Pos.z);
		}
		printf("\tWeights(%d):\n", m->m_Weights.size());
		for (Weight *w : m->m_Weights) {
			printf("\t\t%f %f %f (%f %f %f)\n", w->m_Index,w->m_Joint,w->m_Bias, w->m_Pos.x, w->m_Pos.y, w->m_Pos.z);
		}
	}
	printf("end write");
}

Entity::~Entity(){
	for (Joint *j : m_Joints) {
		delete j;
	}
	for (Mesh *m : m_Mesh) {
		delete m->m_Texture;
		for (Vertex *v : m->m_Vertexes) {
			delete v;
		}
		for (Tri *t : m->m_Tris) {
			delete t;
		}
		for (Weight *w : m->m_Weights) {
			delete w;
		}
		delete m;
	}
}

void Entity::loadMesh(const int version, const string fileMesh, const string folder) {
	ifstream mesh("Resources\\Entitys\\" + folder + "\\" + fileMesh);
	if (!mesh.good()) {
		return;
		//TODO: wrong file exeption
	}
	bool oneMesh = false;
	string line, key, value;
	while (getline(mesh, line)) {
		istringstream ln(line);
		ln >> key;
		if (key == "MD5Version") {
			ln >> value;
			if (version != stoi(value)) {
				//TODO: not equal exeption
			}
		}
		else if (key == "joints") {
			Joint *joint = new Joint();
			while(getline(mesh, line)){
				if (line.find("}") == string::npos) {
					break;
				}
				else if (line.find("(") == string::npos) {
					continue;
				}
				setJoint(joint, line);
				m_Joints.push_back(joint);
			}
		}
		else if (key == "mesh") {
			Mesh *meshP = new Mesh();
			string word, junk;
			while (getline(mesh, line)) {
				if (line.find("}") != string::npos) {
					break;
				}
				istringstream meshLn(line);
				printf("%s",line);
				meshLn >> word;
				if (word == "shader") {
					meshLn >> word;
					meshP->m_Texture = new Texture("Resources\\Entitys\\" + folder + "\\" + word);
				}
				else if (word == "vert") {
					Vertex *vertex = new Vertex();
					meshLn >> word;
					vertex->m_Index = stoi(word);
					meshLn >> junk >> word;
					vertex->m_TextureCord.x = stof(word);
					meshLn >> word >> junk;
					vertex->m_TextureCord.y = stof(word);
					meshLn >> word;
					vertex->m_StartWeight = stoi(word);
					meshLn >> word;
					vertex->m_CountWeight = stoi(word);
					meshP->m_Vertexes.push_back(vertex);
				}
				else if (word == "tri") {
					Tri *tri = new Tri();
					meshLn >> word;
					tri->m_Index = stoi(word);
					meshLn >> junk >> word;
					tri->m_Pos.x = stoi(word);
					meshLn >> word;
					tri->m_Pos.y = stoi(word);
					meshLn >> word >> junk;
					tri->m_Pos.z = stoi(word);
					meshP->m_Tris.push_back(tri);
				}
				else if (word == "weight") {
					Weight *weight = new Weight();
					meshLn >> word;
					weight->m_Index = stoi(word);
					meshLn >> word;
					weight->m_Joint = stoi(word);
					meshLn >> word;
					weight->m_Bias = stof(word);
					meshLn >> junk >> word;
					weight->m_Pos.x = stof(word);
					meshLn >> word;
					weight->m_Pos.y = stof(word);
					meshLn >> word >> junk;
					weight->m_Pos.z = stof(word);
					meshP->m_Weights.push_back(weight);
				}
			}
			m_Mesh.push_back(meshP);
		}
	}
	mesh.close();
}

void Entity::removeQuotes(string& str) {
	str = str.substr(1, str.length()-2);
}

void Entity::setJoint(Joint *j, string line) {
	line = line.substr(0,line.find("//")-1);
	string word, junk;
	istringstream ln(line);
	ln >> word;
	removeQuotes(word);
	j->m_Name = word; 
	ln >> word;
	j->m_ParentID = stoi(word);
	ln >> junk >> word;
	j->m_Pos.x = stoi(word);
	ln >> word;
	j->m_Pos.y = stoi(word);
	ln >> word >> junk;
	j->m_Pos.z = stoi(word); 

	ln >> junk >> word;
	j->m_Rot.x = stoi(word);
	ln >> word;
	j->m_Rot.y = stoi(word);
	ln >> word >> junk;
	j->m_Rot.z = stoi(word);
}

void Entity::setPos(vec3 pos) {
	m_Pos = pos;
}
void Entity::addPos(vec3 pos) {
	m_Pos += pos;
}

void Entity::loadAnim(const int version, const string name, const string fileAnim, const string folder) {
	m_Animations.push_back(new Animation(version,name, folder + "\\" + fileAnim));
}
