#include <doxygen.h>
#include <ESP8266.h>
#include <SoftwareSerial.h>
#include <Arduino.h>
#include <Servo.h>

const char* SSID = "esp";
const char* PASSWORD = "pas123456";

SoftwareSerial softSerial(2,3); //RX, TX


//DEFINICIONES de constantes
#define BAUDRATE            9600
#define TAM_BUFFER          512  
#define F_comunicacion       50
#define F_movimiento         97
 
// Declaramos las variables globales
ESP8266 wifi(softSerial);
Servo servo1;
Servo servo2;
Servo servo3; 
Servo servo4;




uint8_t buffer[TAM_BUFFER]={0};//buffer para recibir informacion
uint32_t len;//Tamaño del mensaje recibido
uint32_t frecuencia=1; //variable que nos permite administrar las tareas


//variable de movimiento
uint8_t direccion=0; // 0=parar, 1=avanzar, 2=retroceder , 3=izquierda , 4=derecha  //si va para adelante, atras, izquierda o derecha

void setup(void)
{ 
    Serial.begin(BAUDRATE);
    Serial.println("setup begin\r\n");
    servo1.attach(5);
    servo2.attach(6);
    servo3.attach(9);
    servo4.attach(11);
    Configuration();
    Serial.println("setup end\r\n");
}
 
void loop(void)
{
  // Control de Movimiento
   if (frecuencia % F_movimiento == 0 ){ //Si es momento de realizar un movimiento
            if( direccion == 1 ) { // Si voy hacia adelante
              Serial.print("AVANZAR\r\n");
              avanzar();
            } 
            if( direccion == 2 ) { // Si voy hacia atras
              Serial.print("RETROCEDER\r\n");
              retroceder();
            }
            if( direccion == 3 ) { // Si voy hacia izquierda
              Serial.print("IZQUIERDA\r\n");
              for(int i=0; i<3;i++)
                izquierda();
            } 
            if( direccion == 4 ) { // Si voy hacia derecha
              Serial.print("DERECHA\r\n");
              for(int i=0; i<3;i++)
                derecha();
            }
            if (direccion == 0){  // Si me detengo
              parar();
            }
            Serial.print("dir:");
            Serial.print(direccion);
            
            Serial.print("\r\n");
   
   }
    // termina el control del movimiento


   // Control de la Comunicacion
   if (frecuencia % F_comunicacion == 0 ){ //Si es momento de controlar la comunicacion
          len=wifi.recv(buffer,sizeof(buffer),1000);
          Serial.print ("len:");
          Serial.print (len);
          Serial.print("\r\n");
          if (len >0){ //Si se recibe una orden
                     Serial.print("ORDEN");
                     Serial.print("\r\n");
               //Recibí un mensaje de movimiento, almacenamiento de los movimientos que decidió el usuario
                     direccion=buffer[0]-48; //se resta 48 porque el valor que se recibe está en ascci
                     Serial.print("direccion: ");
                     Serial.print(direccion);
                     Serial.print("\r\n");
          }    
                    
   }
   //termina el control de la comunicacion


  frecuencia++;//Aumento de la iteracion realizada
  if (frecuencia == 6300){
      frecuencia=0;
  }
  
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


void izquierda(){
  servo2.write(90);
  servo4.write(90);
  delay(800);
  servo1.write(100);
  servo2.write(70);  
  servo3.write(70);
  servo4.write(50);  
  delay(800);
 }
 
void derecha(){ 
  servo1.write(90);
  servo3.write(100);
  delay(800);
  servo1.write(70);
  servo2.write(70);  
  servo3.write(120);
  servo4.write(110);  
  delay(800);
 }


void avanzar(){
  servo1.write(85);
  servo2.write(95);
  servo3.write(90);
  servo4.write(90);
  delay(500);
  servo3.write(120);
  delay(500);
  servo4.write(60);
  delay(500);
  servo3.write(90);
  servo4.write(90);
  servo1.write(60);
  servo2.write(120);
  delay(500);
}


void retroceder(){
  servo1.write(90);
  servo2.write(90);
  servo3.write(90);
  servo4.write(90);
  delay(500);
  servo1.write(60);
  delay(500);
  servo2.write(120);
  delay(500);
  servo1.write(90);
  servo2.write(90);
  servo3.write(120);
  servo4.write(60);
  delay(500);
  
  }
