#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

// number of words in a typical Unix dictionary file
#define DICT_WORDS 99171	// american-english.txt
//#define DICT_WORDS 13		// i4.txt
//#define DICT_WORDS 12		// i1.txt

// number of replacement suggestions
#define SUGGESTIONS 10

/**
    Name: Hsin-Jung Wang (Cindy)
    TCSS 333 
    Assignment: #3
    NetID: 1260340
*/

// This is a struct that stores the content of the
// word and the option that the word satisfied. 
struct dictionary {
    int optionSatisfied; 
    char* string; 
};

// This method stores each word into a struct. 
void checkCharDict(char target[], char word[], int index, struct dictionary wordList[DICT_WORDS]);

// This method checks and stores the top 10 words into an array of size 10. 
int checkSatisfy(int, int, struct dictionary[], char *suggest[]);

// This is the main method 
int main(int argc, char *argv[]){

    // make sure that the correct number of arguments are being passed
    // when running the program. 
    if (argc != 3) { 
        printf("Wrong number of arguments\n");
	exit(0);
    } else { 
        printf("Suggestions:\n");
    }
    
    //char *target = malloc(sizeof(argv[2])); // +1 for '\0'
    //strcpy(target, argv[2]); // target is the target word

   // open the dictionary for reading
    FILE *fptr = fopen(argv[1], "r");
    if (fptr == NULL) {
        printf("File not found! Exiting\n");
        exit(1);
    }

    // set up a string that will be used to 
    // read one word at a time from the dictionary file 
    char word[60];

    // set up a string array for the dictionary, 
    // where each row/word will be allocated 
    // dynamically based on the actual word length
    char *dict[DICT_WORDS];

    // set up a string array for the top 10 suggestions, 
    // where each row/word will be allocated dynamically 
    // based on the actual word length
    char *suggest[SUGGESTIONS+1]; 


    //*suggest = (char* )malloc(sizeof(char*) * SUGGESTIONS); 
    struct dictionary wordList[DICT_WORDS];
    //struct dictionary *wordList;


    int index = 0;
    int choice = 0;
    char *arr; 
    int found; 
    found = 0;

    // while the reading of a word has been successful 
    while (fscanf(fptr, "%s", word) > 0) {
        char *arr; 
        arr = (char *)malloc(sizeof(char) * (sizeof(word)));
        strcpy(arr, word);
        dict[index] = arr; 
	
	//dict[index] = (char *)malloc(sizeof(char) * (sizeof(word)));
        //strcpy(dict[index], word);

        // if the inputted word matches one of
        // the word in the dictionary. 
        if(strcmp(arr, argv[2]) == 0) {
            found = 1;  
        }

        // set to default
        wordList[index].optionSatisfied = 0;
	wordList[index].string = (char *)malloc(strlen(dict[index]) +1); 
        
	strcpy(wordList[index].string, word);
        //checkCharDict(target, dict[index], index, wordList);
checkCharDict(argv[2], dict[index], index, wordList);

        index++;
    }


    if(found ==1) {
        printf("%s found\n", argv[2]);
	exit(0);
    }
 


    // loop through all the structs, find the optionsatisfied
    // and stores the top 10 choices into the suggested array. 
    int printCount = 0;
    int tmp = 0; 
    // check for words that satisfy the first option.
    tmp = checkSatisfy(1, printCount, wordList, suggest); 
    printCount = tmp; 
    
    if(printCount <10) {
        // check for words that satisfy the second option. 
    	tmp = checkSatisfy(2, printCount, wordList, suggest); 
    	printCount = tmp;
    }

    if(printCount <10) {
	// check for word that satisfy the third option. 
    	tmp = checkSatisfy(3, printCount, wordList, suggest); 
    	printCount = tmp; 
    }

    if(printCount <10) {
	// check for word that satisfy the fourth option. 
        tmp = checkSatisfy(4, printCount, wordList, suggest); 
    	printCount = tmp;
    }


    if(printCount <10) {
	// check for word that satisfy the fifth option.
    	tmp = checkSatisfy(5, printCount, wordList, suggest); 
    	printCount = tmp; 
    }

    if(printCount <10) {
	// check the word that satisfy the sixth option. 
    	tmp = checkSatisfy(6, printCount, wordList, suggest); 
    	printCount = tmp;
    }

    int i, j; 
    // if the inputted word matches a word in the dictionary
    // then prints word is found. 
    // Otherwaise, print the top 10 suggested words. 
    if(found != 1) {
        for(i = 0; i < printCount; i++) {
            printf("%s\n", suggest[i]); 
        }
    }
 
	

    int k, p= 0; 

    // free the array that stores the 10 suggested words
    for(k =0; k < printCount; k++) {
        free(suggest[k]);   

    }

    // free the array of struct that stores the words from the dictionary
    // and free the array that contains all the dictionary words. 
    for(k = 0; k < index; k++) {
	free(wordList[k].string);
	free(dict[k]);
    }

    // free the pointer of the array that stores all the words from 
    // the dictionary.txt
    free(*dict); 

    // closes the pointer
    fclose(fptr);

    // free the array that stores the inputted target word
    //free(target);
    return(0);
}

// This method inputs the top 10 choices into the suggested array. 
// Pre: option determines how the words should be prioritized and added to the list. 
//      printCount is the number of words store in the suggested array.
//      wordList is a struct that contains all the words and its option. 
//      suggest is the array that stores the top ten choices. 
// Post: returns the current number of elements inside the suggested array. 
int checkSatisfy(int option, int printCount, struct dictionary wordList[DICT_WORDS], char **suggest) {
    int i = 0; 
    
    for (i = 0; i < DICT_WORDS; i++) {
        // break out of the loop when reach top 10 suggestions
        if(printCount >= 10) {
            return 10;
        }
        // add the top 10 words into the suggested array. 
        if(wordList[i].optionSatisfied == option) {
	    suggest[printCount] = (char *)malloc(strlen(wordList[i].string)+1); 
            strcpy(suggest[printCount], wordList[i].string);

             printCount++;
 
        }
    }

    return printCount; 
}

// Find the words of the same length but only one letter different.
// pre: target is a char array that stores the user's input word
//      word is a char array that stores a word from the dictionary.txt
//      index is the index where the current word is stored inside the struct
//      wordList is a struct array that contains the word and its option.
// post: all the words from the dictionary.txt are now stored in an array 
//       of struct with a specified option. 
void checkCharDict(char target[], char word[], int index, struct dictionary wordList[DICT_WORDS]) {
    int i, sameCount, count, length, checkoption;
    checkoption = 0; 
    length = 0; 
    count = 0; 
    sameCount = 0; 

    // make sure we assign the length value
    // based on whichever word that has a  
    // shorter length.
    if (strlen(target) < strlen(word)) {
        length = strlen(target);
    } else {
        length = strlen(word);
    }
 
    // count the number of different letters 
    for(i = 0; i < length; i++) {
        if (target[i] != word[i]) {
            count++; 
        } 
    }
	
    // This is the top choice
    if((strlen(target) - strlen(word)) == 0) {         
        if(count == 1) {
           // printf("difference of one character in 1st option \n");
             wordList[index].optionSatisfied = 1;
             checkoption = 1; 
             
        }
    // This is the 2nd top choice    
    } else if ((strlen(target) - strlen(word)) == -1) {
        // e.g., (belo - below) = -1
        // dictionary word is one letter longer
        if(count == 0) {
           // printf("difference of one character in 2nd option \n");
             wordList[index].optionSatisfied = 2;
             checkoption = 1; 
        }

    // This is the 3rd top choice
    } else if ((strlen(target) - strlen(word)) == 1) {  
        // dictionary word is one letter longer
        if(count == 0) {
            // printf("\n difference of one character in 3rd option \n");
             wordList[index].optionSatisfied = 3;
             checkoption = 1; 
        }

    // This is the 4th top choice
    } else if ((strlen(target) >= 5) && (strlen(target) - strlen(word)) == 0) {  
        // dictionary word is one letter longer
        if(count == 2) {
          //  printf("\n difference of one character in 4th option \n");
             wordList[index].optionSatisfied = 4;
             checkoption = 1; 
        }
    } 

    if (checkoption ==0) {
        // 5th and 6th options 
    	int m, n, count5, count6 = 0; 
    	count5 =0;
        count6 = 0; 
        n = 0;  
    	char tempWord[strlen(word) +1]; 
    	strncpy(tempWord, word, strlen(word) +1); // copy the entire word
        int wordLength, targetLength = 0; 
        wordLength = strlen(word);
        targetLength = strlen(target);
        
        if (wordLength < ((targetLength -1) *2)) {
            if (wordLength > targetLength) {
               for(m= 0; m < strlen(word) - (strlen(target) -2); m++) {
                   if(strncmp(target, tempWord, (strlen(target)-1)) == 0) {
                       if(m == 0) {
                           count5 = 5; 
                       } else {
                           count6 = 6; 
                      }
                  } else {
                       tempWord[n] = tempWord[n+1];
                       n++;
                  } 
               }
           }
        }
        
        if(count5 == 5) {
            //printf("difference of one character in 4th option \n");
            wordList[index].optionSatisfied = 5;
        } else if(count6 == 6) {
           // printf("difference of one character in 5th option \n");
            wordList[index].optionSatisfied = 6;
        } 

    } 
}
    









