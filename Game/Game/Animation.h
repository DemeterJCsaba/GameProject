#pragma once
#include<string>

using namespace std;

class Animation
{
public:
	string name;
public:
	Animation(const int version,const string name,const string file);
	~Animation();
};

