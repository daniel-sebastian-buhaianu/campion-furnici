#include <stdio.h>
#include <stdlib.h>

#define MIN_D 1
#define MAX_D 1000000
#define MIN_U 1
#define MAX_U 100000
#define MIN_L 1
#define MAX_L 100000
#define MIN_R 1
#define MAX_R 100000
#define MIN_T 0
#define MAX_T 2000000

int main()
{
	FILE *fin = fopen("furnici.in", "r");

	if (!fin)
	{
		printf("Eroare fisier furnici.in\n");
		return 1;
	}

	unsigned D, U;
	
	// citesc lungime tunel si numar locuri speciale
	fscanf(fin, "%u %u", &D, &U);

	if (D < MIN_D || D > MAX_D)
	{
		printf("Eroare valoare D\n");
		return 2;
	}

	if (U < MIN_U || U > MAX_U)
	{
		printf("Eroare valoare U\n");
		return 3;
	}

	unsigned i, *loc;

	loc = (unsigned*)malloc((U+2)*sizeof(unsigned));

	// citesc locurile speciale
	for (i = 1; i <= U; i++)
	{
		fscanf(fin, "%u", &loc[i]);
	}

	loc[0] = 0, loc[U+1] = D;

	unsigned L;

	// citesc cate furnici intra prin stanga
	fscanf(fin, "%u", &L);

	if (L < MIN_L || L > MAX_L)
	{
		printf("Eroare valoare L\n");
		return 4;
	}

	unsigned timp, maxL, maxR;

	// citesc timpul (in secunde) cand intra in tunel fiecare furnica din stanga
	for (maxL = maxR = 0, i = 1; i <= L; i++)
	{
		fscanf(fin, "%u", &timp);

		if (timp < MIN_T || timp > MAX_T)
		{
			printf("Eroare valoare timp\n");
			return 5;
		}

		// retin timpul cand intra ultima furnica prin stanga
		if (timp > maxL)
		{
			maxL = timp;
		}
	}

	unsigned R;

	// citesc cate furnici intra prin dreapta
	fscanf(fin, "%u", &R);

	if (R < MIN_R || R > MAX_R)
	{
		printf("Eroare valoare R\n");
		return 6;
	}
	
	// citesc timpul (in secunde) cand intra in tunel fiecare furnica din dreapta
	for (i = 1; i <= R; i++)
	{
		fscanf(fin, "%u", &timp);
		
		if (timp < MIN_T || timp > MAX_T)
		{
			printf("Eroare valoare timp\n");
			return 5;
		}

		// retin timpul cand intra ultima furnica prin dreapta
		if (timp > maxR)
		{
			maxR = timp;
		}
	}

	fclose(fin);

	unsigned st, dr, poz, rez;

	// nu ma intereseaza decat ultimele furnici care intra in tunel prin stanga si prin dreapta,
	// deci pentru aceste doua furnici se face calculul timpului
	for (i = 0; i <= U+1; i++)
	{
		// pentru fiecare dintre locurile speciale 
		// determin timpul maxim cand ajunge ultima furnica din dreapta in acest loc
		st = maxL + loc[i];

		// si timpul maxim cand ajunge ultima furnica din dreapta in acest loc
		dr = maxR + D - loc[i];

		// in acest loc se ajunge dupa poz secunde,
		// poz fiind maximul dintre furnica stanga si furnica dreapta
		poz = st > dr ? st : dr;

		// adaug eventualul timp de asteptare pana ajunge cealalta furnica
		if (loc[i] > D-loc[i])
		{
			poz += loc[i];
		}
		else
		{
			poz += D-loc[i];
		}

		// retin minimul pana in acest moment
		if (poz < rez)
		{
			rez = poz;
		}
	}

	free(loc);
	
	FILE *fout = fopen("furnici.out", "w");

	fprintf(fout, "%u", rez);

	fclose(fout);

	return 0;
}

// scor 100 (sol. oficiala)
