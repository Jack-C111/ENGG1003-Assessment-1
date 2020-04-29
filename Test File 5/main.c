#include <stdio.h>
#include <string.h>

void railFence(char *message, char *cipherText, int length, int A); // rail fence encription function declaration
int findSize(char filename[]); // test file size function declaration

int main() {
    
    char filename[] = "message";
    
    FILE *file;
    file = fopen(filename, "r"); //opening rail fence input file in read mode
    
    int rails = 3;
    int length = 0;
    
//    char message, *message_pointer;
//    message_pointer = &message;
    
    int res = findSize(filename);
    if (res != -1) {
        printf("Size of the file is %d bytes \n", res);
        length = res;
    }
    
    else {
        printf("file error");
        res = 0;
        return 1;
    }
    
    char cipherText[length];
    char messageinput, *inputpointer;
    inputpointer = &messageinput;
    
    while (!feof(file)) {
        fscanf(file, "%c", inputpointer);
        railFence(&messageinput, cipherText, length, rails);
    }
    
    
    
    
    return 0;
}

void railFence(char *message, char *cipherText, int length, int A) {
    
//    char message [] = "hello world";
//    int A = 3;
    
    char grid[length][A];
    
    int i = 0, j = 0; // i is x coordinate and j is y coordinate
        
    // RESET ALL VALUES IN ARRAY TO 0 AND PRINT VISUAL REPRESENTATION - WORKING
    
    for (j = 0; j < A; j++) { //2 nested 'for' loops to reset all values in grid to 0, also prints visual representation
        printf ("\n");
        for (i = 0; i < strlen(message); i++) {
            grid [i][j] = 0;
            printf("%d ", grid[i][j]);
        }
    }
    printf ("\n");

    // SET VALUES WHICH WILL CONTAIN CHARACTER TO '1' - WORKING
    
    j = 0; //resets both coordinates to zero so algorithm starts from (0,0)
    i = 0;
    
    while (i < strlen(message)) { // only proceeds for length of message
        if (j == 0) { //if at top of rails, algorithm moves diagonally down unntil it reaches the bottom rail (A-1). this happens by adding one to both j and i
            while (1) {
                grid [i][j] = 1;

                if (j == A-1) { // if at bottom of rails (A-1), then loop is broken so code can continue at next if statement
                    break;
                }
                i++;
                j++;
            }
        }
        
        if (j == A-1) { // if at bottom of rails (A-1), algorithm moves diagonally up toward the right until it reaches the top rail. this happens by adding one to i and subracting one from j
            while (1) {
                grid [i][j] = 1;

                if (j == 0) { // if at the top rail, loop is broken, if not then it continues to move upward and to the right diagonally
                    break;
                }
                i++;
                j--;
            }
        }
        
    }
    // end block
         
    // PRINT VISUAL REPRESENTATION OF ARRAY - WORKING
    
         for (j = 0; j < A; j++) {
             printf ("\n");
             for (i = 0; i < strlen(message); i++) {
                 printf("%d ", grid[i][j]);
             }
         }
         printf ("\n\n");

        
    
    //START ASSIGNING CHARACTERS TO ARRAY CHARACTERS WITH '1' - WORKING
    
    i = 0;
    j = 0;
    
    while (i < strlen(message)) { // repeats process for every column
        while (j < A) { // while loop sets every '1' in the given [i] column to its related character from the string
            if (grid[i][j] == 1) {
                grid[i][j] = message[i];
                j++;
            }
            else {
                j++;
            }
        }
        i++;
        j = 0; // resets j to 0 as algorithm moves to next column
    }
            
    // PRINT VISUAL REPRESENTATION OF ARRAY - WORKING
    
            for (j = 0; j < A; j++) {
                printf ("\n");
                for (i = 0; i < strlen(message); i++) {
                    printf("%d ", grid[i][j]);
                }
            }
            printf ("\n\n");
    
    i = 0;
    j = 0;
    
    // READ VALUES ROW BY ROW AND PRINT ENCRIPTED TEXT - WORKING
    
    while (j < A) {
        while (i < strlen(message)) {
            if (grid[i][j] != 0) {
                printf("%c", grid [i][j]);
                i++;
            }
            else
                i++;
        }
        i = 0;
        j++;
        
    }
    
    printf("\n\n");
    
    
}





int findSize(char filename[]) // function to determine length of file - WORKING
{
    FILE* file = fopen(filename, "r"); // opening the file in read mode
  
    if (file == NULL) { // if statements occurs if file does not exist and prints error
        perror("error");
        return -1;
    }
  
    fseek(file, 0L, SEEK_END); // seeks to end of file so position of last character can be determined
  
    int res = (int)ftell(file); // determines size of file as integer
  
    fclose(file); // close file
  
    return res; // return length of file (will be no. of characters +1 for terminating character)
}
