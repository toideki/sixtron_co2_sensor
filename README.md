

##  Mise en place du git 


##  Utilisation du projet
# Cloner le git
```bash
    git clone https://github.com/toideki/sixtron_co2_sensor.git
```
## Étapes

```bash
    cd sixtron_co2_sensor/
```
### 1. Déployer les dépendances du projet
Dans un terminal, placez-vous dans le dossier du projet cloné, puis exécutez :  

```bash
    mbed deploy
```
### 2. Créer un environnement virtuel Python ( Au besoins)

Créez un environnement virtuel pour isoler les dépendances Python :

```bash
    python -m venv mbed_virtual
```
Activez l'environnement virtuel :
```bash
    source mbed_virtual/bin/activate
```
### 3. Configurer la cible et la chaîne d'outils Mbed

Définissez la cible matérielle et la chaîne d'outils à utiliser :

```bash
    mbed target ZEST_CORE_FMLR-72 && mbed toolchain GCC_ARM
```

# 6. Compiler le projet

Compilez le projet avec la commande suivante :
```bash
    mbed compile
```
# 7. Flasher le programme sur la carte

Téléchargez le programme sur la carte :
```bash
    sixtron_flash
```
# 8. Lancer la communication série avec la carte

Pour lire les messages ou interagir avec la carte, ouvrez une communication série :

```bash
    minicom -b 9600 -D /dev/ttyUSBX 
```

# EXERCICE 1 : Contrôle d'une LED avec une interruption sur bouton

Cet exercice utilise la bibliothèque **Mbed OS** pour contrôler une LED en réponse à un bouton poussoir. Le code utilise des interruptions pour basculer l'état d'une LED à chaque appui ou relâchement du bouton. 

## Commande pour l'utilisation
    
## Fonctionnement du code 

1. **Initialisation des objets :**
   - Un bouton est configuré comme une entrée avec interruptions (`InterruptIn`).
   - Une LED est configurée comme une sortie numérique (`DigitalOut`).

2. **Gestion des interruptions :**
   - Une fonction `led_on_off` bascule l'état de la LED.
   - Cette fonction est déclenchée par les événements d'interruption (montée et descente) du bouton.

3. **Boucle principale :**
   - Une boucle infinie maintient le programme actif.
   - Une temporisation (250 ms) est utilisée pour éviter une consommation inutile de ressources, bien que cette boucle n'interagisse pas activement avec le bouton ou la LED.

# EXERCICE 2 : Mesure du temps d'appui sur un bouton avec affichage et contrôle de LED

Cet exercice utilise **Mbed OS** pour mesurer la durée d'appui sur un bouton. En parallèle, une LED change d'état au début et à la fin de l'appui. La durée est affichée sur la console à l'aide d'un `printf`.

## Fonctionnement

1. **Gestion des interruptions :**
   - Lors de l'appui sur le bouton (`rise`), la LED change d'état et un minuteur démarre.
   - Lors du relâchement du bouton (`fall`), la LED revient à son état initial, et la durée d'appui est enregistrée.

2. **Boucle principale :**
   - Une boucle vérifie si une durée a été enregistrée.
   - Si oui, elle affiche la durée (en millisecondes) sur la console.

## Explications

- **Appui sur le bouton :**
  - La fonction `led_on()` est déclenchée :
    - Le minuteur est réinitialisé et démarré.
    - La LED change d'état.

- **Relâchement du bouton :**
  - La fonction `led_off()` est déclenchée :
    - Le minuteur s'arrête.
    - Une variable indique qu'une durée est prête à être affichée.
    - La LED revient à son état initial.

- **Affichage de la durée :**
  - La boucle principale surveille si une durée est prête à être affichée.
  - Lorsque c'est le cas, elle utilise `printf` pour afficher la durée en millisecondes dans la console.


# EXERCICE 3 : Modification de la fréquence de clignotement d'une LED via un bouton

Cet exercice utilise la bibliothèque **Mbed OS** pour contrôler une LED. La fréquence de clignotement de la LED est modifiée à chaque appui sur un bouton, grâce à l'utilisation d'un **Ticker**.

## Fonctionnement du code 

1. **Initialisation des objets :**
   - Un bouton est configuré comme une entrée avec interruptions (`InterruptIn`).
   - Une LED est configurée comme une sortie numérique (`DigitalOut`).
   - Un **Ticker** est utilisé pour basculer l'état de la LED à intervalle régulier.

2. **Gestion des interruptions :**
   - Une fonction `ChangeFreq` est déclenchée à chaque appui sur le bouton :
     - Elle augmente la période du **Ticker**.
     - Si la période dépasse une certaine limite, elle est réinitialisée.

3. **Clignotement de la LED :**
   - La fonction `led_on` est appelée périodiquement par le **Ticker** pour inverser l'état de la LED.

4. **Boucle principale :**
   - Une boucle infinie maintient le programme actif.
   - Une temporisation (100 ms) est utilisée pour réduire la consommation de ressources.

## Explications

- **Appui sur le bouton :**
  - La fonction `ChangeFreq` :
    - Augmente la période du **Ticker** (`tick_value`).
    - Réinitialise la période si elle dépasse une certaine limite.
    - Redéfinit le **Ticker** avec la nouvelle période.

- **Clignotement de la LED :**
  - Le **Ticker** appelle `led_on` à intervalle régulier défini par `tick_value`.

- **Détection passive :**
  - Le programme ne réalise aucune autre tâche active, mais reste prêt à détecter les événements du bouton ou à activer le clignotement.


# EXERCICE 4 : Lecture de données depuis un capteur de CO2 via I2C

Cet exercice utilise la bibliothèque **Mbed OS** pour lire des données provenant d'un capteur de CO2 connecté via un bus I2C. Le programme configure le capteur pour effectuer des mesures périodiques et récupère les concentrations de CO2 en boucle.

## Fonctionnement du code

1. **Configuration du capteur :**
   - Une commande de démarrage est envoyée au capteur pour initialiser les mesures périodiques.
   - Cette commande utilise l'adresse I2C spécifique du capteur et un ensemble de données prédéfinies.

2. **Lecture des données de CO2 :**
   - Une commande est envoyée pour demander la dernière mesure de concentration en CO2 disponible.
   - Les données sont lues dans un tampon et converties en un entier représentant la concentration en ppm (parties par million).

3. **Affichage des résultats :**
   - Les données de CO2 sont affichées sur la console en format décimal et hexadécimal.
   - En cas d'erreur, un message correspondant est affiché.

4. **Boucle principale :**
   - Une boucle infinie exécute périodiquement la commande de lecture et affiche les concentrations mesurées.

## Explications

- **Initialisation du bus I2C :**
  - L'objet `I2C` est configuré avec les broches spécifiques (`P1_I2C_SDA` et `P1_I2C_SCL`).

- **Démarrage des mesures :**
  - Une commande composée de deux octets (`START_PERIOD_MEASURE_BYTE1` et `START_PERIOD_MEASURE_BYTE2`) est envoyée pour activer les mesures périodiques du capteur.
  - Un retour d'erreur est vérifié pour s'assurer que l'opération a été exécutée correctement.

- **Lecture des données de CO2 :**
  - Une commande de lecture est envoyée avec deux octets (`READ_SENSOR_BYTE1` et `READ_SENSOR_BYTE2`).
  - Les données de concentration en CO2 sont lues dans un tampon de trois octets, puis converties en une valeur entière (ppm).

- **Gestion des erreurs :**
  - Après chaque opération I2C (écriture ou lecture), le code vérifie si une erreur s'est produite et affiche un message d'erreur si nécessaire.

- **Résolution et unité des données :**
  - La valeur mesurée correspond à une concentration en CO2 exprimée en ppm (parts per million).


# EXERCICE 5 : Driver pour un capteur de CO2 SCD4x avec lecture I2C

Cet exercice utilise la bibliothèque **Mbed OS** pour interfacer un capteur de CO2 SCD4x via un bus I2C. Le programme est structuré autour d'une classe **SCD4x_driver**, qui gère les communications avec le capteur et permet d'obtenir des mesures de CO2, de température et d'humidité.

## Fonctionnement du code 

### **Driver `SCD4x_driver`**

1. **Initialisation :**
   - Le driver est initialisé avec les broches I2C (SDA, SCL) et l'adresse du capteur.

2. **Démarrage des mesures :**
   - La méthode `startMeasurement` envoie une commande pour démarrer les mesures périodiques.

3. **Lecture des données :**
   - La méthode `readData` récupère les données brutes du capteur, les décode et met à jour les variables internes pour le CO2, la température et l'humidité.

4. **Accès aux données :**
   - Les méthodes `getCO2`, `getTemperature`, et `getHumidity` retournent respectivement les concentrations de CO2 (en ppm), la température (en °C), et l'humidité relative (en %).

5. **Sécurité multi-thread :**
   - Un mutex assure que les communications I2C et les mises à jour de données sont thread-safe.

### **Programme principal**

1. **Initialisation du driver :**
   - L'objet `SCD4x_driver` est créé et configuré pour utiliser les broches I2C définies (`P1_I2C_SDA`, `P1_I2C_SCL`).

2. **Démarrage des mesures :**
   - La méthode `startMeasurement` est appelée pour lancer la collecte périodique de données.

3. **Lecture périodique :**
   - Une boucle infinie appelle `readData` toutes les 5 secondes pour lire les données depuis le capteur.
   - Les valeurs mesurées (CO2, température, humidité) sont affichées sur la console.

## Avantages de l'utilisation de drivers

1. **Réutilisabilité :**
   - Le driver peut être utilisé dans différents projets sans modifier le code principal.

2. **Sécurité multi-thread :**
   - L'utilisation d'un mutex assure un fonctionnement stable même dans des applications multi-thread.

3. **Clarté et organisation :**
   - Le code est divisé en responsabilités distinctes : le driver gère les interactions avec le capteur, tandis que le programme principal gère la logique applicative.

# EXERCICE 6 : Synchronisation de threads avec Mutex et clignotement de LED

Cet exercice utilise **Mbed OS** pour démontrer la gestion de threads synchronisés à l'aide d'un mutex. Deux threads exécutent des tâches concurrentes ("Ping" et "Pong"), tandis que le thread principal clignote une LED et signale son activité via un message.

## Fonctionnement du code 

### **Threads**

1. **Thread 1 ("Ping") :**
   - Affiche le mot "Ping" sur la console.
   - Utilise un mutex pour assurer une gestion exclusive de l'accès à la console.

2. **Thread 2 ("Pong") :**
   - Affiche le mot "Pong" sur la console.
   - Utilise également le mutex pour éviter les collisions lors de l'accès à la console.

3. **Thread Principal :**
   - Clignote une LED (LED1) toutes les 5 secondes.
   - Affiche "Alive!" sur la console, tout en respectant le verrouillage du mutex.

### **Mutex**

- Un mutex global (`mutex_pp`) est utilisé pour s'assurer que les messages "Ping", "Pong" et "Alive!" ne se chevauchent pas sur la console.
- Les threads acquièrent le mutex avant d'accéder à la console et le libèrent après l'écriture.

### **Boucle Principale**

- Le thread principal fonctionne en parallèle avec les deux autres threads.
- Il clignote une LED et vérifie périodiquement l'état d'activité du programme via des messages console.

## Explications détaillées

1. **Initialisation des threads :**
   - Deux threads (`thread1` et `thread2`) sont créés et démarrés avec les fonctions `ping_thread` et `pong_thread`.

2. **Gestion du mutex :**
   - Les fonctions des threads verrouillent le mutex avant d'accéder à la console.
   - Cela garantit que les messages ne se mélangent pas, même si les threads sont exécutés de manière concurrente.

3. **Clignotement des LEDs :**
   - Une LED est configurée pour alterner son état (ON/OFF) dans la boucle principale, indiquant que le programme fonctionne.

4. **Synchronisation :**
   - Les délais (`sleep_for`) introduits dans chaque thread contrôlent la fréquence des opérations sans interférer avec les autres threads.

# PROJET FINAL : Intégration d'un capteur CO₂ avec LoRaWAN et Mbed OS

Cet exercice combine un capteur SCD4x pour mesurer le CO₂, la température et l'humidité, avec LoRaWAN pour transmettre les données collectées à un réseau distant. Le tout est implémenté à l'aide de Mbed OS.

## Structure des fichiers du projet
      src
      ├── driver
      │   ├── include
      │   │   └── SCD4x_driver.hpp   # Interface du driver pour le capteur SCD4x
      │   └── src
      │       └── SCD4x_driver.cpp   # Implémentation du driver
      ├── include
      │   ├── lora_radio_helper.h    # Configuration et initialisation des modules radio LoRaWAN
      │   └── mbedtls_lora_config.h  # Configuration de la bibliothèque Mbed TLS pour LoRa
      └── src
         └── main.cpp               # Programme principal du projet

## Fonctionnalités principales

1. **Mesure avec le capteur SCD4x** :
   - Le capteur collecte des données environnementales (CO₂, température, humidité).
   - Les données sont transmises via l'interface I2C.

2. **Communication LoRaWAN** :
   - Le programme utilise la pile LoRaWAN pour envoyer et recevoir des données.
   - Les messages sont transmis sous forme de JSON aux serveurs distants.

3. **Gestion des événements LoRaWAN** :
   - Les événements (connexion, envoi/réception, erreurs) sont gérés via un gestionnaire d'événements.

4. **Utilisation d'une file d'événements** :
   - Les tâches, comme l'envoi de messages périodiques, sont programmées à l'aide de la file `EventQueue`.

---

## **Structure du programme**

### **Capteur SCD4x**

- **Initialisation** :
  - Le capteur est configuré via l'interface I2C à l'adresse `0x62`.
  - Les mesures périodiques sont démarrées avec `startMeasurement()`.

- **Lecture des données** :
  - Les mesures sont lues à intervalles réguliers avec `readData()`.
  - Les valeurs sont extraites via les méthodes `getCO2()`, `getTemperature()`, et `getHumidity()`.

### **Pile LoRaWAN**

- **Configuration initiale** :
  - Initialisation de la pile LoRaWAN avec `lorawan.initialize()`.
  - Activation de l'ADR (Adaptive Data Rate) pour optimiser les paramètres de transmission.

- **Envoi de messages** :
  - Les données mesurées sont encapsulées dans un message JSON envoyé avec `lorawan.send()`.

- **Réception de messages** :
  - Les messages reçus du réseau LoRaWAN sont traités avec `lorawan.receive()`.

- **Gestion des événements** :
  - Les événements LoRaWAN, comme les erreurs de transmission ou la réception, sont gérés dans `lora_event_handler()`.

### **Envoi périodique des messages**

- Une tâche récurrente est planifiée avec `ev_queue.call_every()` pour envoyer les mesures à intervalle régulier.

---

## **Explications détaillées**

### **Configuration LoRaWAN**

- Les paramètres de configuration LoRaWAN, comme les clés d'accès ou le port d'application, sont définis dans le fichier `mbed_app.json`.
- La fréquence d'envoi est contrôlée par la constante `TX_TIMER`.

### **Structure des messages**

- Les données envoyées sont formatées en JSON. Exemple :
  ```json
  {
      "CO2": 400,
      "Temp": 25,
      "Humidity": 50
  }

### Résultat sur LoRaWAN

    Résultat du programme après avoir soufflé dessus :


    Résultat précédent sans avoir soufflé dessus (capture d'écran prise un jour différent):








