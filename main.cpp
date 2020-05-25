#include <iostream>
#include <fstream>
#include <windows.h>

using namespace std;

int LoadStrFile(string szFileName,string szData[]) {
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
	HWND hOldTop;
	HWND hMe;
	string szAllowInTop[200];

	hOldTop = 0;

	int AllowInTopCount = LoadStrFile("in.txt", szAllowInTop);
	hMe = GetConsoleWindow();
	ShowWindow(hMe, SW_HIDE);
	bool bWantLock = false;
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
						if (szAllowInTop[i] == szFileName) {
							bIsAllowInTop = true;
							break;
						}
					}
					
					if (bWantLock == 1 && bIsAllowInTop == 0) {
						LockWorkStation();
						printf("!!!!!!!!!!!!!!!Lock\n");
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
