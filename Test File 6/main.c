#include <stdio.h>
#include <string.h>

int findSize(char filename[]);

int main() {
    
    char filename[] = "message";
    
    FILE *file;
    file = fopen(filename, "r"); //opening rail fence input file in read mode
    
    int length = 0;
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
    
//    int pos = 0;
    char messageinput, *inputpointer;
    inputpointer = &messageinput;
     
    while (!feof(file)) {
    
        messageinput = fscanf(file, "%c", &messageinput);
    
    printf("%c", messageinput);
    }
    
    printf("%c", messageinput);
    
    return 0;
}



    int findSize(char filename[]) { // function to determine length of file - WORKING
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
