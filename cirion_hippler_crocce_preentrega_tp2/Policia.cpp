#include "Policia.h"

Policia::Policia(int xArtista, int yArtista)
{
  m_x = xArtista;
  m_y = yArtista + 1;
}

void Policia::update(int xArtista, int yArtista)
{
  m_x = xArtista + 2;
  m_y = yArtista + 5;
}

void Policia::draw()
{
    wchar_t w_poli = 0x1F46E;
    cchar_t poli;
    setcchar(&poli, &w_poli, A_NORMAL, 0, nullptr);
    mvadd_wch(m_y, m_x, &poli);
}