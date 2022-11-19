#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>

const int pinCE = 9;
const int pinCSN = 10;
RF24 radio(pinCE, pinCSN);

// Single radio pipe address for the 2 nodes to communicate.
const byte pipe [][6] = {"00001","00002"};
 
float data[2];
float data2[2];

void setup(void)
{
  Serial.begin(9600);
   radio.begin();
   radio.openWritingPipe(pipe[1]);
   radio.openReadingPipe(1,pipe[0]);
}
 
void loop(void)
{ 
  delay(5);
  data[0]=3.14;
  data[1]=millis()/1000.0;
  radio.startListening();
    if(radio.available()){
      radio.read(data2, sizeof data2);
      Serial.print("dato 0.1= ");
      Serial.print(data2[0]);
      Serial.print("dato 1.1= ");
      Serial.print(data2[1]);
    }
   else{
    Serial.println("sin datos recibidos");
   }
   delay(5);
   radio.stopListening();
}
