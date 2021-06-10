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
const int CARACTER_FICHA = 'o';

const int PRIMERA_OPCION_MENU = 0;
const int ULTIMA_OPCION_MENU = 2;

const int MARCO_IZQUIERDA_MENU = 45;
const int MARCO_IZQUIERDA_TABLERO = 10;
const int MARCO_ARRIBA_TABLERO = 3;

const ConsoleColor COLOR_FICHA_B = ConsoleColor::Red;
const ConsoleColor COLOR_FICHA_A = ConsoleColor::White;

//declaracion de funciones
void menu();
void moverFlechitaMenu(int&);
void dibujarMapa();
void ubicarCoordenada(int&, int&);
void iniciarPartida();
void moverFlechitasTablero(int&, int&);
void inisializarFichas();
void moverFicha(int, int, int, int);
void dibujarFichas();
void borrarTexto();
bool puedeMover(int, int, int, int);
bool estaEnDiagonal(int, int, int, int);
void mensajesDeError(int);

struct ficha {
	bool existe = false;
	char tipo;
};

ficha** fichas;

void inisializarFichas() {
	fichas = new ficha* [LADO_TABLERO];

	for (int i = 0; i < LADO_TABLERO; i++)
	{
		fichas[i] = new ficha[LADO_TABLERO];
	}
	
	for (int i = 0; i < 3; i++)
	{
		for (int j = i%2==0? 1 : 0; j < 8; j+=2)
		{
			fichas[i][j].existe = true;
			fichas[i][j].tipo = 'A';
		}
	}
	for (int i = LADO_TABLERO - 3; i < LADO_TABLERO; i++)
	{
		for (int j = i % 2 == 0 ? 1 : 0; j < 8; j += 2)
		{
			fichas[i][j].existe = true;
			fichas[i][j].tipo = 'B';
		}
	}
}

void moverFicha(int x, int y, int xNuevo, int yNuevo)
{
	if (puedeMover(x, y, xNuevo, yNuevo))
	{
		Console::SetCursorPosition(MARCO_IZQUIERDA_TABLERO + x * 5 + 2,
			MARCO_ARRIBA_TABLERO + (y + 1) * 2);
		Console::BackgroundColor = ConsoleColor::Black;
		printf(" ");
		fichas[yNuevo][xNuevo] = fichas[y][x];
		fichas[y][x].existe = false;
	}
	else
		mensajesDeError(2);
}

void dibujarFichas()
{
	for (int i = 0; i < LADO_TABLERO; i++)
	{
		for (int j = 0; j < LADO_TABLERO; j++)
		{
			ficha f = fichas[i][j];
			if (f.existe)
			{
				Console::SetCursorPosition(MARCO_IZQUIERDA_TABLERO + j * 5 + 2,
					MARCO_ARRIBA_TABLERO + (i+1)*2);
				Console::BackgroundColor = ConsoleColor::Black;
				switch (f.tipo)
				{
				case 'A':
					Console::ForegroundColor = COLOR_FICHA_A;
					break;
				case 'B':
					Console::ForegroundColor = COLOR_FICHA_B;
					break;
				}
				
				printf("%c", CARACTER_FICHA);
			}
			
		}
		
	}
	
}

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
	int xNuevo, yNuevo;
	Console::Clear();
	dibujarMapa();
	inisializarFichas();
	
	do {
		dibujarFichas();
		ubicarCoordenada(x, y);
		if (!fichas[y][x].existe)
		{
			mensajesDeError(1);
			continue;
		}
		else
			borrarTexto();
		ubicarCoordenada(xNuevo, yNuevo);
		moverFicha(x, y, xNuevo, yNuevo);
	} while (x != 0 || y != 0);
	_getch();
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
			printf("     ");
			Console::SetCursorPosition(MARCO_IZQUIERDA_TABLERO + j, posicionY+1);
			printf("     ");
			z++;
		}
		
	}
}

void ubicarCoordenada(int& x, int& y)
{
	Console::ForegroundColor = COLOR_FICHA_B;
	Console::BackgroundColor = ConsoleColor::Black;
	moverFlechitasTablero(x, y);
} 

void moverFlechitasTablero(int& x, int& y)
{
	y = x = 0;
	int posicionXHorizontal, posicionYHorizontal;
	posicionXHorizontal = MARCO_IZQUIERDA_TABLERO + 2;
	posicionYHorizontal = MARCO_ARRIBA_TABLERO + 8 * 2 + 2;

	int posicionXVertical, posicionYVertical;
	posicionXVertical = MARCO_IZQUIERDA_TABLERO + 8 * 5 + 1;
	posicionYVertical = MARCO_ARRIBA_TABLERO + 2;
	char tecla;

	Console::ForegroundColor = COLOR_FICHA_A;
	
	do {
		int posicionAnteriorHorizontal = posicionXHorizontal + x * 5;
		Console::SetCursorPosition(posicionAnteriorHorizontal, posicionYHorizontal);
		printf("%c", FLECHA_ARRIBA);
		int posicionAnteriorVertical = posicionYVertical + y * 2;
		Console::SetCursorPosition(posicionXVertical, posicionAnteriorVertical);
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
		//borrar anteriores flechitas
		Console::SetCursorPosition(posicionAnteriorHorizontal, posicionYHorizontal);
		printf(" ");
		Console::SetCursorPosition(posicionXVertical, posicionAnteriorVertical);
		printf(" ");
	} while (tecla != ENTER);
}
void borrarTexto()
{
	for (int i = 0; i < 6; i++)
	{
		Console::SetCursorPosition(60, 6 + i);
		printf("                                         ");
	}
	
}

bool puedeMover(int x, int y, int xNuevo, int yNuevo)
{
	bool estaEnNegro = false;
	bool direccionCorrecta = false;
	bool come = false;
	switch (fichas[y][x].tipo)
	{
	case 'A':
		for (int i = 0; i < 7; i++)
		{
			if (fichas[yNuevo][xNuevo].existe) {
				yNuevo--;
				come = true;
			}
		}
		direccionCorrecta = yNuevo - y == 1;
		break;
	case 'B':
		if (fichas[yNuevo][xNuevo].existe) {
			yNuevo++;
			come = true;
		}
		direccionCorrecta = y - yNuevo == 1;
		break;
	}
	
	if (yNuevo % 2 == 0)
		estaEnNegro = xNuevo % 2 != 0;
	else
		estaEnNegro = xNuevo % 2 == 0;

	if (fichas[yNuevo][xNuevo].existe || !estaEnNegro)
	{
		//No se puede mover a esa posicion
		mensajesDeError(2);
		return false;
	}
	if (come)
		mensajesDeError(3);

	return true && estaEnDiagonal(x, y, xNuevo, yNuevo) && direccionCorrecta;
}

bool estaEnDiagonal(int x, int y, int xNuevo, int yNuevo)
{
	bool esDiag = abs(x - xNuevo) == abs(y - yNuevo);
	return esDiag;
}
void mensajesDeError(int tipo)
{
	borrarTexto();
	Console::ForegroundColor = COLOR_FICHA_A;
	
	switch (tipo)
	{
	case 1:
		Console::SetCursorPosition(60,7);
		printf("NO EXISTE NINGUNA FICHA EN ESA POSICION");
		Console::SetCursorPosition(60,8);
		printf("INTENTE OTRA VEZ");
		break;
	case 2:
		Console::SetCursorPosition(60, 7);
		printf("NO PUEDE MOVER A ESA POSICION");
		Console::SetCursorPosition(60, 8);
		printf("INTENTE OTRA VEZ");
		break;
	case 3:
		Console::SetCursorPosition(60, 10);
		printf("Come");
		Console::SetCursorPosition(60, 8);
		printf("INTENTE OTRA VEZ");
		break;
	default:
		break;
	}
	
}

