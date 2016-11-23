#include "Animation.h"



Animation::Animation(const int& version, const string& name, const string& filename)
{
	m_Name = name;
	FILE* f = fopen(filename.c_str(),"rt");
	if (f == NULL)
	{
		string str("Faild load animation: bad file name!(" + filename + ")");
		throw new exception(str.c_str());
		return;
	}
	/*fseek(f, 0, SEEK_END);
	printf("filesize(f):%d\n",ftell(f));//*/
	

	std::string param;
	std::string junk;   // Read junk from the file

	/*ifstream file(filename);

	printf("filesize(if): %d\n",file.tellg());*/

	m_JointInfos.clear();
	m_Bounds.clear();
	m_BaseFrames.clear();
	m_Frames.clear();
	m_AnimatedSkeleton.m_Joints.clear();
	m_iNumFrames = 0;

	//fscanf(f, "%s", &param);

	while (fscanf(f, "%s", &param) != EOF)
	{
		if (param == "MD5Version")
		{
			//file >> m_iMD5Version;
			fscanf(f,"%d",&m_iMD5Version);
			if (m_iMD5Version != version) {
				string str("Faild load animation: bad version name!(" + m_iMD5Version);
				str.append(" != " + version);
				str.append(")");
				throw new exception(str.c_str());
				return;
			}
		}
		else if (param == "numFrames")
		{
			//file >> m_iNumFrames;
			fscanf(f, "%d", &m_iNumFrames);
		}
		else if (param == "numJoints")
		{
			//file >> m_iNumJoints;
			fscanf(f, "%d", &m_iNumJoints);
		}
		else if (param == "frameRate")
		{
			//file >> m_iFramRate;
			fscanf(f, "%d", &m_iFramRate);
		}
		else if (param == "numAnimatedComponents")
		{
			//file >> m_iNumAnimatedComponents;
			fscanf(f, "%d", &m_iNumAnimatedComponents);
		}
		else if (param == "hierarchy")
		{
			//file >> junk; // read in the '{' character
			fscanf(f, "%s", &junk);
			for (int i = 0; i < m_iNumJoints; ++i)
			{
				JointInfo joint;
				//file >> joint.m_Name >> joint.m_ParentID >> joint.m_Flags >> joint.m_StartIndex;
				fscanf(f, "%s%d%d%d", &joint.m_Name,&joint.m_ParentID,&joint.m_Flags,&joint.m_StartIndex);
				//Utility::removeQuotes(joint.m_Name);

				//fscanf(f,"%[^\n]", &junk);
				//getline(file,junk);

				m_JointInfos.push_back(joint);
			}
			//file >> junk; // read in the '}' character
			fscanf(f, "%s", &junk);
		}
		/*else if (param == "bounds")
		{
			file >> junk; // read in the '{' character
			for (int i = 0; i < m_iNumFrames; ++i)
			{
				Bound bound;
				file >> junk; // read in the '(' character
				file >> bound.m_Min.x >> bound.m_Min.y >> bound.m_Min.z;
				file >> junk >> junk; // read in the ')' and '(' characters.
				file >> bound.m_Max.x >> bound.m_Max.y >> bound.m_Max.z;

				m_Bounds.push_back(bound);
				//printf("int i = %d\n",i);
			}
			//printf("kilep\n");
			file >> junk; // read in the '}' character
		}
		else if (param == "baseframe")
		{
			file >> junk; // read in the '{' character

			for (int i = 0; i < m_iNumJoints; ++i)
			{
				BaseFrame baseFrame;
				file >> junk;
				file >> baseFrame.m_Pos.x >> baseFrame.m_Pos.y >> baseFrame.m_Pos.z;
				file >> junk >> junk;
				file >> baseFrame.m_Orient.x >> baseFrame.m_Orient.y >> baseFrame.m_Orient.z;

				m_BaseFrames.push_back(baseFrame);
			}
			file >> junk; // read in the '}' character
		}
		else if (param == "frame")
		{
			FrameData frame;
			file >> frame.m_iFrameID >> junk; // Read in the '{' character

			for (int i = 0; i < m_iNumAnimatedComponents; ++i)
			{
				float frameData;
				file >> frameData;
				frame.m_FrameData.push_back(frameData);
			}

			m_Frames.push_back(frame);

			// Build a skeleton for this frame
			BuildFrameSkeleton(m_Skeletons, m_JointInfos, m_BaseFrames, frame);

			file >> junk; // Read in the '}' character
		}*/
	} // while ( !file.eof )

	  // Make sure there are enough joints for the animated skeleton.
	m_AnimatedSkeleton.m_Joints.assign(m_iNumJoints, SkeletonJoint());

	m_fFrameDuration = 1.0f / (float)m_iFramRate;
	m_fAnimDuration = (m_fFrameDuration * (float)m_iNumFrames);
	m_fAnimTime = 0.0f;

	fclose(f);
}


Animation::~Animation()
{
}

void Animation::BuildFrameSkeleton(	FrameSkeletonList& skeletons, const JointInfoList& jointInfos, 
									const BaseFrameList& baseFrames, const FrameData& frameData)
{
	FrameSkeleton skeleton;

	for (unsigned int i = 0; i < jointInfos.size(); ++i)
	{
		unsigned int j = 0;

		const JointInfo& jointInfo = jointInfos[i];
		// Start with the base frame position and orientation.
		SkeletonJoint animatedJoint = baseFrames[i];

		animatedJoint.m_Parent = jointInfo.m_ParentID;

		if (jointInfo.m_Flags & 1) // Pos.x
		{
			animatedJoint.m_Pos.x = frameData.m_FrameData[jointInfo.m_StartIndex + j++];
		}
		if (jointInfo.m_Flags & 2) // Pos.y
		{
			animatedJoint.m_Pos.y = frameData.m_FrameData[jointInfo.m_StartIndex + j++];
		}
		if (jointInfo.m_Flags & 4) // Pos.x
		{
			animatedJoint.m_Pos.z = frameData.m_FrameData[jointInfo.m_StartIndex + j++];
		}
		if (jointInfo.m_Flags & 8) // Orient.x
		{
			animatedJoint.m_Orient.x = frameData.m_FrameData[jointInfo.m_StartIndex + j++];
		}
		if (jointInfo.m_Flags & 16) // Orient.y
		{
			animatedJoint.m_Orient.y = frameData.m_FrameData[jointInfo.m_StartIndex + j++];
		}
		if (jointInfo.m_Flags & 32) // Orient.z
		{
			animatedJoint.m_Orient.z = frameData.m_FrameData[jointInfo.m_StartIndex + j++];
		}

		vec4::ComputeQuatW(animatedJoint.m_Orient);

		if (animatedJoint.m_Parent >= 0) // Has a parent joint
		{
			SkeletonJoint& parentJoint = skeleton.m_Joints[animatedJoint.m_Parent];
			vec3 rotPos = vec3::multiplicate_vec4( parentJoint.m_Orient, animatedJoint.m_Pos);

			animatedJoint.m_Pos = parentJoint.m_Pos + rotPos;
			animatedJoint.m_Orient = vec4::multiplicate(parentJoint.m_Orient, animatedJoint.m_Orient);

			animatedJoint.m_Orient.normalize();
		}

		skeleton.m_Joints.push_back(animatedJoint);
	}

	skeletons.push_back(skeleton);
}

void Animation::Update(float fDeltaTime)
{
	if (m_iNumFrames < 1) return;

	m_fAnimTime += fDeltaTime;

	while (m_fAnimTime > m_fAnimDuration) m_fAnimTime -= m_fAnimDuration;
	while (m_fAnimTime < 0.0f) m_fAnimTime += m_fAnimDuration;

	// Figure out which frame we're on
	float fFramNum = m_fAnimTime * (float)m_iFramRate;
	int iFrame0 = (int)floorf(fFramNum);
	int iFrame1 = (int)ceilf(fFramNum);
	iFrame0 = iFrame0 % m_iNumFrames;
	iFrame1 = iFrame1 % m_iNumFrames;

	float fInterpolate = fmodf(m_fAnimTime, m_fFrameDuration) / m_fFrameDuration;

	InterpolateSkeletons(m_AnimatedSkeleton, m_Skeletons[iFrame0], m_Skeletons[iFrame1], fInterpolate);
}

void Animation::InterpolateSkeletons(FrameSkeleton& finalSkeleton, const FrameSkeleton& skeleton0, const FrameSkeleton& skeleton1, float fInterpolate)
{
	for (int i = 0; i < m_iNumJoints; ++i)
	{
		SkeletonJoint& finalJoint = finalSkeleton.m_Joints[i];
		const SkeletonJoint& joint0 = skeleton0.m_Joints[i];
		const SkeletonJoint& joint1 = skeleton1.m_Joints[i];

		finalJoint.m_Parent = joint0.m_Parent;

		finalJoint.m_Pos = vec3::mix(joint0.m_Pos, joint1.m_Pos, fInterpolate);
		finalJoint.m_Orient = vec4::mix(joint0.m_Orient, joint1.m_Orient, fInterpolate);
	}
}

void Animation::Render()
{
	glPointSize(5.0f);
	glColor3f(1.0f, 0.0f, 0.0f);

	glPushAttrib(GL_ENABLE_BIT);

	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);

	const SkeletonJointList& joints = m_AnimatedSkeleton.m_Joints;

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
			const SkeletonJoint& j0 = joints[i];
			if (j0.m_Parent != -1)
			{
				const SkeletonJoint& j1 = joints[j0.m_Parent];
				glVertex3fv(vec3::value_ptr(j0.m_Pos));
				glVertex3fv(vec3::value_ptr(j1.m_Pos));
			}
		}
	}
	glEnd();

	glPopAttrib();
}
