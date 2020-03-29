#include <stdio.h>
#include <stdlib.h>

int ctrl();
int brutal_solve(int pos);
void print_sudoku();
void load_example();
void modify_sudoku();
void erase_sudoku();
void exclusion_solve();
int  P[9][9];

int main()
{

    int choose = 1, i, j, ris, brutal_ris=-1;

    /*Init sudoku scheme*/
    for(i=0; i<9; i++)
        for(j=0; j<9; j++)
            P[i][j] = 0;

    /*Main menu*/
    while(choose!=0){
        print_sudoku();


        if(brutal_ris==0){
            printf("\nUNSOLVABLE SUDOKU!\n");
            brutal_ris=-1;
        }
        else{
            ris = ctrl(P);
            if(ris)
                printf("\nCorrect solution!\n");
            else
                printf("\nWrong/incomplete solution!\n\n");
        }

        printf("Choose:\n");
        printf("1 - Modify sudoku\n");
        printf("3 - Solve by exclusion\n");
        printf("4 - Solve by brutal force\n");
        printf("5 - Print sudoku\n");
        printf("6 - Erase sudoku\n");
        printf("7 - Load sudoku example\n");
        printf("0 - Exit.\n");
        printf("Choose: ");
        scanf("%d", &choose);

        switch (choose){

            case 1:
                modify_sudoku();
                break;

            case 3:
                exclusion_solve();

                break;
            case 4:
                brutal_ris = brutal_solve(0);
                break;
            case 5:
                print_sudoku();
                break;
            case 6:
                erase_sudoku();
                break;
            case 7:
                load_example();
                break;
            case 0:
                break;
            default:
                printf("Wrong command!\n");


        }
    }
    return 0;
}

/*check solution*/
int ctrl(){

    int ris=1, i, j,k, w,x, sum, mark[9];
    for(i=0; i<9; i++){
        for(k = 0; k<9; k++) mark[k] = 0;
        sum = 0;
        for(j=0; j<9; j++)
            mark[P[i][j]-1] = 1;
        for(k = 0; k<9; k++) sum+=mark[k];
        if(sum!=9){
            ris = 0;
            break;
        }
    }
    for(x=0; x<=6; x+=3){
        for(w=0; w<=6; w+=3){
            for(k = 0; k<9; k++) mark[k] = 0;
            sum = 0;
            for(i=0; i<3; i++)
                for(j=0; j<3; j++)
                    mark[ P[i+x][j+w]-1  ] = 1;

            for(k = 0; k<9; k++) sum+=mark[k];
            if(sum!=9){
                ris = 0;
                break;
            }
        }
    }

    return ris;
}

/*Solving part of sudoku with smart logic, as much as possible,
reducing the overload of the sequent brutal solving solution*/

/*
This exclusion_solve can teoritically let the sudoku semi-solved, for this reason a brutal solver is developed and can be called after this.
The brutal solver is always able to solve the sudoku in any situation.

The exclusion solve use a 3 dimensional matrix call "exclusion" for saving for each square the possible values assignable.
Every time a new value is added into the sudoku scheme, this matrix is reevaluated.
*/
void exclusion_solve(){

    int exclusion[9][9][9], flag;
    int i, j, k, r, c, value, iter1, iter2, squareR, squareC, squareRlim, squareClim;
    int rToAdd, cToAdd;
    for(i=0;i<9;i++)
        for(j=0;j<9;j++)
            for(k=0;k<9;k++)
                exclusion[i][j][k]=1;

    /*this flag will be used for checking if a new value has been inserted in the Sudoku scheme*/
    flag = 1;
    while(flag){
        flag = 0;
        for(i=0;i<9;i++){
            for(j=0;j<9;j++){
                if(P[i][j]!=0){
                    value = P[i][j] - 1;
                    for(k=0;k<9;k++)
                        exclusion[i][j][k]=0;
                    for(r=0;r<9;r++)
                        exclusion[r][j][value]=0;
                    for(c=0;c<9;c++)
                        exclusion[i][c][value]=0;
                    r = i/3;
                    r = r*3;
                    c = j/3;
                    c = c*3;
                    for(iter1=0;iter1<3;iter1++){
                        for(iter2=0;iter2<3;iter2++){
                            exclusion[r][c][value]=0;
                            c++;
                        }
                        r++;
                        c = j/3;
                        c = c*3;
                    }
                }
            }
        }
        for(iter1=0;iter1<9&&flag==0;iter1++){
            for(r=0;r<9&&flag==0;r++){
                value = 0;
                for(c=0;c<9&&flag==0;c++){
                    if(exclusion[r][c][iter1]!=0){
                        rToAdd=r;
                        cToAdd=c;
                    }
                    value += exclusion[r][c][iter1];
                }
                if(value == 1){
                    P[rToAdd][cToAdd] = iter1+1;
                    flag=1;
                }
            }

            for(c=0;c<9&&flag==0;c++){
                value = 0;
                for(r=0;r<9&&flag==0;r++){
                    if(exclusion[r][c][iter1]!=0){
                        rToAdd=r;
                        cToAdd=c;
                    }
                    value += exclusion[r][c][iter1];
                }
                if(value == 1){
                    P[rToAdd][cToAdd] = iter1+1;
                    flag=1;
                }
            }

            for(squareR=0;squareR<3&&flag==0;squareR++){
                for(squareC=0;squareC<3&&flag==0;squareC++){
                    value =0;
                    squareRlim = squareR*3;
                    squareClim = squareC*3;
                    for(r=squareRlim;r<squareRlim+3&&flag==0;r++){
                        for(c=squareClim;c<squareClim+3&&flag==0;c++){
                            if(exclusion[r][c][iter1]!=0){
                                rToAdd=r;
                                cToAdd=c;
                            }
                            value += exclusion[r][c][iter1];
                        }
                    }
                    if(value == 1){
                        P[rToAdd][cToAdd] = iter1+1;
                        flag=1;
                    }
                }
            }
        }
    }

    return;
}

/*

The brutal solver develop a powerset, where every combination of numbers for the missing values is tested up to find the correct one.
The function is developed as a recursive function.
*/

int brutal_solve(int pos){
    int i, j, ris = 0, k, flag = 1;

    while(P[pos/9][pos%9]!=0)  pos++;
    if(pos>=81){
        ris = 1;
        return ris;
    }

    for(k=1; k<=9; k++){
        flag = 1;
        for(i=0; i<9;i++){
            if(P[pos/9][i]==k) flag = 0;
            if(P[i][pos%9]==k) flag = 0;
        }
        for(i=(pos/9)-((pos/9)%3); i<(pos/9)-((pos/9)%3)+3; i++)
            for(j=(pos%9)-((pos%9)%3); j<(pos%9)-((pos%9)%3)+3; j++)
                if(P[i][j]==k) flag = 0;
        if(flag){
            P[pos/9][pos%9] = k;
            ris = brutal_solve(pos +1);
            if(ris==0)
                P[pos/9][pos%9] = 0;
            else
                return ris;

        }
    }
    return ris;
}

void print_sudoku(){

    int i, j;
    system("cls");
    printf("Welcome to the Sudoku Solver! (by Luca Mazzucco)\n");
    printf("\nScheme: \n");
     for(i=0; i<9; i++){
        for(j=0; j<9; j++){
            printf("%d ", P[i][j]);
            if((j+1)%3==0&&j!=8) printf(" | ");
        }
        printf("\n");
        if((i+1)%3==0) printf("-----------------------\n");

     }
    return;
}

void load_example(){
    P[0][0]=5;
    P[0][1]=3;
    P[0][4]=7;
    P[1][0]=6;
    P[1][3]=1;
    P[1][4]=9;
    P[1][5]=5;
    P[2][1]=9;
    P[2][2]=8;
    P[2][7]=6;
    P[3][0]=8;
    P[3][4]=6;
    P[3][8]=3;
    P[4][0]=4;
    P[4][3]=8;
    P[4][5]=3;
    P[4][8]=1;
    P[5][0]=7;
    P[5][4]=2;
    P[5][8]=6;
    P[6][1]=6;
    P[6][6]=2;
    P[6][7]=8;
    P[7][3]=4;
    P[7][4]=1;
    P[7][5]=9;
    P[7][8]=5;
    P[8][4]=8;
    P[8][7]=7;
    P[8][8]=9;
    return;
}


void modify_sudoku(){
    int r, c, n;
    while(n!=0){
        printf("Insert row, column, number(0 0 0 to terminate): ");
        scanf("%d%d%d", &r, &c, &n);
        if(r==0) break;
        P[--r][--c] = n;
    }
    print_sudoku();
    return;
}

void erase_sudoku(){
    int i, j;
    for(i=0; i<9; i++)
        for(j=0; j<9; j++)
            P[i][j] = 0;

    return;
}
