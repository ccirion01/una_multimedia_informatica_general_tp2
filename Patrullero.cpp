#include "Patrullero.h"

Patrullero::Patrullero(float x, float y)
{
  m_x = x;
  m_y = y;
}

void Patrullero::update()
{
  m_y = m_y + 0.4f;

  if (m_y >= 39)
  {
    m_x = rand() % 119 + 1;
    m_y = 1;
  }
}

void Patrullero::draw()
{
  wchar_t w_carita = 0x1F693;
  cchar_t carita;
  setcchar(&carita, &w_carita, A_NORMAL, 0, nullptr);
  mvadd_wch(m_y, m_x, &carita);
}

void Patrullero::colision(Artista &rArtista )
{
  if(m_x >= rArtista.getX() && m_x <= rArtista.getX() + 4 && m_y >= rArtista.getY() && m_y <= rArtista.getY() + 2)
  {
    rArtista.setAerosoles(rArtista.getAerosoles() - 1);

    m_x = rand() % 119 + 1;
    m_y = 1;
  }
}

float Patrullero::getX() { return m_x; }
float Patrullero::getY() { return m_y; }