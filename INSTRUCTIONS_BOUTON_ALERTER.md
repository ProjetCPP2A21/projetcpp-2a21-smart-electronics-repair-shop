# Instructions pour ajouter le bouton "Alerter" dans l'interface

## Étapes pour ajouter le bouton dans Qt Designer

1. **Ouvrir le fichier `mainwindow.ui` dans Qt Designer**

2. **Aller sur la page RDV** (stackedWidgetC, page index 1)

3. **Ajouter un QPushButton** :
   - Glisser un `QPushButton` depuis la palette d'outils
   - Le placer à côté des boutons "Ajouter RDV" et "Supprimer RDV"

4. **Configurer le bouton** :
   - **Nom de l'objet** : `btnAlerterRDV` (IMPORTANT : ce nom exact est requis)
   - **Texte** : "Alerter"
   - **Tooltip** (optionnel) : "Envoyer une alerte à l'afficheur pour ce RDV"

5. **Sauvegarder** le fichier `.ui`

6. **Recompiler** le projet avec `qmake` et `make`

## Fonctionnalités du bouton

### Alerte manuelle :
- Sélectionner une date dans le calendrier
- Sélectionner un RDV dans le tableau
- Cliquer sur "Alerter"
- L'ID du client sera envoyé à Arduino et affiché sur le LCD

### Vérification automatique :
- Continue de fonctionner en arrière-plan
- Vérifie toutes les 60 secondes les RDV en cours
- Envoie automatiquement les alertes pour les nouveaux RDV

## Comportement

- **Si Arduino n'est pas connecté** : Affiche un message d'erreur
- **Si aucun RDV n'est sélectionné** : Affiche un message d'avertissement
- **Si l'envoi réussit** : Affiche un message de confirmation avec l'ID du client

## Format du message envoyé

Le message envoyé à Arduino est au format : `RDV:[ID_CLIENT]`
- Exemple : `RDV:123`

Le code Arduino existant (`arduino_lcd.ino`) gère déjà ce format et affichera :
- Ligne 1 : "ID 123"
- Ligne 2 : "RDV maintenant"

