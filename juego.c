#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define V 21 
             	//Tamano del campo de juego
#define H 65
#define N 100 	//Tamano de la serpiente

typedef struct
{
	int x, y;
	int ModX,ModY;
	char imagen;
}snk; 			//Movimiento de la serpiente

typedef struct
{
	int x,y;
}frt; 			//Coordenadas de la fruta

typedef struct
{
	char nombre[N] ;
	int nota;
}jug;

jug jugador[N];
snk snake[N];
frt fruta;

void inicio(int *tam, char campo[V][H]); 				//Inicia todos los elementos
void Intro_Campo(char campo[V][H]); 					//Dibuja el campo de juego
void Intro_Datos(char campo[V][H], int tam); 			//Introduce los datos en la matriz del campo (serpiente y fruta)
void input(char campo[V][H], int *tam, int *muerto); 	//Programa
void update(char campo[V][H],int tam); 					//Borra los datos de la matriz campo y los reescribe
void Intro_Datos2(char campo[V][H], int tam); 			//Movimiento de la serpiente
void loop (char campo[V][H], int tam); 					//Ejecuta draw, input y update
char menu(void);

void main()
{
	jug jugador[N];
	int tam;
	char campo[V][H];
	char opcion;
	int puntos;
	char h;
	FILE *F;
	int i=0,iMax=0;
	do
	{
		system("color 09");
		printf ("Seleccione una de estas opciones:\n");	
		printf ("N - Nueva partida\n");
		printf ("C - Consultar puntuacion\n");
		printf ("S - Salir del programa\n");
		printf("M - Maxima punto que ha obtenido");
		printf ("\n");
		printf ("Durante la partida, pulse P para pausar el juego\n");
		fflush(stdin);
		scanf ("%c", &opcion);
		fflush(stdin);
		switch (opcion)
		{
			case 'N':
			case 'n':
			{	
				inicio(&tam, campo); 
				loop(campo, tam);		
			}break;
			case 'C':
			case 'c':
			{
				
				F=fopen("puntuacio.txt","r");
				while(fscanf(F, "%c", &h) != EOF)
				printf("%c",h);
				printf("\n");
				fclose(F);
				
			}break;
			case 'M':
			case 'm':
			{
			F=fopen("puntuacio.txt","r");
			while(fscanf(F, "%s\t%d", &jugador[i].nombre,&jugador[i].nota) != EOF)
			{
				if (jugador[i].nota > jugador[iMax].nota)
     		 	iMax = i;	
     		 	i++;
			}fclose(F);
			printf(" la maxima puntuacion de este juego es %d de %s\n",jugador[iMax].nota,jugador[iMax].nombre);
			}break;	
			
	}	}	while (opcion != 's' && opcion != 'S');

}
	
//Inicia todos los elementos
void inicio (int *tam, char campo[V][H])
{
	int i;
	//Cabeza de la serpiente
	snake[0].x = 32;
	snake[0].y = 10;
	//Tama耧
	*tam = 4;
	//Coordenadas aleatorias de la fruta
	srand(time(NULL));
	fruta.x = rand() % (H-1);
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
				campo[i][j] = '|';
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
		system("cls");
		draw(campo);
		input(campo,&tam,&muerto);
		update(campo,tam);
	}while(muerto == 0);
	
}

void input(char campo[V][H], int *tam, int *muerto)
{
	int i, punt;
	char key;
	char nombre[10];
	FILE *f;
	//Comprobaci箢 de si hemos muerto
	if(snake[0].x == 0 || snake[0].x == H-1 || snake[0].y == 0 || snake[0].y == V-1)
	{
		*muerto = 1;
		system("color 0A");
		printf("GAME OVER\n");
	}
	for(i = 1; i < *tam && *muerto == 0; i++)
	{
		if(snake[0].x == snake[i].x && snake[0].y == snake[i].y)
		{
			*muerto = 1;
			system("color 0A");
			printf("GAME OVER\n");
		}
	}
	//Comprobar si nos hemos comido la fruta
	if(snake[0].x == fruta.x && snake[0].y == fruta.y)
	{
		*tam +=1;
		snake[*tam-1].imagen = '$';
		fruta.x = rand()%(H-1);
		fruta.y = rand()%(V-1);
		while(fruta.x == 0)
		{
			fruta.x = rand()%(H-1);
		}
		while(fruta.y == 0)
		{
			fruta.y = rand()%(V-1);
		}
	}
	
	if(*muerto == 1)
	{
		printf("Nombre:\t");
		scanf ("%s", nombre);
		punt=(*tam-4);
		printf ("%s has ganado %i puntos\n", nombre, punt);
		f=fopen("puntuacio.txt","a");
		fprintf(f, "%s\t %d\n", nombre, punt);
		
		fclose(f);
		
	}
	
	if(*muerto == 0)
	{
		if(kbhit() == 1)
		{
			key = getch();
			if((key == '2' || key == 's') && snake[0].ModY != -1)
			{
				snake[0].ModX = 0;
				snake[0].ModY = 1;
			}
			if((key == '8' || key == 'w') && snake[0].ModY != 1)
			{
				snake[0].ModX = 0;
				snake[0].ModY = -1;
			}
			if((key == '4'|| key == 'a' ) && snake[0].ModX != 1)
			{
				snake[0].ModX = -1;
				snake[0].ModY = 0;
			}
			if((key == '6' || key == 'd') && snake[0].ModX != -1)
			{
				snake[0].ModX = 1;
				snake[0].ModY = 0;
			}
			if(key == 'p') 
			{
				system("color 0A");
				printf("Pause\n");
				system("pause");
			}
			
		}
	}
}

void update(char campo[V][H],int tam)
{
	//Borrar los datos de la matriz
	Intro_Campo(campo);
	//Introducir nuevos datos
	Intro_Datos2(campo,tam);
}

void Intro_Datos2(char campo[V][H], int tam)
{
	//Hacer que el cuerpo siga a la cabeza. Cada elemento copia al anterior menos la cabeza
	int i;
	for(i = tam-1 ; i > 0 ; i--)
	{
		snake[i].x = snake[i-1].x;
		snake[i].y = snake[i-1].y;
	}
	snake[0].x += snake[0].ModX;
	snake[0].y += snake[0].ModY;
	
	for(i = 0 ; i < tam ; i++)
	{
		campo[snake[i].y][snake[i].x] = snake[i].imagen;
	}
	
	campo[fruta.y][fruta.x] = '&';
}



