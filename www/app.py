# Imports
from flask import Flask
from flask import render_template
import socket
import time


# Create a TCP/IP socket
#sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# Connect the socket to the port where the server is listening
server_address = ('192.168.4.1', 666)
app = Flask(__name__)

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/avanzar')
def avanzar():
    av=True
    try:
        s=socket.socket()
        s.settimeout(5)
        s.connect(server_address)
        s.sendall(b'1')
        print("envio")
        s.close()
    except socket.error as socketerror:
        while (av):
            try:
                s=socket.socket()
                s.settimeout(5)
                s.connect(server_address)
                s.sendall(b'1')
                print("envio")
                s.close()
                av=False
            except:
                print("Error: ", socketerror)
    return render_template('index.html')

@app.route('/detener')
def detener():
    det=True
    try:
        s=socket.socket()
        s.settimeout(5)
        s.connect(server_address)
        s.sendall(b'0')
        print("envio")
        s.close()
    except socket.error as socketerror:
        while (det):
            try:
                s=socket.socket()
                s.settimeout(5)
                s.connect(server_address)
                s.sendall(b'0')
                print("envio")
                s.close()
                det=False
            except:
                print("Error: ", socketerror)
    return render_template('index.html')

@app.route('/retroceder')
def retroceder():
    ret=True
    try:
        s=socket.socket()
        s.settimeout(5)
        s.connect(server_address)
        s.sendall(b'2')
        print("envio")
        s.close()
    except socket.error as socketerror:
        while (ret):
            try:
                s=socket.socket()
                s.settimeout(5)
                s.connect(server_address)
                s.sendall(b'2')
                print("envio")
                s.close()
                ret=False
            except:
                print("Error: ", socketerror)
    return render_template('index.html')

@app.route('/izquierda')
def izquierda():
    izq=True
    try:
        s=socket.socket()
        s.settimeout(5)
        s.connect(server_address)
        s.sendall(b'3')
        print("envio")
        s.close()
    except socket.error as socketerror:
        while (izq):
            try:
                s=socket.socket()
                s.settimeout(5)
                s.connect(server_address)
                s.sendall(b'3')
                print("envio")
                s.close()
                izq=False
            except:
                print("Error: ", socketerror)
    return render_template('index.html')

@app.route('/derecha')
def derecha():
    der=True
    try:
        s=socket.socket()
        s.settimeout(5)
        s.connect(server_address)
        s.sendall(b'4')
        print("envio")
        s.close()
    except socket.error as socketerror:
        while (der):
            try:
                s=socket.socket()
                s.settimeout(5)
                s.connect(server_address)
                s.sendall(b'4')
                print("envio")
                s.close()
                der=False
            except:
                print("Error: ", socketerror)
    return render_template('index.html')


if __name__ == "__main__":
    app.run(host='0.0.0.0', port=8888)