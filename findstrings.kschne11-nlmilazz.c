//
// Created by Kentd on 10/30/2026.
//

#include "findstrings.kschne11-nlmilazz.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

#define LINELEN 1024
#define NUM_THREADS 2



char buffer[BUFLEN]; //GLOBAL VARIABLE

int readFile(char *filename, int *numChars) {
    char line[LINELEN];
    FILE *fp = fopen(filename, "r"); // filename is the char* passed to your readFile() function
    if (fp == NULL) {
        printf("ERROR: cannot open file '%s'\n", filename);
        return 8;
    }
    // now you can read from the file
    int total_length = 0;
    while (!feof(fp)) {
        //char *fgets(char *s, int size, FILE *fp);
        char *chp = fgets(line, LINELEN, fp);
        int len = strlen(line);
        if (line[len-1] == '\n') {
            line[len-1] = '\0';
            len = len - 1;
        }
        for (int i=0; i<len; i++) {
            if (isalpha(line[i])) {
                buffer[total_length] = tolower(line[i]);
                total_length += 1;
            }
        }
    }
    for (int i=0; i<total_length; i++) {
        printf("%c", buffer[i]);
    }
    return 0;
}

void *findStrings(void *param) {

}

int main(int argc, char *argv[]) {
    int rc, numChars;
    /*if (argc < 2) {
        printf("ERROR: need a filename\n");
        return 8;
    }*/
    //rc = readFile(argv[1], &numChars);
    rc = readFile("C:/Users/Kentd/CLionProjects/ProgrammingAssignment4-Threads/coyote.asc", &numChars);
    if (rc != 0)
        return 8;
    // prompt the user for the string to search for, using PROMPT
    // create the threads
    SearchInfo searchInfo[NUM_THREADS];
    pthread_t tid[NUM_THREADS];
    pthread_t threads[NUM_THREADS];

    char *prompt = "1";
    int partition_size = strlen(buffer) / NUM_THREADS;
    int start_index = 0;
    int num_found = 0;
    for (int i=0; i<NUM_THREADS; ++i) {
        searchInfo[i] = (SearchInfo){start_index, start_index + partition_size, prompt, num_found};
        threads[i] = pthread_create(&tid[i], NULL, findStrings, &searchInfo[i]);
        start_index = start_index + partition_size;
    }
    // wait for the threads to finish
    // summarize the results from the threads
    return 0;
}