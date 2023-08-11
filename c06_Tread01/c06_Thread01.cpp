#include "../common.h"

struct Point3D
{
	int x, y, z;
};

//�����带 ������� ȣ���Ŵ
DWORD WINAPI MyThread(LPVOID arg)
{
	//1�ʵڿ� �����Ŵ
	Sleep(1000);
	Point3D* pt = (Point3D*)arg;
	printf("Running my thread() %d: %d, %d, %d\n", GetCurrentThreadId(), pt->x, pt->y, pt->z);
	return 0;
}

int main(int argc, char* argv[])
{
	Point3D pt1 = { 10, 20, 30 };
	HANDLE hThread1 = CreateThread(NULL, 0, MyThread, &pt1, 0, NULL);
	//�Ʒ��� ���� �����ϸ� ������ ���� ��������
	//HANDLE hThread1 = CreateThread(NULL, 0, MyThread, &pt1, CREATE_SUSPENDED, NULL);
	
	if (NULL == hThread1)
		CloseHandle(hThread1);

	Point3D pt2 = { 40, 50, 60 };
	HANDLE hThread2 = CreateThread(NULL, 0, MyThread, &pt2, 0, NULL);
	if (NULL == hThread2)
		CloseHandle(hThread2);

	printf("Running main() %d\n", GetCurrentThreadId());
	//2�ʵڿ� ������ ��Ŵ��
	Sleep(2000);

	//ResumeThread(hThread1);
	return 0;
}