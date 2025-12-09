# Guide Étape par Étape - Ajouter le bouton "Voir Tous RDV"

## ⚠️ IMPORTANT : Le bouton doit être ajouté dans Qt Designer

Le message "ATTENTION: Bouton btnVoirTousRDV non trouvé" signifie que le bouton n'existe pas encore dans l'interface.

## 📋 Étapes détaillées

### Étape 1 : Ouvrir Qt Designer

1. Dans Qt Creator, faire un **clic droit** sur le fichier `mainwindow.ui`
2. Sélectionner **"Ouvrir avec"** → **"Qt Designer"**
   - OU double-cliquer sur `mainwindow.ui` dans l'explorateur de fichiers Windows
   - OU ouvrir Qt Designer séparément et ouvrir le fichier `mainwindow.ui`

### Étape 2 : Trouver la page principale

1. Dans Qt Designer, regarder le **panneau de gauche** (hiérarchie des widgets)
2. Chercher `stackedWidgetC` dans la liste
3. **Développer** `stackedWidgetC` en cliquant sur la flèche
4. Vous verrez plusieurs pages (page, page_2, etc.)
5. **Sélectionner la première page** (celle qui contient les boutons comme "Ajouter", "Supprimer", "PDFC", etc.)
   - C'est la **page principale** (page index 0)

### Étape 3 : Trouver le bouton PDFC

1. Sur la page principale, chercher le bouton **"PDFC"** (Exporter PDF)
2. Vous pouvez le trouver :
   - En cliquant dessus directement sur la page
   - OU en le cherchant dans la hiérarchie des widgets (panneau de gauche)
   - Le bouton PDFC devrait être visible en bas de la page

### Étape 4 : Ajouter le nouveau bouton

1. Dans la **palette d'outils** (généralement à gauche), chercher **"Push Button"**
2. **Glisser-déposer** le Push Button sur la page, juste à côté du bouton PDFC
3. Le bouton apparaîtra sur la page

### Étape 5 : Configurer le bouton (CRUCIAL)

1. **Clic droit sur le nouveau bouton** → **"Changer le nom de l'objet..."**
   - OU sélectionner le bouton et regarder dans le panneau "Propriétés" en bas à droite
   - Chercher la propriété **"objectName"**

2. **Entrer exactement** : `btnVoirTousRDV`
   - ⚠️ **ATTENTION** : Le nom doit être EXACTEMENT `btnVoirTousRDV`
   - Pas d'espaces
   - Respecter la casse (minuscules/majuscules)
   - Pas de fautes de frappe

3. **Configurer le texte** :
   - Dans les propriétés, chercher **"text"**
   - Entrer : `Voir Tous RDV`

4. **Ajuster la position** :
   - Position du bouton PDFC : x=710, y=580
   - Position suggérée pour le nouveau bouton : x=810, y=580 (juste à droite)
   - Vous pouvez aussi le placer manuellement en le glissant

5. **Ajuster la taille** (optionnel) :
   - Largeur : 90 (comme PDFC)
   - Hauteur : 29 (comme PDFC)

### Étape 6 : Vérifier

1. **Sélectionner le bouton**
2. Dans le panneau "Propriétés", vérifier :
   - ✅ **objectName** = `btnVoirTousRDV` (exactement)
   - ✅ **text** = `Voir Tous RDV`
   - ✅ **visible** = true (coché)
   - ✅ **enabled** = true (coché)

### Étape 7 : Sauvegarder

1. **Fichier → Enregistrer** (Ctrl+S)
2. Vérifier que le fichier `mainwindow.ui` a bien été modifié (date de modification)

### Étape 8 : Recompiler dans Qt Creator

1. **Retourner dans Qt Creator**
2. **Construire → Nettoyer** (pour supprimer les anciens fichiers)
3. **Construire → Exécuter qmake** (pour régénérer les fichiers à partir du .ui)
4. **Construire → Construire le projet** (pour compiler)

### Étape 9 : Vérifier le résultat

1. **Lancer l'application**
2. Regarder la **console de sortie** dans Qt Creator
3. Vous devriez voir : `"Bouton btnVoirTousRDV trouvé et connecté"` au lieu de l'avertissement
4. Le bouton devrait apparaître à côté du bouton "Exporter PDF"

## 🔍 Vérification visuelle dans Qt Designer

Après avoir ajouté le bouton, vous devriez voir dans la hiérarchie des widgets :

```
stackedWidgetC
  └── page (page principale)
      ├── ... (autres widgets)
      ├── PDFC (bouton Exporter PDF)
      └── btnVoirTousRDV (votre nouveau bouton) ← DOIT APPARAÎTRE ICI
```

## ❌ Erreurs courantes

1. **Bouton sur la mauvaise page** :
   - Le bouton doit être sur la **première page** du stackedWidgetC
   - Pas sur la page RDV (page_2)

2. **Mauvais nom** :
   - ❌ `btnVoirTousRDV ` (avec espace à la fin)
   - ❌ `BtnVoirTousRDV` (majuscule au début)
   - ❌ `btnVoirTousRDVs` (avec 's' à la fin)
   - ✅ `btnVoirTousRDV` (exactement comme ça)

3. **Bouton masqué** :
   - Vérifier que `visible = true` dans les propriétés
   - Vérifier que le bouton n'est pas derrière un autre widget

4. **Projet non recompilé** :
   - Toujours faire qmake après avoir modifié le .ui
   - Toujours reconstruire le projet

## 🆘 Si ça ne fonctionne toujours pas

1. Vérifier que le fichier `mainwindow.ui` a bien été modifié :
   - Regarder la date de modification du fichier
   - Ouvrir le fichier .ui dans un éditeur de texte et chercher `btnVoirTousRDV`

2. Supprimer le dossier `build` et recompiler complètement

3. Vérifier qu'il n'y a pas d'erreurs de compilation

4. Essayer de renommer le bouton PDFC temporairement pour voir si le problème vient de la recherche de widgets

