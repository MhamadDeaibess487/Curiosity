CC = cc
CFLAGS ?= -Wall
CPPFLAGS += -Iinclude
PYTHON ?= python3

PROGRAMMES := test_terrain test_robot robot_terrain curiosity curiosity-test \
              test_generation_terrains curiosity-perf curiosity-obs curiosity-obs2
VARIANTES := $(addprefix curiosity-test,0 1 2 3 4 5 6 7 8 9)
BASE := build/src/programme.o build/src/robot.o build/src/terrain.o build/src/type_pile.o
ENV := build/src/environnement.o build/src/observateur.o
CORE := $(BASE) $(ENV) build/src/interprete.o
GEN := build/src/generation_terrains.o

.PHONY: all variants clean test smoke $(PROGRAMMES) $(VARIANTES)
.SECONDARY:
all: $(addprefix build/bin/,$(PROGRAMMES))
variants: $(addprefix build/bin/,$(VARIANTES))
$(PROGRAMMES) $(VARIANTES): %: build/bin/%

build/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -MP -c $< -o $@

build/bin/test_terrain: build/tests/test_terrain.o build/src/terrain.o
build/bin/test_robot: build/tests/test_robot.o build/src/robot.o
build/bin/robot_terrain: build/apps/robot_terrain.o build/src/terrain.o build/src/robot.o
build/bin/curiosity: build/apps/curiosity.o $(CORE)
build/bin/curiosity-test: build/tests/curiosity-test.o $(CORE)
build/bin/test_generation_terrains: build/tests/test_generation_terrains.o $(GEN) build/src/terrain.o
build/bin/curiosity-perf: build/apps/curiosity-perf.o $(CORE) $(GEN)
build/bin/curiosity-obs: build/apps/curiosity-obs.o $(CORE) $(GEN)
build/bin/curiosity-obs2: build/apps/curiosity-obs2.o $(BASE) build/src/interprete.o \
                        build/src/environnement_alt.o build/src/observateur2.o $(GEN)

$(addprefix build/bin/,$(PROGRAMMES)):
	@mkdir -p $(@D)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

# Les variantes partagent l'environnement principal et son observateur.
build/bin/curiosity-test%: build/tests/curiosity-test.o build/src/variants/interprete%.o $(BASE) $(ENV)
	@mkdir -p $(@D)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

test: all
	$(PYTHON) tests/run_tests.py

smoke: all
	$(PYTHON) tests/run_tests.py --smoke

clean:
	rm -rf build

# Dépendances des headers, générées automatiquement par le compilateur.
-include $(wildcard build/src/*.d build/src/variants/*.d build/apps/*.d build/tests/*.d)
