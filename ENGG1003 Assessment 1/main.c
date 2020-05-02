#include <stdio.h>
#include <string.h>
#include <time.h>

void railFence(char *message, char *cipherText, int length, int A); // rail fence function declaration as specified in task
void railFence2(char *message, char *cipherText, int length, int A, int B, int dir); // two level rail fence function declaration as specified in task
int findSize(char filename[]); // declaration of function used to determine length of file

int main(int argc, char *argv[]) {
    
    char decryptedFilename[] = "Message"; // variables for file names - makes it simpler to change files rather than if it was hard coded
    char encryptedFilename[] = "Cipher Text";
    
    int menuSelection = 0; // variable for user to input menu selection
    int length = 0; // variable for length of message (determined by findSize function)
    
    // following 3 printf statements print menu text to stdout
    printf ("\n MAIN MENU:\n\n Make selection by inputing integer denoted before option.\n\n");
    printf (" 1. Encryption using classic rail-fence cipher\n 2. Encryption using 2-level rail-fence cipher\n 3. Decryption using 2-level rail-fence cipher\n 4. Decryption using substitution cipher\n 5. Exit\n");
    printf ("\n    Enter selection: ");
    scanf ("%d", &menuSelection); // scans user input as an integer used for selecting menu item
    
    while ((menuSelection < 1) || (menuSelection > 5)) { // while loop repeats selection prompt if an integer outside the avaliable values is input
        
        printf ("\n    Invalid input '%d', try again.", menuSelection);
        printf ("\n    Enter selection: ");
        scanf ("%d", &menuSelection);
    }
    
    int A; // number of rails used for classic and two level rail fence cipher
    int B; // number of rails cipher steps up for two-level rail fence cipher
    int dir; // used to specify encryption or decription in two-level rail fence function
    
    switch (menuSelection) { // switch case for menu selections
        case 1: { // CLASSIC RAIL FENCE ENCRYPTION
            
            FILE* decryptedFile; // opens original message file in read mode
            decryptedFile = fopen (decryptedFilename, "r");
            
            FILE* encryptedFile; // opens output file in write mode
            encryptedFile = fopen (encryptedFilename, "w");
            
            length = findSize(decryptedFilename); // calls findSize function passing it the filename which is being used as input and sets returned integer as length variable
            
            char message[length]; // string to store original message
            char cipherText[length]; // string to store encrypted message
            
            int pos = 0; // position integer to track position of character within file
            char buffer; // buffer string to temporarily store characters from input file
            
            while (pos < (length - 1)) { // loop to read file character by character
                fscanf (decryptedFile, "%c", &buffer); // scans charcter from the message file and stores it in the buffer string
                message[pos] = buffer; // assigns the character in the buffer string to the corresponding position in the message string
                pos++; // moves position indicator to next position on string so next character can be assigned in correct position
            }

            printf ("\n\n    Classic rail-fence encryption selected");
            printf ("\n    Input number of rails: ");
            scanf ("%d", &A); // scans integer from stdin to use for number of rails
            railFence(message, cipherText, length, A); // calls rail fence function, inputting the message, length of the message and number of rails (A). cipherText variable is used to return encrypted string from void function
            fprintf(encryptedFile, "%s", cipherText); // prints resultant encrypted message into Cipher Text file
            printf ("    Encrypted text has successfully been printed to the '%s' file.", encryptedFilename);
            
            fclose (encryptedFile); // closes both files used for input and output
            fclose (decryptedFile);
            
            break;
        }
        
        case 2: { // TWO-LEVEL RAIL FENCE ENCRYPTION
            
            FILE* decryptedFile; // opens original message file in read mode
            decryptedFile = fopen (decryptedFilename, "r");
            
            FILE* encryptedFile; // opens output file in write mode
            encryptedFile = fopen (encryptedFilename, "w");
            
            length = findSize(decryptedFilename); // calls findSize function passing it the filename which is being used as input and sets returned integer as length variable
            
            char message[length]; // string to store original message
            char cipherText[strlen(message)]; // string to store encrypted message
            
            int key = 0; // position integer to track position of character within file
            char buffer; // buffer string to temporarily store characters from input file
            
            while (key < (length - 1)) { // loop to read file character by character
                fscanf (decryptedFile, "%c", &buffer); // scans charcter from the message file and stores it in the buffer string
                message[key] = buffer; // assigns the character in the buffer string to the corresponding position in the message string
                key++; // moves position indicator to next position on string so next character can be assigned in correct position
            }
            message[(length - 1)] = 0; // sets last character of message string to be a terminating char
            
            dir = 0; // dir is set to zero as this is passed to function to determine that user selected encryption
            
            printf ("\n\n    Two-level rail-fence encryption selected");
            printf ("\n    Input number of rails: ");
            scanf ("%d", &A); // scans integer from stdin to use for height of grid
            printf ("\n    Input height of peaks: ");
            scanf ("%d", &B); // scans integer from stdin to use for secondary height algorithm moves back up
            railFence2(message, cipherText, length, A, B, dir); // calls two level rail fence function, inputting the message, length of the message and number of rails (A). cipherText variable is used to return encrypted string from void function, dir is used to determine whether encryption or decryption has been selected by the user (in this case dir is set to 0 for encryption)
            fprintf(encryptedFile, "%s", cipherText); // prints resultant encrypted message into Cipher Text file
            printf ("    Encrypted text has successfully been printed to the '%s' file.", encryptedFilename);
            
            fclose (encryptedFile); // closes both files used for input and output
            fclose (decryptedFile);
            
            break;
        }
        
        case 3: { // TWO LEVEL RAIL FENCE DECRYPTION
            
            FILE* encryptedFile; // opens original, encrypted message file in read mode
            encryptedFile = fopen (encryptedFilename, "r");
            
            FILE* decryptedFile; // opens output file in write mode, same file as the original decrypted message file
            decryptedFile = fopen (decryptedFilename, "w");
            
            FILE* debugFile; // opens debug file in write mode
            debugFile = fopen ("Debugging Visualisations", "w");
            
            length = findSize(encryptedFilename); // calls findSize function passing it the filename which is being used as input and sets returned integer as length variable
            fprintf (debugFile, "message length is: %d\n", length); // prints length of string to debug file (used for debugging)
            
            char cipherText[length]; // string to store inputed encrypted message
            char message[strlen(cipherText)]; // string to store decrypted output message
            
            int key = 0; // position integer to track position of character within file
            char buffer; // buffer string to temporarily store characters from input file
            
            while (key < length) { // loop to read file character by character
                fscanf (encryptedFile, "%c", &buffer); // scans charcter from the Cipher Text file and stores it in the buffer string
                cipherText[key] = buffer; // assigns the character in the buffer string to the corresponding position in the cipherText string
                key++; // moves position indicator to next position on string so next character can be assigned in correct position
            }
                   
            dir = 1; // dir is set to one as this is passed to function to determine that user selected decryption
            
            printf ("\n\n    Two-level rail-fence decryption selected");
            printf ("\n    Input number of rails: ");
            scanf ("%d", &A); // scans integer from stdin to use for height of grid
            printf ("\n    Input height of peaks: ");
            scanf ("%d", &B); // scans integer from stdin to use for secondary height algorithm moves back up
            railFence2(message, cipherText, length, A, B, dir); // calls two level rail fence function, inputting the encrypted message, length of the message and number of rails (A). message variable is used to return decrypted string from void function, dir is used to determine whether encryption or decryption has been selected by the user (in this case dir is set to 1 for decryption)
            fprintf(decryptedFile, "%s", message); // prints resultant encrypted message into Message file
            printf ("    Decrypted text has successfully been printed to the '%s' file.", decryptedFilename);
            
            fclose (encryptedFile); // closes all files
            fclose (decryptedFile);
            fclose (debugFile);
            
            break;
        }
        
        case 5: // EXIT
            printf ("\n    Program exited\n\n\n"); // if exit option selected from menu, confirmation message printed to stdout and program returns 1
            return 1;

        default: { // DEFAULT
            printf ("An error has occured"); // if option outside of menu values (should be impossible due to while loop above) prints error to stdout and returns 8
            return 8;
        }
    }

    printf("\n\n\n\n\n\n\n\n"); // unnecessary block of new lines for visual enhancement
    
    // LOG FILE
    /* The following generates a log file after each run of the program. It places the date at the top and then copies the contents of the debug, message and cipher text files into a log file. The log file is written to accumulatively.*/
    
    FILE* debugFile;
    debugFile = fopen ("Debugging Visualisations", "r");
    
    FILE* logFile;
    logFile = fopen ("Log", "a");
    
    FILE* decryptedFile;
    decryptedFile = fopen (decryptedFilename, "r");
    
    FILE* encryptedFile;
    encryptedFile = fopen (encryptedFilename, "r");
    
    time_t now;
    time(&now);
    fprintf (logFile, "\n%s", ctime(&now));
    fprintf (logFile, "---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    length = findSize("Log");
    char buffer[length], *b;
    b = &buffer[length];
    fprintf (logFile, "\n");
    
    while (!feof(debugFile)) {
        fscanf (debugFile, "%c", b);
        fprintf (logFile, "%c", *b);
    }
    
    fprintf (logFile, "\n\nContents of %s File:\n", decryptedFilename);
    while (!feof(decryptedFile)) {
        fscanf (decryptedFile, "%c", b);
        fprintf (logFile, "%c", *b);
        buffer[length] = 0;
    }
    
    fprintf (logFile, "\n\nContents of %s File:\n", encryptedFilename);
    while (!feof(encryptedFile)) {
        fscanf (encryptedFile, "%c", b);
        fprintf (logFile, "%c", *b);
        buffer[length] = 0;
    }
    
    fprintf (logFile, "\n---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
    
    fclose(debugFile);
    fclose(logFile);
    
    return 0;
}


int findSize(char filename[]) // start of function definition to determine length of file
{
    FILE* file = fopen(filename, "r"); // opens file with name passed to function from main
  
    if (file == NULL) { // if statements occurs if file does not exist
        perror("error"); // prints error and error description to stdout
        return -1; // returns impossible length for file if file does not exist
    }
  
    fseek(file, 0L, SEEK_END); // seeks to end of file so position of last character can be determined
    int size = (int)ftell(file); // determines size of file as integer
    fclose(file); // close file
    
    return size; // return length of file (will be no. of characters +1 for terminating character)
}


void railFence(char *message, char *cipherText, int length, int A) { // start of function definition for classic rail fence function
    
    FILE* debugFile; // opens debug file in write mode
    debugFile = fopen ("Debugging Visualisations", "w");
    
    char grid[length][A]; // establishes 2D array responsible for holding message in correct order
    
    int i = 0, j = 0; // i is x-coordinate and j is y-coordinate in grid array
    int key = 0; // designates position of character on cipherText string
        
    // ----RESET ALL VALUES IN ARRAY TO 0 AND PRINT VISUAL REPRESENTATION----
    
    for (j = 0; j < A; j++) { // two nested 'for' loops move through all values in grid array
        fprintf (debugFile, "\n"); // used for debugging
        for (i = 0; i < strlen(message); i++) {
            grid [i][j] = 0; // sets each grid element to zero
            fprintf(debugFile, "%d ", grid[i][j]); // prints visual representation of zeroed grid to debug file, used for debugging
        }
    }
    fprintf (debugFile, "\n"); // used for debugging

    // ----SET VALUES WHICH WILL CONTAIN CHARACTER TO '1'----
    
    j = 0; //resets both coordinates to zero so algorithm starts from (0,0)
    i = 0;
    
    while (i < strlen(message)) { // only proceeds for length of message
        if (j == 0) { //if at top of rails, algorithm moves diagonally down until it reaches the bottom rail (A-1). this happens by adding one to both j and i
            while (1) {
                grid [i][j] = 1; // sets targeted array element to '1'

                if (j == A-1) { // if at bottom of rails (A-1), then loop is broken so code can continue at next if statement
                    break;
                }
                i++; // incriments both j and i by 1 to move algorithm diagonally downward
                j++;
            }
        }
        
        if (j == A-1) { // if at bottom of rails (A-1), algorithm moves diagonally up toward the right until it reaches the top rail. this happens by adding one to i and subracting one from j
            while (1) {
                grid [i][j] = 1; // sets targeted array element to '1'

                if (j == 0) { // if at the top rail, loop is broken, if not then it continues to move upward and to the right diagonally until it reaches top rail
                    break;
                }
                i++; // incriments i by 1 to move algorithm right
                j--; // decrements j by 1 to move algorithm up
            }
        }
        
    }
         
    
    // ----START ASSIGNING CHARACTERS TO ARRAY CHARACTERS WITH '1'----
    
    i = 0; // resets coordinates to (0,0) so algortithm starts from top right again
    j = 0;
    
    while (i < strlen(message)) { // repeats process for every column until message length is reached
        while (j < A) { // while and if loops sets every '1' in the given [i] column to its related character from the string
            if (grid[i][j] == 1) {
                grid[i][j] = message[i]; // sets relevant array elements to corresponding message character
                j++; // incriments j by 1 to move algorthm gradually downward
            }
            else {
                j++;
            }
        }
        i++; // moves algorithm to next column
        j = 0; // resets j to 0 as algorithm moves to next column
    }
    
    // ----READ VALUES ROW BY ROW AND PRINT ENCRIPTED TEXT----
    
    i = 0; // resets coordinates to (0,0) so algortithm starts from top right again
    j = 0;
    
    while (j < A) { // two while loops move across each row then move down another column to read encrypted message
        while (i < strlen(message)) {
            if (grid[i][j] != 0) { // if array element contains character assign the character to the corresponding cipherText character
                cipherText[key] = grid[i][j];
                i++; // incriment column and key if character is added to cipherKey
                key++;
            }
            else
                i++; // move to next column if array element is zero
        }
        i = 0; // reset to start of row
        j++; // move to next column
    }

    printf("\n\n");
    
    fclose (debugFile); // close debug file
    
}


void railFence2(char *message, char *cipherText, int length, int A, int B, int dir) { // start of function definition for two-level rail fence function
    
    FILE* debugFile; // opens debug file in write mode
    debugFile = fopen ("Debugging Visualisations", "w");

    int i = 0, j = 0; // i is x-coordinate and j is y-coordinate in grid array
    int key = 0; // designates position of character on strings
    
    // START OF ENCRYPTION
        
    if (dir == 0) { // dir is passed from main and is zero if encryption is selected
        
        char grid[(2 * length)][2 * A]; // establishes 2D array responsible for holding message in correct order
    
        // ----RESET ALL VALUES IN ARRAY TO 0 AND PRINT VISUAL REPRESENTATION----
        
        for (j = 0; j < A; j++) { // two nested 'for' loops move through all values in grid array
            fprintf (debugFile, "\n"); // used for debugging
            for (i = 0; i < strlen(message); i++) {
                grid [i][j] = 0; // sets each grid element to zero
                fprintf(debugFile, "%d ", grid[i][j]); // prints visual representation of zeroed grid to debug file, used for debugging
                if (i == strlen(message))
                    break;
            }
        }
        fprintf (debugFile, "\n"); // used for debugging
        
        
        // ----SET VALUES WHICH WILL CONTAIN CHARACTER TO '1'----
        
        j = 0; //resets both coordinates to zero so algorithm starts from (0,0)
        i = 0;
        
        while (i < strlen(message)) { // repeats process for every column until message length is reached
            
            if (j == 0) { //if at very top
                while (1) { //while loop repeats lines until break condition is met
                    grid[i][j] = 1; // sets targeted array element to '1'
                    i++; // incriments both j and i by 1 to move algorithm diagonally downward
                    j++;
                    if (j == A - 1) // if at bottom rail, loop is broken so algorithm can move toward 'peak'
                        break;
                }
            
                if (j == A-1) { //if reaches bottom (before returning to A-B)
                    while (1) { //loop to bring it back to A-B
                        grid[i][j] = 1; // sets targeted array element to '1'
                        i++; // incriments i by 1 to move algorithm right
                        j--; // decrements j by 1 to move algorithm up
                        if (j == A - B) // if at 'peak' break loop so pattern can proceed downward again
                            break;
                    }
                    if (j == A - B) { // if it reaches A-B
                        while (1) { //bring it back to bottom rail
                            grid [i][j] = 1; // sets targeted array element to '1'
                            i++; // incriments both j and i by 1 to move algorithm diagonally downward
                            j++;
                            if (j == A - 1) // if at bottom rail break so algorithm can move back to top
                                break;
                        }
                    }
                }
            }
            
            if (j == A - 1) { // if at bottom after coming down from peak
                while (1) { // loop executes following lines until break statement is met
                    grid[i][j] = 1; // sets targeted array element to '1'
                    i++; // incriments i by 1 to move algorithm right
                    j--; // decrements j by 1 to move algorithm up
                    if (j == 0) // if at top, break so algorithm can continue downward
                        break;
                }
            }
        }
        
        // ----PRINT VISUAL REPRESENTATION OF ARRAY (for debugging)----
        
             for (j = 0; j < A; j++) { // two for loops which run through each element and print it to debugging file
                 fprintf (debugFile, "\n");
                 for (i = 0; i < strlen(message); i++) {
                     fprintf(debugFile, "%d ", grid[i][j]);
                 }
             }
             fprintf (debugFile, "\n\n");

            
        
        // ----START ASSIGNING CHARACTERS TO ARRAY CHARACTERS WITH '1'----
        
        i = 0; // resets coordinates to (0,0) so algortithm starts from top right again
        j = 0;
        
        while (i < strlen(message)) { // repeats process for every column
            while (j < A) { // moves through grid row by row
                if (grid[i][j] == 1) {
                    grid[i][j] = message[i]; // sets every character previously set to 1 to the corresponding message character
                    j++; // incriments j by 1 to move algorthm gradually downward
                    if (i == length) // if at end of string, break looping
                    break;
                }
                else {
                    j++; // incriments j by 1 to move algorthm gradually downward
                    if (i == length) // if at end of string, break looping
                    break;
                }
            }
            i++; // incriments i by 1 to move algorithm right
            j = 0; // resets j to 0 as algorithm moves to next column
        }

        
        // ----PRINT VISUAL REPRESENTATION OF ARRAY (for debugging)----
        
                for (j = 0; j < A; j++) { // two for loops which pass through every element of the 2D array and prints it to the debug file
                    fprintf (debugFile, "\n");
                    for (i = 0; i < strlen(message); i++) {
                        if (grid[i][j] == 0)
                            fprintf(debugFile, "- ");
                        else
                            fprintf(debugFile, "%c ", grid[i][j]);
                    }
                }
                fprintf (debugFile, "\n\n");
        
        i = 0; // resets coordinates to (0,0) so algortithm starts from top right again
        j = 0;
        key = 0; // resets key to zero so cipherTet string can be written to in order

        
        
        
        
        
        // ----READ VALUES ROW BY ROW AND PRINT ENCRIPTED TEXT TO FILE----
        
        char buffer [strlen(message)];
                
        while (j < A) {
            for (i = 0; i < strlen(message); i++) {
                if (grid[i][j] != 0) {
                    buffer [key] = grid [i][j];
                    key++;
                    if (key == strlen(message))
                    break;
                }
            }
            j++;
            if (key == strlen(message))
                break;
        }
        
        cipherText[length] = '\0'; // sets last character of cipherText and buffer strings to null
        buffer[(length - 1)] = '\0';
        strcpy(cipherText, buffer); // copies contents of buffer string to cipherText string (proved essential during debugging)
        
        // following lines are for debugging purposes
        fprintf(debugFile, "length of string is: %d\n\n\n", length);
        fprintf(debugFile, "%s\n", cipherText);
        fprintf(debugFile, "\n\n");
        fclose(debugFile);
        
    }
    
    // START OF DECRIPTION
    
    if (dir == 1) { // dir is passed from main and is one if decryption is selected
    
        key = 0; // resets key to zero so strings can be written from beginning
        char grid[strlen(cipherText)][A]; // establishes 2D array responsible for holding message in correct order
        fprintf(debugFile, "\n\n%s\n\n", cipherText); // used for debugging

        // ----RESET ALL VALUES IN ARRAY TO 0 AND PRINT VISUAL REPRESENTATION----
        
        fprintf(debugFile, "decrypting:\n"); // used for debugging
        
        for (j = 0; j < A; j++) { //two nested 'for' loops move through all values in grid array
            fprintf (debugFile, "\n"); // used for debugging
            for (i = 0; i < length; i++) {
                grid [i][j] = 0; // sets each grid element to zero
                fprintf(debugFile, "%d ", grid[i][j]); // prints visual representation of zeroed grid to debug file, used for debugging
            }
        }
        fprintf (debugFile, "\n"); // used for debugging
        
        // ----SET VALUES WHICH WILL CONTAIN CHARACTER TO '1'----
        
        j = 0; //resets both coordinates to zero so algorithm starts from (0,0)
        i = 0;
        
        while (i < length) { // repeats process for every column until message length is reached
            
            if (j == 0) { //if at very top
                while (1) { //while loop repeats lines until break condition is met
                    grid[i][j] = 1; // sets targeted array element to '1'
                    i++; // incriments both j and i by 1 to move algorithm diagonally downward
                    j++;
                    if (j == A - 1) // if at bottom rail, loop is broken so algorithm can move toward 'peak'
                        break;
                    if (i == length) // if at end of string, break looping
                        break;
                }
            
                if (j == A-1) { //if reaches bottom (before returning to A-B)
                    while (1) { //loop to bring it back to A-B
                        grid[i][j] = 1; // sets targeted array element to '1'
                        i++; // incriments i by 1 to move algorithm right
                        j--; // decrements j by 1 to move algorithm up
                        if (j == A - B) // if at 'peak' break loop so pattern can proceed downward again
                            break;
                        if (i == length) // if at end of string, break looping
                        break;
                    }
                    if (j == A - B) { // if it reaches A-B
                        while (1) { //bring it back to bottom rail
                            grid[i][j] = 1; // sets targeted array element to '1'
                            i++; // incriments both j and i by 1 to move algorithm diagonally downward
                            j++;
                            if (j == A-1) // if at bottom rail break so algorithm can move back to top
                                break;
                            if (i == length) // if at end of string, break looping
                            break;
                        }
                    }
                }
            }
            if (j == A - 1) { // if at bottom after coming down from peak
                while (1) { // loop executes following lines until break statement is met
                    grid[i][j] = 1; // sets targeted array element to '1'
                    i++; // incriments i by 1 to move algorithm right
                    j--; // decrements j by 1 to move algorithm up
                
                    if (j == 0) // if at top, break so algorithm can continue downward
                        break;
                    if (i == length) // if at end of string, break looping
                    break;
                }
            }
        }
        
        // ----PRINT VISUAL REPRESENTATION OF ARRAY (for debugging)----
        
        for (j = 0; j < A; j++) { // two for loops which run through each element and print it to debugging file
            fprintf (debugFile, "\n");
            for (i = 0; i < length; i++) {
                fprintf(debugFile, "%d ", grid[i][j]);
            }
        }
        fprintf (debugFile, "\n\n");
         
        // ----START ASSIGNING CHARACTERS TO ARRAY ELEMENTS WITH '1'----
        
        i = 0; // resets coordinates to (0,0) so algortithm starts from top right again
        j = 0;
        key = 0; // resets key to zero so strings can be written from beginning

        fprintf(debugFile, "encrypted string is: %s", cipherText); // used for debugging
        
        while (j < A) { // moves through grid row by row
            while (i < length) { // repeats process for every column
                if (grid[i][j] != 0) {
                    grid[i][j] = cipherText[key]; // sets every character previously set to 1 to the corresponding encrypted character
                    i++; // incriments i by 1 to move algorithm right
                    key++; // incrimnet key so next character can be placed correctly
                }
                else
                    i++; // incriments i by 1 to move algorithm right
            }
            i = 0; // resets i to 0 as algorithm moves to next row
            j++; // incriments i by 1 to move algorithm right
            
        }
        
        // ----PRINT VISUAL REPRESENTATION OF ARRAY (for debugging)----
        
                for (j = 0; j < A; j++) { // two for loops which pass through every element of the 2D array and prints it to the debug file
                    fprintf (debugFile, "\n");
                    for (i = 0; i < length; i++) {
                        if (grid[i][j] == 0)
                            fprintf(debugFile, "- ");
                        else
                            fprintf(debugFile, "%c ", grid[i][j]);
                    }
                }
                fprintf (debugFile, "\n\n");
        
        i = 0; // resets coordinates to (0,0) so algortithm starts from top right again
        j = 0;
        key = 0; // resets key to zero so cipherTet string can be written to in order
        
        char buffer [length]; // establishes buffer string with same length as message

        // ----READ VALUES COLUMN BY COLUMN AND PRINT DECRIPTED TEXT----

        for (i = 0; i < length; i++) { // moves algorthm horizontally across through each column until at end of message
            for (j = 0; j < A; j++) { // moves algorithm vertically down through each row until at bottom of grid
                if (grid[i][j] != 0) {
                    message[key] = grid[i][j]; // if array element contains character, place character into message string
                    buffer[key] = grid[i][j]; // also place character into buffer string (proved essential during debugging)
                    key++; // incrimnet key so next character can be placed correctly
                }
            }
        }
 
        message[length] = 0; // sets last character of message and buffer strings to null
        buffer[length] = 0;
        strcpy(message, buffer); // copies contents of buffer string to message string (proved essential during debugging)
        
        // following lines are for debbugging purposes
        fprintf(debugFile, "\n\n");
        fprintf(debugFile, "%d\n\n\n", length);
        fprintf(debugFile, "%s\n", message);
        fprintf(debugFile, "%s", buffer);
        fprintf(debugFile, "\n\n");
        
        }
    fclose (debugFile);
}
