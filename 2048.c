#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

void Print_Matrix(int[][4]);
void Move_up(int[][4], int *score);
void Move_down(int[][4], int *score);
void Move_left(int[][4], int *score);
void Move_right(int[][4], int *score);
void Move_down_generate(int[][4]);
void Move_up_generate(int[][4]);
void Move_left_generate(int[][4]);
void Move_right_generate(int[][4]);
void Generate(int[][4]);
bool check_status(int[][4]);

int main()
{
    // initialize the game
    srand(time(0));

    int size_of_matr = 4;
    int Matrix[size_of_matr][size_of_matr];
    int total_score = 0;
    int checking_score = 0; // useless
    int copy1[4][4];
    int copy2[4][4];
    int copy3[4][4];
    int copy4[4][4];

    int random_number_i = rand() % (size_of_matr);
    int random_number_j = rand() % (size_of_matr);
    int random_two_or_four = (rand() % (2) + 1) * 2;

    for (int i = 0; i < size_of_matr; i++)
    {
        for (int j = 0; j < size_of_matr; j++)
        {
            if (i == random_number_i && j == random_number_j)
            {
                Matrix[i][j] = random_two_or_four;
            }
            else
            {
                Matrix[i][j] = 0;
            }
        }
    }
    Print_Matrix(Matrix);

    // Start the game
    bool game_not_lost = true;
    while (game_not_lost)
    {
        if (getc(stdin) == '\033')
        {                // if the first value is esc
            getc(stdin); // skip the [
            switch (getc(stdin))
            { // the real value
            case 'A':
                // code for arrow up
                printf("UP\n");
                Move_up(Matrix, &total_score);
                Move_up_generate(Matrix);
                Print_Matrix(Matrix);
                printf("Score: %d\n", total_score);
                break;

            case 'B':
                // code for arrow down
                printf("DOWN\n");
                Move_down(Matrix, &total_score);
                Move_down_generate(Matrix);
                Print_Matrix(Matrix);
                printf("Score: %d\n", total_score);
                break;

            case 'C':
                // code for arrow right
                printf("RIGHT\n");
                Move_right(Matrix, &total_score);
                Move_right_generate(Matrix);
                Print_Matrix(Matrix);
                printf("Score: %d\n", total_score);
                break;

            case 'D':
                // code for arrow left
                printf("LEFT\n");
                Move_left(Matrix, &total_score);
                // Generate(Matrix);
                Move_left_generate(Matrix);
                Print_Matrix(Matrix);
                printf("Score: %d\n", total_score);
                break;
            }
        }

        // check game status
        game_not_lost = check_status(Matrix);
        bool Move_up_status = true;
        bool Move_down_status = true;
        bool Move_left_status = true;
        bool Move_right_status = true;

        if (!game_not_lost)
        {
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    copy1[i][j] = Matrix[i][j];
                    copy2[i][j] = Matrix[i][j];
                    copy3[i][j] = Matrix[i][j];
                    copy4[i][j] = Matrix[i][j];
                }
            }

            Move_up(copy1, &checking_score);
            Move_up_status = check_status(copy1);

            Move_down(copy2, &checking_score);
            Move_down_status = check_status(copy2);

            Move_left(copy3, &checking_score);
            Move_left_status = check_status(copy3);

            Move_right(copy4, &checking_score);
            Move_right_status = check_status(copy4);
        }
        if (!Move_up_status && !Move_down_status && !Move_left_status && !Move_right_status)
        {
            printf("Mission Failed, we will get them next time!\nThanks for playing :)\n\n");
            game_not_lost = false;
        }
        else
        {
            game_not_lost = true;
        }
    }
    return 0;
}

void Print_Matrix(int Matrix[][4])
{
    printf("\n\n");
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            printf("%d\t", Matrix[i][j]);
        }
        printf("\n\n\n");
    }
    return;
}

void Move_up(int Matrix[][4], int *score)
{

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (i != 0 && Matrix[i][j] != 0)
            {
                bool Not_done = true;
                int k = i;
                while (Not_done && k > 0)
                {
                    if (Matrix[k - 1][j] == 0)
                    {
                        Matrix[k - 1][j] = Matrix[k][j];
                        Matrix[k][j] = 0;
                    }
                    else if (Matrix[k - 1][j] == Matrix[k][j])
                    {
                        *score += Matrix[k - 1][j] + Matrix[k][j];
                        Matrix[k - 1][j] += Matrix[k][j];
                        Matrix[k][j] = 0;
                    }
                    else
                    {
                        Not_done = false;
                    }
                    k--;
                }
            }
        }
    }

    return;
}

void Move_down(int Matrix[][4], int *score)
{
    for (int i = 3; i >= 0; i--)
    {
        for (int j = 0; j < 4; j++)
        {
            if (i != 3 && Matrix[i][j] != 0)
            {
                bool Not_done = true;
                int k = i;
                while (Not_done && k < 3)
                {
                    bool next_zero = false;
                    if (Matrix[k + 1][j] == 0)
                    {
                        next_zero = true;
                        Matrix[k + 1][j] = Matrix[k][j];
                        Matrix[k][j] = 0;
                    }
                    else if (Matrix[k + 1][j] == Matrix[k][j])
                    {
                        *score += Matrix[k + 1][j] + Matrix[k][j];
                        Matrix[k + 1][j] += Matrix[k][j];
                        Matrix[k][j] = 0;
                    }
                    else
                    {
                        Not_done = false;
                    }
                    k++;
                }
            }
        }
    }

    return;
}

void Move_left(int Matrix[][4], int *score)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (j != 0 && Matrix[i][j] != 0)
            {
                bool Not_done = true;
                int k = j;
                while (Not_done && k > 0)
                {
                    if (Matrix[i][k - 1] == 0)
                    {
                        Matrix[i][k - 1] = Matrix[i][k];
                        Matrix[i][k] = 0;
                    }
                    else if (Matrix[i][k - 1] == Matrix[i][k])
                    {
                        *score += Matrix[i][k - 1] + Matrix[i][k];
                        Matrix[i][k - 1] += Matrix[i][k];
                        Matrix[i][k] = 0;
                    }
                    else
                    {
                        Not_done = false;
                    }
                    k--;
                }
            }
        }
    }

    return;
}

void Move_right(int Matrix[][4], int *score)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 3; j >= 0; j--)
        {
            if (j != 3 && Matrix[i][j] != 0)
            {
                bool Not_done = true;
                int k = j;
                while (Not_done && k < 3)
                {
                    if (Matrix[i][k + 1] == 0)
                    {
                        Matrix[i][k + 1] = Matrix[i][k];
                        Matrix[i][k] = 0;
                    }
                    else if (Matrix[i][k + 1] == Matrix[i][k])
                    {
                        *score += Matrix[i][k + 1] + Matrix[i][k];
                        Matrix[i][k + 1] += Matrix[i][k];
                        Matrix[i][k] = 0;
                    }
                    else
                    {
                        Not_done = false;
                    }
                    k++;
                }
            }
        }
    }

    return;
}

void Move_down_generate(int Matrix[][4])
{
    int random_two_or_four = (rand() % (2) + 1) * 2;
    int count = 0;
    int row_have_zero = 0;
    for (int i = 0; i < 4; i++)
    {
        bool have_zero = false;
        for (int j = 0; j < 4; j++)
        {
            if (Matrix[i][j] == 0)
            {
                count++;
                have_zero = true;
            }
        }
        if (have_zero)
        {
            break;
        }
    }
    int *zero_row = malloc(count * sizeof(int));
    int n = 0;
    for (int j = 0; j < 4; j++)
    {
        if (Matrix[row_have_zero][j] == 0)
        {
            zero_row[n] = j;
            n++;
        }
    }
    int random_select = rand() % count;
    Matrix[row_have_zero][zero_row[random_select]] = random_two_or_four;
    free(zero_row);

    return;
}

void Move_up_generate(int Matrix[][4])
{
    int random_two_or_four = (rand() % (2) + 1) * 2;
    int count = 0;
    int row_have_zero = 3;
    for (int i = 3; i >= 0; i--)
    {
        bool have_zero = false;
        for (int j = 0; j < 4; j++)
        {
            if (Matrix[i][j] == 0)
            {
                count++;
                have_zero = true;
            }
        }
        if (have_zero)
        {
            break;
        }
    }
    int *zero_row = malloc(count * sizeof(int));
    int n = 0;
    for (int j = 0; j < 4; j++)
    {
        if (Matrix[row_have_zero][j] == 0)
        {
            zero_row[n] = j;
            n++;
        }
    }
    int random_select = rand() % count;
    Matrix[row_have_zero][zero_row[random_select]] = random_two_or_four;
    free(zero_row);

    return;
}

void Move_left_generate(int Matrix[][4])
{
    int random_two_or_four = (rand() % (2) + 1) * 2;
    int count = 0;
    int column_have_zero = 3;
    for (int j = 3; j >= 0; j--)
    {
        bool have_zero = false;
        for (int i = 0; i < 4; i++)
        {
            if (Matrix[i][j] == 0)
            {
                count++;
                have_zero = true;
            }
        }
        if (have_zero)
        {
            break;
        }
    }
    int *zero_column = malloc(count * sizeof(int));
    int n = 0;
    for (int i = 0; i < 4; i++)
    {
        if (Matrix[i][column_have_zero] == 0)
        {
            zero_column[n] = i;
            n++;
        }
    }
    int random_select = rand() % count;
    Matrix[zero_column[random_select]][column_have_zero] = random_two_or_four;
    free(zero_column);

    return;
}

void Move_right_generate(int Matrix[][4])
{
    int random_two_or_four = (rand() % (2) + 1) * 2;
    int count = 0;
    int column_have_zero = 0;
    for (int j = 0; j < 4; j++)
    {
        bool have_zero = false;
        for (int i = 0; i < 4; i++)
        {
            if (Matrix[i][j] == 0)
            {
                count++;
                have_zero = true;
            }
        }
        if (have_zero)
        {
            break;
        }
    }
    int *zero_column = malloc(count * sizeof(int));
    int n = 0;
    for (int i = 0; i < 4; i++)
    {
        if (Matrix[i][column_have_zero] == 0)
        {
            zero_column[n] = i;
            n++;
        }
    }
    int random_select = rand() % count;
    Matrix[zero_column[random_select]][column_have_zero] = random_two_or_four;
    free(zero_column);

    return;
}

void Generate(int Matrix[][4])
{

    int random_two_or_four = (rand() % (2) + 1) * 2;
    bool should_return = false;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (Matrix[i][j] == 0)
            {
                Matrix[i][j] = random_two_or_four;
                should_return = true;
                break;
            }
        }
        if (should_return)
        {
            break;
        }
    }
    return;
}

bool check_status(int Matrix[][4])
{
    bool game_not_lost = false;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (Matrix[i][j] == 0)
            {
                game_not_lost = true;
                break;
            }
            if (game_not_lost)
            {
                break;
            }
        }
    }
    return game_not_lost;
}
