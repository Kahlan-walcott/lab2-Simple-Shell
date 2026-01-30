#include <stdio.h>  
#include <sys/types.h>  
#include <unistd.h>  
#include <stdlib.h> 
#include <string.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <sys/time.h>

int main() {  
    char string[100];
    int n = 100;
    pid_t pid, child;
    int status;
    struct rusage usage;
    while (1) { 
        printf("Enter command: ");
        fgets(string, n, stdin);
    
        string[strcspn(string, "\n")] = '\0'; // fgets adds in a new line - this line gets rid of it
    
        char *word1 = strtok(string, " ");
        char *word2 = strtok(NULL, " ");
        char *nullList[] = {word1, word2, NULL}; // the second spot requiers a null terminated list - this is how I got it
     
        if (strcmp(word1, "quit") == 0) {
            printf("You entered: %s to end the program.\n", word1);
            break;
        }
    
        //printf("%d", strcmp(word1, " "));
        if (word1 == NULL) { 
            fputs("Usage: must supply a command\n", stderr);  
            break;  
        } 
        pid = fork();
        if (pid == 0) {
            if (execvp(nullList[0], nullList) < 0) {  // what does the s    econd value have to be here
                perror("exec failed");
                exit(1);
            }
        }
        if (pid != 0) {
            wait(&status);
        }
        if (execvp(word1, nullList) < 0) {  // what does the second value have to be here - this kind of works
            perror("exec failed");  
            exit(1);  
        }  
    }
    
    return 0;  
}

