/*
 * Copyright ©2024 Alex Hansen.  All rights reserved. No use, copying, 
 * distribution, or modification is permitted without prior written consent.
 * Copyrights for third-party components of this work must be honored.
 * 
 * ahansen4@uw.edu
 */

#include <stdio.h>      // for input/output
#include <stdlib.h>     // for EXIT_SUCCESS, EXIT_FAILURE
#include <string.h>     // for string manipulation
#include <fcntl.h>      // for open()
#include <unistd.h>     // for close()
#include <dirent.h>     // for directory manipulation
#include <stdbool.h>    // for bool type

#define MAX_PATH_LENGTH 128  // Arbitrary max input path lang for control.
#define EXTENSION ".txt"  // File extension being filtered for

// Helper function that takes a filename and compares the end of it to EXTENSION
bool comp(char* filename);

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Please provide an input\n");
        return EXIT_FAILURE;
    }

    int file, len;
    DIR* dirName;
    struct dirent* entry;
    char* filename;
    char inputLong[7];  // chars 1-6 of input
    char inputShort[6];  // chars 1-5 of input
    char main[7];  // root directory of the system
    char curDir[MAX_PATH_LENGTH];
    char pathBuf[MAX_PATH_LENGTH];
    char outBuf[MAX_PATH_LENGTH];
    char filePath[MAX_PATH_LENGTH*2];

    // Process directory name from argv[].
    char* end = "";
    len = strlen(argv[1]);
    if ('/' != argv[1][len-1]) {
        end = "/";
    }

    // Processing input directory path and system directory tree to be usable
    snprintf(inputLong, sizeof(inputLong), "%s", argv[1]);  // input
    getcwd(curDir, MAX_PATH_LENGTH);
    strncpy(main, curDir, 6);
    main[6] = '\0';  // "/homes"
    strncpy(inputShort, inputLong, 6);
    inputShort[5] = '\0';  // "homes"

    // Processing to correct for minor variations in directory input
    if (!strcmp(inputShort, main+1)) {  // checking for "homes", need '/'
        snprintf(pathBuf, MAX_PATH_LENGTH, "/%s%s", argv[1], end);
    } else if (strcmp(inputLong, main) && ('/' == argv[1][0])) {
        // checking for relative path starting with '/'
        snprintf(pathBuf, MAX_PATH_LENGTH, "%s%s", argv[1]+1, end);
    } else {  // "/homes" or relative path without '/'
        snprintf(pathBuf, MAX_PATH_LENGTH, "%s%s", argv[1], end);
    }

    // Make sure the directory name is valid.
    dirName = opendir(pathBuf);
    if (dirName == NULL) {
        printf("Please provide a valid relative or absolute directory path\n");
        return EXIT_FAILURE;
    }

    // Iterate through the files in the directory, checking for the extension
    entry = readdir(dirName);
    while (entry != NULL) {
        filename = entry->d_name;
        if (comp(filename)) {
            snprintf(filePath, sizeof(filePath), "%s%s", pathBuf, filename);
            file = open(filePath, O_RDONLY);
            if (file != -1) {
                fflush(stdout);
                while (1) {
                    if (read(file, outBuf, sizeof(char)) == 0) {
                        break;
                    }
                    write(1, outBuf, sizeof(char));
                }
            }
            close(file);
        }
        entry = readdir(dirName);
    }
    closedir(dirName);
    return EXIT_SUCCESS;
}

bool comp(char* filename) {
    char* end = strrchr(filename, '.');
    if (strlen(end) != strlen(EXTENSION)) {
        return false;
    }
    return !strcmp(end, EXTENSION);
}
