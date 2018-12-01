import socket
import time
import select

# Create a TCP/IP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# Connect the socket to the port where the server is listening
server_address = ('192.168.4.1', 666)

if __name__ == "__main__":
    print ("ok")
    while True:
        try:
            s=socket.socket()
            s.settimeout(15)
            s.connect(server_address)
            s.sendall(b'1')
            print("envio")
            s.close()
        except socket.error as socketerror:
            print("Error: ", socketerror)
        time.sleep(1)
        


     