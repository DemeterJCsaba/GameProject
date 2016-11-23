#include "Utility.h"



void Utility::removeQuotes(string& str) {
	str = str.substr(1, str.length() - 2);
}
