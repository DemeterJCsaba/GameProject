#include "ReadThread.h"
#include <stdio.h>

#include<vector>

#include"Lock.h"
#include"Utility.h"
#include"ClientSide.h"
#include"FullMsg.h"

ReadThread::ReadThread(SOCKET* s):m_Soc(s){
	m_OldMsg = "";
}


ReadThread::~ReadThread()
{
	delete m_Soc;
}

void ReadThread::run(void)
{
	m_Neaded = true;
	const int buflen = 1024;
	char tempbuf[buflen];

	while (m_Neaded) {
		int len = recv(*m_Soc, tempbuf, (buflen-1), 0);
		if (len > 0) {
			tempbuf[len] = '\0';
			for (string msg : getReplays(string(tempbuf))) {
				if (!preRender(msg)) {
					//TODO: if wrong msg
				}
			}
			for (auto str: FullMsg::getFullMsgs()) {
				//TODO:update players
			}
		}
	}

	m_Neaded = false;
	closesocket(*m_Soc);
	printf("Kapcsolat bontasa(%s)\n", m_Soc);
}

list<string> ReadThread::getReplays(string reply) {
	list<string> strs;
	vector<string> st = Utility::split(reply,ClientSide::BREAK_CHAR_MSG_START);
	if (m_OldMsg != "") {
		strs.push_back(m_OldMsg + st[0].substr(0,st[0].length() - 1));
		for (int i = 1; i < st.size() - 1; ++i) {
			strs.push_back(st[i].substr(0, st[i].length() - 1));
		}
		m_OldMsg = "";
	}
	else {
		for (int i = 1; i < st.size() - 1; ++i) {
			strs.push_back(st[i].substr(0, st[i].length() - 1));
		}
	}
	if (st[st.size() - 1].find(ClientSide::BREAK_CHAR_MSG_STOP) != string::npos) {
		strs.push_back(st[st.size() - 1].substr(0, st[st.size() - 1].length() - 1));
	}
	else {
		m_OldMsg = st[st.size() - 1];
	}
	return strs;
}

bool ReadThread::preRender(std::string replay)
{
	vector<string> parts = Utility::split(replay,ClientSide::BREAK_CHAR);
	if (parts[1] == ClientSide::TYPE_MSG) {
		FullMsg::addMsg(parts);
	}
	else if (parts[1] == ClientSide::TYPE_DISCONNECT) {
		//TODO: delete player
	}
	else if (parts[1] == ClientSide::TYPE_LOGIN) {
		//TODO: create new player
	}
	return false;
}
