#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>



//배열을 출력해줌
void print_array(int array[][5])
{
    for (int i = 0; i < 25; i++) {
        //hi , ro 레지스터 착안
        int lo = i / 5;    //행 
        int hi = i % 5;    //열
        if (hi == 0)
            printf("\n");
        printf("%d ", array[lo][hi]);
    }
    printf("\n\n");
}


// 일차원 행렬 -> 2차원 행렬로 변환해주는 함수
void matrixFolder(int origin_one[25], int origin_two[][5])
{
    for (int i = 0; i < 25; i++) {
        int lo = i / 5;    //행 
        int hi = i % 5;    //열
        origin_two[lo][hi] = origin_one[i];
    }
}

void makeMatrix(int matrix_v[][5], int binaryColumn[5], int v, int value)
{
    int col = 0;
    for (int i = 0; i < 5; i++)
        col += pow(2, i) * binaryColumn[i];
    matrix_v[v][col] = value;
}

//인덱스 리셋함수
void resetMatrix(int binaryColumn[5])
{
    for (int i = 0; i < 5; i++)
        binaryColumn[i] = 0;
}

int binaryToTen(int binaryColumn[5])
{
    int sum = 0;
    for (int i = 0; i < 5; i++)
        sum += pow(2, i) * binaryColumn[i];
    return sum;
}






//max 행렬 경로 구하는 함수
int matrixPath(int matrix[][5], int index[][5])
{
    //{v0,v1,v2,v3,v4}순으로 값 넣기 -> 2진수화
    int binaryColumn[5] = { 0, };
    int minimumPath[4] = { 0, };
    for (int i = 1; i < 5; i++)
    {
        //공집합이므로 0000-> 0임
        index[i][0] = matrix[i][0];
    }

    //A = {1개}
    for (int k = 1; k < 5; k++)
    {
        resetMatrix(binaryColumn);
        binaryColumn[k] = 1;
        for (int j = 1; j < 5; j++)
        {
            if (k != j)
            {
                //int col = binaryToTen(binaryColumn);
                /* 첫 코드라서 10진수 변환 필요 없음,*/
                int value = matrix[j][k] + index[k][0];
                makeMatrix(index, binaryColumn, j, value);
            }
        }
    }

    //A = {2개}
    //4개 중 2개를 골라 1로 변환
    for (int a = 1; a < 5; a++)
    {
        for (int b = a + 1; a < 5; a++)
        {
            resetMatrix(binaryColumn);
            binaryColumn[a] = 1;
            binaryColumn[b] = 1;
            for (int j = 1; j < 5; j++)
            {
                if (j != a && j != b)
                {
                    //index 값 이진수 -> 10진수로 바꾸기
                    int col = pow(2,b);
                    int value = matrix[j][a] + index[a][col];
                    int col2 = pow(2,a);
                    int value2 = matrix[j][b] + index[b][col2];
                    if (value > value2)
                        makeMatrix(index, binaryColumn, j, value2);
                    else
                        makeMatrix(index, binaryColumn, j, value);
                }
            }
        }
    }

    //A ={3개} , 반례 이용
    for (int e = 1; e < 5; e++)
    {
        
        resetMatrix(binaryColumn);
        for (int s = 1 ; s < 5 ; s++)
            if (s != e)
            {
                binaryColumn[s] = 1;
            }

        int minVal[3] = { 0, };
        int k = 0;
        int first_row = 0;
        for (int j = 1; j < 5; j++)
        { 
            int binaryCal[5] = { 0, };
            if (j == e)
            {
                first_row = j;
            }
            else
            {
                for (int v = 1 ; v < 5 ; v++)
                    if (v != j)
                    {
                        binaryCal[v] = 1;
                    }
                int key = binaryToTen(binaryCal);
                minVal[k] = matrix[first_row][j] + index[j][key];
                k++;
            }
        
        }   
        int final_value = minVal[0];
        if (final_value > minVal[1])
            final_value = minVal[1];
        if (final_value > minVal[2])
            final_value = minVal[2];
        makeMatrix(index, binaryColumn, first_row, final_value);
            
    }


    // A = {4개}
    for (int i = 1; i < 5; i++)
    {
        int bin[5] = { 0, };
        for (int j = 1; j < 5; j++)
            if (j != i)
                bin[j] = 1;
        int col = binaryToTen(bin);
        minimumPath[i-1] = matrix[0][i] + index[i][col];
    }
    
    int minimum = 1000;
    for (int i = 1; i < 4; i++)
    {
        minimum = minimumPath[i];
        if (minimum > minimumPath[i - 1])
            minimum = minimumPath[i - 1];
    }

    return minimum;

}


//경로 출력 함수
void findPath(int matrix[][5], int modified[][5], int path[][5])
{

}


/* 실행 함수들 */

int main()
{
    /*필요한배열 세팅*/
    int origin_two[5][5] = { 0, };
    int origin_one[25] = { 0,8,13,18,20,3,0,7,8,10,4,11,0,10,7,6,6,7,0,11,10,6,2,1,0 };
    matrixFolder(origin_one, origin_two);
    int matrix_v[5][32] = { 0, } ;
    matrixPath(origin_two, matrix_v);

    return 0;
}