//
// Created by Kentd on 10/30/2026.
//

#ifndef PROGRAMMINGASSIGNMENT4_THREADS_FINDSTRINGS_KSCHNE11_NMILAZZ_H
#define PROGRAMMINGASSIGNMENT4_THREADS_FINDSTRINGS_KSCHNE11_NMILAZZ_H

#define BUFLEN 10100
#define LINELEN 1024

#define PROMPT "String to search for? "

typedef struct {
    int startIndex; // start index in buffer[] at which to begin searching
    int endIndex; // end index
    char *pattern; // the pattern to look for
    int numFound; // #instances of the pattern found
    
} SearchInfo;

typedef struct {
    int expected_char_index;
    int current_index;
    int matched_chars;
    int offset;
} SearchBranch;

int readFile(char *filename, int *numChars);
void *findMatches(void *param);
#endif //PROGRAMMINGASSIGNMENT4_THREADS_FINDSTRINGS_KSCHNE11_NMILAZZ_H
