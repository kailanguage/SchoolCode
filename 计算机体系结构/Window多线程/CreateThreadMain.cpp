#include<windows.h>
#include<iostream>
using namespace std;

DWORD WINAPI FunOne(LPVOID param) {
	
	while (true)
	{
		Sleep(1000);
		cout << "hello 1! \n";
	}

	return 0;
}

DWORD WINAPI FunTwo(LPVOID param) {

	while (true)
	{
		Sleep(1000);
		cout << "hello 2! \n";
	}

	return 0;
}

int main(int argc, char* argv[]) {
	int input = 0;
	HANDLE hand1 = CreateThread(NULL, 0, FunOne, (void*)&input, CREATE_SUSPENDED, NULL);
	HANDLE hand2 = CreateThread(NULL, 0, FunTwo, (void*)&input, CREATE_SUSPENDED, NULL);

	while (true) {
		cin >> input;
		switch (input){
		case 1:
			ResumeThread(hand1);
			break;
		case 2:
			SuspendThread(hand1);
			break;
		case 3:
			TerminateThread(hand1, 1);
			break;
		case 5:
			ResumeThread(hand2);
			break;
		case 6:
			SuspendThread(hand2);
			break;
		case 7:
			TerminateThread(hand2, 1);
			break;
		}
	}
	return 0;
}
