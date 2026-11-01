//
// Created by Kentd on 10/30/2026.
//

#include "findstrings.kschne11-nlmilazz.h"
#include <pthread.h>

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>

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
    while (fgets(line, LINELEN, fp) != NULL) {
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
    return 0;
}

void *findStrings(void *param) {

    SearchInfo *info = (SearchInfo *)param;
    char starting_char = info->pattern[0];

    // Create a list of different word branches. It is true that we can never be constructing a new word a number of
    // times greater than the pattern size, so there can only be that many branches or less, so that is the array size.
    SearchBranch branches[strlen(info->pattern)];

    for (int i = 0; i < strlen(info->pattern); i++){
        branches[i].offset = i;
        branches[i].current_index = 0;
        branches[i].matched_chars = 0;
        branches[i].expected_char_index = 0;
    }
    for (int i = info->startIndex; i < info->endIndex; i++) {
        bool passed = true;
        for (int j = 0; j < strlen(info->pattern); j++) {
            if (i + j <= strlen(buffer)) {
                if (buffer[i + j] != info->pattern[j]) {
                    passed = false;
                    break;
                }
            }
            else {
                passed = false;
                break;
            }
        }
        if (passed == true) {
            info->numFound++;
        }
    }
    /*
    int overall_index = info->startIndex;

    // Compare the current buffer character with the current local character
    // If they match:
    //  -> matched_chars increases
    //  -> If matched chars is large enough to mean that a whole word was found
    //     -> matched chars is reset, the current index (local) is reset to 0
    // Otherwise:
    //  -> reset the local current_index because that strain of characters failed to match the word

    printf("\nthread started");
    // printf("\nStart Index: %i. End Index: %i.", info->startIndex, info->endIndex);

    while (true){
        // For every branch, do the comparison and increments
        for (int i = 0; i < strlen(info->pattern); i++){

            // Keep track of the current character in the buffer
            // we offset by the branch offset to look for potentially overlapping words

            // THIS SYSTEM DOES NOT QUITE WORK BECAUSE BRANCHES EARLIER IN THE PROCESS (lower offset) WILL
            // COUNT WORDS THAT LATER BRANCHES (larger offset) HAVE ALREADY FOUND.

            if (overall_index + branches[i].offset >= strlen(buffer)){
                continue;
            }

            char current_char = buffer[overall_index + branches[i].offset];

            // This is the character the branch is looking for
            char branch_char = info->pattern[branches[i].expected_char_index];

            if (current_char == branch_char){
                // If the branch found the character it is looking for, increment matched chars
                branches[i].matched_chars++;
                if (branches[i].matched_chars == strlen(info->pattern)){
                    // Then, if we matched enough to be a whole word,
                    // increment numFound, reset matched_chars, and reset the expected_char_index
                    //     (once we find a word now we are looking for the start of the word once more)
                    info->numFound++;
                    branches[i].matched_chars = 0;
                    branches[i].expected_char_index = 0;
                } else {
                    // If we matched but do not have enough characters to be the whole targer word, simply set to
                    // look for the next character in the pattern
                    branches[i].expected_char_index = (branches[i].expected_char_index + 1) % strlen(info->pattern);
                }
            } else {
                // If the character didn't match, go back to looking for the start of the word and reset matched_chars
                branches[i].matched_chars = 0;
                branches[i].expected_char_index = 0;
            }
        }

        // printf("\nTHREAD: %i. This is the word: %s. This is the index: %i. This is the local char: %c. This is the global char: %c.", info->startIndex, info->pattern, current_index, info->pattern[current_index], buffer[overall_index]);
//        if (buffer[overall_index] == info->pattern[current_index]){
            // The current letter of the target word and the current letter of the buffer match.
            // This means we get to increment the number of characters that have matched in order
//            matched_chars++;
            // printf("\nmatched char. Count: %i", matched_chars);
//            if (matched_chars == strlen(info->pattern)){
                // The number of matched characters in order we have found equals the number we need in order
                // to be sure we found the target word.
                // Therefore, we increment numFound, reset the matched chars, and start from the beginning of the
                // target word once more by resetting the current index.
//                info->numFound++;
//                matched_chars = 0;
//                current_index = 0;
                // printf("\nfound a word");
//            } else {
                // If they matched but do not make the whole word, increment the local index because we
                // can keep comparing further to see if it will make a whole word
//                current_index++;
//            }
//        } else {
            // They didn't match, meaning the current strain of characters failed to create the target word
            // Therefore, we reset the current index to start from the beginning of the target word once more
//            matched_chars = 0;
//            current_index = 0;
//        }

        // Increment the current index
        overall_index++;

        // If we have reached or passed the target end and we are not in the middle of identifying a word, quit
        // This will not break if we are either still within our start-end range OR we are in the middle of identifying
        // a word.

        // This makes sure none of the branches are still working on a word
        bool none_matching = true;
        for (int i = 0; i < strlen(info->pattern); i++){
            if (branches[i].matched_chars != 0) {
                none_matching = false;
            }
        }

        if ((overall_index >= info->endIndex && none_matching) || overall_index >= strlen(buffer)) {
            printf("\nthread ended");
            break;
        }
    }*/
}

int main(int argc, char *argv[]) {
    int rc, numChars;
    /*if (argc < 2) {
        printf("ERROR: need a filename\n");
        return 8;
    }*/
    //rc = readFile(argv[1], &numChars);
    //"C:/Users/Kentd/CLionProjects/ProgrammingAssignment4-Threads/abba.asc"
    //"C:/Users/nmila/Downloads/OperatingSystems/ProgrammingAssignment4-Threads/abba.asc"
    rc = readFile("C:/Users/Kentd/CLionProjects/ProgrammingAssignment4-Threads/abba.asc", &numChars);
    if (rc != 0)
        return 8;

    // prompt the user for the string to search for, using PROMPT

    // create the threads
    SearchInfo searchInfo[NUM_THREADS];
    pthread_t tid[NUM_THREADS];
    pthread_t threads[NUM_THREADS];

    char input[100];
    char* prompt = input;
    printf("\nEnter prompt: ");
    if (fgets(prompt, sizeof(buffer), stdin) != NULL) {
        prompt[strcspn(prompt, "\n")] = '\0';
    }
    for (int i = 0; prompt[i] != '\0'; i++) {
        prompt[i] = tolower((unsigned char)prompt[i]);
    }
    printf("prompt received:");
    printf(prompt);
    int partition_size = strlen(buffer) / NUM_THREADS;
    int start_index = 0;
    int num_found = 0;
    for (int i=0; i<NUM_THREADS; ++i) {
        searchInfo[i] = (SearchInfo){start_index, start_index + partition_size, prompt, num_found};
        threads[i] = pthread_create(&tid[i], NULL, findStrings, &searchInfo[i]);
        start_index = start_index + partition_size;
    }
    // wait for the threads to finish
    for (int i=0; i<NUM_THREADS; ++i) {
        pthread_join(tid[i], NULL);
        // summarize the results from the threads
        num_found += searchInfo[i].numFound;
    }
    printf("\nNumber of items found: %d\n", num_found);
    return 0;
}