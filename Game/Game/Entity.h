#pragma once
#include<string>
#include<fstream>
#include<sstream>
#include<vector>

#include"Animation.h"
#include"vec3.h"
#include"vec2.h"
#include"Texture.h"

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
	struct Vertex {
		float m_Index;
		vec2 m_TextureCord;
		float m_StartWeight;
		float m_CountWeight;
	};
	struct Tri {
		float m_Index;
		vec3 m_Pos;
	};
	struct Weight {
		float m_Index;
		float m_Joint;
		float m_Bias;
		vec3 m_Pos;
	};
	struct Mesh
	{
		Texture* m_Texture;
		vector<Vertex*> m_Vertexes;
		vector<Tri*> m_Tris;
		vector<Weight*> m_Weights;
	};
	vector<Mesh*> m_Mesh;
	vector<Animation*> m_Animations;
	vec3 m_Pos;
protected:
public:
private://metodusok
	void write();
	void removeQuotes(string& str);
	void setJoint(Joint *j, string line);
	void loadMesh(const int version, const string fileMesh, const string folder);
	void loadAnim(const int version, const string name, const string fileAnim, const string folder);
protected:
public:
	void setPos(vec3 pos);
	void addPos(vec3 pos);
	Entity(const string fileName);
	~Entity();
};

