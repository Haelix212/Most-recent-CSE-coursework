/*
 * Copyright ©2024 Hal Perkins.  All rights reserved.  Permission is
 * hereby granted to students registered for University of Washington
 * CSE 333 for use solely during Winter Quarter 2024 for purposes of
 * the course.  No other use, copying, distribution, or modification
 * is permitted without prior written consent. Copyrights for
 * third-party components of this work must be honored.  Instructors
 * interested in reusing these course materials should contact the
 * author.
 */

// Feature test macro for strtok_r (c.f., Linux Programming Interface p. 63)
#define _XOPEN_SOURCE 600

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#include "libhw1/CSE333.h"
#include "./CrawlFileTree.h"
#include "./DocTable.h"
#include "./MemIndex.h"

//////////////////////////////////////////////////////////////////////////////
// Helper function declarations, constants, etc
static void Usage(void);
static bool NormalizeInput(char* path, char** result);
static void ProcessQueries(DocTable* dt, MemIndex* mi);
static int GetNextLine(FILE* f, char** ret_str);
bool IsEmpty(char *s);


//////////////////////////////////////////////////////////////////////////////
// Main
int main(int argc, char** argv) {
  if (argc != 2) {
    Usage();
  }

  // Implement searchshell!  We're giving you very few hints
  // on how to do it, so you'll need to figure out an appropriate
  // decomposition into functions as well as implementing the
  // functions.  There are several major tasks you need to build:
  //
  //  - Crawl from a directory provided by argv[1] to produce and index
  //  - Prompt the user for a query and read the query from stdin, in a loop
  //  - Split a query into words (check out strtok_r)
  //  - Process a query against the index and print out the results
  //
  // When searchshell detects end-of-file on stdin (cntrl-D from the
  // keyboard), searchshell should free all dynamically allocated
  // memory and any other allocated resources and then exit.
  //
  // Note that you should make sure the fomatting of your
  // searchshell output exactly matches our solution binaries
  // to get full points on this part.

  DocTable* table;
  MemIndex* index;
  char* path = malloc(512);

  printf("Indexing '%s'\n", argv[1]);
  NormalizeInput(argv[1], &path);

  if (!CrawlFileTree(path, &table, &index) &&
      !CrawlFileTree(argv[1], &table, &index)) {
    printf("Path '%s' is not indexable\n", argv[1]);
    free(path);
    Usage();
    return EXIT_FAILURE;
  } else {
    ProcessQueries(table, index);
  }
  free(path);
  DocTable_Free(table);
  MemIndex_Free(index);
  return EXIT_SUCCESS;
}


//////////////////////////////////////////////////////////////////////////////
// Helper function definitions

static void Usage(void) {
  fprintf(stderr, "Usage: ./searchshell <docroot>\n");
  fprintf(stderr,
          "where <docroot> is an absolute or relative " \
          "path to a directory to build an index under.\n");
  exit(EXIT_FAILURE);
}

static bool NormalizeInput(char* path, char** result) {
  if ((char) *path != '.') {
    snprintf(*result, strlen(path) + 4, "./%s/", path);
    return false;
  } else {
    snprintf(*result, strlen(path) + 2, "%s/", path);
    return true;
  }
}

static void ProcessQueries(DocTable* dt, MemIndex* mi) {
  char** buf;
  int combo, que_len = 0, spaces = 0;
  LinkedList* results;
  LLIterator* itr;
  SearchResult* res;

  while (1) {
    printf("enter query:\n");
    buf = malloc(512 * sizeof(char *));
    // Masking to pass back multiple values
    combo = GetNextLine(stdin, buf);
    que_len = combo / 100;
    spaces = combo % 100;

    if (combo == -1 || buf == NULL) {
      break;
    }

    // Get the list of results
    results = MemIndex_Search(mi, buf, que_len);
    if (results != NULL) {
      itr = LLIterator_Allocate(results);
      if (itr == NULL) {
        break;
      }
      // Print to console
      while (LLIterator_IsValid(itr)) {
        LLIterator_Get(itr, (LLPayload_t*) &res);
        char* name = DocTable_GetDocName(dt, res->doc_id);
        int num = res->rank;
        printf("  %s (%d)\n", name, num);
        LLIterator_Next(itr);
      }
      LLIterator_Free(itr);
      LinkedList_Free(results, &free);
    }
    if (que_len != 0) {
      free(*buf - spaces);
    }
    free(buf);
  }
  printf("shutting down...\n");
  free(buf);
}

static int GetNextLine(FILE *f, char **ret_str) {
  char* input = (char *) malloc(1024);
  char* token;
  char* ptr;
  char* p;
  int que_len = 0, num_space = 0;

  if (fgets(input, 1024, f) != NULL) {
    p = input;
    while (isspace(*p)) {
      num_space++;
      p++;
    }

    while (1) {
      token = strtok_r(input, " ", &ptr);
      if (token == NULL || IsEmpty(token)) {
        break;
      }
      for (int i = 0; i < strlen(token) + 1; i++) {
        token[i] = tolower(token[i]);
      }
      ret_str[que_len] = token;
      que_len++;
      input = NULL;  // Lets the while loop end
    }

    if (que_len != 0) {
      p = strchr(ret_str[que_len - 1], '\n');
      if (p) {
        *p = '\0';
      }
    }

    free(input);
    return (que_len * 100) + num_space;
  }
  free(input);
  return -1;
}

// Checks if an input string is all whitespace, returns false otherwise
bool IsEmpty(char* s) {
  while (*s) {
    if (!isspace(*s)) {
      return false;
    }
    s++;
  }
  return true;
}
