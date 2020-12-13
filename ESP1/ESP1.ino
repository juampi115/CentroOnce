////////////////////////////////// ESP8266 Parlante 1 ////////////////////////////////////

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
//#include <SoftwareSerial.h>
#ifndef STASSID
#define STASSID "NodeMCU-ESP8266"
#define STAPSK  "CENTRO1120"
#endif

char packetBuffer[255];          // Buffer para paquetes entrantes
unsigned int localPort = 8888;   // Puerto local
WiFiUDP Udp;

// Declaro un nuevo puerto para la comunicación serie
//SoftwareSerial mySerial(3, 1); // RX, TX

void setup() {
 // mySerial.begin(115200); // Comienzo de la comunicación serie
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(STASSID, STAPSK);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Conectando");
    delay(50);
  }
  Serial.println("Connected! IP address: ");
  Serial.print(WiFi.localIP());
  Serial.println();
  Serial.printf("UDP server on port %d\n", localPort);
  Udp.begin(localPort);
}


void loop() {

  ////////////// Lectura puerto udp /////////////////
  int packetSize = Udp.parsePacket();
  if (packetSize) {
    int len = Udp.read(packetBuffer, 255);    // lee un paquete de packetBufffer
    if (len > 0) packetBuffer[len] = 0;
    Serial.println();
    Serial.print("Mensaje: ");
    Serial.print(packetBuffer);
    Serial.println();
    MostrarDatosMensaje(packetSize);
    delay(100);
  }

/////////////////////////// Envio de datos al parlante ////////////////////////
 Serial.write(packetBuffer); // Enviamos el dato por el puerto serie (TX)
///////////////////////////////////////////////////////////////////////////////
} // end loop

void MostrarDatosMensaje(int n) {
  Serial.println();
  Serial.print("Tamaño de paquete: ");
  Serial.print(n);
  Serial.println();
  Serial.print("Desde: ");
  IPAddress remoteIp = Udp.remoteIP();
  Serial.print(remoteIp);
  Serial.println();
  Serial.print("Puerto: ");
  Serial.print(Udp.remotePort());
  Serial.println();
}
