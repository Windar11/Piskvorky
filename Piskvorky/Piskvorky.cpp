// Piskvorky.cpp : Defines the entry point for the application.
//

#include "Piskvorky.h"
#include <iostream>
#include <math.h>

#define PLAYER_NAME_SIZE 20

using namespace std;

void vyberMena(char *player1, char *player2)
{
	FILE* subor;
	char nove;
	char znak;
	printf("Chcete vytvorit nove mena? a[ANO] / n[NIE]\n");
	nove = tolower(getchar());
	while (getchar() != '\n');
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
			while (getchar() != '\n');
			fprintf(subor, "%s\n", &player1);
			printf("\nZadajte meno hraca 2 : \n");
			scanf_s("%s", &player2, PLAYER_NAME_SIZE);
			while (getchar() != '\n');
			fprintf(subor, "%s\n", &player2);
			fclose(subor);
			break;
		}

	case 'n':
		printf("\n\nMena z predchadzajucej hry\n\n");
		if (fopen_s(&subor, "menahracov.txt", "r") != 0)
		{
			printf("errror");
		}
		else
		{
			
			//printf("good");
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
			fscanf_s(subor, "%s", &player1, PLAYER_NAME_SIZE);
			fscanf_s(subor, "%s", &player2, PLAYER_NAME_SIZE);
			printf("\n%s\n", &player1);
			printf("%s\n", &player2);
		

		}
		break;
	default:
		printf("!!!Vozeny nespravny znak.!!!\n");
		printf("Prosim zadajte znova.\n\n");
		vyberMena(player1, player1);
		break;
	}
	
	
}

int main()
{
	
	char *player1[PLAYER_NAME_SIZE];
	char *player2[PLAYER_NAME_SIZE];

	vyberMena(*player1,*player2);
	//printf("\n%s\n", *player1, PLAYER_NAME_SIZE);
	//printf("%s\n", *player2, PLAYER_NAME_SIZE);
	return 0;
}
