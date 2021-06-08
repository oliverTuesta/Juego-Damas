#include <iostream>
#include <conio.h>

using namespace std;
using namespace System;

const int LADO_TABLERO = 8;

const int ARRIBA = 72;
const int ABAJO = 80;
const int IZQUIERDA = 75;
const int DERECHA = 77;
const int ENTER = 13;

const int FLECHA_DERECHA = 16;
const int FLECHA_ARRIBA = 94;
const int FLECHA_IZQUIERDA = 60;

const int PRIMERA_OPCION_MENU = 0;
const int ULTIMA_OPCION_MENU = 2;

const int MARCO_IZQUIERDA_MENU = 45;
const int MARCO_IZQUIERDA_TABLERO = 10;
const int MARCO_ARRIBA_TABLERO = 3;


//declaracion de funciones
void menu();
void moverFlechitaMenu(int&);
void dibujarMapa();
void ubicarFicha(int&, int&);
void iniciarPartida();
void moverFlechitasTablero(int&, int&);


int main()
{

	menu();
	return 0;
}

void menu()
{	
	int opcion = 0;
	do {
		Console::Clear();
		Console::BackgroundColor = ConsoleColor::Black;
		Console::SetCursorPosition(10, 1);
		printf("\t******************************* DAMAS *******************************\n");
		Console::SetCursorPosition(MARCO_IZQUIERDA_MENU, 6);
		printf("Nueva partida");
		Console::SetCursorPosition(MARCO_IZQUIERDA_MENU, 8);
		printf("Creditos");
		Console::SetCursorPosition(MARCO_IZQUIERDA_MENU, 10);
		printf("Salir");
		
		moverFlechitaMenu(opcion);

		switch (opcion)
		{
		case 0:
		//iniciar juego
			iniciarPartida();
			break;
		case 1:
			//creditos
			break;
		}

	} while (opcion != ULTIMA_OPCION_MENU);
}

void moverFlechitaMenu(int& opcion)
{
	char tecla;
	do {
		int anterior = opcion;
		Console::SetCursorPosition(MARCO_IZQUIERDA_MENU - 1, 6 + opcion * 2);
		printf("%c", FLECHA_DERECHA);

		tecla = getch();

		switch (tecla)
		{
		case ARRIBA:
			if (opcion == PRIMERA_OPCION_MENU)
				opcion = ULTIMA_OPCION_MENU;
			else
				opcion--;
			break;
		case ABAJO:
			if (opcion == ULTIMA_OPCION_MENU)
				opcion = PRIMERA_OPCION_MENU;
			else
				opcion++;
			break;
		}

		Console::SetCursorPosition(MARCO_IZQUIERDA_MENU - 1, 6 + anterior * 2);
		printf(" ");

	} while (tecla != ENTER);
}

void iniciarPartida()
{
	int x, y;
	Console::Clear();
	dibujarMapa();
	ubicarFicha(x, y);
}

void dibujarMapa()
{

	int posicionY = MARCO_ARRIBA_TABLERO;
	for (int i = 0; i < LADO_TABLERO * 2; i += 2)
	{
		posicionY += 2;
		int z = i / 2 % 2 == 0 ? 0 : 1;
		for (int j = 0; j < LADO_TABLERO * 5; j += 5)
		{
			if (z % 2 == 0) {
				Console::BackgroundColor = ConsoleColor::Green;
			}
			else
				Console::BackgroundColor = ConsoleColor::Black;

			Console::SetCursorPosition(MARCO_IZQUIERDA_TABLERO + j, posicionY);
			printf("  o  ");
			Console::SetCursorPosition(MARCO_IZQUIERDA_TABLERO + j, posicionY+1);
			printf("     ");
			z++;
		}
		
	}
}

void ubicarFicha(int& x, int& y)
{
	Console::BackgroundColor = ConsoleColor::Black;
	moverFlechitasTablero(x, y);
	Console::SetCursorPosition(60, 6);
	printf("x=%d y=%d", x, y);
} 

void moverFlechitasTablero(int& x, int& y)
{
	y = x = 0;
	int posicionXHorizontal, posicionYHorizontal;
	posicionXHorizontal = MARCO_IZQUIERDA_TABLERO + 2;
	posicionYHorizontal = MARCO_ARRIBA_TABLERO + 8 * 2 + 2;

	int posicionX, posicionY;
	posicionX = MARCO_IZQUIERDA_TABLERO + 8 * 5 + 1;
	posicionY = MARCO_ARRIBA_TABLERO + 2;
	char tecla;

	
	do {
		int posicionAnteriorHorizontal = posicionXHorizontal + x * 5;
		Console::SetCursorPosition(posicionAnteriorHorizontal, posicionYHorizontal);
		printf("%c", FLECHA_ARRIBA);
		int posicionAnterior = posicionY + y * 2;
		Console::SetCursorPosition(posicionX, posicionAnterior);
		printf("%c", FLECHA_IZQUIERDA);
		tecla = getch();
		switch (tecla)
		{
		case DERECHA:
			if (x < 8 - 1) 
				x++;
			
			break;
		case IZQUIERDA:
			if (x > 0) 
				x--;
			break;
		case ABAJO:
			if (y < 8 - 1)
				y++;
			break;
		case ARRIBA:
			if (y > 0)
				y--;
			break;
		}
		Console::SetCursorPosition(posicionAnteriorHorizontal, posicionYHorizontal);
		printf(" ");
		Console::SetCursorPosition(posicionX, posicionAnterior);
		printf(" ");
	} while (tecla != ENTER);
}
