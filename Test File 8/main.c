#include <stdio.h>
#include <string.h>

int main() {
    
    char message [] = "this message is encrypted using the two level rail fence algorithm";
    int A = 5;
    int B = 3;
    
    char grid[strlen(message)][A];
    
    /*int rail,*/ int i = 0, j = 0; // i is x coordinate and j is y coordinate
        
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
    
    while (i < strlen(message)) {
        
        if (j == 0) { //if at very top
            while (1) { //while loop moves values
                grid[i][j] = 1;
                i++;
                j++;
                if (j == A - 1)
                    break;
            }
        
            if (j == A-1) { //if reaches bottom first time
                while (1) { //loop to bring it back to A-B
                    grid[i][j] = 1;
                    i++;
                    j--;
                    if (j == A - B)
                        break;
                }
                if (j == A - B) { // if it reaches A-B
                    while (1) { //bring it back to bottom
                        grid [i][j] = 1;
                        i++;
                        j++;
                        if (j == A-1)
                            break;
                    }
                }
            }
        }
        if (j == A - 1) {
            while (1) {
                grid[i][j] = 1;
                i++;
                j--;
            
                if (j == 0)
                    break;
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
    
    return 0;
    
}
