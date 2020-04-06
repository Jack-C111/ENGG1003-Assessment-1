#include <stdio.h>

int main() {
    int menu_selection; //variable used to select from items on menu
    FILE *RF_input, *RF_output;
    
    RF_input = fopen("Rail Fence Input", "r"); //opening rail fence input file in read mode
    RF_output = fopen("Rail Fence Output", "w"); //opening rail fence output file in write mode
    
    printf("Select Task:\n\n(1) Rail Fence Encription\n(2) Exit\n\nEnter Selection: "); //menu text
    scanf("%d", &menu_selection); //user input on main menu
    
    switch(menu_selection) { //menu
        
        case(1): //rail fence encription menu selection
            printf("Rail Fence Encription Selected\n");
            break;
        
        case(2): //exit program menu selection
            printf("Program exited by user\n");
            return 0;
            break;
    
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
