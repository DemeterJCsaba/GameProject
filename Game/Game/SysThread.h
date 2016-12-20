#pragma once
#include "winsock2.h"

class SysThread
{
public:
	SysThread(void);
	virtual ~SysThread();
	virtual bool start();
	virtual bool stop(unsigned int timeout = 0);
	inline volatile bool& isRunning()
	{
		return m_bRunning;
	}
	inline volatile bool& isExited()
	{
		return m_bExited;
	}
protected:
	virtual void run() = 0;

private:
	friend DWORD WINAPI runStub(LPVOID mthread);
public:
	static const unsigned int INFINIT_WAIT;
private:
	volatile bool m_bRunning;
	volatile bool m_bExited;
	HANDLE m_thread;
};
