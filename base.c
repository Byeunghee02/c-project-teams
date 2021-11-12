#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    FILE *fin = fopen("input.txt", "r");

    //입력 개수
    int readLine = 0;
    int a, b, readItem;
    readItem = fscanf(fin,"%d %d",&a, &b);
    while(readItem >= 0){
        readLine++;
        readItem = fscanf(fin,"%d %d",&a, &b);
    } 
    srand(time(NULL));
    
    //input list
    int ** inputList = (int**) malloc(sizeof(int*)*readLine);
    for (int i = 0; i < readLine; i++)
    {
        inputList[i] = (int*) malloc(sizeof(int)*2);
    }
    
    //matrix list
    int *** matrixList =(int***) malloc(sizeof(int**)*readLine);
    
    //input matrix
    for (int i = 0; i < readLine; i++)
    {
        int a, b;
        fscanf(fin,"%d %d",&a,&b);
        inputList[i][0] = a; inputList[i][1] = b;
        matrixList[i] = (int**) malloc(sizeof(int*)*b);
        for(int j = 0; j < b; j++){
            matrixList[i][j] = (int*) malloc(sizeof(int)*a);
        }
        for(int j = 0; j < b; j++){
            for(int k = 0; k < a; k++){
                matrixList[i][j][k] = rand() % 10 + 1;
                printf("%d~ ",matrixList[i][j][k]);
            }
        }
    }
    fclose(fin);
    FILE* fout = fopen("output.txt", "w+");
    for (int i = 0; i < readLine; i++)
    {
        fprintf(fout,"%d matrix\n", i+1);
        for (int j = 0; j < inputList[i][1]; j++)
        {
            for (int k = 0; k < inputList[i][0]; k++)
            {
                fprintf(fout,"%d ", matrixList[i][j][k]);
            }
            fprintf(fout,"\n");
        }
        
    }
    fclose(fout);
    printf("done");
    printf("%d",readLine);
    // for (int i = 0; i < readLine; i++)
    // {
    //     for (int j = 0; j < 2; j++)
    //     {
    //         printf("%d ", inputList[i][j]);
    //     }
        
    // }
    
}
