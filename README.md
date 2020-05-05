# railway_threads
# ZASOBY:
## kasa biletowa
jest ich kilka, pasażerowie bez biletu ustawiają sie w kolejce w celu zakupu biletu, jeśli są jeszcze bilety to są sprzedawane pasażerowi, jeśli nie
			to pasażrer wraca z pustymi rękami. Może mieć stan wolna, zajęta. Ilość: kilka (ok. 3 na stację)
## pociąg
 rozwozi pasażerów między stacjami, jego pojemność jest równa liczbie biletów możliwych do sprzedania na jeden kurs pociągu. Ma on stałą trasę przejazdu między
		stacjami. Pasażerowie znają trasę pociągu tj. pasażer nie wsiądzie do pociągu który nie jedzie na jego stację. Pociąg stoi na stacji przez pewien czas
		i czeka na chętnych pasażerów. Stany: stoi na stacji, jedzie, czeka przed
		semaforem (czeka na wolną stację). Ilość: kilka
## stacja
zawiera unikalne kasy biletowe wydające bilety. Na nich znajdują się pasażerowie czekający na pociąg. Na stacji może znajdować się w jednym momencie tylko jeden
		pociąg. Stany: wolna, zajęta. Ilość: kilka

# WĄTKI:
## pasażer
 pasażer po utworzeniu ma obrany konkretny cel (stację). Ustawia się przy kasie biletowej po zakup biletu. Jeśli kupił bilet to czeka na pociąg, jeśli nie to 
		czeka jakiś czas i próbuje ponownie. Gdy pojawi się jego pociąg to do niego wsiada. Wysiada na swojej stacji po czym czeka jakiś czas a następnie
		obiera nowy cel podróży - cykl się powtarza. Stany: czeka, czeka w kolejce po bilet, czeka na pociąg, podróżuje. Ilość: kilkadziesiąt
## pociąg
 w kontekscie stacji będzie musiał funkcjonować jako wątek czekający na wjazd do stacji i konkurujący o to z innymi pociągami

## Dodatkowe informacje:
Pasażer przy kasie biletowej sprawdza którym pociągiem dojedzie do celu. Ilość biletów pociągu jest globalna tj. kasy biletowe na każdej stacji mają informację o ilości biletów
dostępnych w danej chwili dla danego pociągu. Ilość dostępnych biletów będzie aktualizowana w momencie zmiany ilości pasażerów będących aktualnie w pociągu.