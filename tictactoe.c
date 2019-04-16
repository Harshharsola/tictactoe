#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

int turn = 0, A[3][3], completion = 1, count = 0;
void *player_1()
{
    while (completion)
    {

        if (turn == 0 && count != 9 && completion)
        {

            int x, y;
            x = rand() % 3;
            y = rand() % 3;
            printf("p1 %d %d\n", x, y);
            if (A[x][y] == 0)
            {
                A[x][y] = 1;
                count++;
                turn = 1;
            }
            else
            {
                printf("repeat\n");
            }
        }
    }
}
void *player_2()
{

    while (completion)
    {
        if (turn == 2 && count != 9 && completion)
        {
            int x, y;
            x = rand() % 3;
            y = rand() % 3;
            printf("p2 %d %d\n", x, y);
            if (A[x][y] == 0)
            {
                A[x][y] = 2;
                count++;
                turn = 3;
            }
            else
            {
                printf("repeat\n");
            }
        }
    }
}
void *checking()
{
    while (completion)
    {

        if (turn == 1 || turn == 3)
        {
            for (int i = 0; i < 3; i++)
            {
                if ((A[i][0] == A[i][1]) && (A[i][1] == A[i][2]) && (A[i][0] != 0)) // row check
                {
                    if (A[i][0] == 1)
                    {
                        printf("Player 1 wins RC\n");
                    }
                    else
                    {
                        printf("Player 2 wins RC\n");
                    }
                    completion = 0;
                }
            }

            if ((A[0][0] == A[1][1]) && (A[1][1] == A[2][2]) && (A[1][1] != 0)) // diagnal check
            {
                if (A[0][0] == 1)
                {
                    printf("Player 1 wins DC\n");
                }
                else
                {
                    printf("Player 2 wins DC\n");
                }
                completion = 0;
            }

            for (int i = 0; i < 3; i++)
            {
                if ((A[0][i] == A[1][i]) && (A[1][i] == A[2][i]) && (A[0][i] != 0)) //column check
                {
                    if (A[0][i] == 1)
                    {
                        printf("Player 1 wins CC\n");
                    }
                    else
                    {
                        printf("Player 2 wins CC\n");
                    }
                    completion = 0;
                }
            }

            if ((A[0][2] == A[1][1]) && (A[1][1] == A[2][0]) && (A[2][0] != 0)) //reverse diagnal check
            {
                if (A[0][2] == 1)
                {
                    printf("Player 1 wins RDC\n");
                }
                else
                {
                    printf("Player 2 wins RDC\n");
                }
                completion = 0;
            }
            if (turn == 1)
            {
                turn = 2;
            }
            else if (turn == 3)
            {
                turn = 0;
            }
        }
        if (count >= 9 && completion != 0)
        {
            printf("Game Draw\n");
            completion = 0;
        }
    }
}
void main()
{
    srand(time(0));
    pthread_t player1, player2, check;
    pthread_create(&player1, NULL, player_1, NULL);
    pthread_create(&player2, NULL, player_2, NULL);
    pthread_create(&check, NULL, checking, NULL);
    pthread_join(player1, NULL);
    pthread_join(player2, NULL);
    pthread_join(check, NULL);

    return;
}