#include <iostream>
#include <fstream>
#include <windows.h>

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

string LowCase(char *y) {
	string x = y;
	unsigned int xlen = x.length();
	for (unsigned int i = 0; i < xlen; i++) {
		if (x[i] > 'A' && x[i] < 'Z') {
			x[i] += 32;
		}
	}
	return x;
}

int LoadStrFile(string szFileName,string szData[]) {
	cout << "load " <<szFileName  << ":" << endl;
	ifstream srcFile(szFileName, ios::in);
	int n = 0;
	while (srcFile >> szData[n]) {
		n++;
		if (n > 199) {
			break;
		}
		cout << szData[n-1] << endl;
	}
		
	return n;
}

int main(int argc, char** argv) {
	HWND hDesktop;
	HWND hCurrentTop;
	HWND hOldTop=0;
	HWND hMe;
	string szAllowInTop[200];
	TCHAR szCurrentPath[255] = { 0 };
	bool bHideConsole = true;

	GetCurrentDirectory( 200, szCurrentPath);
	DWORD NoHideAttr = GetFileAttributes("NoHide");
	hMe = GetConsoleWindow();
	if (NoHideAttr != 0xffffffff)
	{
		ShowWindow(hMe, SW_SHOW);
	}
	else{
		ShowWindow(hMe, SW_HIDE);

	}
	printf("CurrentPath = %s \t NoHide Attrib = %d\n", szCurrentPath, NoHideAttr);

	int AllowInTopCount = LoadStrFile("AllowInTop.txt", szAllowInTop);

	bool bWantLock = false;

	cout << "Who is Top:" << endl;
	while(1){
		hDesktop = GetDesktopWindow();
		//hCurrentTop = GetForegroundWindow();
		hCurrentTop = GetTopWindow(hDesktop);
		
		if(hCurrentTop!=hOldTop){
			DWORD pidCurrentTop;
			TCHAR szFileName[255] = { 0 };

			
			bool  bIsAllowInTop = false;

			hOldTop=hCurrentTop;
			GetWindowThreadProcessId(hCurrentTop,&pidCurrentTop);

			HANDLE handle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
					               0, pidCurrentTop);
				if(handle)
				{
					DWORD maxsize = 255;
					QueryFullProcessImageName(handle, 0, szFileName, &maxsize);
					for (int i = 0; i < AllowInTopCount; i++) {
						
						if (LowCase(szAllowInTop[i]) == LowCase(szFileName)) {
							bIsAllowInTop = true;
							break;
						}
					}
					
					if (bWantLock == 1 && bIsAllowInTop == 0) {
						LockWorkStation();
						printf("!!!!!!!!!!!!!!!Lock>>>");
						bWantLock = 0;
					}
					if (bWantLock == 0 && bIsAllowInTop == 1) {
						bWantLock = 1;
					}
					CloseHandle(handle);
				}

			printf("HWND = %p\t PID = %d\t FileName = %s\t AllowInTop = %d \n",hCurrentTop,pidCurrentTop,szFileName, bIsAllowInTop);
			
			
		}
	}
	return 0;
}
