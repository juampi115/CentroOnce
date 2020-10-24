
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

//#ifndef STASSID
//#define STASSID "Fibertel WiFi333 2.4GHz"
//#define STAPSK  "0043801931"
//#endif

unsigned int localPort = 8888;            // Puerto local
const char ssid[] = "NodeMCU-ESP8266";    // Nombre de la red 
const char password[] = "CENTRO1120";     // Contraseña del servidor
char  ReplyBuffer[] = "";                 // Mensaje a enviar
// Variables para lectura de teclado
int incomingByte = 1;                     
char aChar = ' ';

WiFiUDP Udp;
void setup() {
  
  Serial.begin(115200);
  WiFi.mode(WIFI_AP);                     // Crea el Puerto de acceso
  WiFi.softAP(ssid, password,8888);       // Red con clave, en el canal 1 y visible
  WiFi.begin();
  Serial.println("IP Access Point - por defecto: ");
  Serial.println(WiFi.softAPIP()); 
  Serial.print("MAC Access Point: ");
  Serial.println(WiFi.softAPmacAddress()); 
  Serial.println("Server Started..");
  Serial.println("Connected! IP address: ");
  Serial.println(WiFi.localIP());
  Serial.printf("UDP server on port %d\n", 8888);
  Udp.begin(8888);
}

void loop() {

  //////// Lee el teclado y carga de mensaje  //////////////
  if (Serial.available() > 0) {   
     incomingByte = Serial.read();  // Lee el puerto serial
     aChar = incomingByte;          // Transforma un numero a caracter
     ReplyBuffer[0] = aChar;        // Caracter a enviar
  }else{
     ReplyBuffer[0] = ' ';          // Si no hay nada, envia un espacio en blanco
  }

  //////// Envio de mensaje //////////////
  //Udp.beginPacket(Udp.remoteIP(), 8888);  // Envia a una ip automatica
  Udp.beginPacket("192.168.4.2", 8888);     // Envia a una ip fija
  Udp.write(ReplyBuffer);                   // Envia la variable ReplyBuffer
  Udp.endPacket();                          // Finaliza el envio

  // Imprime por el puero seria lo que envia por udp
  Serial.println();
  Serial.print("Envio: ");          
  Serial.print(ReplyBuffer);
  delay(100);
    
} //end loop
