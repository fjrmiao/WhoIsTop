#pragma once
#include <iostream>
#include <fstream>
#include <windows.h>

#include "public.h"
using namespace std;
class whentodie {

	int TimeItemsCount = 0;
	string szTimeItems[200];

	void init(string filestr) {
		TimeItemsCount = LoadStrFile(filestr, szTimeItems);
		for (int i = 0; i < TimeItemsCount; i++) {
			cout << szTimeItems[i] << "->->->" << szTimeItems[i].find(">>>",0)<<endl;
			
		}
	}

public:
	whentodie() {
		init("TaskList.txt");
	}
	whentodie(string filestr) {
		init(filestr);
	}

};