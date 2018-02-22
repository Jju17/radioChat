

#include <SPI.h>
#include <NRFLite.h>

NRFLite radio;
byte dataRX;
byte dataTX;
byte ligne = 2261321620;


boolean flag = false;

void setup()
{
  Serial.begin(9600);
  radio.init(1, 9, 10); // Set radio Id = 0, along with the CE and CSN pins
}

void loop()
{

  if (Serial.available() > 0) {
    flag = true;
    // read the incoming byte:
    dataTX = Serial.read();

    // say what you got:
    if(dataTX == ligne){
      Serial.println();
    }else{
      Serial.print((char) dataTX);
    }
    radio.send(0, &dataTX, sizeof(dataTX)); // Send to the radio with Id = 1
    
  }
  if(Serial.available() == 0 && flag == true){
    Serial.println();
    radio.send(0, &ligne, sizeof(ligne));
    flag = false;
  }

  while (radio.hasData())
  {
    radio.readData(&dataRX);
    if(dataRX == ligne){
      Serial.println();
    }else{
      Serial.print((char)dataRX);
  }
  }

}
