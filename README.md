# VCU-Valkyriz
Bienvenue dans le Git pour la programmation du VCU de Valkyriz (saison 2021)

![Le VCU au sein du faisceau](/documentation/Hardware_VCU.jpg)


# Objectifs du VCU
## Liste des fonctions retenues à faire implémenter par le VCU cette année
* Gestion APPS
  * Si on freine et qu’on accélère pendant plus de 500 ms on arrête d’accélérer
  * Si incohérence sur les 2 capteurs d’accélération de la pédale, on disjoncte.
* Loi de commande de la voiture :
  * Faire une map de la puissance voulu en fonction de la position pédale
  * Faire varier la map de la loi de commande selon  le SOC de la batterie, la température de la batterie.


## Liste des fonctions rejetées
* Niveau loi de commande:
  * Fonctions de Launch Control et Traction control pour éviter de faire patiner les roues arrières (Anti patinage)
  * Prendre en compte la charge sur les pneus (à partir de l’accélération) pour ajouter un feed forward dans le launch control
* Fonctions de diagnostic
  * Vérifier que les 4 vitesses de roue sont cohérentes (sinon pb capteur et ça peut impacter la loi de commande) 
  * étudier la variation de la température dans la batterie en fonction de la puissance qu’on lui demande pour vérifier que tout va bien. 
  * vérifier l'adéquation entre la puissance envoyée au moteur et celle tirée de la batterie.

# Le VCU en pratique
## Code
Le détail des variables, de l'organisation du code est fait dans l'excel situé dans [ce fichier](https://github.com/shock-elekh/VCU-Valkyriz/tree/main/documentation/code-teensy-vcu.xlsx)

`#include <FlexCAN.h>`



## Manuels
Le manuel de la teensy est dans la documentation.
La documentation du Bamocar est sur ce drive https://drive.google.com/drive/folders/1ejnI4x0l66PUooj8r0KLAIZRRiR4TCU6

## Le VCU au sein du faisceau sur le banc
![Le VCU au sein du faisceau](/documentation/faisceau-bastie.png)



## Le VCU au sein du faisceau sur le véhicule

![Le VCU au sein du faisceau](/documentation/faisceau-chaipe.png)

Il est donc relié:

* 

## La librairie FlexCAN

Sa documentation et son github sont situés ici (Teensy 3.1): https://github.com/teachop/FlexCAN_Library

Et là (Teensy 3.1 à 3.5): https://github.com/collin80/FlexCAN_Library

### La structure des données du type `CAN-message-t`:

`typedef struct CAN_message_t {
  uint32_t id; // can identifier
  uint8_t ext; // l'identifiant est étendu
  uint8_t rtr; // remote transmission request packet type
  uint8_t len; // longueur des données
  uint16_t timeout; // en millisecondes, 0 désactivera l'attente `

`  uint8_t buf[8];`





## Dump

Emphasis, aka italics, with *asterisks* or _underscores_.

Strong emphasis, aka bold, with **asterisks** or __underscores__.

Combined emphasis with **asterisks and _underscores_**.

Strikethrough uses two tildes. ~~Scratch this.~~





