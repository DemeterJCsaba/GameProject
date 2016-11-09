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
		int m_Id;
		vec2 m_TextureCord;
		int m_StartWeight;
		int m_CountWeight;
	};
	struct Tri {
		int m_Index;
		vec3 m_Pos;
	};
	struct Weight {
		int m_Index;
		int m_Joint;
		float m_Bias;
		vec3 m_Pos;
	};
	struct Mesh
	{
		Texture* m_Texture;
		vector<Vertex> m_Vertexes;
		vector<Tri> m_Tris;
		vector<Weight> m_Weights;
	};
	vector<Mesh*> m_Mesh;
protected:
	vector<Animation*> m_Animations;
public:
private://metodusok
	void removeQuotes(string& str);
	void setJoint(Joint *j, string line);
	void loadMesh(const int version, const string fileMesh, const string folder);
	void loadAnim(const int version, const string name, const string fileAnim, const string folder);
protected:
public:
	Entity(const string fileName);
	~Entity();
};

