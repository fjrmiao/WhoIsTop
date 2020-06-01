#pragma once
#include <iostream>
#include <fstream>
#include <windows.h>
#include "public.h"

using namespace std;
class whoistop {
	HWND hCurrentTop=0;
	HWND hOldTop = 0;
	

	bool bWantLock = false;
	int AllowInTopCount=0;
	string szAllowInTop[200];
	void init(string filestr) {
		AllowInTopCount = LoadStrFile(filestr, szAllowInTop);
	}

	public:
		whoistop() {
			init("AllowInTop.txt");
		}
		whoistop(string filestr) {
			init(filestr);
		}
		void scan(){
			//hDesktop = GetDesktopWindow();hCurrentTop = GetTopWindow(hDesktop);
			hCurrentTop = GetForegroundWindow();
			//hCurrentTop = GetTopWindow(NULL);

			if (hCurrentTop != hOldTop && hCurrentTop != 0) {
				DWORD pidCurrentTop;
				TCHAR szFileName[255] = { 0 };


				bool  bIsAllowInTop = false;

				hOldTop = hCurrentTop;
				GetWindowThreadProcessId(hCurrentTop, &pidCurrentTop);

				HANDLE handle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
					0, pidCurrentTop);
				if (handle)
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
						cout << "!!!!!!!!!!!!!!!Lock>>>";
						bWantLock = 0;
					}
					if (bWantLock == 0 && bIsAllowInTop == 1) {
						bWantLock = 1;
					}
					CloseHandle(handle);
				}

				cout << "HWND = " << hCurrentTop << "\t PID = " << pidCurrentTop << "\t FileName = " << szFileName << "\t AllowInTop = " << bIsAllowInTop << endl;


			}
		}
};