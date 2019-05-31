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
#define COLOR_MAX_VALUE 255

void PrintRowMessage();
void PrintColumnMessage();
void PrintEnterMatrix();
int **create_matrix(int row, int column);
int **get_matrix_from_user(int **image, int n, int m);
void PrintImageMessage();
void PrintPrompt();
void average(int **image, int n, int m, int **target);
int get_adjacent_cells_average(int **image, int n, int m, int row, int column);
void rotate(int **image, int n, int m, int **target, int d);
void negative(int **image, int n, int m, int **target);
void print_image(int **image, int n, int m);
void PrintLeftRotation();
void PrintRightRotation();
void PrintAveraging();
void PrintNegating();
void free_mem(int **image, int n);

/*-------------------------------------------------------------------------
  This program takes as input a two dimensional matrix representing an
  image.
  The program is able to modify the image according to a determined set of
  actions.
 -------------------------------------------------------------------------*/
int main()
{
    int n = 0, m = 0;
    int **image = NULL, **target = NULL;
    char user_action;

    PrintRowMessage();
    scanf("%d", &n);
    PrintColumnMessage();
    scanf("%d", &m);
    image = create_matrix(n, m);
    if (image == NULL)
    {
        return 0;
    }
    PrintEnterMatrix();
    get_matrix_from_user(image, n, m);
    PrintImageMessage();
    print_image(image, n, m);
    PrintPrompt();
    scanf(" %c", &user_action);
    switch (user_action)
    {
    case OP_ROTATE_LEFT:
        target = create_matrix(m, n);
        if (target == NULL)
        {
            free_mem(image, n);
            return 0;
        }
        rotate(image, n, m, target, 1);
        free_mem(target, m);
        break;
    case OP_ROTATE_RIGHT:
        target = create_matrix(m, n);
        if (target == NULL)
        {
            free_mem(image, n);
            return 0;
        }
        rotate(image, n, m, target, 0);
        free_mem(target, m);
        break;

    case OP_AVERAGE:
        target = create_matrix(n, m);
        if (target == NULL)
        {
            free_mem(image, n);
            return 0;
        }
        average(image, n, m, target);
        free_mem(target, n);
        break;
    case OP_NEGATE:
        target = create_matrix(n, m);
        if (target == NULL)
        {
            free_mem(image, n);
            return 0;
        }
        negative(image, n, m, target);
        free_mem(target, n);
        break;
    }

    free_mem(image, n);

    return 0;
}

/*
  Function to free memory used by image matrix.
*/
void free_mem(int **image, int n)
{
    for (int i = 0; i < n; i++)
    {
        free(image[i]);
    }
    free(image);
}

/*
  Function to create a two dimensional dynamic matrix.
*/
int **create_matrix(int row, int column)
{
    int **image = (int **)malloc(row * sizeof(int *));
    if (image == NULL)
    {
        return image;
    }
    for (int i = 0; i < row; i++)
    {
        image[i] = malloc(column * sizeof(int));
        if (image[i] == NULL)
        {
            // There was an issue allocating the sub arrays, freeing already allocated memory.
            for (i -= 1; i >= 0; i--);
            {
                free(image[i]);
            }
            free(image);
            return image;
        }
    }
    return image;
}

/*
  Function to get values of image matrix from the user.
*/
int **get_matrix_from_user(int **image, int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &(image[i][j]));
        }
    }
    return image;
}

/*
  Function to calculate the average of all cells and their
  adjacent cells.
*/
void average(int **image, int n, int m, int **target)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            target[i][j] = get_adjacent_cells_average(image, n, m, i, j);
        }
    }
    PrintAveraging();
    print_image(target, n, m);
}

/*
  Function to check which cells are adjacent to the input cell in the matrix
  and calculate the average of those cells.
*/
int get_adjacent_cells_average(int **image, int n, int m, int row, int column)
{
    int sum = 0;
    int cells_count = 0;
    for (int i = -1; i < 2; i++)
    {
        if (row + i < 0 || row + i >= n)
        {
            continue;
        }
        for (int j = -1; j < 2; j++)
        {
            if (column + j < 0 || column + j >= m)
            {
                continue;
            }
            sum += image[row + i][column + j];
            cells_count++;
        }
    }
    return sum / cells_count;
}

/*
  Function to rotate the image matrix 90 degrees in the direction
  specified by the user.
*/
void rotate(int **image, int n, int m, int **target, int d)
{
    if (d == ROTATE_RIGHT)
    {
        // turn clockwise.
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                target[j][n - i - 1] = image[i][j];
            }
        }
        PrintRightRotation();
        print_image(target, m, n);
    }
    else if (d == ROTATE_LEFT)
    {
        // turn counter-clockwise.
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                target[m - j - 1][i] = image[i][j];
            }
        }
        PrintLeftRotation();
        print_image(target, m, n);
    }
}

/*
  Function to negate values of image matrix.
*/
void negative(int **image, int n, int m, int **target)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            target[i][j] = COLOR_MAX_VALUE - image[i][j];
        }
    }
    PrintNegating();
    print_image(target, n, m);
}

void print_image(int **image, int n, int m)
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            if (j != m - 1)
            {
                printf("%d\t", image[i][j]);
            }
            else
            {
                printf("%d", image[i][j]);
            }
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
