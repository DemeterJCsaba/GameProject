#pragma once
#include<string>
#include<fstream>
#include<sstream>
#include<vector>

#include"Animation.h"
#include"Maths.h"
#include"Texture2D.h"
#include"Utility.h"
#include"RawModel3D.h"

using namespace std;

class Entity
{
private://adatatg
	struct Joint
	{
		string m_Name;
		int m_ParentID;
		vec3 m_Pos;
		vec4 m_Rot;
	};
	vector<Joint> m_Joints;
	struct Vertex {
		float m_Index;
		vec2 m_TextureCord;
		float m_StartWeight;
		float m_CountWeight;

		vec3 m_Pos;
		vec3 m_Normal;
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
		vector<Vertex> m_Vertexes;
		vector<Tri> m_Tris;
		vector<Weight> m_Weights;

		vector<vec3> m_PositionBuffer;
		vector<vec3> m_NormalBuffer;
		vector<vec2> m_Tex2DBuffer;
		vector<GLuint> m_IndexBuffer;
	};
	vector<Mesh> m_Mesh;
	vector<Animation*> m_Animations;
	Animation *m_Active;

	vec3 m_Pos;
	vec3 m_Rot;

	RawModel3D rawModel;
protected:
public:
private://metodusok
	void write();
	void setJoint(Joint& j, string line);
	void loadMesh(const int version, const string fileMesh, const string folder);
	void loadAnim(const int version, const string name, const string fileAnim, const string folder);
protected:
public:
	void setPos(vec3 pos);
	void addPos(vec3 pos);
	void setRot(vec3 rot);
	void addRot(vec3 rot);
	Entity(const string fileName, int type = 0);
	~Entity();

	//////////////////////////////////////////
	void Update(float fDeltaTime);
	void Render();
	bool PrepareMesh(Mesh& mesh);
	bool PrepareMesh(Mesh& mesh, 
		const Animation::FrameSkeleton& skel);
	bool PrepareNormals(Mesh& mesh);

	// Render a single mesh of the model
	void RenderMesh(const Mesh& mesh);
	void RenderNormals(const Mesh& mesh);

	// Draw the skeleton of the mesh for debugging purposes.
	void RenderSkeleton(const vector<Joint>& joints);

	bool CheckAnimation(const Animation& animation) const;
	RawModel3D loadObj(const char* fileName);

	RawModel3D* getRawModel(){return &rawModel;}
	vec3 getPosition() { return m_Pos; }
	vec3 getRotation() { return m_Rot; }
};

//TODO:
/*
struct VertexData3D {
vec3 vertex;
vec3 normal;
vec3 color;
};
vector<VertexData3D> m_Vertices;
vector<unsigned int> m_Indices; faces(1,2,3)

vertex (x =3.5 y=3.6 z=3.8);
normal = ;
color = red;
*/