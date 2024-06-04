#include <iostream>
#include <cstdlib>
#include <ctime>

const int SIZE = 4;  // game board size
const int EMPTY = 0; // empty cell value

int board[SIZE][SIZE] = {EMPTY}; // initialize empty board

// Function prototypes
void moveUp();
void moveDown();
void moveLeft();
void moveRight();
void spawnNewTile();
bool isGameOver();
bool isWin();
void displayBoard();
int getScore();

int main()
{
    srand(time(0)); // seed random number generator

    // Initialize with two starting tiles
    spawnNewTile();
    spawnNewTile();

    while (true)
    {
        displayBoard(); // print current board state

        char input;
        std::cout << "Enter move (w/a/s/d): ";
        std::cin >> input;

        switch (input)
        {
        case 'w':
            moveUp();
            break;
        case 's':
            moveDown();
            break;
        case 'a':
            moveLeft();
            break;
        case 'd':
            moveRight();
            break;
        default:
            std::cout << "Invalid move. Try again!" << std::endl;
        }

        if (isGameOver())
        {
            std::cout << "Game Over! Final score: " << getScore() << std::endl;
            break;
        }

        if (isWin())
        {
            std::cout << "You won! Final score: " << getScore() << std::endl;
            break;
        }

        spawnNewTile();
    }

    return 0;
}

// Function definitions
void moveUp()
{
    for (int col = 0; col < SIZE; col++)
    {
        for (int row = 1; row < SIZE; row++)
        {
            if (board[row][col] != EMPTY)
            {
                int nextRow = row - 1;
                while (nextRow >= 0 && board[nextRow][col] == EMPTY)
                {
                    nextRow--;
                }
                if (nextRow >= 0 && board[nextRow][col] == board[row][col])
                {
                    board[nextRow][col] *= 2;
                    board[row][col] = EMPTY;
                }
                else
                {
                    board[nextRow + 1][col] = board[row][col];
                    board[row][col] = EMPTY;
                }
            }
        }
    }
}

void moveDown()
{
    for (int col = 0; col < SIZE; col++)
    {
        for (int row = SIZE - 2; row >= 0; row--)
        {
            if (board[row][col] != EMPTY)
            {
                int nextRow = row + 1;
                while (nextRow < SIZE && board[nextRow][col] == EMPTY)
                {
                    nextRow++;
                }
                if (nextRow < SIZE && board[nextRow][col] == board[row][col])
                {
                    board[nextRow][col] *= 2;
                    board[row][col] = EMPTY;
                }
                else
                {
                    board[nextRow - 1][col] = board[row][col];
                    board[row][col] = EMPTY;
                }
            }
        }
    }
}

void moveLeft()
{
    for (int row = 0; row < SIZE; row++)
    {
        for (int col = 1; col < SIZE; col++)
        {
            if (board[row][col] != EMPTY)
            {
                int nextCol = col - 1;
                while (nextCol >= 0 && board[row][nextCol] == EMPTY)
                {
                    nextCol--;
                }
                if (nextCol >= 0 && board[row][nextCol] == board[row][col])
                {
                    board[row][nextCol] *= 2;
                    board[row][col] = EMPTY;
                }
                else
                {
                    board[row][nextCol + 1] = board[row][col];
                    board[row][col] = EMPTY;
                }
            }
        }
    }
}

void moveRight()
{
    for (int row = 0; row < SIZE; row++)
    {
        for (int col = SIZE - 2; col >= 0; col--)
        {
            if (board[row][col] != EMPTY)
            {
                int nextCol = col + 1;
                while (nextCol < SIZE && board[row][nextCol] == EMPTY)
                {
                    nextCol++;
                }
                if (nextCol < SIZE && board[row][nextCol] == board[row][col])
                {
                    board[row][nextCol] *= 2;
                    board[row][col] = EMPTY;
                }
                else
                {
                    board[row][nextCol - 1] = board[row][col];
                    board[row][col] = EMPTY;
                }
            }
        }
    }
}

void spawnNewTile()
{
    int row, col;
    do
    {
        row = rand() % SIZE;
        col = rand() % SIZE;
    } while (board[row][col] != EMPTY);

    board[row][col] = (rand() % 2) ? 2 : 4;
}

bool isGameOver()
{
    for (int row = 0; row < SIZE; row++)
    {
        for (int col = 0; col < SIZE; col++)
        {
            if (board[row][col] == EMPTY)
            {
                return false;
            }
        }
    }
    return true;
}

bool isWin()
{
    for (int row = 0; row < SIZE; row++)
    {
        for (int col = 0; col < SIZE; col++)
        {
            if (board[row][col] == 2048)
            {
                return true;
            }
        }
    }
    return false;
}

void displayBoard()
{
    for (int row = 0; row < SIZE; row++)
    {
        for (int col = 0; col < SIZE; col++)
        {
            std::cout << board[row][col] << "\t";
        }
        std::cout << std::endl;
    }
}

int getScore()
{
    int score = 0;
    for (int row = 0; row < SIZE; row++)
    {
        for (int col = 0; col < SIZE; col++)
        {
            score += board[row][col];
        }
    }
    return score;
}