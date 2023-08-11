//오류 처리 관련 함수들이 선언되어 있음
//err_quit함수는 프로그램을 종료하고 오류 메시지를 출력
//err_dis[play함수는 오류 메시지를 출력
#include "../common.h"


//exercise 3-1
// 호스트 바이트와 네트워크 바이트 간의 변환을 테스트하기 위한 예제 코드
int main(int argc, char* argv[])
{
//	initialize WinSock //1. Winsock을 초기화
	WSADATA wsa;
	if (0 != WSAStartup(MAKEWORD(2, 2), &wsa))
		err_quit("WSAStartup()");

	//x1, y1 변수를 할당하고 호스트바이트에서 네트워크 바이트로 변환하여 할당
	u_short x1 = 0x1234;
	u_long y1 = 0x12345678;
	u_short x2;
	u_long y2;

//	host byte -> network byte
	
// byte order를 바꾸는 함수인 htons, htonl을 사용하여 host byte order에서 netwokr byte order로 바꿔 출력

	printf("[호스트 바이트 -> 네트워크 바이트]\n");
	printf("%#x -> %#x\n", x1, x2 = htons(x1));
	printf("%#x -> %#x\n", y1, y2 = htonl(y1));

//	network byte -> host byte
// network byte orer -> host byte order로 바꿔줌
	printf("[네트워크 바이트 -> 호스트 바이트]\n");
	printf("%#x -> %#x\n", x2, ntohs(x2));
	printf("%#x -> %#x\n", y2, ntohl(y2));

//	misuse case
//잘못 사용한 경우에도 printf로 출력해줌

	printf("[잘못된 사용 예]\n");
	printf("%#x -> %#x\n", x1, ntohl(x1));

//	close Winsock
	WSACleanup();

	return 0;
}



//	exercise 3-2
//IPv4와 IPv6 주소간 변환을 테스트하기 위한 코드
int main(int argc, char* argv[])
{
//	initialize WinSock
	//Winsock을 초기화
	WSADATA wsa;
	if (0 != WSAStartup(MAKEWORD(2, 2), &wsa))
		err_quit("WSAStartup()");

//char 포인터에서 IPv4, IPv6 주소를 각각 할당하고, inet_pton함수를 사용하여 해당 주소를 struct in_addr 또는 struct in6_addr 타입의 변수로 변환
// 이후 inet_ntop 함수를 사용해서 다시 변수들을 주소 문자열로 변환한다.
//	IPv4
	const char* ipv4test = "147.46.114.70";
	printf("IPv4 address (before transformation) = %s\n", ipv4test);

	struct in_addr ipv4num;
	inet_pton(AF_INET, ipv4test, &ipv4num);
	printf("IPv4 a1181888147ddress (after transformation) = %#x\n", ipv4num.S_un.S_addr);

	char ipv4str[INET_ADDRSTRLEN] = { 0, };
 	inet_ntop(AF_INET, &ipv4num, ipv4str, sizeof(ipv4str));
	printf("IPv4 address (after transformation again) = %s\n", ipv4str);
	printf("\n");

//	IPv6
	const char* ipv6test = "2001:0230:abcd:ffab:0023:eb00:ffff:1111";
	printf("IPv6 address (before transformation) = %s\n", ipv6test);

	struct in6_addr ipv6num;
	inet_pton(AF_INET6, ipv6test, &ipv6num);
	printf("IPv6 address (after transformation) = 0x");
	for (int i = 0; i < 16; i++)
		printf("%02x", ipv6num.s6_addr[i]);
	printf("\n");

	char ipv6str[INET6_ADDRSTRLEN] = {0, };
	inet_ntop(AF_INET6, &ipv6num, ipv6str, sizeof(ipv6str));
	printf("IPv4 address (after transformation again) = %s\n", ipv6str);
	printf("\n");

	//	close Winsock
	WSACleanup();

	return 0;
}


#define TESTNAME	"www.google.com"
bool GetIPAddr(IN const char* name, OUT struct in_addr* addr);
bool GetDomainName(IN struct in_addr addr, OUT char* name, int namelen);

//세번째 예전는 도메인 이름과 IP주소간의 변환을 보여준다.
//excercise 3-3

int main(int argc, char* argv[])
{
//	initialize WinSock
	WSADATA wsa;
	if (0 != WSAStartup(MAKEWORD(2, 2), &wsa))
		err_quit("WSAStartup()");

	printf("Domain name (before transformation) = %s\n", TESTNAME);

//	domain name -> ip address
	struct in_addr addr;
	if (GetIPAddr(TESTNAME, &addr))
	{
		char str[INET_ADDRSTRLEN] = { 0, };
		inet_ntop(AF_INET, &addr, str, sizeof(str));
		printf("IP address (after transformation) = %s\n", str) ;

		char name[256] = { 0, };
		if(GetDomainName(addr, name, sizeof(name)))
			printf("Domain name (after transformation again) = %s\n", name);
	}

//	close Winsock
	WSACleanup();

	return 0;
}

bool GetIPAddr(IN const char* name, OUT struct in_addr* addr)
{
	//도메인 이름을 IP 주소로 변환
	struct hostent* ptr = gethostbyname(name);
	if (NULL == ptr)
	{
		err_display("gethostbyname()");
		return false;
	}

	if (AF_INET != ptr->h_addrtype)
		return false;

	memcpy(addr, ptr->h_addr, ptr->h_length);

	return true;
}

bool GetDomainName(IN struct in_addr addr, OUT char* name, int namelen)
{
	//IP주소를 도메인 이름으로 변환
	struct hostent* ptr = gethostbyaddr((const char*)&addr, sizeof(addr), AF_INET);
	if (NULL == ptr)
	{
		err_display("gethostbyaddr()");
		return false;
	}

	if (AF_INET != ptr->h_addrtype)
		return false;

	strncpy(name, ptr->h_name, namelen);

	return TRUE;
}
