#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>

const int pinCE = 9;
const int pinCSN = 10;
RF24 radio(pinCE, pinCSN);

// Single radio pipe address for the 2 nodes to communicate.
const uint64_t pipe = 0xE8E8F0F0E1LL;
const uint64_t pipe2 = 0xE9E8F0F0E1LL;
 
float firstdata[2];
float seconddata[2];

void setup(void)
{
  Serial.begin(9600);
   radio.begin();
   radio.openWritingPipe(pipe2);
   radio.openReadingPipe(1,pipe);
}
 
void loop(void)
{ 
  delay(5);
  radio.stopListening();
  firstdata[0]=3.14;
  firstdata[1]=millis()/1000.0;
  radio.write(firstdata, sizeof firstdata);
  delay(5);
  
  radio.startListening();
  if(radio.available()){
      radio.read(seconddata, sizeof seconddata);
      Serial.print("dato 0.1= ");
      Serial.print(seconddata[0]);
      Serial.print(" ");
      Serial.print("dato 1.1= ");
      Serial.println(seconddata[1]);
    }  
}
