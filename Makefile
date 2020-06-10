railway_threads: main.o Passenger.o Station.o Train.o TicketBooth.o Map.o SynchOut.o RandomIntGenerator.o GUI.o
	g++ -g main.o Passenger.o Station.o Train.o TicketBooth.o Map.o SynchOut.o RandomIntGenerator.o GUI.o -o railway_threads -pthread -lncurses -g

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
	g++ -g -c Map.cpp -pthread

SynchOut.o: SynchOut.cpp
	g++ -g -c SynchOut.cpp -pthread

RandomIntGenerator.o: RandomIntGenerator.cpp
	g++ -g -c RandomIntGenerator.cpp

GUI.o: GUI.cpp
	g++ -g -c GUI.cpp


clean:
	rm *.o railway_threads
