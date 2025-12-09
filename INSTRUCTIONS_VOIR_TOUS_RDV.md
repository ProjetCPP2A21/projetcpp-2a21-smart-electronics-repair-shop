# Instructions pour ajouter la fonctionnalité "Voir Tous les RDV"

## Fonctionnalités ajoutées

1. **Bouton "Voir Tous RDV"** : Affiche tous les RDV dans un tableau
2. **Bouton "Alerter"** : Un bouton pour chaque RDV dans le tableau pour envoyer une alerte à Arduino
3. **Bouton "Retour"** : Pour revenir à la page principale

## Étapes pour ajouter dans Qt Designer

### 1. Ajouter le bouton "Voir Tous RDV" sur la page principale

1. Ouvrir `mainwindow.ui` dans Qt Designer
2. Aller sur la **page principale** (page index 0)
3. Trouver le bouton **"PDFC"** (Exporter PDF) dans la hiérarchie ou sur la page
   - Le bouton PDFC se trouve généralement en bas de la page (coordonnées x=710, y=580)
4. Ajouter un **QPushButton** juste à côté du bouton PDFC
   - Position suggérée : à droite du bouton PDFC (par exemple x=810, y=580)
5. **Nommer le bouton** : `btnVoirTousRDV` (nom exact requis)
6. **Texte** : "Voir Tous RDV"
7. Ajuster la taille pour correspondre au bouton PDFC (largeur ~90, hauteur ~29)

### 2. Créer une nouvelle page pour afficher tous les RDV

1. Dans Qt Designer, trouver `stackedWidgetC` dans la hiérarchie
2. **Clic droit sur stackedWidgetC** → **"Insérer une page"** ou **"Ajouter une page"**
3. Une nouvelle page sera créée (probablement index 2)

### 3. Ajouter les widgets sur la nouvelle page

Sur la nouvelle page créée, ajouter :

#### a) QTableWidget
1. Glisser un **QTableWidget** sur la page
2. **Nommer** : `tableWidgetTousRDV` (nom exact requis)
3. Ajuster la taille pour remplir la page

#### b) QPushButton "Retour"
1. Glisser un **QPushButton** sur la page
2. **Nommer** : `btnRetourTousRDV` (nom exact requis)
3. **Texte** : "Retour"
4. Le placer en haut ou en bas de la page

### 4. Sauvegarder et recompiler

1. **Fichier → Enregistrer** (Ctrl+S)
2. Dans Qt Creator :
   - **Construire → Exécuter qmake**
   - **Construire → Construire le projet**

## Structure de la page

```
Page "Voir Tous RDV" (index 2)
├── QPushButton "Retour" (btnRetourTousRDV)
└── QTableWidget (tableWidgetTousRDV)
    ├── Colonne 1: ID Client
    ├── Colonne 2: Date RDV
    ├── Colonne 3: Heure
    ├── Colonne 4: Client
    └── Colonne 5: Bouton "Alerter" (généré dynamiquement)
```

## Fonctionnement

1. **Clic sur "Voir Tous RDV"** :
   - Récupère tous les RDV depuis la base de données
   - Affiche dans le tableau avec colonnes : ID Client, Date RDV, Heure, Client
   - Ajoute un bouton "Alerter" pour chaque ligne

2. **Clic sur "Alerter"** (dans une ligne) :
   - Envoie l'ID du client à Arduino
   - Affiche un message de confirmation ou d'erreur

3. **Clic sur "Retour"** :
   - Retourne à la page principale

## Code déjà implémenté

- ✅ Fonction `afficherTousLesRDV()` dans `client.cpp`
- ✅ Fonction `on_btnVoirTousRDV_clicked()` dans `mainwindow.cpp`
- ✅ Fonction `on_btnRetourTousRDV_clicked()` dans `mainwindow.cpp`
- ✅ Fonction `alerterRDVDepuisTable()` dans `mainwindow.cpp`
- ✅ Connexions automatiques des boutons (si les noms sont corrects)

## Vérification

Après avoir ajouté les widgets dans Qt Designer :

1. Vérifier les noms exacts :
   - `btnVoirTousRDV` (bouton sur la page principale)
   - `tableWidgetTousRDV` (tableau sur la nouvelle page)
   - `btnRetourTousRDV` (bouton retour sur la nouvelle page)

2. Recompiler le projet

3. Tester :
   - Cliquer sur "Voir Tous RDV" → devrait afficher tous les RDV
   - Cliquer sur "Alerter" dans une ligne → devrait envoyer l'alerte à Arduino
   - Cliquer sur "Retour" → devrait revenir à la page principale

## Notes

- Le tableau est rempli dynamiquement avec les données de la base
- Chaque ligne a son propre bouton "Alerter" qui envoie l'ID du client correspondant
- Les boutons sont créés automatiquement lors du chargement des RDV
- La vérification automatique des RDV en cours continue de fonctionner en arrière-plan

