// SUBBSTITUTION CIPHER
#include <stdio.h>
#include <string.h>

int findSize(char filename[]); // declaration of function used to determine length of file

int main() {
    
    char cipherFilename[] = "Cipher";
    int pos = 0;
    int length = 0;
    char orderedAlphabet[26] = "ETAOINSRHDLUCMFYWGPBVKXQJZ";
    
    length = findSize(cipherFilename);
    
    FILE* cipherFile;
    cipherFile = fopen (cipherFilename, "r");
    
    
    
    char input[length];
    char buffer;
    
    while (pos < (length - 1)) {
        fscanf (cipherFile, "%c", &buffer);
        input[pos] = buffer;
        pos++;
    }

    input [pos] = 0;
    
    printf ("%s\n\n", input);
    
    pos = 0;
    int x;
    int count[26] = {0};
    
    while (input [pos] != '\0') {
        if ((input [pos] >= 'a') && (input [pos] <= 'z')) {
            x = input [pos] - 'a';
                    count[x]++;
        }
        pos++;
    }
    
    for (pos = 0; pos < 26; pos++)
        printf("%c occurs %d times\n", pos + 'a', count [pos]);
    
    buffer = 0;
    
    int runs = 0;
    while (runs < 1000) {
        
        
    }
    
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
