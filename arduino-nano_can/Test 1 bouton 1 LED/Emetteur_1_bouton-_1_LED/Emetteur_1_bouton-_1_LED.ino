/*
 * Emetteur CAN pour 1 bouton et 1 LED ==> à télécharger sur l'arduino relié à un bouton sur le pin 3
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
 * messages CAN en emission
 * Par defaut les messages sont standard avec l'identifiant 0
 * et aucun octet de donnees
 */
CANMessage messageCANEmission;


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
  
  /* On définit le bouton */
  pinMode(3,INPUT);
  
  /* Un seul octet de donnees  */
  messageCANEmission.len = 1; 
}

void loop()
{
  uint8_t value=digitalRead(3);
  if (value==HIGH) {
      messageCANEmission.data[0] = 1;
      const bool ok_1 = controleurCAN.tryToSend(messageCANEmission);
      if (ok_1) {
        Serial.print("message ");
        Serial.println(" envoye !");
      }
    }
    else {
      messageCANEmission.data[0] = 0;
      const bool ok_2 = controleurCAN.tryToSend(messageCANEmission);
      if (ok_2) {
        Serial.print("message ");
        Serial.println(" envoye !");}
    }
    delay(100);
}
