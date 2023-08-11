// headers

#include <WinSock2.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//	winsock2 library //���� ���� �����
#pragma comment(lib, "ws2_32")

//	define constants
//��Ʈ������ ���ۻ����� 512byte�� ����
#define	SERVER_PORT		9000
#define BUFSIZE			512

int main(int argc, char* argv[])
{
//	initialize //������ ���� �ʱ�ȭ
	WSADATA wsa;
	if (0 != WSAStartup(MAKEWORD(2, 2), &wsa))
	{
		printf("WSAStartup error\n");
		return 1;
	}

//	create socket //Sock_STREAM�� TCP�� ����ϰٴٴ� �ǹ�
	SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == listen_sock)
	{
		printf("socket error\n");
		return 1;
	}

//	set server infomation
	// ����ü�� ��� �����ϱ�. SOCKADDR_IN

	struct sockaddr_in serveraddr; 
	memset(&serveraddr, 0, sizeof(serveraddr));	 
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY); //INADDR_ANY�� �� ���� IP�ּ�
	serveraddr.sin_port = htons(SERVER_PORT); //��Ʈ��ȣ ����

//	bind
	int retval = bind(listen_sock, (struct sockaddr*)&serveraddr, sizeof(serveraddr)); //�� ��ȯ �ʿ�
	if (SOCKET_ERROR == retval)
	{
		printf("bind error: %d\n", retval);
		return 1;
	}

//	listen
	retval = listen(listen_sock, SOMAXCONN); 
	if (SOCKET_ERROR == retval)
	{
		printf("listen error: %d\n", retval); 
		return 1;
	}

//	release resources
	closesocket(listen_sock);

	WSACleanup();

	return 0;
}