//**************************************************************************
// Codigo del usuario
//
// Domingo Martin Perandres 2013
//
// GPL
//**************************************************************************

#include "user_code.h"
#include "vertex.h"
#include <math.h>
#include <stdio.h>
#include "object.cc"


const float pi=3.14159265;
bool arriba=false, abajo=false, leido0=true, leido1=false, leido2=false, leido3=false, norm_ver=false, norm_car=false, ini=true, inicio=true, revo1=false, revo2=false, aje, aumento=true,id, in=true, nnormal=false, texin1=false, texin2=false, t_on=false;
float vy1, vy2, ang1 = 0.0 ,ang2 = 360.0, gr1=0,gr2, gr3=0,desp=0, aum=1;
int gral,val, movimiento=100;
jpg::Imagen * img_lata1, *img_lata2, * img_madera;
_file_ply ply;
char * archivo1 = "ply/beethoven.ply";
char * archivo2 = "ply/perfil.ply";
Object peon, peon_text, latasup, latacue1, latacue2, latainf, ply_beethoven, generic, sphere_form, semisphere_form, cylinder_form, cylinder2_form, cylinder3_form, semicylinder_form, cube_form, tetrahedron_form;
enum Figuras { cube=0, sphere=1, semisphere=2, cylinder=3, cylinder_2 = 4, cylinder_3 = 5, semicylinder=6, tetrahedron=7 };

/******************************************************************************/
//MATERIALES
/******************************************************************************/

GLfloat skin_a[]={0.8,0.65,0.3,0.0}, skin_d[]={1,0.85,0.5,1.0}, skin_s[]={0.0,0.0,0.0,1.0}, skin_e=5.0; // Piel
GLfloat shirt_a[]={1,0.52,0.047,1.0}, shirt_d[]={1,0.52,0.047,1.0}, shirt_s[]={0.1,0.1,0.1,1.0}, shirt_e=2.0; // Camiseta
GLfloat jeans_a[]={0.33,0.67,0.968}, jeans_d[]={0.33,0.67,0.968,1.0}, jeans_s[]={0.1,0.1,0.1,1.0}, jeans_e=2.0; // Pantalones
GLfloat shoes_a[]={0.5,0.2,0.05,1.0}, shoes_d[]={0.5,0.2,0.05,1.0}, shoes_s[]={1.0,1.0,1.0,1.0}, shoes_e=50.0; // Zapatos
GLfloat iron_a[]={0.5,0.5,0.5,1.0}, iron_d[]={0.5,0.5,0.5,1.0}, iron_s[]={1.0,1.0,1.0,1.0}, iron_e=75.0; // Hierro


GLfloat tex_a[]={1.0,1.0,1.0,1.0}, tex_d[]={1.0,1.0,1.0,1.0}, tex_s[]={1.0,1.0,1.0,1.0}, tex_e=70.0; //text
GLfloat mat1_a[]={0.3,0.3,0.3,1.0}, mat1_d[]={0.6,0.6,0.6,1.0}, mat1_s[]={0.0,0.0,0.0,1.0}, e1=0.0; // blanca
GLfloat mat2_a[]={0.0,0.0,0.0,1.0}, mat2_d[]={0.2,0.2,0.2,1.0}, mat2_s[]={1.0,1.0,1.0,1.0}, e2=100.0; //negra

//**************************************************************************
// Funciones auxiliares
//**************************************************************************
void mostrar_vertices(vector<_vertex3f> &Vertices){
  for(unsigned i=0; i<Vertices.size(); i++)
      cout << "POSICION " << i << " "  << Vertices[i].x << " " << Vertices[i].y << " " << Vertices[i].z << endl;

}

void view_objects_1();

void mostrar_caras(vector<_vertex3i> &Faces){
  for(unsigned i=0; i<Faces.size(); i++)
      cout << "POSICION " << i << " " << Faces[i]._0 << " " << Faces[i]._1 << " " << Faces[i]._2 << endl;

}

bool is_here(int v0, int v1, int v2, int val){
  bool found=false;
  if ((v0 == val || v1 == val || v2 == val) && !(v0==0 && v1==0 && v2==0)){
      found=true;

    }
  return found;
}

void load_images(){
  img_madera = new jpg::Imagen("imagenes/text-madera.jpg");
  img_lata1 = new jpg::Imagen("imagenes/duff.jpg");
  img_lata2 = new jpg::Imagen("imagenes/lata.jpg");
}

void load_objects()
{
  load_images();
  ply_beethoven.load_ply("ply/beethoven.ply");
  generic.load("ply/dibujo0.ply",NULL,100);
  cube_form.load_form(cube);
  sphere_form.load_form(sphere);
  semisphere_form.load_form(semisphere);
  cylinder_form.load_form(cylinder,20);
  cylinder2_form.load_form(cylinder_2);
  cylinder3_form.load_form(cylinder_3);
  semicylinder_form.load_form(semicylinder);
  tetrahedron_form.load_form(tetrahedron);
  peon.load(archivo2);
  peon_text.load(archivo2,img_madera);
  latasup.load("ply/lata-psup.ply",NULL,50);
  latacue1.load("ply/lata-pcue.ply",img_lata1,50);
  latainf.load("ply/lata-pinf.ply",NULL,50);
  latacue2.load("ply/lata-pcue.ply",img_lata2,50);
}


void menu(){
  cout << endl;
  cout << "************************************" << endl;
  cout << "BOTONES:" << endl;
  cout << "************************************" << endl;
  cout << "PRÁCTICA 1 -> 1" << endl;
  cout << "************************************" << endl;
  cout << "PRÁCTICA 2 -> 2" << endl;
  cout << "************************************" << endl;
  cout << "PRÁCTICA 3 -> 3" << endl;
  cout << "Z/z -> 1º grado de libertad" << endl;
  cout << "X/x -> 2º grado de libertad" << endl;
  cout << "C/c -> 3º grado de libertad" << endl;
  cout << "V/v -> Mover en eje x" << endl;
  cout << "Para conseguir animacion cambiar en PRACTICA3.CC la variable de la linea 7 idle=true" << endl;
  cout << "************************************" << endl;
  cout << "PRÁCTICA 4 -> 4" << endl;
  cout << "T/t -> Aplicar/Quitar Texturas " << endl;
  cout << "B/b -> Activar iluminacion plana " << endl;
  cout << "N/n -> Activar iluminacion suave" << endl;
  cout << "J/j -> Girar luz dinamica " << endl;
  cout << "************************************" << endl;
  cout << "Para todas las prácticas" << endl;
  cout << "P -> exit" << endl;
  cout << "CAMBIAR VISTA:" << endl;
  cout << "P -> Puntos" << endl;
  cout << "L -> Aristas" << endl;
  cout << "S -> Solido" << endl;
  cout << "A -> Solido/Ajedrez" << endl;
  cout << "RePag -> Alejar vista" << endl;
  cout << "AvPag -> Acercar vista" << endl;
  cout << "************************************" << endl;
  cout << endl;
}

float ecRect(float &gr, int mov, float ang1, float ang2){
    float g;
      if((gr<mov && gr>0))
        g=gr/(mov-1);
      else if(gr>=mov){
          gr=(mov-1);
          g=1;
      }
      else if(gr<=0){
          gr=0;
          g=0;
      }
    return ((1-g)*ang1+g*ang2);
}


//**************************************************************************
// Funcion para dibujar vertices
//**************************************************************************

void draw_vertices(vector<_vertex3f> &Vertices)
{
  glColor3f(0,0,0);
  glPointSize(4);
  glBegin(GL_POINTS);
  for (unsigned i=0;i<Vertices.size();i++){
      glVertex3f(Vertices[i].x, Vertices[i].y, Vertices[i].z);
  }
  glEnd();
}

//**************************************************************************
// Funcion para dibujar aristas
//**************************************************************************

void draw_edges(vector<_vertex3f> &Vertices, vector<_vertex2i> &Edges)
{
  glColor3f(0,0,0);
  glBegin(GL_LINES);
  for (unsigned i=0;i<Edges.size();i++){
      glVertex3f(Vertices[Edges[i]._0].x, Vertices[Edges[i]._0].y, Vertices[Edges[i]._0].z);
      glVertex3f(Vertices[Edges[i]._1].x, Vertices[Edges[i]._1].y, Vertices[Edges[i]._1].z);
  }
  glEnd();
}

//**************************************************************************
// Funcion para dibujar caras
//**************************************************************************

void draw_faces(vector<_vertex3f> &Vertices, vector<_vertex3i> &Faces)
{
  glColor3f(0,0,1);
  glBegin(GL_TRIANGLES);
  for (unsigned i=0;i<Faces.size();i++){
      glVertex3f(Vertices[Faces[i]._0].x, Vertices[Faces[i]._0].y, Vertices[Faces[i]._0].z);
      glVertex3f(Vertices[Faces[i]._1].x, Vertices[Faces[i]._1].y, Vertices[Faces[i]._1].z);
      glVertex3f(Vertices[Faces[i]._2].x, Vertices[Faces[i]._2].y, Vertices[Faces[i]._2].z);

  }
  glEnd();
}


//**************************************************************************
// Estructura del modelo
//**************************************************************************



void pecho(){
  //pecho
  glPushMatrix();
    glTranslatef(0,5.5,0.3);
    glScalef(2,2,2);
    glColor3f(1,0.52,0.047);
    cylinder2_form.crea_material(shirt_a,shirt_d,shirt_s,shirt_e);
    cylinder2_form.draw(norm_car,norm_ver,aje);
  glPopMatrix();
}

void cintura_arriba(){
  //cintura2
  glPushMatrix();
    glTranslatef(0,3.5,0.3);
    glRotatef(180,0,1,0);
    glScalef(4,4,4);
    glColor3f(1,0.52,0.047);
    semisphere_form.crea_material(shirt_a,shirt_d,shirt_s,shirt_e);
    semisphere_form.draw(norm_car,norm_ver,aje);
  glPopMatrix();

}

void cintura_abajo(){
  //cintura1
  glPushMatrix();
        glTranslatef(0,3.8,0.3);
        glRotatef(180,0,0,1);
        glScalef(4,3,4);
        glColor3f(0.33,0.67,0.968);
        semisphere_form.crea_material(jeans_a,jeans_d,jeans_s,jeans_e);
        semisphere_form.draw(norm_car,norm_ver,aje);
  glPopMatrix();
}

void hombroi(){
  //hombroi
  glPushMatrix();
      glTranslatef(-1.25,6,0);
      glRotatef(90,0,0,1);
      glColor3f(1,0.52,0.047);
      sphere_form.crea_material(shirt_a,shirt_d,shirt_s,shirt_e);
      sphere_form.draw(norm_car,norm_ver, aje);
  glPopMatrix();
}

void hombrod(){
  //hombrod
  glPushMatrix();
      glTranslatef(1.25,6,0);
      glRotatef(90,0,0,1);
      glColor3f(1,0.52,0.047);
      sphere_form.crea_material(shirt_a,shirt_d,shirt_s,shirt_e);
      sphere_form.draw(norm_car,norm_ver, aje);
  glPopMatrix();
}

void brazoi(){
  //brazoi
  glPushMatrix();
      glTranslatef(-2.25,6,0);
      glRotatef(270,0,0,1);
      glScalef(1,1.5,1);
      glColor3f(1,0.52,0.047);
      cylinder_form.crea_material(shirt_a,shirt_d,shirt_s,shirt_e);
      cylinder_form.draw(norm_car,norm_ver,aje);
  glPopMatrix();
}

void brazod(){
  //brazod
  glPushMatrix();
      glTranslatef(2.25,6,0);
      glRotatef(90,0,0,1);
      glScalef(1,1.5,1);
      glColor3f(1,0.52,0.047);
      cylinder_form.crea_material(shirt_a,shirt_d,shirt_s,shirt_e);
      cylinder_form.draw(norm_car,norm_ver,aje);
  glPopMatrix();
}

void manod(){
  //manod
  glPushMatrix();
    glTranslatef(3,6,0);
    glColor3f(1,0.85,0.05);
    cylinder_form.crea_material(skin_a, skin_d, skin_s, skin_e);
    sphere_form.draw(norm_car,norm_ver, aje);
  glPopMatrix();
}

void manoi(){
  //manoi
  glPushMatrix();
        glTranslatef(-3,6,0);
        glColor3f(1,0.85,0.05);
        cylinder_form.crea_material(skin_a, skin_d, skin_s, skin_e);
        sphere_form.draw(norm_car,norm_ver, aje);
  glPopMatrix();
}

void cuello(){
  //cuello
  glPushMatrix();
      glTranslatef(0,7,0.5);
      glRotatef(15,1,0,0);
      glScalef(1.5,1.25,1.5);
      glColor3f(1,0.85,0.05);
      cylinder_form.crea_material(skin_a, skin_d, skin_s, skin_e);
      cylinder_form.draw(norm_car,norm_ver,aje);
  glPopMatrix();
}

void cabeza(){
  //cabeza
  glPushMatrix();
      glTranslatef(0,9.25,1);
      glRotatef(355,1,0,0);
      glScalef(1.5,1.5,1.5);
      head();
  glPopMatrix();
}

  void pied(){
  //pied
  glPushMatrix();
      glTranslatef(-1.25,0,0.3);
      glScalef(1.5,1.5,2.25);
      glColor3f(0.5,0.2,0.05);
      semisphere_form.crea_material(shoes_a,shoes_d,shoes_s, shoes_e);
      semisphere_form.draw(norm_car,norm_ver,aje);
  glPopMatrix();
  }
  void piei(){
  //piei
  glPushMatrix();
      glTranslatef(1.25,0,0.3);
      glScalef(1.5,1.5,2.25);
      glColor3f(0.5,0.2,0.05);
      semisphere_form.crea_material(shoes_a,shoes_d,shoes_s, shoes_e);
      semisphere_form.draw(norm_car,norm_ver,aje);
  glPopMatrix();
  }

  void piernad(){
  //piernad
  glPushMatrix();
      glTranslatef(-1.25,2,0);
      glScalef(1,3,1);
      glColor3f(0.33,0.67,0.968);
      cylinder3_form.crea_material(jeans_a,jeans_d,jeans_s,jeans_e);
      cylinder3_form.draw(norm_car,norm_ver,aje); //3
  glPopMatrix();
  }
  void piernai(){
  //piernai
  glPushMatrix();
      glTranslatef(1.25,2,0);
      glScalef(1,3,1);
      glColor3f(0.33,0.67,0.968);
      cylinder3_form.crea_material(jeans_a,jeans_d,jeans_s,jeans_e);
      cylinder3_form.draw(norm_car,norm_ver,aje); //3
  glPopMatrix();
  }

  void lata(){
    glPushMatrix();
    glTranslatef(3.75,5,0);
    glScalef(1.5,1.5,1.5);
    glRotatef(180,0,1,0);
    glColor3f(0.5,0.5,0.5);
    latasup.crea_material(iron_a,iron_d,iron_s,iron_e);
    latasup.draw(norm_car,norm_ver, aje);
    latacue1.crea_material(tex_a,tex_d,tex_s,tex_e);
    latacue1.draw(norm_car,norm_ver, aje);
    latainf.crea_material(iron_a,iron_d,iron_s,iron_e);
    latainf.draw(norm_car,norm_ver, aje);
    glPopMatrix();
  }

  void skeleton(){
  float v1,v2,v3;
  v1 = ecRect(gr1,100,0,40);
  v2 = ecRect(gr2,30,0,40);
  v3 = ecRect(gr3,60,0,90);
  glPushMatrix();
    pied();
    piei();
    piernad();
    piernai();
    glTranslatef(0,4.5,0);
    glRotatef(v1,1,0,0); //2º grado de libertad
    glTranslatef(0,-4.5,0);
    glPushMatrix();
        cintura_abajo();
        cintura_arriba();
        pecho();
        glPushMatrix();
            glTranslatef(1.25,6,0);
            glRotatef(360-v2,0,0,1);//3º grado de libertad
            glTranslatef(-1.25,-6,0);
            glPushMatrix();
                hombrod();
                brazod();
                glPushMatrix();
                    glTranslatef(3,6,0);
                    glRotatef(360-v3,0,1,0); //4º grado de libertad
                    glTranslatef(-3,-6,0);
                    glPushMatrix();
                      manod();
                      glPushMatrix();
                      //LATA
                      lata();
                      glPopMatrix();
                    glPopMatrix();
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();
        glPushMatrix();
            glTranslatef(-1.25,6,0);
            glRotatef(v2,0,0,1);
            glTranslatef(1.25,-6,0);
            glPushMatrix();
                hombroi();
                brazoi();
                manoi();
            glPopMatrix();
        glPopMatrix();
        cuello();
        cabeza();
    glPopMatrix();
  glPopMatrix();
  }

void head(){
  //forma
  glPushMatrix();
      glScalef(2,2,2);
      glColor3f(1,0.85,0.05);
      cylinder_form.crea_material(skin_a, skin_d, skin_s, skin_e);
      cylinder3_form.draw(norm_car,norm_ver,aje); //3
  glPopMatrix();

  //ojoi
  glPushMatrix();
      glTranslatef(-0.4,0.1,0.82);
      glRotatef(90,1,0,0);
      glRotatef(15,0,0,1);
      glScalef(0.75,0.75,0.75);
      glColor3f(1,1,1);
      semisphere_form.draw(norm_car,norm_ver,aje);
  glPopMatrix();
  //ojod
  glPushMatrix();
      glTranslatef(0.4,0.1,0.82);
      glRotatef(90,1,0,0);
      glRotatef(345,0,0,1);
      glScalef(0.75,0.75,0.75);
      glColor3f(1,1,1);
      semisphere_form.draw(norm_car,norm_ver,aje);
  glPopMatrix();

  //pupilad
  glPushMatrix();
      glTranslatef(0.4,0.1,1.2);
      glRotatef(90,1,0,0);
      glScalef(0.08,0.08,0.08);
      glColor3f(0,0,0);
      sphere_form.draw(norm_car,norm_ver, aje);
  glPopMatrix();
  //pupilai
  glPushMatrix();
      glTranslatef(-0.4,0.1,1.2);
      glRotatef(90,1,0,0);
      glScalef(0.08,0.08,0.08);
      glColor3f(0,0,0);
      sphere_form.draw(norm_car,norm_ver, aje);
  glPopMatrix();
  //nariz
  glPushMatrix();
      glTranslatef(0,-0.2,1);
      glRotatef(90,1,0,0);
      glScalef(0.25,0.25,0.25);
      glColor3f(1,0.85,0.05);
      cylinder_form.crea_material(skin_a, skin_d, skin_s, skin_e);
      cylinder_form.draw(norm_car,norm_ver,aje);
  glPopMatrix();

  //punta nariz
  glPushMatrix();
      glTranslatef(0,-0.2,1.1);
      glRotatef(90,1,0,0);
      glScalef(0.25,0.25,0.25);
      glColor3f(1,0.85,0.05);
      semisphere_form.crea_material(skin_a, skin_d, skin_s, skin_e);
      semisphere_form.draw(norm_car,norm_ver,aje);
  glPopMatrix();
  //boca1
  glPushMatrix();
      glTranslatef(0,-1,-0.2);
      glRotatef(180,1,0,0);
      glRotated(90,0,1,0);
      glScalef(1.55,0.7,2);
      glColor3f(1,0.85,0.05);
      semisphere_form.crea_material(skin_a, skin_d, skin_s, skin_e);
      semisphere_form.draw(norm_car,norm_ver,aje);
  glPopMatrix();
  //boca2
  glPushMatrix();
      glTranslatef(0,-1.05,0.15);
      glScalef(1.8,0.05,1);
      glColor3f(0,0,0);
      cylinder_form.draw(norm_car,norm_ver,aje);
  glPopMatrix();
  //orejad
  glPushMatrix();
      glTranslatef(1.05,-0.45,-0.2);
      glRotatef(90,0,0,1);
      glRotatef(340,1,0,0);
      glScalef(0.5,0.15,0.5);
      glColor3f(1,0.85,0.05);
      cylinder_form.crea_material(skin_a, skin_d, skin_s, skin_e);
      cylinder_form.draw(norm_car,norm_ver,aje);
  glPopMatrix();
  //orejai
  glPushMatrix();
      glTranslatef(-1.05,-0.45,-0.2);
      glRotatef(90,0,0,1);
      glRotatef(20,1,0,0);
      glScalef(0.5,0.15,0.5);
      glColor3f(1,0.85,0.05);
      cylinder_form.crea_material(skin_a, skin_d, skin_s, skin_e);
      cylinder_form.draw(norm_car,norm_ver,aje);
  glPopMatrix();
  //pelo
  for(unsigned i=0; i<25; i++){
      glPushMatrix();
      glRotatef(i*15,0,1,0);
      hair();
      glPopMatrix();
  }

}

void hair(){
  glPushMatrix();
      glTranslatef(0,1.25,0.94);
      glRotatef(300,0,1,0);
      glScalef(0.25,0.5,0.25);
      glColor3f(1,0.85,0.05);
      tetrahedron_form.crea_material(skin_a, skin_d, skin_s, skin_e);
      tetrahedron_form.draw(norm_car,norm_ver,aje);
  glPopMatrix();
}

void skateboard(){
    glPushMatrix();
    glPushMatrix();
    //base
        glScalef(4,0.15,2);
        glColor3f(0,0.4,0);
        cube_form.draw(norm_car,norm_ver,aje);
    glPopMatrix();
    //lateral1
    glPushMatrix();
        glTranslatef(-2,0,0);
        glRotatef(90,0,1,0);
        glScalef(2,0.15,2);
        glColor3f(0,0.4,0);
        semicylinder_form.draw(norm_car,norm_ver,aje);
    glPopMatrix();
    //lateral2
    glPushMatrix();
        glTranslatef(2,0,0);
        glRotatef(270,0,1,0);
        glScalef(2,0.15,2);
        glColor3f(0,0.4,0);
        semicylinder_form.draw(norm_car,norm_ver,aje);
    glPopMatrix();
  //rueda1
    glPushMatrix();
        glRotatef(90,1,0,0);
        glTranslatef(-1.5,0.75,0.30);
        glRotatef(360-desp*15,0,1,0);
        glScalef(0.5,0.125,0.5);
        glColor3f(0,0,0.5);
        cylinder_form.draw(norm_car,norm_ver,aje);
    glPopMatrix();
    //rueda2
    glPushMatrix();
        glRotatef(90,1,0,0);
        glTranslatef(-1.5,-0.75,0.30);
        glRotatef(360-desp*15,0,1,0);
        glScalef(0.5,0.125,0.5);
        glColor3f(0,0,0.5);
        cylinder_form.draw(norm_car,norm_ver,aje);
    glPopMatrix();
    //rueda3
    glPushMatrix();
        glRotatef(90,1,0,0);
        glTranslatef(1.5,0.75,0.30);
        glRotatef(360-desp*15,0,1,0);
        glScalef(0.5,0.125,0.5);
        glColor3f(0,0,0.5);
        cylinder_form.draw(norm_car,norm_ver,aje);
    glPopMatrix();
    //rueda4
    glPushMatrix();
        glRotatef(90,1,0,0);
        glTranslatef(1.5,-0.75,0.30);
        glRotatef(360-desp*15,0,1,0);
        glScalef(0.5,0.125,0.5);
        glColor3f(0,0,0.5);
        cylinder_form.draw(norm_car,norm_ver,aje);
    glPopMatrix();
    //beethoven
    glPushMatrix();
    glTranslatef(2.25,1.25,0);
    glRotatef(90,0,1,0);
    glScalef(0.2,0.2,0.2);
    glColor3f(0.6,0.6,0.6);
    //ply_beethoven.draw(norm_car, norm_ver,aje);
    view_objects_1();
    glPopMatrix();
  glPopMatrix();
}


void skater(){
    glPushMatrix();
        glTranslatef(0,4.5,0);
        glTranslatef(0,-4.5,0);
        glPushMatrix();
            //skateboard
                glPushMatrix();
                glTranslatef(0,0,0);
                glScalef(1.5,1.5,1.5);
                skateboard();
            glPopMatrix();
            //muñeco
            glPushMatrix();
                glTranslatef(0,0.17,-0.5);
                skeleton();
        glPopMatrix();
    glPopMatrix();
}


void animar(){
    if(aumento){
      if(aum>0 && aum<movimiento-1){
        desp+=0.3;
        gr1++;
        gr2++;
        gr3++;
        aum++;
      }
      else if(aum==movimiento-1){
          aumento=false;
        }
    }
    else
      {
        if(aum>0 && aum<=movimiento){
          desp-=0.3;
          gr1--;
          gr2--;
          gr3--;
          aum--;
        }
        else if(aum==0){
            aumento=true;
            aum+=1;
          }
      }
}

void grados_libertad(int gral){
  switch(gral){
  case 0:
      desp+=0.25;
    break;
  case 1:
      desp-=0.25;
    break;
  case 2:
      gr1+=1;
    break;
  case 3:
      gr1-=1;
    break;
  case 4:
      gr2+=1;
    break;
  case 5:
      gr2-=1;
      break;
  case 6:
      gr3+=1;
    break;
  case 7:
      gr3-=1;
      break;
  }
}


  void crea_luz_fija(GLfloat PosTipo[], GLfloat luz_a[], GLfloat luz_d[], GLfloat luz_s[]){
  glLightfv(GL_LIGHT1,GL_POSITION, PosTipo);
  glLightfv(GL_LIGHT1,GL_AMBIENT,luz_a);
  glLightfv(GL_LIGHT1,GL_DIFFUSE,luz_d);
  glLightfv(GL_LIGHT1,GL_SPECULAR,luz_s);
  }
  void crea_luz_dinamica(GLfloat PosTipo[], GLfloat luz_a[], GLfloat luz_d[], GLfloat luz_s[],float alpha, float beta){
    glPushMatrix() ;
    //rotación alpha grados en torno al eje Y
    glRotatef( alpha, 0.0, 1.0, 0.0 ) ;
    //rotación beta grados en torno al eje X
    glRotatef( beta, 1.0, 0.0, 0.0 ) ;
    //hacer l_i : = ( 0, 0, 1 ) (paralela eje Z+)
    glLightfv(GL_LIGHT0,GL_POSITION, PosTipo);
    glPopMatrix() ;
    glLightfv(GL_LIGHT1,GL_POSITION, PosTipo);
    glLightfv(GL_LIGHT1,GL_AMBIENT,luz_a);
    glLightfv(GL_LIGHT1,GL_DIFFUSE,luz_d);
    glLightfv(GL_LIGHT1,GL_SPECULAR,luz_s);
  }

  void view_objects_1(){
    GLfloat mat_a[]={0.0,0.0,0.0,1.0}, mat_d[]={0.2,0.2,0.2,1.0}, mat_s[]={1.0,1.0,1.0,1.0}, e=100.0;
    glColor3f(0.25,0.25,0.25);
    ply_beethoven.crea_material(mat_a,mat_d,mat_s,e);
    ply_beethoven.draw(norm_car,norm_ver, aje);

  }

  void view_objects_2(){
    GLfloat mat_a[]={0.0,0.0,0.0,1.0}, mat_d[]={0.2,0.2,0.2,1.0}, mat_s[]={1.0,1.0,1.0,1.0}, e=100.0;
    glColor3f(0.25,0.25,0.25);
    generic.crea_material(mat_a,mat_d,mat_s,e);
    generic.draw(norm_car,norm_ver,aje);
  }

  void view_objects_3(){
      glPushMatrix();
          //skater
          glPushMatrix();
              glTranslatef(desp,0,0); //1º grado de libertad
              skater();
          glPopMatrix();
      glPopMatrix();
  }

  void view_objects_4()
  {

    GLfloat Luz0[4]={1,1,1,0};
    GLfloat Ambiente[4]={1,1,1,1};
    GLfloat Blanco[4]={1,1,1,1};
    GLfloat Color[4]={0.6,0.6,0.6,0.6};
    GLfloat Color1[4]={0.4,0.4,0.4,1};

    //peon1
    glPushMatrix();
    glTranslatef(-2,0,-2);
    glColor3f(0.6,0.6,0.6);
    peon.crea_material(mat1_a,mat1_d,mat1_s,e1);
    peon.draw(norm_car,norm_ver,aje);
    glPopMatrix();



    //peon2
    glPushMatrix();
    glTranslatef(0,0,-1);
    glColor3f(0.15,0.15,0.15);
    peon.crea_material(mat2_a,mat2_d,mat2_s,e2);
    peon.draw(norm_car,norm_ver,aje);
    glPopMatrix();



    //peon3
    glPushMatrix();
    glTranslatef(2,0,0);
    glColor3f(1,0,0);
    peon_text.crea_material(tex_a,tex_d,tex_s,tex_e);
    peon_text.draw_without_cover(norm_car,norm_ver,aje);
    glPopMatrix();


    //lata_sup
    glPushMatrix();
    glTranslatef(0,0,-3);
    glScalef(5,5,5);
    glColor3f(0.75,0.75,0.75);
    latasup.crea_material(mat1_a,mat1_d,mat1_s,e1);
    latasup.draw(norm_car,norm_ver,aje);
    glPopMatrix();

    //lata_cue
    glPushMatrix();
    glTranslatef(0,0,-3);
    glScalef(5,5,5);
    latacue2.crea_material(tex_a,tex_d,tex_s,tex_e);
    latacue2.draw(norm_car,norm_ver,aje);
    glPopMatrix();



    //lata_inf
    glPushMatrix();
    glTranslatef(0,0,-3);
    glScalef(5,5,5);
    glColor3f(0.75,0.75,0.75);
    latainf.crea_material(mat1_a,mat1_d,mat1_s,e1);
    latainf.draw(norm_car,norm_ver,aje);
    glPopMatrix();
  }







//**************************************************************************
// Funcion para dibujar archivos PLY
//**************************************************************************

void draw_file(int valor, bool color, bool ajedrez, bool normal, int gl,bool idle, bool noc, bool nov, _vertex2f angles){
  if(inicio){
     menu();
     inicio=false;
     load_objects();
    }
    val=valor;
    aje=ajedrez;
    norm_car=noc;
    norm_ver=nov;
    gral=gl;
    id=idle;
    GLfloat Blanco[4]={1,1,1,1};
    GLfloat Color[4]={0.6,0.6,0.6,0.6};
    GLfloat Color1[4]={0.4,0.4,0.4,1};
    GLfloat direccion_luz[]={-4.0,3.0,-2.0,0.0}, posicion_luz[]={0.0,3.0,9.0,0.0};
    crea_luz_dinamica(posicion_luz, Color1, Color, Blanco, angles.x, angles.y); //luz dinamica
    crea_luz_fija(direccion_luz, Color1, Color, Blanco); //luz fija

    glPushMatrix();
    glColor3f(0.5,0.5,1);
    glRotatef(angles.x,0,1,0);
    glRotatef(angles.y,1,0,0);
    glTranslatef(posicion_luz[0],posicion_luz[1],posicion_luz[2]);
    glScalef(3,3,3);
    sphere_form.draw();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.5,0.5,1);
    glTranslatef(direccion_luz[0],direccion_luz[1],direccion_luz[2]);
    glScalef(1,1,1);
    sphere_form.draw();
    glPopMatrix();

    glColorMaterial(GL_FRONT, GL_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glMatrixMode(GL_MODELVIEW);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    switch (val) {
    case 0:
      view_objects_1();

    break;

    case 1:
      view_objects_2();
        break;
    case 2:
      if(!idle){
          grados_libertad(gral);
          view_objects_3();
          gral=-1;

      }
      else
      {
        animar();
        view_objects_3();
        gral=-1;
      }
    break;
    case 3:
          view_objects_4();
    break;

    }
}


