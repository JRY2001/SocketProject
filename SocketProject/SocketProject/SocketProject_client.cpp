// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <winsock2.h>
#include <stdio.h>
#include<string.h>

// Need to link with Ws2_32.lib
#pragma comment(lib, "ws2_32.lib")
#include <iostream>

//文件发送函数
void send_file(char* filename, char* ip, u_short port) {
	//-------初始化-------

	//initiates use of the Winsock DLL by a process
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	//读取文件
	FILE* fp;
	int fr = fopen_s(&fp,filename, "rb");
	if (fr != 0)
	{
		printf("文件读取出错");
		return;
	}
	
	//启动winsock动态链接库，并检查是否出错
	err = WSAStartup(0x202, &wsaData);
	if (err != 0) {
		printf("WSAStartup failed with error: %d\n", err);
		return;
	}
	
	//-------连接--------
	//创建一个socket
	SOCKET s = socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in dest_addr;
	memset((void*)&dest_addr, 0, sizeof(dest_addr));//初始化dest_addr
	dest_addr.sin_family = AF_INET;//地址族(ipv4)
	dest_addr.sin_addr.s_addr = inet_addr(ip);//目的ip地址
	dest_addr.sin_port = htons(port);//使用端口号
	
	//创建连接
	printf("正在连接中...");
	int connect_err = connect(s, (struct sockaddr *)&dest_addr, sizeof(dest_addr));
	//sockaddr_in是sockaddr的优化，二者可互相转化且指向sockaddr的指针也可指向sockaddr_in
	if (connect_err != 0) {
		printf("连接出错");
		return;
	}
	else {
		printf("连接成功");
	}

	//-------发送--------
	send(s, filename, strlen(filename), 0);
}
int main()
{
	char a[3] = { '1','2','3' };
	char b[3] = { '1','2','3' };
	std::cout << "Hello World!\n";
	send_file(a, b, 0000);
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
