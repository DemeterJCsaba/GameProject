#include "ClientSide.h"

#include<vector>
#include<sstream>

#include"Lock.h"
#include"ReadThread.h";
#include"WriteThread.h"
#include"MultiPlayerState.h"
#include"StringRunnable.h"

using namespace std;

const int ClientSide::buflen = 1024;

const char ClientSide::BREAK_CHAR = (char)178;
const char ClientSide::BREAK_CHAR_MSG_START = (char)179;
const char ClientSide::BREAK_CHAR_MSG_STOP = (char)180;//torolni a globalt

const string ClientSide::TYPE_LOGIN = "1";//log
const string ClientSide::TYPE_DISCONNECT = "2";//dis
const string ClientSide::TYPE_MSG = "3";//send objects, pos, stb

mutex ClientSide::s_Mutex;
int ClientSide::s_Id = 0;
string ClientSide::s_Ip = "no";

string ClientSide::getId()
{
	string id = "";
	for (Lock l = s_Mutex; l; l.setUnlock()) {
		id = std::to_string(s_Id++) + string("/") + s_Ip;
	}
	return id;
}

string ClientSide::getIp()
{
	return s_Ip;
}

ClientSide::ClientSide(char* ip, int port, StringRunnable* n, StringRunnable* d, StringRunnable* u){
	WSAData wsa;
	SOCKET soc;
	sockaddr_in adr;
	const int buflen = 1024;
	char buf[buflen];

	WSAStartup(MAKEWORD(2, 2), &wsa);

	soc = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	adr.sin_addr.s_addr = inet_addr(ip);//id
	adr.sin_family = AF_INET;
	adr.sin_port = htons(port);

	if (::connect(soc, (SOCKADDR *)&adr, sizeof(adr)) == SOCKET_ERROR) {
		printf("hiba a csatlakozasnal");

		WSAGetLastError();
		WSACleanup();

		return;
	}

	m_good = true;
	m_Soc = soc;
	s_Ip = string(ip) + string(":") + std::to_string(port);

	m_Read = new ReadThread(new SOCKET(soc), n,d,u);
	m_Write = new WriteThread(new SOCKET(soc));

	m_Read->start();
	m_Write->start();
}

ClientSide::~ClientSide()
{
	if (m_good) {
		disconnect();
	}
	if (m_Soc != NULL) {
		closesocket(m_Soc);
	}
	WSACleanup();
}

void ClientSide::addMsg(string msg)
{
	m_Write->addToList(msg);
}

void ClientSide::disconnect()
{
	m_good = false;
	m_Read->m_Neaded = false;
	m_Write->m_Neaded = false;
}
