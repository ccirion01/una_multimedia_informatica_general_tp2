#pragma once
#include <ncurses.h>

class Policia
{
public:
  Policia(int xArtista, int yArtista);
  void update(int xArtista, int yArtista);
  void draw();

  int getX();
  int getY();

private:
  int m_x, m_y;
};