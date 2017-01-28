//**************************************************************************
// Práctica 1
//
// Domingo Martin Perandres 2013
//
// GPL
//**************************************************************************

#include <GL/gl.h>
#include <vector>
#include "vertex.h"
#include "file_ply_stl.h"
#include <iostream>
#include "jpg_imagen.hpp"

using namespace std;

void menu();

void draw_file(int valor, bool color, bool ajedrez, bool normal, int gl, bool idle, bool noc, bool nov, _vertex2f angles, _vertex2f coord);
void draw_file();
void draw_file2(int valor, bool color, bool ajedrez, bool normal, int gl,bool idle, bool noc, bool nov, _vertex2f angles, _vertex2f coord);

float ecRect(float &gr, int mov, float ang1, float ang2);

void grados_libertad(int gral);

void animar();

//Estructuras
void skater();
void skateboard();
void skeleton();
void head();
void tetraedro();
void hair();
void beethoven();


