//////////////////////// Proyecto Aro de Básquet  /////////////////////
///////////////////////////// Parlante 1  /////////////////////////////
//////////////////////// Declaración de variables /////////////////////
#include <SoftwareSerial.h>
SoftwareSerial ESPserial(2, 3); // RX | TX
int estado = 9;
int poten = 0;
int ValMapeado = 0;
boolean aux = false;
int Datos = 0;                    // para datos en serie entrantes
int spk = 3;                             // altavoz a GND y pin 3
int c[5] = {131, 262, 523, 1046, 2093};  // frecuencias 4 octavas de Do
int cs[5] = {139, 277, 554, 1108, 2217}; // Do#
int d[5] = {147, 294, 587, 1175, 2349};  // Re
int ds[5] = {156, 311, 622, 1244, 2489}; // Re#
int e[5] = {165, 330, 659, 1319, 2637};  // Mi
int f[5] = {175, 349, 698, 1397, 2794};  // Fa
int fs[5] = {185, 370, 740, 1480, 2960}; // Fa#
int g[5] = {196, 392, 784, 1568, 3136};  // Sol
int gs[5] = {208, 415, 831, 1661, 3322}; // Sol#
int a[5] = {220, 440, 880, 1760, 3520};  // La
int as[5] = {233, 466, 932, 1866, 3729}; // La#
int b[5] = {247, 494, 988, 1976, 3951};  // Si

///////////////////////////////////////////////////////////////////////
void setup() {
  Serial.begin(115200);     // communication with the host computer
  ESPserial.begin(115200); // Comienzo de la comunicación serie
  pinMode(poten, INPUT);

}
///////////////////////////////////////////////////////////////////////
void nota(int frec, int t)
{
  tone(spk, frec);         // suena la nota frec recibida
  delay(t);                // para despues de un tiempo t
}
///////////////////////////////////////////////////////////////////////
void loop() {
  ///////////////////////////envio 1///////////////////////////////////
  /* if (mySerial.available()) {
     // Almaceno el carácter que llega por el puerto serie (RX)
     estado = mySerial.read();
    }
    Serial.println(estado);*/
  ////////////////////////////////////////////////////////////////////
  ///////////////////////////intento 2////////////////////////////////
  // listen for communication from the ESP8266 and then write it to the serial monitor
  if ( ESPserial.available() )   {
    Datos = ESPserial.read();
    Serial.write( Datos );
  }
  /*
    // listen for user input and send it to the ESP8266
    if ( Serial.available() )       {
      ESPserial.write( Serial.read() );
    } */
  delay(10);
  //////////////////////////////ACTUACION//////////////////////////////////////
  poten = analogRead(A0);     // Cambio de tono mediante potenciometro
  ValMapeado = map(poten, 0, 1023, 36, 3000);   // Mapeo potenciometro
  if (Datos == 2) {
    aux = false;
  }
  else if (Datos == 4) {
    aux = true;
  }
  if (aux == false) {
    tone(3, ValMapeado);
    delay(300);
    noTone(3);
    delay(900);
  }
  else {
    nota(d[3], 150); noTone(spk); delay(50);
    nota(cs[2], 150); noTone(spk); delay(50);
    nota(e[3], 700); noTone(spk); delay(1000);
    aux = false;
  }

}
