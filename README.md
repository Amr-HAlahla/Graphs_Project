# Dijkstra's Algorithm Implementation in C

## Description

This C program implements Dijkstra's algorithm to find the shortest path in a weighted graph. It provides functionalities to load cities from a file, compute the shortest path from a given source city, print the full route of the shortest path including the distance between each two cities and the total shortest cost, and save the information of the shortest path to a file.

## Features

- **Load Cities**: Load cities from a file and construct the graph with weights representing distances between cities.
- **Compute Shortest Path**: Enter a source city and compute the shortest path using Dijkstra's algorithm.
- **Print Full Route**: Enter a destination city and print the full route of the shortest path including distances between each pair of cities.
- **Save Shortest Path**: Save the information of the shortest path to a file named `shortest_path.txt` and exit the program.

## Usage

1. **Load Cities**: Choose option 1 to load cities from the file `cities.txt` and construct the graph.
2. **Enter Source City**: Choose option 2 to enter a source city and compute the shortest path from that city.
3. **Enter Destination City**: Choose option 3 to enter a destination city and print the full route of the shortest path from the previously selected source city to the destination.
4. **Save Shortest Path and Exit**: Choose option 4 to save the information of the shortest path to a file named `shortest_path.txt` and exit the program.

## Input File Format

The input file `cities.txt` should contain data in the following format:

```
source_city destination_city distance
```

Example:
```
New_York Los_Angeles 3000
```

## Compilation

Compile the program using any C compiler. For example, using GCC:

```
gcc -o dijkstra main.c
```

## Execution

Execute the compiled program:

```
./dijkstra
```

Follow the on-screen prompts to interact with the program.

## Dependencies

- Standard C libraries: `stdio.h`, `string.h`, `stdlib.h`


## Notes

- Ensure that the input file `cities.txt` is present in the same directory as the executable.
