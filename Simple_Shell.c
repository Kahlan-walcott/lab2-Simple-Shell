#include <stdio.h>  
#include <sys/types.h>  
#include <unistd.h>  
#include <stdlib.h> 
#include <string.h>

int main() {  
    char string[100];
    int n = 100;
    while (1) { // this may or may not work yet I don't know
        printf("Enter command: ");
        fgets(string, n, stdin);
        printf("%s", string); // debugging print
    
        string[strcspn(string, "\n")] = '\0'; // fgets adds in a new line - this line gets rid of it
    
        char *word1 = strtok(string, " ");
        char *word2 = strtok(NULL, " ");
        char *nullList[] = {string, NULL}; // the second spot requiers a null terminated list - this is how I got it
    
        printf("Word1: %s Word2: %s\n", word1, word2); // debugging print
    
        if (strcmp(word1, "quit") == 0) {
            printf("You entered: %s to end the program.\n", word1);
            break;
        }
    
        //printf("%d", strcmp(word1, " "));
        if (*word1 =='\0' || string == NULL) { // trying to figure out this one - when no command is suplied (dosen't work)
            fputs("Usage: must supply a command\n", stderr);  
            break;  
        } 
    
        puts("Before the exec");  
        if (execvp(word1, nullList) < 0) {  // what does the second value have to be here - this kind of works
            perror("exec failed");  
            exit(1);  
        }  
    }
    puts("After the exec"); 
    
    return 0;  
}

