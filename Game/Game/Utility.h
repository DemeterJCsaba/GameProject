#pragma once
#include<string>
#include<vector>

using namespace std;

class Utility
{
public:
	static void removeQuotes(string& str);
	static void split(const std::string &s, char delim, std::vector<std::string> &elems);
	static vector<string> split(const std::string &s, char delim);
};