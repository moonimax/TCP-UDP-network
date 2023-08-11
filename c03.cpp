//���� ó�� ���� �Լ����� ����Ǿ� ����
//err_quit�Լ��� ���α׷��� �����ϰ� ���� �޽����� ���
//err_dis[play�Լ��� ���� �޽����� ���
#include "../common.h"


//exercise 3-1
// ȣ��Ʈ ����Ʈ�� ��Ʈ��ũ ����Ʈ ���� ��ȯ�� �׽�Ʈ�ϱ� ���� ���� �ڵ�
int main(int argc, char* argv[])
{
//	initialize WinSock //1. Winsock�� �ʱ�ȭ
	WSADATA wsa;
	if (0 != WSAStartup(MAKEWORD(2, 2), &wsa))
		err_quit("WSAStartup()");

	//x1, y1 ������ �Ҵ��ϰ� ȣ��Ʈ����Ʈ���� ��Ʈ��ũ ����Ʈ�� ��ȯ�Ͽ� �Ҵ�
	u_short x1 = 0x1234;
	u_long y1 = 0x12345678;
	u_short x2;
	u_long y2;

//	host byte -> network byte
	
// byte order�� �ٲٴ� �Լ��� htons, htonl�� ����Ͽ� host byte order���� netwokr byte order�� �ٲ� ���

	printf("[ȣ��Ʈ ����Ʈ -> ��Ʈ��ũ ����Ʈ]\n");
	printf("%#x -> %#x\n", x1, x2 = htons(x1));
	printf("%#x -> %#x\n", y1, y2 = htonl(y1));

//	network byte -> host byte
// network byte orer -> host byte order�� �ٲ���
	printf("[��Ʈ��ũ ����Ʈ -> ȣ��Ʈ ����Ʈ]\n");
	printf("%#x -> %#x\n", x2, ntohs(x2));
	printf("%#x -> %#x\n", y2, ntohl(y2));

//	misuse case
//�߸� ����� ��쿡�� printf�� �������

	printf("[�߸��� ��� ��]\n");
	printf("%#x -> %#x\n", x1, ntohl(x1));

//	close Winsock
	WSACleanup();

	return 0;
}



//	exercise 3-2
//IPv4�� IPv6 �ּҰ� ��ȯ�� �׽�Ʈ�ϱ� ���� �ڵ�
int main(int argc, char* argv[])
{
//	initialize WinSock
	//Winsock�� �ʱ�ȭ
	WSADATA wsa;
	if (0 != WSAStartup(MAKEWORD(2, 2), &wsa))
		err_quit("WSAStartup()");

//char �����Ϳ��� IPv4, IPv6 �ּҸ� ���� �Ҵ��ϰ�, inet_pton�Լ��� ����Ͽ� �ش� �ּҸ� struct in_addr �Ǵ� struct in6_addr Ÿ���� ������ ��ȯ
// ���� inet_ntop �Լ��� ����ؼ� �ٽ� �������� �ּ� ���ڿ��� ��ȯ�Ѵ�.
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

//����° ������ ������ �̸��� IP�ּҰ��� ��ȯ�� �����ش�.
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
	//������ �̸��� IP �ּҷ� ��ȯ
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
	//IP�ּҸ� ������ �̸����� ��ȯ
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
