import socket

class MSGTypes:
    LOG = "[LOG]"
    SERVER = "[SERVER]"


class ServerSock(socket.socket, MSGTypes):
    
    def __init__(self, HOST: str,
                 PORT: str | int,
                 socket_family,
                 socket_type,
                 backlog: int,
                 BUFFER_SIZE: int
                 ):
        
        super().__init__(socket_family, socket_type)
        
        self.HOST = HOST
        self.PORT = PORT
        self.BUFFER_SIZE = BUFFER_SIZE
        self.backlog = backlog
        
    def init(self) -> None:
        
        self.bind((self.HOST, self.PORT))
        self.listen(self.backlog)
        self.client_socket, self.address = self.accept()
        print("Server started")

    def client_connect_message(self) -> str:
        return f"Client connect: {self.address}"
    
    def send_msg(self, msg: str, TYPE: str) -> None:
        self.client_socket.send(f"{TYPE} {msg}".encode())
        # TYPE log/server/...
        

    def start(self) -> None:
        try:
            
            self.init()
            print(self.client_connect_message())
            self.send_msg("connected", self.LOG)           
            while True:
                command = input("(q for quit) ▓ ")
                if command is None or command==" " or command=='':
                    print("EOFerror")
                    command = "ERROR"
                    
                elif command=="getlog":
                    with open("logfile.txt", "a") as f:
                        f.write(self.client_socket.recv(self.BUFFER_SIZE).decode())
                        
                self.send_msg(command.encode(), self.SERVER)
                print(self.client_socket.recv(self.BUFFER_SIZE).decode())
                
        except KeyboardInterrupt:
            print("CLOSE")
            self.client_socket.close()
        except socket.error as e:
            print(e)
            
if __name__=="__main__":
    
    ServerSock(HOST='26.199.90.194', 
            PORT=12345,
            socket_family=socket.AF_INET, 
            socket_type=socket.SOCK_STREAM, 
            backlog=1, 
            BUFFER_SIZE=1024
            ).start()
    
