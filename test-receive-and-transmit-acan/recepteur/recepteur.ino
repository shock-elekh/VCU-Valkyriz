
#include <ACAN.h>
const int ledPin = 13;


//-----------------------------------------------------------------

void setup () {
  pinMode(ledPin, OUTPUT); 
  Serial.begin (9600) ;
  ACANSettings settings (125 * 1000) ; // 125 kbit/s

  const uint32_t errorCode = ACAN::can0.begin (settings) ;
  if (0 == errorCode) {
    Serial.println ("can0 ok reciever") ;
  }else{
    Serial.print ("Error can0 receiver: 0x") ;
    Serial.println (errorCode, HEX) ;
  }
}

//-----------------------------------------------------------------


static uint32_t gReceivedCount = 0 ;

//-----------------------------------------------------------------

void loop () {
  CANMessage message ;

  message.id = 0x542 ;
  message.ext = false ;
  
  if (ACAN::can0.receive (message)) {
    gReceivedCount += 1 ;
    Serial.print ("Received: ") ;
    Serial.println (gReceivedCount) ;
    delay(80);
    digitalWrite(ledPin, HIGH);
    delay(10);
    digitalWrite(ledPin, LOW);
  }

}
