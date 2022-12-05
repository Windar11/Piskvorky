#include"Lederboard.h"

#include <iostream>


void addToBoard(leader* LeaderBoard, char* meno)
{
	FILE* board;
	if (fopen_s(&board, "leaderboard.txt", "r") != 0)
	{
		printf("errror");
	}
	else
	{
		int poz = 27;
		bool found = false;
		for (int i = 0; i < 10; i++)
		{
			if (board != 0)
			{
				fscanf_s(board, "%d\n", &LeaderBoard[i].obsadene);
				fscanf_s(board, "%s\n", LeaderBoard[i].meno, 20);
				fscanf_s(board, "%d\n", &LeaderBoard[i].pocetVyhier);

				if (strcmp(LeaderBoard[i].meno, meno) == 0)
				{
					found = true;
					LeaderBoard[i].pocetVyhier++;
					break;
				}
			}
		}
		fclose(board);



		if (found == false)
		{
			for (int i = 0; i < 10; i++)
			{
				if (LeaderBoard[(i)].obsadene == 0)
				{
					poz = i;
					break;
				}
			}
			LeaderBoard[poz].obsadene = 1;
			strcpy_s(LeaderBoard[poz].meno, meno);
			LeaderBoard[poz].pocetVyhier = 1;
		}


		/*SORT		Z NEJAKEHO DOVODU NEFUNGUJE
		int i, j;
		leader tmp = *(leader*)malloc(sizeof(leader));
		for (i = 0; i < poz - 1; i++) 
		{
			for (j = 0; j < poz - i - 1; j++)
			{
				if (LeaderBoard[j].pocetVyhier < LeaderBoard[j + 1].pocetVyhier)
				{
					tmp.obsadene = LeaderBoard[j].obsadene;
					LeaderBoard[j].obsadene = LeaderBoard[j + 1].obsadene;
					LeaderBoard[j + 1].obsadene = tmp.obsadene;
					
				}

				if (LeaderBoard[j].pocetVyhier < LeaderBoard[j + 1].pocetVyhier)
				{
					strcpy_s(tmp.meno, LeaderBoard[j].meno);
					strcpy_s(LeaderBoard[j].meno, LeaderBoard[j + 1].meno);
					strcpy_s(LeaderBoard[j + 1].meno, tmp.meno);

				}

				if (LeaderBoard[j].pocetVyhier < LeaderBoard[j + 1].pocetVyhier)
				{
					tmp.pocetVyhier = LeaderBoard[j].pocetVyhier;
					LeaderBoard[j].pocetVyhier = LeaderBoard[j + 1].pocetVyhier;
					LeaderBoard[j + 1].pocetVyhier = tmp.pocetVyhier;

				}
					
			}
				
		}

			


		!SORT*/


		if (fopen_s(&board, "leaderboard.txt", "w") != 0)
		{
			printf("errror");
		}
		else
		{
			for (int i = 0; i < poz + 1; i++)
			{
				fprintf(board, "%d\n", LeaderBoard[i].obsadene);
				fprintf(board, "%s\n", LeaderBoard[i].meno);
				fprintf(board, "%d\n", LeaderBoard[i].pocetVyhier);

			}
			for (int i = (poz + 2); i < 10; i++)
			{
				fprintf(board, "0\n");
				fprintf(board, " \n");
				fprintf(board, " \n");

			}

		}
		fclose(board);

	}
}


void ShowBoard(leader LeaderBoard[10])
{
	int poz = 0;
	FILE* board;
	if (fopen_s(&board, "leaderboard.txt", "r") != 0)
	{
		printf("errror");
	}
	else
	{
		for (int j = 0; j < 10; j++)
		{
			fscanf_s(board, "%d\n", &LeaderBoard[j].obsadene);
			fscanf_s(board, "%s\n", LeaderBoard[j].meno, 20);
			fscanf_s(board, "%d\n", &LeaderBoard[j].pocetVyhier);

		}
	}
	fclose(board);

	printf("\n\n");

	for (int i = 0; i < 10; i++)
	{
		if (LeaderBoard[(i)].obsadene == 0)
		{
			poz = i;
			break;
		}

	}
	for (int i = 0; i < poz; i++)
	{
		//printf("%d\n", LeaderBoard[i].obsadene);
		printf("Player: %s, Pocet vyhier: %d\n", LeaderBoard[i].meno, LeaderBoard[i].pocetVyhier);
	}
	int c;
	while ((c = getchar()) != '\n' && c != EOF) {}
}