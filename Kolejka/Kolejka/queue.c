#define _CRT_SECURE_NO_WARNINGS

#define MAX 30
#define PESEL 0
#define OSOBA 1
#define EXIT 11

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

/*
Podstawowe operacje na strukturze - kolejka.

@autor
Pawel Salicki
*/

union informacje
{
	char imie_nazwisko[MAX];
	uint64_t pesel;
}informacje;

typedef
struct kolejka
{
	int co_wpisal_uzytkownik;
	union informacje informacje;
	struct kolejka* nastepny;
	struct kolejka* poprzedni;
}kolejka;

void umiesc_element_na_poczatku_kolejki(kolejka** glowa, kolejka** ogon, uint64_t nr_pesel, char* dane_osobowe, int co_wpisal_uzytkownik)
{
	kolejka* kolejka_tmp;
	kolejka_tmp = (kolejka*)malloc(sizeof(kolejka));
	if (co_wpisal_uzytkownik == PESEL)
		kolejka_tmp->informacje.pesel = nr_pesel;
	else
		strcpy(kolejka_tmp->informacje.imie_nazwisko, dane_osobowe);
	kolejka_tmp->co_wpisal_uzytkownik = co_wpisal_uzytkownik;

	kolejka_tmp->nastepny = NULL;
	kolejka_tmp->poprzedni = NULL;

	if (*glowa == NULL)
	{
		*glowa = kolejka_tmp;
		*ogon = kolejka_tmp;
	}
	else
	{
		kolejka_tmp->poprzedni = NULL;
		kolejka_tmp->nastepny = *glowa;
		(*glowa)->poprzedni = kolejka_tmp;
		*glowa = kolejka_tmp;
	}

}

void wstaw_element(kolejka** glowa, kolejka** ogon, uint64_t nr_pesel, char* dane_osobowe, int co_wpisal_uzytkownik)
{
	kolejka* kolejka_tmp;
	kolejka_tmp = (kolejka*)malloc(sizeof(kolejka));

	if (co_wpisal_uzytkownik == PESEL)
		kolejka_tmp->informacje.pesel = nr_pesel;
	else
		strcpy(kolejka_tmp->informacje.imie_nazwisko, dane_osobowe);

	kolejka_tmp->co_wpisal_uzytkownik = co_wpisal_uzytkownik;
	kolejka_tmp->nastepny = NULL;
	kolejka_tmp->poprzedni = NULL;

	if (*glowa == NULL)
	{
		*glowa = kolejka_tmp;
		*ogon = kolejka_tmp;
	}
	else
	{
		kolejka_tmp->poprzedni = *ogon;
		(*ogon)->nastepny = kolejka_tmp;
		(*ogon) = kolejka_tmp;
	}
}

void wyswietl_liste(kolejka* glowa)
{
	while (glowa != NULL)
	{
		if (glowa->co_wpisal_uzytkownik == PESEL)
			printf("%lld\n", glowa->informacje.pesel);
		else
			printf("%s\n", glowa->informacje.imie_nazwisko);

		glowa = glowa->nastepny;
	}
}

void usun_kolejke(kolejka** glowa)
{
	kolejka* kolejka_tmp;

	while (*glowa != NULL)
	{
		kolejka_tmp = *glowa;
		*glowa = (*glowa)->nastepny;
		free(kolejka_tmp);
	}
}

kolejka* szukaj_elementu(kolejka* glowa, char* dane_osobowe, int co_wpisal_uzytkownik)
{
	kolejka* glowa_tmp;
	uint64_t tmp;

	glowa_tmp = glowa;

	if (co_wpisal_uzytkownik == PESEL)
	{
		tmp = strtoull(dane_osobowe, NULL, 0);
		while (glowa_tmp != NULL && glowa_tmp->informacje.pesel != tmp)
		{
			glowa_tmp = glowa_tmp->nastepny;
		}
	}
	else
	{
		while (glowa_tmp != NULL && strcmp(glowa_tmp->informacje.imie_nazwisko, dane_osobowe) != 0)
		{
			glowa_tmp = glowa_tmp->nastepny;
		}
	}
	return glowa_tmp;
}

void usun_po_lub_przed(kolejka** glowa, char* dane_osobowe, int co_wpisal_uzytkownik, int jaka_operacja)
{
	kolejka* tmp, * pomoc;
	tmp = szukaj_elementu(*glowa, dane_osobowe, co_wpisal_uzytkownik);

	if (tmp != NULL)
	{
		if (jaka_operacja == PESEL)
			tmp = tmp->nastepny;
		else
			tmp = tmp->poprzedni;
	}

	if (tmp == NULL)
		puts("Nie ma klucza ktorego mozna by usunac!");
	else
		if (tmp == *glowa)
		{
			*glowa = (*glowa)->nastepny;
			free(tmp);
		}
		else
		{
			pomoc = *glowa;
			if (co_wpisal_uzytkownik == OSOBA)
			{
				while ((strcmp(pomoc->nastepny->informacje.imie_nazwisko, tmp->informacje.imie_nazwisko) != 0))
					pomoc = pomoc->nastepny;

				if (pomoc->nastepny != NULL)
					pomoc->nastepny->poprzedni = tmp->poprzedni;

				pomoc->nastepny = tmp->nastepny;
				free(tmp);
			}
			else
			{
				while (pomoc->nastepny->informacje.pesel == tmp->informacje.pesel)
					pomoc = pomoc->nastepny;

				if (pomoc->nastepny != NULL)
					pomoc->nastepny->poprzedni = tmp->poprzedni;

				pomoc->nastepny = tmp->nastepny;
				free(tmp);
			}
		}
}

int sprawdz_co_zostalo_wpisane(char* dane_osobowe, int jak_dlugi)
{
	for (int i = 0; i < jak_dlugi; i++)
	{
		if (dane_osobowe[i] >= 48 && dane_osobowe[i] <= 57)
		{
			return  PESEL;
		}
	}
	return OSOBA;
}

void dodaj_po_lub_przed(kolejka* glowa, uint64_t nr_pesel, char* dane_osobowe, int co_wpisal_uzytkownik, int jaka_operacja)
{
	if (glowa == NULL)
	{
		puts("Nie mozna wstawic elementu bo jest to pierwszy element, wybierz opcje wstawiania do kolejki lub na poczatku!");
		return;
	}

	kolejka* kolejka_tmp;
	kolejka_tmp = (kolejka*)malloc(sizeof(kolejka));

	if (co_wpisal_uzytkownik == PESEL)
		kolejka_tmp->informacje.pesel = nr_pesel;
	else
		strcpy(kolejka_tmp->informacje.imie_nazwisko, dane_osobowe);

	kolejka_tmp->co_wpisal_uzytkownik = co_wpisal_uzytkownik;
	kolejka_tmp->nastepny = NULL;
	kolejka_tmp->poprzedni = NULL;

	if (jaka_operacja == PESEL)
	{
		kolejka_tmp->nastepny = glowa->nastepny;
		glowa->nastepny = kolejka_tmp;
		kolejka_tmp->poprzedni = glowa;

		if (kolejka_tmp->nastepny != NULL)
			kolejka_tmp->nastepny->poprzedni = kolejka_tmp;
	}
	else
	{
		kolejka_tmp->poprzedni = glowa->poprzedni;
		glowa->poprzedni = kolejka_tmp;
		kolejka_tmp->nastepny = glowa;

		if (kolejka_tmp->poprzedni != NULL)
			kolejka_tmp->poprzedni->nastepny = kolejka_tmp;
	}
}

uint64_t wyszukaj_peselu(int rok_uzytkownika, kolejka* glowa, int co_wpisal_uzytkownik)
{
	kolejka* glowa_tmp;
	uint64_t nr_pesel;

	int rok, miesiac;
	char liczby_odpowiadajace_za_rok[MAX];

	glowa_tmp = glowa;

	if (co_wpisal_uzytkownik == PESEL)
	{
		while (glowa_tmp != NULL)
		{
			nr_pesel = glowa_tmp->informacje.pesel;

			sprintf(liczby_odpowiadajace_za_rok, "%lld", nr_pesel);

			rok = 10 * (liczby_odpowiadajace_za_rok[0] - 48);
			rok += (liczby_odpowiadajace_za_rok[1] - 48);
			miesiac = 10 * (liczby_odpowiadajace_za_rok[2] - 48);
			miesiac += (liczby_odpowiadajace_za_rok[3] - 48);

			if (miesiac > 80 && miesiac < 93)
				rok += 1800;
			else if (miesiac > 0 && miesiac < 13)
				rok += 1900;
			else if (miesiac > 20 && miesiac < 33)
				rok += 2000;
			else if (miesiac > 40 && miesiac < 53)
				rok += 2100;
			else if (miesiac > 60 && miesiac < 73)
				rok += 2200;

			if (rok_uzytkownika == rok)
			{
				memset(liczby_odpowiadajace_za_rok, '\0', sizeof(liczby_odpowiadajace_za_rok));
				rok = 0;
				miesiac = 0;
				return nr_pesel;
			}
			else
			{
				rok = 0;
				miesiac = 0;
				glowa_tmp = glowa_tmp->nastepny;
			}
		}
	}
	rok = 0;
	miesiac = 0;
	memset(liczby_odpowiadajace_za_rok, '\0', sizeof(liczby_odpowiadajace_za_rok));
	return NULL;
}

int main(int argc, char* argv[])
{
	int jak_dlugi = 0;
	int wybor = 0;
	int jaka_operacja = 0;
	int co_wpisal_uzytkownik = 1;

	char wpis_uzytkownika[MAX];
	char nazwisko[MAX];

	uint64_t nr_pesel;

	kolejka* glowa = NULL;
	kolejka* ogon = NULL;
	kolejka* pomoc = NULL;

	while (1)
	{
		puts("------");
		puts("Co chcesz zrobic?\nWstaw odpowiednia cyfre:");
		puts("1 - Umiesc element w kolejce\n2 - Wyswietl zawartosc danych\n3 - Usun cala zawartosc danych\n4 - Znajdz dany element");
		puts("5 - Usun element PO podanym elemencie\n6 - Usun element PRZED podanym elementem\n7 - Dodaj element na sam poczatek");
		puts("8 - Dodaj element PO danym kluczu\n9 - Dodaj element PRZED danym kluczem\n10 - Wyszukaj numeru pesel, ktory pasuje do danego roku");
		puts("11 - Wyjscie z programu");
		puts("------");
		scanf("%d", &wybor);
		puts("------");

		switch (wybor)
		{
		case 1:
			puts("Podaj element (PESEL lub IMIE i NAZWISKO):");
			scanf("%s", &wpis_uzytkownika);
			jak_dlugi = strlen(wpis_uzytkownika);
			co_wpisal_uzytkownik = sprawdz_co_zostalo_wpisane(wpis_uzytkownika, jak_dlugi);

			if (co_wpisal_uzytkownik == OSOBA)
			{
				scanf("%s", &nazwisko);
				strcat(wpis_uzytkownika, " ");
				strcat(wpis_uzytkownika, nazwisko);
			}
			else
				nr_pesel = strtoull(wpis_uzytkownika, NULL, 0);

			while (getc(stdin) != '\n');

			wstaw_element(&glowa, &ogon, nr_pesel, &wpis_uzytkownika, co_wpisal_uzytkownik);
			break;
		case 2:
			wyswietl_liste(glowa);
			break;
		case 3:
			usun_kolejke(&glowa);
			break;
		case 4:
			puts("Wpisz element, by zobaczyc czy istnieje w bazie danych:");
			scanf("%s", &wpis_uzytkownika);

			while (getc(stdin) != '\n');

			jak_dlugi = strlen(wpis_uzytkownika);
			co_wpisal_uzytkownik = sprawdz_co_zostalo_wpisane(wpis_uzytkownika, jak_dlugi);

			if ((pomoc = szukaj_elementu(glowa, wpis_uzytkownika, co_wpisal_uzytkownik)) == NULL)
				printf("Nie znaleziono elementu: %s !\n", wpis_uzytkownika);
			else
				puts("Znaleziono taki element!");
			break;
		case 5:
			puts("Wpisz element PO ktorym ma byc usuniety element:");
			scanf("%s", &wpis_uzytkownika);

			jak_dlugi = strlen(wpis_uzytkownika);
			co_wpisal_uzytkownik = sprawdz_co_zostalo_wpisane(wpis_uzytkownika, jak_dlugi);

			if (co_wpisal_uzytkownik == OSOBA)
			{
				scanf("%s", &nazwisko);
				strcat(wpis_uzytkownika, " ");
				strcat(wpis_uzytkownika, nazwisko);
			}

			jaka_operacja = 0;

			while (getc(stdin) != '\n');

			jak_dlugi = strlen(wpis_uzytkownika);
			co_wpisal_uzytkownik = sprawdz_co_zostalo_wpisane(wpis_uzytkownika, jak_dlugi);
			usun_po_lub_przed(&glowa, wpis_uzytkownika, co_wpisal_uzytkownik, jaka_operacja);
			break;
		case 6:
			puts("Wpisz element PRZED ktorym ma byc usuniety element:");
			scanf("%s", &wpis_uzytkownika);

			jak_dlugi = strlen(wpis_uzytkownika);
			co_wpisal_uzytkownik = sprawdz_co_zostalo_wpisane(wpis_uzytkownika, jak_dlugi);

			if (co_wpisal_uzytkownik == OSOBA)
			{
				scanf("%s", &nazwisko);
				strcat(wpis_uzytkownika, " ");
				strcat(wpis_uzytkownika, nazwisko);
			}

			jaka_operacja = 1;

			while (getc(stdin) != '\n');

			jak_dlugi = strlen(wpis_uzytkownika);
			co_wpisal_uzytkownik = sprawdz_co_zostalo_wpisane(wpis_uzytkownika, jak_dlugi);
			usun_po_lub_przed(&glowa, wpis_uzytkownika, co_wpisal_uzytkownik, jaka_operacja);
			break;
		case 7:
			puts("Wpisz PESEL lub IMIE i NAZWISKO:");
			scanf("%s", &wpis_uzytkownika);

			jak_dlugi = strlen(wpis_uzytkownika);
			co_wpisal_uzytkownik = sprawdz_co_zostalo_wpisane(wpis_uzytkownika, jak_dlugi);

			if (co_wpisal_uzytkownik == OSOBA)
			{
				scanf("%s", &nazwisko);
				strcat(wpis_uzytkownika, " ");
				strcat(wpis_uzytkownika, nazwisko);
			}
			else
				nr_pesel = strtoull(wpis_uzytkownika, NULL, 0);

			while (getc(stdin) != '\n');

			umiesc_element_na_poczatku_kolejki(&glowa, &ogon, nr_pesel, &wpis_uzytkownika, co_wpisal_uzytkownik);
			break;
		case 8:
			puts("Podaj element (PESEL lub IMIE i NAZWISKO) Po ktorym ma byc dodany nowy element:");

			scanf("%s", &wpis_uzytkownika);
			jak_dlugi = strlen(wpis_uzytkownika);
			co_wpisal_uzytkownik = sprawdz_co_zostalo_wpisane(wpis_uzytkownika, jak_dlugi);

			if (co_wpisal_uzytkownik == OSOBA)
			{
				scanf("%s", &nazwisko);
				strcat(wpis_uzytkownika, " ");
				strcat(wpis_uzytkownika, nazwisko);
			}
			else
				nr_pesel = strtoull(wpis_uzytkownika, NULL, 0);

			while (getc(stdin) != '\n');

			if ((pomoc = szukaj_elementu(glowa, wpis_uzytkownika, co_wpisal_uzytkownik)) == NULL)
			{
				puts("Nie znaleziono elementu o takim kluczu!");
				break;
			}
			else
				printf("Znaleziono taki element! Wpisz nowy, ktory zostanie dodany PO elemencie %s :\n", wpis_uzytkownika);

			scanf("%s", &wpis_uzytkownika);

			jak_dlugi = strlen(wpis_uzytkownika);
			co_wpisal_uzytkownik = sprawdz_co_zostalo_wpisane(wpis_uzytkownika, jak_dlugi);

			if (co_wpisal_uzytkownik == OSOBA)
			{
				scanf("%s", &nazwisko);
				strcat(wpis_uzytkownika, " ");
				strcat(wpis_uzytkownika, nazwisko);
			}
			else
				nr_pesel = strtoull(wpis_uzytkownika, NULL, 0);

			jaka_operacja = 0;

			while (getc(stdin) != '\n');


			dodaj_po_lub_przed(pomoc, nr_pesel, &wpis_uzytkownika, co_wpisal_uzytkownik, jaka_operacja);
			break;
		case 9:
			puts("Podaj element (PESEL lub IMIE i NAZWISKO) PRZED ktorym ma byc dodany nowy element:");
			scanf("%s", &wpis_uzytkownika);
			jak_dlugi = strlen(wpis_uzytkownika);
			co_wpisal_uzytkownik = sprawdz_co_zostalo_wpisane(wpis_uzytkownika, jak_dlugi);

			if (co_wpisal_uzytkownik == OSOBA)
			{
				scanf("%s", &nazwisko);
				strcat(wpis_uzytkownika, " ");
				strcat(wpis_uzytkownika, nazwisko);
			}
			else
				nr_pesel = strtoull(wpis_uzytkownika, NULL, 0);

			if ((pomoc = szukaj_elementu(glowa, wpis_uzytkownika, co_wpisal_uzytkownik)) == NULL)
			{
				puts("Nie znaleziono elementu o takim kluczu!");
				break;
			}
			else
				printf("Znaleziono taki element! Wpisz nowy, ktory zostanie dodany PRZED elementem %s :\n", wpis_uzytkownika);

			scanf("%s", &wpis_uzytkownika);
			jak_dlugi = strlen(wpis_uzytkownika);
			co_wpisal_uzytkownik = sprawdz_co_zostalo_wpisane(wpis_uzytkownika, jak_dlugi);

			if (co_wpisal_uzytkownik == OSOBA)
			{
				scanf("%s", &nazwisko);
				strcat(wpis_uzytkownika, " ");
				strcat(wpis_uzytkownika, nazwisko);
			}
			else
				nr_pesel = strtoull(wpis_uzytkownika, NULL, 0);

			jaka_operacja = 1;

			while (getc(stdin) != '\n');

			dodaj_po_lub_przed(pomoc, nr_pesel, &wpis_uzytkownika, co_wpisal_uzytkownik, jaka_operacja);
			break;
		case 10:
			puts("Podaj rok dla ktorego ma byc wyszukany numer PESEL:");
			scanf("%s", &wpis_uzytkownika);
			jak_dlugi = strlen(wpis_uzytkownika);
			co_wpisal_uzytkownik = sprawdz_co_zostalo_wpisane(wpis_uzytkownika, jak_dlugi);

			if (co_wpisal_uzytkownik == OSOBA)
			{
				puts("To nie nr PESEL.");
				break;
			}

			while (getc(stdin) != '\n');

			nr_pesel = strtoull(wpis_uzytkownika, NULL, 0);
			nr_pesel = wyszukaj_peselu(nr_pesel, glowa, co_wpisal_uzytkownik);

			if (nr_pesel == NULL)
				puts("Nie znaleziono.");
			else
				printf("Wyszukano PESEL: %lld\n", nr_pesel);

			break;
		case EXIT:
			usun_kolejke(&glowa);
			puts("Program zakonczony.");
			exit(0);
			break;
		default:
			puts("Taka opcja nie istnieje!");
			break;
			memset(wpis_uzytkownika, '\0', sizeof(wpis_uzytkownika));
			memset(nazwisko, '\0', sizeof(nazwisko));
		}
	}

	return 0;
}