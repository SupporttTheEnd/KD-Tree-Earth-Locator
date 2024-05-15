CXX = g++
CXXFLAGS = -Wall

p: mytest.cpp geolocate.o 
	$(CXX) $(CXXFLAGS) mytest.cpp geolocate.o -o hw5

d: driver.cpp geolocate.o 
	$(CXX) $(CXXFLAGS) driver.cpp geolocate.o -o hw5

geolocate.o: geolocate.h geolocate.cpp
	$(CXX) $(CXXFLAGS) -c geolocate.cpp

clean:
	rm *.o*
	rm *~ 

v:
	valgrind --leak-check=full --track-origins=yes ./hw5

r:
	./hw5

b:
	gdb ./hw5
