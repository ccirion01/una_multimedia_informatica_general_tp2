#pragma once
#include <ncurses.h>

class Muro
{
public:
  Muro(float x, float y, int alto, int ancho, int anchoMax);
  void update();
  void draw();
  bool ocupa(int x, int y);

private:
  float m_x, m_y;
  int m_ancho, m_alto, m_anchoMax;
};