#Source Raspberry

Les fichiers sources doivent être compilés sur la Raspberry-Pi pour fonctionner, voir [Integration&IA/README.md](../../Integration/README.md)

####Liste des fichiers  
  * **SPI.c/.h :**  
    Gére la communication SPI avec le CAN.
  * **I2C.c/.h :**  
    Gére la communication I2C avec le microcontrolleur
  * **CapteurIR.c/.h :**  
    Fonction necessaire à la commande des capteurs IR.
  * **test_Blinck.c :**  
    Simple programme qui fait clignoté une LED. Permet de vérifier le fonctionnement de la raspberry.
  * **test_I2C.c :**  
    Programme de test de la communication I2C avec l'Atmega. Fonctionne de pair avec le fichier test_I2C.c des source de l'Atmega
  * **test_SPI.c :**  
    Programme de test de la communication SPI. Fonctionne de pair avec un programme codé sur Arduino Uno.
  * **test_Moteur.c :**  
    Programme de test des contrôles des moteurs. Ouvre une interface terminal permettant à l'utilisateur d'envoyer différentes commandes.
  * **test_CAN_COM.c :**  
    Programme de test de la communication SPI avec le CAN.