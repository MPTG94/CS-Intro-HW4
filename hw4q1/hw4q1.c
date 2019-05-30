/*-------------------------------------------------------------------------
  Include files:
--------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>



/*=========================================================================
  Constants and definitions:
==========================================================================*/

#define ROTATE_LEFT 1
#define ROTATE_RIGHT 0
#define OP_ROTATE_LEFT 'L'
#define OP_ROTATE_RIGHT 'R'
#define OP_AVERAGE 'V'
#define OP_NEGATE 'N'

void PrintRowMessage();
void PrintColumnMessage();
void PrintEnterMatrix();
void get_matrix_from_user(int* image, int n, int m);
void PrintImageMessage();
void PrintPrompt();
void average(int* image, int n, int m, int* target);
void rotate(int* image, int n, int m, int* target, int d);
void negative(int* image, int n, int m, int* target);
void print_image(int* image, int n, int m);
void PrintLeftRotation();
void PrintRightRotation();
void PrintAveraging();
void PrintNegating();
/*-------------------------------------------------------------------------
  This program takes as input a two dimensional matrix representing an
  image.
  The program is able to modify the image according to a determined set of
  actions.
 -------------------------------------------------------------------------*/
int main()
{
    int n = 0, m = 0;
    int *image = NULL, *target = NULL;
    char user_action;
    PrintRowMessage();
    scanf("%d", &n);
    PrintColumnMessage();
    scanf("%d", &m);
    image = (int*)malloc(n * m * sizeof(int));
    if (image == NULL)
    {
        return 0;
    }
    target = (int*)malloc(n * m * sizeof(int));
    if (target== NULL)
    {
        return 0;
    }
    PrintEnterMatrix();
    get_matrix_from_user(image, n, m);
    PrintImageMessage();
    print_image(image, n, m);
    PrintPrompt();
    scanf(" %c", &user_action);
    switch(user_action)
    {
    case OP_ROTATE_LEFT:
        rotate(image, n, m, target, 1);
        PrintLeftRotation();
        print_image(target, m, n);
        break;
    case OP_ROTATE_RIGHT:
        rotate(image, n, m, target, 0);
        PrintRightRotation();
        print_image(target, m, n);
        break;

    case OP_AVERAGE:
        average(image, n, m, target);
        PrintAveraging();
        print_image(target, n, m);
        break;
    case OP_NEGATE:
        negative(image, n, m, target);
        PrintNegating();
        print_image(target, n, m);
        break;

    }
    free(image);
    free(target);
    return 0;
}

/*
  Function to get values of image matrix from the user.
*/
void get_matrix_from_user(int* image, int n, int m)
{
    int count = 0, num = 0;
    while (count < n*m)
    {
        scanf("%d", &num);
        *(image+count) = num;
        count++;
    }
}

void average(int* image, int n, int m, int* target)
{
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            int cells_count = 1;
            int sum = *(image + i + j);
            if(adjacent_cell(image, n, m, i - 1, j - 1))
            {
                sum += *(image + i - 1 + j - 1);
                cells_count++;
            }
            if(adjacent_cell(image, n, m, i - 1, j))
            {
                sum += *(image + i - 1 + j);
                cells_count++;
            }
            if(adjacent_cell(image, n, m, i - 1, j + 1))
            {
                sum += *(image + i - 1 + j + 1);
                cells_count++;
            }
            if(adjacent_cell(image, n, m, i, j - 1))
            {
                sum += *(image + i + j - 1);
                cells_count++;
            }
            if(adjacent_cell(image, n, m, i, j + 1))
            {
                sum += *(image + i + j + 1);
                cells_count++;
            }
            if(adjacent_cell(image, n, m, i + 1, j - 1))
            {
                sum += *(image + i + 1 + j - 1);
                cells_count++;
            }
            if(adjacent_cell(image, n, m, i + 1, j))
            {
                sum += *(image + i + 1 + j);
                cells_count++;
            }
            if(adjacent_cell(image, n, m, i + 1, j + 1))
            {
                sum += *(image + i + 1 + j + 1);
                cells_count++;
            }
            *(target + i +j) = sum/cells_count;
        }
    }

}

/*void get_adjacent_cells_average(int* image, int n, int m, int* target, int count)
{
    int sum = *(image + count);
    int cells = 1;
    if (count - m > 0)
    {
        sum += *(image + count -m);
        cells++;
    }
    if (count - m - 1> 0)
    {
        sum += *(image + count - m - 1);
        cells++;
    }
    if (count + m < m*n)
    {
        sum += *(image + count + m);
        cells++;
    }
    if (count + m - 1 < m*n)
    {
        sum += *(image + count + m - 1);
        cells++;
    }
    //if (count - 1 > 0 && (count - 1) % )
}*/

/*
  Function to rotate the image matrix 90 degrees in the direction
  specified by the user.
*/
void rotate(int* image, int n, int m, int* target, int d)
{
    if (d == 0)
    {
        // turn clockwise.
        int count = 0;
        for (int column = n - 1; column >= 0; column--)
        {
            for (int row = 0; row < m; row++)
            {
                *(target + row * n + column) = *(image + count);
                count++;
            }
        }
    }
    else if (d == 1)
    {
        // turn counter-clockwise.
        int count = 0;
        for (int column = 0; column < n; column++)

        {
            for (int row = m - 1; row >= 0; row--)
            {
                *(target + row * n + column) = *(image + count);
                count++;
            }
        }
    }
}

/*
  Function to negate values of image matrix.
*/
void negative(int* image, int n, int m, int* target)
{
    int count = 0;
    while (count < n*m)
    {
        *(target+count) = 255-*(image+count);
        count++;
    }
}

void print_image(int* image, int n, int m)
{
    int i,j;
    for(j=0; j < n; j++)
    {
        for (i =0; i < m; i++)
        {
            if (i != m-1)
                printf("%d\t", *( (image+j*m) + i));//image[j][i]
            else
                printf("%d", *( (image+j*m) + i));

        }
        printf("\n");
    }
}

void PrintRowMessage()
{
    printf("Enter the number of rows in your image matrix:\n");
}

void PrintColumnMessage()
{
    printf("Enter the number of columns in your image matrix:\n");
}

void PrintEnterMatrix()
{
    printf("Enter your matrix:\n");
}

void PrintImageMessage()
{
    printf("Your original image is:\n");
}

void PrintPrompt()
{
    printf("What you would like to do with your photo (L,R,V,N)?\n");
}

void PrintLeftRotation()
{
    printf("The image after left rotation:\n");
}

void PrintRightRotation()
{
    printf("The image after right rotation:\n");
}

void PrintAveraging()
{
    printf("The image after averaging:\n");
}

void PrintNegating()
{
    printf("The image after negating:\n");
}
