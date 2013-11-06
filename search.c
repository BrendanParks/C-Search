/*
 * Brendan Parks and James Do
 * search.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

// SEARCH (LOGICAL AND STATEMENT)

// SEARCH (LOGICAL OR STATEMENT)

const char *WORD_START = "<list>";
const char *WORD_END = "</list>";

int getNextWordFromIndex() {
	

}

int main(int argc, const char **argv) {
    
    
    
    
    
    const char **n, *names[] = { "betty", "bob", "joe", NULL };
    
    struct hash *tobeadded, *tmp, *users, *subfile = NULL;
    
    
    
    //add words
    for (n = names; *n != NULL; n++) {
        tobeadded = (struct hash*)malloc(sizeof(struct hash));
        tobeadded->name = *n;
        HASH_ADD_KEYPTR( hh, users, tobeadded->name, strlen(tobeadded->name), tobeadded);
        
        
        //for loop to add paths
        subfile = (struct hash*)malloc(sizeof(struct hash));
        subfile->name = *n;
        HASH_ADD_KEYPTR( hh, tobeadded->sub, subfile->name, strlen(subfile->name), subfile);
        
        
    }
    
    
    
    
    HASH_FIND_STR( users, argv[1], tobeadded);
    
    
    
    
    //if found!!!
    if (tobeadded){
        
        printf("here!\n");
        
        //if not here
    }else{
        
        printf("not here\n");
    }
    
    
    /* free the hash table contents */
    HASH_ITER(hh, users, tobeadded, tmp) {
        HASH_DEL(users, tobeadded);
        free(tobeadded);
        free(subfile);
    }
    return 0;
}
    
    
    
    
	if (argc != 2){
		fprintf(stderr,"USAGE: search <inverted-index file name>\n");
		return 1;
	}
	
	FILE *indexFile;
	/* Open index file for reading */
	if (  (indexFile = fopen(argv[1], "r")) == NULL) {
		fprintf(stderr,"ERROR: File open\n");
		return 1;
	}
	
	
	
	char line[16384];
	char *tokBuffer;
	char pathBuffer[4096];
	char *tokBufPath; /* Used for getting whole path */
	
	/* State flags */
	int atStart = 0;
	int inWord = 0;
	int firstWordToken = 0;
	int isCount = 0;
	
	/*Get each line of index file*/
	while(fgets(line, sizeof(line), indexFile)){
				
				atStart = 0;
		while ((tokBuffer = strtok(atStart == 0 ? line : NULL," \f\n\r\t\v")) != NULL) {
		
			if (atStart == 0) atStart = 1;
			
			/*Continue at newline character*/
			if (tokBuffer[0] == 0x0d) {
				continue;
			}

			if (inWord==0) {
				printf("==================WORD START\n");
				if (strcmp(WORD_START,tokBuffer) != 0){
				/*If not at start of word and haven't started word...*/
					fprintf(stderr, "ERROR: Illegal start of word!\n");
					return 1; /*Bad index format*/
				} else {
					/*Start of new word*/
					inWord = 1;
					firstWordToken = 1;
				}			
			} else { /* inWord = 1, Currently in word*/
			
				if (strcmp(WORD_END,tokBuffer) == 0) { /*End of word*/
					inWord = 0;
					firstWordToken=0;
					isCount=0;
					
					continue;
				}
				if (firstWordToken == 1) { /* get word */
					printf("WORD: %s\n",tokBuffer);
					firstWordToken = 0;
					continue;
				} else if (isCount == 0) { /* get path */
					
					strcpy(pathBuffer,tokBuffer);
					/* printf("DEBUG: Start path is %s\n",pathBuffer); */
					
					/* Get whole path. Concat extra parts of path
						onto path snippet. This is done because
						of possible spaces inside of the path.*/
					while(pathBuffer[strlen(pathBuffer)-1] != '\"') { /*Looking for close quote*/
						tokBufPath = strtok(NULL," ");
						if (tokBufPath == NULL) {
							fprintf(stderr,"ERROR: Reached end of line without receiving full path\n");
							exit(1);
						}
						
						/* printf("DEBUG: tokBufPath is %s\n",tokBufPath); */
						
						/*Append space back on because it was a delimiter before*/
						if (strlen(pathBuffer)<4096) {
							pathBuffer[strlen(pathBuffer)+1] = '\0';
							pathBuffer[strlen(pathBuffer)] = ' ';
						} else {
							fprintf(stderr,"ERROR: Potential buffer overflow in path determination\n");
							exit(1);
						}
						
						strcat(pathBuffer,tokBufPath);
					}
					
					/*Return path*/
					printf("PATH IS: %s\n", pathBuffer);
					
					isCount = 1;
					continue;
				} else { /* isCount = 1, do nothing */
					printf("COUNT\n");
					isCount = 0;
					continue;
				}
				
			}
		}
	}
	
	fclose(indexFile);

}
