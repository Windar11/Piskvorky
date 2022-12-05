// Piskvorky.cpp : Defines the entry point for the application.
//

#include "Piskvorky.h"
#include "Lederboard.h"
#include <iostream>
#include <math.h>
#include <time.h>
int vyhra;
using namespace std;

typedef struct
{
	int obsadene;
	char meno[NAME_SIZE];
	int pocetVyhier;
}leader;

void addToBoard(leader* LeaderBoard,char* meno)
{
	FILE* board = NULL;
	fopen_s(&board, "leaderboard.txt", "r");
	if (board != NULL)
	{
		printf("errror");
	}
	else
	{
		int poz=27;
		bool found = false;
		for (int i = 0; i < 10; i++)
		{
			if (board != 0)
			{
				fscanf_s(board, "%d\n", &LeaderBoard[i].obsadene);
				fscanf_s(board, "%s\n", LeaderBoard[i].meno, 20);
				fscanf_s(board, "%d\n", &LeaderBoard[i].pocetVyhier);

				if (LeaderBoard[i].meno == meno)
				{
					found = true;
					LeaderBoard[i].pocetVyhier = LeaderBoard[i].pocetVyhier + 1;
					break;
				}
			}
		}
		fclose(board);
		


		if (found == false)
		{
			for (int i = 0; i < 10; i ++ )
			{
				if (LeaderBoard[(i)].obsadene == 0 )
				{
					poz = i;
					break;
				}
			}
			LeaderBoard[poz].obsadene = 1;
			strcpy_s(LeaderBoard[poz].meno, meno);
			LeaderBoard[poz].pocetVyhier =  1;
		}
		


		if (fopen_s(&board, "leaderboard.txt", "w") != 0)
		{
			printf("errror");
		}
		else
		{
			for (int i = 0; i < poz; i++)
			{
				fprintf(board, "%d\n", LeaderBoard[i].obsadene);
				fprintf(board,"%s\n", LeaderBoard[i].meno);
				fprintf(board, "%d\n", LeaderBoard[i].pocetVyhier);
								
			}
			for (int i = (poz+1); i < 10; i++)
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
	fopen_s(&board, "leaderboard.txt", "r");
	for (int j = 0; j < 10; j++)
	{
		fscanf_s(board, "%d\n", &LeaderBoard[j].obsadene);
		fscanf_s(board, "%s\n", LeaderBoard[j].meno, 20);
		fscanf_s(board, "%d\n", &LeaderBoard[j].pocetVyhier);

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


bool winCheck(int** P, int x, int y, int velkostX, int velkostY);

void vyberMena(char *player1, char *player2)
{
	FILE* subor;
	char nove;
	//char znak;
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
	
	for (int z = 0; z < velkostX; z++)
	{
		printf("  %c%c%d%c%c ",' ',' ', (z+1),' ',' ');
	}
	printf("\n");
	
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

					if (j == 2)
					{
						switch (hraciaDoska[j][k])
						{
						case 0:
						{
							printf("%d%c%c%c%c%c%c ", k - 1, ' ', VERT, ' ', 'O', ' ', VERT);
							break;
						}
						case 1:
						{
							printf("%d%c%c%c%c%c%c ", k - 1, ' ', VERT, ' ', 'X', ' ', VERT);
							break;
						}

						default:
							printf("%d%c%c%c%c%c%c ", k - 1, ' ', VERT, ' ', ' ', ' ', VERT);
							break;
						}
					}
					else
					{
						switch (hraciaDoska[j][k])
						{
						case 0:
						{
							printf(" %c%c%c%c%c%c ", ' ', VERT, ' ', 'O', ' ', VERT);
							break;
						}
						case 1:
						{
							printf(" %c%c%c%c%c%c ", ' ', VERT, ' ', 'X', ' ', VERT);
							break;
						}

						default:
							printf(" %c%c%c%c%c%c ", ' ', VERT, ' ', ' ', ' ', VERT);
							break;
						}
					}
					
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

void jeRemiza(int** P, int velkostX, int velkostY)
{
	int o = 0;
	for (int i = 2; i < (velkostY + 2); i++)
	{
		for (int j = 2; j < (velkostX + 2); j++)
		{
			if (P[j][i] == -2)
			{
				i = velkostX + 2;
				j = velkostY + 2;
			}
			else
			{
				o++;
			}
		}
	}if (o == velkostX * velkostY)
	{
		system("cls");
		vykreslenieDosky(P, velkostX, velkostY);
		printf("\n\n\n!!!\tREMIZA\t!!!\n\n");
		vyhra = 1;
	}
}

void urobTah(int** hraciaDoska , bool *startPlayer, char* player1, char* player2, int velkostX, int velkostY,int *pocetTahov1, int *pocetTahov2,leader* LeaderBoard)
{
	int zadaneX = 2;
	int zadaneY = 2;
	int c = 2;
	if (*startPlayer == 0)
	{
		
		printf("Na tahu je hrac: %s (O)\n", player1);
		do {
			printf("Zadajte suradnice [ X,Y ]\n");
			scanf_s("%d,%d", &zadaneX, &zadaneY);
			while ((c = getchar()) != '\n' && c != EOF) {}

		} while (zadaneX < 1 || zadaneX > velkostX || zadaneY < 1 || zadaneY > velkostY || hraciaDoska[zadaneX + 1][zadaneY + 1 ] == 0 || hraciaDoska[zadaneX + 1][zadaneY + 1] == 1);
		
		(*pocetTahov1)++;
		hraciaDoska[zadaneX + 1][zadaneY + 1] = 0;

		if (winCheck(hraciaDoska, zadaneX, zadaneY, velkostX, velkostY) == true)
		{

			system("cls");
			vykreslenieDosky(hraciaDoska, velkostX, velkostY);
			printf("\n\n\n!!!\tVYHRAL %s\t!!!\n\n", player1);
			printf("\tPocet tahov: %d\t\n\n\n", *pocetTahov1);
			addToBoard(LeaderBoard, player1);
			vyhra = 1;
			
		}else
			jeRemiza(hraciaDoska, velkostX, velkostY);
		
		

	}///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	else if (*startPlayer == 1)
	{
		printf("Na tahu je hrac: %s (X)\n", player2);
		do
		{
			printf("Zadajte suradnice [ X,Y ]\n");
			scanf_s("%d,%d", &zadaneX, &zadaneY);
			while ((c = getchar()) != '\n' && c != EOF) {}

		} while (zadaneX < 1 || zadaneX > velkostX || zadaneY < 1 || zadaneY > velkostY || hraciaDoska[zadaneX + 1][zadaneY + 1] == 0 || hraciaDoska[zadaneX + 1][zadaneY + 1] == 1);
		
		(*pocetTahov2)++;
		hraciaDoska[zadaneX + 1][zadaneY + 1] = 1;

		if (winCheck(hraciaDoska, zadaneX, zadaneY, velkostX, velkostY) == true)
		{
			system("cls");
			vykreslenieDosky(hraciaDoska, velkostX, velkostY);
			printf("\n\n\n!!!\tVYHRAL %s\t!!!\n\n", player2);
			printf("\tPocet tahov: %d\t!!!", *pocetTahov2);
			addToBoard(LeaderBoard, player2);
			vyhra = 1;
		}else
			jeRemiza(hraciaDoska, velkostX, velkostY);
		
		
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
	int pocetTahov1=0;
	int pocetTahov2=0;
	leader LeaderBoard[10];
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
				urobTah(hraciaDoska, &startPlayer, player1, player2, velkostX, velkostY,&pocetTahov1, &pocetTahov2, LeaderBoard);			

			} while (vyhra != 1);

			for (int i = 0; i < (velkostX + 4); i++)
			{
				free(hraciaDoska[i]);
			}
			free(hraciaDoska);

			while ((c = getchar()) != '\n' && c != EOF) {}
			break;

		case 'l':
			ShowBoard(LeaderBoard);
			break;
		}
	} while (opt != 'q'); 

	
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