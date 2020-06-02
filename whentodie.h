#pragma once
#include <iostream>
#include <fstream>
#include <windows.h>

#include "public.h"
using namespace std;

typedef struct _ZoneData {
	string ZoneType;//date,week
	string DateBegin;
	string TimeBegin;
	string DateEnd;
	string TimeEnd;
	string Action;
} ZoneData;

string ProcessItem(string x, void* data) {
	int  iSpliteLoc = x.find(">>>", 0);
	if (iSpliteLoc >= 0) {
		string szItemType = x.substr(0, iSpliteLoc);
		//cout << szItemType << endl;
		if (szItemType == "Zone") {
			//cout << "dadadadada" << endl;
			return x;
		}
		else {
			return "";
		}
	}
	return "";
}

class whentodie {

	int TimeItemsCount = 0;
	string szTimeItems[200];

	

	void init(string filestr) {
		int test = 0;
		TimeItemsCount = LoadStrFile(filestr, szTimeItems, ProcessItem,&test );
		cout << test;
		for (int i = 0; i < TimeItemsCount; i++) {
			//cout << szTimeItems[i] << "->->->" << szTimeItems[i].find(">>>",0)<<endl;
			
			
				
			
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