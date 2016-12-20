#include "RawModel3D.h"

#include <iostream>
#include <fstream>
#include <sstream>


string RawModel3D::m_Dir = "Resources\\Entitys\\";

void RawModel3D::loadFromOBJ(string fileName) {	
	ifstream in(m_Dir + fileName);
	string line;
	string temp, s1, s2, s3;
	string s;
	string s11, s12, s13, s21, s22, s23, s31, s32, s33;

	int i;
	int j;

	m_Colors.push_back(vec3(1.0f, 0.0f, 0.0f));

	mat4 scale = mat4::translation(0.0f, -1.0f, 0.0f)*mat4::scale(0.015f, 0.015f, 0.015f);

	while (getline(in, line)) {
		istringstream iss(line);
		
		// Vertex Coordinates
		if (line[0] == 'v' && line[1] == ' ') {
			iss >> temp >> s1 >> s2 >> s3;
			m_Vertices.push_back(scale*vec3(atof(s1.c_str()), atof(s2.c_str()), atof(s3.c_str())));
		}
		// Texture Coordinates
		else if (line[0] == 'v' && line[1] == 't' && line[2] == ' ') {
			continue;
		}
		// Normal Coordinates
		else if (line[0] == 'v' && line[1] == 'n' && line[2] == ' ') {
			//iss >> temp >> s1 >> s2 >> s3;
			//m_Normals.push_back(vec3(atof(s1.c_str()), atof(s2.c_str()), atof(s3.c_str())));
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

			int a = atoi(s31.c_str()) - 1;
			int b = atoi(s21.c_str()) - 1;
			int c = atoi(s11.c_str()) - 1;
			m_IndicesVertex.push_back(a);
			m_IndicesVertex.push_back(b);
			m_IndicesVertex.push_back(c);

			vec3 normal = norm(
				m_Vertices[a],
				m_Vertices[c],
				m_Vertices[b]);
			normal.normalize(); 
			m_Normals.push_back(normal);

			m_IndicesNormal.push_back(m_Normals.size() - 1);
			m_IndicesNormal.push_back(m_Normals.size() - 1);
			m_IndicesNormal.push_back(m_Normals.size() - 1);
			/*m_IndicesNormal.push_back(atoi(s33.c_str())-1);
			m_IndicesNormal.push_back(atoi(s23.c_str())-1);
			m_IndicesNormal.push_back(atoi(s13.c_str())-1);*/
			m_IndicesColor.push_back(0);
			m_IndicesColor.push_back(0);
			m_IndicesColor.push_back(0);
		}
	}
}