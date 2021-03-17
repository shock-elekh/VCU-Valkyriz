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

## Manuels
Le manuel de la teensy est dans la documentation.
La documentation du Bamocar est sur ce drive https://drive.google.com/drive/folders/1ejnI4x0l66PUooj8r0KLAIZRRiR4TCU6

## Le VCU au sein du faisceau (pour mémoire)
![Le VCU au sein du faisceau](/documentation/faisceau_final_TNN.png)
