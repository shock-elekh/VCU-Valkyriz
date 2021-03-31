// LoopBackDemo

// This demo runs on Tennsy 3.1 / 3.2, 3.5 and 3.6
// The FlexCAN module is configured in loop back mode: it internally receives
// every CAN frame it sends.

// No external hardware required.

//-----------------------------------------------------------------

#include <ACAN.h>

//-----------------------------------------------------------------
const int ledPin = 13;
void setup () {
  pinMode(ledPin, OUTPUT);
  Serial.begin (9600) ;
  ACANSettings settings (125 * 1000) ; // 125 kbit/s
  //settings.mLoopBackMode = true ;
  //settings.mSelfReceptionMode = true ;
  const uint32_t errorCode = ACAN::can0.begin (settings) ;
  if (0 == errorCode) {
    Serial.println ("can0 ok") ;
  }else{
    Serial.print ("Error can0: 0x") ;
    Serial.println (errorCode, HEX) ;
  }
}

//-----------------------------------------------------------------


static uint32_t gSentCount = 0 ;


//-----------------------------------------------------------------

void loop () {
  CANMessage message ;

  message.id = 0x542 ;
  message.ext = false ;
  const bool ok = ACAN::can0.tryToSend (message) ;
  if (ok) {
    gSentCount += 1 ;
    Serial.print ("Sent: ") ;
    Serial.println (gSentCount) ;
    digitalWrite(ledPin, HIGH);   // set the LED on
    delay(10);                  // wait for a second
    digitalWrite(ledPin, LOW);    // set the LED off
    delay(1000);
    
  }
  

}
