#define _CRT_SECURE_NO_WARNINGS
#define ROZMIAR 200

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
Program, odczytuje nazwe pliku z parametru,
a nastepnie odwraca jego zawartosc w ponizszy sposob:
123		789
456	->	456
789		123

W buforze przetrzymywany jest maksymalnie JEDEN znak.

@autor
Pawel Salicki
*/

void czytaj_plik(char* nazwa_pliku);

int main(int argc, char* argv[])
{
	char nazwa_pliku[ROZMIAR]; //deklaracja tablicy, ktora przechowuje sciezke do pliku

	if (argc == 2)
	{
		strcpy(nazwa_pliku, argv[1]); //skopiowanie nazwy pliku z linii polecen do tablicy
		czytaj_plik(nazwa_pliku); //przejscie do funkcji odpowiedzialnej za zmodyfikowanie pliku
	}
	else
	{
		puts("W linii polecen, po wpisaniu nazwy programu, wprowadz nazwe pliku!\n");
	}

	return 0;
}

void czytaj_plik(char* nazwa_pliku) //funkcja odwracajaca zawartosc pliku
{
	FILE* plik = fopen(nazwa_pliku, "r+"); //otwarcie pliku do czytania i edytowania

	if (plik == NULL)
	{
		perror("Nie mozna otworzyc pliku!");
		return;
	}

	int ilosc_znakow_od_poczatku = 0; //ilosc znakow od poczatku pliku do konca linijki ktora jeszcze nie zostala przeniesiona
	int ilosc_znakow_do_konca = 0; //punkt graniczny pierwotnego pliku
	int ilosc_znakow_w_linii = 0; //ilosc znakow w jednej linii
	int ilosc_znakow_w_pliku; //ilosc znakow na poczatku
	int ilosc_linii = 1; //ilosc linii w pliku
	int tmp = 0; //przechowywanie znaku z pliku w postaci liczby z tablicy ASCII
	int ile_przetworzonych_znakow = 0; //ilosc znakow w danej linii pliku

	while (tmp != EOF) //zliczanie ilosci linijek w pliku
	{
		tmp = getc(plik);
		if (tmp == '\n')
		{
			ilosc_linii++;
		}
	}

	fseek(plik, 0, SEEK_END);
	ilosc_znakow_w_pliku = ftell(plik); //pobranie pierwotnej liczby znakow z pliku
	fseek(plik, 0, SEEK_SET);

	int i = 1; //zmienna pomagajaca kontrolowac petle

	while (ilosc_linii != 0)
	{
		fseek(plik, 0, SEEK_SET); //ustawienie sie na poczatku pliku

		while ((tmp = getc(plik)) != EOF)
		{
			if (tmp == '\n')
			{
				ilosc_znakow_od_poczatku = ftell(plik); //zliczanie ilosci znakow od poczatku pliku do linijki ktora jeszcze nie zostala odwrocona
				i++;
			}
			if (i == ilosc_linii)
				break;
		}

		i = 1; //zresetowanie zmiennej pomocniczej

		fseek(plik, -(ile_przetworzonych_znakow), SEEK_END); //ustawienie sie na poczatku linijki
		ilosc_znakow_do_konca = ftell(plik); //odczytanie ilosci znakow od poczatku pliku do poczatku edytowanej linijki
		ilosc_znakow_w_linii = ilosc_znakow_do_konca - ilosc_znakow_od_poczatku; //okreslenie ilosci znakow w linii, ktora ma byc odwrocona
		ile_przetworzonych_znakow += ilosc_znakow_w_linii; //ile znakow zostalo w pliku odwroconych
		fseek(plik, -ile_przetworzonych_znakow, SEEK_END); //ustawienie sie na poczatek linii

		for (int j = 0; j < ilosc_znakow_w_linii; j++) //przenoszenie danej linijki na koniec pliku
		{
			tmp = getc(plik);
			if (tmp == '\n')
				break;
			fseek(plik, 0, SEEK_END);
			putc(tmp, plik);
			fseek(plik, -(ile_przetworzonych_znakow), SEEK_END);
		}

		fseek(plik, 0, SEEK_END);
		ilosc_linii--;

		if (ilosc_linii != 0)
		{
			putc('\n', plik); //dodanie znaku "przejscia do nowej linii" by znaki nie byly sklejone
			ile_przetworzonych_znakow += (ilosc_znakow_w_linii + 2); //uwzglednienie do ilosci przetworzonych znakow, znaku "przejscia do nowej linii"
			ilosc_znakow_od_poczatku = 0;
		}
	}
	fseek(plik, 0, SEEK_SET);

	for (int j = 0; j < ilosc_znakow_w_pliku; j++) //w pliku znajduje sie oryginalna wersja tekstu oraz odwrocona
	{
		fputc('\r', plik); //usuniecie oryginalnej wersji tekstu za pomoca znaku "powrotu karetki"
	}

	fclose(plik);

	printf("Plik \" %s \" zostal pomyslnie odwrocony!", nazwa_pliku);
}
