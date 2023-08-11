// headers

#include <WinSock2.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//	winsock2 library //서버 소켓 만들기
#pragma comment(lib, "ws2_32")

//	define constants
//포트지정과 버퍼사이즈 512byte로 조정
#define	SERVER_PORT		9000
#define BUFSIZE			512

int main(int argc, char* argv[])
{
//	initialize //윈도우 소켓 초기화
	WSADATA wsa;
	if (0 != WSAStartup(MAKEWORD(2, 2), &wsa))
	{
		printf("WSAStartup error\n");
		return 1;
	}

//	create socket //Sock_STREAM은 TCP을 사용하겟다는 의미
	SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == listen_sock)
	{
		printf("socket error\n");
		return 1;
	}

//	set server infomation
	// 구조체에 담아 설정하기. SOCKADDR_IN

	struct sockaddr_in serveraddr; 
	memset(&serveraddr, 0, sizeof(serveraddr));	 
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY); //INADDR_ANY는 내 로컬 IP주소
	serveraddr.sin_port = htons(SERVER_PORT); //포트번호 지정

//	bind
	int retval = bind(listen_sock, (struct sockaddr*)&serveraddr, sizeof(serveraddr)); //형 변환 필요
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