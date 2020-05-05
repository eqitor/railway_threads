railway_threads: main.o Passenger.o Station.o Train.o TicketBooth.o
	g++ main.o Passenger.o Station.o Train.o TicketBooth.o -o railway_threads -pthread -lncurses

main.o: main.cpp
	g++ -c main.cpp -pthread -lncurses


Passenger.o: Passenger.cpp
	g++ -c Passenger.cpp -pthread -lncurses

Station.o: Station.cpp
	g++ -c Station.cpp -lncurses

Train.o: Train.cpp
	g++ -c Train.cpp -lncurses

TicketBooth.o: TicketBooth.cpp
	g++ -c TicketBooth.cpp -lncurses

clean:
	rm *.o railway_threads