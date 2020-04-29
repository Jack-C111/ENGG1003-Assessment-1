#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    
    FILE *RF_input, *RF_output;
    RF_input = fopen("Rail Fence Input", "r"); //opening rail fence input file in read mode
    RF_output = fopen("Rail Fence Output", "w"); //opening rail fence output file in write mode
    
    
    size_t length_written; //variable to record how many characters have been written
                
                char RF_array, *RF; //initialise pointer to rail fence array
                RF = &RF_array;
                
                char c;
               
    if (RF_input == NULL) { //checks to see if input file exists and prints error if it does not
                            perror("error");
                        }
                else
                    printf ("file loaded successfully\n\n"); //continues with rail fence encription

    //length_written = strlen(RF_input);
    
    printf("%c", strlen(RF_input));
                
   /* while (fgetc(RF_input) != EOF) {
        c = fgetc(RF_input);
        printf("%c", c);
    }
    
    */
    
    
    
    /*
    
    
                    do {
                        c = fgetc (RF_input) ; // reading the file character by character
                    printf("%c", c);
                    
    //                if (feof(RF_input)) {
    //                    printf("message length is: %d\n", length_written);
    //                    break;
    //                }
                    
                    length_written++;
                        
                }
                while (fgetc(RF_input) != EOF);
                printf("message length is: %d\n", length_written);
                
    
    */
    
    return 0;
}
