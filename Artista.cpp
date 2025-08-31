#include "Artista.h"
#include "Muro.h"
#include <vector>

using namespace std;

Artista::Artista() 
  :m_x(60), m_y(20), m_aerosoles(5), m_vidas(2), m_atrapada(false)
{
}

void Artista::setup()
{
  m_x = 60;
  m_y = 20;
  
  m_aerosoles = 5;
  m_vidas = 2;

  m_atrapada = false;
}

void Artista::update()
{
  if (m_aerosoles <= 0)
	{
    m_atrapada = true;
    m_vidas--;
    m_aerosoles = 5;
  }
}

void Artista::draw()
{
  if (!m_atrapada)
  {
    // TODO: Dibujar a la artista libre.
    mvaddch(m_y, m_x + 2, '^');
    mvaddch(m_y + 1, m_x + 1, '(');
    mvaddch(m_y + 1, m_x + 2, ACS_PLMINUS);
    mvaddch(m_y + 1, m_x + 3, ')');
    mvaddch(m_y + 2, m_x, ACS_ULCORNER);
    mvaddch(m_y + 2, m_x + 1, '#');
    mvaddch(m_y + 2, m_x + 2, ' ');
    mvaddch(m_y + 2, m_x + 3, '#');
    mvaddch(m_y + 2, m_x + 4, ACS_URCORNER);
  }
  else
  {
    // TODO: Dibujar a la artista atrapada por la policia.
    wchar_t w_fuego = 128293;
    wchar_t w_explosion = 128165;
    cchar_t fuego;
    cchar_t explosion;
    setcchar(&fuego, &w_fuego, A_NORMAL, 0, nullptr);
    setcchar(&explosion, &w_explosion, A_NORMAL, 0, nullptr);

    // Dibujamos el fuego.
    mvadd_wch(m_y, m_x + 2, &fuego);
    mvadd_wch(m_y + 1, m_x + 1, &fuego);
    mvadd_wch(m_y + 1, m_x + 2, &fuego);
    mvadd_wch(m_y + 2, m_x, &fuego);
    mvadd_wch(m_y + 2, m_x + 1, &fuego);
    mvadd_wch(m_y + 2, m_x + 2, &fuego);

    refresh();
    delay_output(200);

    // Dibujamos la explosión.
    mvprintw(m_y - 1, m_x - 3, ".         .");
    mvprintw(m_y + 3, m_x - 3, "'         '");
    mvadd_wch(m_y - 1, m_x + 2, &explosion);

    mvadd_wch(m_y, m_x, &explosion);
    mvadd_wch(m_y, m_x + 5, &explosion);
    mvaddch(m_y, m_x + 2, ' ');

    mvadd_wch(m_y + 1, m_x - 2, &explosion);
    mvadd_wch(m_y + 1, m_x + 6, &explosion);
    // Borramos un fuego para que quede bien.
    mvaddch(m_y + 1, m_x + 1, ' ');

    mvadd_wch(m_y + 2, m_x, &explosion);
    mvadd_wch(m_y + 2, m_x + 5, &explosion);
    // Borramos un fuego para que quede bien.
    mvaddch(m_y + 2, m_x + 2, ' ');

    mvadd_wch(m_y + 3, m_x + 2, &explosion);

    refresh();
    delay_output(200);
  
    m_atrapada = false;
  }
}

// TODO: Mover colisiones con muros acá.
// bool Artista::puedeMover(int nuevoX, int nuevoY, const vector<Muro>& muros)
// {
//     for (int i = 0; i < muros.size(); i++)
//     {
//         if (muros[i].ocupa(nuevoX, nuevoY))
//             return false;
//     }
//     return true;
// }

void Artista::setX(int x) { m_x = x; }
void Artista::setY(int y) { m_y = y; }

int Artista::getX() { return m_x; }
int Artista::getY() { return m_y; }

void Artista::setAerosoles(int aerosoles) { 
  m_aerosoles = aerosoles;
  if (m_aerosoles < 0) m_aerosoles = 0;
  if (m_aerosoles > 5) m_aerosoles = 5;
}
int Artista::getAerosoles() { return m_aerosoles; }

void Artista::setVidas(int vidas) { m_vidas = vidas; }
int Artista::getVidas() { return m_vidas; }