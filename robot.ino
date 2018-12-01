#include <doxygen.h>
#include "ESP8266.h"
#include <SoftwareSerial.h>

/*FUNCIONES ORIGINALES*/
#include <Arduino.h>
#include <Servo.h>

const char* SSID = "esp";
const char* PASSWORD = "pas123456";

SoftwareSerial softSerial(2,3); //RX, TX

/*FUNCIONES EDITADAS O DESARROLLADAS*/

/*DEFINICIONES DE CONFIGURACION*/
#define BAUDRATE            9600
#define TAM_BUFFER          512  

/*DEFINICIONES DE TIEMPO DE EJECUCION*/
#define F_Communication       50
#define F_Movement            97
#define F_Testing             2000  

/*DECLARACION DE VARIABLES GLOBALES*/
ESP8266 wifi(softSerial);
// Declaramos la variable para controlar el servo
Servo servo1;
Servo servo2;
Servo servo3; 
Servo servo4;




uint8_t buffer[TAM_BUFFER]={0};//buffer para enviar y recibir informacion
uint32_t len;//Tamaño del mensaje recibido o el mensaje a enviar
uint32_t frecuency=1; //variables que nos permite implementar un porgrmacion de tareas
String data_send;
uint8_t buffer2[TAM_BUFFER]={0};
uint32_t buffer_size = 512;
uint32_t timeout1= 1000;

//variables de desplazamiento -> el vehiculo lee estas variables y decide su movimiento
uint8_t direction=0; // 0=stop, 1=front, 2=back , 3=left , 4=right  //si va para adelante, atras, izquierda o derecha

void setup(void)
{ 
    Serial.begin(BAUDRATE);
    Serial.println("setup begin\r\n");
    servo1.attach(4);
    servo2.attach(6);
    servo3.attach(9);
    servo4.attach(11);
    Configuration();
    Serial.println("setup end\r\n");
}
 
void loop(void)
{
  // DEZPLAZAMIENTO
   /*if (frecuency % F_Movement == 0 ){ //Si es momento de realizar un movimiento
            if( direction == 1 ) { // Si voy hacia adelante
              Serial.print("AVANZAR\r\n");
              //avanzar();
            } 
            if( direction == 2 ) { // Si voy hacia adelante
              Serial.print("RETROCEDER\r\n");
              //retroceder();
            }
            if( direction == 3 ) { // Si voy hacia adelante
              Serial.print("IZQUIERDA\r\n");
              //izquierda();
            } 
            if( direction == 4 ) { // Si voy hacia adelante
              Serial.print("DERECHA\r\n");
              //derecha();
            }
            if (direction == 0){
              //parar();
            }
            Serial.print("dir:");
            Serial.print(direction);
            
            Serial.print("\r\n");
   
   }
    // FIN DEZPLAZAMIENTO
*/

   // COMUNICACION
   if (frecuency % F_Communication == 0 ){ //SI es momento de procesar la comunicacion
          len=wifi.recv(buffer,sizeof(buffer),3000);
          Serial.print ("len:");
          Serial.print (len);
          Serial.print("\r\n");
          if (len >0){ //SI SE RECIBE ORDEN
                     Serial.print("ORDEN");
                     Serial.print("\r\n");
               //REcibí un mensaje de desplazamiento, almacenamiento de los movimientos que decidió el usuario
                     direction=buffer[0]-48; //se resta 48, pues el valro que se recibe está en ascci
                     Serial.print("direccion: ");
                     Serial.print(direction);
                     Serial.print("\r\n");
          }    
                    
   }
   // FIN COMUNICACION


// CONFIGURACION DE TIEMPOS
 //delayMicroseconds(1000);
  // delay(1); //espera entre iteraciones

  frecuency++;//Aumento de la iteracion realizada
  if (frecuency == 6300){
      frecuency=0;
  }
// FIN CONFIGURACION DE TIEMPOS    
}

//-------------------------------//FUNCIONES//-------------------------------//

void Configuration(){
   wifi.restart();
   delay(500);
   if (wifi.setOprToSoftAP()) {
      Serial.print("to station + softap ok\r\n");
   }
   else {
      Serial.print("to station + softap err\r\n");
   }
   
    if (wifi.setSoftAPParam(SSID, PASSWORD,3,0)) {
      Serial.print("AP param ok\r\n");
   }
   else {
      Serial.print("AP param err\r\n");
   }

   if (wifi.enableMUX()) {
      Serial.print("multiple ok\r\n");
   }
   else {
      Serial.print("multiple err\r\n");
   }
 
   if (wifi.startTCPServer(666)) {
      Serial.print("start tcp server ok\r\n");
   }
   else {
      Serial.print("start tcp server err\r\n");
   }
 
   if (wifi.setTCPServerTimeout(20)) {
      Serial.print("set tcp server timout 10 seconds\r\n");
   }
   else {
      Serial.print("set tcp server timout err\r\n");
   }
   Serial.print(wifi.getLocalIP());
   
}

void parar(){
  servo1.write(90);
  servo2.write(90);
  servo3.write(90);
  servo4.write(90);
}


void izquierda(){ //prototipo
    parar();
    delay(500);
    servo2.write(65);
    delay(500);
    servo2.write(90);
    servo4.write(60);
    delay(500);
  }

void retroceder(){
  parar();
  delay(500);
  servo3.write(60);
  delay(500);
  servo4.write(120);
  delay(500);
  servo3.write(90);
  servo4.write(90);
  servo1.write(120);
  servo2.write(60);
  delay(500);
}


void avanzar(){
  parar();
  delay(500);
  servo1.write(120);
  delay(500);
  servo2.write(60);
  delay(500);
  servo1.write(90);
  servo2.write(90);
  servo3.write(60);
  servo4.write(120);
  delay(500);
  
}
