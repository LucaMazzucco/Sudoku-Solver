#include <stdio.h>
#include <stdlib.h>

int ctrl(int P[9][9]);
int solve(int pos);
void print(int P[9][9]);

int  P[9][9];

int main()
{

    int scelta = 1, i, j, r, c, n, ris, M[9][9];

    while(scelta!=0){
        printf("Scegli:\n");
        printf("1 - Carica nuovo sudoku;\n");
        printf("2 - Carica soluzione e controlla;\n");
        printf("3 - Risolvi;\n");
        printf("0 - Uscita.\n");
        printf("Scelta: ");
        scanf("%d", &scelta);
        switch (scelta){

            case 1:
                for(i=0; i<9; i++)
                    for(j=0; j<9; j++)
                        M[i][j] = 0;
                while(n!=0){
                    printf("Inserisci riga, colonna, numero(0 per terminare): ");
                    scanf("%d%d%d", &r, &c, &n);
                    M[--r][--c] = n;
                }
                system("cls");
                printf("Griglia inserita:\n\n");
                for(i=0; i<9; i++){
                    for(j=0; j<9; j++){
                        printf("%d ", M[i][j]);
                        P[i][j] = M[i][j];
                        if((j+1)%3==0&&j!=8) printf(" | ");
                    }
                    printf("\n");
                    if((i+1)%3==0) printf("-----------------------\n");
                }
                break;

            case 2:
                for(i=0; i<9; i++)
                    for(j=0; j<9; j++)
                    {
                        if(P[i][j]==0){
                            printf("Posizione %d %d = : ", i+1, j+1);
                            scanf("%d", &n);
                            P[i][j] = n;
                        }
                    }
                    ris = ctrl(P);
                    if(ris)
                        printf("\nSoluzione corretta!\n");
                    else
                        printf("\nSoluzione errata!\n");

                break;
            case 3:
                ris = solve(0);
                break;
            case 0:
                break;
            default:
                printf("Valore non corretto!\n");


        }
    }
    return 0;
}

int ctrl(int P[9][9]){

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

int solve(int pos){
    int i, j, ris = 0, k, flag = 1;
    if(pos>=81){
        ris = 1;
        print(P);
        return ris;
    }
    while(P[pos/9][pos%9]!=0)  pos++;
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
            ris = solve(pos +1);
            P[pos/9][pos%9] = 0;
            if(ris) return ris;
        }}
    return ris;
}

void print(int P[9][9]){

    int i, j;
    system("cls");
    printf("\nSoluzione: \n");
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
