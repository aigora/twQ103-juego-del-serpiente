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

void inicio(int *tam, char campo[V][H]); //Iniciar todos los elementos
void Intro_Campo(char campo[V][H]);  //Creacion del campo de juego
void Intro_Datos(char campo[V][H], int tam); //Datos en matriz de campo
void input(char campo[V][H], int *tam, int *muerto);  	//Comprobacion de si hemos muerto
void update(char campo[V][H],int tam);  	//Borrar los datos de la matriz
void Intro_Datos2(char campo[V][H], int tam);	//Hacer que el cuerpo siga a la cabeza. Cada elemento copia al anterior menos la cabeza
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
