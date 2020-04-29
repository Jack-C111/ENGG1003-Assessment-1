#include <stdio.h>
#include <string.h>


//Putting a letter in single quotes turns it into its ASCII value
//Double quotes create a string and end it with a terminating zero, and create a memory address
//Initialise a string with double quotes

void railFence(char *message, char *cipherText, int length, int A); // rail fence function declaration as specified in task
void railFence2(char *message, char *cipherText, int length, int A, int B, int dir); // two level rail fence function declaration as specified in task
int findSize(char filename[]); // declaration of function used to determine length of file

int main(int argc, char *argv[]) {
    
    char decryptedFilename[] = "Message"; // variable for file names - makes it simpler to change files rather than if it was hard coded
    char encryptedFilename[] = "Cipher Text";
    
    int menuSelection = 0; // variable for user to input menu selection
    int length = 0;
    
    // following 3 printf statements print menu text to console
    printf ("\n MAIN MENU:\n\n Make selection by inputing integer denoted before option.\n\n");
    printf (" 1. Encryption using classic rail-fence cipher\n 2. Encryption using 2-level rail-fence cipher\n 3. Decryption using 2-level rail-fence cipher\n 4. Decryption using substitution cipher\n 5. Exit\n");
    printf ("\n    Enter selection: ");
    scanf ("%d", &menuSelection); // scans user input as an integer
    
    while ((menuSelection < 1) || (menuSelection > 5)) { // while loop repeats selection prompt if an integer outside the possible values is input
        
        printf ("\n    Invalid input '%d', try again.", menuSelection);
        printf ("\n    Enter selection: ");
        scanf ("%d", &menuSelection);
    
    }
    
    int A; // number of rails
    int B; // number of rails cipher steps up for two-level rail fence cipher
    int dir; // used to specify encryption or decription in two-level rail fence function
    
    switch (menuSelection) { // switch case for menu selections
        case 1: { // CLASSIC RAIL FENCE ENCRYPTION
            
            FILE* decryptedFile; // opens input file in read mode
            decryptedFile = fopen (decryptedFilename, "r");
            
            FILE* encryptedFile; // opens output file in write mode
            encryptedFile = fopen (encryptedFilename, "w");
            
            length = findSize(decryptedFilename); // calls function and returns integer which is length of input file
            
            char message[length]; // decrypted message
            char cipherText[length]; // encripted message
            
            fgets(message, length, decryptedFile); // gets string from file and stores it in message char
            
            
            printf ("\n\n   Classic rail-fence encryption selected");
            printf ("\n   Input number of rails: ");
            scanf ("%d", &A);
            railFence(message, cipherText, length, A); // calls rail fence function
            fprintf(encryptedFile, "%s", cipherText);
            printf ("   Encrypted text has successfully been printed to the '%s' file.", encryptedFilename);
            
            fclose (encryptedFile);
            fclose (decryptedFile);
            
            break;
        }
        
        case 2: { // TWO-LEVEL RAIL FENCE ENCRYPTION
            
            FILE* decryptedFile; // opens input file in read mode
            decryptedFile = fopen (decryptedFilename, "r");
            
            FILE* encryptedFile; // opens output file in write mode
            encryptedFile = fopen (encryptedFilename, "w");
            
            length = findSize(decryptedFilename); // calls function and returns integer which is length of input file
            
            char message[length]; // decrypted message
            char cipherText[length]; // encripted message
            
            fgets(message, length, decryptedFile); // gets string from file and stores it in message char
            
            dir = 0;
            printf ("\n\n   Two-level rail-fence encryption selected");
            printf ("\n   Input number of rails: ");
            scanf ("%d", &A);
            printf ("\n   Input height of peaks: ");
            scanf ("%d", &B);
            railFence2(message, cipherText, length, A, B, dir);
            fprintf(encryptedFile, "%s", cipherText);
            printf ("   Encrypted text has successfully been printed to the '%s' file.", encryptedFilename);
            
            fclose (encryptedFile);
            fclose (decryptedFile);
            
            break;
        }
        
        case 3: { // TWO LEVEL RAIL FENCE DECRYPTION
            
            FILE* encryptedFile; // opens input file in read mode
            encryptedFile = fopen (encryptedFilename, "r");
            
            FILE* decryptedFile; // opens output file in write mode
            decryptedFile = fopen (decryptedFilename, "w");
            
            length = findSize(encryptedFilename); // calls function and returns integer which is length of input file
            
            char message[length]; // decrypted message
            char cipherText[length]; // encripted message
            
            fgets(cipherText, length, encryptedFile); // gets string from file and stores it in message char
            
            dir = 1;
            printf ("\n\n   Two-level rail-fence decryption selected");
            printf ("\n   Input number of rails: ");
            scanf ("%d", &A);
            printf ("\n   Input height of peaks: ");
            scanf ("%d", &B);
            railFence2(message, cipherText, length, A, B, dir);
            fprintf(decryptedFile, "%s", message);
            printf ("   Decrypted text has successfully been printed to the '%s' file.", decryptedFilename);
            
            fclose (encryptedFile);
            fclose (decryptedFile);
            
            break;
        }
        
        case 5:
            printf ("\n    Program exited\n\n\n");
            return 0;

        default: {
            
            printf ("An error has occured");
            return 8;
            
            break;
        }
    }
        
    
    
    
    printf("\n\n\n\n\n\n\n\n");
    return 0;
}


int findSize(char filename[]) // function to determine length of file - WORKING
{
    FILE* file = fopen(filename, "r"); // opening the file in read mode
  
    if (file == NULL) { // if statements occurs if file does not exist and prints error
        perror("error");
        return -1;
    }
  
    fseek(file, 0L, SEEK_END); // seeks to end of file so position of last character can be determined
  
    int size = (int)ftell(file); // determines size of file as integer
  
    fclose(file); // close file
  
    return size; // return length of file (will be no. of characters +1 for terminating character)
}


void railFence(char *message, char *cipherText, int length, int A) {
    
    char grid[length][A]; // establishes 2D array
    
    int i = 0, j = 0; // i is x coordinate and j is y coordinate
        
    // RESET ALL VALUES IN ARRAY TO 0 AND PRINT VISUAL REPRESENTATION
    
    for (j = 0; j < A; j++) { //2 nested 'for' loops to reset all values in grid to 0, also prints visual representation
//        printf ("\n");
        for (i = 0; i < strlen(message); i++) {
            grid [i][j] = 0;
//            printf("%d ", grid[i][j]);
        }
    }
    printf ("\n");

    // SET VALUES WHICH WILL CONTAIN CHARACTER TO '1'
    
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
         
    
    //START ASSIGNING CHARACTERS TO ARRAY CHARACTERS WITH '1'
    
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
            
    i = 0;
    j = 0;
    
    // READ VALUES ROW BY ROW AND PRINT ENCRIPTED TEXT
   
    
    FILE* outputFile; // opens output file in write mode
    outputFile = fopen ("Output", "w");
    
    int key = 0; // designates position of character on cipherText string
    
    while (j < A) {
        while (i < strlen(message)) {
            if (grid[i][j] != 0) {
                cipherText[key] = grid[i][j];
                i++;
                key++;
            }
            else
                i++;
        }
        i = 0;
        j++;
    }

    printf("\n\n");
    
    
}


void railFence2(char *message, char *cipherText, int length, int A, int B, int dir) {

    int i = 0, j = 0;
    char grid[length][A];
    int key = 0;
  
    
    if (dir == 0) {
    
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
                    if (i == strlen(cipherText)) {
                        break;
                    }
                }
            
                if (j == A-1) { //if reaches bottom first time
                    while (1) { //loop to bring it back to A-B
                        grid[i][j] = 1;
                        i++;
                        j--;
                        if (j == A - B)
                            break;
                        if (i == strlen(cipherText)) {
                            break;
                        }
                    }
                    if (j == A - B) { // if it reaches A-B
                        while (1) { //bring it back to bottom
                            grid [i][j] = 1;
                            i++;
                            j++;
                            if (j == A-1)
                                break;
                            if (i == strlen(cipherText)) {
                                break;
                            }
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
                    if (i == strlen(cipherText)) {
                        break;
                    }
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
                    if (i == strlen(cipherText)) {
                        break;
                    }
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
            key = 0;

        // READ VALUES ROW BY ROW AND PRINT ENCRIPTED TEXT - WORKING
        
        while (j < A) {
            while (i < strlen(message)) {
                if (grid[i][j] != 0) {
    //                printf("%c", grid [i][j]);
                    cipherText[key] = grid [i][j];
                    i++;
                    key++;
                    if (j == A) {
                        break;
                    }
                }
                else
                    i++;
            }
            i = 0;
            j++;
            if (j == A) {
                break;
            }
            
        }
        

        printf("%s", cipherText);
        printf("\n\n");
    
    }
    
    
    
    // START OF DECRIPTION
    
    
    if (dir == 1) {
    
        key = 0;
        char grid2[strlen(cipherText)][A];

        // RESET ALL VALUES IN ARRAY TO 0 AND PRINT VISUAL REPRESENTATION - WORKING
        
        printf("grid 2:\n");
        
        for (j = 0; j < A; j++) { //2 nested 'for' loops to reset all values in grid to 0, also prints visual representation
            printf ("\n");
            for (i = 0; i < strlen(cipherText); i++) {
                grid2 [i][j] = 0;
                printf("%d ", grid2[i][j]);
            }
        }
        printf ("\n");

        
        
        
        
        
        // SET VALUES WHICH WILL CONTAIN CHARACTER TO '1' - WORKING
        
        j = 0; //resets both coordinates to zero so algorithm starts from (0,0)
        i = 0;
        
        while (i < strlen(cipherText)) {
            
            if (j == 0) { //if at very top
                while (1) { //while loop moves values
                    grid2[i][j] = 1;
                    i++;
                    j++;
                    if (j == A - 1)
                        break;
                    
                    
                    if (i == strlen(cipherText)) {
                        break;
                    }
                }
            
                if (j == A-1) { //if reaches bottom first time
                    while (1) { //loop to bring it back to A-B
                        grid2[i][j] = 1;
                        i++;
                        j--;
                        if (j == A - B)
                            break;
                        
                        if (i == strlen(cipherText)) {
                            break;
                        }
                    }
                    if (j == A - B) { // if it reaches A-B
                        while (1) { //bring it back to bottom
                            grid2[i][j] = 1;
                            i++;
                            j++;
                            if (j == A-1)
                                break;
                            if (i == strlen(cipherText)) {
                                break;
                            }
                        }
                    }
                }
            }
            if (j == A - 1) {
                while (1) {
                    grid2[i][j] = 1;
                    i++;
                    j--;
                
                    if (j == 0)
                        break;
                }
            }
        
        }
        
        
        for (j = 0; j < A; j++) {
            printf ("\n");
            for (i = 0; i < strlen(cipherText); i++) {
                printf("%d ", grid2[i][j]);
            }
        }
        printf ("\n\n");
        
        
        
        //START ASSIGNING CHARACTERS TO ARRAY CHARACTERS WITH '1' - NOT WORKING
        
        i = 0;
        j = 0;
        key = 0;
        
        
        while (j < A) {
            while (i <= strlen(cipherText)) {
                if (grid2[i][j] != 0) {
                    grid2[i][j] = cipherText[key];
                    i++;
                    key++;
                }
                else
                    i++;
            }
            i = 0;
            j++;
            }
            
        
        
        // PRINT VISUAL REPRESENTATION OF ARRAY - WORKING
        
                for (j = 0; j < A; j++) {
                    printf ("\n");
                    for (i = 0; i < strlen(cipherText); i++) {
                        printf("%d ", grid2[i][j]);
                    }
                }
                printf ("\n\n");
        
        
        i = 0;
        j = 0;
            key = 0;

        // READ VALUES COLUMN BY COLUMN AND PRINT DECRIPTED TEXT - NOT WORKING

        while (i <= strlen(cipherText)) {
            for (j = 0; j < A; j++) {
                if (grid2[i][j] != 0) {
                    message[key] = grid2[i][j];
                    key++;
                }
            }
            i++;
        }

        printf("\n\n");

        
        printf("%s", message);
        
        printf("\n\n");
        
        
        }
    

}





/*

int main() {
    FILE *input;
    FILE *output;

    input = fopen("File", "r");
    output = fopen("Result", "w");
    
    if (input == NULL) {
        perror("error" );
        return 1;
    }
    
    char string, *p;
    p = &string;
    
    while (!feof(input)) {
        fscanf(input, "%c", p);
        printf("%c", *p);
        fprintf(output, "%c", *p);
        
        
        
    }

    return 0;

}

*/
