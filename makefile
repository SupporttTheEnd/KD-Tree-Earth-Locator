CXX = g++
CXXFLAGS = -Wall

# make t is to make the test
# make d is to make the driver
# make clean is to remove .o and copies
# make v is to use valgrind
# make r is to make run
# make b is to use the de-bugger

d: driver.cpp geolocate.o 
	$(CXX) $(CXXFLAGS) driver.cpp geolocate.o -o hw5
	
t: mytest.cpp geolocate.o 
	$(CXX) $(CXXFLAGS) mytest.cpp geolocate.o -o hw5

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
