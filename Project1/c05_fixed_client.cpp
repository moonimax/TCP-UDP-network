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
		"안녕하세요",
		"반가워요",
		"오늘따라 할 이야기가 많을 것 같네요",
		"저도 그렇네요"
		
	};


	//해당 부분에서 복사붙히기 해서 사용하면됨
	//for문 안에서 채팅프로그램을 구현할수 있는 능력을 줄 수 있음
	for (int i = 0; i < 4; i++)
	{
		memset(buf, '#', sizeof(buf));  //버퍼의 길이만큼 #을 채워줌
		strncpy(buf, testdata[i], strlen(testdata[i])); //순차적으로 돌면서 버퍼에 채워줌

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

