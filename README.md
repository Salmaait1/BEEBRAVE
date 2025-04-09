# BEEBRAVE
# Guide Utilisateur – Projet OpenRuche 
# Contexte & Objectif du projet 

OpenRuche est un système de surveillance autonome et intelligent conçu pour protéger et 
suivre à distance les colonies d’abeilles. Grâce à l’intégration de capteurs multiples, d’une intelligence artificielle embarquée, et d’un système de communication LoRaWAN, le projet permet : 

        • Un suivi temps réel des paramètres clés de la ruche (température, humidité, poids, 
          activité). 
          
        • Une protection proactive contre des menaces comme les frelons ou l'absence de la 
          reine. 
          
        • Une autonomie énergétique assurée par un panneau solaire. 
        
        
Le tout vise à fournir à l’apiculteur une solution fiable et non-intrusive, accessible à distance via 
la plateforme BEEP.

# Accès aux données (The Things Network) 

Le système OpenRuche utilise le réseau LoRaWAN via The Things Network (TTN) pour transmettre les données de la ruche en temps réel. 
Informations de connexion TTN : 

    - Lien : https://eu1.cloud.thethings.network/console 
    
    - Email : idriliza@gmail.com 
    
    - Mot de passe : FarahSalmaWassim4! 
    
    - Nom de l'application TTN : openruche 
    
    - Nom du device : mkrwan118 
    
    - AppEUI : 0000000000000000 
    
    - AppKey : 70C141C1E9629690E70ACF0077435A69 
    
Les données sont envoyées automatiquement toutes les 10 minutes depuis la ruche.
#
# Visualisation des données sur BEEP 
Les données collectées sont redirigées vers la plateforme BEEP, spécialisée dans le suivi intelligent des ruches. 

  • Lien : https://beep.nl 
  
  • Interface conviviale permettant de :
  
      o Suivre les évolutions de la température, humidité, poids, niveau de batterie, 
        etc. 
        
      o Visualiser des graphiques sur plusieurs jours 
      
      o Identifier rapidement les anomalies (perte de poids, chute de température, etc.) 
      
# Intégration avec TTN 

L’envoi vers BEEP se fait via une requête POST HTTP au format attendu par BEEP. Cela nécessite 
de configurer un Payload Formatter dans TTN (TTS v3). 

  • URL de réception des données : https://beep-test.azurewebsites.net/api/yann 
  
  • Compte BEEP générique utilisé : 
  
      o Login : or2021@yopmail.com 
      
      o Mot de passe : Sigfox21# 

    
Exemple de Payload Formatter (en JavaScript) : 

     
        function decodeUplink(input) { 
        
    var data = {}; 
    
    data.key = "ecbawllr2r3xxxx"; // identifiant unique de la ruche dans BEEP 
    
    data.t_i = (input.bytes[1] << 8 | input.bytes[0]) / 100; 
    
    data.h = (input.bytes[3] << 8 | input.bytes[2]) / 100; 
    
    return { 
    
    data: data, 
    
    warnings: [], 
    
    errors: [] 
    
          }; 
  
        } 
Le champ key correspond à l’identifiant unique de votre ruche sur BEEP. Il peut être trouvé dans 
l’interface BEEP > Appareils > Modifier > Champ “identifiant unique”.

# Liste des capteurs et fonctions 
<img width="341" alt="image" src="https://github.com/user-attachments/assets/d982bb36-8214-4005-a6b8-b2c8bd5b2950" />

# Intelligence embarquée (IA) 
La carte Nano 33 BLE Sense embarque un modèle Edge Impulse permettant : 

  • L’analyse du son capté dans la ruche. 
  
  • La détection de la présence ou absence de la reine selon le comportement sonore. 
  
  • La transmission du résultat à la carte MKR, qui intègre l’information dans le message 
    LoRa. 
    
La Nano est alimentée seulement quelques secondes toutes les 10 minutes pour réduire la 
consommation. 

# Système d’alimentation et autonomie 
  • Batterie : LiPo 3.7V – 1050mAh 
  
  • Recharge : Panneau solaire connecté via contrôleur de charge 
  
  • Temporisation : Coupure automatique de l’alimentation des broches toutes les 10 minutes à l’aide d’un régulateur REG09P, utilisé pour couper uniquement l’alimentation des capteurs (la carte MKR WAN reste sous tension). 
  
  • Mesure de consommation via Otii : 
  
      o Autonomie observée sans panneau : ~4.6 jours 
      
      o Autonomie avec recharge solaire : prolongée de plusieurs jours 
      
      o La batterie chute lentement de 4.0V à 3.7V en 27h, et se recharge à 4.1V en 2–3h. 
      
  • Tension minimale observée : Jamais en dessous de 3.3V (seuil de coupure de la 
  MKRWAN)
  
# Organisation & gestion de projet 
  • Répartition initiale des tâches : chaque membre avait une mission claire 
    (programmation, capteurs, IA, électronique). 
    
  • Méthode agile : En cas de blocage, entraide immédiate puis retour aux tâches initiales. 
  
  • Phase d’intégration : Travail en binôme pour l’assemblage global. 
  
  • Outils utilisés : Google Docs, WhatsApp, Canva, GitHub.

# Publication du projet 
Un article complet est publié sur une plateforme de partage de projets open-source : 
  • Lien : (à insérer une fois disponible, ex : hackster.io ou snapiculture.com) 
  
  • Il contient : 
  
      o Schémas de montage 
      
      o Code Arduino 
      
      o Explications techniques 
      
      o Visualisation des données en temps réel 
      
# Utilisation résumée 
  1. Déployer la ruche avec les capteurs correctement installés 
  2. Alimenter le système (batterie + panneau solaire) 
  3. Attendre la connexion automatique à TTN 
  4. Visualiser les données sur BEEP 
  5. Intervenir en cas d’alerte (baisse de poids, attaque de frelon, température anormale, 
    etc.)


Ce guide résume l’utilisation de notre système de surveillance OpenRuche, à destination 
des apiculteurs et des acteurs de la protection des abeilles.
