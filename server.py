import socket

host = '26.199.90.194'
port = 12345

server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind((host, port))

print("Server STARTED")
server_socket.listen(1)
client_socket, addr = server_socket.accept()
print("Client connected from:", addr)
while True:
    
    try: 
        command = input("write command: ").strip()

        if command == '' or command is None or command == ' ':
            print("EOF error")
            continue
        client_socket.send(command.encode())
        data = client_socket.recv(1024)

        print("Client: ", data.decode())
    except KeyboardInterrupt:
        command = "disconnect"
        print(command)
        client_socket.send(command.encode())
        client_socket.close()
        server_socket.close()
        break


