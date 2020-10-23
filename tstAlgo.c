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


//�迭�� �������
void print_array(int array[][5])
{
    for (int i = 0; i < 25; i++) {
        //hi , ro �������� ����
        int lo = i / 5;    //�� 
        int hi = i % 5;    //��
        if (hi == 0)
            printf("\n");
        printf("%d ", array[lo][hi]);
    }
    printf("\n\n");
}


// ������ ��� -> 2���� ��ķ� ��ȯ���ִ� �Լ�
void matrixFolder(int origin_one[25], int origin_two[][5])
{
    for (int i = 0; i < 25; i++) {
        int lo = i / 5;    //�� 
        int hi = i % 5;    //��
        origin_two[lo][hi] = origin_one[i];
    }
}

void makeMatrix(int matrix_v[][32], int binaryColumn[5], int v, int value)
{
    int col = 0;
    for (int i = 0; i < 5; i++)
        col += pow(2, i) * binaryColumn[i];
    matrix_v[v][col] = value;
}

//�ε��� �����Լ�
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






//max ��� ��� ���ϴ� �Լ�
int matrixPath(int matrix[][5], int index[][32])
{
    //{v0,v1,v2,v3,v4}������ �� �ֱ� -> 2����ȭ
    int binaryColumn[5] = { 0, };
    int minimumPath[4] = { 0, };
    for (int i = 1; i < 5; i++)
    {
        //�������̹Ƿ� 0000-> 0��
        index[i][0] = matrix[i][0];
    }

    //A = {1��}
    for (int k = 1; k < 5; k++)
    {
        resetMatrix(binaryColumn);
        binaryColumn[k] = 1;
        for (int j = 1; j < 5; j++)
        {
            if (k != j)
            {
                //int col = binaryToTen(binaryColumn);
                /* ù �ڵ�� 10���� ��ȯ �ʿ� ����,*/
                int value = matrix[j][k] + index[k][0];
                makeMatrix(index, binaryColumn, j, value);
            }
        }
    }

    //A = {2��}
    //4�� �� 2���� ��� 1�� ��ȯ
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
                    //index �� ������ -> 10������ �ٲٱ�
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

    //A ={3��} , �ݷ� �̿� ---�����ʿ�
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
        int first_row = e;
        for (int j = 1; j < 5; j++)
        { 
            int binaryCal[5] = { 0, };
            if (j != first_row)
            {
                for (int v = 1 ; v < 5 ; v++)
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


    // A = {4��}
    for (int i = 1; i < 5; i++)
    {
        int bin[5] = { 0, };
        for (int j = 1; j < 5; j++)
            if (j != i)
                bin[j] = 1;
        int col = binaryToTen(bin);
        minimumPath[i-1] = matrix[0][i] + index[i][col];
    }
    
    for (int i = 0; i < 4; i++)
        printf("%d ", minimumPath[i]);
    printf("\n");

    int minimum = 1000;
    for (int i = 1; i < 4; i++)
    {
        minimum = minimumPath[i];
        if (minimum > minimumPath[i - 1])
            minimum = minimumPath[i - 1];
    }

    return minimum;

}


//��� ��� �Լ�
void findPath(int matrix[][5], int modified[][5], int path[][5])
{

}


/* ���� �Լ��� */

int main()
{
    /*�ʿ��ѹ迭 ����*/
    int origin_two[5][5] = { 0, };
    int origin_one[25] = { 0,8,13,18,20,3,0,7,8,10,4,11,0,10,7,6,6,7,0,11,10,6,2,1,0 };
    matrixFolder(origin_one, origin_two);
    int matrix_v[5][32] = { 0, } ;
    matrixPath(origin_two, matrix_v);

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 32; j++)
            printf("%d ", matrix_v[i][j]);
        printf("\n");
    }
        
    return 0;
}