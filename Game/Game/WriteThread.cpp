#include "WriteThread.h"
#include<stdio.h>

#include"Lock.h"
#include"ClientSide.h"


WriteThread::WriteThread(SOCKET* s):m_Soc(s){}


WriteThread::~WriteThread()
{
	delete m_Soc;
}

void WriteThread::run() {//protokol: SC + id + BC + tipus + BC + x/y + BC + msg + EC
	m_Neaded = true;
	const int buflen = 1024;
	char buf[buflen];

	if (m_Neaded) {
		memset(buf, '\0', buflen);
		string s =
			ClientSide::BREAK_CHAR_MSG_START + ClientSide::getId() +
			ClientSide::BREAK_CHAR + ClientSide::TYPE_LOGIN +
			ClientSide::BREAK_CHAR + string("1/1") +
			ClientSide::BREAK_CHAR + ClientSide::getIp() +
			ClientSide::BREAK_CHAR_MSG_STOP;
		strcpy(buf, s.c_str());
		send(*m_Soc, buf, strlen(buf), 0);
	}

	while (m_Neaded) {
		if (m_List.size() > 0 && m_Neaded) {
			for (Lock l = m_Mutex; l && m_Neaded; l.setUnlock()) {
				for (string s : calcData(
					ClientSide::BREAK_CHAR_MSG_START + ClientSide::getId() +
					ClientSide::BREAK_CHAR + ClientSide::TYPE_MSG +
					ClientSide::BREAK_CHAR,
					m_List.front())) {
					memset(buf, '\0', buflen);
					strcpy(buf, s.c_str());

					if (m_Neaded) {
						send(*m_Soc, buf, strlen(buf), 0);
					} else {
						break;
					}
				}

				m_List.remove(m_List.front()); 
			}
		}else{
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
	}

	//TODO: ha kilepes uzenetet kap a felhasznalotol, jelzi az olvaso oldalnak is
	
	if(m_Soc){
		memset(buf, '\0', buflen);
		string s = 
			ClientSide::BREAK_CHAR_MSG_START + ClientSide::getId() + 
			ClientSide::BREAK_CHAR + ClientSide::TYPE_DISCONNECT + 
			ClientSide::BREAK_CHAR + string("1/1") + 
			ClientSide::BREAK_CHAR + ClientSide::getIp() + 
			ClientSide::BREAK_CHAR_MSG_STOP;
		strcpy(buf, s.c_str());
		send(*m_Soc,buf,strlen(buf),0);
	}

	m_Neaded = false;
}

void WriteThread::addToList(std::string data)
{
	for (Lock l = m_Mutex; l && m_Neaded; l.setUnlock()) {
		m_List.push_back(data);
	}
}

void WriteThread::addToList(char data[1024])
{
	for (Lock l = m_Mutex; l && m_Neaded; l.setUnlock()) {
		m_List.push_back(std::string(data));
	}
}

std::list<std::string> WriteThread::calcData(std::string pre, std::string data)
{
	std::list<std::string> list;

	int plen = pre.length();
	int dlen = data.length();
	int len = plen + dlen;
	int lenner = 1024 - plen - 50;
	int size = (len / lenner) + 1;
	for (int i = 0; i < size && m_Neaded; ++i) {
		string aftSub;
		if ((i + 1)*lenner > dlen) {
			aftSub = data.substr(i * lenner, i * lenner + (dlen - i * lenner));
		}
		else {
			aftSub = data.substr(i * lenner, (i + 1) * lenner);
		}
		string db = std::to_string(i + 1) + string("/") + std::to_string(size);
		list.push_back(pre + db + ClientSide::BREAK_CHAR + aftSub + ClientSide::BREAK_CHAR_MSG_STOP);
	}

	return list;
}
