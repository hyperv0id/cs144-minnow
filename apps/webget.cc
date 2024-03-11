#include "socket.hh"

#include <cstdlib>
#include <iostream>
#include <span>
#include <string>

using namespace std;

void get_URL(const string &host, const string &path) {

    // 1. 建立 TCP 连接

    Address addr(host, "http");
    TCPSocket sc;     // 创建 TCP 连接对象
    sc.connect(addr); // 连接到远程地址

    // Your code here.

    // You will need to connect to the "http" service on
    // the computer whose name is in the "host" string,
    // then request the URL path given in the "path" string.

    // 2. 发送HTTP请求
    string msg = "GET " + path + " HTTP/1.1\r\n"; // 注意必须以 \r\n 结尾
    msg += "Host: " + host + "\r\n";
    msg += "Connection: closed\r\n\r\n";
    sc.write(msg);
    sc.shutdown(SHUT_WR); // 表示不在向对方传输信息

    // Then you'll need to print out everything the server sends back,
    // (not just one call to read() -- everything) until you reach
    // the "eof" (end of file).

    // 3. 从服务端接收消息
    string data;
    while (!sc.eof()) {
        sc.read(data);
        cout << data;
    }

    // 4. 关闭 TCP 连接
    sc.close();

    // cerr << "Function called: get_URL(" << host << ", " << path << ").\n";
    // cerr << "Warning: get_URL() has not been implemented yet.\n";
}

int main(int argc, char *argv[]) {
    try {
        if (argc <= 0) {
            abort(); // For sticklers: don't try to access argv[0] if argc <= 0.
        }

        auto args = span(argv, argc);

        // The program takes two command-line arguments: the hostname and "path"
        // part of the URL. Print the usage message unless there are these two
        // arguments (plus the program name itself, so arg count = 3 in total).
        if (argc != 3) {
            cerr << "Usage: " << args.front() << " HOST PATH\n";
            cerr << "\tExample: " << args.front()
                 << " stanford.edu /class/cs144\n";
            return EXIT_FAILURE;
        }

        // Get the command-line arguments.
        const string host{args[1]};
        const string path{args[2]};

        // Call the student-written function.
        get_URL(host, path);
    } catch (const exception &e) {
        cerr << e.what() << "\n";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
