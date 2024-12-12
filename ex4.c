/******************
Name:
ID:
Assignment:
*******************/
#include <stdio.h>
#include <string.h>
#define CHEERLEADERS 15
void task1_robot_paths();
int CalculatePath(int column, int row, int result);
void task2_human_pyramid(int size);
float HumanPyramid(float weight[], int size, int column, int row);
void task3_parenthesis_validator();
void task4_queens_battle();
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
                task2_human_pyramid(CHEERLEADERS);
                break;
            case 3:
                task3_parenthesis_validator();
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
        // else
        // {
        //     scanf("%*s");
        // }

    } while (task != 6);
}

void task1_robot_paths()
{
    int column, row;
    int result = 0;
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

void task2_human_pyramid(int size)
{
    float weight[size] = {0};
    printf("Please enter the weights of the cheerleaders: \n");
    for (int i = 0; i < size; i++) {
        scanf("%f", &weight[i]);
        if (weight[i] < 0) {
            printf("Negative weights are not supported.\n");
            return;
        }
    }
}

float HumanPyramid(float weight[], int size, int column, int row) {

}

void task3_parenthesis_validator()
{
    // Todo
}

void task4_queens_battle()
{
    // Todo
}

void task5_crossword_generator()
{
    // Todo
}