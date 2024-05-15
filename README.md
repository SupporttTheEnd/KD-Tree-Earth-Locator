# Geolocation KD-Tree Implementation

## Overview
This repository contains the implementation of a KD-Tree data structure for geolocation purposes. The KD-Tree is used to efficiently search for nearest neighbors based on latitude and longitude coordinates.

## Files
- `geolocate.h` and `geolocate.cpp`: These files contain the implementation of the KDTree class, which includes methods for inserting points, finding the nearest neighbor, and dumping the contents of the tree.
- `mytest.cpp`: This file contains the main function for testing the functionality of the KD-Tree implementation.
- `Makefile`: Contains instructions for compiling the project.

## How to Use
1. Include `geolocate.h` in your C++ project.
2. Create instances of the `KDTree` class to manage geolocation data.
3. Use the `insert` method to insert new points into the KD-Tree.
4. Utilize the `nearest` method to find the nearest neighbor to a given point.
5. Optionally, use the `dump` method to output the contents of the KD-Tree.
6. Compile the project using the provided Makefile instructions.

## Compilation
To compile the project, you can use the provided Makefile. Use the following commands:
- `make p`: Compiles `mytest.cpp` with `geolocate.o` to create an executable named `hw5`.
- `make d`: Compiles `driver.cpp` with `geolocate.o` to create an executable named `hw5`.
- `make b`: Runs `gdb` for debugging purposes.
- `make v`: Runs `valgrind` to check for memory leaks.

## Cleaning Up
To clean up object files and executables, you can use:
- `make clean`: Removes object files and temporary files.
