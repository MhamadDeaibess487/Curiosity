#!/usr/bin/env python3
"""Vérifie les sorties des outils C existants sans modifier leurs algorithmes."""

import argparse
from pathlib import Path
import subprocess
import tempfile


ROOT = Path(__file__).resolve().parents[1]
BIN = ROOT / "build" / "bin"
FIXTURES = ROOT / "tests" / "fixtures"


def run(program, *args, stdin=""):
    return subprocess.run(
        [str(BIN / program), *map(str, args)], cwd=FIXTURES,
        input=stdin, capture_output=True, text=True, timeout=10,
    )


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--smoke", action="store_true", help="contrôles représentatifs uniquement")
    args = parser.parse_args()
    failures = []
    passed = 0

    def check(name, program, arguments, predicate, stdin=""):
        nonlocal passed
        try:
            result = run(program, *arguments, stdin=stdin)
            ok = predicate(result)
            detail = result.stdout.strip().splitlines()[-1:] + result.stderr.strip().splitlines()[-1:]
        except (OSError, subprocess.TimeoutExpired) as error:
            ok, detail = False, [str(error)]
        if ok:
            passed += 1
            print(f"PASS {name}")
        else:
            failures.append(name)
            print(f"FAIL {name}: {'; '.join(detail)}")

    def contains(text):
        return lambda r: r.returncode == 0 and text in r.stdout

    fixtures = ["test1.txt", "test2.txt", "test4.txt", "chemin.test"]
    if not args.smoke:
        fixtures += ["test5.txt", "test6.txt", "test7.txt", "test8.txt"]
    for fixture in fixtures:
        check(fixture, "curiosity-test", [fixture],
              lambda r: r.returncode == 0 and "OK" in r.stdout.splitlines())

    check("sortie du terrain", "curiosity", ["terrain_1.txt", "simple1.prg"], contains("Le robot est sorti :-)"))
    check("lecture du terrain", "test_terrain", ["terrain_1.txt"], contains("Position initiale du robot : (4, 2)"))
    check("déplacements et rotations", "test_robot", [], contains("Position : (1, -1) - Orientation : Est"), "a\ng\na\nd\nf\n")
    check("robot interactif sur terrain", "robot_terrain", ["terrain_1.txt"], contains("Position : (5, 1) - Orientation : Est"), "a\ng\na\nd\nf\n")
    check("observateur principal", "curiosity-obs", ["terrain_1.txt", "simple1.prg"], contains("Observateur : propriété fausse !"))
    check("observateur alternatif", "curiosity-obs2", ["terrain_1.txt", "simple1.prg"], contains("Observateur : propriété valide"))

    with tempfile.TemporaryDirectory(prefix="curiosity-tests-") as temp:
        generated = Path(temp) / "terrains.txt"
        results = Path(temp) / "performance.txt"
        check("génération de trois terrains libres", "test_generation_terrains", [3, 5, 5, 0, generated],
              lambda r: r.returncode == 0 and "le nb de reussi est 3" in r.stdout
              and generated.read_text().count("..C..") == 3
              and "100.000000" in generated.read_text())
        check("trois simulations reproductibles", "curiosity-perf", ["simple1.prg", 3, 5, 5, 0, 1, 20, results],
              lambda r: r.returncode == 0 and "Sorti avec succès : 3 (100.0%)" in r.stdout
              and results.read_text() == "3\n3\n3\n3\n")

    if not args.smoke:
        check("rejet des coordonnées incorrectes (test3)", "curiosity-test", ["test3.txt"],
              lambda r: r.returncode == 0 and "Position incorrecte" in r.stdout and "OK" not in r.stdout.splitlines())
        check("terrain manquant (test10)", "curiosity-test", ["test10.txt"],
              lambda r: r.returncode == 1 and "Erreur lecture du terrain" in r.stdout)
        check("programme manquant (test11)", "curiosity-test", ["test11.txt"],
              lambda r: r.returncode == 2 and "Erreur lecture du programme" in r.stdout)
        print("SKIP test9.txt : coordonnées absentes, variables non initialisées dans le runner C.")

    print(f"{passed} contrôles réussis, {len(failures)} échecs.")
    return bool(failures)


if __name__ == "__main__":
    raise SystemExit(main())
