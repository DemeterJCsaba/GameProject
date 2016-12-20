#pragma once
#include<map>
#include<string>
#include<list>
#include<vector>

#include"Msg.h"

class FullMsg
{
private:
	static std::map<std::string,FullMsg> s_FullMsgs;
public:
	static void addMsg(std::vector<std::string> parts);
	static std::list<std::string> getFullMsgs();
private:
	bool volatile m_isBuildt;
	int m_MaxNumber;
	std::string m_Msg;
	std::vector<Msg> m_Msgs;
private:
	FullMsg(std::vector<std::string> parts);
	bool chack();
	Msg getI(int i);
};

