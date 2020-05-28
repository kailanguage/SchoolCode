#include<windows.h>
#include<iostream>
#include<process.h>
using namespace std;
HANDLE evRead, evFinish;
void ReadThread(LPVOID param)
{
	cout << "Reading" << endl;
	WaitForSingleObject(evRead, INFINITE);
	SetEvent(evFinish);
}
void WriteThread(LPVOID param)
{
	cout << "Writing" << endl;
	SetEvent(evRead);
}


int main() {
	
	_beginthread(ReadThread, 0, NULL);
	_beginthread(WriteThread, 0, NULL);

	evRead = CreateEvent(NULL, FALSE, FALSE, NULL);
	evFinish = CreateEvent(NULL, FALSE, FALSE, NULL);
	WaitForSingleObject(evFinish, INFINITE);
	cout << "The Program is End\n";
}
