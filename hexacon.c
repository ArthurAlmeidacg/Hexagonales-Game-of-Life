/* testhexacon zum Testen der Belegaufgabe 5 */
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>

typedef struct{
    int x;
    int y;
}point_t;

point_t *hexagol(unsigned int esize, const point_t start[], unsigned int rounds);
// esize = Passe o comprimento da borda do campo de jogo.
//start é um array de point_t contendo as coordenadas de todas as células vivas da configuração inicial.
//O valor {INT_MIN, INT_MAX} é anexado ao array para marcar o final do array

// int main (int argc, char **args){
//     argc = 3;

//     if (argc != 3) return -1;

//     point_t startconf []={
//         /* Hier die gewünschten Zellkoordinaten eintragen */
//         { -3 , -2} ,{ -2 , -3} ,{ -2 ,1} ,{ -1 ,0} ,{0 , -1} ,{0 ,2} ,{1 , -2} ,{2 ,0} ,{2 ,3} ,{3 ,2} , {INT_MAX, INT_MAX}
//     };
//     //unsigned size = (unsigned) atoi(args [1]);
//     //unsigned rounds = (unsigned) atoi(args [2]);
//     int rounds = 2;
//     int size = 4;

//     point_t *res = hexagol (size, startconf, rounds);
//     printf (" Nach %u Runden sind folgende Zellen lebendig :\n",rounds );
//     for (int i =0; ( res [i].x != INT_MAX) || (res [i].y != INT_MAX ); i ++){
//         if (i !=0) printf (", ");
//         printf ("(%d ,%d)",res[i].x, res[i].y);
//     }
//     printf ("\n");
//     free ( res );
//     return 0;
// }

point_t *hexagol(unsigned int esize, const point_t start[], unsigned int rounds){
    
    int row_m = esize+(esize-1);
    int col_m = esize+(esize-1);
    int (*second_array)[col_m] = calloc(row_m, sizeof(*second_array));
    int (*array)[col_m] = calloc(row_m, sizeof(*array));
    int count_is_green = 0;
    int negative_esize = -1*esize;
    int count_size_end_struct = 0;
    int count_col = 0;
    int count_col_row = esize;
    int test = (esize*2)-1;
    
    for (int row = (esize-1); row != negative_esize; row--){
        for(int col = (esize-1); col != negative_esize; col--){
            if(row > 0){
                if(count_col < count_col_row){
                    second_array[row][col] = 0;
                    count_col++;
                }else{
                    second_array[row][col] = -1;
                        count_col++;
                }
            }else if (row == 0){
                second_array[row][col] = 0;
            }else{
                if(test >= count_col_row){
                    second_array[row][col] = -1;
                    test--;
                }else{
                    second_array[row][col] = 0;
                    test--;
                }
            }
        }

        if(row > 0){
            count_col_row++;
        }else if(row < 0){
            count_col_row--;
            test = (esize*2)-1;
        }
        count_col = 0;
    }

    // for (int row = (esize-1); row != negative_esize; row--){
    //     for(int col = (esize-1); col != negative_esize; col--){
    //         printf("%d ",second_array[row][col]);
    //     }
    //     printf("\n");
    // }

    for (int row = (esize-1); row != negative_esize; row--){
        for(int col = (esize-1); col != negative_esize; col--){
            array[row][col] = second_array[row][col];
        }
    }
    
        // Setzen 1 in das neue Array.
    for (int row = (esize-1); row != negative_esize; row--){
        for(int col = (esize-1); col != negative_esize; col--){
            for(int run_struct = 0; (start[run_struct].x != INT_MAX) || (start[run_struct].y != INT_MAX ); run_struct++){
                if(start[run_struct].x == row && start[run_struct].y == col){ 
                    second_array[row][col] = 1;  
                }  
            }
        }
    }

    for(int i = 0; i < rounds; i++){
        for (int row = (esize-1); row != negative_esize; row--){
            for(int col = (esize-1); col != negative_esize; col--){

                if(second_array[row][col] != -1){
                
                    if(second_array[row-1][col-1] == 1){
                        count_is_green++;
                    }
                    if(second_array[row-1][col] == 1){
                        count_is_green++;
                    }
                    if(second_array[row][col+1] == 1){
                        count_is_green++;
                    }
                    if(second_array[row+1][col+1] == 1){
                        count_is_green++;
                    }
                    if(second_array[row+1][col] == 1){
                        count_is_green++;
                    }
                    if(second_array[row][col-1] == 1){
                        count_is_green++;
                    }

                    if(count_is_green == 2){
                        array[row][col] = 1;
                        count_size_end_struct++;
                    }else{
                        array[row][col] = 0;
                    }
                    if(second_array[row][col] == 1){
                        if(count_is_green == 3){
                            array[row][col] = 1;
                            count_size_end_struct++;
                        }else if(count_is_green == 5){
                            array[row][col] = 1;
                            count_size_end_struct++;
                        }else{
                            array[row][col] = 0;
                        }
                    }
                    count_is_green = 0;
                }
            }
        }
            
        // Legen Sie das Array in das second_array, damit die nächste runde überprüft
        for(int row = (esize-1); row != negative_esize; row--){
            for(int col = (esize-1); col != negative_esize; col--){
                second_array[row][col] = array[row][col];
            }
        }
    }

    int count = 0;
    point_t *endConfig = calloc(count_size_end_struct, sizeof(*endConfig));

    for(int row = (esize-1); row != negative_esize; row--){
        for(int col = (esize-1); col != negative_esize; col--){
            if(array[row][col] == 1){
                endConfig[count].x = row;
                endConfig[count].y = col;   
                count++;
            }
        }
    }
    endConfig[count].x = INT_MAX;
    endConfig[count].y = INT_MAX;
    
    return endConfig;
}