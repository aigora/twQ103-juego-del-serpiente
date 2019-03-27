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

