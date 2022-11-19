#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>

const int pinCE = 53;
const int pinCSN = 48;
RF24 radio(pinCE, pinCSN);

// Single radio pipe address for the 2 nodes to communicate.
const byte pipe [][6] = {"00001","00002"};

float data[2];
float data2[2];

void setup(void)
{
   Serial.begin(9600);
   radio.begin();
   radio.openWritingPipe(pipe[0]);
   radio.openReadingPipe(1,pipe[1]);
   
}
 
void loop(void)
{
  delay(5);
  data2[0]=3000;
  data2[1]=15.00;
  radio.startListening();
   if (radio.available())
   {
      radio.read(data, sizeof data); 
      Serial.print("dato 0= ");
      Serial.print(data[0]);
      Serial.print("dato 1= ");
      Serial.println(data[1]);
   }
   else {
    Serial.println("sin datos de radio recibidos");
    }
    delay(5);
    radio.stopListening();
}
