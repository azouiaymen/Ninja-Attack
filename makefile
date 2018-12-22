EXEC_NAME_NORM = bin/Ninjattack
EXEC_NAME_TXT = bin/NinjattackTxt
EXEC_NAME_SANSSDL = bin/NinjattackSansSDL
OBJ_FILES_NORM = obj/Carte.o obj/Definition.o obj/DefinitionSDL.o obj/Entite.o obj/Hitbox.o obj/Jeu.o obj/main.o obj/Personnage/Personnage.o obj/Personnage/Hero.o obj/Personnage/Aigle.o obj/Personnage/Requin.o obj/Personnage/Tortue.o obj/Sort/Sort.o obj/Sort/Contact.o obj/Sort/Dash.o obj/Sort/DashHero.o obj/Sort/ShurikenShotGun.o obj/Sort/ShurikenTroisCoups.o obj/Sort/Tir.o obj/Sprite.o obj/winTxt.o 
OBJ_FILES_TXT = obj/Carte.o obj/Definition.o obj/DefinitionSDL.o obj/Entite.o obj/Hitbox.o obj/Jeu.o obj/mainText.o obj/Personnage/Personnage.o obj/Personnage/Hero.o obj/Personnage/Aigle.o obj/Personnage/Requin.o obj/Personnage/Tortue.o obj/Sort/Sort.o obj/Sort/Contact.o obj/Sort/Dash.o obj/Sort/DashHero.o obj/Sort/ShurikenShotGun.o obj/Sort/ShurikenTroisCoups.o obj/Sort/Tir.o obj/Sprite.o obj/winTxt.o 
OBJ_FILES_SANSSDL = obj/Carte.o obj/Definition.o obj/DefinitionSDL.o obj/Entite.o obj/Hitbox.o obj/Jeu.o obj/mainNonSDL.o obj/Personnage/Personnage.o obj/Personnage/Hero.o obj/Personnage/Aigle.o obj/Personnage/Requin.o obj/Personnage/Tortue.o obj/Sort/Sort.o obj/Sort/Contact.o obj/Sort/Dash.o obj/Sort/DashHero.o obj/Sort/ShurikenShotGun.o obj/Sort/ShurikenTroisCoups.o obj/Sort/Tir.o obj/Sprite.o obj/winTxt.o 

CC = g++
CFLAGS = -Wall -ggdb
INCLUDES = -I/usr/include -I/usr/include/SDL2
LIBS = -L/usr/lib -lm -lSDL2 -lSDL2_image -lSDL2_ttf

all: $(EXEC_NAME_NORM) $(EXEC_NAME_TXT) $(EXEC_NAME_SANSSDL)

sdl: $(EXEC_NAME_NORM)

txt: $(EXEC_NAME_TXT)

sanssdl: $(EXEC_NAME_SANSSDL)

$(EXEC_NAME_NORM): $(OBJ_FILES_NORM)
	$(CC) -o $(EXEC_NAME_NORM) $(OBJ_FILES_NORM) $(LIBS)

$(EXEC_NAME_TXT): $(OBJ_FILES_TXT)
	$(CC) -o $(EXEC_NAME_TXT) $(OBJ_FILES_TXT) $(LIBS)

$(EXEC_NAME_SANSSDL): $(OBJ_FILES_SANSSDL)
	$(CC) -o $(EXEC_NAME_SANSSDL) $(OBJ_FILES_SANSSDL) $(LIBS)
	
obj/%.o: src/%.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<
	
clean:
	rm -r obj/*/*.o obj/*.o
	
veryclean:
	rm -r obj/*/*.o obj/*.o $(EXEC_NAME_NORM) $(EXEC_NAME_TXT) $(EXEC_NAME_SANSSDL)

