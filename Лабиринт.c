#include <stdio.h>
#include <locale.h>
#include <windows.h>
int terr[21][21], terr1[21][21], path[100];  // pole 21x21
int i, j, a, b, random, n, v, l, p, schet, stop, backwood=0;
char stena = 219, tochka = 35, text, sled = 176;
// i j - massiv, a b - zapolnenie massiva, random - pomogaet vibrat mesto stenok, flag - proverka funkcii dviweniya, schet - s4et4ik wagov.
// n - niz, v - verx, l - levo, p - pravo
// 0 - clear, 1 - stena, 2 - proidenii pyt, 3 - bot tam ne okawetsya
//p n v l		0 - clear		1 - stena		2 - sled

void spirit() {
	for (a = 0; a < 21; a++)  //vivod labirinta
	{
		for (b = 0; b < 21; b++)
		{
			if (terr[a][b] == 0) printf("  ");
			if (terr[a][b] == 1) printf("%c%c", stena, stena);
			if (terr[a][b] == 2) printf("%c%c", sled, sled);
			if (terr[a][b] == 3) printf("%c%c", tochka, tochka);
		}
		printf("\n");
	}
}

void cena()		//zadaet cennost' kawdoi kletke
{
	if (terr[i + 1][j] == 2) { n = 2; }
	else if (terr[i + 1][j] == 1) { n = 1; }
	else if (terr[i + 1][j] == 0) { n = 0; }

	if (terr[i][j + 1] == 2) { p = 2; }
	else if (terr[i][j + 1] == 1) { p = 1; }
	else if (terr[i][j + 1] == 0) { p = 0; }

	if (terr[i][j - 1] == 2) { l = 2; }
	else if (terr[i][j - 1] == 1) { l = 1; }
	else if (terr[i][j - 1] == 0) { l = 0; }

	if (terr[i - 1][j] == 2) { v = 2; }
	else if (terr[i - 1][j] == 1) { v = 1; }
	else if (terr[i - 1][j] == 0) { v = 0; }

	if (schet == 200) stop = 1;
}

void vpravo()		//sdvig vpravo 
{
	if (terr[i][j + 1] != 1)
	{
		j = j + 2;
		terr[i][j] = 2;
		terr[i][j - 1] = 2;
		schet = schet + 1;
		path[backwood - 1]=1;
		cena();
		system("cls");
		spirit();
	}
}

void vniz()		//sdvig vniz
{
	if (terr[i + 1][j] != 1)
	{
		i = i + 2;
		terr[i][j] = 2;
		terr[i - 1][j] = 2;
		schet = schet + 1;
		path[backwood - 1] = 2;
		cena();
		system("cls");
		spirit();
	}
}

void vverx()		//sdvig vverx
{
	if (terr[i - 1][j] != 1)
	{
		i = i - 2;
		terr[i][j] = 2;
		terr[i + 1][j] = 2;
		schet = schet + 1;
		path[backwood - 1] = 3;
		cena();
		system("cls");
		spirit();
	}
}

void vlevo()		//sdvig vlevo 
{
	if (terr[i][j - 1] != 1)
	{
		j = j - 2;
		terr[i][j] = 2;
		terr[i][j + 1] = 2;
		schet = schet + 1;
		path[backwood - 1] = 4;
		cena();
		system("cls");
		spirit();
	}
}

void back() 
{
	while ((p != 0) && (n != 0) && (v != 0) && (l != 0) && (backwood >= 0))
	{
		if (path[backwood - 1] == 1) vlevo();
		else if (path[backwood - 1] == 2) vverx();
		else if (path[backwood - 1] == 3) vniz();
		else if (path[backwood - 1] == 4)vpravo();
		backwood--;
	}
}

void check()
{
	if (p == 0) { vpravo(); backwood++; }
	else if (n == 0) { vniz();backwood++; }
	else if (v == 0) { vverx(); backwood++; }
	else if (l == 0) { vlevo(); backwood++;	}
	else back();
	Sleep(50);
}

void dvijenie()
{
	while (((i != 19) || (j != 19))&&(stop!=1)) { check(); }
	if (stop == 1)
	{
		printf("Y robota seli batareiki! Otkroite emy proxod\n");
		printf("\nWagov soverwenno:");
		printf("%d", schet);
		printf("\n");
	}
	else
	{
		printf("Robot spravilsya s postavlennoi zada4ei!");
		printf("\nWagov soverwenno:");
		printf("%d", schet);
		printf("\n");
	}
}

int main() {
	system("cls");
	srand(time(0));
	for (i = 0; i < 21; i++) // zapolnil massiv nulyami
	{
		for (j = 0; j < 21; j++)
		{
			terr[i][j] = 0;
		}
	}

	for (j = 0; j < 21; j++) // to4ki
	{
		for (i = 0; i < 21; i++)
		{
			if ((j % 2 == 0) && (i % 2 == 0))
			{
				terr[i][j] = 3;
			}
			if (((i % 2 == 0) && (j % 2 != 0)) || ((i % 2 != 0) && (j % 2 == 0)))
			{
				random = rand() % 4;
				if (random == 1) terr[i][j] = 1;
			}
		}
	}

	for (i = 0; i < 21; i++) // crai labirinta
	{
		terr[20][i] = 1;
		terr[0][i] = 1;
		terr[i][0] = 1;
		terr[i][20] = 1;
	}

	i = 1; j = 1; // na4alo pyti
	terr[i][j] = 2;

	if (stop !=1)
	{
		spirit();
		cena();
		dvijenie();
	}
	return 0;
}