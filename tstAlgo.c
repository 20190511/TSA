#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>


void print_debug(int index[][32])
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 32; j++)
            printf("%d ", index[i][j]);
        printf("\n");
    }
    printf("\n");
}


int find_key(int array[5] , int key)
{
    for (int i = 0 ; i < 5 ; i++)
        if(array[i] == key)
            return i;
    return 100;
}

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

void print_path(int path[][5])
{
    int row[5] = { 0, };
    int col[5] = { 0, };
    int count = 0;
    printf("\n\n ++++++++ print Path : Start ++++++++ \n\n");
    for (int i = 0; i < 25; i++) {
        //hi , ro 레지스터 착안
        int lo = i / 5;    //행 
        int hi = i % 5;    //열
        if (path[lo][hi] == 1)
        {
            row[count] = lo;
            col[count] = hi;
            count++;
        }
    }
    int node = 0;
    for (int j = 0; j < 5; j++)
    {
        printf("%d->", row[node]+1);
        int next = row[node];
        node = find_key(row, col[next]);
    }
    printf("%d 순환" , row[node]+1);


    printf("\n\n ++++++++ print Path : End ++++++++ \n\n");
}

// 일차원 행렬 -> 2차원 행렬로 변환해주는 함수 김병기 교수님 방식 착안
void matrixFolder(int origin_one[25], int origin_two[][5])
{
    for (int i = 0; i < 25; i++) {
        int lo = i / 5;    //행 
        int hi = i % 5;    //열
        origin_two[lo][hi] = origin_one[i];
    }
}

//{v1,v2,v3,v4,v5}를 {이진수화}시켜서 이진수에 해당하는 인덱스로 반환
void makeMatrix(int matrix_v[][32], int binaryColumn[5], int v, int value)
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

//이진수 -> 십진수로 바꿔줌
int binaryToTen(int binaryColumn[5])
{
    int sum = 0;
    for (int i = 0; i < 5; i++)
        sum += pow(2, i) * binaryColumn[i];
    return sum;
}






//max 행렬 경로 구하는 함수 , 최소 거리를 출력해줌.
int matrixPath(int matrix[][5], int index[][32], int minimumPath[4])
{
    //{v0,v1,v2,v3,v4}순으로 값 넣기 -> 2진수화
    int binaryColumn[5] = { 0, };
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
        for (int b = a + 1; b < 5; b++)
        {
            resetMatrix(binaryColumn);
            binaryColumn[a] = 1;
            binaryColumn[b] = 1;
            for (int j = 1; j < 5; j++)
            {
                if (j != a && j != b)
                {
                    //index 값 이진수 -> 10진수로 바꾸기
                    int col = pow(2, b);

                    int value = matrix[j][a] + index[a][col];

                    int col2 = pow(2, a);
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
        for (int s = 1; s < 5; s++)
            if (s != e)
            {
                binaryColumn[s] = 1;
            }

        int minVal[3] = { 0, };
        int k = 0;
        int first_row = e;
        for (int j = 1; j < 5; j++)
        {
            int binaryCal[5] = { 0, };
            if (j != first_row)
            {
                for (int v = 1; v < 5; v++)
                    if (v != j && v != e)
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
        minimumPath[i - 1] = matrix[0][i] + index[i][col];
    }

    for (int i = 0; i < 4; i++)
        printf("%d ", minimumPath[i]);
    printf("\n");

    int minimum = 1000;
    minimum = minimumPath[0];
    if (minimum > minimumPath[1])
        minimum = minimumPath[1];
    if (minimum > minimumPath[2])
        minimum = minimumPath[2];
    if (minimum > minimumPath[3])
        minimum = minimumPath[3];

    return minimum;

}


void copy_array(int a[], int b[])
{
    for (int i = 0; i < 5; i++)
        a[i] = b[i];
}

//경로 출력 함수 , 역추적
void findPath(int matrix[][5], int index[][32], int path[][5], int minimum, int minimumPath[4])
{
    int arr[5] = { 0, };
    //w[1][i] = index[i][A-i] , A = {4}에서 역추적
    int index4 = 100;
    for (int i = 1; i < 5; i++)
    {
        if (minimum == minimumPath[i - 1])
        {
            index4 = i;
            path[0][i] = 1;
        }
    }
    for (int j = 1; j < 5; j++)
        if (j != index4)
            arr[j] = 1;

    // A ={3} 에서 역추적
    int index_3num;
    int takeKey2[3] = { 0, };
    int takeNum[3] = { 0, };
    int binary[5] = { 0. };
    int count = 0;
    for (int i = 1; i < 5; i++)
    {
        // i 는 path의 행의 번호가됨
        if (arr[i] != 1)
            index_3num = i;
    }
    for (int i = 1; i < 5; i++)
    {
        copy_array(binary, arr);
        if (arr[i] == 1)
        {
            int sub_index = i;
            binary[i] = 0;
            takeKey2[count] = i;
            int bi = binaryToTen(binary);
            takeNum[count] = matrix[index_3num][i] + index[i][bi];
            count++;
        }
    }

    //최소가 되는 값의 행, 열값을 알아냄.
    int min3 = takeNum[0];
    int index3 = takeKey2[0];
    if (min3 > takeNum[1])
        index3 = takeKey2[1];
    if (min3 > takeNum[2])
        index3 = takeKey2[2];

    path[index_3num][index3] = 1;  /*arr[1][2]*/
    arr[index3] = 0;                 //해당 인덱스의 arr값 0으로 전환 -> arr에 1이 두개 존재




    //A = {2} 역추적 , index3가 path의 행의 인덱스가 됨. -> A ={1}까지 안가고 여기서 다 구할 수 있음.
    int takeKey3[2] = { 0, };
    count = 0;
    for (int i = 1; i < 5; i++)
    {
        if (arr[i] == 1)
        {
            takeKey3[count] = i;
            count++;
        }
    }
    int a = takeKey3[0];
    int b = takeKey3[1];
    int col_a = pow(2, a);
    int col_b = pow(2, b);
    int value1 = matrix[index3][a] + index[a][col_b];
    int value2 = matrix[index3][b] + index[b][col_a];

    int min2 = value1;
    int min2_index = a;
    int min1_index = b;
    if (value1 > value2)
    {
        min2_index = b;
        min1_index = a;
    }


    path[index3][min2_index] = 1;         /* path[2][4]*/
    path[min2_index][min1_index] = 1;     /*path[4][3]*/
    path[min1_index][0] = 1;              /*path[3][0]*/

    print_array(path);
}


/* 실행 함수들 */

int main()
{
    /*필요한배열 세팅*/
    int origin_two[5][5] = { 0, };
    int origin_one[25] = { 0,8,13,18,20,3,0,7,8,10,4,11,0,10,7,6,6,7,0,11,10,6,2,1,0 };
    matrixFolder(origin_one, origin_two);
    int matrix_v[5][32] = { 0, };
    int path[5][5] = { 0, };
    int minimumPath[4] = { 0, };
    int minimum = matrixPath(origin_two, matrix_v, minimumPath);


    printf("\n\n");
    findPath(origin_two, matrix_v, path, minimum, minimumPath);
    print_path(path);
    return 0;
}