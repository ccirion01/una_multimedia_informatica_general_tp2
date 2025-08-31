#include "Artista.h"
#include "Muro.h"
#include <vector>

using namespace std;

Artista::Artista() 
  :m_x(60), m_y(20), m_aerosoles(3), m_vidas(2), m_atrapada(false)
{
}

void Artista::setup()
{
  m_x = 60;
  m_y = 20;
  
  m_aerosoles = 3;
  m_vidas = 2;

  m_atrapada = false;
}

void Artista::update()
{
  if (m_aerosoles <= 0)
	{
    m_atrapada = true;
    m_vidas--;
    m_aerosoles = 3;
  }
}

void Artista::draw()
{
  if (!m_atrapada)
  {
    mvaddch(m_y,     m_x + 2, 'O');        // Cabeza
    mvaddch(m_y + 1, m_x + 1, '/');
    mvaddch(m_y + 1, m_x + 2, '|');        // Cuerpo
    mvaddch(m_y + 1, m_x + 3, '\\');
    mvaddch(m_y + 2, m_x + 1, '/');
    mvaddch(m_y + 2, m_x + 3, '\\');
    mvaddch(m_y + 2, m_x + 2, 'o');        // Spray en mano
  }
  else
  {
    wchar_t w_policia = 0x1F694;   // 🚔
    wchar_t w_golpe   = 0x1F4A2;   // 💢
    cchar_t policia;
    cchar_t golpe;
    setcchar(&policia, &w_policia, A_NORMAL, 0, nullptr);
    setcchar(&golpe,   &w_golpe,   A_NORMAL, 0, nullptr);

    // Artista atrapada
    mvadd_wch(m_y,     m_x + 2, &golpe);
    mvadd_wch(m_y + 1, m_x + 1, &policia);
    mvadd_wch(m_y + 1, m_x + 3, &policia);
    mvadd_wch(m_y + 2, m_x + 2, &golpe);

    mvprintw(m_y + 4, m_x - 8, "La poli te atrapó!");
    refresh();
    delay_output(1500);
  
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
  if (m_aerosoles > 3) m_aerosoles = 3;
}
int Artista::getAerosoles() { return m_aerosoles; }

void Artista::setVidas(int vidas) { m_vidas = vidas; }
int Artista::getVidas() { return m_vidas; }