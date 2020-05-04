#include <stdio.h>
#include <string.h>
#include <time.h>

void railFence(char *message, char *cipherText, int length, int A); // rail fence function declaration as specified in task
void railFence2(char *message, char *cipherText, int length, int A, int B, int dir); // two level rail fence function declaration as specified in task
void subCipher(int length); // function declaration for substitution cipher - only passed length of message
int findSize(char filename[]); // declaration of function used to determine length of file

int main(int argc, char *argv[]) {
    
    char decryptedFilename[] = "Message"; // variables for file names - makes it simpler to change files rather than if it was hard coded
    char encryptedFilename[] = "Cipher Text";
    char taskSelectionFilname[] = "Task Selection";
    char AFilename[] = "A";
    char BFilename[] = "B";
    
    FILE* taskSelectionFile;
    taskSelectionFile = fopen (taskSelectionFilname, "r");
    
    int menuSelection = 0; // variable for user to input menu selection
    int length = 0; // variable for length of message (determined by findSize function)
    
    // following 3 printf statements print menu text to stdout
    printf ("\n MAIN MENU:\n\n Make selection by inputing integer denoted before option.\n\n");
    printf (" 1. Encryption using classic rail-fence cipher\n 2. Encryption using 2-level rail-fence cipher\n 3. Decryption using 2-level rail-fence cipher\n 4. Decryption using substitution cipher\n");
    fscanf (taskSelectionFile, "%d", &menuSelection); // scans user input from file as an integer used for selecting menu item
    
    if ((menuSelection < 1) || (menuSelection > 4)) { // if selection is outside range of options
        
        printf ("\n    Invalid Integer between 1 and 5 must be placed in %s file. Replace integer and restart program.", taskSelectionFilname);
        char enter = 0;
        printf ("\n    Press ENTER to continue... ");
        while (enter != '\r' && enter != '\n') { // loop which proceeds only when newline char detected in stdin, gives user time to read menu
            enter = getchar();
        }
        return 1;
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
            
            FILE* taskSelectionFile; // opens task selection file in read mode
            taskSelectionFile = fopen (taskSelectionFilname, "r");
            
            FILE* AFile; // opens A file in read mode
            AFile = fopen (AFilename, "r");
            
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
            printf ("\n    Press ENTER to continue... ");
            fscanf (AFile, "%d", &A); // scans integer from file to use for number of rails
            char enter = 0;
            while (enter != '\r' && enter != '\n') { // loop which proceeds only when newline char detected in stdin, gives user time to read menu
                enter = getchar();
            }
            
            railFence(message, cipherText, length, A); // calls rail fence function, inputting the message, length of the message and number of rails (A). cipherText variable is used to return encrypted string from void function
            fprintf(encryptedFile, "%s", cipherText); // prints resultant encrypted message into Cipher Text file
            printf ("    Encrypted text has successfully been printed to the '%s' file.", encryptedFilename);
            
            fclose (encryptedFile); // closes both files used for input and output
            fclose (decryptedFile);
            fclose (taskSelectionFile);
            fclose (AFile);
            
            break;
        }
        
        case 2: { // TWO-LEVEL RAIL FENCE ENCRYPTION
            
            FILE* decryptedFile; // opens original message file in read mode
            decryptedFile = fopen (decryptedFilename, "r");
            
            FILE* encryptedFile; // opens output file in write mode
            encryptedFile = fopen (encryptedFilename, "w");
            
            FILE* taskSelectionFile; // opens task selection file in read mode
            taskSelectionFile = fopen (taskSelectionFilname, "r");
            
            FILE* AFile; // opens A file in read mode
            AFile = fopen (AFilename, "r");
            
            FILE* BFile; // opens B file in read mode
            BFile = fopen (BFilename, "r");
            
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
            
            char enter = 0;
            printf ("\n    Press ENTER to continue... ");
            while (enter != '\r' && enter != '\n') { // loop which proceeds only when newline char detected in stdin, gives user time to read menu
                enter = getchar();
            }
            fscanf (AFile, "%d", &A); // scans integer from file to use for height of grid/number of rails
            fscanf (BFile, "%d", &B); // scans integer from file to use for secondary height algorithm moves back up
            railFence2(message, cipherText, length, A, B, dir); // calls two level rail fence function, inputting the message, length of the message and number of rails (A). cipherText variable is used to return encrypted string from void function, dir is used to determine whether encryption or decryption has been selected by the user (in this case dir is set to 0 for encryption)
            fprintf(encryptedFile, "%s", cipherText); // prints resultant encrypted message into Cipher Text file
            printf ("    Encrypted text has successfully been printed to the '%s' file.", encryptedFilename);
            
            fclose (encryptedFile); // closes both files used for input and output
            fclose (decryptedFile);
            fclose (taskSelectionFile);
            fclose (AFile);
            fclose (BFile);
            
            break;
        }
        
        case 3: { // TWO LEVEL RAIL FENCE DECRYPTION
            
            FILE* encryptedFile; // opens original, encrypted message file in read mode
            encryptedFile = fopen (encryptedFilename, "r");
            
            FILE* decryptedFile; // opens output file in write mode, same file as the original decrypted message file
            decryptedFile = fopen (decryptedFilename, "w");
            
            FILE* debugFile; // opens debug file in write mode
            debugFile = fopen ("Debugging Visualisations", "w");
            
            FILE* taskSelectionFile; // opens task selection file in read mode
            taskSelectionFile = fopen (taskSelectionFilname, "r");
            
            FILE* AFile; // opens A file in read mode
            AFile = fopen (AFilename, "r");
            
            FILE* BFile; // opens B file in read mode
            BFile = fopen (BFilename, "r");
            
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
            char enter = 0;
            printf ("\n    Press ENTER to continue... ");
            while (enter != '\r' && enter != '\n') { // loop which proceeds only when newline char detected in stdin, gives user time to read menu
                enter = getchar();
            }
            fscanf (AFile, "%d", &A); // scans integer from stdin to use for height of grid
            fscanf (BFile, "%d", &B); // scans integer from stdin to use for secondary height algorithm moves back up
            railFence2(message, cipherText, length, A, B, dir); // calls two level rail fence function, inputting the encrypted message, length of the message and number of rails (A). message variable is used to return decrypted string from void function, dir is used to determine whether encryption or decryption has been selected by the user (in this case dir is set to 1 for decryption)
            fprintf(decryptedFile, "%s", message); // prints resultant encrypted message into Message file
            printf ("    Decrypted text has successfully been printed to the '%s' file.", decryptedFilename);
            
            fclose (encryptedFile); // closes all files
            fclose (decryptedFile);
            fclose (taskSelectionFile);
            fclose (AFile);
            fclose (BFile);
            fclose (debugFile);
            fclose (taskSelectionFile);
            
            break;
        }

        case 4: {
            
            FILE* encryptedFile; // opens original, encrypted message file in read mode
            encryptedFile = fopen (encryptedFilename, "r");
            
            FILE* debugFile; // opens debug file in write mode
            debugFile = fopen ("Debugging Visualisations", "w");
            
            length = findSize(encryptedFilename); // calls findSize function passing it the filename which is being used as input and sets returned integer as length variable
            fprintf (debugFile, "message length is: %d\n", length); // prints length of string to debug file (used for debugging)
            
            printf ("\n\n    Decryption using substitution cipher selected");
            char enter = 0;
            printf ("\n    Press ENTER to continue... ");
            while (enter != '\r' && enter != '\n') { // loop which proceeds only when newline char detected in stdin, gives user time to read menu
                enter = getchar();
            }
            
            subCipher(length); // calls function, passing it length of file containing the encrypted message
            
            printf ("    Decrypted text has successfully been printed to the '%s' file.", decryptedFilename);
            
            fclose (encryptedFile); // closes all files
            fclose (debugFile);
            
            break;
            
        }
            
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
    
    fclose (debugFile);
    fclose (logFile);
    
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
    
    char grid[(2 * length)][(2* A)]; // establishes 2D array responsible for holding message in correct order
    
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
    
    // ----PRINT VISUAL REPRESENTATION OF ARRAY (for debugging)----
           
                   for (j = 0; j < A; j++) { // two for loops which pass through every element of the 2D array and prints it to the debug file
                       fprintf (debugFile, "\n");
                       for (i = 0; i < strlen(message); i++) {
                           if (grid[i][j] == 0)
                               fprintf(debugFile, "- ");
                           else
                               fprintf(debugFile, "1 ");
                       }
                   }
                   fprintf (debugFile, "\n\n");
         
    
    // ----START ASSIGNING CHARACTERS TO ARRAY CHARACTERS WITH '1'----
    
    i = 0; // resets coordinates to (0,0) so algortithm starts from top right again
    j = 0;
    
    while (i < strlen(message)) { // repeats process for every column until message length is reached
        while (j < A) { // while and if loops sets every '1' in the given [i] column to its related character from the string
            if (grid[i][j] == 1) {
                grid[i][j] = message[i]; // sets relevant array elements to corresponding message character
                j++; // incriments j by 1 to move algorthm gradually downward
                if (i == strlen(message))
                break;
            }
            else {
                j++;
                if (i == strlen(message))
                break;
            }
        }
        i++; // moves algorithm to next column
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
    
    // ----READ VALUES ROW BY ROW AND PRINT ENCRIPTED TEXT----
    
    i = 0; // resets coordinates to (0,0) so algortithm starts from top right again
    j = 0;
    
    while (j < A) { // two while loops move across each row then move down another column to read encrypted message
        while (i < length) {
            if (grid[i][j] != 0) { // if array element contains character assign the character to the corresponding cipherText character
                cipherText[key] = grid[i][j];
                i++; // incriment column and key if character is added to cipherKey
                key++;
                if (i == strlen(message))
                    break;
            }
            else {
                i++; // move to next column if array element is zero
                if (i == strlen(message))
                    break;
            }
        }
        i = 0; // reset to start of row
        j++; // move to next column
    }

    cipherText [key] = 0;
    
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
        
        printf("%s", message);
        
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
        
        printf ("\n\nThe encrypted message is:\n%s\n\n\n", cipherText); // prints encrypted message to stdout
        
        // following lines are for debugging purposes
        fprintf(debugFile, "length of string is: %d\n\n\n", length);
        fprintf(debugFile, "%s\n", cipherText);
        fprintf(debugFile, "\n\n");
        fclose(debugFile);
        
    }
    
    // START OF DECRIPTION
    
    if (dir == 1) { // dir is passed from main and is one if decryption is selected
    
        key = 0; // resets key to zero so strings can be written from beginning
        char grid[2 * (strlen(cipherText))][(2 * A)]; // establishes 2D array responsible for holding message in correct order
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
        
        printf ("\n\nThe decrypted message is:\n%s\n\n\n", message); // prints decrypted message to stdout
        
        // following lines are for debbugging purposes
        fprintf(debugFile, "\n\n");
        fprintf(debugFile, "%d\n\n\n", length);
        fprintf(debugFile, "%s\n", message);
        fprintf(debugFile, "%s", buffer);
        fprintf(debugFile, "\n\n");
        
        }
    fclose (debugFile);
}

void subCipher(int length) {
    
        // initialise necessary strings used to open files
        char cipherFilename[] = "Cipher Text";
        char decryptedFilename[] = "Message";
        char keyFilename[] = "Key";
        
        // open necessary files in read or write modes
        FILE* cipherFile;
        cipherFile = fopen (cipherFilename, "r");
        
        FILE* decryptedFile;
        decryptedFile = fopen (decryptedFilename, "w");
        
        FILE* debugFile; // opens debug file in write mode
        debugFile = fopen ("Debugging Visualisations", "w");
        
        FILE* keyFile;
        keyFile = fopen (keyFilename, "w");
        
        // initialise strings to hold characters, where 'length' is length of input file and 26 is length of alphabet
        char input[length];
        char output[length];
        char buffer;
        char inputCopy[length];
        char buffer2[26];
        char orderedAlphabet[26] = "etaoinsrhdlucmfywgpbvkxqjz"; // string containing ordered list of letters from most to least common
        char alphabet[26] = "abcdefghijklmnopqrstuvwxyz";
        char orderedFrequencyAlphabet[26];
        
        // initialise counter variables, used for tracking positions of characters within strings
        int counter = 0;
        int x = 0;
        int y = 0;
        int a = 0;
        int pos = 0;
        int bufferpos = 0;
        
        
        while (pos < (length - 1)) { // while loop scans file character by character, then loads into input string.
            fscanf (cipherFile, "%c", &buffer);
            input[pos] = buffer;
            pos++;
        }

        input [pos] = 0; // terminates input string
        
        fprintf (debugFile, "Encrypted message:\n%s\n\n", input); // used for debugging
        
        pos = 0; // resets position counter so counter can begin from start of string
        
        int count[26] = {0};
        while (input [pos] != '\0') { // while loop moves through string until terminating string is found
            if ((input [pos] >= 'a') && (input [pos] <= 'z')) { // only counts lower case characters (i.e. ASCII values between 97 and 122)
                x = input [pos] - 'a'; // assigns number from 1 to 26 to each letter in alphabet
                        count[x]++; // increases value of array element at that position to denote how many times character occurs in string
            }
            pos++; // incriments pos to move to next character in input string
        }
        fprintf (debugFile, "In alphabetical order:\n"); // used for debugging
        for (pos = 0; pos < 26; pos++) {
            fprintf(debugFile, "%c occurs %d times\n", (pos + 'a'), count [pos]);
        }
            
        fprintf (debugFile, "\n\nCharacter frequency alphabet:\n"); // used for debugging
        for (a = 0; a < 26; a++) {
            fprintf (debugFile, "%c\n", orderedAlphabet [a]);
        }

        fprintf (debugFile, "\n\nIn order of frequency:\n"); // used for debugging

        for(a = 0; a < 26; a++) { // for loop ensures it is run 26 times so each letter in alphabet can be tested
            y = 0; // y reset to zero so testing can begin again otherwise only most frequent character will be counted
            for(x = 0; x < 26; x++) { // for loop test character against another and if it is more frequent it replaces it, continuting this process the most frequent number at the end will be y
                if(count[x] > count[y]) {
                    y = x;
                }
            }
            
            orderedFrequencyAlphabet[y] = alphabet[y]; // orderedFrequencyAlphabet is an array storing the ASCII values of characters, stored in order of their frequency.
            fprintf (debugFile, "%c occurs %d times           %c\n", (y + 'a'), count[y], orderedFrequencyAlphabet[y]); // count at y is largets frequency at letter y - used for debugging
            
            buffer2[bufferpos] = orderedFrequencyAlphabet [y]; // load characters into second string in order or frequency so it can be removed from string to not be counted again
            bufferpos++;
            
            count[y] = 0; // since y will be largest array element (of frequencies) at this point, remove it from the array so it is not counted again
        }
        
        fprintf(debugFile, "\n\n"); // used for debugging
        for (bufferpos = 0; bufferpos < 26; bufferpos++) {
            fprintf (debugFile, "%c\n", buffer2 [bufferpos]);
        }
        fprintf(debugFile, "\n\n"); // used for debugging
        
        for (a = 0; a < 26; a++) { // used for debugging
            fprintf (debugFile, "%c\n", orderedAlphabet [a]);
        }
         fprintf(debugFile, "\n\n"); // used for debugging
        
        for (a = 0; a < 26; a++) { // used for debugging
            fprintf (keyFile, "%c --- %c\n", buffer2 [a], orderedAlphabet [a]);
        }
        
        strcpy(inputCopy, input); // copy input string to another identical string so one can be modified
        
        for (counter = 0; counter < length; counter++) { // for loop runs through each character in the inputCopy string
            for (a = 0; a < 26; a++) { // for loop compares character from input copy string to all characters in buffer2 string to find character with same relative frequency
                if ((inputCopy [counter] >= 'a') && (inputCopy [counter] <= 'z')) { // if statement ensures only lowercase characters are modified
                    if (inputCopy [counter] == buffer2 [a]) // replaces encrypted character with character of same relative frequency
                        output [counter] = orderedAlphabet [a];
                }
                else {
                    output [counter] = input [counter]; // retains any characters which are not lowercase characters between a and z
                }
            }
        }
        
        output [counter] = '\0'; // terminates output string
        
        for (counter = 0; counter < length; counter++) { // used for debugging
            fprintf (decryptedFile, "%c", output [counter]);
        }

        // closes all opened files
        fclose (debugFile);
        fclose (keyFile);
        fclose (decryptedFile);
        fclose (cipherFile);
    }
