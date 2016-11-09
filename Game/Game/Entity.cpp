#include"Entity.h"

Entity::Entity(const string fileName){
	ifstream entityLoad(fileName);
	if (!entityLoad.good()) {
		return;
		//trow exeption
	}
	int version = -1;
	bool oneMesh = false;
	string line, key, value;
	while (getline(entityLoad, line)) {
		istringstream getFile(line);
		getFile >> key >> value;
		if (key == "MD5Version") {
			version = stoi(value);
		}
		else if (key == "Mesh") {
			if (!oneMesh) {
				oneMesh = true;
				loadMesh(version, value);
			}
		}
		else if (key == "Anim") {
			string state;
			while (getline(entityLoad, line)) {
				istringstream getAnim(line);
				getAnim >> key >> state >> value;
				if (key == "anim") {
					loadAnim(version, state, value);
				}
			}
		}
	}
	entityLoad.close();
}

Entity::~Entity(){

}

void Entity::loadMesh(const int version, const string fileMesh) {
	ifstream mesh(fileMesh);
	if (!mesh.good()) {
		return;
		//trow exeption
	}
	int version = -1;
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
			Joint *joint;
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

		}
	}
	mesh.close();
}

void Entity::setJoint(Joint *j, string line) {
	
}

void Entity::loadAnim(const int version, const string name, const string fileAnim) {
	m_Animations.push_back(new Animation(version,name, fileAnim));
}
