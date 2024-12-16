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
int ParenthesisValidationInput();
int ParenthesisValidation(char validation);
void task4_queens_battle();
int QueenPlacement(int coordinateX[], int coordinateY[], int color[], int size, int counter1, int counter2);
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
                scanf("%*s");
                break;
            case 4:
                task4_queens_battle();
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
    if (column == 0 && row == 0) // base case, there is only one path to go home if robot is already on 0, 0
        return result; //returns the number of paths calculated
    if (column == 0)
        return CalculatePath(column, row -1, result + 1); //if robot can go left then result + 1
    if (row == 0)
        return CalculatePath(column -1, row, result + 1); //if robot can go down the result + 1
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
    if (column == 0 && row == 0) //base case, if there are no cheerleaders above, then returns weight
        return weight[row][column];
    if (column >= 0 && row < size1 && row > 0)
        resultLeft =  0.5 * HumanPyramid(weight, column - 1, row - 1, size1, size2); //result of 0.5 weight of row above and column left
    if (column <= row)
        resultRight = 0.5 * HumanPyramid(weight, column, row - 1, size1, size2); // result of 0.5 weight of row above and column right
    return weight[row][column] + resultLeft + resultRight; //returns result of weight plus column left and right
}

void task3_parenthesis_validator()
{
    printf("Please enter a term for validation:\n");
    scanf("%*c");
    if (ParenthesisValidationInput())
        printf("The parentheses are balanced correctly.\n");
    else
        printf("The parentheses are not balanced correctly.\n");
}

int ParenthesisValidationInput() {
    char validation;
    scanf("%c", &validation);
    if (validation == '\n') // base case, if enter pressed then return 0, recursion ends
        return 0;
    if (ParenthesisValidation(validation)) //if the brackets are closedd correctly returns 0
        return 0;
    if (!ParenthesisValidation(validation)) //if not returns 1
        return 1;
    ParenthesisValidationInput();
}

int ParenthesisValidation(char validation) { //function to check brackets
    switch (validation) {
        case '<': {
            return 1;
            case '>':
                return 0;
        }
        case '[': {
            return 1;
            case ']':
                return 0;
        }
        case '{': {
            return 1;
            case '}':
                return 0;
        }
        case '(': {
            return 1;
            case ')':
                return 0;
        }
        default:
            return 0;
    }
}

void task4_queens_battle()
{
    int dimension;
    printf("Please enter the board dimensions:\n");
    scanf("%d", &dimension);
    char board[dimension][dimension]; //user enters board colors as letters
    int color[dimension];
    int coordinateX[dimension], coordinateY[dimension];
    printf("Please enter the %d*%d puzzle board\n", dimension, dimension);
    scanf("%*c");
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++){
            scanf(" %c", &board[i]);
            color[j] = i;
            if (board[0][0] != board[i][j])
                color[j] = i + 1; //checking if there is a new color for board that user entered
            //if (colors new)
            //colors.push color
        }
    }
    for (int i = dimension; i > 0; i--) {
        for (int j = dimension; j > 0; j--) {
            if (QueenPlacement(coordinateX, coordinateY, color, dimension, j, i))
                printf("X ");
            else
                printf("* ");
        }
        printf("\n");
    }
//colors[dimension]
}

int QueenPlacement(int coordinateX[], int coordinateY[], int color[], int size, int counter1, int counter2){
    if (coordinateX[0] == 0 && coordinateY[0] == 0)
        return 0;
    // if (colors.not.used)
    if (coordinateX[counter1] == coordinateX[counter2] || coordinateY[counter1] == coordinateY[counter2])
        return 1;
    if (coordinateX[counter1] - coordinateX[counter2] == 1 || coordinateY[counter1] - coordinateY[counter2] == 1)
        return 1;
    if (coordinateX[counter1] - coordinateX[counter2] == -1 || coordinateY[counter1] - coordinateY[counter2] == -1)
        return 1;
    //if (coordinateX[counter1] == color[counter1] && coordinateY[counter1] == color[counter1])
    //else return false
    //return QueenPlacement(coordinateX, coordinateY, color, size-1, counter1, counter2);
}

void task5_crossword_generator()
{
    // Todo
}