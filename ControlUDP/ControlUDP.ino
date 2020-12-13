
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

unsigned int localPort = 8888;            // Puerto local
const char ssid[] = "NodeMCU-ESP8266";    // Nombre de la red
const char password[] = "CENTRO1120";     // Contraseña del servidor
char  ReplyBuffer[] = "";                 // Mensaje a enviar
// Variables para lectura de teclado
int incomingByte = 1;
char aChar = ' ';

#define Pulsador1 2
#define Pulsador2 4
#define Pulsador3 5

int aux1 = 0;
int aux2 = 0;
int aux3 = 0;

WiFiUDP Udp;
void setup() {

  Serial.begin(115200);
  WiFi.mode(WIFI_AP);                     // Crea el Puerto de acceso
  WiFi.softAP(ssid, password, 8888);      // Red con clave, en el canal 1 y visible
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

  pinMode(Pulsador1, INPUT_PULLUP);
  pinMode(Pulsador2, INPUT_PULLUP);
  pinMode(Pulsador3, INPUT_PULLUP);

}
void loop() {
  ///////////////////// Lectura de botones //////////////////////////////
  aux1 = digitalRead(Pulsador1);
  aux2 = digitalRead(Pulsador2);
  aux3 = digitalRead(Pulsador3);


  //////// Lee el teclado y carga de mensaje  //////////////
  if (Serial.available() > 0) {
    incomingByte = Serial.read();  // Lee el puerto serial
    aChar = incomingByte;          // Transforma un numero a caracter
    ReplyBuffer[0] = aChar;        // Caracter a enviar
  }
  ////////////////////// CONDICIONALES BOTONES //////////////////////////////////////////////
  if (aux1 == HIGH && aux2 == HIGH) {
    ReplyBuffer[0] = ' ';          // Si no hay nada, envia un espacio en blanco
  }
  if (aux1 == LOW && aux3 == HIGH) {          // si se aprieta boton 1 (local) manda "1" y no hay tanto
    ReplyBuffer[0] = '1';
  }
  else if (aux1 == LOW && aux3 == LOW) {      // si hay tanto manda "3"
    ReplyBuffer[0] = '3';                     
  }
  else if (aux2 == LOW && aux3 == HIGH) {     // si se aprieta boton 2 (visitante) manda "2" y no hay tanto
    ReplyBuffer[0] = '2';
  }
  else if (aux2 == LOW && aux3 == LOW) {    // si hay tanto manda "4"
    ReplyBuffer[0] = '4';                     
  }
  //////// Envio de mensaje //////////////
  // Udp.beginPacket(Udp.remoteIP(), 8888);  // Envia a una ip automatica (no funciona)
  Udp.beginPacket("192.168.4.2", 8888);     // Envia a una ip fija (antena uno)
  Udp.write(ReplyBuffer);                   // Envia la variable ReplyBuffer
  Udp.endPacket();                          // Finaliza el envio

  Udp.beginPacket("192.168.4.3", 8888);     // Envia a una ip fija (antena dos)
  Udp.write(ReplyBuffer);                   // Envia la variable ReplyBuffer
  Udp.endPacket();                          // Finaliza el envio

  // Imprime por el puero seria lo que envia por udp
  Serial.println();
  Serial.print("Envio: ");
  Serial.print(ReplyBuffer);
  delay(100);

}
