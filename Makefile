all: main clean
main: Manager.o GamingField.o Ship.o Errors.o DoubleAttack.o Locator.o Bombing.o AbilitiesManager.o main.o
	g++ Ship.o Errors.o DoubleAttack.o Locator.o Bombing.o AbilitiesManager.o GamingField.o Manager.o main.o -o main
Errors.o: Errors.cpp Errors.h
	g++ -c Errors.cpp
Ship.o: Ship.cpp Ship.h
	g++ -c Ship.cpp
GamingField.o: GamingField.h GamingField.cpp Ship.h
	g++ -c GamingField.cpp
main.o: main.cpp Manager.h GamingField.h AbilitiesManager.h
	g++ -c main.cpp
Manager.o: Manager.cpp Manager.h Ship.h
	g++ -c Manager.cpp
DoubleAttack.o:  DoubleAttack.h DoubleAttack.cpp
	g++ -c DoubleAttack.cpp
Locator.o: Locator.cpp Locator.h
	g++ -c Locator.cpp
Bombing.o: Bombing.cpp Bombing.h
	g++ -c Bombing.cpp
AbilitiesManager.o: AbilitiesManager.cpp AbilitiesManager.h
	g++ -c AbilitiesManager.cpp
clean:
	rm -rf *.o