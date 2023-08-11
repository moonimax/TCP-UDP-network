#include "../common.h"
#include <string.h>


char* SERVERIP = (char*)"127.0.0.1";
#define SERVERPORT 9000
#define BUFSIZE    50

int main(int argc, char* argv[])
{
	int retval = -1;

	//	get IP address from users
	if (argc > 1)
		SERVERIP = argv[1];

	//	initialize winsock
	WSADATA wsa;
	if (0 != WSAStartup(MAKEWORD(2, 2), &wsa))
		return 1;

	//	create socket
	SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == sock)
		err_quit("socket()");

	// connect()
	struct sockaddr_in serveraddr;
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	inet_pton(AF_INET, SERVERIP, &serveraddr.sin_addr);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = connect(sock, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
	if (SOCKET_ERROR == retval)
		err_quit("connect()");

	//	variables declaration
	char buf[BUFSIZE + 1] = { 0, };
	const char* testdata[] = {
		"�ȳ��ϼ���",
		"�ݰ�����",
		"���õ��� �� �̾߱Ⱑ ���� �� ���׿�",
		"���� �׷��׿�"
		
	};


	//�ش� �κп��� ��������� �ؼ� ����ϸ��
	//for�� �ȿ��� ä�����α׷��� �����Ҽ� �ִ� �ɷ��� �� �� ����
	for (int i = 0; i < 4; i++)
	{
		memset(buf, '#', sizeof(buf));  //������ ���̸�ŭ #�� ä����
		strncpy(buf, testdata[i], strlen(testdata[i])); //���������� ���鼭 ���ۿ� ä����

		retval = send(sock, buf, BUFSIZE, 0);


		if (SOCKET_ERROR == retval)
		{
			err_display("send()");
			break;
		}
		printf("[TCP Client] %d bytes has been sent.\n", retval);
	}

	//	close socket
	closesocket(sock);

	//	close socket
	WSACleanup();

	return 0;
}
