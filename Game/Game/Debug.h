#pragma once

#include <iostream>

using namespace std;

#define DEBUG_MODE 1

#if DEBUG_MODE
#define DEBUG(x) (cout << (x) << endl);
#else
#define DEBUG(x) ;
#endif