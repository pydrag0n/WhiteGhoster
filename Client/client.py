import socket
import time

class ClientSock(socket.socket):
    def __init__(self, HOST, PORT, socket_family, socket_type, BUFFER_SIZE):
        super().__init__(socket_family, socket_type)
        self.HOST = HOST
        self.PORT = PORT
        self.BUFFER_SIZE = BUFFER_SIZE
        self.is_connecting = False

    def init(self):
        self.connect((self.HOST, self.PORT))
        self.is_connecting = True
        
    def start(self):
        while True:
            try:
                self.init()
                while True:
                    OK_message = "OK"
                    self.send(OK_message.encode())
                    server_message = self.recv(self.BUFFER_SIZE).decode()
                    print(server_message)
                    if server_message=="ERROR": pass
            except KeyboardInterrupt:
                print("disconnect...")
            except socket.error as e:
                print(e)
                

                time.sleep(1)
                if e.args[0]==10053:
                    self.connect((self.HOST, self.PORT))
                    self.close()

ClientSock(HOST='127.0.0.1',
           PORT=12345,
           socket_family=socket.AF_INET,
           socket_type=socket.SOCK_STREAM,
           BUFFER_SIZE=1024
           ).start()