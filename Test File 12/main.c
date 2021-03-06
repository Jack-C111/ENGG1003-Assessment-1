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
        char grid2[length][A];

        // RESET ALL VALUES IN ARRAY TO 0 AND PRINT VISUAL REPRESENTATION - WORKING
        
        printf("grid 2:\n");
        
        for (j = 0; j < A; j++) { //2 nested 'for' loops to reset all values in grid to 0, also prints visual representation
            printf ("\n");
            for (i = 0; i <= length; i++) {
                grid2 [i][j] = 0;
                printf("%d ", grid2[i][j]);
            }
        }
        printf ("\n");

        
        
        
        
        
        // SET VALUES WHICH WILL CONTAIN CHARACTER TO '1' - WORKING
        
        j = 0; //resets both coordinates to zero so algorithm starts from (0,0)
        i = 0;
        
        while (i < length) {
            
            if (j == 0) { //if at very top
                while (1) { //while loop moves values
                    grid2[i][j] = 1;
                    i++;
                    j++;
                    if (j == (A - 1))
                        break;
                    if (i == length)
                        break;
                }
            
                if (j == A-1) { //if reaches bottom first time
                    while (1) { //loop to bring it back to A-B
                        grid2[i][j] = 1;
                        i++;
                        j--;
                        if (j == A - B)
                            break;
                        if (i == length)
                        break;
                        
                    }
                    if (j == A - B) { // if it reaches A-B
                        while (1) { //bring it back to bottom
                            grid2[i][j] = 1;
                            i++;
                            j++;
                            if (j == A-1)
                                break;
                            if (i == length)
                            break;
                            
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
                    if (i == length)
                    break;
                }
            }
        
        }
        
        
        for (j = 0; j < A; j++) {
            printf ("\n");
            for (i = 0; i <= length; i++) {
                printf("%d ", grid2[i][j]);
            }
        }
        printf ("\n\n");
        
        
        
        //START ASSIGNING CHARACTERS TO ARRAY CHARACTERS WITH '1' - NOT WORKING
        
        i = 0;
        j = 0;
        key = 0;
        
        
        while (j < A) {
            while (i < length) {
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
                    for (i = 0; i <= length; i++) {
                        printf("%d ", grid2[i][j]);
                    }
                }
                printf ("\n\n");
        
        
        i = 0;
        j = 0;
        key = 0;

        // READ VALUES COLUMN BY COLUMN AND PRINT DECRIPTED TEXT - WORKING

        while (i <= length) {
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
