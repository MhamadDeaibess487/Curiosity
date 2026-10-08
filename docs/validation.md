# Bilan de réorganisation et de validation

## Branche et intégrité

Travail réalisé sur `chore/reorganisation-professionnelle`, à partir du checkout
fourni sur la branche `work`. Aucun changement n’a été intégré à `main`.
Les 29 sources C, les 8 headers et les autres données déplacées (89 fichiers
au total) sont identiques octet par octet à leur version initiale, vérifiés
par SHA-256. Les sources et données utiles sont toutes conservées.
Neuf binaires et deux rapports générés ont été retirés du suivi Git, sans
supprimer les copies locales. Aucun objet `.o` n’était initialement suivi.

## Compilation

Environnement de validation : Linux, GCC 14.2.0, GNU Make 4.4.1.
Clang n’est pas installé ; sa compatibilité n’est donc pas revendiquée comme
testée. La compilation initiale a utilisé GCC via le remplacement de `CC`
et un répertoire extérieur au checkout pour ne pas écraser les binaires suivis.

La nouvelle compilation utilise :

```sh
make clean
make -j2 all variants
make smoke
make test
```

Les neuf exécutables principaux et les dix variantes compilent. Le lien des
variantes inclut désormais l’observateur requis par l’environnement. Les modules
sans `main` ne sont plus annoncés comme des exécutables autonomes.
Les avertissements préexistants de `test_terrain`, `observateur`, `observateur2`
et `curiosity-perf` restent visibles. Les changements de headers déclenchent la
recompilation via les fichiers `.d` ; une compilation à jour ne refait pas
inutilement le travail.

## Résultats

`make smoke` : **12 contrôles réussis, zéro échec**.
Il exécute `test1`, `test2`, `test4`, `chemin.test`, la simulation principale,
la lecture de terrain, les mouvements et rotations, le robot interactif,
les deux observateurs, la génération de trois terrains libres et trois
simulations reproductibles. Les résultats écrits sont vérifiés, pas uniquement
le code de retour. Les neuf programmes principaux sont ainsi exercés.

`make test` : **15 contrôles réussis, quatre échecs, un scénario exclu**.
Le processus Python retourne 1, et Make signale une erreur. Les quatre échecs
ne sont ni désactivés ni convertis en succès attendus dans la suite étendue.

| Scénario d’origine | Résultat observé avant et après réorganisation |
| --- | --- |
| `test1.txt` | `OK` : sortie du terrain |
| `test2.txt` | `OK` : eau |
| `test3.txt` | Rejet des coordonnées attendues (3,4), position réelle (3,2) ; cas négatif |
| `test4.txt` | `OK` : programme terminé en (3,2), orientation sud |
| `test5.txt` | Échec : `DA` entre dans l’eau, alors que `O` attend un rocher |
| `test6.txt` | Échec : après deux instructions `AG`, robot encore dans le terrain ; `S` attend une sortie |
| `test7.txt` | Échec : programme terminé en (9,4), orienté est, sans sortie ; `S` attend une sortie |
| `test8.txt` | Échec : `AGAA` sort du terrain, alors que `O` attend un rocher |
| `test9.txt` | Coordonnées/orientation absentes après `F`, lectures non contrôlées ; comportement indéfini |
| `test10.txt` | Rejet : erreur terrain, code 1 ; fichier de terrain absent du scénario |
| `test11.txt` | Rejet : erreur programme, code 2 ; fichier programme absent du scénario |
| `chemin.test` | `OK` : arrêt après neuf pas en (9,4), orientation est |

`test9` a été exécuté ponctuellement avant et après déplacement : dans cette
instance il a affiché une position incorrecte avec code zéro. Ce résultat ne
peut pas être une référence déterministe, puisque des variables non initialisées
sont lues. Le lanceur reproductible l’affiche explicitement comme exclu ; les
autres scénarios malformés sont testés avec leurs erreurs observables.

## Comparaison avant/après

Onze scénarios déterministes de l’interprète principal (tous sauf `test9`) et
quatre scénarios (`test1`, `test2`, `test4`, `chemin.test`) pour chacune des dix
variantes ont été exécutés avec les binaires reconstruits de l’ancienne et de
la nouvelle organisation : **51 sorties standard, sorties d’erreur et codes
de retour strictement identiques**. La variante 6 échoue toujours sur le scénario
d’eau, conformément à son échange des résultats eau/rocher. Cela vérifie la
préservation des comportements exercés, pas la correction de chaque variante
pour toutes les instructions.

## Portée

Les scripts de vérification sont nouveaux ; ils rendent les tests historiques
automatisables sans changer le runner C. `make smoke` est un contrôle représentatif
et ne remplace pas `make test`. Les paramètres choisis pour la génération
évitent les problèmes de terminaison aux fortes densités ; les valeurs limites,
la sûreté mémoire et les longs programmes ne sont pas validés exhaustivement.
La compilation avec warnings et les défauts décrits dans [l’analyse](architecture.md)
doivent être traités séparément avant de promettre un logiciel robuste.

Les changements restent sur la branche de travail pour revue. Ni fusion,
publication GitHub, ni réécriture d’historique n’a été effectuée.
