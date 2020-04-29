#include <stdio.h>
#include <stdlib.h>

int main() {

//    char * buffer = 0;
//    long length;
    char message[99];
    FILE * file = fopen ("textfile", "r");

    
    fgets(message, 99, file);
    
    printf("%s\n", message);
    
    
    
    /*if (f)
    {
      fseek (file, 0, SEEK_END);
      length = ftell (file);
      fseek (file, 0, SEEK_SET);
      buffer = malloc (length);
      if (buffer)
      {
        fread (buffer, 1, length, file);
      }
      fclose (file);
    }

    if (buffer)
    {
      
        
        printf("%c", *buffer);
        
        
        
        
        
        // start to process your data / extract strings here...
    }
    
    */
    return 0;
}
