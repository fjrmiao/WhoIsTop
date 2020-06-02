#pragma once
#include <iostream>
#include<string>
using namespace std;

string LowCase(string x,void * data) {
	unsigned int xlen = x.length();
	for (unsigned int i = 0; i < xlen; i++) {
		if (x[i] > 'A' && x[i] < 'Z') {
			x[i] += 32;
		}
	}
	return x;
}
string LowCase(string x) {
	return LowCase(x, NULL);
}

string NoProcessStr(string x,void * data) {
	return x;
}



int LoadStrFile(string szFileName, string szData[], string (*strproc)(string,void *),void * data) {
	cout << "load " << szFileName << ":" << endl;
	ifstream srcFile(szFileName, ios::in);
	int n = 0;
	string verstr = "";
	getline(srcFile, verstr);
	if (verstr != "Ver 0.2") {
		cout << szFileName << " Version Error" << endl;
		return 0;
	}
	else{
		cout << szFileName << " Version Right" << endl;
	}

	while (getline(srcFile, szData[n])) {
		//srcFile >> noskipws >> szData[n];
		//srcFile >> szData[n];
		szData[n] = strproc(szData[n],data);
		if (szData[n] != "") {
			cout << szData[n] << endl;
			n++;
		}
		if (n > 199) {
			break;
		}
		
	}

	return n;
}

int LoadStrFile(string szFileName, string szData[], string(*strproc)(string, void*)) {
	return LoadStrFile(szFileName, szData, strproc, NULL);
}

int LoadStrFile(string szFileName, string szData[]) {
	return LoadStrFile(szFileName, szData, NoProcessStr,NULL);
}

void HideConsoleWindow() {
	HWND hMe;
	TCHAR szCurrentPath[255] = { 0 };
	bool bHideConsole = true;
	GetCurrentDirectory(200, szCurrentPath);
	DWORD NoHideAttr = GetFileAttributes("NoHide");
	hMe = GetConsoleWindow();
	if (NoHideAttr != 0xffffffff)
	{
		ShowWindow(hMe, SW_SHOW);
	}
	else {
		ShowWindow(hMe, SW_HIDE);

	}
	cout << "CurrentPath = " << szCurrentPath << " \t NoHide Attrib =" << NoHideAttr << endl;
}


