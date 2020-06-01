#pragma once
#include <iostream>
#include<string>
using namespace std;

string LowCase(string x) {
	unsigned int xlen = x.length();
	for (unsigned int i = 0; i < xlen; i++) {
		if (x[i] > 'A' && x[i] < 'Z') {
			x[i] += 32;
		}
	}
	return x;
}



int LoadStrFile(string szFileName, string szData[]) {
	cout << "load " << szFileName << ":" << endl;
	ifstream srcFile(szFileName, ios::in);
	int n = 0;
	while (getline(srcFile, szData[n])) {
		//srcFile >> noskipws >> szData[n];
		//srcFile >> szData[n];
		n++;
		if (n > 199) {
			break;
		}
		cout << szData[n - 1] << endl;
	}

	return n;
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


