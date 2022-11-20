#include <stdio.h>

int main() {
    int i,j,k;
    char puzzle[15][15];
    char character[2];
    char word[15];
    char result[15][15] = "*";
    
//Get Characters From User
    for (i = 0; i < 15; i++) {
        for (j = 0; j < 15; j++) {
            scanf("%s", character);
            puzzle[i][j] = character[0];
        }
    }

    scanf("%s", word);

    
    for (i = 0; i < 15; i++) {
        for (j = 0; j < 15; j++) {
            if(puzzle[i][j] == word[0]) {
                for(k = 1; word[k] >= 'A' && word[k] <= 'Z'; k++) {
                    
                    if (
                        puzzle[i-k][j] != word[k] && 
                        puzzle[i+k][j] != word[k] && 
                        puzzle[i][j+k] != word[k] && 
                        puzzle[i][j-k] != word[k] &&
                        puzzle[i+k][j+k] != word[k] &&
                        puzzle[i-k][j-k] != word[k] && 
                        puzzle[i+k][j-k] != word[k] &&
                        puzzle[i-k][j+k] != word[k] ) {
                        
                        break;
                    }
                    
                    //else if 
                
                }
            }
        }
    }
}

/*    
    for(i = 0; i<15; i++) {
        printf("%c", word[i]);
    }
*/

/*
    for (i = 0; i < 15; i++) {
        for (j = 0; j < 15; j++) {
            printf("%c", puzzle[i][j]);
        }
        printf("\n");
    }
*/
