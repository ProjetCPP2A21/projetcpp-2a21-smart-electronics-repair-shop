# Instructions pour ajouter le bouton "Alerter" dans Qt Designer

## Étapes détaillées :

### 1. Ouvrir le fichier UI
- Ouvrir `mainwindow.ui` dans Qt Designer (clic droit → Ouvrir avec → Qt Designer)

### 2. Aller sur la page RDV
- Dans la hiérarchie des widgets à gauche, trouver `stackedWidgetC`
- Cliquer sur la page index **1** (c'est la page RDV avec le calendrier)
- Ou cliquer sur l'onglet "page_2" en bas de l'éditeur

### 3. Ajouter le bouton
- Dans la palette d'outils à gauche, trouver **"Push Button"**
- Glisser-déposer le bouton sur la page RDV
- Le placer à côté des boutons "Ajouter RDV" et "Supprimer RDV"

### 4. Configurer le bouton (IMPORTANT)
- **Clic droit sur le bouton** → **"Changer le nom de l'objet..."**
- Entrer exactement : `btnAlerterRDV` (sans espaces, respecter la casse)
- Cliquer sur OK

### 5. Personnaliser le bouton
- **Texte** : "Alerter" (dans les propriétés à droite)
- **Tooltip** (optionnel) : "Envoyer une alerte à l'afficheur pour ce RDV"
- Ajuster la taille et la position si nécessaire

### 6. Sauvegarder
- **Fichier → Enregistrer** (Ctrl+S)
- Fermer Qt Designer

### 7. Recompiler
- Dans Qt Creator : **Construire → Exécuter qmake**
- Puis **Construire → Construire le projet**

### 8. Vérifier
- Le bouton devrait maintenant apparaître à côté des autres boutons RDV
- Le code de connexion est déjà décommenté dans `mainwindow.cpp`

## Vérification du nom du bouton

Pour vérifier que le nom est correct :
1. Dans Qt Designer, sélectionner le bouton
2. Regarder dans le panneau "Propriétés" en bas à droite
3. La propriété "objectName" doit être exactement `btnAlerterRDV`

## Si le bouton n'apparaît toujours pas

1. **Vérifier que vous êtes sur la bonne page** :
   - Le bouton doit être sur la page RDV (page index 1), pas sur la page principale

2. **Vérifier le nom exact** :
   - Le nom doit être `btnAlerterRDV` (pas `btnAlerter`, pas `BtnAlerterRDV`, etc.)

3. **Vérifier que le fichier .ui est sauvegardé** :
   - Le fichier `mainwindow.ui` doit être modifié et sauvegardé

4. **Recompiler complètement** :
   - Nettoyer le projet (Construire → Nettoyer)
   - Exécuter qmake
   - Reconstruire

5. **Vérifier les erreurs de compilation** :
   - Si le bouton existe mais le code ne compile pas, vérifier les erreurs dans la console

