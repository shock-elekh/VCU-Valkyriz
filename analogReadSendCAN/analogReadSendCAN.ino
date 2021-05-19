
#include <FlexCAN.h>

static CAN_message_t msg;
static uint8_t hex[17] = "0123456789abcdef"; // c'est quoi ça ?

int val_potentiometre = 0;
int valeur = 0;

const int LED = 13;
const int port_potentiometre = A9;




class overriddenListener : public CANListener 
{
public:
   void printFrame(CAN_message_t &frame, int mailbox);
   bool frameHandler(CAN_message_t &frame, int mailbox, uint8_t controller); //overrides the parent version so we can actually do something
};

void overriddenListener::printFrame(CAN_message_t &frame, int mailbox)
{
   Serial.print("ID: ");
   Serial.print(frame.id, HEX);
   Serial.print(" Data: ");
   for (int c = 0; c < frame.len; c++)
   {
      Serial.print(frame.buf[c]);
      Serial.write(' ');
   }
   Serial.write('\r');
   Serial.write('\n');
}

bool overriddenListener::frameHandler(CAN_message_t &frame, int mailbox, uint8_t controller)
{
    printFrame(frame, mailbox);

    return true;
}

overriddenListener receiveObj;




void setup(void)
{
  pinMode(port_potentiometre, INPUT);
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
  delay(1000);
  Serial.println(F("Test teensy envoyer message"));

  Can0.begin(1000000);  // 1 MBit/s

  Can0.attachObj(&receiveObj);
  receiveObj.attachGeneralHandler();

  msg.ext = 0; // Identifiant en cas de filters setting extended
  msg.id = 0x123; // l'identifiant en héxadécimal
  msg.len = 8; // taille des donnée transmise en octet (de 0 à 8 octet au maximum)
  msg.buf[0] = 00; 
  msg.buf[1] = 00;
  msg.buf[2] = 00;
  msg.buf[3] = 00;
  msg.buf[4] = 00;
  msg.buf[5] = 00;
  msg.buf[6] = 00;
  msg.buf[7] = 00;
}


void loop(void)
{

    delay(500);
  val_potentiometre = analogRead(port_potentiometre);
  valeur = map(val_potentiometre, 0, 1023, 0, 255);

if (val_potentiometre >= 600) 
{
  analogWrite(LED, 1023);
  }
else
{
   analogWrite(LED, 0);
}


  // Serial.println(valeur, HEX);
  Serial.println(val_potentiometre);
  
  Can0.begin(1000000); 


  msg.buf[0] = valeur; 

  Can0.write(msg);

}
