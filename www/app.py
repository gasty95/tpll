# Imports
from flask import Flask
from flask import render_template
import socket

# Create a TCP/IP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# Connect the socket to the port where the server is listening
server_address = ('192.168.4.1', 666)

app = Flask(__name__)

@app.route('/')
def index():
    global sock
    return render_template('index.html')

@app.route('/connect')
def connect():
    global sock
    sock.connect(server_adress)
    return render_template('index.html')

@app.route('/detener', methods = ["POST"])
def detener():
    sock.sendall(b'0') #0 sera para detener
    return render_template('index.html')

@app.route('/avanzar', methods = ["POST"])
def avanzar():
    sock.sendall(b'1')# 1 será para avanzar
    return render_template('index.html')

@app.route('/retroceder', methods = ["POST"])
def retroceder():
    sock.sendall(b'2') #2 sera para retroceder
    return render_template('index.hmtl')

@app.route('/izquierda', methods = ["POST"])
def izquierda():
    sock.sendall(b'3') #3 sera para izquierda
    return render_template('index.hmtl')

@app.route('/derecha', methods = ["POST"])
def derecha():
    sock.sendall(b'4')# 4 sera para derecha
    return render_template('index.html')


if __name__ == "__main__":
    app.run(host='0.0.0.0', port=8888)