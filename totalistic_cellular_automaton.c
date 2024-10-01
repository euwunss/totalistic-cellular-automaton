// Totalistic Cellular Automaton

// ----------------------------------------------------
// This Totalistic Cellular Automaton program evolves a world where
// each cell can exist in one of the three possible statuses: 0, 1, or 2.
// The future state of each cell is determined by the local sum of the statuses
// of its neighboring cells and its own status value.
// Depending on the local sum, the cell's status updates according to the the rule based 
// on a user-specified number in the 0 - 2186 range, leading to different patterns and behaviors over time.

// Course: CS 211, Fall 2024, UIC
// Author: Olha Lashchukevych
// ----------------------------------------------------

#include <stdio.h>
#include <stdbool.h>

const int WORLD_SIZE = 65;
const int ARRAY_SIZE = 7;

typedef struct cell_struct{
    int localSum; // total sum of local cells, [left] + [me] + [right]: possible values are 0-6
    int status;   // this cell's current status: 0, 1, or 2
    int count;    // running accumulated count of this cell's active status for all generations
} cell;

// function prototypes
bool isValid(int num);
void printValArray(int valArray[], int ruleNum);
void printEvolutionStep(int valArray[]);
void printGeneration(cell world[WORLD_SIZE], int statusSum);
void printEvolvedWorld(cell world[WORLD_SIZE], int valArray[], int numGenerations);

// Converts an integer rule number (0-2186) into its base-3 ternary represenation
// Number is stored in reverse order as an array of 7 status digits (0, 1, or 2)
// Each element of valArray represents base-3 digits of ruleNum
// Returns true if ruleNum is valid (0-2186)
// Returns false if ruleNum is out of the valid range
bool setValArray(int valArray[7], int ruleNum) {
    if (!isValid(ruleNum)) {
        return false;
    }

    for (int i = 0; i < 7; i++) {
        if (ruleNum == 0) {
            valArray[i] = 0;
            continue;
        }
        valArray[i] = ruleNum % 3;
        ruleNum /= 3;
    }
    return true;
}

// Updates the local sum for each element in the world array,
// using the status of the current cell along with its immediate neighbors [left, center, right].
// The array is treated as cyclic, meaning the first and last cells are adjacent to each other.
// This wrapping allows cells on the edges to interact with those on the opposite ends.
void setSums(cell world[WORLD_SIZE]) {
    for (int i = 1; i <= WORLD_SIZE - 1; i++) {
        world[i].localSum = world[i-1].status + world[i].status + world[i+1].status;
    }
    world[0].localSum = world[WORLD_SIZE-1].status + world[0].status + world[1].status;
    world[WORLD_SIZE-1].localSum = world[WORLD_SIZE-2].status + world[0].status + world[WORLD_SIZE-1].status;
    return;
}

// Updates the status of each cell in the world array based on a given set of rules
// and the current localSum of each cell. The ruleValArray maps each possible localSum
// (0-6) to a new status value for the cell. The function also increments the count
// of active states for each cell and accumulates the overall statusSum of the world.
// After updating all cells, it recalculates the local sums for the next iteration.
// Returns the total status sum of all cells after the update.
int evolveWorld(cell world[WORLD_SIZE], int ruleValArray[7]) {
    //TODO: Task 6 - write the evolveWorld() function
    int statusSum = 0;
    for (int i = 0; i < WORLD_SIZE; i++) {
        world[i].status = ruleValArray[world[i].localSum];
        world[i].count += world[i].status;
        statusSum += world[i].status;
    }
    setSums(world);
    return statusSum;
}

// check if a rule number input is in a valid range
bool isValid(int num) {
    if (num < 0 || num > 2186) {
        return false;
    }
    return true;
}

// Prompt user for a number in a range displaying message
// int min - minimum number in a range, int max - maximum number in a range
// char* message - message that keeps reappearing if user enters invalid number
// returns a user-specified number
int getUserNum(int min, int max, char* message) {
    int num;
    do {
        printf("\n%s", message);
        scanf("%d", &num);
    } while (num < min || num > max);
    return num;
}

// Prints a rule value array
// Rule value array stores a base-3 ternary number in a reverse order
// int valArray[] is a rule number array, int ruleNum - user-speified rule number
void printValArray(int valArray[], int ruleNum) {
    printf("\n\nThe value array for rule #%d is ", ruleNum);
    for (int i = ARRAY_SIZE - 1; i >= 0; i--) {
        printf("%d", valArray[i]);
    }
    printf("\n");
    return;
}

// Prints a status of the rule ternary number
// status 0: prints ' '
// status 1: prints '-'
// status 2: printf '+'
void printNewStatus(int valArray[]) {
    for (int i = ARRAY_SIZE - 1; i >= 0; i--) {
        char status;
        switch (valArray[i]) {
            case 0: status = ' '; break;
            case 1: status = '-'; break;
            case 2: status = '+'; break;
            default: break;
        }
        printf("|%c|     ", status);
    }
    printf("\n");
    return;
}

// Prints evolutionary step for a user-specified rule number status
void printEvolutionStep(int valArray[]) {
    printf("Local Sum:   6       5       4       3       2       1       0      \n");
    printf("States:    |+++|   |++-|   |++ |   |+- |   |-- |   |-  |   |   |    \n");
    printf("                   |+-+|   |+ +|   |+ -|   |- -|   | - |            \n");
    printf("                   |-++|   | ++|   |-+ |   | --|   |  -|            \n");
    printf("                           |+--|   | +-|   |+  |                    \n");
    printf("                           |-+-|   |- +|   | + |                    \n");
    printf("                           |--+|   | -+|   |  +|                    \n");
    printf("                                   |---|                            \n");
    printf("New Status: ");
    printNewStatus(valArray);
    return;
}

// Initializes world array of size WORLD_SIZE
// Sets status 0 for all cells except for the middle cell
// Middle cell's status is determined by user-specified initVal
// Prints the initialized first (0) generation
void initWorld(cell world[WORLD_SIZE], int initVal) {
    for (int i = 0; i < WORLD_SIZE; i++) {
        world[i].status = 0;
        world[i].count = world[i].status;
    }   
    world[WORLD_SIZE/2].status = initVal;
    world[WORLD_SIZE/2].count = initVal;
    setSums(world);

    printGeneration(world, initVal);
    return;
}

// Prints a generational chart based on cells' status values
// After chart prints the total sum of all cells' status values
// For status 0 prints ' ', for status 1 - '-', for status 2 - '+'
void printGeneration(cell world[WORLD_SIZE], int statusSum) {
    for (int i = 0; i < WORLD_SIZE; i++) {
        switch(world[i].status) {
            case 0: printf(" "); break;
            case 1: printf("-"); break;
            case 2: printf("+"); break;
        }
    }
    printf(" %d \n", statusSum);
    return;
}

// Prints the chart of the evolved world
// Calls printGeneration() numGenerations times, prints each generation,
// and calls evolveWorld() to evolve the world to the next generation
// cell world[WORLD_SIZE] - array of cells of WORLD_SIZE size
// int valArray[] - array holding a rule ternary number in reversed order
// int numGenerations - user-specified number of total number of generations
void printEvolvedWorld(cell world[WORLD_SIZE], int valArray[], int numGenerations) {
    for (int i = 0; i < numGenerations; i++) {
        int statusSum = evolveWorld(world, valArray);
        printGeneration(world, statusSum);
    }
    return;
}

// Prints the world cells' sums underneath the cells columns
// Since two-digit numbers wouldn't fit, such numbers are outputted vertically
// with the first digit in the second row, and the second digit in first row
// For total sums of zero, prints both digits as whitespaces.
void printCellSums(cell world[WORLD_SIZE]) {
    char buffer[WORLD_SIZE];
    for (int i = 0; i < WORLD_SIZE; i++) {
        if (world[i].count >= 10) {
            printf("%d", world[i].count / 10);
            buffer[i] = '0' + (world[i].count % 10);
        }
        else if (world[i].count > 0) {
            printf(" ");
            buffer[i] = '0' + world[i].count;
        }
        else {
            printf(" ");
            buffer[i] = ' ';
        }
    }
    printf("\n");
    for (int i = 0; i < WORLD_SIZE; i++) {
        printf("%c", buffer[i]);
    }
    return;
}

int main() {
    cell world[WORLD_SIZE];
    int valArray[ARRAY_SIZE];

    printf("Welcome to the Totalistic Cellular Automaton!");

    // Prompt user for a rule number and print the converted to ternary rule number stored in a rule value array
    int ruleNum = getUserNum(0, 2186, "Enter the rule # (0-2186): ");
    setValArray(valArray, ruleNum);
    printValArray(valArray, ruleNum);

    printf("\nThe evolution of all possible states are as follows:\n");
    
    // Print evolution step for the ternary rule number printing ' ' for status 0, '-' for status 1, and '+' for status 2 
    printEvolutionStep(valArray);

    // Prompt user for the number of generations to evolve
    int numGenerations = getUserNum(1, 49, "Enter the number of generations (1-49): ") - 1;

    // Prompt user to enter 1 or 2 initial active sell status
    int initCellVal = getUserNum(1, 2, "Enter the value (1 or 2) for the initial active cell: ");

    printf("\n\nInitializing world & evolving...\n");

    // Initialize world and set all cells' status values to 0 except for the initial active cell     
    initWorld(world, initCellVal);

    // Print the chart of the evolved world
    printEvolvedWorld(world, valArray, numGenerations);
    printf("_________________________________________________________________\n");

    // Print the total sum for each cell throughout all evolution steps vertically 
    printCellSums(world);
    printf("\n");

    return 0;
}