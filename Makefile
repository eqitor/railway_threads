railway_threads: main.o Passenger.o Station.o Train.o TicketBooth.o Map.o
	g++ main.o Passenger.o Station.o Train.o TicketBooth.o Map.o -o railway_threads -pthread -lncurses

main.o: main.cpp
	g++ -c main.cpp -pthread -lncurses

Station.o: Station.cpp
	g++ -c Station.cpp -lncurses

Passenger.o: Passenger.cpp
	g++ -c Passenger.cpp -pthread -lncurses

Train.o: Train.cpp
	g++ -c Train.cpp -lncurses -pthread

TicketBooth.o: TicketBooth.cpp
	g++ -c TicketBooth.cpp -lncurses

Map.o: Map.cpp
	g++ -c Map.cpp -pthread


clean:
	rm *.o railway_threads
