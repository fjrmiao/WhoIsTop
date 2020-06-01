#include <iostream>
#include <fstream>
#include <windows.h>

#include "public.h"
#include "whoistop.h"
#include "whentodie.h"
using namespace std;

whoistop *WIT;
whentodie* WTD;

void CALLBACK TimerProcWIT(	HWND hWnd,	UINT nMsg,	UINT_PTR dwUser,	DWORD dwTime) {
	WIT->scan();
}

void CALLBACK TimerProcWTD(HWND hWnd, UINT nMsg, UINT_PTR dwUser, DWORD dwTime) {

	SYSTEMTIME sys;
	GetLocalTime(&sys);
	//cout << sys.wYear << "//"  << sys.wMonth <<  "//" << sys.wDay  << endl;

}

int main(int argc, char** argv) {
	//HWND hDesktop;

	
	HideConsoleWindow();
	
	WIT = new whoistop();
	SetTimer(NULL, 1000, 200, TimerProcWIT);

	WTD = new whentodie();
	SetTimer(NULL, 2000, 1000, TimerProcWTD);

	
	cout << "Who is Top:" << endl;
	
	while(1){
		MSG   msg;
		if(GetMessage(&msg, NULL, 0, 0)){
			 if (msg.message == WM_TIMER){
				             DispatchMessage(&msg);
				}
		}
		
	}
	return 0;
}
