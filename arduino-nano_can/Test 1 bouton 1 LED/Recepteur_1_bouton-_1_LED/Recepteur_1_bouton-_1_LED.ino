/*
 * Recepteur CAN pour 1 bouton et 1 LED ==> à télécharger sur l'arduino relié à une LED sur le pin 3
 */
#include <ACANBuffer16.h>
#include <ACANBuffer.h>
#include <ACAN2515Settings.h> /* Pour les reglages  */
#include <ACAN2515.h>         /* Pour le controleur */
#include <CANMessage.h>       /* Pour les messages  */

/*
 * Broches pour le chip select et l'interruption du MCP2515
 */
static const uint8_t MCP2515_CS  = 10;
static const uint8_t MCP2515_INT = 2;

/*
 * L'objet pour piloter le MCP2515. SPI designe l'objet
 * utilise pour la connexion SPI car sur certaines cartes
 * notamment les Teensy, il peut y avoir plusieurs SPI.
 */
ACAN2515 controleurCAN(MCP2515_CS, SPI, MCP2515_INT);

/*
 * La frequence du quartz du MCP2515 en hertz. 
 * Sur les cartes CAN que l'on peut trouvez chez les revendeurs
 * chinois, il s'agit generalement d'un quartz 8MHz
 */
static const uint32_t FREQUENCE_DU_QUARTZ = 16ul * 1000ul * 1000ul;

/*
 * La fréquence du bus CAN
 */
static const uint32_t FREQUENCE_DU_BUS_CAN = 125ul * 1000ul;

/*
 * Cet Arduino ne s'occupe que de la réception des messages
 */
 
CANMessage messageCANReception;

void setup()
{
  /* Demarre la connexion serie */
  Serial.begin(9600);
  /* Demarre le SPI */
  SPI.begin();
  
  /* Configuration du MCP2515 */
  Serial.println("Configuration du MCP2515");
  ACAN2515Settings configuration(FREQUENCE_DU_QUARTZ, FREQUENCE_DU_BUS_CAN);
  
  /* Demarrage du CAN */
  const uint32_t codeErreur = controleurCAN.begin(configuration, [] { controleurCAN.isr(); });
  if (codeErreur != 0) {
    Serial.print("Erreur : 0x");
    Serial.println(codeErreur, HEX);
    while (1);
  }
  else {
    Serial.println("OK !");
  }

  /* Déclaration de la sortie LED */
  pinMode(3,OUTPUT);
}

void loop()
{ uint32_t numero = 0;
  if (controleurCAN.receive(messageCANReception)) {
    Serial.print("recu");
    Serial.println(numero++);
    const uint8_t etat = messageCANReception.data[0];
    if (etat==0){
      digitalWrite(3,LOW);}
    else {
      digitalWrite(3,HIGH);}
  }
}
