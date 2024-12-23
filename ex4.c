/******************
Name:
ID:
Assignment: ex4
*******************/
#include <stdio.h>
#include <string.h>
#define MAX_DIMENSION 20
#define ROW 5
#define COLUMN 5
#define MAX_SLOTS 100
#define MAX_LENGTH 15
#define MAX_GRID_SIZE 30
struct Crossword {
    int row;
    int column;
    int length;
    char direction;
};
void task1_robot_paths();
int CalculatePath(int column, int row);
void task2_human_pyramid(int size1, int size2);
float HumanPyramid(float weight[][COLUMN], int column, int row, int size1, int size2);
void task3_parenthesis_validator();
int ParenthesisValidationInput(char expected);
void task4_queens_battle();
int CheckColorPlacement(int colorGrid[][MAX_DIMENSION], int colorUsed[], int row, int column);
int RowCheck(char board[][MAX_DIMENSION], int row, int checkRow);
int ColumnCheck(char board[][MAX_DIMENSION], int column, int checkColumn);
int DiagonalCheck(char board[][MAX_DIMENSION], int row, int column, int dimension);
int PlaceQueens(int colorGrid[][MAX_DIMENSION], int colorUsed[], char board[][MAX_DIMENSION], int dimension, int row, int column);
void task5_crossword_generator();
int PlaceWords(char words[][MAX_SLOTS], struct Crossword check[], int slots_index, int row, int column, int index, char board[][MAX_GRID_SIZE], int used[], int dictionary, int slots);
int OverlapCheck(char words[],char board[][MAX_GRID_SIZE], int row, int column, char direction, int index);
void FillBoard(char board[][MAX_GRID_SIZE], int row_index, int column_index, char words[], int index, char direction);
void ClearBoard(char board[][MAX_GRID_SIZE], int row_index, int column_index, int length, char direction);



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
                printf("\n");
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
    int result = 0;
    printf("Please enter the coordinates of the robot (column, row):\n");
    scanf("%d%d", &column, &row);
    if (column < 0 || row < 0) {
        printf("The total number of paths the robot can take to reach home is: %d\n", result);
        return;
    }
    result = CalculatePath(column, row);
    printf("The total number of paths the robot can take to reach home is: %d\n", result);
}

int CalculatePath(int column, int row) {
    if (column == 0 && row == 0) // base case, there is only one path to go home if robot is already on 0, 0
        return 1;
    if (column == 0)
        return CalculatePath(column, row -1); //if robot can go left then result + 1
    if (row == 0)
        return CalculatePath(column -1, row); //if robot can go down the result + 1
    return CalculatePath(column - 1, row) + CalculatePath(column, row - 1); //both directions
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
    printf("The total weight on each cheerleader is:\n");
    for (int i = 0; i < size1; i++) {
        for (int j = 0; j <= i; j++) {
            result = HumanPyramid(weight, j, i, size1, size2);
            result *= 100;
            result = (int)(result + 0.5);
            result /= 100; //rounding fucking up
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
    if (column > 0 && row < size1 && row > 0)
        resultLeft =  0.5 * HumanPyramid(weight, column - 1, row - 1, size1, size2); //result of 0.5 weight of row above and column left
    if (column <= row)
        resultRight = 0.5 * HumanPyramid(weight, column, row - 1, size1, size2); // result of 0.5 weight of row above and column right
    return weight[row][column] + resultLeft + resultRight; //returns result of weight plus column left and right
}

void task3_parenthesis_validator()
{
    printf("Please enter a term for validation:\n");
    scanf("%*c"); //this thing is gonna kill me
    if (!ParenthesisValidationInput(0))
        printf("The parentheses are balanced correctly.\n");
    else {
        printf("The parentheses are not balanced correctly.\n");
    }
}

int ParenthesisValidationInput(char expected) {
    char validation;
    scanf("%c", &validation);
    if (validation == '\n') {// base case, if enter pressed then return 0, recursion ends
        if (expected == 0) //if no unmached brackets then valid
            return 0;
        return 1;
    }
    switch (validation) { //checking parentheses
        case '<':
            if (ParenthesisValidationInput('>'))
                return 1;
            break;
        case '(':
            if (ParenthesisValidationInput(')'))
                return 1;
            break;
        case '{':
            if (ParenthesisValidationInput('}'))
                return 1;
            break;
        case '[':
            if (ParenthesisValidationInput(']')) //if recursion found closing brackets
                return 1;
        break;
        case '>':
        case ')':
        case '}':
        case ']':
            if (validation != expected) { // not found the expected closing brackets
                scanf("%*[^\n]");
                scanf("%*c");
                return 1;
            }
            return 0;

        default: //default case, other characters
            return ParenthesisValidationInput(expected);
    }
    return ParenthesisValidationInput(expected); //continue recursion
}

void task4_queens_battle()
{
    int dimension;
    printf("Please enter the board dimensions:\n");
    scanf("%d", &dimension);
    char colorBoard[MAX_DIMENSION][MAX_DIMENSION]; //user enters board colors as letters
    int colorGrid[MAX_DIMENSION][MAX_DIMENSION];
    int colorUsed[MAX_DIMENSION];
    char board[MAX_DIMENSION][MAX_DIMENSION];
    printf("Please enter a %d*%d puzzle board:\n", dimension, dimension);
    scanf("%*c");
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++){
            scanf(" %c", &colorBoard[i][j]);
            colorGrid[i][j] = colorBoard[i][j]; //implicit casting probably not a great choice but i was out of ideas and in hysterics
            //if (colors new)
            //colors.push color
            colorUsed[i] = 0;
            board[i][j] = '*';
        }
    }
    if (PlaceQueens(colorGrid, colorUsed, board, dimension, 0, 0)) {
        printf("Solution:\n");
        for (int i = 0; i < dimension; i++) {
            for (int j = 0; j < dimension; j++) {
                printf("%c ", board[i][j]);
            }
            printf("\n");
        }
    }
    else
        printf("This puzzle cannot be solved.\n");
}

int CheckColorPlacement(int colorGrid[][MAX_DIMENSION], int colorUsed[], int row, int column) { //getting the color of the current cell
    int color = 0;
    color = colorGrid[row][column] - 'A';
    if (color < 0) //checking if it's lowercase letters
        color = colorGrid[row][column] - 'a';
    if (colorUsed[color] == 1)
        return 1;
    return 0;
}

int RowCheck(char board[][MAX_DIMENSION], int row, int checkRow) {
    if (checkRow < 0) //base case for recursion if and actually checkrow is a column
        return 0;
    if (board[row][checkRow] == 'X')
        return 1;
    return RowCheck(board, row, checkRow - 1); //if queen.not.found then next column till it's found
}

int ColumnCheck(char board[][MAX_DIMENSION], int column, int checkColumn) {
    if (checkColumn < 0) //base case for checking column and checkcolumn is a row
        return 0;
    if (board[checkColumn][column] == 'X')
        return 1;
    return ColumnCheck(board, column, checkColumn - 1); //if queen.not.found then next row till it's found
}

int DiagonalCheck(char board[][MAX_DIMENSION], int row, int column, int dimension) { //just checking a diagonal near
    if (row > 0 && column > 0 && board[row - 1][column - 1] == 'X')
        return 1;
    if (row > 0 && column < dimension  && board[row - 1][column + 1] == 'X')
        return 1;
    if (row < dimension && column > 0 && board[row + 1][column - 1] == 'X')
        return 1;
    if (row < dimension && column < dimension && board[row + 1][column + 1] == 'X')
        return 1;
    return 0;
}

int PlaceQueens(int colorGrid[][MAX_DIMENSION], int colorUsed[], char board[][MAX_DIMENSION], int dimension, int row, int column) {
    int color = 0;
    if (row == dimension) //base case
        return 1;
    if (column == dimension) //also base case
        return 0;
    if (!CheckColorPlacement(colorGrid, colorUsed, row, column) && !RowCheck(board, row, dimension) // if all check functions return 0 then let's gooooooo
        && !ColumnCheck(board, column, dimension) && !DiagonalCheck(board, row, column, dimension)) {
        color = colorGrid[row][column] - 'A';
        if (color < 0) // also checking if it's lowercase letters
            color = colorGrid[row][column] - 'a';
        colorUsed[color] = 1;
        board[row][column] = 'X';
        if (PlaceQueens(colorGrid, colorUsed, board, dimension, row + 1, 0)) //backtraking
            return 1;
        colorUsed[color] = 0;
        board[row][column] = '*';
    }
    return PlaceQueens(colorGrid, colorUsed, board, dimension, row, column + 1);
}



void task5_crossword_generator()
{
    int dimension;
    int slots;
    int UsedWord[MAX_SLOTS] = {0};
    struct Crossword crossword[MAX_SLOTS];
    int dictionary;
    char words[MAX_LENGTH][MAX_SLOTS];
    char board[MAX_GRID_SIZE][MAX_GRID_SIZE];
    printf("Please enter the dimensions of the crossword grid:\n");
    scanf("%d", &dimension);
    printf("Please enter the number of slots in the crossword:\n");
    scanf("%d", &slots);
    printf("Please enter the details for each slot (Row, Column, Length, Direction):\n");
    for (int i = 0; i < slots; i++)
    {
        scanf("%d %d %d", &crossword[i].row, &crossword[i].column, &crossword[i].length);
        scanf(" %c", &crossword[i].direction);
    }
    printf("Please enter the number of words in the dictionary:\n");
    scanf("%d", &dictionary);
    while (dictionary < slots) {
        printf("The dictionary must contain at least %d words.  Please enter a valid dictionary size: \n", slots);
        scanf("%d", &dictionary);
    }
    printf("Please enter the words for the dictionary:\n");
    for (int i = 0; i < dictionary; i++) {
        scanf(" %s", words[i]);
    }
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            board[i][j] = '#'; //initialized the board
        }
    }
    if (PlaceWords(words, crossword, 0, 0, 0, 0, board, UsedWord, dictionary - 1, slots)) {
        for (int i = 0; i < dimension; i++) {
            for (int j = 0; j < dimension; j++) {
                printf("| %c ", board[i][j]);
            }
            printf("|\n");
        }
    }
    else
        printf("This crossword cannot be solved.\n");
}

int OverlapCheck(char words[],char board[][MAX_GRID_SIZE], int row, int column, char direction, int index){
    if (words[index] == '\0') //base case is the word is ended
        return 1;
   // printf("row index: %d, column index: %d word: %c, board: %c\n", row, column, words[index], board[row][column]);
    if (board[row][column] != '#' && board[row][column] != words[index]) {
        //printf("conflict at row index: %d, column index: %d word: %c, board: %c\n", row, column, words[index], board[row][column]);
        return 0;
    }
    if (direction == 'H') //if horizontal then returns next character and next column
        return OverlapCheck(words, board, row, column + 1, direction, index + 1);

    return OverlapCheck(words, board, row + 1, column, direction, index + 1); //if vertical next character and row
}

int PlaceWords(char words[][MAX_SLOTS], struct Crossword check[], int slot_index, int row, int column, int index, char board[][MAX_GRID_SIZE], int used[], int dictionary, int slots) {
    if (index >= dictionary)
        return 0;//no words left
    if (slot_index >= slots)
        return 1;//all slots are filled
    //if direction is horizontal then place word from row[slots] to strlen(word) and column[slots] to length
    char word[MAX_LENGTH];
    strcpy(word, words[index]); //copying one word from array to send it to function
  //  printf("Checking word: %s with length %llu against required length %d\n", words[index], strlen(words[index]), check[slots].length);
    if (!used[index] && (int)strlen(word) == check[slot_index].length && //checks if the word is used already and if the length of the word fits
        OverlapCheck(word, board, check[slot_index].row, check[slot_index].column, check[slot_index].direction, 0)) {
        FillBoard(board, check[slot_index].row, check[slot_index].column, word, 0 ,check[slot_index].direction);
        used[index] = 1; //puts that the word is used
        if (PlaceWords(words, check, slot_index + 1, row, column, 0, board, used, dictionary, slots)) //next slot
            return 1;
        ClearBoard(board, check[slot_index].row, check[slot_index].column, check[slot_index].length, check[slot_index].direction);
        used[index] = 0;
    }
    //backtracking
    // if (PlaceWords(words, check, slots, row, column, index - 1, board, used, dictionary))
    //     return 1;
    return PlaceWords(words, check, slot_index, row, column, index + 1, board, used, dictionary, slots); //next word
}

void FillBoard(char board[][MAX_GRID_SIZE], int row_index, int column_index, char words[], int index, char direction) {
    if (words[index] == '\0') //function for filling the board with words
        return; ///base case if the word ended
    board[row_index][column_index] = words[index];
    if (direction == 'H') { //if horizontal returns next character in string and next column
        FillBoard(board, row_index, column_index + 1, words, index + 1, direction);
    }
    else { //if vertical next character and next row
        FillBoard(board, row_index + 1, column_index, words, index + 1, direction);
    }
}

void ClearBoard(char board[][MAX_GRID_SIZE], int row_index, int column_index, int length, char direction) { //function for backtracking
    if (length == 0) //base case if length of word 0 then word is deleted
        return;
    board[row_index][column_index] = '#';  //deletes words
    if (direction == 'H') { //if horizontal then next column and minus length
        ClearBoard(board, row_index, column_index + 1, length - 1, direction);
    }
    else { // if vertical then next row and minus length
        ClearBoard(board, row_index + 1, column_index, length - 1, direction);
    }
}