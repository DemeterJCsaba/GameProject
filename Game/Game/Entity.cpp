#include"Entity.h"

Entity::Entity(const string fileName){
	ifstream entityLoad(fileName);
	if (!entityLoad.good()) {
		return;
		//trow exeption
	}
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
}

Entity::~Entity(){

}

void Entity::loadMesh(const int version, const string fileMesh, const string folder) {
	ifstream mesh(fileMesh);
	if (!mesh.good()) {
		return;
		//trow exeption
	}
	bool oneMesh = false;
	string line, key, value;
	while (getline(mesh, line)) {
		istringstream ln(line);
		ln >> key;
		if (key == "MD5Version") {
			ln >> value;
			if (version != stoi(value)) {
				//not equal
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
				if (line.find("}") == string::npos) {
					break;
				}
				istringstream meshLn(line);
				meshLn >> word;
				if (word == "shader") {
					meshLn >> word;
					meshP->m_Texture = new Texture(("Resources\\Entitys\\" + folder + "\\" + word).c_str());
				}
				else if (word == "vert") {
					
				}
				else if (word == "tri") {
					
				}
				else if (word == "weight") {
					
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

void Entity::loadAnim(const int version, const string name, const string fileAnim, const string folder) {
	m_Animations.push_back(new Animation(version,name, folder + "\\" + fileAnim));
}
