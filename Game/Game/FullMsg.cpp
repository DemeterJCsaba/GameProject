#include "FullMsg.h"
#include"Utility.h"
#include"ClientSide.h"

std::map<std::string, FullMsg> FullMsg::s_FullMsgs = std::map<std::string, FullMsg>();

void FullMsg::addMsg(std::vector<std::string> parts)
{
	auto f = s_FullMsgs.find(parts[0]);
	if (f == s_FullMsgs.end()) {//ha meg nincs
		s_FullMsgs.insert(std::pair<std::string,FullMsg>(parts[0],FullMsg(parts)));
	}
	else {//ha mar van
		FullMsg m = f->second;
		std::vector<std::string> nums = Utility::split(parts[2], '/');
		int nr = std::stoi(nums[0]);
		m.m_Msgs.push_back(Msg(parts[3],nr));
	}
}

std::list<std::string> FullMsg::getFullMsgs()
{
	std::list<std::string> lista;

	for (auto f : s_FullMsgs) {
		if (f.second.chack()) {
			lista.push_back(f.second.m_Msg);
			f.second.m_isBuildt = true;
			s_FullMsgs.erase(f.first);
		}
	}

	return lista;
}

FullMsg::FullMsg(std::vector<std::string> parts) {
	std::vector<std::string> nums = Utility::split(parts[2], '/');
	m_MaxNumber = std::stoi(nums[1]);
	m_Msgs.push_back(Msg(parts[3],std::stoi(nums[0])));
}

bool FullMsg::chack() {
	for (int i = 1; i <= m_MaxNumber; ++i) {
		try {
			Msg m = getI(i);
			m_Msg += m.m_Msg;
		}
		catch (exception e) {
			m_Msg = "";
			return false;
		}
	}
	return true;
}

Msg FullMsg::getI(int i) {
	for (auto a : m_Msgs) {
		if (a.m_number == i) {
			return a;
		}
	}
	throw exception("Nincs ilyen Msg!");
}
