#include <windows.h>
#include <stdio.h>

//스레드의 포맷이다
DWORD WINAPI MyThread(LPVOID arg)
{
	while (1);

	return 0;
}

int main(int argc, char* argv[])
{

	//	display the value of each priority level
	printf("priority: %d ~ %d\n", THREAD_PRIORITY_IDLE, THREAD_PRIORITY_TIME_CRITICAL);

	//	how many cpus are in this system
	SYSTEM_INFO si;
	GetSystemInfo(&si);
	int num = (int)si.dwNumberOfProcessors;
	printf("number of CPUs = %d\n", num);

	//	create threads as the number of CPUs
	for (int i = 0; i < num; i++)
	{
		HANDLE hThread = CreateThread(NULL, 0, MyThread, NULL, 0, NULL);
		SetThreadPriority(hThread, THREAD_PRIORITY_ABOVE_NORMAL);
		CloseHandle(hThread);
	}

	HANDLE hPriority = GetCurrentThread();
	SetThreadPriority(hPriority, THREAD_PRIORITY_BELOW_NORMAL);
	Sleep(1000);
	printf("executing the main thread (%d)\n", GetThreadPriority(hPriority));

	return 0;

}
