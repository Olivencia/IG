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

void update_points(vector<_vertex3f> &Vertices, int &rep);

void update_faces(vector<_vertex3f> &Vertices, vector<_vertex3i> &Faces, int rep);

void normal_faces(vector<_vertex3f> &Vertices,vector<_vertex3i> &Faces, vector<_vertex3f> &n, vector<_vertex3f> &bariv);

void normal_points(vector<_vertex3f> &Vertices, vector<_vertex3i> &Faces, vector<int> &nv, vector<int> &nf);

bool is_here(int v0, int v1, int v2, int val);

void update_components(vector<_vertex3f> &Vertices, vector<_vertex3i> &Faces, int rep, bool color, bool ajedrez);

void adjust(vector<float> &v, vector<int> &f, vector<_vertex3f> &Vertices, vector<_vertex3i> &Faces);

void write(vector<_vertex3f> &Vertices, vector<_vertex3i> &Faces, vector<_vertex3f> &n, vector<_vertex3f> bariv, bool color, bool ajedrez, bool normal);

void draw_file(int valor, bool color, bool ajedrez, bool normal);

void leidos(bool leido0, bool leido1, bool leido2, bool leido3);


