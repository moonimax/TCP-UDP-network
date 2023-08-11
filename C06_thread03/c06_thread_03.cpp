#include <stdio.h>
#include <windows.h>

int sum = 0;

DWORD WINAPI my_thread(LPVOID arg)
{
	int num = (int)(long long)arg;
	for (int i = 1; i <= num; i++)
		sum += i;

	return 0;
}

int main(int argc, char* argv[])
{
	int num = 100;
	HANDLE hTrhead = CreateThread(NULL, 0, my_thread, (LPVOID)(long long)num, CREATE_SUSPENDED, NULL);

	printf("before executing the thread. calculation result = %d\n", sum);
	ResumeThread(hTrhead);
	WaitForSingleObject(hTrhead, INFINITE);
	printf("after executing the thread. calculation result = %d\n", sum);
	CloseHandle(hTrhead);

	return 0;
}