/*
 ============================================================================
 Name        : multi.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void multi(char * zm1, char * zm2)
{
	int size1 = strlen(zm1);
	int size2 = strlen(zm2);
	int i = 0, j = 0;
	char wynik[size2][size1+2];
	for(i=0; i<size2; i++)
	{
		memset(wynik[i],'0',size1+2);
		wynik[i][size1+1] = '\0';
	}
	//memset(wynik[0],'0',6);
	//memset(wynik[1],'0',6);
	//wynik[0][5] = '\0';
	//wynik[1][5] = '\0';
	int zmwynik = 0;

	for (i = 0; i<size2; i++)
	{
		printf("%s",wynik[i]);
		//for(j = 0; j<size1; j++)
		//{
		//	printf("%c",wynik[j][i]);
		//}
		printf("\n");
	}

	for(i=size1-1; i>=0 ; i--)
	{
		int liczba1 = (int)zm1[i] - 48;
		printf("zm1 %d ", liczba1);
		for(j=size2-1; j>=0; j--)
		{
			int liczba2 = (int)zm2[j] - 48;
			printf("* zm2 %d ", liczba2);
			if (!liczba1 || !liczba2)
			{
				continue;
			}
			else if(liczba1 == 1)
			{
				zmwynik = liczba2;
			}
			else if(liczba2 == 1)
			{
				zmwynik = liczba1;
			}
			else
			{
				zmwynik = liczba1*liczba2;
			}

			if(wynik[j][i+1] != '0')
			{
				printf("bylo przesuniecie %c \n", wynik[j][i+1]);
				zmwynik += (int)(wynik[j][i+1])-48;
			}

			if(zmwynik>9)
			{
				int jednosci = zmwynik%10;
				int dalej = (zmwynik - jednosci)/10;
				printf("dalej = %d", dalej);
				wynik[j][i+1] = (char)jednosci+48;
				wynik[j][i] = (char)dalej+48;
			}
			else
			{
				wynik[j][i+1] = (char)zmwynik+48;
			}

			printf("zapis do kom %d %d = %c ", j, i+1, wynik[j][i+1]);
		}
		printf("\n");

	}
	for (i = 0; i<size2; i++)
	{
		printf("%s",wynik[i]);
		//for(j = 0; j<size1; j++)
		//{
		//	printf("%c",wynik[j][i]);
		//}
		printf("\n");
	}

	char suma[size1+size2+1];
	memset(suma,'0',size1+size2+1);
	suma[size1+size2] = '\0';

	int k = size1+size2;

	for(i = size2-1; i>= 0; i--)
	{
		for(j = size1+1; j>= 0; j--)
		{
			suma[k] = 0;
			k--;
		}
	}
}

void multi2(char * zm1, char * zm2)
{
	int size1 = strlen(zm1);
	int size2 = strlen(zm2);

	int i = 0, j = 0, zmwynik = 0, k = 0, p = 1;

	//2 wymiarowa tablica wynikow
	char wynik[size2][size1+2];
	for(i=0; i<size2; i++)
	{
		memset(wynik[i],'0',size1+2);
		wynik[i][size1+1] = '\0';
	}

	// tablica wynikowa
	char suma[size1+size2+1];
	memset(suma,'0',size1+size2+1);
	suma[size1+size2] = '\0';
	//int k = size1+size2-1;

	for(i=size1-1; i>=0 ; i--,p++)
	{
		k = size1+size2-p;
		int liczba1 = (int)zm1[i] - 48;
		printf("p = %d :\n", p);

		for(j=size2-1; j>=0; j--)
		{
			int liczba2 = (int)zm2[j] - 48;
			printf("zm1 %d * zm2 %d ", liczba1, liczba2);

			if (!liczba1 || !liczba2)
			{
				k--;
				continue;
			}
			else if(liczba1 == 1)
			{
				zmwynik = liczba2;
			}
			else if(liczba2 == 1)
			{
				zmwynik = liczba1;
			}
			else
			{
				zmwynik = liczba1*liczba2;
			}

			//if(wynik[j][i+1] != '0')
			//{
			//	printf("bylo przesuniecie %c \n", wynik[j][i+1]);
			//	zmwynik += (int)(wynik[j][i+1])-48;
			//}

			if(suma[k] != '0')
			{
				printf(" uwaga bylo przesuniecie o %c \n",suma[k]);
				zmwynik += (int)(suma[k])-48;
			}

			if(zmwynik>9)
			{
				int jednosci = zmwynik%10;
				int dalej = (zmwynik - jednosci)/10;
				printf("zapis  dalej = %d do kom %d\n", dalej, k-1);
				//wynik[j][i+1] = (char)jednosci+48;
				//wynik[j][i] = (char)dalej+48;
				suma[k] = (char)jednosci+48;
				if(suma[k-1] != '0')
				{
					dalej += (int)(suma[k-1])-48;
					suma[k-1] = (char)dalej+48;
				}
				else
				{
					suma[k-1] = (char)dalej+48;
				}
			}
			else
			{
				//wynik[j][i+1] = (char)zmwynik+48;
				suma[k] = (char)zmwynik+48;
			}

			printf(" nastepuje zapis do kom %d = %c \n\n", k, suma[k]);
			k--;
		}
		printf("\n");


	}

	//wypisanie wynikow
	for (i = 0; i<size2; i++)
	{
		printf("%s\n",wynik[i]);
	}
	printf("suma = %s\n",suma);

}

int main(void) {
	puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */

	//char a[] = {'1', '2', '2' , '2', '\0'};
	//char b[] = {'1', '2','2','\0'};
	char a[] = {'9', '9','9','9','\0'};
	char b[] = {'9','9','9','9','\0'};

	//multi(a,b);
	multi2(a,b);
	return EXIT_SUCCESS;
}
