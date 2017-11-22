CC=g++

FLAGS=-I. -I"./rapidjson/include/" -std=c++11 
CURFLAGS = $(FLAGS)

.PHONY: gatherer

# all:
# 	g++ $(FLAGS) mutlithread_reading.cpp StatAggregator.cpp StatElement.cpp StatGatherer.cpp  -o gatherer

gatherer: StatAggregator.o StatElement.o StatGatherer.o gatherer.o
	$(CC) -pthread -o gatherer   StatAggregator.o StatElement.o StatGatherer.o gatherer.o $(CURFLAGS)
	@echo ----------------------------
	@echo BUILD COMPLETE

StatAggregator.o: StatAggregator.cpp StatElement.o StatGatherer.o
	g++ -c -pthread -o StatAggregator.o StatAggregator.cpp $(CURFLAGS)

StatElement.o: StatElement.cpp
	g++ -c -pthread -o StatElement.o StatElement.cpp $(CURFLAGS)

StatGatherer.o: StatGatherer.cpp StatElement.o
	g++ -c -pthread -o StatGatherer.o StatGatherer.cpp $(CURFLAGS)

gatherer.o: mutlithread_reading.cpp
	g++ -c -pthread  mutlithread_reading.cpp $(CURFLAGS) -o gatherer.o

clear:
	rm -f *.o
	rm -f gatherer

verbal: CURFLAGS = -DVERBOSE $(FLAGS)
verbal: gatherer