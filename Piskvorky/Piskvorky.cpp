// Piskvorky.cpp : Defines the entry point for the application.
//

#include "Piskvorky.h"
#include <iostream>
#include <math.h>
#include <time.h>
int vyhra;
using namespace std;

bool winCheck(int** P, int x, int y, int velkostX, int velkostY);

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
			scanf_s("%s", player1, PLAYER_NAME_SIZE);
			fprintf_s(subor, "%s\n", player1);
			while ((c = getchar()) != '\n' && c != EOF) {}
			
			printf("\nZadajte meno hraca 2 : \n");
			scanf_s("%s", player2, PLAYER_NAME_SIZE);
			fprintf_s(subor, "%s\n", player2);
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
		vyberMena(player1, player2);
		break;
	}
	
	
}

void vyberVelkosti(int *velkostX,int *velkostY)
{
	
	do
	{
		system("cls");
		printf("Prosim zadajte velkost hracieho pola (min 3x3)\n");
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

void vykreslenieDosky(int** hraciaDoska,int velkostX,int velkostY)
{
	system("cls");
	for (int l = 1; l < (velkostX + 1); l++)
	{
		printf("  %c%c%d%c%c ", ' ', ' ', l, ' ', ' ');
	}printf("\n");
	for (int k = 2; k < (velkostY+2); k++)
	{
		//printf("%d", k - 1);
		for (int i = 0; i < 3; i++)
		{
			switch (i)
			{
			case 0:
			{
				
				for (int j = 2; j < (velkostX+2); j++)
				{
					printf("  %c%c%c%c%c ", UPPER_LEFT_CORNER, HORIZ, HORIZ, HORIZ, UPPER_RIGHT_CORNER);
				}
				printf("\n");
				break;
			}

			case 1:
			{
				
				for (int j = 2; j < (velkostX+2); j++)
				{
					if (hraciaDoska[j][k] != -2)
					{
						if (j == 2)
							printf("%d%c%c%c%d%c%c ", k - 1, ' ', VERT, ' ', hraciaDoska[j][k], ' ', VERT);
						else
							printf(" %c%c%c%d%c%c ", ' ', VERT, ' ', hraciaDoska[j][k], ' ', VERT);
							
					}
					else
						if(j==2)
							printf("%d%c%c%c%c%c%c ",k-1, ' ', VERT, ' ', ' ', ' ', VERT);
						else
							printf(" %c%c%c%c%c%c ",  ' ', VERT, ' ', ' ', ' ', VERT);
				}
				printf("\n");
				break;
			}

			case 2:
			{
				
				for (int j = 2; j < (velkostX+2); j++)
				{
					printf("  %c%c%c%c%c ", LOWER_LEFT_CORNER, HORIZ, HORIZ, HORIZ, LOWER_RIGHT_CORNER);
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


void urobTah(int** hraciaDoska , bool *startPlayer, char* player1, char* player2, int velkostX, int velkostY)
{
	int zadaneX = 2;
	int zadaneY = 2;
	int c = 2;
	if (*startPlayer == 0)
	{
		printf("Na tahu je hrac: %s\n", player1);
		do {
			printf("Zadajte suradnice [ X,Y ]\n");
			scanf_s("%d,%d", &zadaneX, &zadaneY);
			while ((c = getchar()) != '\n' && c != EOF) {}

		} while (zadaneX < 1 || zadaneX > velkostX || zadaneY < 1 || zadaneY > velkostY || hraciaDoska[zadaneX + 1][zadaneY + 1 ] == 0 || hraciaDoska[zadaneX + 1][zadaneY + 1] == 1);

		hraciaDoska[zadaneX + 1][zadaneY + 1] = 0;
		if (winCheck(hraciaDoska, zadaneX, zadaneY, velkostX, velkostY) == true)
		{

			system("cls");
			vykreslenieDosky(hraciaDoska, velkostX, velkostY);
			printf("\n\n\n!!!\tVYHRAL %s\t!!!\n\n\n", player1);
			vyhra = 1;
		}

	}///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	else if (*startPlayer == 1)
	{
		printf("Na tahu je hrac: %s\n", player2);
		do
		{
			printf("Zadajte suradnice [ X,Y ]\n");
			scanf_s("%d,%d", &zadaneX, &zadaneY);
			while ((c = getchar()) != '\n' && c != EOF) {}

		} while (zadaneX < 1 || zadaneX > velkostX || zadaneY < 1 || zadaneY > velkostY || hraciaDoska[zadaneX + 1][zadaneY + 1] == 0 || hraciaDoska[zadaneX + 1][zadaneY + 1] == 1);
		
		hraciaDoska[zadaneX + 1][zadaneY + 1] = 1;

		if (winCheck(hraciaDoska, zadaneX, zadaneY, velkostX, velkostY) == true)
		{
			system("cls");
			vykreslenieDosky(hraciaDoska, velkostX, velkostY);
			printf("\n\n\n!!!\tVYHRAL %s\t!!!\n\n\n", player2);
			vyhra = 1;
		}
	}
	*startPlayer = !(*startPlayer);
	
}



int main()
{
	int velkostX=3;
	int velkostY=3;
	char player1[PLAYER_NAME_SIZE];
	char player2[PLAYER_NAME_SIZE];
	char opt;
	bool startPlayer=0;
	int** hraciaDoska = NULL;
	int rozmerX;
	int rozmerY;
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
			rozmerX = velkostX + 4;
			rozmerY = velkostY + 4;
			

			break;
		case 'z':
			FILE * subor;
			if (fopen_s(&subor, "menahracov.txt", "r") != 0)
			{
				printf("\nProsim najprv vyplnte nastavenia!\n");
				break;

			}
			else {

				fseek(subor, 0, SEEK_END);
				if (ftell(subor) == 0)
				{
					system("cls");
					printf("\n\n!!Mena z predoslej hry nie su dostupne!!\n");
					printf("Prosim vyplnete najprv nastavenia.\n\n");
					fclose(subor);
					break;
				}
				else
				{
					fseek(subor, 0, SEEK_SET);
					fscanf_s(subor, "%s", player1, PLAYER_NAME_SIZE);
					fscanf_s(subor, "%s", player2, PLAYER_NAME_SIZE);

					system("cls");
					printf("Meno hraca 1: %s\n", &player1);
					printf("Meno hraca 2: %s\n", &player2);
					printf("Velkost hracieho pola: %dx%d \n", velkostX, velkostY);
					printf("Zacina hrac1/hrac2  [0/1] :  %d\n", startPlayer);
					int c;
					while ((c = getchar()) != '\n' && c != EOF) {}
					fclose(subor);
					break;
				}
			}
			

		case 's':

			hraciaDoska = (int**)calloc((rozmerX),sizeof(int));
			for (int i = 0; i < (velkostX + 4); i++)
			{
				hraciaDoska[i] = (int*)calloc((rozmerY), sizeof(int));
			}

			for (int i = 0; i < (velkostY + 4); i++)
			{
				for (int j = 0; j < (velkostX + 4); j++)
				{
					hraciaDoska[j][i] = -2;
				}
			}

			do
			{
				vykreslenieDosky(hraciaDoska, velkostX, velkostY);
				urobTah(hraciaDoska, &startPlayer, player1, player2, velkostX, velkostY);
				
			} while (vyhra != 1);


			while ((c = getchar()) != '\n' && c != EOF) {}
			break;

		case 'l':

			break;
		}
	} while (opt != 'q'); 

	for (int i = 0; i < (velkostX+4); i++)
	{
		free(hraciaDoska[i]);
	}
	//free(hraciaDoska);
	return 0;
}


bool winCheck(int** P, int xx, int yy,int velkostX, int velkostY)
{
	int x = xx + 1;
	int y = yy + 1;
	
	if (SS2 ||	SL ||	SP ||	SS1 ||	SD ||	SH ||	HS ||	HH ||	HD ||	VS ||	VD ||	VH )
	{
		return true;
	}
	else
		return false;
	
}