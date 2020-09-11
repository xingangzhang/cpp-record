// 非unix系统
#if defined(_MSC_VER) || defined(__MINGW32__) || defined(WIN32)

#include <ws2tcpip.h>
#include <windows.h>

#define close closesocket

class WinSockInit {
    WSADATA _wsa;
public:
    WinSockInit() { // 分配套接字版本信息2.0 WSA变量地址
        WSAStartup(MAKEWORD(2, 0), &_wsa);

    }

    ~WinSockInit() {
        WSACleanup(); // 终止ws2_32.dll
    }
};

// Unix系统
#else
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif

#include <iostream>
#include <string>

using namespace std;

// 处理URL
void router(int clientSock, string const &url) {
    string hint;
    cout << url << " 收到信息\n";
    if (url == "/") {
        hint = "<h1 style=\"text-align: center;\">主页</h1>";
        send(clientSock, hint.c_str(), hint.length(), 0);
    } else if (url == "/test") {
        hint = "测试接口";
        send(clientSock, hint.c_str(), hint.length(), 0);
    } else {
        hint = "404";
        send(clientSock, hint.c_str(), hint.length(), 0);
    }
}

int main() {
#if defined(_MSC_VER) || defined(__MINGW32__) || defined(WIN32)
    WinSockInit sockInit; // 为windows系统 进行WSAStartup
#endif

    int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); // 建立套接字 失败返回-1
    sockaddr_in addr = {0};
    addr.sin_family = AF_INET; // 指定地址族
    addr.sin_addr.s_addr = INADDR_ANY; // ip初始化
    addr.sin_port = htons(8080); // 端口号初始化

    bind(sock, (sockaddr *) &addr, sizeof(addr)); // 分配ip和端口

    listen(sock, 0); // 设置监听

    // 设置客户端
    sockaddr_in clientAddr;
    int clientAddrSize = sizeof(clientAddr);
    int clientSock;
    // 接受客户端请求
    while (-1 != (clientSock = accept(sock, (sockaddr *) &clientAddr, (socklen_t *) &clientAddrSize))) {
        // 收请求
        string requestStr;
        int bufSize = 4096;
        requestStr.resize(bufSize);
        // 接受数据
        recv(clientSock, &requestStr[0], bufSize, 0);

        // 取得第一行
        string firstLine = requestStr.substr(0, requestStr.find("\r\n"));
        // 获取url substr 复制函数 参数为起始位置(默认0) 复制的字符数目
        firstLine = firstLine.substr(firstLine.find(" ") + 1);
        // find返回找到的第一个匹配字符串的位置 而不管其后是否还有相匹配的字符串。
        string url = firstLine.substr(0, firstLine.find(" "));

        // 发送响应头
        string response =
                "HTTP/1.1 200 OK\r\n"
                "Content-Type: text/html; charset=gbk\r\n"
                "Connection: close\r\n"
                "\r\n";
        send(clientSock, response.c_str(), response.length(), 0);
        // 处理url
        router(clientSock, url);
        close(clientSock); // 关闭客户端套接字
    }
    close(sock); // 关闭服务器套接字
    return 0;
}