#include <stdio.h>
#include <string.h>

// Prototype of the function specified in the project question
void railFence(char *message, char *cipherText, int length, int A);

int main() {
        char output[1024];
    char message[] = "hello world";
    int A = 3;
        railFence(message, output, (int)strlen(message), A);
        printf("%s\n", output);

    return 0;
}

// Template for you to fill in. The variables listed were the ones my
// implementation used. Declare more if needed.
// Note that I ignore the "length" parameter. It needs to be there to meet spec
// but you are welcome to ignore it and call strlen() from this function
void railFence(char *message, char *cipherText, int length, int A) {
        // Declare the "rail" grid with appropriate size.
        // Choice of row/col order in indexing is arbitrary
    
        char grid[strlen(message)][A];
        
   
//    char message [] = "hello world";
//    int A = 3;
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
                output[i] = grid[i][j];
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
    
    
    
    
    
        // TODO:
        // Zero out or pre-fill the grid[][] array - COMPLETE
        // Apply rail fence algorithm to fill it in
        // Read out the written letters right-to-left-top-to-bottom
        // fill in cipherText[] so the array output[] in main() gets filled in

