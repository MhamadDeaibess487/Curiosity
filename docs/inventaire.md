# Inventaire des fichiers d’origine

Chaque source, header et donnée déplacés a été conservé sans changement de contenu.
Les regroupements ci-dessous couvrent tous les fichiers initialement suivis.

| Ancien chemin | Nouveau chemin | Rôle |
| --- | --- | --- |
| `chemin.test` | `tests/fixtures/chemin.test` | Scénario du runner C ; voir le bilan de validation. |
| `correcte_accepte.txt` | `tests/fixtures/correcte_accepte.txt` | Programme du langage à pile (exemple ou donnée d’observation/expérimentation). |
| `correcte_accepte2.txt` | `tests/fixtures/correcte_accepte2.txt` | Programme du langage à pile (exemple ou donnée d’observation/expérimentation). |
| `correcte_non_accept.txt` | `tests/fixtures/correcte_non_accept.txt` | Programme du langage à pile (exemple ou donnée d’observation/expérimentation). |
| `correcte_non_accept2.txt` | `tests/fixtures/correcte_non_accept2.txt` | Programme du langage à pile (exemple ou donnée d’observation/expérimentation). |
| `curiosity-obs.c` | `apps/curiosity-obs.c` | CLI de validation de la propriété de l’observateur principal. |
| `curiosity-obs2.c` | `apps/curiosity-obs2.c` | CLI de validation de la propriété de l’observateur alternatif. |
| `curiosity-perf.c` | `apps/curiosity-perf.c` | CLI d’expérimentation sur plusieurs terrains, graine et statistiques. |
| `curiosity-test.c` | `tests/curiosity-test.c` | Runner C des scénarios terrain/programme/limite/résultat. |
| `curiosity.c` | `apps/curiosity.c` | CLI de simulation avec affichage à chaque instruction. |
| `environnement.c` | `src/environnement.c` | Intégration robot/terrain et observation après mesure devant. |
| `environnement.h` | `include/environnement.h` | Interface et types : Intégration robot/terrain et observation après mesure devant. |
| `environnement_alt.c` | `src/environnement_alt.c` | Même environnement avec observation après mesure à gauche. |
| `generation_terrains.c` | `src/generation_terrains.c` | Génération aléatoire et recherche de chemin vers un bord. |
| `generation_terrains.h` | `include/generation_terrains.h` | Interface et types : Génération aléatoire et recherche de chemin vers un bord. |
| `impossible_a_tester.txt` | `docs/archives/impossible_a_tester.txt` | Note pédagogique originale, conservée comme archive (affirmations à confronter au code). |
| `incorrecte_accepte.txt` | `tests/fixtures/incorrecte_accepte.txt` | Programme du langage à pile (exemple ou donnée d’observation/expérimentation). |
| `incorrecte_accepte2.txt` | `tests/fixtures/incorrecte_accepte2.txt` | Programme du langage à pile (exemple ou donnée d’observation/expérimentation). |
| `incorrecte_non_accepte.txt` | `tests/fixtures/incorrecte_non_accepte.txt` | Programme du langage à pile (exemple ou donnée d’observation/expérimentation). |
| `incorrecte_non_accepte2.txt` | `tests/fixtures/incorrecte_non_accepte2.txt` | Programme du langage à pile (exemple ou donnée d’observation/expérimentation). |
| `interprete.c` | `src/interprete.c` | Interprétation pas à pas avec deux piles et compteur de programme. |
| `interprete.h` | `include/interprete.h` | Interface et types : Interprétation pas à pas avec deux piles et compteur de programme. |
| `interprete0.c` | `src/variants/interprete0.c` | Duplication supplémentaire pour C. |
| `interprete1.c` | `src/variants/interprete1.c` | Équivalent au principal. |
| `interprete2.c` | `src/variants/interprete2.c` | Échange X neutralisé. |
| `interprete3.c` | `src/variants/interprete3.c` | Direction de mesure modulo 8. |
| `interprete4.c` | `src/variants/interprete4.c` | Branche fausse remplacée par la vraie. |
| `interprete5.c` | `src/variants/interprete5.c` | Adresse de bloc empilée deux fois. |
| `interprete6.c` | `src/variants/interprete6.c` | Eau et rocher échangés. |
| `interprete7.c` | `src/variants/interprete7.c` | Équivalent au principal. |
| `interprete8.c` | `src/variants/interprete8.c` | Boucle exécutée pour compteur zéro. |
| `interprete9.c` | `src/variants/interprete9.c` | Ordre de soustraction inversé. |
| `observateur.c` | `src/observateur.c` | Automate contrôlant la mesure avant avancement. |
| `observateur.h` | `include/observateur.h` | Interface et types : Automate contrôlant la mesure avant avancement. |
| `observateur2.c` | `src/observateur2.c` | Automate contrôlant la mesure avant rotation gauche. |
| `programme.c` | `src/programme.c` | Lecture du langage, commandes et appariement des blocs. |
| `programme.h` | `include/programme.h` | Interface et types : Lecture du langage, commandes et appariement des blocs. |
| `programme2_test_perf.txt` | `tests/fixtures/programme2_test_perf.txt` | Programme du langage à pile (exemple ou donnée d’observation/expérimentation). |
| `programme_obs.txt` | `tests/fixtures/programme_obs.txt` | Programme du langage à pile (exemple ou donnée d’observation/expérimentation). |
| `programme_test_perf.txt` | `tests/fixtures/programme_test_perf.txt` | Programme du langage à pile (exemple ou donnée d’observation/expérimentation). |
| `qui_test_quoi.txt` | `docs/archives/qui_test_quoi.txt` | Note pédagogique originale, conservée comme archive (affirmations à confronter au code). |
| `robot.c` | `src/robot.c` | Géométrie du robot : position, orientation, rotations et avance. |
| `robot.h` | `include/robot.h` | Interface et types : Géométrie du robot : position, orientation, rotations et avance. |
| `robot_terrain.c` | `apps/robot_terrain.c` | Pilotage interactif avec contrôle des cases libres. |
| `simple.prg` | `tests/fixtures/simple.prg` | Programme du langage à pile (exemple ou donnée d’observation/expérimentation). |
| `simple1.prg` | `tests/fixtures/simple1.prg` | Programme du langage à pile (exemple ou donnée d’observation/expérimentation). |
| `simple2.prg` | `tests/fixtures/simple2.prg` | Programme du langage à pile (exemple ou donnée d’observation/expérimentation). |
| `simple3.prg` | `tests/fixtures/simple3.prg` | Programme du langage à pile (exemple ou donnée d’observation/expérimentation). |
| `simple5.prg` | `tests/fixtures/simple5.prg` | Programme du langage à pile (exemple ou donnée d’observation/expérimentation). |
| `simple6.prg` | `tests/fixtures/simple6.prg` | Programme du langage à pile (exemple ou donnée d’observation/expérimentation). |
| `simple7.prg` | `tests/fixtures/simple7.prg` | Programme du langage à pile (exemple ou donnée d’observation/expérimentation). |
| `simple8.prg` | `tests/fixtures/simple8.prg` | Programme du langage à pile (exemple ou donnée d’observation/expérimentation). |
| `terrain.c` | `src/terrain.c` | Lecture, affichage et écriture des grilles ; accès aux cases libres. |
| `terrain.h` | `include/terrain.h` | Interface et types : Lecture, affichage et écriture des grilles ; accès aux cases libres. |
| `terrain_1.txt` | `tests/fixtures/terrain_1.txt` | Terrain d’entrée de simulation ou d’observation. |
| `terrain_11x9.txt` | `tests/fixtures/terrain_11x9.txt` | Terrain d’entrée de simulation ou d’observation. |
| `terrain_2.txt` | `tests/fixtures/terrain_2.txt` | Terrain d’entrée de simulation ou d’observation. |
| `terrain_3.txt` | `tests/fixtures/terrain_3.txt` | Terrain d’entrée de simulation ou d’observation. |
| `terrain_5.txt` | `tests/fixtures/terrain_5.txt` | Terrain d’entrée de simulation ou d’observation. |
| `terrain_6.txt` | `tests/fixtures/terrain_6.txt` | Terrain d’entrée de simulation ou d’observation. |
| `terrain_7.txt` | `tests/fixtures/terrain_7.txt` | Terrain d’entrée de simulation ou d’observation. |
| `terrain_8.txt` | `tests/fixtures/terrain_8.txt` | Terrain d’entrée de simulation ou d’observation. |
| `terrain_correcte_non_accept.txt` | `tests/fixtures/terrain_correcte_non_accept.txt` | Terrain d’entrée de simulation ou d’observation. |
| `terrain_correcte_non_accept2.txt` | `tests/fixtures/terrain_correcte_non_accept2.txt` | Terrain d’entrée de simulation ou d’observation. |
| `terrain_echec.txt` | `docs/archives/terrain_echec.txt` | Grilles commentées et notes d’expérimentation ; pas un fichier terrain d’entrée complet. |
| `terrain_echec2.txt` | `docs/archives/terrain_echec2.txt` | Grilles commentées et notes d’expérimentation ; pas un fichier terrain d’entrée complet. |
| `terrain_incorrecte_accepte.txt` | `tests/fixtures/terrain_incorrecte_accepte.txt` | Terrain d’entrée de simulation ou d’observation. |
| `terrain_incorrecte_accepte2.txt` | `tests/fixtures/terrain_incorrecte_accepte2.txt` | Terrain d’entrée de simulation ou d’observation. |
| `terrain_incorrecte_non_accepte.txt` | `tests/fixtures/terrain_incorrecte_non_accepte.txt` | Terrain d’entrée de simulation ou d’observation. |
| `terrain_incorrecte_non_accepte2.txt` | `tests/fixtures/terrain_incorrecte_non_accepte2.txt` | Terrain d’entrée de simulation ou d’observation. |
| `terrain_reussi.txt` | `docs/archives/terrain_reussi.txt` | Grilles commentées et notes d’expérimentation ; pas un fichier terrain d’entrée complet. |
| `terrain_reussi2.txt` | `docs/archives/terrain_reussi2.txt` | Grilles commentées et notes d’expérimentation ; pas un fichier terrain d’entrée complet. |
| `terrainctually.txt` | `tests/fixtures/terrainctually.txt` | Terrain d’entrée de simulation ou d’observation. |
| `test1.txt` | `tests/fixtures/test1.txt` | Scénario du runner C ; voir le bilan de validation. |
| `test10.txt` | `tests/fixtures/test10.txt` | Scénario du runner C ; voir le bilan de validation. |
| `test11.txt` | `tests/fixtures/test11.txt` | Scénario du runner C ; voir le bilan de validation. |
| `test2.txt` | `tests/fixtures/test2.txt` | Scénario du runner C ; voir le bilan de validation. |
| `test3.txt` | `tests/fixtures/test3.txt` | Scénario du runner C ; voir le bilan de validation. |
| `test4.txt` | `tests/fixtures/test4.txt` | Scénario du runner C ; voir le bilan de validation. |
| `test5.txt` | `tests/fixtures/test5.txt` | Scénario du runner C ; voir le bilan de validation. |
| `test6.txt` | `tests/fixtures/test6.txt` | Scénario du runner C ; voir le bilan de validation. |
| `test7.txt` | `tests/fixtures/test7.txt` | Scénario du runner C ; voir le bilan de validation. |
| `test8.txt` | `tests/fixtures/test8.txt` | Scénario du runner C ; voir le bilan de validation. |
| `test9.txt` | `tests/fixtures/test9.txt` | Scénario du runner C ; voir le bilan de validation. |
| `test_generation_terrains.c` | `tests/test_generation_terrains.c` | Outil de génération, filtrage par chemin et rapport. |
| `test_robot.c` | `tests/test_robot.c` | Outil interactif de manipulation du robot sans grille. |
| `test_terrain.c` | `tests/test_terrain.c` | Outil de lecture et affichage de terrain. |
| `type_pile.c` | `src/type_pile.c` | Pile d’entiers dans un tableau fixe. |
| `type_pile.h` | `include/type_pile.h` | Interface et types : Pile d’entiers dans un tableau fixe. |
| `curiosity` | `build/bin/curiosity` (généré) | Ancien binaire retiré du suivi Git, conservé localement ; recompilation depuis les sources. |
| `curiosity-perf` | `build/bin/curiosity-perf` (généré) | Ancien binaire retiré du suivi Git, conservé localement ; recompilation depuis les sources. |
| `curiosity-test` | `build/bin/curiosity-test` (généré) | Ancien binaire retiré du suivi Git, conservé localement ; recompilation depuis les sources. |
| `curiosity-obs` | `build/bin/curiosity-obs` (généré) | Ancien binaire retiré du suivi Git, conservé localement ; recompilation depuis les sources. |
| `curiosity-obs2` | `build/bin/curiosity-obs2` (généré) | Ancien binaire retiré du suivi Git, conservé localement ; recompilation depuis les sources. |
| `robot_terrain` | `build/bin/robot_terrain` (généré) | Ancien binaire retiré du suivi Git, conservé localement ; recompilation depuis les sources. |
| `test_robot` | `build/bin/test_robot` (généré) | Ancien binaire retiré du suivi Git, conservé localement ; recompilation depuis les sources. |
| `test_terrain` | `build/bin/test_terrain` (généré) | Ancien binaire retiré du suivi Git, conservé localement ; recompilation depuis les sources. |
| `test_generation_terrains` | `build/bin/test_generation_terrains` (généré) | Ancien binaire retiré du suivi Git, conservé localement ; recompilation depuis les sources. |
| `fichier_res.txt` | Local, ignoré | Rapport de sortie généré retiré du suivi Git, contenu conservé localement. |
| `fichier_res_aleatoire.txt` | Local, ignoré | Rapport de sortie généré retiré du suivi Git, contenu conservé localement. |
| `Makefile` | `Makefile` | Règles remplacées pour objets dans build/, headers dans include/ et variantes liées à leur observateur. |
| `.gitignore` | `.gitignore` | Ignore les produits de compilation et anciens artefacts ; ne cache plus les sources ni le Makefile. |
| `README.md` | `README.md` | Présentation réécrite à partir du code et des exécutions réelles. |

## Nouveaux fichiers

- `tests/run_tests.py` : assertions sur les sorties, délais et codes de retour des outils existants.
- `docs/architecture.md` : architecture, langage, variantes et défauts existants.
- `docs/validation.md` : commandes vérifiées, résultats et limites.
- `docs/inventaire.md` : cet inventaire.

Les objets `*.o` étaient déjà ignorés et aucun n’était suivi dans le dépôt initial.
Le retrait du suivi des artefacts ne réécrit pas l’historique Git.
