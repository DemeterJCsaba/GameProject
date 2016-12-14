#pragma once

#include <vector>
#include <iostream>

#include "Maths.h"

using namespace std;

class RawModel3D {
protected:
	vector<vec3> m_Vertices;
	vector<vec3> m_Normals;
	vector<vec3> m_Colors;
	vector<unsigned int> m_IndicesVertex;
	vector<unsigned int> m_IndicesNormal;
	vector<unsigned int> m_IndicesColor;

	vec3 m_Position;
	vec3 m_Rotation;
public:
	RawModel3D(vec3 postion = vec3(), vec3 rotation = vec3()) :m_Position(postion), m_Rotation(rotation) {}
	
	vector<vec3>& getVertices() { return m_Vertices; }
	vector<vec3>& getNormals() { return m_Normals; }
	vector<vec3>& getColors() { return m_Colors; }
	vector<unsigned int>& getIndicesVertex() { return m_IndicesVertex; }
	vector<unsigned int>& getIndicesNormal() { return m_IndicesNormal; }
	vector<unsigned int>& getIndicesColor() { return m_IndicesColor; }

	const vec3& getPosition() const { return m_Position; }
	const vec3& getRotation() const { return m_Rotation; }

	void setPosition(vec3 position) { m_Position = position; }
	void setRotation(vec3 rotation) { m_Rotation += rotation; }
	void addPosition(vec3 position) { m_Position = position; }
	void addRotation(vec3 rotation) { m_Rotation += rotation; }

	friend static RawModel3D* loadFromOBJ(string fileName) {
		RawModel3D* result = new RawModel3D();
		/*
		ifstream in(filename);
		string line;
		string temp, s1, s2, s3;
		string s;
		string s11, s12, s13, s21, s22, s23, s31, s32, s33;

		int i;
		int j;

		while (getline(in, line))
		{
			istringstream iss(line);
			// Vertex Coordinates
			if (line[0] == 'v' && line[1] == ' ') {
				iss >> temp >> s1 >> s2 >> s3;
				OBJVertex v;
				v.x = atof(s1.c_str());
				v.y = atof(s2.c_str());
				v.z = atof(s3.c_str());
				vertices->push_back(v);
			}
			// Texture Coordinates
			else if (line[0] == 'v' && line[1] == 't' && line[2] == ' ') {
				iss >> temp >> s1 >> s2;
				OBJTexture t;
				t.x = atof(s1.c_str());
				t.y = atof(s2.c_str());
				textures->push_back(t);
			}
			// Normal Coordinates
			else if (line[0] == 'v' && line[1] == 'n' && line[2] == ' ') {
				iss >> temp >> s1 >> s2 >> s3;
				OBJNormal n;
				n.x = atof(s1.c_str());
				n.y = atof(s2.c_str());
				n.z = atof(s3.c_str());
				normals->push_back(n);
			}
			// Index Coordinates
			else if (line[0] == 'f' && line[1] == ' ') {
				iss >> temp >> s1 >> s2 >> s3;
				istringstream iss1(s1);
				istringstream iss2(s2);
				istringstream iss3(s3);
				getline(iss1, s11, '/');
				getline(iss1, s12, '/');
				getline(iss1, s13, '/');
				getline(iss2, s21, '/');
				getline(iss2, s22, '/');
				getline(iss2, s23, '/');
				getline(iss3, s31, '/');
				getline(iss3, s32, '/');
				getline(iss3, s33, '/');
				OBJIndex i1;
				OBJIndex i2;
				OBJIndex i3;
				i1.VertexIndex = atoi(s11.c_str());
				i1.TextureIndex = atoi(s12.c_str());
				i1.NormalIndex = atoi(s13.c_str());
				i2.VertexIndex = atoi(s21.c_str());
				i2.TextureIndex = atoi(s22.c_str());
				i2.NormalIndex = atoi(s23.c_str());
				i3.VertexIndex = atoi(s31.c_str());
				i3.TextureIndex = atoi(s32.c_str());
				i3.NormalIndex = atoi(s33.c_str());
				indices->push_back(i1);
				indices->push_back(i2);
				indices->push_back(i3);
			}
		}*/
		
		return result;
	}
};