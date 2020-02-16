#define _CRT_SECURE_NO_WARNINGS
#define MAX_DLUGOSC 256

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Program pobiera od u¿ytkownika ci¹g liter (dowolne zdanie).
W kolejnym kroku pobiera kolejny ci¹g liter, które maj¹ byæ odszukane we wprowadzonym wczeœniej ci¹gu.
Jako wynik dla ka¿dej litery jest zwracany numer indeksu jej wystêpowania w zdaniu, w postaci mapy.

@autor
Pawel Salicki
*/

void znajdz(int*** mapa, char* dowolny_napis, char* zbior_malych_liter)
{
	int j = 0;
	int x = 0;
	int y = 0;
	int** mapa_tmp;

	mapa_tmp = (int**)malloc(strlen(zbior_malych_liter) * sizeof(int*));
	for (int i = 0; i < strlen(zbior_malych_liter); i++)
	{
		mapa_tmp[i] = (int*)malloc(strlen(dowolny_napis) * sizeof(int));
	}

	for (int i = 0; i < strlen(zbior_malych_liter); i++)
	{
		for (int j = 0; j < strlen(dowolny_napis); j++)
			mapa_tmp[i][j] = 0;
	}

	for (int i = 0; i < strlen(dowolny_napis) + 1; i++)
	{
		if (dowolny_napis[i] == zbior_malych_liter[j] || dowolny_napis[i] == (zbior_malych_liter[j]) - 32)
		{
			mapa_tmp[x][y] = ++i;
			--i;
			y++;
		}
		if (dowolny_napis[i] == '\0')
		{
			x++;
			j++;
			i = 0;
			y = 0;
		}
		if (zbior_malych_liter[j] == '\0')
			break;
	}
	*mapa = mapa_tmp;
}

void wypisz(int** mapa, int x, int y)
{
	puts("Zawartosc mapy:");
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			if (j == 0)
				printf("[");

			if (mapa[i][j] == 0)
			{
				printf("]\n");
				break;
			}
			else
				printf("%i", mapa[i][j]);

			if (mapa[i][j + 1] != 0)
				printf(",");
		}
	}
}

void zwolnij_pamiec(int** mapa, int N)
{
	for (int i = 0; i < N; i++)
		free(mapa[i]);
	free(mapa);
}

int main(int argc, char* argv[])
{
	int** mapa;
	char* dowolny_napis;
	char* zbior_malych_liter;

	dowolny_napis = (char*)malloc(MAX_DLUGOSC * sizeof(*dowolny_napis));
	if (dowolny_napis == NULL)
		return EXIT_FAILURE;

	zbior_malych_liter = (char*)malloc(MAX_DLUGOSC * sizeof(*zbior_malych_liter));
	if (zbior_malych_liter == NULL)
		return EXIT_FAILURE;

	puts("Podaj dowolny napis:");
	fgets(dowolny_napis, MAX_DLUGOSC, stdin);
	puts("Podaj zbior malych liter:");
	fgets(zbior_malych_liter, MAX_DLUGOSC, stdin);

	if ((strlen(dowolny_napis) > 0) && (dowolny_napis[strlen(dowolny_napis) - 1] == '\n'))
		dowolny_napis[strlen(dowolny_napis) - 1] = '\0';
	if ((strlen(zbior_malych_liter) > 0) && (zbior_malych_liter[strlen(zbior_malych_liter) - 1] == '\n'))
		zbior_malych_liter[strlen(zbior_malych_liter) - 1] = '\0';

	znajdz(&mapa, dowolny_napis, zbior_malych_liter);
	wypisz(mapa, strlen(zbior_malych_liter), strlen(dowolny_napis));
	zwolnij_pamiec(mapa, strlen(zbior_malych_liter));
	free(dowolny_napis);
	free(zbior_malych_liter);
	getchar();
	return 0;
}