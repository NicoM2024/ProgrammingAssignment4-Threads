//
// Created by Kentd on 10/30/2026.
//

#include "findstrings.kschne11-nlmilazz.h"

#include <stdio.h>

char buffer[BUFLEN]; //GLOBAL VARIABLE


int readFile(char *filename, int *numChars) {
    FILE *fp = fopen(filename, "r"); // filename is the char* passed to your readFile() function
    if (fp == NULL) {
        printf("ERROR: cannot open file '%s'\n", filename);
        return 8;
    }
    // now you can read from the file
}

int main(int argc, char *argv[]) {
    int rc, numChars;
    if (argc < 2) {
        printf("ERROR: need a filename\n");
        return 8;
    }
    rc = readFile(argv[1], &numChars);
    if (rc != 0)
        return 8;
    // prompt the user for the string to search for, using PROMPT
    // create the threads
    // wait for the threads to finish
    // summarize the results from the threads
    return 0;
}