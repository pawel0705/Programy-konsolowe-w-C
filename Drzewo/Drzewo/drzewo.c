/*
Tworzenie drzewa w c:
1) Wczytanie ciagu liczb.
2) Wstawienie liczb do drzewa binarnego.
3) Wypisanie w kolejnosci malejacej.

@autor
Pawel Salicki
*/

#define _CRT_SECURE_NO_WARNINGS //by uzyc w Visual Studio funkcji 'scanf'
#include <stdio.h>

typedef
struct drzewo //struktura drzewa
{
	int liczba; //przechowywanie liczby
	struct drzewo* lewo; //wskaznik na lewego syna
	struct drzewo* prawo; //wskaznik na prawego syna
} wezel;

/* deklaracje funkcji */
void wstaw(wezel** korzen, wezel* element); //wstawianie elementu do drzewa
void drukuj(wezel* korzen); //drukowanie drzewa
void zwolnij_pamiec(wezel* korzen); //zwalnianie pamieci przez dynamiczne drzewo
void wypelnij_tablice_liczbami(int* tablica_liczb, int N); //wypelnianie zczytanych liczb uzytkownika do tablicy dynamicznej

int main(int argc, char* argv)
{
	int N = 0; //wielkosc tablicy, ilosc liczb wprowadzonych przez uzytkownika
	int liczba = 0; //zmienna pomocnicza do wstawiania liczby do drzewa
	int* tablica_liczb; //utworzenie jednowymiarowej tablicy
	wezel* element, * korzen = NULL; //zmienne o typie drzewiastym

	printf("Ile elementow chcesz umiescic?: ");
	scanf("%d", &N); //zczytanie liczby elementow ile chce wprowadzic uzytkownik
	puts("Wpisz je: ");
	tablica_liczb = (double*)malloc(N * sizeof(double)); //utworzenie zmiennej dynamicznej tablicy, zaalokowanie pamieci

	wypelnij_tablice_liczbami(tablica_liczb, N);

	for (int i = 0; i < N; i++)
	{
		liczba = tablica_liczb[i]; //pobranie liczby z tablicy
		element = (wezel*)malloc(sizeof(wezel)); //zaalokowanie pemieci 
		element->lewo = element->prawo = NULL; //nadanie lewemu i prawemu wskaznikowi wartosci 0
		element->liczba = liczba; //wstawienie do pierwszego elementu drzewa liczby
		wstaw(&korzen, element);
	}

	free(tablica_liczb); //zwolnienie pamieci dynamicznej tablicy

	printf("Liczby w kolejnosci malejacej:\n");

	drukuj(korzen);
	zwolnij_pamiec(korzen);

	getchar(); //czekanie na znak od uzytkownika
	return 0;
}

void wstaw(wezel** korzen, wezel* element) //wstawianie elementow do lisci drzewa
{
	if (!(*korzen))
	{
		*korzen = element;
		return;
	}
	else
	{
		if (element->liczba < (*korzen)->liczba)
		{
			wstaw(&(*korzen)->lewo, element);
		}
		else
			wstaw(&(*korzen)->prawo, element);
	}
}

void drukuj(wezel* korzen) //wypisywanie elementow drzewa nierosnaco
{
	if (korzen)
	{
		drukuj(korzen->prawo);
		printf("Liczba w drzewie: %d\n", korzen->liczba);
		drukuj(korzen->lewo);
	}
}

void zwolnij_pamiec(wezel* korzen) //zwolnienie pamieci
{
	if (korzen != NULL)
	{
		zwolnij_pamiec(korzen->prawo);
		zwolnij_pamiec(korzen->lewo);
		free(korzen);
	}
}

void wypelnij_tablice_liczbami(int* tablica_liczb, int N) //wypelnianie tablicy liczbami od uzytkownika
{
	for (int i = 0; i < N; i++)
	{
		float pojemnik = 0;
		scanf("%f", &pojemnik);
		tablica_liczb[i] = pojemnik;
	}

	while (getc(stdin) != '\n') //jezeli uzytkownik podawal liczby po spacji i jest ich wiecej niz mialo byc, to ta funkcja je pobierze do siebie i zwolni sie bufor
	{
	}
}
