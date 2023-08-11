#include "../common.h"

struct Point3D
{
	int x, y, z;
};

//쓰레드를 순서대로 호출시킴
DWORD WINAPI MyThread(LPVOID arg)
{
	//1초뒤에 실행시킴
	Sleep(1000);
	Point3D* pt = (Point3D*)arg;
	printf("Running my thread() %d: %d, %d, %d\n", GetCurrentThreadId(), pt->x, pt->y, pt->z);
	return 0;
}

int main(int argc, char* argv[])
{
	Point3D pt1 = { 10, 20, 30 };
	HANDLE hThread1 = CreateThread(NULL, 0, MyThread, &pt1, 0, NULL);
	//아래와 같이 생성하면 실행은 되지 않을것임
	//HANDLE hThread1 = CreateThread(NULL, 0, MyThread, &pt1, CREATE_SUSPENDED, NULL);
	
	if (NULL == hThread1)
		CloseHandle(hThread1);

	Point3D pt2 = { 40, 50, 60 };
	HANDLE hThread2 = CreateThread(NULL, 0, MyThread, &pt2, 0, NULL);
	if (NULL == hThread2)
		CloseHandle(hThread2);

	printf("Running main() %d\n", GetCurrentThreadId());
	//2초뒤에 실행을 시킴ㄴ
	Sleep(2000);

	//ResumeThread(hThread1);
	return 0;
}