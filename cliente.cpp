#include <iostream>
#include <thread>
#include <stdio.h>
#include <winsock2.h>

using namespace std;

bool gameover = false;

string resp;
string ques;

void comunica(){
    WSADATA WSAData;
    SOCKET server;
    SOCKADDR_IN addr;

    WSAStartup(MAKEWORD(2,0), &WSAData);
    server = socket(AF_INET, SOCK_STREAM, 0);

    addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // replace the ip with your futur server ip address. If server AND client are running on the same computer, you can use the local ip 127.0.0.1
    addr.sin_family = AF_INET;
    addr.sin_port = htons(5555);

    connect(server, (SOCKADDR *)&addr, sizeof(addr));
    printf("Connected to server!\n");

    char buffer[1024];

    while (resp != "end" && !gameover){
        send(server, ques, sizeof(ques), 0);
        recv(server, resp, sizeof(resp), 0);
    }

    closesocket(server);
    WSACleanup();
    printf("Socket closed.");
}

void prog(){

    cout<< "server disse que: " << resp << endl;

}


int main(){

    thread com(comunica);
    thread exec(prog);

    com.join();
    exec.join();
    return 0;

}
