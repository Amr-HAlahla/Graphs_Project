#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int INFINITY = 1000000;
int size = 0;

/* This code was written using C Lion.
 * Amr Halahla ,, 1200902
 * All requirements of the project have been prepared */

//find the minimum distance between nodes from the source
int minDistance(int distances[], int booleanArray[]) {
    // Initialize min value
    int min = INFINITY, min_index;
    for (int v = 0; v < size; v++)
        if (booleanArray[v] == -1 && distances[v] <= min)
            min = distances[v], min_index = v;
    return min_index;
}

// print the shortest path from source to all other destinations
void printPath(int shortestPath[], int j, char cities[size][20]) {
    // Base Case : If j is source
    if (shortestPath[j] == -1)
        return;
    printPath(shortestPath, shortestPath[j], cities);
    printf("%s  ", cities[j]);

}

//print the shortest path from source to a specific destination.
void printPath2(int shortestPath[], int j, char cities[size][20], int costs[size], char outputPath[120]) {
    if (shortestPath[j] == -1)
        return;
    printPath2(shortestPath, shortestPath[j], cities, costs, outputPath);
    printf("%d %s ", costs[j], cities[j]);
    char d[10];
    itoa(costs[j], d, 10);
    strcat(outputPath, "\t");
    strcat(outputPath, d);
    strcat(outputPath, "\t");
    strcat(outputPath, cities[j]);
    strcat(outputPath, "\t");
}

void printSolution(int dist[], int src, int shortestPAth[], char cities[size][20]) {
    printf("Vertex\t\t\t\t\t Distance\t\tPath");
    for (int i = 0; i < size; i++) {
        printf("\n%-10s-> %-10s \t\t %-5dKm\t\t%s ", cities[src], cities[i], dist[i], cities[src]);
        printPath(shortestPAth, i, cities);
    }
    printf("\n------------------------------------------------------\n");
}

void
printSolution2(int dist[], int src, int shortestPath[], int dest, char cities[size][20], int costs[size],
               char outputPath[120]) {

    printf("\n%-10s-> %-10s \t\t %-5dKm\t\t%s ", cities[src], cities[dest], dist[dest], cities[src]);
    strcat(outputPath, cities[src]);
    strcat(outputPath, "->");
    strcat(outputPath, cities[dest]);
    strcat(outputPath, "\t\t");
    char d[10];
    itoa(dist[dest], d, 10);
    strcat(outputPath, d);
    strcat(outputPath, "\t");
    strcat(outputPath, cities[src]);
    strcat(outputPath, "\t");
    printPath2(shortestPath, dest, cities, costs, outputPath);
}


void dijkstra(int graph[size][size], int src, char cities[size][20]) {
    // The output array. distances[i] will hold the shortest
    // distance from src to i
    int distances[size];

    /* booleanArray[i] will true if vertex i is included / in
     shortest path tree or shortest distance from src to i is finalized*/

    int booleanArray[size];
    for (int i = 0; i < size; ++i) {
        booleanArray[i] = -1;
    }

    // Parent array to store shortest path tree
    int shortestPath[size];
    for (int i = 0; i < size; ++i) {
        shortestPath[i] = -1;
    }

    // Initialize all distances as INFINITE and booleanArray[] as -1

    for (int i = 0; i < size; i++) {
        distances[i] = INFINITY;
    }

    // Distance of source vertex from itself is always 0
    distances[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < size - 1; count++) {
        // Pick the minimum distance vertex from the set of
        // vertices not yet processed. u is always equal to
        // src in first iteration.
        int u = minDistance(distances, booleanArray);
        // Mark the picked vertex as processed
        booleanArray[u] = 1;
        // Update distances value of the adjacent vertices of the
        // picked vertex.
        for (int v = 0; v < size; v++)
            // Update distances[v] only if is not in booleanArray,
            // there is an edge from u to v, and total
            // weight of path from src to v through u is
            // smaller than current value of distances[v]
            if (booleanArray[v] == -1 && graph[u][v]
                && distances[u] + graph[u][v] < distances[v]) {
                shortestPath[v] = u;
                distances[v] = distances[u] + graph[u][v];
            }
    }
    // print the constructed distance array
    printSolution(distances, src, shortestPath, cities);

}

void dijkstraWithDestination(int graph[size][size], int src, int dest, char cities[size][20], char outputPath[120]) {
    // The output array. distances[i] will hold the shortest
    // distance from src to i
    int distances[size];
    int pathCost[size];

    /* booleanArray[i] will true if vertex i is included / in
     shortest path tree or shortest distance from src to i is finalized*/
    int booleanArray[size];
    for (int i = 0; i < size; ++i) {
        booleanArray[i] = -1;
    }
    // Parent array to store shortest path tree
    int shortestPath[size];
    for (int i = 0; i < size; ++i) {
        shortestPath[i] = -1;
    }
    // Initialize all distances as INFINITE and stpSet[] as -1
    for (int i = 0; i < size; i++) {
        distances[i] = INFINITY;
    }
    // Distance of source vertex from itself is always 0
    distances[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < size - 1; count++) {
        // Pick the minimum distance vertex from the set of
        // vertices not yet processed. u is always equal to
        // src in first iteration.
        int u = minDistance(distances, booleanArray);
        // Mark the picked vertex as processed
        booleanArray[u] = 1;
        // Update distances value of the adjacent vertices of the
        // picked vertex.
        for (int v = 0; v < size; v++)
            // Update distances[v] only if is not in booleanArray,
            // there is an edge from u to v, and total
            // weight of path from src to v through u is
            // smaller than current value of distances[v]
            if (booleanArray[v] == -1 && graph[u][v]
                && distances[u] + graph[u][v] < distances[v]) {
                shortestPath[v] = u;
                distances[v] = distances[u] + graph[u][v];
                pathCost[v] = graph[u][v];
            }
    }
    // print the constructed distance array

    printSolution2(distances, src, shortestPath, dest, cities, pathCost, outputPath);

}

int main() {

    int counter = 0;
    int src = -1, indexDest = -1;
    FILE *file;
    file = fopen("cities.txt", "r");


    char output[50];
    if (file) {
        /* calculate number of cities in the file.*/
        while (fgets(output, sizeof(output), file)) {
            counter++;
        }
        fclose(file);
    } else {
        printf("Error In File\n");
        exit(10);
    }
    //update the value of size
    size = 2 * counter;
    char allCities[size][20]; /* array to store all cities from the file. */
    counter = 0;
    char temp[20], temp2[20];
    char tempData[50];
    file = fopen("cities.txt", "r");
    while (fgets(tempData, sizeof(tempData), file)) {
        sscanf(tempData, "%[^ ] %[^ ] %[^ ]", temp, temp2, NULL);
        //printf("%s     %s  \n", temp, temp2);
        strcpy(allCities[counter++], temp);
        strcpy(allCities[counter++], temp2);

    }
    fclose(file);
    printf("------------------------------\n");
    /* shift all duplicate cities and minimize the size of the array as same as number of unique cities */
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            // use if statement to check duplicate element
            if (strcmp(allCities[i], allCities[j]) == 0) {
                // delete the current position of the duplicate element
                for (int k = j; k < size - 1; k++) {
                    strcpy(allCities[k], allCities[k + 1]);
                }
                // decrease the size of array after removing duplicate element
                size--;

                // if the position of the elements is changes, don't increase the index j
                j--;
            }
        }
    }
    /* create and initialize the graph with zero value */
    int Graph[size][size];
    int row = 0, column = 0;
    char data[50];
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            Graph[i][j] = 0;
        }
    }

    char outputPath[120]; /* to store the shortest path with the costs between each cities */
    /* ----------------------------------*/

    int s;
    printf("select an option :\n");
    printf("1. Load cities: loads the file and construct the graph\n"
           "2. Enter source city: read the source city and compute the Dijkstra algorithm (single source shortest path)\n"
           "3. Enter destination city: print the full route of the shortest path including the distance between each two cities and the total shortest cost\n"
           "4. Exit: prints the information of step 3 to a file called shortest_path.txt and exits the program\n");
    scanf("%d", &s);
    while (s) {
        switch (s) {
            case 1: {
                /* read the file and create the graph and append the weight */
                file = fopen("cities.txt", "r");
                while (fgets(data, sizeof(data), file)) {
                    char source[20], dest[20], weight[10];
                    sscanf(data, "%[^ ] %[^ ] %[^ ]", source, dest, weight);
                    for (int i = 0; i < size; ++i) {
                        /* get the index of the source city */
                        if (strcmp(allCities[i], source) == 0) {
                            row = i;
                            break;
                        }
                    }
                    for (int i = 0; i < size; ++i) {
                        /* get hte index of the destination city */
                        if (strcmp(allCities[i], dest) == 0) {
                            column = i;
                            break;
                        }
                    }
                    /* store the weight in the graph*/
                    Graph[row][column] = strtol(weight, NULL, 10);
                }
                fclose(file);
                /* print the unique cities */
                for (int i = 0; i < size; ++i) {
                    printf("%d = %s\n", i, allCities[i]);
                }
                break;
            }
            case 2: {
                /* read the source city and get the index of it */
                char source[20], out;
                printf("Enter source city :\n");
                scanf("%c", &out);
                scanf("%s", source);
                /* search for the index of the source city */
                for (
                        int i = 0;
                        i < size;
                        ++i) {
                    if (
                            strcmp(allCities[i], source
                            ) == 0) {
                        src = i;
                        break;
                    }
                }
                if (src == -1) {
                    printf("The source city hasn't found\n");
                    exit(10);
                } else
                    dijkstra(Graph, src, allCities);
                break;
            }
            case 3: {
                /* read the destination */
                char dest[20], out;
                printf("Please enter destination city\n");
                scanf("%c", &out);
                scanf("%s", dest);
                /* search for the index of the destination */
                for (
                        int i = 0;
                        i < size;
                        ++i) {
                    if (
                            strcmp(allCities[i], dest
                            ) == 0) {
                        indexDest = i;
                        break;
                    }
                }
                if (indexDest != -1) {
                    printf("\nShortest path from %s to %s :\n", allCities[src], allCities[indexDest]);
                    printf("Vertex\t\t\t\t\t Distance\t\tPath");
                    dijkstraWithDestination(Graph, src, indexDest, allCities, outputPath);
                }
                printf("\n----------------------------------\n\n");
                break;
            }
            case 4: {
                FILE *outFile = fopen("shortest_path.txt", "w");
                if (!outFile) {//check if the file founded.
                    printf("File Not Found!\n");
                } else {
                    fprintf(outFile, "%s", outputPath);
                }
                fclose(outFile);
                printf("Done!\n");
                exit(111);

            }
            default: {
                printf("Please select only a number between 1-4\n");
            }

        }
        printf("select an option :\n");
        printf("1. Load cities: loads the file and construct the graph\n"
               "2. Enter source city: read the source city and compute the Dijkstra algorithm (single source shortest path)\n"
               "3. Enter destination city: print the full route of the shortest path including the distance between each two cities and the total shortest cost\n"
               "4. Exit: prints the information of step 3 to a file called shortest_path.txt and exits the program\n");
        scanf("%d", &s);
    }

    return 0;
}