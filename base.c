#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define INPUT_FILE_NAME "input.txt"
#define OUTPUT_FILE_NAME "input_sol.txt"

int main()
{
    FILE *fin = fopen(INPUT_FILE_NAME, "r");

    //input count
    char *line = NULL;
    size_t len = 0;
    ssize_t readItem;
    int readLine = 0;
    int val1, val2;
    while ((readItem = getline(&line, &len, fin)) != EOF)
    {
        readLine++;
    }
    printf("%d\n", readLine);
    fseek(fin, 0, SEEK_SET);

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
            matrixList[i][j] = (int *)malloc(sizeof(int) * val2);
            for (int k = 0; k < val2; k++)
            {
                matrixList[i][j][k] = rand() % 10 + 1;
            }
        }
    }

    //matrix multiple
    int **tempMatrix = (int **)calloc(inputList[0][0], sizeof(int *));
    for (int i = 0; i < inputList[0][0]; i++)
    {
        tempMatrix[i] = (int *)calloc(inputList[0][1], sizeof(int));
    }
    for (int i = 0; i < inputList[0][0]; i++)
        for (int j = 0; j < inputList[0][1]; j++)
        {
            tempMatrix[i][j] = matrixList[0][i][j];
        }

    int **result = (int **)calloc(inputList[0][0], sizeof(int *));
    for (int j = 0; j < inputList[0][0]; j++)
    {
        result[j] = (int *)calloc(inputList[readLine - 1][1], sizeof(int));
    }

    int multipleCounter = 0;
    for (int i = 0; i < readLine - 1; i++)
    {
        int **resultMatrix = (int **)calloc(inputList[0][0], sizeof(int *));
        for (int j = 0; j < inputList[i][0]; j++)
        {
            resultMatrix[j] = (int *)calloc(inputList[i + 1][1], sizeof(int));
        }
        for (int j = 0; j < inputList[0][0]; j++)
            for (int k = 0; k < inputList[i + 1][1]; k++){
                for (int t = 0; t < inputList[i + 1][0]; t++)
                {
                    resultMatrix[j][k] += tempMatrix[j][t] * matrixList[i + 1][t][k];
                    multipleCounter++;
                }
                printf("%d ", resultMatrix[j][k]);}
        free(tempMatrix);
        int **tempMatrix = (int **)calloc(inputList[0][0], sizeof(int *));
        for (int j = 0; j < inputList[i][0]; j++)
        {
            tempMatrix[j] = (int *)calloc(inputList[i + 1][1], sizeof(int));
        }
        for (int j = 0; j < inputList[0][0]; j++)
            for (int k = 0; k < inputList[i + 1][1]; k++)
            {
                tempMatrix[j][k] = resultMatrix[j][k];
            }
        if (i == readLine - 2)
        {
            for (int j = 0; j < inputList[0][0]; j++)
                for (int k = 0; k < inputList[readLine-1][1]; k++)
                {
                    result[j][k] = resultMatrix[j][k];
                }
        }
    }

    //result output
    FILE *fout = fopen(OUTPUT_FILE_NAME, "w+");
    fprintf(fout, "%d\n", multipleCounter);
    fprintf(fout, "Output Matrix\n\n");
    for (int i = 0; i < inputList[0][0]; i++)
    {
        for (int j = 0; j < inputList[readLine - 1][1]; j++)
        {
            fprintf(fout, "%d ", result[i][j]);
        }
        fprintf(fout, "\n");
    }
    fprintf(fout, "\n");
    for (int i = 0; i < readLine; i++)
    {
        fprintf(fout, "Input Matrix %d\n\n", i + 1);
        for (int j = 0; j < inputList[i][0]; j++)
        {
            for (int k = 0; k < inputList[i][1]; k++)
            {
                fprintf(fout, "%d ", matrixList[i][j][k]);
            }
            fprintf(fout, "\n");
        }
        fprintf(fout, "\n");
    }

    fclose(fout);
}
