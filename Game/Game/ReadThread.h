#pragma once
#include "SysThread.h"

#include<list>
#include<string>
#include<mutex>

class ReadThread :
	public SysThread
{
private:
	std::list<std::string> m_List;
	std::mutex m_Mutex;
	std::string m_OldMsg;
public:
	volatile bool m_Neaded;
	SOCKET *m_Soc;
public:
	ReadThread(SOCKET* s);
	~ReadThread();
	virtual void run();
private:
	std::list<std::string> getReplays(std::string reply);
	bool preRender(std::string replay);
};

