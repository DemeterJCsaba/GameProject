#pragma once
#include "SysThread.h"
#include<list>
#include<string>
#include<mutex>

class WriteThread:
	public SysThread
{
private:
	std::list<std::string> m_List;
	std::mutex m_Mutex;
	SOCKET *m_Soc;
public:
	volatile bool m_Neaded;
public:
	WriteThread(SOCKET* s);
	~WriteThread();

	virtual void run();
	void addToList(std::string data);
	void addToList(char data[1024]);
private:
	std::list<std::string> calcData(std::string pre, std::string data);
};

