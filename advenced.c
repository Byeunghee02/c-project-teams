#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

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
    }
    fclose(fin);

    //optimized multiplication
    //dp create
    int **dp = (int **)calloc(readLine + 1, sizeof(int *));
    for (int i = 0; i < readLine + 1; i++)
        dp[i] = (int *)calloc(readLine + 1, sizeof(int));

    //backTrack create
    int ***backTrack = (int ***)calloc(readLine + 1, sizeof(int **));
    for (int i = 0; i < readLine + 1; i++)
        backTrack[i] = (int **)calloc(readLine + 1, sizeof(int *));
    for (int i = 0; i < readLine + 1; i++)
        for (int j = 0; j < readLine + 1; j++)
            backTrack[i][j] = (int *)calloc(4, sizeof(int));

    //exploring dp & backTracking
    for (int i = 1; i < readLine + 1; i++)
        for (int j = 1; i + j < readLine + 1; j++)
        {
            dp[j][i + j] = INT_MAX;
            for (int k = j; k <= i + j - 1; k++)
            {
                int tmp = dp[j][k] + dp[k + 1][i + j] + inputList[j - 1][0] * inputList[k][0] * inputList[i + j - 1][1];
                if (tmp < dp[j][i + j])
                {
                    dp[j][i + j] = tmp;
                    backTrack[j][i + j][0] = j;
                    backTrack[j][i + j][1] = k;
                    backTrack[j][i + j][2] = k + 1;
                    backTrack[j][i + j][3] = i + j;
                }
            }
        }

    //optimized order
    int *optimizedOrder = (int *)malloc(sizeof(int) * readLine);
    int idx1 = 1, idx2 = readLine, idxo = 0;
    for (int i = 0; i < readLine - 1; i++)
    {
        int val1 = backTrack[idx1][idx2][0];
        int val2 = backTrack[idx1][idx2][1];
        int val3 = backTrack[idx1][idx2][2];
        int val4 = backTrack[idx1][idx2][3];
        if (val1 == val2)
        {
            optimizedOrder[idxo] = val1;
            idxo++;
        }
        else
        {
            idx1 = val1;
            idx2 = val2;
        }
        if (val3 == val4)
        {
            optimizedOrder[idxo] = val3;
            idxo++;
        }
        else
        {
            idx1 = val3;
            idx2 = val4;
        }
    }

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
    //create array
    idxo = readLine - 1;
    int firstIdx = optimizedOrder[idxo] - 1;
    int **tempMatrix = (int **)calloc(inputList[firstIdx][0], sizeof(int *));
    for (int i = 0; i < inputList[firstIdx][0]; i++)
    {
        tempMatrix[i] = (int *)calloc(inputList[firstIdx][1], sizeof(int));
    }
    for (int i = 0; i < inputList[firstIdx][0]; i++)
        for (int j = 0; j < inputList[firstIdx][1]; j++)
        {
            tempMatrix[i][j] += matrixList[firstIdx][i][j];
        }

    int **result = (int **)calloc(inputList[0][0], sizeof(int *));
    for (int j = 0; j < inputList[0][0]; j++)
    {
        result[j] = (int *)calloc(inputList[readLine - 1][1], sizeof(int));
    }
    int frontIdx, backIdx, midIdx;
    if (optimizedOrder[idxo - 1] < optimizedOrder[idxo])
    {
        frontIdx = optimizedOrder[idxo - 1] - 1;
        backIdx = optimizedOrder[idxo] - 1;
    }
    else
    {
        backIdx = optimizedOrder[idxo - 1] - 1;
        frontIdx = optimizedOrder[idxo] - 1;
    }
    midIdx = backIdx;
    idxo--;

    //multiple
    int multipleCounter = 0;
    for (int i = 0; i < readLine - 1; i++)
    {
        //resultMatrix init
        int **resultMatrix = (int **)calloc(inputList[frontIdx][0], sizeof(int *));
        for (int j = 0; j < inputList[frontIdx][0]; j++)
        {
            resultMatrix[j] = (int *)calloc(inputList[backIdx][1], sizeof(int));
        }
        //multiply
        if (optimizedOrder[idxo] < optimizedOrder[idxo + 1])
        {
            for (int j = 0; j < inputList[frontIdx][0]; j++)
                for (int k = 0; k < inputList[backIdx][1]; k++)
                    for (int t = 0; t < inputList[midIdx][0]; t++)
                    {
                        resultMatrix[j][k] += matrixList[backIdx][j][t] * tempMatrix[t][k];
                        multipleCounter++;
                    }
        }
        else
        {
            for (int j = 0; j < inputList[frontIdx][0]; j++)
                for (int k = 0; k < inputList[backIdx][1]; k++)
                {
                    for (int t = 0; t < inputList[midIdx][1]; t++)
                    {
                        resultMatrix[j][k] += tempMatrix[j][t] * matrixList[backIdx][t][k];
                        multipleCounter++;
                    }
                }
        }

        //tempMatrix copy
        free(tempMatrix);
        int **tempMatrix = (int **)calloc(inputList[frontIdx][0], sizeof(int *));
        for (int j = 0; j < inputList[frontIdx][0]; j++)
        {
            tempMatrix[j] = (int *)calloc(inputList[backIdx][1], sizeof(int));
        }
        for (int j = 0; j < inputList[frontIdx][0]; j++)
            for (int k = 0; k < inputList[backIdx][1]; k++)
            {
                tempMatrix[j][k] = resultMatrix[j][k];
            }

        if (i == readLine - 2)
        {
            for (int j = 0; j < inputList[0][0]; j++)
                for (int k = 0; k < inputList[readLine - 1][1]; k++)
                {
                    result[j][k] = resultMatrix[j][k];
                }
            break;
        }

        idxo--;
        if (optimizedOrder[idxo] < optimizedOrder[idxo + 1])
        {
            midIdx = frontIdx;
            frontIdx = optimizedOrder[idxo] - 1;
        }
        else
        {
            midIdx = backIdx;
            backIdx = optimizedOrder[idxo] - 1;
        }
    }

    //result output
    FILE *fout = fopen(OUTPUT_FILE_NAME, "w+");
    fprintf(fout, "multiple counter: %d\n", multipleCounter);
    fprintf(fout, "optimized multiple counter: %d\n\n", dp[1][readLine]);
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
    printf("Done!");
}
