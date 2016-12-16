#ifndef EVENT_H
#define EVENT_H

#include <string>

using namespace std;

class Event {
private:
	string m_Action;
public:
	Event(string action);

	string& getAction() { return m_Action; }
};


#endif // !EVENT_H

