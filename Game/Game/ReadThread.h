#pragma once
#include "SysThread.h"

#include<list>
#include<string>
#include<mutex>

#include"StringRunnable.h"

class ReadThread :
	public SysThread
{
private:
	std::list<std::string> m_List;
	std::mutex m_Mutex;
	std::string m_OldMsg;
private:
	StringRunnable* newPlayer;
	StringRunnable* deletePlayer;
	StringRunnable* updatePlayer;
public:
	volatile bool m_Neaded;
	SOCKET *m_Soc;
public:
	ReadThread(SOCKET* s, StringRunnable* n, StringRunnable* d, StringRunnable* u);
	~ReadThread();
	virtual void run();
private:
	std::list<std::string> getReplays(std::string reply);
	bool preRender(std::string replay);
};

