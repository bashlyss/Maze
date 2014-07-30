# Project: Maze
# Makefile created by Dev-C++ 4.9.9.2

CPP  = g++ 
CC   = gcc

OBJ  = Main.o Character.o WeaponProperties.o Weapon.o Gun.o AbstractGun.o AbstractGunDecorator.o WideShot.o ExplodingShot.o Grenade.o Bomb.o Nuke.o WallBreaker.o Player.o StandardEnemy.o Map.o Input.o Interaction.o EnemyWeapon.o Display.o Game.o Enemy.o EnemyFactory.o FloatingEnemy.o ShootingEnemy.o SurvivalGame.o Button.o ButtonManager.o Menu.o
DEPENDS = ${OBJ:.o=.d}
LIBS =  `pkg-config --libs allegro-5.0`

DEBUGFLAGS = -g -ggdb3
BIN  = Maze
CXXFLAGS = -O3 $(DEBUGFLAGS) ${LIBS}
RM = rm -f

.PHONY: all clean

all: Maze

clean:
	${RM} $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CPP) $(OBJ) ${CXXFLAGS} -o Maze

