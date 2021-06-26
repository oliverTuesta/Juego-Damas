﻿#include <iostream>
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
const int CARACTER_FICHA = 'O';
const int CARACTER_FICHA_DAMA = '@';

const int PRIMERA_OPCION_MENU = 0;
const int ULTIMA_OPCION_MENU = 3;

const int MARCO_IZQUIERDA_MENU = 45;
const int MARCO_IZQUIERDA_TABLERO = 10;
const int MARCO_ARRIBA_TABLERO = 5;
const int MARCO_ARRIBA_MENU = 14;
const int MARCO_IZQUIERDA_MENSAJE = 60;

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
bool moverFicha(int, int, int, int);
void dibujarFichas();
void borrarTexto();
bool puedeMover(int, int, int, int, bool &);
bool estaEnDiagonal(int, int, int, int);
void mensajes(int);
void comerFichas(int, int, int, int, int&, int&);
bool estaEnNegro(int, int);
void cambiarTurno(char&);
void mostrarTurno(char, string, string);
void pedirDatos(string&, string&);
bool quedanMovimientos();
void dibujarFichasComidas(int, int);
void graficos();
void mostrarMovimientos(int, int);
void mostrarGanador(int, int, string, string);

struct ficha {
	bool existe = false;
	char tipo;
	bool dama = false;
};

ficha** fichas;


int main()
{
	setlocale(LC_ALL, "spanish");
	Console::SetWindowSize(110, 30);
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
		Console::ForegroundColor = ConsoleColor::Cyan;
		printf("\t\t\t  ______   _______  _______  _______  _______ \n\t\t\t\t (  __  ) (  ___  )(       )(  ___  )(  ____ )\n\t\t\t\t | (  )  )| (   ) || () () || (   ) || (    )/\n\t\t\t\t | |   ) || (___) || || || || (___) || (_____ \n\t\t\t\t | |   | ||  ___  || |(_)| ||  ___  |(_____  )\n\t\t\t\t | |   ) || (   ) || |   | || (   ) |      ) |\n\t\t\t\t | (__/  )| )   ( || )   ( || )   ( |/)____) |\n\t\t\t\t (______/ |/     (||/     (||/     (|(_______)\n");

		moverFlechitaMenu(opcion);

		switch (opcion)
		{
		case 0:
			//iniciar juego hola safdafasdfa
			iniciarPartida();
			break;
		case 1:
			//instrucciones
			mensajes(4);
			break;
		case 2:
			//creditos
			mensajes(3);
			break;
		}

	} while (opcion != ULTIMA_OPCION_MENU);
}


void graficos() {
	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 25; j++) {
			Console::BackgroundColor = ConsoleColor::DarkGray;

			cout << " ";

		}
		cout << endl;
	}
	for (int i = 0; i < 25; i++) {
		for (int j = 0; j < 30; j++) {
			Console::BackgroundColor = ConsoleColor::DarkGray;
			Console::SetCursorPosition(85 + i, 0 + j);
			cout << " ";
		}
		cout << endl;
	}
	Console::BackgroundColor = ConsoleColor::Black;
}
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

bool moverFicha(int x, int y, int xNuevo, int yNuevo, int &comidasA, int &comidasB)
{
	bool come = false;
	if (puedeMover(x, y, xNuevo, yNuevo, come))
	{
		if (come)
		{
			comerFichas(x, y, xNuevo, yNuevo, comidasA, comidasB);
		}

		fichas[yNuevo][xNuevo] = fichas[y][x];
		fichas[y][x].existe = false;
		if (yNuevo == 0 || yNuevo == LADO_TABLERO - 1)
		{
			fichas[yNuevo][xNuevo].dama = true;
		}
		return true;
	}
	else
		return false;
}

void dibujarFichas()
{
	for (int i = 0; i < LADO_TABLERO; i++)
	{
		for (int j = 0; j < LADO_TABLERO; j++)
		{
			ficha f = fichas[i][j];
			Console::SetCursorPosition(MARCO_IZQUIERDA_TABLERO + j * 5 + 2,
				MARCO_ARRIBA_TABLERO + i * 2);
			Console::BackgroundColor = ConsoleColor::Black;
			if (f.existe)
			{
				switch (f.tipo)
				{
				case 'A':
					Console::ForegroundColor = COLOR_FICHA_A;
					break;
				case 'B':
					Console::ForegroundColor = COLOR_FICHA_B;
					break;
				}

				if (f.dama)
					printf("%c", CARACTER_FICHA_DAMA);
				
				else
					printf("%c", CARACTER_FICHA);
			}
			else if(estaEnNegro(j, i))
				printf(" ");
			
		}
		
	}
	
}

void moverFlechitaMenu(int& opcion)
{
	char tecla;
	do {
		int anterior = opcion;
		Console::SetCursorPosition(MARCO_IZQUIERDA_MENU - 1, MARCO_ARRIBA_MENU + opcion * 2);
		printf("%c", FLECHA_DERECHA);

		Console::SetCursorPosition(MARCO_IZQUIERDA_MENU, MARCO_ARRIBA_MENU);
		if (opcion == 0)
		{
			Console::ForegroundColor = ConsoleColor::White;
		}
		else
		{
			Console::ForegroundColor = ConsoleColor::Magenta;
		}
		printf("\tNueva partida");
		Console::SetCursorPosition(MARCO_IZQUIERDA_MENU, MARCO_ARRIBA_MENU + 2);
		if (opcion == 1)
		{
			Console::ForegroundColor = ConsoleColor::White;
		}
		else
		{
			Console::ForegroundColor = ConsoleColor::DarkGray;
		}
		printf("\tInstrucciones");
		Console::SetCursorPosition(MARCO_IZQUIERDA_MENU, MARCO_ARRIBA_MENU + 4);
		if (opcion == 2)
		{
			Console::ForegroundColor = ConsoleColor::White;
		}
		else
		{
			Console::ForegroundColor = ConsoleColor::DarkGray;
		}
		printf("\tCreditos\n");
		Console::SetCursorPosition(MARCO_IZQUIERDA_MENU, MARCO_ARRIBA_MENU + 6);
		if (opcion == 3)
		{
			Console::ForegroundColor = ConsoleColor::White;
		}
		else
		{
			Console::ForegroundColor = ConsoleColor::Red;
		}
		printf("\tSalir\n");

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

		Console::SetCursorPosition(MARCO_IZQUIERDA_MENU - 1, MARCO_ARRIBA_MENU + anterior * 2);
		printf(" ");

	} while (tecla != ENTER);
}

void iniciarPartida()
{

	char turnoJugador = 'A';
	int movimientosA = 0;
	int movimientosB = 0;
	int puntosA = 0; //piezas B comidas
	int puntosB = 0; //piezas A comidas

	int x, y;
	x = y = 0;
	int xNuevo = 0, yNuevo = 0;
	Console::Clear();
	dibujarMapa();
	string jugadorA;
	string jugadorB;
	pedirDatos(jugadorA, jugadorB);
	inisializarFichas();

	bool gameOver = false;

	do {
		mostrarTurno(turnoJugador, jugadorA, jugadorB);
		dibujarFichas();
		ubicarCoordenada(x, y);
		if (fichas[y][x].existe && fichas[y][x].tipo == turnoJugador)
		{
			xNuevo = x;
			yNuevo = y;
			borrarTexto();
			ubicarCoordenada(xNuevo, yNuevo);
			if(!moverFicha(x, y, xNuevo, yNuevo, puntosA, puntosB))
			{
				mensajes(2);
				int t = getch();
				if (t == 101 || t == 69) {
					mensajes(5);
					return;
				}
				else
					borrarTexto();
			}
			
			else {
				cambiarTurno(turnoJugador);
				if (puntosA == 12 || puntosB == 12 || !quedanMovimientos())
				{
					gameOver = true;
				}
				if (fichas[yNuevo][xNuevo].tipo == 'A')
					movimientosA++;
				else
					movimientosB++;

				dibujarFichasComidas(puntosA, puntosB);
				mostrarMovimientos(movimientosA, movimientosB);
			}
		}
		else
			mensajes(1);
		x = xNuevo;
		y = yNuevo;
	} while (!gameOver);
	mostrarGanador(puntosA, puntosB, jugadorA, jugadorB);
}

void cambiarTurno(char& turnoJugador)
{
	if (turnoJugador == 'A')
		turnoJugador = 'B';
	else
		turnoJugador = 'A';
}

void dibujarMapa()
{

	int posicionY = MARCO_ARRIBA_TABLERO;
	for (int i = 0; i < LADO_TABLERO * 2; i += 2)
	{
		
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
		posicionY += 2;
	}
	//Dibujar coordenadas
	for (int i = 0; i < LADO_TABLERO; i++)
	{
		Console::SetCursorPosition(MARCO_IZQUIERDA_TABLERO - 2, MARCO_ARRIBA_TABLERO + i * 2);
		Console::BackgroundColor = ConsoleColor::Black;
		Console::ForegroundColor = ConsoleColor::DarkGray;
		printf("%d", LADO_TABLERO - i);

		Console::SetCursorPosition(MARCO_IZQUIERDA_TABLERO + 2 + i * 5, MARCO_ARRIBA_TABLERO - 1);
		printf("%c", 97 + i);

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
	int posicionXHorizontal, posicionYHorizontal;
	posicionXHorizontal = MARCO_IZQUIERDA_TABLERO + 2;
	posicionYHorizontal = MARCO_ARRIBA_TABLERO + 8 * 2;

	int posicionXVertical, posicionYVertical;
	posicionXVertical = MARCO_IZQUIERDA_TABLERO + 8 * 5 + 1;
	posicionYVertical = MARCO_ARRIBA_TABLERO;
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
		tecla = toupper(tecla);
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
	Console::BackgroundColor = ConsoleColor::Black;
	for (int i = 0; i < 6; i++)
	{
		Console::SetCursorPosition(MARCO_IZQUIERDA_MENSAJE, 5 + i);
		printf("                                            ");
	}
	
}

bool movimientoDamaValido(int x, int y, int xNuevo, int yNuevo, bool& come)
{
	int fichasEnRango = 0;
	
	int xAux, yAux;
	xAux = x;
	yAux = y;
	for (int i = 0; i < abs(y-yNuevo); i++)
	{
		if (xNuevo >= x)
			xAux++;
		else
			xAux--;
		
		if (yNuevo >= y)
			yAux++;
		else
			yAux--;

		if (fichas[yAux][xAux].existe)
		{
			fichasEnRango++;
			if (fichas[yAux][xAux].tipo == fichas[y][x].tipo)
				return false;
			
		}
		
	}
	

		Console::SetCursorPosition(0, 0);
		cout << fichasEnRango;
	come = fichasEnRango == 1;
	return fichasEnRango == 0 || fichasEnRango == 1;
}

bool puedeMover(int x, int y, int xNuevo, int yNuevo, bool &come)
{
	if (fichas[y][x].dama)
	{
		return !fichas[yNuevo][xNuevo].existe && estaEnNegro(xNuevo, yNuevo) &&
			estaEnDiagonal(x, y, xNuevo, yNuevo) && movimientoDamaValido(x, y, xNuevo, yNuevo, come);
	}
	else {
		bool movimientoValido = false;
		switch (fichas[y][x].tipo)
		{
		case 'A':
			if (yNuevo < y)
				return false;

			if (y + 1 < LADO_TABLERO)
			{
				if (x - 1 >= 0 && xNuevo < x && fichas[y + 1][x - 1].existe && fichas[y + 1][x - 1].tipo == 'B')
					come = true;
				else if (x + 1 < LADO_TABLERO && xNuevo > x && fichas[y + 1][x + 1].existe && fichas[y + 1][x + 1].tipo == 'B')
					come = true;
				else
					come = false;

				movimientoValido = yNuevo - y == 1;
				break;
			}

		case 'B':
			if (yNuevo > y)
				return false;
			if (y - 1 >= 0) {
				if (x - 1 >= 0 && xNuevo < x && fichas[y - 1][x - 1].existe && fichas[y - 1][x - 1].tipo == 'A')
					come = true;
				else if (x + 1 < LADO_TABLERO && xNuevo > x && fichas[y - 1][x + 1].existe && fichas[y - 1][x + 1].tipo == 'A')
					come = true;
				else
					come = false;

				movimientoValido = y - yNuevo == 1;
				break;
			}
		}

		if (come)
			movimientoValido = abs(yNuevo - y) == 2;

		if (fichas[yNuevo][xNuevo].existe || !estaEnNegro(xNuevo, yNuevo))
		{
			//No se puede mover a esa posicion
			mensajes(2);
			return false;
		}
		Console::SetCursorPosition(65, 14);
		return estaEnDiagonal(x, y, xNuevo, yNuevo) && movimientoValido;
	}
}

bool estaEnDiagonal(int x, int y, int xNuevo, int yNuevo)
{
	bool esDiag = abs(x - xNuevo) == abs(y - yNuevo);
	return esDiag;
}
void mensajes(int tipo)
{
	borrarTexto();
	Console::ForegroundColor = COLOR_FICHA_A;
	
	switch (tipo)
	{
	case 1:
		Console::SetCursorPosition(MARCO_IZQUIERDA_MENSAJE,7);
		printf("NO PUEDE SELECCIONAR ESA POSICION");
		Console::SetCursorPosition(MARCO_IZQUIERDA_MENSAJE,8);
		printf("INTENTE OTRA VEZ");
		break;
	case 2:
		Console::SetCursorPosition(MARCO_IZQUIERDA_MENSAJE, 7);
		printf("NO PUEDE MOVER A ESA POSICION");
		Console::SetCursorPosition(MARCO_IZQUIERDA_MENSAJE, 8);
		printf("INTENTE OTRA VEZ");
		//preguntar por empate
		Console::SetCursorPosition(MARCO_IZQUIERDA_MENSAJE, 10);
		printf("SI DESEA DECLARAR EMPATE DIGITE LA TECLA  E");
		break;
	case 3:
		//creditos
		system("cls");
		graficos();
		Console::BackgroundColor = ConsoleColor::Black;
		Console::SetCursorPosition(47, 4);
		cout << "Akkadia Studios";
		Console::BackgroundColor = ConsoleColor::Black;
		Console::SetCursorPosition(49, 10);
		cout << "Creadores:";
		Console::BackgroundColor = ConsoleColor::Black;
		Console::SetCursorPosition(49, 15);
		cout << "Luis Maco";
		Console::BackgroundColor = ConsoleColor::Black;
		Console::SetCursorPosition(47, 16);
		cout << "Oliver Tuesta";
		Console::BackgroundColor = ConsoleColor::Black;
		Console::SetCursorPosition(49, 17);
		cout << "Brian Díaz";
		Console::BackgroundColor = ConsoleColor::Black;
		Console::SetCursorPosition(35, 26);
		cout << "Presione cualquier tecla para volver...";
		_getch();
		break;
	case 4:
		//Instrucciones
		system("cls");
		graficos();
		Console::BackgroundColor = ConsoleColor::Black;
		Console::SetCursorPosition(47, 4);
		cout << "INSTRUCCIONES";
		Console::SetCursorPosition(26, 7);
		cout << "Este juego es para dos personas, en el cual deberán";
		Console::SetCursorPosition(26, 8);
		cout << "competir por turnos. Para ganar, se debe dejar inmovilizado";
		Console::SetCursorPosition(26, 9);
		cout << "al otro jugador o comer todas sus fichas, así de simple.";
		Console::SetCursorPosition(47, 12);
		cout << "JUGABILIDAD";
		Console::SetCursorPosition(26, 14);
		cout << "las mecanicas necesarias para jugar este videojuego son:";
		Console::SetCursorPosition(26, 15);
		cout << "Con FLECHA ARRIBA, FLECHA ABAJO, FLECHA IZQUIERA, FLECHA";
		Console::SetCursorPosition(26, 16);
		cout << "DERECHA se selecciona la ficha, se presiona ENTER para";
		Console::SetCursorPosition(26, 17);
		cout << "confirmar la misma y seleccionar la posición de destino.";
		Console::SetCursorPosition(26, 18);
		cout << "Si una ficha llega al extremo contrario del tablero, se";
		Console::SetCursorPosition(26, 19);
		cout << "convierte en reina, pudiendo moverse dentro de varios";
		Console::SetCursorPosition(26, 20);
		cout << "cuadros en diagonal.";
		Console::SetCursorPosition(26, 22);
		cout << "               Eso es todo. Buena suerte.";
		Console::SetCursorPosition(35, 25);
		cout << "Presione cualquier tecla para volver...";
		Console::SetCursorPosition(35, 29);
		cout << "       © Akkadia Studios, 2021";
		_getch();
		break;
	case 5:
		//EMAPATE
		system("cls");
		graficos();
		Console::BackgroundColor = ConsoleColor::Black;
		Console::SetCursorPosition(50, 4);
		cout << "GAME OVER";
		Console::SetCursorPosition(40, 8);
		cout << "EL JUEGO SE HA DECLARADO EMPATE";
		Console::SetCursorPosition(35, 28);
		cout << "Presione cualquier tecla para volver...";
		_getch();
		break;

	}
	
}

void mostrarTurno(char turnoJugador, string jugadorA, string jugadorB)
{
	switch (turnoJugador)
	{
	case 'A':
		Console::SetCursorPosition(MARCO_IZQUIERDA_MENSAJE, 5);
		cout << "turno del jugador " << jugadorA << " (blancas)";
		break;
	case 'B':
		Console::SetCursorPosition(MARCO_IZQUIERDA_MENSAJE, 5);
		cout << "turno del jugador " << jugadorB << " (rojas)";
		break;
	}
}

void comerFichas(int x, int y, int xNuevo, int yNuevo, int &puntosA, int &puntosB)
{	
	ficha f;
	if (fichas[y][x].dama)
	{
		int xAux, yAux;
		xAux = x;
		yAux = y;
		for (int i = 0; i < abs(y - yNuevo); i++)
		{
			if (xNuevo >= x)
				xAux++;
			else
				xAux--;

			if (yNuevo >= y)
				yAux++;
			else
				yAux--;

			if (fichas[yAux][xAux].existe)
			{
				if (fichas[yAux][xAux].tipo == 'A')
					puntosB++;
				
				else
					puntosA++;

				fichas[yAux][xAux].existe = false;
			}
		}
	}
	else {
		if (fichas[y][x].tipo == 'A')
		{
			if (xNuevo < x) {
				fichas[y + 1][x - 1].existe = false;
				f = fichas[y + 1][x - 1];
			}
			else if (xNuevo > x) {
				fichas[y + 1][x + 1].existe = false;
				f = fichas[y + 1][x + 1];
			}
			puntosA++;
		}
		else
		{
			if (xNuevo < x) {
				fichas[y - 1][x - 1].existe = false;
				f = fichas[y - 1][x - 1];
			}
			else if (xNuevo > x) {
				fichas[y - 1][x + 1].existe = false;
				f = fichas[y - 1][x + 1];
			}
			puntosB++;
		}
	}
		
}

bool estaEnNegro(int x, int y)
{
	bool estaNegro;
	if (y % 2 == 0)
		estaNegro = x % 2 != 0;
	else
		estaNegro = x % 2 == 0;
	return estaNegro;
}
void pedirDatos(string &jugadorA, string &jugadorB)
{
	borrarTexto();
	Console::BackgroundColor = ConsoleColor::Black;
	Console::ForegroundColor = COLOR_FICHA_A;
	Console::SetCursorPosition(MARCO_IZQUIERDA_MENSAJE, 5);
	cout << "Jugador A (blancas) ingrese su nombre : \n";
	Console::SetCursorPosition(MARCO_IZQUIERDA_MENSAJE, 6);
	cin >> jugadorA;
	borrarTexto();
	Console::SetCursorPosition(MARCO_IZQUIERDA_MENSAJE, 5);
	cout << "Jugador B (Rojas) ingrese su nombre : \n";
	Console::SetCursorPosition(MARCO_IZQUIERDA_MENSAJE, 6);
	cin >> jugadorB;
	borrarTexto();
}

bool quedanMovimientos()
{
	//TODO 
	bool quedan = true;
	for (int i = 0; i < LADO_TABLERO; i++)
	{
		for (int j = i % 2 == 0 ? 1 : 0; j < 8; j += 2)
		{
			if ((j + 1 < LADO_TABLERO && fichas[j][i].tipo == 'A') || 
				(j - 1 >= 0 && fichas[j][i].tipo == 'B'))
			{
				quedan = true;
			}
			else if ((j + 2 < LADO_TABLERO && fichas[j][i].tipo == 'A' && fichas[j][i].tipo == 'B') ||
				(j - 2 >= 0 && fichas[j][i].tipo == 'B' && fichas[j][i].tipo == 'A'))
			{
				quedan = true;
			}
		}
	}
	return quedan;
}

void dibujarFichasComidas(int puntosA, int puntosB) 
{
	Console::BackgroundColor = ConsoleColor::Black;
	//fichas comidas por A
	Console::ForegroundColor = COLOR_FICHA_B;
	for (int i = 0; i < puntosA; i++)
	{
		Console::SetCursorPosition(MARCO_IZQUIERDA_MENSAJE + i * 2 , 19);
		printf("%c", CARACTER_FICHA);

	}
	//fichas comidas por B
	Console::ForegroundColor = COLOR_FICHA_A;
	for (int i = 0; i < puntosB; i++)
	{
		Console::SetCursorPosition(MARCO_IZQUIERDA_MENSAJE + i * 2, 20);
		printf("%c", CARACTER_FICHA);
	}

}

void mostrarMovimientos(int a, int b) 
{
	Console::SetCursorPosition(MARCO_IZQUIERDA_MENSAJE, 16);
	printf("MOVIMIENTOS:");
	Console::SetCursorPosition(MARCO_IZQUIERDA_MENSAJE, 17);
	printf("BLANCAS: %d  ROJAS: %d", a, b);

}

void mostrarGanador(int puntosA, int puntosB, string jugadorA, string jugadorB) 
{
	system("cls");
	graficos();
	Console::BackgroundColor = ConsoleColor::Black;
	Console::SetCursorPosition(50, 4);
	cout << "GAME OVER";
	Console::SetCursorPosition(35, 8);
	cout << "El ganador es: ";
	if (puntosA>puntosB)
		cout << jugadorA << " (BLANCAS)";
	else
		cout << jugadorB << " (ROJAS)";

	Console::SetCursorPosition(35, 28);
	cout << "Presione cualquier tecla para volver...";
	_getch();
}