#pragma once
#include<string>
#include<vector>
#include<fstream>
#include<sstream>
#include<stdlib.h>
#include<stdio.h>

#include"Maths.h"
#include"Texture.h"
#include"Utility.h"

using namespace std;

class Animation{
public:
	string m_Name;
public:
	Animation(const int& version,const string& name,const string& file);
	~Animation();

	void Update(float fDeltaTime);
	// Draw the animated skeleton
	void Render();

	// The JointInfo stores the information necessary to build the 
	// skeletons for each frame
	struct JointInfo
	{
		string m_Name;
		int m_ParentID;
		int m_Flags;
		int m_StartIndex;
	};
	typedef vector<JointInfo> JointInfoList;

	struct Bound
	{
		vec3 m_Min;
		vec3 m_Max;
	};
	typedef vector<Bound> BoundList;

	struct BaseFrame
	{
		vec3 m_Pos;
		vec4 m_Orient;
	};
	typedef vector<BaseFrame> BaseFrameList;

	struct FrameData
	{
		int m_iFrameID;
		vector<float> m_FrameData;
	};
	typedef  vector<FrameData> FrameDataList;

	struct SkeletonJoint
	{
		SkeletonJoint(): m_Parent(-1), m_Pos(0){}
		SkeletonJoint(const BaseFrame& copy): m_Pos(copy.m_Pos), m_Orient(copy.m_Orient){}

		int m_Parent;
		vec3 m_Pos;
		vec4 m_Orient;
	};
	typedef vector<SkeletonJoint> SkeletonJointList;

	struct FrameSkeleton
	{
		SkeletonJointList   m_Joints;
	};
	typedef vector<FrameSkeleton> FrameSkeletonList;

	const FrameSkeleton& GetSkeleton() const
	{
		return m_AnimatedSkeleton;
	}

	int GetNumJoints() const
	{
		return m_iNumJoints;
	}

	const JointInfo& GetJointInfo(unsigned int index) const
	{
		if (index < m_JointInfos.size()) {
			return m_JointInfos[index];
		}
		throw new exception("Wrong get(getjointinfo)");
	}

protected:

	JointInfoList       m_JointInfos;
	BoundList           m_Bounds;
	BaseFrameList       m_BaseFrames;
	FrameDataList       m_Frames;
	FrameSkeletonList   m_Skeletons;    // All the skeletons for all the frames

	FrameSkeleton       m_AnimatedSkeleton;

	// Build the frame skeleton for a particular frame
	void BuildFrameSkeleton(FrameSkeletonList& skeletons, const JointInfoList& jointInfo, const BaseFrameList& baseFrames, const FrameData& frameData);
	void InterpolateSkeletons(FrameSkeleton& finalSkeleton, const FrameSkeleton& skeleton0, const FrameSkeleton& skeleton1, float fInterpolate);


private:
	int m_iMD5Version;
	int m_iNumFrames;
	int m_iNumJoints;
	int m_iFramRate;
	int m_iNumAnimatedComponents;

	float m_fAnimDuration;
	float m_fFrameDuration;
	float m_fAnimTime;
};

