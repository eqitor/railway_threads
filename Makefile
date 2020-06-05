railway_threads: main.o Passenger.o Station.o Train.o TicketBooth.o Map.o SynchIO.o RandomIntGenerator.o
	g++ -g main.o Passenger.o Station.o Train.o TicketBooth.o Map.o SynchIO.o RandomIntGenerator.o -o railway_threads -pthread -lncurses

main.o: main.cpp
	g++ -g -c main.cpp -pthread -lncurses

Station.o: Station.cpp
	g++ -g -c Station.cpp -lncurses

Passenger.o: Passenger.cpp
	g++ -g -c Passenger.cpp -pthread -lncurses

Train.o: Train.cpp
	g++ -g -c Train.cpp -lncurses -pthread

TicketBooth.o: TicketBooth.cpp
	g++ -g -c TicketBooth.cpp -lncurses

Map.o: Map.cpp
	g++ -g -c Map.cpp -pthread -lncurses

SynchIO.o: SynchIO.cpp
	g++ -g -c SynchIO.cpp -pthread

RandomIntGenerator.o: RandomIntGenerator.cpp
	g++ -g -c RandomIntGenerator.cpp




clean:
	rm *.o railway_threads
