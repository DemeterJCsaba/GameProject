#pragma once
#include<string>
#include<mutex>

#include "winsock2.h"

using namespace std;

class WriteThread;
class ReadThread;

class ClientSide
{
public:
	static const int buflen;

	static const char BREAK_CHAR;//elvalaszto karakter
	static const char BREAK_CHAR_MSG_START;//elvalaszto karakter eleje
	static const char BREAK_CHAR_MSG_STOP;//elvalaszto karakter vege

										  //tipus konstatnsok
	static const string TYPE_LOGIN;
	static const string TYPE_DISCONNECT;
	static const string TYPE_MSG;
private:
	WriteThread* m_Write;
	ReadThread* m_Read;

	static int s_Id;
	static mutex s_Mutex;
	static string s_Ip;

	bool volatile m_good = false;
	SOCKET m_Soc;
public:
	static string getId();
	static string getIp();

	void disconnect();

	ClientSide(char* ip, int port);
	~ClientSide();
};

