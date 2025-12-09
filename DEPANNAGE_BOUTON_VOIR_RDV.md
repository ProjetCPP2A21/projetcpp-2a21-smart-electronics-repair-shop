# Dépannage - Le bouton "Voir Tous RDV" n'apparaît pas

## Vérifications à faire

### 1. Vérifier que le bouton existe dans Qt Designer

1. Ouvrir `mainwindow.ui` dans Qt Designer
2. Aller sur la **page principale** (page index 0, première page du stackedWidgetC)
3. Chercher le bouton dans la hiérarchie des widgets (panneau de gauche)
4. Vérifier que le bouton existe et qu'il s'appelle exactement **`btnVoirTousRDV`**

### 2. Vérifier le nom du bouton

**IMPORTANT** : Le nom doit être exactement `btnVoirTousRDV` (sans espaces, respecter la casse)

Pour vérifier/modifier le nom :
1. Sélectionner le bouton dans Qt Designer
2. Regarder dans le panneau "Propriétés" en bas à droite
3. Chercher la propriété **"objectName"**
4. Elle doit être exactement : `btnVoirTousRDV`
5. Si ce n'est pas le cas, modifier directement dans le champ "objectName"

### 3. Vérifier que le bouton est visible

1. Dans Qt Designer, sélectionner le bouton
2. Vérifier dans les propriétés :
   - **"visible"** doit être coché (true)
   - **"enabled"** doit être coché (true)
   - Le bouton ne doit pas être masqué par un autre widget

### 4. Vérifier que le bouton est sur la bonne page

Le bouton doit être sur la **page principale** (page index 0), pas sur une autre page du stackedWidgetC.

Pour vérifier :
1. Dans la hiérarchie des widgets, trouver `stackedWidgetC`
2. Vérifier que le bouton est dans la première page (page index 0)
3. Si le bouton est sur une autre page, le déplacer vers la page principale

### 5. Recompiler le projet

Après avoir ajouté/modifié le bouton dans Qt Designer :

1. **Sauvegarder** le fichier `.ui` (Ctrl+S)
2. Dans Qt Creator :
   - **Construire → Nettoyer** (pour supprimer les anciens fichiers générés)
   - **Construire → Exécuter qmake** (pour régénérer les fichiers à partir du .ui)
   - **Construire → Construire le projet** (pour compiler)

### 6. Vérifier les messages de debug

Le code ajoute maintenant des messages de debug. Lors du lancement de l'application, vérifier dans la console :

- Si vous voyez : `"Bouton btnVoirTousRDV trouvé et connecté"` → Le bouton est bien détecté
- Si vous voyez : `"ATTENTION: Bouton btnVoirTousRDV non trouvé dans l'interface"` → Le bouton n'existe pas ou a un mauvais nom

### 7. Vérifier la position du bouton

Le bouton doit être à côté du bouton "PDFC" (Exporter PDF) :
- Position du bouton PDFC : x=710, y=580
- Position suggérée pour btnVoirTousRDV : x=810, y=580 (juste à droite)

Si le bouton est en dehors de la zone visible de la fenêtre, il ne sera pas visible.

### 8. Solution alternative : Vérifier manuellement dans le code

Si le bouton existe mais n'est toujours pas détecté, vous pouvez vérifier manuellement :

1. Ouvrir `mainwindow.cpp`
2. Chercher la ligne avec `findChild<QPushButton*>("btnVoirTousRDV")`
3. Ajouter temporairement ce code pour lister tous les boutons :

```cpp
// Code de debug - à ajouter temporairement dans le constructeur
QList<QPushButton*> allButtons = findChildren<QPushButton*>();
qDebug() << "Tous les boutons trouvés:";
foreach(QPushButton* btn, allButtons) {
    qDebug() << "  -" << btn->objectName();
}
```

Cela affichera tous les noms de boutons trouvés et vous permettra de voir si le bouton existe avec un autre nom.

## Étapes de création complète du bouton

Si le bouton n'existe pas du tout, suivez ces étapes :

1. **Ouvrir Qt Designer** avec `mainwindow.ui`
2. **Sélectionner la page principale** (première page du stackedWidgetC)
3. **Trouver le bouton PDFC** (Exporter PDF)
4. **Ajouter un nouveau QPushButton** :
   - Glisser-déposer depuis la palette d'outils
   - Le placer à côté du bouton PDFC
5. **Configurer le bouton** :
   - Clic droit → "Changer le nom de l'objet..."
   - Entrer : `btnVoirTousRDV`
   - Texte : "Voir Tous RDV"
   - Position : x=810, y=580 (ou juste à côté de PDFC)
   - Taille : largeur=90, hauteur=29 (comme PDFC)
6. **Sauvegarder** (Ctrl+S)
7. **Recompiler** le projet

## Si le problème persiste

1. Vérifier que le fichier `mainwindow.ui` a bien été modifié et sauvegardé
2. Vérifier qu'il n'y a pas d'erreurs de compilation
3. Vérifier les messages de debug dans la console Qt Creator
4. Essayer de supprimer le dossier `build` et recompiler complètement

