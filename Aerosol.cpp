#include "Aerosol.h"

Aerosol::Aerosol(float x, float y)
{
  m_x = x;
  m_y = y;
}

void Aerosol::update()
{
  m_y = m_y + 0.4f;

  if (m_y >= 39)
  {
    m_x = rand() % 119 + 1;
    m_y = 1;
  }
}

void Aerosol::draw()
{
  wchar_t w_aerosol = 0x1F3A8;
  setcchar(&aerosol, &w_aerosol, A_NORMAL, 0, nullptr);
  mvadd_wch(m_y, m_x, &aerosol);
}

void Aerosol::colision(Artista &rArtista)
{
  if(m_x >= rArtista.getX() && m_x <= rArtista.getX() + 4 && m_y >= rArtista.getY() && m_y <= rArtista.getY() + 2)
  {
    rArtista.setAerosoles(rArtista.getAerosoles() + 1);

    m_x = rand() % 119 + 1;
    m_y = 1;
  }
}

float Aerosol::getX() { return m_x; }
float Aerosol::getY() { return m_y; }