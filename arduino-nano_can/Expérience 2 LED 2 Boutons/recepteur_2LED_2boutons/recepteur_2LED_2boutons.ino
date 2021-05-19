/*
 * Exemple de liaison CAN pour la réception
 * 
 * recepteur.ino
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
#include <Servo.h>

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
 * Un objet pour le message CAN. Par defaut c'est un message
 * standard avec l'identifiant 0 et aucun octet de donnees
 */
CANMessage messageCAN;

void messagePourLED1(const CANMessage & inMessage)
{
  Serial.println("Message LED reçu, changement de l'etat de la LED 1 ");
  uint8_t etatLED1 = inMessage.data[0];
  digitalWrite(3, etatLED1);
}

void messagePourLED2(const CANMessage & inMessage)
{
  Serial.println("Message LED reçu, changement de l'etat de la LED 1 ");
  uint8_t etatLED2 = inMessage.data[0];
  digitalWrite(4, etatLED1);
}

/* 
 * Définition des masques et filtres.
 * Il s'agit de deux messages d'identifiant 1 et 2, 
 * c'est à dire en binaire sur 11 bits (taille d'un identifiant
 * de trame standard) :
 * 00000000001
 * 00000000010
 * On ne veut que ces deux messages, donc le masque sélectionne
 * tous les bits :
 */
const ACAN2515Mask masque = standard2515Mask(0x7FF, 0, 0); /* Que des 1 sur 11 bits */
/* 
 *  Et on définit deux filtres, le premier pour les messages
 *  relatifs aux LEDs et le second pour les messages relatifs
 *  aux servos.
 */
const ACAN2515AcceptanceFilter filtres[] = {
   { standard2515Filter(1, 0, 0), messagePourLED1 }, 
   { standard2515Filter(2, 0, 0), messagePourLED2 }
};

void setup()
{
  /* Demarre la ligne serie */
  Serial.begin(9800);
  /* Demarre le SPI */
  SPI.begin();
  /* Configure le MCP2515 */
  Serial.println("Configuration du MCP2515");
  /* Fixe la vitesse du bus a 125 kbits/s */
  ACAN2515Settings reglages(FREQUENCE_DU_QUARTZ, FREQUENCE_DU_BUS_CAN);
  /* 1 emplacement suffit dans la file d'attente de reception */
  reglages.mReceiveBufferSize = 1;
  /* Pas de file d'attente d'emission */
  reglages.mTransmitBuffer0Size = 0;
  /* Demarre le CAN */
  const uint16_t codeErreur = controleurCAN.begin(reglages, [] { controleurCAN.isr(); }, masque, filtres, 2 );
  /* Verifie que tout est ok */
  if (codeErreur == 0) {
    Serial.println("Recepteur: configuration ok");
  }
  else {
    Serial.println("Recepteur: Probleme de connexion");
    while (1); 
  }

  /*
   * Initialise les broche des LEDs
   */
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
 
}

void loop()
{
  controleurCAN.dispatchReceivedMessage();
}
