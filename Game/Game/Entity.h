#pragma once
#include<string>
#include<fstream>
#include<sstream>
#include<vector>

#include"Animation.h"
#include"vec3.h"

using namespace std;

class Entity
{
private://adatatg
	struct Joint
	{
		std::string m_Name;
		int m_ParentID;
		vec3 m_Pos;
		vec3 m_Rot;
	};
	vector<Joint*> m_Joints;

	struct Mesh
	{
		std::string m_TextureName;

		//TODO
	};
	vector<Mesh*> m_Mesh;
protected:
	vector<Animation*> m_Animations;
public:
private://metodusok
	void setJoint(Joint *j, string line);
	void loadMesh(const int version, const string fileMesh);
	void loadAnim(const int version, const string name, const string fileAnim);
protected:
public:
	Entity(const string fileName);
	~Entity();
};

