#pragma once
#include <ncurses.h>
#include <cstdlib>
#include "Artista.h"

class Aerosol
{
public:
  Aerosol(float x, float y);
  void update();
  void draw();

  void colision(Artista &rArtista);

  float getX();
  float getY();

private:
  float m_x, m_y;
};