/*
 * Exemple de liaison CAN pour la commande
 * 
 * emetteur.ino
 * 
 * Materiel :
 * - 1 carte CAN a base de MCP2515
 * - 2 arduino NANO
 * - 2 boutons poussoir
 * - 2 LED
 * 
 * Bibliotheque employees (disponibles via le gestionnaire de bibliothèques) :
 * - acan2515
 */

/*
 * Inclusions pour acan2515
 */
#include <ACANBuffer16.h>
#include <ACANBuffer.h>
#include <ACAN2515Settings.h>
#include <ACAN2515.h>
#include <CANMessage.h>

/*
 * Broches pour le chip select et l'interruption du MCP2515
 */
static const uint8_t MCP2515_CS  = 10; /* Broches qui concernent la connection entre le module CAN et l'arduino
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
 * Un objet pour le message CAN des LEDs. Par defaut c'est un message
 * standard avec l'identifiant 0 et aucun octet de donnees
 */
CANMessage messageCANLED1;

/*
 * Un objet pour le message CAN des Servos. Par defaut c'est un message
 * standard avec l'identifiant 0 et aucun octet de donnees
 */
CANMessage messageCANLED2;


void setup()
{
  /* Demarre la ligne serie */
  Serial.begin(9600); /* ATTENTION VERIFIER LA F
  /* Demarre le SPI */
  SPI.begin();
  /* Configure le MCP2515 */
  Serial.println("Configuration du MCP2515");
  /* Fixe la vitesse du bus a 125 kbits/s */
  ACAN2515Settings reglages(FREQUENCE_DU_QUARTZ, FREQUENCE_DU_BUS_CAN);
  /* Pas de file d'attente de reception */
  reglages.mReceiveBufferSize = 0;
  /* 1 emplacement suffit dans la file d'attente d'emission */
  reglages.mTransmitBuffer0Size = 1;
  /* Demarre le CAN */
  const uint16_t codeErreur = controleurCAN.begin(reglages, [] { controleurCAN.isr(); } );
  /* Verifie que tout est ok */
  if (codeErreur == 0) {
    Serial.println("Configuration ok");
  }
  else {
    Serial.println("Probleme de connexion");
    while (1); 
  }

  /* Initialise les boutons */
    pinMode(3, INPUT);
    pinMode(4, INPUT);
  }
  /* 
   * Initialise les messages. Le message pour les LEDs a un identifiant à 1
   * Celui des servos a un identifiant à 2. Les deux messages on un
   * octet de données
   */
  messageCANLED1.id = 1;
  messageCANLED1.len = 1;

  messageCANLED2.id = 2;
  messageCANLED2.len = 1;
}



void loop() {
  uint8_t Bouton1=digitalRead(3)
  uint8_t Bouton2=digitalRead(4)
  if (Bouton1 == HIGH) { /* Le bouton 1 est pressé on veut donc allumer la Led 1 */
        messageCANLED1.data[0] = 1;
        const bool ok = controleurCAN.tryToSend(messageCANLEDs);
        if (ok) {
          Serial.println("Message pour la led 1 envoye !");
        }
        else {
          Serial.println("echec de l'envoi pour la led 1");
        }
      }
  else if (Bouton1 == LOW) { /* Le bouton 1 n'est pas pressé on veut donc éteindre la Led 1 */
    messageCANLED1.data[0] = 0;
    const bool ok = controleurCAN.tryToSend(messageCANLEDs);
    if (ok) {
      Serial.println("Message pour la led 1 envoye !");
    }
    else {
      Serial.println("echec de l'envoi pour la led 1");
    }
  if (Bouton2 == HIGH) { /* Le bouton 2 est pressé on veut donc allumer la Led 2 */
      messageCANLED2.data[0] = 1;
      const bool ok = controleurCAN.tryToSend(messageCANLEDs);
      if (ok) {
        Serial.println("Message pour la led 2 envoye !");
      }
      else {
        Serial.println("echec de l'envoi pour la led 2");
      }
    }
  else if (Bouton1 == LOW) { /* Le bouton 2 n'est pas pressé on veut donc éteindre la Led 2 */
    messageCANLED2.data[0] = 0;
    const bool ok = controleurCAN.tryToSend(messageCANLEDs);
    if (ok) {
      Serial.println("Message pour la led 2 envoye !");
      }
    else {
      Serial.println("echec de l'envoi pour la led 2");
      }
    }
  delay(100);
  }    
  
