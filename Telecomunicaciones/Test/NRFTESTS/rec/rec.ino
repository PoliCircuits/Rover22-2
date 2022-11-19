#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>

const int pinCE = 53;
const int pinCSN = 48;
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
   radio.openWritingPipe(pipe);
   radio.openReadingPipe(1,pipe2);  
}
 
void loop(void)
{
  delay(5);
  seconddata[0]=3000;
  seconddata[1]=15.00;
  radio.stopListening();
  radio.write(seconddata , sizeof seconddata);
  delay(5);
  //
  radio.startListening();
   if (radio.available())
   {
      radio.read(firstdata, sizeof firstdata); 
      Serial.print("dato 0= ");
      Serial.print(firstdata[0]);
      Serial.print(" ");
      Serial.print("dato 1= ");
      Serial.println(firstdata[1]);
   }
    
}
