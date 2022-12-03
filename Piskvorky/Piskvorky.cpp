// Piskvorky.cpp : Defines the entry point for the application.
//

#include "Piskvorky.h"
#include <iostream>
#include <math.h>
#include <time.h>

using namespace std;

void vyberMena(char *player1, char *player2)
{
	FILE* subor;
	char nove;
	char znak;
	printf("Chcete vytvorit nove mena? a[ANO] / n[NIE]\n");
	nove = tolower(getchar());
	
	int c;
	while ((c = getchar()) != '\n' && c != EOF) {}

	switch (nove)
	{
	case 'a':
		if (fopen_s(&subor, "menahracov.txt", "w") != 0)
		{
			printf("errror");
		}
		else
		{
			system("cls");
			printf("Zadajte meno hraca 1 : \n");
			scanf_s("%s", &player1, PLAYER_NAME_SIZE);
			fprintf_s(subor, "%s\n", &player1);
			while ((c = getchar()) != '\n' && c != EOF) {}
			
			printf("\nZadajte meno hraca 2 : \n");
			scanf_s("%s", &player2, PLAYER_NAME_SIZE);
			fprintf_s(subor, "%s\n", &player2);
			while ((c = getchar()) != '\n' && c != EOF) {}
			
			fclose(subor);
			break;
		}

	case 'n':
		printf("\n\nMena z predchadzajucej hry\n\n");
		if (fopen_s(&subor, "menahracov.txt", "r") != 0)
		{
			printf("errror");
			fopen_s(&subor, "menahracov.txt", "w");
			fclose(subor);
		}
		else
		{
			
			
			fseek(subor, 0, SEEK_END);
			if (ftell(subor) == 0)
			{
				system("cls");
				printf("\n\n!!Mena z predoslej hry nie su dostupne!!\n");
				printf("Prosim zadajte nove mena.\n\n");
				fclose(subor);
				vyberMena(player1, player2);
			}
			fseek(subor, 0, SEEK_SET);
			fscanf_s(subor, "%s", player1, PLAYER_NAME_SIZE);
			fscanf_s(subor, "%s", player2, PLAYER_NAME_SIZE);
			
			
			fclose(subor);
		}
		break;
	default:
		printf("!!!Vozeny nespravny znak.!!!\n");
		printf("Prosim zadajte znova.\n\n");
		vyberMena(player1, player1);
		break;
	}
	
	
}

void vyberVelkosti(int *velkostX,int *velkostY)
{
	
	do
	{
		system("cls");
		printf("Prosím zadajte velkost hracieho pola (min 3x3)\n");
		scanf_s("%dx%d", velkostX, velkostY);
		while (getchar() != '\n');
	} while (*velkostX < 3 && *velkostY < 3);

	
}

void pickFirst(bool *startPlayer)
{
	srand(time(NULL));
	*startPlayer = rand() % 2;
}

void vypisNastaveni(char *player1, char *player2, int *velkostX, int *velkostY, bool *startPlayer)
{
	system("cls");
	printf("Meno hraca 1: %s\n", player1);
	printf("Meno hraca 2: %s\n", player2);
	printf("Velkost hracieho pola: %dx%d \n", *velkostX, *velkostY);
	printf("Zacina hrac1/hrac2  [0/1] :  %d\n", *startPlayer);

	int c;
	while ((c = getchar()) != '\n' && c != EOF) {}

}
/*
void drawSquare()
{
	printf("%c%c%c%c%c", UPPER_LEFT_CORNER, HORIZ, HORIZ, HORIZ, UPPER_RIGHT_CORNER);
	printf("%c%c%c%c%c", VERT, ' ', ' ', ' ', VERT);
	printf("%c%c%c%c%c", LOWER_LEFT_CORNER, HORIZ, HORIZ, HORIZ, LOWER_RIGHT_CORNER);
}
*/
void vykreslenieDosky(int** hraciaDoska,int velkostX,int velkostY)
{
	system("cls");
	for (int k = 0; k < velkostY; k++)
	{
		for (int i = 0; i < 3; i++)
		{
			switch (i)
			{
			case 0:
			{
				for (int j = 0; j < velkostX; j++)
				{
					printf(" %c%c%c%c%c ", UPPER_LEFT_CORNER, HORIZ, HORIZ, HORIZ, UPPER_RIGHT_CORNER);
				}
				printf("\n");
				break;
			}

			case 1:
			{

				for (int j = 0; j < velkostX; j++)
				{
					if (hraciaDoska[j][k] != -1)
					{

						printf(" %c%c%d%c%c ", VERT, ' ', hraciaDoska[j][k], ' ', VERT);
					}
					else
					printf(" %c%c%c%c%c ", VERT, ' ', ' ', ' ', VERT);
				}
				printf("\n");
				break;
			}

			case 2:
			{
				for (int j = 0; j < velkostX; j++)
				{
					printf(" %c%c%c%c%c ", LOWER_LEFT_CORNER, HORIZ, HORIZ, HORIZ, LOWER_RIGHT_CORNER);
				}
				printf("\n");
				break;
			}

			}

		}
	}
		
	/*
	int c;
	while ((c = getchar()) != '\n' && c != EOF) {}
	*/
}


void urobTah(int** hraciaDoska , bool *startPlayer, char* player1, char* player2)
{
	int zadaneX = 0;
	int zadaneY = 0;
	int c = 0;
	if (*startPlayer == 0)
	{
		printf("Na tahu je hrac: %s\n", player1);
		printf("Zadaj súradnice [ X,Y ]\n");
		scanf_s("%d,%d", &zadaneX, &zadaneY);

		while ((c = getchar()) != '\n' && c != EOF) {}
		hraciaDoska[zadaneX - 1][zadaneY - 1] = 0;
	}
	else if (*startPlayer == 1)
	{
		printf("Na tahu je hrac: %s\n", player2);
		printf("Zadaj súradnice [ X,Y ]\n");
		scanf_s("%d,%d", &zadaneX, &zadaneY);

		while ((c = getchar()) != '\n' && c != EOF) {}
		hraciaDoska[zadaneX - 1][zadaneY - 1] = 1;
	}
	*startPlayer = !(*startPlayer);
}



int main()
{
	int velkostX;
	int velkostY;
	char player1[PLAYER_NAME_SIZE];
	char player2[PLAYER_NAME_SIZE];
	char opt;
	bool startPlayer;
	int** hraciaDoska = NULL;
	do
	{
		
		system("cls");		
		printf("N: Nastavenia hry   ");
		printf("Z: Zobrazit aktualne nastavenia   ");
		printf("S: Start hry     ");
		printf("L: Leaderboard     ");
		printf("Q: Ukoncit hru\n\n");

		opt = tolower(getchar());
		int c;
		while ((c = getchar()) != '\n' && c != EOF) {}

		switch (opt)
		{
		case 'n':
			vyberMena(player1, player2);
			vyberVelkosti(&velkostX, &velkostY);
			pickFirst(&startPlayer);

			hraciaDoska = (int**)malloc(velkostX * sizeof(int));
			for (int i = 0; i < velkostX; i++)
			{
				hraciaDoska[i] = (int*)malloc(velkostY * sizeof(int));
			}

			for (int i = 0; i < velkostY; i++)
			{
				for (int j = 0; j < velkostY; j++)
				{
					hraciaDoska[i][j] = -1;
				}
			}

			break;
		case 'z':
			
			system("cls");
			printf("Meno hraca 1: %s\n", &player1);
			printf("Meno hraca 2: %s\n", &player2);
			printf("Velkost hracieho pola: %dx%d \n", velkostX, velkostY);
			printf("Zacina hrac1/hrac2  [0/1] :  %d\n", startPlayer);
			int c;
			while ((c = getchar()) != '\n' && c != EOF) {}
			break;

		case 's':
			do
			{
				vykreslenieDosky(hraciaDoska, velkostX, velkostY);
				urobTah(hraciaDoska, &startPlayer, player1, player2);

			} while (1);


			while ((c = getchar()) != '\n' && c != EOF) {}
			break;

		case 'l':

			break;
		}
	} while (opt != 'q'); 

	for (int i = 0; i < velkostX; i++)
	{
		free(hraciaDoska[i]);
	}
	//free(hraciaDoska);
	return 0;
}
