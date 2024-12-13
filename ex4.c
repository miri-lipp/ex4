/******************
Name:
ID:
Assignment:
*******************/
#include <stdio.h>
#include <string.h>
#define DIMENSION 20
#define ROW 5
#define COLUMN 5
void task1_robot_paths();
int CalculatePath(int column, int row, int result);
void task2_human_pyramid(int size1, int size2);
float HumanPyramid(float weight[][COLUMN], int column, int row, int size1, int size2);
void task3_parenthesis_validator();
int ParenthesisValidation(int openCircle, int openCurvy, int openSquare, int openTriangle);
void task4_queens_battle(int size);
void task5_crossword_generator();


int main()
{
    int task = -1;
    do
    {
        printf("Choose an option:\n"
               "1. Robot Paths\n"
               "2. The Human Pyramid\n"
               "3. Parenthesis Validation\n"
               "4. Queens Battle\n"
               "5. Crossword Generator\n"
               "6. Exit\n");

        if (scanf("%d", &task))
        {
            switch (task)
            {
            case 1:
                task1_robot_paths();
                break;
            case 2:
                task2_human_pyramid(ROW, COLUMN);
                break;
            case 3:
                task3_parenthesis_validator();
                //scanf("%*s");
                break;
            case 4:
                task4_queens_battle(DIMENSION);
                break;
            case 5:
                task5_crossword_generator();
                break;
            case 6:
                printf("Goodbye!\n");
                break;
            default:
                printf("Please choose a task number from the list.\n");
                break;
            }
        }
        else
        {
            scanf("%*s");
        }

    } while (task != 6);
}

void task1_robot_paths()
{
    int column, row;
    int result = 1;
    printf("Please enter the coordinates of the robot (column, row):\n");
    scanf("%d%d", &column, &row);
    if (column < 0 || row < 0) {
        printf("The total number of paths the robot can take to reach home is: %d\n", result);
        return;
    }
    result = CalculatePath(column, row, result);
    printf("The total number of paths the robot can take to reach home is: %d\n", result);
}

int CalculatePath(int column, int row, int result) {
    if (column == 0 && row == 0)
        return result;
    if (column == 0)
        return CalculatePath(column, row -1, result + 1);
    if (row == 0)
        return CalculatePath(column -1, row, result + 1);
    return CalculatePath(column - 1, row, result + 1);
}

void task2_human_pyramid(int size1, int size2)
{
    float weight[size1][size2];
    float result = 0;
    printf("Please enter the weights of the cheerleaders: \n");
    for (int i = 0; i < size1; i++) {
        for (int j = 0; j <= i; j++) {
            scanf("%f", &weight[i][j]);
            if (weight[i][j] < 0) {
                printf("Negative weights are not supported.\n");
                return;
            }
        }
    }
    for (int i = 0; i < size1; i++) {
        for (int j = 0; j <= i; j++) {
            result = HumanPyramid(weight, j, i, size1, size2);
            printf("%.2f ", result);
        }
        printf("\n");
    }
}

float HumanPyramid(float weight[][COLUMN], int column, int row, int size1, int size2) {
    float resultLeft = 0;
    float resultRight = 0;
    if (column == 0 && row == 0)
        return weight[row][column];
    if (column >= 0 && row < size1 && row > 0)
        resultLeft =  0.5 * HumanPyramid(weight, column - 1, row - 1, size1, size2);
    if (column <= row)
        resultRight = 0.5 * HumanPyramid(weight, column, row - 1, size1, size2);
    return weight[row][column] + resultLeft + resultRight;
}

void task3_parenthesis_validator()
{
    int openCurvy = 0;
    int openCircle = 0;
    int openSquare = 0;
    int openTriangle = 0;
    printf("Please enter a term for validation:\n");
    scanf("%*c");
    if (ParenthesisValidation(openCircle, openCurvy, openSquare, openTriangle))
        printf("The parentheses are balanced correctly.\n");
    else
        printf("The parentheses are not balanced correctly.\n");
}

int ParenthesisValidation( int openCircle, int openCurvy, int openSquare, int openTriangle) {
    char validation;
    scanf("%c", &validation);
    if (validation == '\n')
        return openCircle == 0 && openCurvy == 0 && openSquare == 0 && openTriangle == 0;
    if (validation == '[')
        return ParenthesisValidation(openCircle, openCurvy, openSquare + 1, openTriangle);
    if (validation == ']') {
        if (openSquare > 0)
            return ParenthesisValidation(openCircle, openCurvy, openSquare - 1, openTriangle);
        return 0;
    }
    if (validation == '(')
        return ParenthesisValidation(openCircle + 1, openCurvy, openSquare, openTriangle);
    if (validation == ')') {
        if (openCircle > 0)
            return ParenthesisValidation(openCircle - 1, openCurvy, openSquare, openTriangle);
        return 0;
    }
    if (validation == '{')
        return ParenthesisValidation(openCircle, openCurvy + 1, openSquare, openTriangle);
    if (validation == '}') {
        if (openCurvy > 0)
            return ParenthesisValidation(openCircle, openCurvy - 1, openSquare, openTriangle);
        return 0;
    }
    if (validation == '<')
        return ParenthesisValidation(openCircle, openCurvy, openSquare, openTriangle + 1);
    if (validation == '>') {
        if (openTriangle > 0)
            return ParenthesisValidation(openCircle, openCurvy, openSquare, openTriangle - 1);
        return 0;
    }

    ParenthesisValidation(openCircle, openCurvy, openSquare, openTriangle);
}



void task4_queens_battle(int size)
{
    int dimension;
    char board[size][size];
    printf("Please enter the board dimensions:\n");
    scanf("%d", &dimension);
    printf("Please enter the %d*%d puzzle board\n", dimension, dimension);
    scanf("%*c");
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++)
            scanf(" %c", &board[i][j]);
    }
}

void task5_crossword_generator()
{
    // Todo
}