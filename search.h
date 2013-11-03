#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <err.h>
/*File traversal*/
#include <fts.h>
/*Hash table*/
#include "ext/uthash.h"

/*
 * In global scope:
 *  Inverted index data structure
 *	Linked-list of results
 * 	(for possible future threading, we can
 *	 mutex-lock the linked list)
 */

int parseAndStoreIndex(const char *indexfile );

/*Function name: searchAnd()
  Steps:
		1. Search for first word.
			a. Get word's file list, add to results
		2. Search for subsequent words
			a. For each file in results,
				IF file does not exist in subsequent word,
					remove from results;
				END IF	
*/
int searchAnd();


/*Function name: searchOr()
  Steps:
		1. Do search for each word subsequently
			a. Get word's file list
				IF file doesn't exist in results,
					add file to results;
				END IF
*/
int searchOr();


/*Return 0 if found duplicate, do NOT allow duplicates*/
int addToResults();

/*Used in searchOr function, checks 
int addAndCheckResults();
/*Only used in */
int deleteFromResults();

int checkResultsForFile(char *filename);


