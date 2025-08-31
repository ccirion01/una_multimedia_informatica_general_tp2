// Crocce Ana Laura
// Hippler María Silvina
// Cirión Constanza

#include <iostream>
#include <ncurses.h>
#include <cstdlib>
#include <ctime>
#include "Artista.h"
#include "Patrullero.h"
#include "Policia.h"
#include "Aerosol.h"
#include "Muro.h"
#include <vector>

using namespace std;

//=========================================================================
// DECLARACION DE LAS CONSTANTES
//=========================================================================

const int ANCHO_PANTALLA = 120;
const int ALTO_PANTALLA = 40;
const int DELAY = 30;

//=========================================================================
// DEFINICION DE LAS VARIABLES GLOBALES
//=========================================================================

bool game_over;
int puntaje;
bool salir;

Artista artista;
Policia policia(artista.getX(), artista.getY());

vector<Patrullero> Patrulleros;
vector<Aerosol> Aerosoles;
vector<Muro> Muros;

//=========================================================================
// DECLARACION DE LAS FUNCIONES GLOBALES
//=========================================================================

void setup();
void input();
void update();
void draw();
void gameOver();
bool puedeMoverArtista(int nuevoX, int nuevoY);

//=========================================================================
// MAIN
//=========================================================================

int main()
{
	setlocale(LC_ALL, "");

	srand(time(0));
	
	initscr();
	noecho();
	curs_set(FALSE);
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);

	// if (LINES < ALTO_PANTALLA || COLS < ANCHO_PANTALLA)
	// {
	// 	endwin();
	// 	printf("La terminal tiene que tener como mínimo %dx%d\n\n", ANCHO_PANTALLA, ALTO_PANTALLA);
	// 	exit(1);
	// }

	setup();

	salir = false;

	while (!salir)
	{
		while (!game_over)
		{
			input();
			update();
			draw();
		}
		gameOver();
	}

	endwin();

	cout << endl;
	return 0;
}

//=========================================================================
// DEFINICION DE LAS FUNCIONES GLOBALES
//=========================================================================

void setup()
{
	game_over = FALSE;
	puntaje = 0;

	artista.setup();

	Patrulleros.clear();
	Aerosoles.clear();
	Muros.clear();

	for (int i = 0; i < 3; i++)
	{
		Patrulleros.push_back(Patrullero(rand() % 119 + 1, rand() % 10 + 1));
		Aerosoles.push_back(Aerosol(rand() % 119 + 1, rand() % 7 + 1));
	}

	int anchoMax = ANCHO_PANTALLA / 3 + 5;

	// TODO: Reutilizar codigo.
    // Muros izquierda
    float y = 5;
    for (int i = 0; i <= 7; i++)
    {
        int ancho = rand() % (anchoMax - 5) + 4;
		float x = 1;
        int alto = rand() % 4 + 3;
        if (y + alto >= ALTO_PANTALLA - 1) break;
        Muros.push_back(Muro(x, y, alto, ancho, anchoMax));
        y += alto + 0.5f;
    }

    // Muros derecha
    y = 5;
    for (int i = 0; i <= 7; i++)
    {
        int ancho = rand() % (anchoMax - 5) + 4;
        float x = ANCHO_PANTALLA - ancho - 1;
        int alto = rand() % 4 + 3;
        if (y + alto >= ALTO_PANTALLA - 1) break;
        Muros.push_back(Muro(x, y, alto, ancho, anchoMax));
        y += alto + 0.5f;
    }
}

///////////////////////////////////////////////////////////////////////////
void input()
{
	int tecla = getch();
    int nuevoX = artista.getX();
    int nuevoY = artista.getY();

	switch (tecla)
	{
		case KEY_UP:
			nuevoY = artista.getY() - 1;
			if (nuevoY > 1 && puedeMoverArtista(nuevoX, nuevoY)) artista.setY(nuevoY);
			break;
		case KEY_DOWN:
			nuevoY = artista.getY() + 1;
			if (nuevoY < ALTO_PANTALLA - 7 && puedeMoverArtista(nuevoX, nuevoY)) artista.setY(nuevoY);
			break;
		case KEY_LEFT:
			nuevoX = artista.getX() - 1;
			if (nuevoX > 1 && puedeMoverArtista(nuevoX, nuevoY)) artista.setX(nuevoX);
			break;
		case KEY_RIGHT:
			nuevoX = artista.getX() + 1;
			if (nuevoX < ANCHO_PANTALLA - 6 && puedeMoverArtista(nuevoX, nuevoY)) artista.setX(nuevoX);
			break;
		case 27:
			game_over = TRUE;
			break;
		default:
			break;
	}
}

///////////////////////////////////////////////////////////////////////////
void update()
{
	artista.update();
	policia.update(artista.getX(), artista.getY());

	if (artista.getVidas() <= 0) game_over = true;

	for (int i = 0; i < Patrulleros.size(); i++)
	{
		Patrulleros[i].update();
		Patrulleros[i].colision(artista);
	}

	for (int i = 0; i < Aerosoles.size(); i++)
	{
		Aerosoles[i].update();
		Aerosoles[i].colision(artista);
	}

	for (int i = 0; i < Muros.size(); i++)
	{
		Muros[i].update();
	}
}

///////////////////////////////////////////////////////////////////////////
void draw()
{
	erase();
	box(stdscr, 0, 0);

	mvprintw(0, 15, "[ AEROSOLES:           ]");
    for (int i = 0; i < artista.getAerosoles(); i++)
    {
        wchar_t w_aerosol = 0x1F3A8; // 🎨
        cchar_t aerosol;
        setcchar(&aerosol, &w_aerosol, A_NORMAL, 0, nullptr);
        mvadd_wch(0, 27 + i * 2, &aerosol);
    }

	mvprintw(0, 80, "[ VIDAS:     ]");
	for (int i = 0; i < artista.getVidas(); i++)
	{
		wchar_t w_corazon = 0x1F49B; // 💛
		cchar_t corazon;
		setcchar(&corazon, &w_corazon, A_NORMAL, 0, nullptr);
		mvadd_wch(0, 89 + i, &corazon);
	}

	artista.draw();
	policia.draw();

	for (int i = 0; i < Patrulleros.size(); i++)
		Patrulleros[i].draw();

	for (int i = 0; i < Aerosoles.size(); i++)
		Aerosoles[i].draw();

	for (int i = 0; i < Muros.size(); i++)
        Muros[i].draw();

	refresh();
	delay_output(DELAY);
}

///////////////////////////////////////////////////////////////////////////
// TODO: Mover a clase Artista.
bool puedeMoverArtista(int nuevoX, int nuevoY)
{
    for (int i = 0; i < Muros.size(); i++)
    {
        if (Muros[i].ocupa(nuevoX, nuevoY))
            return false;
    }
    return true;
}

///////////////////////////////////////////////////////////////////////////
void gameOver()
{
	// TODO: Meter algun grafico de "Game Over".
	for (int y = 10; y < 16; y++)	mvhline(y, 40, ' ', 40);

	mvaddch(9, 39, ACS_ULCORNER);
	mvaddch(9, 80, ACS_URCORNER);
	mvaddch(16, 39, ACS_LLCORNER);
	mvaddch(16, 80, ACS_LRCORNER);

	mvhline(9, 40, ACS_HLINE, 40);
	mvhline(16, 40, ACS_HLINE, 40);

	mvvline(10, 39, ACS_VLINE, 6);
	mvvline(10, 80, ACS_VLINE, 6);

	mvprintw(12, 55, "GAME OVER");
	mvprintw(13, 50, "VOLVER A JUGAR? (S/N)");

	int opcion = getch();

	if (opcion == 's' || opcion == 'S')
	{
		game_over = false;
		setup();
	}
	else if (opcion == 'n' || opcion == 'N')
	{
		salir = TRUE;
	}
}