#pragma once
#include<string>

using namespace std;

class Utility
{
public:
	static void removeQuotes(string& str) {
		str = str.substr(1, str.size() - 1);
	}
};

