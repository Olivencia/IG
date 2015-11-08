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

using namespace std;

void menu();

void mostrar_vertices(vector<_vertex3f> &Vertices);

void mostrar_caras(vector<_vertex3i> &Faces);

void update_points(vector<_vertex3f> &Vertices, int &rep);

void update_points_mitad(vector<_vertex3f> &Vertices, int &rep);

void update_faces(vector<_vertex3f> &Vertices, vector<_vertex3i> &Faces, int rep);

void normal_faces(vector<_vertex3f> &Vertices,vector<_vertex3i> &Faces, vector<_vertex3f> &n, vector<_vertex3f> &bariv);

void normal_points(vector<_vertex3f> &Vertices, vector<_vertex3i> &Faces, vector<int> &nv, vector<int> &nf);

bool is_here(int v0, int v1, int v2, int val);

void update_components(vector<_vertex3f> &Vertices, vector<_vertex3i> &Faces, int rep, bool color, bool ajedrez);

void adjust(vector<float> &v, vector<int> &f, vector<_vertex3f> &Vertices, vector<_vertex3i> &Faces);

void write(vector<_vertex3f> &Vertices, vector<_vertex3i> &Faces, bool color, bool ajedrez);

void draw_file(int valor, bool color, bool ajedrez, bool normal, int gl, bool idle);

void leidos(bool leido0, bool leido1, bool leido2, bool leido3);

void draw(vector<_vertex3f> &Vertices,vector<_vertex3i> &Faces, bool ajedrez);

float ecRect(float &gr, int mov, float ang1, float ang2);

void animar();

//Objetos
void figura();
void cubo();
void cono();
void esfera();
void semiesfera();
void cilindro();
void cilindro2();
void cilindro3();

//Estructuras
void skater();
void skateboard();
void skeleton();
void head();
void tetraedro();
void hair();
void beethoven();

//Las demás funciones no son necesarias declararlas aquí


