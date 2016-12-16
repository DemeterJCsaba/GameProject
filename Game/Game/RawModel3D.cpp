#include "RawModel3D.h"

#include <iostream>
#include <fstream>
#include <sstream>

RawModel3D* RawModel3D::loadFromOBJ(string fileName) {
	RawModel3D* result = new RawModel3D();
	
	ifstream in(fileName);
	string line;
	string temp, s1, s2, s3;
	string s;
	string s11, s12, s13, s21, s22, s23, s31, s32, s33;

	int i;
	int j;

	result->m_Colors.push_back(vec3(1.0f, 0.0f, 0.0f));

	while (getline(in, line)) {
		istringstream iss(line);
		
		// Vertex Coordinates
		if (line[0] == 'v' && line[1] == ' ') {
			iss >> temp >> s1 >> s2 >> s3;
			result->m_Vertices.push_back(vec3(atof(s1.c_str()), atof(s2.c_str()), atof(s3.c_str())));
		}
		// Texture Coordinates
		else if (line[0] == 'v' && line[1] == 't' && line[2] == ' ') {
			continue;
		}
		// Normal Coordinates
		else if (line[0] == 'v' && line[1] == 'n' && line[2] == ' ') {
			iss >> temp >> s1 >> s2 >> s3;
			result->m_Normals.push_back(vec3(atof(s1.c_str()), atof(s2.c_str()), atof(s3.c_str())));
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

			result->m_IndicesVertex.push_back(atoi(s31.c_str())-1);
			result->m_IndicesNormal.push_back(atoi(s33.c_str())-1);
			result->m_IndicesColor.push_back(0);
			result->m_IndicesVertex.push_back(atoi(s21.c_str())-1);
			result->m_IndicesNormal.push_back(atoi(s23.c_str())-1);
			result->m_IndicesColor.push_back(0);
			result->m_IndicesVertex.push_back(atoi(s11.c_str())-1);
			result->m_IndicesNormal.push_back(atoi(s13.c_str())-1);
			result->m_IndicesColor.push_back(0);
		}
	}
	
	return result;
}