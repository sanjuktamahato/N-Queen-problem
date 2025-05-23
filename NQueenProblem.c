#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int N;
void printSolution(int** board)
{
	int i,j;
    for (i = 0; i < N; i++) 
	{
        for (j = 0; j < N; j++) 
		{
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
}
int** allocateBoard()
{
	int i;
    int** board = (int**)malloc(N * sizeof(int*));
    for (i = 0; i < N; i++) 
	{
        board[i] = (int*)malloc(N * sizeof(int));
    }
    return board;
}
bool* allocateBooleanArray(int size)
{
	int i;
    bool* array = (bool*)malloc(size * sizeof(bool));
    for (i = 0; i < size; i++) 
	{
        array[i] = false;
    }
    return array;
}
bool isSafe(int row, int col, bool* rows,bool* leftDiagonals, bool* rightDiagonals)
{
    if (rows[row] || leftDiagonals[row + col]
        || rightDiagonals[col - row + N - 1]) 
	{
  
        return false;
    }
    return true;
}
bool solve(int** board, int col, bool* rows,bool* leftDiagonals, bool* rightDiagonals)
{
	int i;
    if (col >= N) 
	{

        return true;
    }
    for (i = 0; i < N; i++) 
	{
        if (isSafe(i, col, rows, leftDiagonals,rightDiagonals)) 
		{
            rows[i] = true;
            leftDiagonals[i + col] = true;
            rightDiagonals[col - i + N - 1] = true;
            board[i][col] = 1;
            if (solve(board, col + 1, rows, leftDiagonals,rightDiagonals)) 
			{
                return true;
            }
            rows[i] = false;
            leftDiagonals[i + col] = false;
            rightDiagonals[col - i + N - 1] = false;
            board[i][col] = 0; 
        }
    }
    return false;
}

int main()
{
	int i;
    printf("Enter the number of rows for the square board: ");
    scanf("%d", &N);
    int** board = allocateBoard();
    bool* rows = allocateBooleanArray(N);
    bool* leftDiagonals = allocateBooleanArray(2 * N - 1);
    bool* rightDiagonals = allocateBooleanArray(2 * N - 1);
    if (solve(board, 0, rows, leftDiagonals,
              rightDiagonals)) {
        printf("Solution found:\n");
        printSolution(board);
    }
    else {
        printf("Solution does not exist\n");
    }
    for (i = 0; i < N; i++) {
        free(board[i]);
    }
    free(board);
    free(rows);
    free(leftDiagonals);
    free(rightDiagonals);

    return 0;
}