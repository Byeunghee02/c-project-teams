#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    FILE *fin = fopen("input.txt", "r");

    //input count
    char *line = NULL;
    size_t len = 0;
    ssize_t readItem;
    int readLine = 0;
    int val1, val2;
    while ((readItem = getline(&line,&len,fin)) != EOF)
    {
        readLine++;
    }
    printf("%d\n", readLine);


    //input list
    int **inputList = (int **)malloc(sizeof(int *) * readLine);
    for (int i = 0; i < readLine; i++)
    {
        inputList[i] = (int *)malloc(sizeof(int) * 2);
    }
    for (int i = 0; i < readLine; i++)
    {
        fscanf(fin, "%d %d", &inputList[i][0], &inputList[i][1]);
        printf("%d %d ", inputList[i][0], inputList[i][1]);
    }
    fclose(fin);

    //matrix generation
    int ***matrixList = (int ***)malloc(sizeof(int **) * readLine);
    srand(time(NULL));
    for (int i = 0; i < readLine; i++)
    {
        val1 = inputList[i][0], val2 = inputList[i][1];
        matrixList[i] = (int **)malloc(sizeof(int *) * val1);
        for (int j = 0; j < val1; j++)
        {
            // printf ("%d %d", val1, val2);
            matrixList[i][j] = (int *)malloc(sizeof(int) * val2);
            for (int k = 0; k < val2; k++)
            {
                matrixList[i][j][k] = rand() % 10 + 1;
                // printf("%d,",matrixList[i][j][k]);
            }
        }
    }

    FILE *fout = fopen("output.txt", "w+");
    for (int i = 0; i < readLine; i++)
    {
        fprintf(fout, "%d matrix", i+1);
        for (int j = 0; j < inputList[i][0]; j++)
        {
            for (int k = 0; k < inputList[i][1]; k++)
            {
                fprintf(fout, "%d " , matrixList[i][j][k]);
            }
            fprintf(fout, "\n");
        }
        fprintf(fout, "\n");
    }
    
    fclose(fout);
}
