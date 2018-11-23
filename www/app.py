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

@app.rpute('/connect')
def connect():
    global sock
    sock.connect(server_adress)
    return render_template('index.html')

@app.route('/avanzar')
def avanzar():
    sock.sendall('1')# 1 será para avanzar
    return render_template('index.html')

@app.route('/detener')
def detener():
    sock.sendall('2') #2 sera para detener
    return render_template('index.html')

@app.route('/retroceder')
def retroceder():
    sock.sendall('3') #3 sera para retroceder
    return render_template('index.hmtl')

@app.route('/izquierda')
def izquierda():
    sock.sendall('4') #4 sera para izquierda
    return render_template('index.hmtl')

@app.route('/derecha')
def derecha():
    sock.sendall('5')# 5 sera para derecha
    return render_template('index.html')


if __name__ == "__main__":
    app.run(host='0.0.0.0', port=8888)

