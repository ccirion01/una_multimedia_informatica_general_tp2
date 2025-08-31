#include "Muro.h"

Muro::Muro(float x, float y, int alto, int ancho, int anchoMax)
{
    m_x = x;
    m_y = y;    
    m_alto = alto;
    m_ancho = ancho;
    m_anchoMax = anchoMax; // TODO: Ver si es necesario.
}

// TODO: Ver si mover muros o dejarlos fijos.
void Muro::update()
{
    // m_y = m_y + 0.2f;

    // if (m_y >= 39)
    // {
    //     m_ancho = rand() % (m_anchoMax - 5) + 4;
    //     m_y = 5;
    // }
}

void Muro::draw()
{
    for (int i = 0; i < m_alto; i++)
    {
        for (int j = 0; j < m_ancho; j++)
        {
            mvaddch(m_y + i, m_x + j, ACS_CKBOARD);
        }
    }
}

bool Muro::ocupa(int x, int y)
{
    return (y >= m_y && y < m_y + m_alto) && (x >= m_x && x < m_x + m_ancho);
}