import socket

host = '26.199.90.194'
port = 12345

server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind((host, port))

print("Server STARTED")
server_socket.listen(1)
client_socket, addr = server_socket.accept()

while True:


    print("Client connected from:", addr)
    command = input("write command: ")
    client_socket.send(command.encode())
    data = client_socket.recv(1024)
    print("Client: ", data.decode())

server_socket.close()
