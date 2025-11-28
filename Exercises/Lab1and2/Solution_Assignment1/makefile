CC = g++
FLAGS = -std=c++20 -w

TARGET = AnalyseData
OBJECTS = AnalyseData.o CustomFunction.o

all: $(TARGET)
 
$(TARGET): $(OBJECTS)
	$(CC) $(FLAGS) $(OBJECTS) -o $(TARGET)
	     
AnalyseData.o: AnalyseData.cpp CustomFunction.h
	$(CC) $(FLAGS) -c AnalyseData.cpp

CustomFunction.o: CustomFunction.cpp CustomFunction.h
	$(CC) $(FLAGS) -c CustomFunction.cpp

clean:
	rm -f *.o *~

cleantarget:
	rm -f $(TARGET)

