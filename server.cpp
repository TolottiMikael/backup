#include <iostream>
#include <stdio.h>
#include <winsock2.h>

using namespace std;

void comunica(){
    WSADATA WSAData;

    SOCKET server, client, client2;

    SOCKADDR_IN serverAddr, clientAddr, clientAddr2;

    WSAStartup(MAKEWORD(2,0), &WSAData);
    server = socket(AF_INET, SOCK_STREAM, 0);

    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(5555);

    bind(server, (SOCKADDR *)&serverAddr, sizeof(serverAddr));
    listen(server, 0);

    printf("Listening for incoming connections...\n");
    bool a = true;
    char buffer[1024];
    int clientAddrSize = sizeof(clientAddr);
    int clientAddrSize2 = sizeof(clientAddr2);
    if((client = accept(server, (SOCKADDR *)&clientAddr, &clientAddrSize)) != INVALID_SOCKET)
    {

        printf("Client 1 connected!\n");
        do{
        if((client2 = accept(server, (SOCKADDR *)&clientAddr2, &clientAddrSize2)) != INVALID_SOCKET){
           printf("Client 2 connected!\n");
           a = false;
        }
        } while(a);

        while (strcmp(buffer,"end")!=0){

            recv(client, buffer, sizeof(buffer), 0);

            recv(client2, buffer, sizeof(buffer), 0);
            printf("Client 2 says: %s\n",buffer);

        }

        closesocket(client);
        printf("Client disconnected.");
    }
}

int main()
{
    comunica();
}
