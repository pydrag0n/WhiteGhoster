import socket

class ServerSock(socket.socket):
    def __init__(self, HOST, PORT, socket_family, socket_type, backlog, BUFFER_SIZE):
        
        super().__init__(socket_family, socket_type)
        
        self.HOST = HOST
        self.PORT = PORT
        self.BUFFER_SIZE = BUFFER_SIZE
        self.backlog = backlog

    def init(self):
        
        self.bind((self.HOST, self.PORT))
        self.listen(self.backlog)
        self.client_socket, self.address = self.accept()

    def client_connect_message(self):
        return f"Client connect: {self.address}"

    def start(self):
        try:
            self.init()
            print(self.client_connect_message())
            self.client_socket.send("hi".encode())
            while True:

                message = input("write command: ")
                if message is None or message==" " or message=='':
                    print("EOFerror")
                    message = "ERROR"
                self.client_socket.send(message.encode())
        except KeyboardInterrupt:
            print("CLOSE")
            self.client_socket.close()
        except socket.error as e:
            print(e)
if __name__=="__main__":
    
    ServerSock(HOST='127.0.0.1', 
            PORT=12345, socket_family=socket.AF_INET, 
            socket_type=socket.SOCK_STREAM, 
            backlog=1, 
            BUFFER_SIZE=1024
            ).start()