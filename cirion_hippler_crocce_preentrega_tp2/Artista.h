#pragma once
#include <ncurses.h>
#include <cstdlib>
#include <vector>

class Muro;

using namespace std;

class Artista
{
public:
  Artista();
  void setup();
  void draw();
  void update();

  // bool puedeMover(int nuevoX, int nuevoY, const vector<Muro>& muros);

  void setX(int x);
  void setY(int y);

  int getX();
  int getY();

  void setAerosoles(int aerosoles);
  int getAerosoles();

  void setVidas(int vidas);
  int getVidas();

private:
  int m_x, m_y;
  int m_aerosoles;
  int m_vidas;
  bool m_atrapada;
};