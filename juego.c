#include <stdio.h>
#include <stdlib.h>
#define V 21
#define H 65
#define N 100

typedef struct
{
	int x, y;
	int ModX,ModY;
	char imagen;
}snk;

typedef struct
{
	int x,y;
}frt;

snk snake[N];
frt fruta;

void inicio(int *tam, char campo[V][H]);
void Intro_Campo(char campo[V][H]);
void Intro_Datos(char campo[V][H], int tam);
void input(char campo[V][H], int *tam, int *muerto);
void update(char campo[V][H],int tam);
void Intro_Datos2(char campo[V][H], int tam);
void loop (char campo[V][H], int tam);


int main()
{
	int tam;
	char campo[V][H];
	system("color 79");
	inicio(&tam, campo); //Iniciar todos los elementos
	loop(campo, tam);
	
	return 0;
}

//Iniciar todos los elementos
void inicio (int *tam, char campo[V][H])
{
	int i;
	//Cabeza de la serpiente
	snake[0].x = 32;
	snake[0].y = 10;
	//Tamano
	*tam = 4;
	//Coordenadas de la fruta
	srand(time(NULL));// para generar la fruita aleatoria con el tiempo
	fruta.x = rand() % (H-1);// rand () para generar aleatoria
	fruta.y = rand() % (V-1);
	
	while(fruta.x == 0)
	{
		fruta.x = rand() % (H-1);
	}
	while(fruta.y == 0)
	{
		fruta.y = rand() % (V-1);
	}
	for(i = 0; i < *tam; i++)
	{
		snake[i].ModX = 1;
		snake[i].ModY = 0;
	}
	
	Intro_Campo(campo);
	Intro_Datos(campo, *tam);
}

//Creacion del campo de juego
void Intro_Campo(char campo[V][H])
{
	int i, j;
	for (i = 0; i < V; i++)
	{
		for (j = 0; j < H; j++)
		{
			if(i == 0 || i == V-1)
			{
				campo[i][j] = '=';
			}
			else if (j == 0 || j == H-1)
			{
				campo[i][j] = '||';
			}
			else
			{
				campo[i][j] = ' ';
			}
		}
	}
}

//Datos en matriz de campo
void Intro_Datos(char campo[V][H], int tam)
{
	int i;
	for (i = 1; i < tam; i++)
	{
		snake[i].x = snake[i-1].x - 1;
		snake[i].y = snake[i-1].y - 1;
		
		snake[i].imagen = '$';
	}
	snake[0].imagen = 'O';
	
	for(i = 0; i < tam; i++)
	{
		campo[snake[i].y][snake[i].x] - snake[i].imagen;
	}
	campo[fruta.y][fruta.x] - '&';
}

void draw(char campo[V][H])
{
	int i,j;
	for (i = 0; i < V; i++)
	{
		for (j = 0; j < H; j++)
		{
			printf("%c", campo[i][j]);
		}
		printf("\n");
	}
}

void loop (char campo[V][H], int tam)
{
	int muerto = 0;
	do
	{
		system("cls");// para limpiar
		draw(campo);
		input(campo,&tam,&muerto);
		update(campo,tam);
	}while(muerto == 0);
}

