// SUBBSTITUTION CIPHER
#include <stdio.h>
#include <string.h>

int findSize(char filename[]); // declaration of function used to determine length of file

int main() {
    
    char cipherFilename[] = "Cipher";
    char decryptedFilename[] = "Decrypted";
    char keyFilename[] = "Key";
    int pos = 0;
    int length = 0;
    char orderedAlphabet[26] = "etaoinsrhdlucmfywgpbvkxqjz";
    char alphabet[26] = "abcdefghijklmnopqrstuvwxyz";
    char orderedFrequencyAlphabet[26];
    
    length = findSize(cipherFilename);
    
    FILE* cipherFile;
    cipherFile = fopen (cipherFilename, "r");
    
    FILE* decryptedFile;
    decryptedFile = fopen (decryptedFilename, "w");
    
    FILE* debugFile; // opens debug file in write mode
    debugFile = fopen ("Debugging Visualisations", "w");
    
    FILE* keyFile;
    keyFile = fopen (keyFilename, "w");
    
    
    char input[length];
    char output[length];
    char buffer;
    
    while (pos < (length - 1)) {
        fscanf (cipherFile, "%c", &buffer);
        input[pos] = buffer;
        pos++;
    }

    input [pos] = 0;
    
    fprintf (debugFile, "Encrypted message:\n%s\n\n", input);
    
    pos = 0;
    int x, y = 0, focusLetter; // array element counters
    int count[26] = {0};
    
    while (input [pos] != '\0') {
        if ((input [pos] >= 'a') && (input [pos] <= 'z')) {
            x = input [pos] - 'a';
                    count[x]++;
        }
        pos++;
    }
    fprintf (debugFile, "In alphabetical order:\n");
    for (pos = 0; pos < 26; pos++)
        fprintf(debugFile, "%c occurs %d times\n", (pos + 'a'), count [pos]);

    fprintf(debugFile, "\n\n");
    
    int a = 0,b = 0;
    
    fprintf (debugFile, "Character frequency alphabet:\n");
    for (a = 0; a < 26; a++) {
        fprintf (debugFile, "%c\n", orderedAlphabet [a]);
    }
    a = 0;
   
    fprintf(debugFile, "\n\n");
    
    fprintf (debugFile, "In order of frequency:\n");
    
    char buffer2[26];
    int bufferpos = 0;
    
    
    
    for(focusLetter = 0; focusLetter<26; focusLetter++) {
    y = 0;
    for(x=0; x<26; x++) {
        if(count[x] > count[y]) {
            y = x;
        }
    }
        orderedFrequencyAlphabet[y] = alphabet[y];
        // orderedFrequencyAlphabet is an array storing the ASCII values of characters, stored in order of their frequency.
        fprintf (debugFile, "%c occurs %d times           %c\n", (y + 'a'), count[y], orderedFrequencyAlphabet[y]);
        // count at y is largets frequency at letter y
        
        buffer2[bufferpos] = orderedFrequencyAlphabet [y];
        bufferpos++;
        
            count[y] = 0;
            b++;
        
    }
    
    fprintf(debugFile, "\n\n");
    for (bufferpos = 0; bufferpos < 26; bufferpos++) {
        fprintf (debugFile, "%c\n", buffer2 [bufferpos]);
    }
    fprintf(debugFile, "\n\n");
    
    for (a = 0; a < 26; a++) {
        fprintf (debugFile, "%c\n", orderedAlphabet [a]);
    }
     fprintf(debugFile, "\n\n");
    
    for (a = 0; a < 26; a++) {
        fprintf (keyFile, "%c --- %c\n", buffer2 [a], orderedAlphabet [a]);
    }
    
    int counter = 0;
    char inputCopy[length];
    strcpy(inputCopy, input);
    
    for (counter = 0; counter < length; counter++) {
        for (a = 0; a < 26; a++) {
            if ((inputCopy [counter] >= 'a') && (inputCopy [counter] <= 'z')) {
                if (inputCopy [counter] == buffer2 [a])
                    output [counter] = orderedAlphabet [a];
            }
            else {
                output [counter] = input [counter];
            }
        }
    }
    
    output [counter] = '\0';
    
    for (counter = 0; counter < length; counter++) {
        fprintf (decryptedFile, "%c", output [counter]);
    }
    
    
    
    
    fclose (debugFile);
    fclose (keyFile);
    fclose (decryptedFile);
    fclose (cipherFile);
}

    int findSize(char filename[]) { // start of function definition to determine length of file

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
