from socket import socket, AF_INET, SOCK_STREAM
from sys import argv, exit

class Server:
    client_socket = client_addr = None

    def __init__(self, ip, port, password):
        self.sock = socket(AF_INET, SOCK_STREAM) 
        self.address = ip, int(port)
        self.passw= passw
        self.ip, self.port = self.address
    
    def init(self):
        self.sock.bind(self.address)
        self.sock.listen(1)
    
    def wait(self):
        print('Esperando nueva conexion ...')
        self.client_socket, self.client_addr = self.sock.accept()
        print(f'Nueva conexion: {self.client_addr[0]}:{self.client_addr[1]}')
        return self.run()
    
    def verify(self, data):
        print('Verificando cliente ...')
        password = data.split(':')[1]
        if password != self.passw:
            print('Clave incorrecta')
            self.client_socket.close()
            return self.wait()
        print('Cliente verificado')
        self.client_socket.send(b'sexo')
    
    def close_client(self):
        print('Cerrando conexion con cliente ...')
        self.client_socket.close()
        return self.wait()

    def send_command(self):
        command = None
        while not command:
            command = str(input('> '))
        self.client_socket.send(command.encode())
        return command
    
    def run(self):
        while True:
            data = self.client_socket.recv(1024).decode('utf-8')
            print('>>', data)
            if 'login' in data: self.verify(data)
            command = self.send_command()
            if command == 'salir': self.close_client()

    def close(self):
        self.sock.close()

if __name__ == "__main__":
    if len(argv) != 4: exit()
    _, host, port, passw = tuple(argv)
    server = Server(host, port, passw)
    server.init()
    server.wait()
