#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>

const int pinCE = 9;
const int pinCSN = 10;
RF24 radio(pinCE, pinCSN);

const uint64_t pipe = 0x1658;

int data[2];

void setup()
{
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(1, pipe);
  radio.startListening();
}

void loop()
{
  if (radio.available())
  {
    radio.read(data, sizeof data);
    Serial.print("X: ");
    Serial.print(data[0]);
    Serial.print("Y: ");
    Serial.println(data[1]);
  }
}
