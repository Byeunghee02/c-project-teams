#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//행렬만들고 저장하기
int main(){
    int arr[] = {2,2,3,2,3};
    int line=4;
    int** mats;
    int*** mat_list = malloc(sizeof(int**) * line);
    srand(time(NULL));
    for(int i=0; i<line; i++){
    int p = arr[i];
    int q = arr[i+1];
    mats = (int**)malloc(sizeof(int*) * p);
        for (int j = 0; j < p; j++) {
            mats[j] = (int*)malloc(sizeof(int) * q);
        }
        for (int k = 0; k < p; k++) {
            for (int l = 0; l < q; l++) {
                mats[k][l] = rand() % 5 + 1;
            }
        }
    mat_list[i] = (int**)mats;      //mat_list의 인덱스에 k가 아니라 i가 들어가야하고 인자가 k인 반복문에 있으면 제대로 저장이 안된다. 추가적인 설명은 내일 하도록 하겠음
        //행렬출력
        for (int h = 0; h < p; h++) {
            for (int k = 0; k < q; k++) {
                printf("%d ",mats[h][k]);
            }
            printf("\n");
        }printf("\n");
    }
    
    //행렬곱하기
    int*** mat_mid = malloc(sizeof(int**) * line-1);
    for(int a=0; a<line-1; a++){
        int** mat_new = malloc(sizeof(int**) * arr[0]);
        //mat_mid[a] = (int**)mat_new;
        for(int b=0; b<arr[0]; b++){
            mat_new[b] = (int*)malloc(sizeof(int) * arr[a+2]);
        }
        if(a==0){
            for(int c=0; c<arr[0]; c++){
                for(int d=0; d<arr[a+2]; d++){
                    mat_new[c][d]=0;
                    for(int e=0; e<arr[a+1]; e++){
                        mat_new[c][d] += mat_list[a][c][e] * mat_list[a+1][e][d];
                    }
                }
            }
            mat_mid[a] = mat_new;
        }
        else{
            for(int c=0; c<arr[0]; c++){
                for(int d=0; d<arr[a+2]; d++){
                    mat_new[c][d]=0;
                    for(int e=0; e<arr[a+1]; e++){
                        mat_new[c][d] += mat_mid[a-1][c][e] * mat_list[a+1][e][d];
                    }
                }
            }
            mat_mid[a] = mat_new;
        }
    }
    for(int k=0; k<arr[0]; k++){
        for(int n=0; n<arr[line]; n++){             //for문 안에 arr의 인덱스가 line-1이라서 출력이 이상하게 되고 있었음, 인덱스를 line으로 고치니 해결됨
            printf("%d ", mat_mid[line-2][k][n]);
        }
        printf("\n");
    }
}