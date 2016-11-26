#include"Entity.h"

Entity::Entity(const string fileName, int type){
	if (type == 0) {
		rawModel = loadObj(fileName.c_str());
	}
	else {
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
}

void Entity::write() {
	printf("write out\n");
	for (Mesh m : m_Mesh) {
		printf("Mesh:\n\tVertexes(%d):\n",m.m_Vertexes.size());
		for (Vertex v : m.m_Vertexes) {
			printf("\t\t%f (%f %f) %f %f\n",v.m_Index, v.m_TextureCord.x, v.m_TextureCord.y,v.m_StartWeight, v.m_CountWeight);
		}
		printf("\tTris(%d):\n", m.m_Tris.size());
		for (Tri t : m.m_Tris) {
			printf("\t\t%f (%f %f %f)\n",t.m_Index,t.m_Pos.x,t.m_Pos.y,t.m_Pos.z);
		}
		printf("\tWeights(%d):\n", m.m_Weights.size());
		for (Weight w : m.m_Weights) {
			printf("\t\t%f %f %f (%f %f %f)\n", w.m_Index,w.m_Joint,w.m_Bias, w.m_Pos.x, w.m_Pos.y, w.m_Pos.z);
		}
	}
	printf("end write");
}

Entity::~Entity(){
}

void Entity::loadMesh(const int version, const string fileMesh, const string folder) {
	ifstream mesh("Resources\\Entitys\\" + folder + "\\" + fileMesh);
	if (!mesh.good()) {
		return;
		//TODO: wrong file exeption
	}

	string param, junk, line;

	mesh >> param;

	while (!mesh.eof())
	{
		if (param == "MD5Version") {
			mesh >> param;
			if (version != stoi(param)) {
				//TODO: not equal exeption
			}
		}
		else if (param == "joints")
		{
			Joint joint;
			mesh >> junk;
			while(getline(mesh, line))
			{
				if (line.find("}") == string::npos) {
					break;
				}else if (line.find("(") == string::npos) {
					continue;
				}
				setJoint(joint, line);
				m_Joints.push_back(joint);
			}
		}
		else if (param == "mesh")
		{
			Mesh meshP;
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
					meshP.m_Texture = new Texture("Resources\\Entitys\\" + folder + "\\" + word);
				}
				else if (word == "vert") {
					Vertex vertex;
					meshLn >> word;
					vertex.m_Index = stoi(word);
					meshLn >> junk >> word;
					vertex.m_TextureCord.x = stof(word);
					meshLn >> word >> junk;
					vertex.m_TextureCord.y = stof(word);
					meshLn >> word;
					vertex.m_StartWeight = stoi(word);
					meshLn >> word;
					vertex.m_CountWeight = stoi(word);
					meshP.m_Vertexes.push_back(vertex);

					meshP.m_Tex2DBuffer.push_back(vertex.m_TextureCord);
				}
				else if (word == "tri") {
					Tri tri;
					meshLn >> word;
					tri.m_Index = stoi(word);
					meshLn >> junk >> word;
					tri.m_Pos.x = stoi(word);
					meshLn >> word;
					tri.m_Pos.y = stoi(word);
					meshLn >> word >> junk;
					tri.m_Pos.z = stoi(word);
					meshP.m_Tris.push_back(tri);
					meshP.m_IndexBuffer.push_back((GLuint)tri.m_Pos.x);
					meshP.m_IndexBuffer.push_back((GLuint)tri.m_Pos.y);
					meshP.m_IndexBuffer.push_back((GLuint)tri.m_Pos.z);
				}
				else if (word == "weight") {
					Weight weight;
					meshLn >> word;
					weight.m_Index = stoi(word);
					meshLn >> word;
					weight.m_Joint = stoi(word);
					meshLn >> word;
					weight.m_Bias = stof(word);
					meshLn >> junk >> word;
					weight.m_Pos.x = stof(word);
					meshLn >> word;
					weight.m_Pos.y = stof(word);
					meshLn >> word >> junk;
					weight.m_Pos.z = stof(word);
					meshP.m_Weights.push_back(weight);
				}
			}
			m_Mesh.push_back(meshP);
		}

		mesh >> param;
	}

	mesh.close();
}

void Entity::setJoint(Joint& j, string line) {
	line = line.substr(0,line.find("//")-1);
	string word, junk;
	istringstream ln(line);
	ln >> word;
	Utility::removeQuotes(word);
	j.m_Name = word; 
	ln >> word;
	j.m_ParentID = stoi(word);
	ln >> junk >> word;
	j.m_Pos.x = stoi(word);
	ln >> word;
	j.m_Pos.y = stoi(word);
	ln >> word >> junk;
	j.m_Pos.z = stoi(word); 

	ln >> junk >> word;
	j.m_Rot.x = stoi(word);
	ln >> word;
	j.m_Rot.y = stoi(word);
	ln >> word >> junk;
	j.m_Rot.z = stoi(word);

	vec4::ComputeQuatW(j.m_Rot);
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

void Entity::RenderMesh(const Mesh& mesh)
{
	glColor3f(1.0f, 1.0f, 1.0f);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	glBindTexture(GL_TEXTURE_2D, mesh.m_Texture->getTextureID());
	glVertexPointer(3, GL_FLOAT, 0, &(mesh.m_PositionBuffer[0]));//itt vmi hiba
	glNormalPointer(GL_FLOAT, 0, &(mesh.m_NormalBuffer[0]));
	glTexCoordPointer(2, GL_FLOAT, 0, &(mesh.m_Tex2DBuffer[0]));

	glDrawElements(GL_TRIANGLES, mesh.m_IndexBuffer.size(), GL_UNSIGNED_INT, &(mesh.m_IndexBuffer[0]));

	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Entity::RenderNormals(const Mesh& mesh)
{

	glPushAttrib(GL_ENABLE_BIT);
	glDisable(GL_LIGHTING);

	glColor3f(1.0f, 1.0f, 0.0f);// Yellow

	glBegin(GL_LINES);
	{
		for (unsigned int i = 0; i < mesh.m_PositionBuffer.size(); ++i)
		{
			vec3 p0 = mesh.m_PositionBuffer[i];
			vec3 p1 = (mesh.m_PositionBuffer[i] + mesh.m_NormalBuffer[i]);

			glVertex3fv(vec3::value_ptr(p0));
			glVertex3fv(vec3::value_ptr(p1));
		}
	}
	glEnd();

	glPopAttrib();
}

void Entity::RenderSkeleton(const vector<Joint>& joints)
{
	glPointSize(5.0f);
	glColor3f(1.0f, 0.0f, 0.0f);

	glPushAttrib(GL_ENABLE_BIT);

	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);

	// Draw the joint positions
	glBegin(GL_POINTS);
	{
		for (unsigned int i = 0; i < joints.size(); ++i)
		{
			glVertex3fv(vec3::value_ptr(joints[i].m_Pos));
		}
	}
	glEnd();

	// Draw the bones
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_LINES);
	{
		for (unsigned int i = 0; i < joints.size(); ++i)
		{
			const Joint& j0 = joints[i];
			if (j0.m_ParentID != -1)
			{
				const Joint& j1 = joints[j0.m_ParentID];
				glVertex3fv(vec3::value_ptr(j0.m_Pos));
				glVertex3fv(vec3::value_ptr(j1.m_Pos));
			}
		}
	}
	glEnd();

	glPopAttrib();

}

bool Entity::CheckAnimation(const Animation& animation) const
{
	// Check to make sure the joints match up
	for (unsigned int i = 0; i < m_Joints.size(); ++i)
	{
		const Joint& meshJoint = m_Joints[i];
		const Animation::JointInfo& animJoint = animation.GetJointInfo(i);

		if (meshJoint.m_Name != animJoint.m_Name ||
			meshJoint.m_ParentID != animJoint.m_ParentID)
		{
			return false;
		}
	}

	return true;
}


// Compute the position of the vertices in object local space
// in the skeleton's bind pose
bool Entity::PrepareMesh(Mesh& mesh)
{
	mesh.m_PositionBuffer.clear();
	mesh.m_Tex2DBuffer.clear();

	// Compute vertex positions
	for (unsigned int i = 0; i < mesh.m_Vertexes.size(); ++i)
	{
		vec3 finalPos(0);
		Vertex& vert = mesh.m_Vertexes[i];

		vert.m_Pos = vec3(0);
		vert.m_Normal = vec3(0);

		// Sum the position of the weights
		for (int j = 0; j < vert.m_CountWeight; ++j)
		{
			Weight& weight = mesh.m_Weights[vert.m_StartWeight + j];
			Joint& joint = m_Joints[weight.m_Index];

			// Convert the weight position from Joint local space to object space
			vec3 rotPos = vec3::multiplicate_vec4( joint.m_Rot , weight.m_Pos);

			vert.m_Pos += (joint.m_Pos + rotPos) * weight.m_Bias;
		}

		mesh.m_PositionBuffer.push_back(vert.m_Pos);
		mesh.m_Tex2DBuffer.push_back(vert.m_TextureCord);
	}

	return true;
}

bool Entity::PrepareMesh(Mesh& mesh, const Animation::FrameSkeleton& skel)
{
	for (unsigned int i = 0; i < mesh.m_Vertexes.size(); ++i)
	{
		const Vertex& vert = mesh.m_Vertexes[i];
		vec3& pos = mesh.m_PositionBuffer[i];
		vec3& normal = mesh.m_NormalBuffer[i];

		pos = vec3(0);
		normal = vec3(0);

		for (int j = 0; j < vert.m_CountWeight; ++j)
		{
			const Weight& weight = mesh.m_Weights[vert.m_StartWeight + j];
			const Animation::SkeletonJoint& joint = skel.m_Joints[weight.m_Index];

			vec3 rotPos = vec3::multiplicate_vec4( joint.m_Orient , weight.m_Pos);
			pos += (joint.m_Pos + rotPos) * weight.m_Bias;

			normal += vec3::multiplicate_vec4(joint.m_Orient , vert.m_Normal) * weight.m_Bias;
		}
	}
	return true;
}


// Compute the vertex normals in the Mesh's bind pose
bool Entity::PrepareNormals(Mesh& mesh)
{
	mesh.m_NormalBuffer.clear();

	// Loop through all triangles and calculate the normal of each triangle
	for (unsigned int i = 0; i < mesh.m_Tris.size(); ++i)
	{
		vec3 v0 = mesh.m_Vertexes[mesh.m_Tris[i].m_Pos.x].m_Pos;
		vec3 v1 = mesh.m_Vertexes[mesh.m_Tris[i].m_Pos.y].m_Pos;
		vec3 v2 = mesh.m_Vertexes[mesh.m_Tris[i].m_Pos.z].m_Pos;

		vec3 normal = vec3::cross(v2 - v0, v1 - v0);

		mesh.m_Vertexes[mesh.m_Tris[i].m_Pos.x].m_Normal += normal;
		mesh.m_Vertexes[mesh.m_Tris[i].m_Pos.y].m_Normal += normal;
		mesh.m_Vertexes[mesh.m_Tris[i].m_Pos.z].m_Normal += normal;
	}

	// Now normalize all the normals
	for (unsigned int i = 0; i < mesh.m_Vertexes.size(); ++i)
	{
		Vertex& vert = mesh.m_Vertexes[i];

		vec3 normal = vec3::normalize(vert.m_Normal);
		mesh.m_NormalBuffer.push_back(normal);

		// Reset the normal to calculate the bind-pose normal in joint space
		vert.m_Normal = vec3(0);

		// Put the bind-pose normal into joint-local space
		// so the animated normal can be computed faster later
		for (int j = 0; j < vert.m_CountWeight; ++j)
		{
			const Weight& weight = mesh.m_Weights[vert.m_StartWeight + j];
			const Joint& joint = m_Joints[weight.m_Index];
			vert.m_Normal += vec3::multiplicate_vec4(joint.m_Rot , normal) * weight.m_Bias;
		}
	}

	return true;
}

void Entity::Update(float fDeltaTime)
{
	printf("size=%d\n", m_Animations.size());
	if (m_Animations.size() > 0)
	{
		if (m_Active == nullptr && m_Animations.size() > 0) {
			m_Active = m_Animations[0];
		}
		else {
			return;
		}
		m_Active->Update(fDeltaTime);
		const Animation::FrameSkeleton& skeleton = m_Active->GetSkeleton();

		for (Mesh m: m_Mesh)
		{
			PrepareMesh(m, skeleton);
		}
	}
}

void Entity::Render()
{
	glPushMatrix();
	//glMultMatrixf(glm::value_ptr(m_LocalToWorldMatrix));

	// Render the meshes
	for (unsigned int i = 0; i < m_Mesh.size(); ++i)
	{
		RenderMesh(m_Mesh[i]);
	}

	m_Active->Render();

	for (unsigned int i = 0; i < m_Mesh.size(); ++i)
	{
		RenderNormals(m_Mesh[i]);
	}

	glPopMatrix();
}

RawModel Entity::loadObj(const char* filename) {
	//cout << "Loading " << filename << "..." << endl;
	FILE* file = fopen(filename, "r");
	if (file == NULL) {
		//cout << "Load faild " << endl;
		RawModel r;
		return r;
	}
	char* ch = new char[100];
	char* str;

	vector<float> vert;
	vector<float> norm;
	//vector<float> color;//text
	vector<unsigned int> face;

	while (fgets(ch, 100, file) != NULL) {
		str = strtok(ch, " ");
		if (!strcmp(str, "v")) {
			str = strtok(NULL, " ");
			while (str != NULL) {
				vert.push_back(atof(str));
				str = strtok(NULL, " ");
			}
		}
		else if (!strcmp(str, "vt")) {
			/*color.push_back(1.0);
			color.push_back(0.0);
			color.push_back(0.0);//*/
		}
		else if (!strcmp(str, "vn")) {
			str = strtok(NULL, " ");
			while (str != NULL) {
				norm.push_back(atof(str));
				str = strtok(NULL, " ");
			}
		}
		else if (!strcmp(str, "f")) {
			str = strtok(NULL, " \\");
			while (str != NULL) {
				int x = atoi(str) - 1;
				str = strtok(NULL, " \\");
				int y = atoi(str) - 1;
				str = strtok(NULL, " \\");
				int z = atoi(str) - 1;
				face.push_back(x);
				face.push_back(y);
				face.push_back(z);
				str = strtok(NULL, " \\");
			}
		}
	}
	fclose(file);
	delete[] ch;
	//cout << "Loading done!" << endl;
	RawModel r;
	r.indices = face;
	for (int i = 0; i < vert.size(); ++i) {
		VertexData3D v;
		v.vertex = vert[i];
		v.normal = norm[i];
		v.color = 1.0;
		r.vertices.push_back(v);
	}
	return r;
}