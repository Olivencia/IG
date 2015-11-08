#include <GL/gl.h>
#include <vector>
#include "vertex.h"
#include "file_ply_stl.h"
#include <iostream>
#include "jpg_imagen.hpp"


using namespace std;

class Object
{
private:

  vector<_vertex3f> Vertices, normal_caras, normal_vertices, bariv;
  vector<_vertex3i> Faces;
  vector<_vertex2f> ctex;
  vector<int> fa;
  vector<float> ve;
  _file_ply ply;
  unsigned tamx, tamy;
  unsigned char * texels;
  int rep,val;
  float vy1=0, vy2=0, ang1 = 0.0 ,ang2 = 360.0;
  bool arriba, abajo;
  int type=10;

public:

  void mostrar_caras(){
    for(unsigned i=0; i<Faces.size(); i++)
        cout << "POSICION " << i << " " << Faces[i]._0 << " " << Faces[i]._1 << " " << Faces[i]._2 << endl;

  }

void mostrar_vertices(){
    for(unsigned i=0; i<Vertices.size(); i++)
        cout << "POSICION " << i << " "  << Vertices[i].x << " " << Vertices[i].y << " " << Vertices[i].z << endl;

  }

int load(char * file = NULL, jpg::Imagen * pimg = NULL, int rev = 20)
{
  ply.open(file);
  ply.read(ve, fa);
  ply.close();
  rep=rev;
  adjust();
  invertirf();
  update_points();
  covers();
  update_faces();
  normal_faces();
  normal_points();
  if(pimg==NULL)
    ctex.resize(Vertices.size());
  else
  {
    apply_img(pimg);
    adjust_texture();
  }
}



int load_form(int type = 0, int rev = 20,  jpg::Imagen * pimg = NULL)
{
  this->type=type;
  rep=rev;
  choose_form(type);
  if(type != 0 && type !=7){
    update_points();
    covers();
    update_faces();
    }

  normal_faces();
  normal_points();
  if(pimg==NULL)
    ctex.resize(Vertices.size());
  else
  {
    apply_img(pimg);
    adjust_texture();
  }
}



int load_ply(char * file){
  ply.open(file);
  ply.read(ve, fa);
  ply.close();
  adjust();
  change_faces();
  normal_faces();
  normal_points();
  ctex.resize(Vertices.size());
}


void cilindro(){
  GLfloat v[4][3]= {{0.0,0.5,0.0},{0.5, 0.5, 0},{0.5, -0.5, 0},{0.0,-0.5,0.0}};
    Vertices.resize(4);
    for(int i=0; i<4;i++){
      Vertices[i].x=v[i][0];
      Vertices[i].y=v[i][1];
      Vertices[i].z=v[i][2];
    }
}

void cilindro2(){
  GLfloat v[4][3]= {{0.0,0.5,0.0},{0.5, 0.5, 0},{0.75, -0.5, 0},{0.0,-0.5,0.0}};
    Vertices.resize(4);
    for(int i=0; i<4;i++){
      Vertices[i].x=v[i][0];
      Vertices[i].y=v[i][1];
      Vertices[i].z=v[i][2];
    }
}

void cilindro3(){
  GLfloat v[6][3]= {{0.0,0.5,0.0},{0.5,0.5,0.0},{0.5, 0.25, 0},{0.5,-0.25,0.0},{0.5, -0.5, 0},{0.0,-0.5,0.0}};
    Vertices.resize(6);
    for(int i=0; i<6;i++){
      Vertices[i].x=v[i][0];
      Vertices[i].y=v[i][1];
      Vertices[i].z=v[i][2];
  }
}

void semicilindro(){
  ang2=180;
  GLfloat v[4][3]= {{0.0,0.5,0.0},{0.5, 0.5, 0},{0.5, -0.5, 0},{0.0,-0.5,0.0}};
    Vertices.resize(4);
    for(int i=0; i<4;i++){
      Vertices[i].x=v[i][0];
      Vertices[i].y=v[i][1];
      Vertices[i].z=v[i][2];
    }
}

void cubo(){
  GLfloat v[8][3]= {{-0.5,-0.5,0.5},{0.5,-0.5,0.5},{0.5,0.5,0.5},{-0.5,0.5,0.5},{-0.5,-0.5,-0.5},{0.5,-0.5,-0.5},{0.5,0.5,-0.5},{-0.5,0.5,-0.5}};
  GLint f[12][3] = {{0,2,1},{0,1,4},{0,3,2},{0,7,3},{0,4,7},{1,2,5},{4,1,5},{2,6,5},{2,3,7},{2,7,6},{4,5,6},{4,6,7}};
    Vertices.resize(8);
    Faces.resize(12);
    for(int i=0; i<12;i++){
      if(i<8){
        Vertices[i].x=v[i][0];
        Vertices[i].y=v[i][1];
        Vertices[i].z=v[i][2];

      }
      Faces[i]._0=f[i][0];
      Faces[i]._1=f[i][1];
      Faces[i]._2=f[i][2];
    }

}

void tetraedro()
{
   GLfloat v[4][3]= {{-0.5,-0.5,-0.5},{0.0,0.5,0.0},{0.5,-0.5,-0.5},{0.0,-0.5,0.5}};
   GLint f[4][3] = {{0,2,1},{0,1,3},{0,3,2},{1,2,3}};
   Vertices.resize(4);
   Faces.resize(4);
   for(int i=0; i<6;i++){
        if(i<4){
           Vertices[i].x=v[i][0];
           Vertices[i].y=v[i][1];
           Vertices[i].z=v[i][2];
           Faces[i]._0=f[i][0];
           Faces[i]._1=f[i][1];
           Faces[i]._2=f[i][2];
        }
     }
}


void esfera(){
  GLfloat punt[1][3]= {{0.0,0.5,0.0}};
  Vertices.resize(rep);
  float pi=3.1415926535;
  float ang, t, r=rep,cy,sy,x,y,z;
    for(int j=0; j<rep ; j++){
      t=(j)/(r-1);
      ang = ((1-t)*0+t*180)*pi/180;
      sy=sin((ang));
      cy=cos((ang));
      x=punt[0][0];
      y=punt[0][1];
      z=punt[0][2];
      Vertices[j].x = x;
      Vertices[j].y = y*cy-z*sy;
      Vertices[j].z = y*sy+z*cy;
    }
}

void semiesfera(){
  ang2=90;
  GLfloat punt[1][3]= {{0.0,0.5,0.0}};
  Vertices.resize(rep);
  float pi=3.1415926535;
  float ang, t, r=rep,cy,sy,x,y,z;
    for(int j=0; j<rep ; j++){
      t=(j)/(r-1);
      ang = ((1-t)*ang1+t*ang2)*pi/180;
      sy=sin((ang));
      cy=cos((ang));
      x=punt[0][0];
      y=punt[0][1];
      z=punt[0][2];
      Vertices[j].x = x;
      Vertices[j].y = y*cy-z*sy;
      Vertices[j].z = y*sy+z*cy;
    }
    ang2=360;
}





void choose_form(int type){
  switch (type){
    case 0:
      cubo();
    break;
    case 1:
      esfera();
    break;
    case 2:
      semiesfera();
    break;
    case 3:
      cilindro();
    break;
    case 4:
      cilindro2();
    break;
    case 5:
      cilindro3();
    break;
    case 6:
      semicilindro();
    break;
    case 7:
      tetraedro();
    break;
    }
}


void adjust(){
  if(Vertices.size() != 0 || Faces.size() != 0){
      Vertices.clear();
      Faces.clear();
    }
  Vertices.resize(ve.size()/3);
  Faces.resize(fa.size()/3);

  int j;
  for(unsigned i=0; i<ve.size(); i+=3){
    j=i/3;
    Vertices[j].x=ve[i];
    Vertices[j].y=ve[i+1];
    Vertices[j].z=ve[i+2];
    }
  for(unsigned i=0; i<fa.size(); i+=3){
    j=i/3;
    Faces[j]._0=fa[i];
    Faces[j]._2=fa[i+1];
    Faces[j]._1=fa[i+2];
    }
}

void invertirf(){
  vector<_vertex3f> aux;
  unsigned tam = Vertices.size();
  aux.resize(tam);
  for(unsigned i=0; i<tam; i++){
    aux[i].x=Vertices[tam-i-1].x;
    aux[i].y=Vertices[tam-i-1].y;
    aux[i].z=Vertices[tam-i-1].z;
  }
  Vertices=aux;
}

void invertiri(){
  vector<_vertex3i> aux;
  unsigned tam = Faces.size();
  aux.resize(tam);
  for(unsigned i=0; i<tam; i++){
      aux[i].x=Faces[tam-i-1]._0;
      aux[i].y=Faces[tam-i-1]._1;
      aux[i].z=Faces[tam-i-1]._2;
    }
  Faces=aux;
}

void change_faces(){
  unsigned j;
  for(unsigned i=0; i<fa.size(); i+=3){
    j=i/3;
    Faces[j]._0=fa[i];
    Faces[j]._2=fa[i+1];
    Faces[j]._1=fa[i+2];
    }
}


void update_points(){
  arriba=false;
  abajo=false;
  float x,y,z,ang,sy,cy;
  vector<_vertex3f> punt;
  punt.resize(Vertices.size());
  if(Vertices[0].x==0){
      arriba=true;
      punt.resize(punt.size()-1);
      vy1=Vertices[0].y;
  }
  if(Vertices[Vertices.size()-1].x==0){
      abajo=true;
      punt.resize(punt.size()-1);
      vy2=Vertices[Vertices.size()-1].y;
  }
  int cnt=0;
  if(arriba &&  abajo) {
      for(unsigned i=1; i<Vertices.size()-1; i++){
          punt[cnt].x = Vertices[i].x;
          punt[cnt].y = Vertices[i].y;
          punt[cnt].z = Vertices[i].z;
          cnt++;
      }
  }
  else if(arriba && !abajo){
      for(unsigned i=1; i<Vertices.size(); i++){
          punt[cnt].x = Vertices[i].x;
          punt[cnt].y = Vertices[i].y;
          punt[cnt].z = Vertices[i].z;
          cnt++;
      }
  }
  else if(!arriba && abajo){
      for(unsigned i=0; i<Vertices.size()-1; i++){
          punt[cnt].x = Vertices[i].x;
          punt[cnt].y = Vertices[i].y;
          punt[cnt].z = Vertices[i].z;
          cnt++;
      }
  }
  else if(!arriba && !abajo){
      for(unsigned i=0; i<Vertices.size(); i++){
          punt[i].x = Vertices[i].x;
          punt[i].y = Vertices[i].y;
          punt[i].z = Vertices[i].z;
      }
  }
int tam=punt.size();
Vertices.resize(tam*rep);
float pi=3.1415926535;
float t, r=rep;
for(int i=0; i<tam; i++){
    for(int j=0; j<rep ; j++){
        t=(j)/(r-1);
        ang = ((1-t)*ang1+t*ang2)*pi/180;
        sy=sin((ang));
        cy=cos((ang));
        x=punt[i].x;
        y=punt[i].y;
        z=punt[i].z;
        Vertices[i+j*tam].x = (x * cy) + (z * sy);
        Vertices[i+j*tam].y = y;
        Vertices[i+j*tam].z = (z * cy) - (x * sy);

    }
  }
}

void covers(){
  if(vy1!=0)
    arriba = true;
  else
    arriba = false;
  if(vy2!=0)
    abajo = true;
  else
    abajo = false;
}

void update_faces(){
  int tam=Vertices.size(), last_tam=tam/rep;
  Faces.clear();
  vector<_vertex3i> f;
  f.resize(Vertices.size()*2);
  Faces.resize(Vertices.size()*2);
  for(int j=0; j<rep; j++){
      for(int i=0; i<last_tam-1; i++){
          if(j==0){
          f[i+j*last_tam]._0=(i+1+(rep-1)*last_tam)%tam;
          f[i+j*last_tam]._1=(i+1+j*last_tam)%tam;
          f[i+j*last_tam]._2=(i+j*last_tam)%tam;

          }
          else{
              f[i+j*last_tam]._0=(i+1+j*last_tam-last_tam)%tam;
              f[i+j*last_tam]._1=(i+j*last_tam)%tam;
              f[i+j*last_tam]._2=(i+1+j*last_tam)%tam;
          }
  }

      for(int i=0; i<last_tam-1; i++){
          if(j==0){
          f[i+j*last_tam+tam]._0=(i+1+(rep-1)*last_tam)%tam;
          f[i+j*last_tam+tam]._1=(i+j*last_tam)%tam;
          f[i+j*last_tam+tam]._2=(i+(rep-1)*last_tam)%tam;
          }
          else{
              f[i+j*last_tam+tam]._0=(i+1+j*last_tam-last_tam)%tam;
              f[i+j*last_tam+tam]._1=(i+j*last_tam-last_tam)%tam;
              f[i+j*last_tam+tam]._2=(i+j*last_tam)%tam;
          }
  }

}
  int cnt=0;
  for(unsigned i=0; i<Faces.size()/2; i++){
          Faces[cnt]._0=f[i]._0;
          Faces[cnt]._1=f[i]._1;
          Faces[cnt]._2=f[i]._2;
          cnt+=2;
  }
  cnt=1;
  for(unsigned i=Faces.size()/2; i<Faces.size(); i++){
          Faces[cnt]._0=f[i]._0;
          Faces[cnt]._1=f[i]._1;
          Faces[cnt]._2=f[i]._2;
          cnt+=2;
  }

  int t = Faces.size();
  if(arriba){
      Vertices.resize(Vertices.size()+1);
      Faces.resize(Faces.size()+rep);
      Vertices[tam].x=0;
      Vertices[tam].y=vy1;
      Vertices[tam].z=0;
      for(int i=0; i<rep-1; i++){
          Faces[t+i]._0=tam;
          Faces[t+i]._2=last_tam*i;
          if(i==rep-1)
              Faces[t+i]._1=0;
          else
              Faces[t+i]._1=last_tam*(i+1);
      }
  }
  if(abajo){
    Vertices.resize(Vertices.size()+1);
    Faces.resize(Faces.size()+rep);
    Vertices[tam+1].x=0;
    Vertices[tam+1].y=vy2;
    Vertices[tam+1].z=0;

    for(int i=0; i<rep-1; i++){
       Faces[t+rep+i]._0=tam+1;
       Faces[t+rep+i]._1=last_tam*(i+1)-1;
       if(i==rep-1)
           Faces[t+rep+i]._2=last_tam-1;
       else
           Faces[t+rep+i]._2=last_tam*(i+2)-1;
   }
  }
}

void normal_faces(){
  int v0,v1,v2, tam=Faces.size();
  normal_caras.resize(tam);
  _vertex3f a,b;
  bariv.resize(tam);
  for(unsigned i=0; i<Faces.size(); i++){
      v0 = Faces[i]._0;
      v1 = Faces[i]._1;
      v2 = Faces[i]._2;

      bariv[i].x=(Vertices[v0].x+Vertices[v1].x+Vertices[v2].x)/3;
      bariv[i].y=(Vertices[v0].y+Vertices[v1].y+Vertices[v2].y)/3;
      bariv[i].z=(Vertices[v0].z+Vertices[v1].z+Vertices[v2].z)/3;

      a= Vertices[v2]-Vertices[v0];
      b= Vertices[v1]-Vertices[v0];


      normal_caras[i]=a.cross_product(b);
      normal_caras[i].normalize();
  }
}


void normal_points(){
  unsigned v0,v1,v2,cnt;
 int tam=Vertices.size();
 normal_vertices.resize(tam);

 for(unsigned i=0; i<Vertices.size();i++){
     cnt=0;
     normal_vertices[i].x=0;
     normal_vertices[i].y=0;
     normal_vertices[i].z=0;

     for(unsigned j=0; j<Faces.size() && cnt < 6; j++){
         v0 = Faces[j]._0;
         v1 = Faces[j]._1;
         v2 = Faces[j]._2;
         if(is_here(v0,v1,v2,i)){
             normal_vertices[i].x+=normal_caras[j].x;
             normal_vertices[i].y+=normal_caras[j].y;
             normal_vertices[i].z+=normal_caras[j].z;
             cnt++;
         }
     }
     normal_vertices[i].x/=cnt;
     normal_vertices[i].y/=cnt;
     normal_vertices[i].z/=cnt;

     normal_vertices[i].normalize();
 }
}

bool is_here(int v0, int v1, int v2, int val){
  bool found=false;
  if ((v0 == val || v1 == val || v2 == val) && !(v0==0 && v1==0 && v2==0)){
      found=true;

    }
  return found;
}

void draw(bool norm_car = false, bool norm_ver = false, bool ajedrez = false){
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
  glTexImage2D(GL_TEXTURE_2D,0,3,tamx,tamy,0,GL_RGB,GL_UNSIGNED_BYTE, texels);
  glPointSize(2);
  unsigned text = ctex.size();
  if(!ajedrez){
    if(norm_car){
        if(text>0){
          glBegin(GL_TRIANGLES);
          unsigned j=0;
          for (unsigned i=0;i<Faces.size();i++){
            glNormal3f(normal_caras[i].x, normal_caras[i].y, normal_caras[i].z);
            glTexCoord2f(ctex[Faces[i]._0].x,ctex[Faces[i]._0].y);
            glVertex3f(Vertices[Faces[i]._0].x, Vertices[Faces[i]._0].y, Vertices[Faces[i]._0].z);
            glTexCoord2f(ctex[Faces[i]._1].x,ctex[Faces[i]._1].y);
            glVertex3f(Vertices[Faces[i]._1].x, Vertices[Faces[i]._1].y, Vertices[Faces[i]._1].z);
            glTexCoord2f(ctex[Faces[i]._2].x,ctex[Faces[i]._2].y);
            glVertex3f(Vertices[Faces[i]._2].x, Vertices[Faces[i]._2].y, Vertices[Faces[i]._2].z);
          }
        glEnd();
        }
        else
          {
            glBegin(GL_TRIANGLES);
            for (unsigned i=0;i<Faces.size();i++){
              glNormal3f(normal_caras[i].x, normal_caras[i].y, normal_caras[i].z);
              glVertex3f(Vertices[Faces[i]._0].x, Vertices[Faces[i]._0].y, Vertices[Faces[i]._0].z);
              glVertex3f(Vertices[Faces[i]._1].x, Vertices[Faces[i]._1].y, Vertices[Faces[i]._1].z);
              glVertex3f(Vertices[Faces[i]._2].x, Vertices[Faces[i]._2].y, Vertices[Faces[i]._2].z);
            }
            glEnd();
          }
      }
    else{
      if(norm_ver){
          if(text>0){
            glBegin(GL_TRIANGLES);
            for (unsigned i=0;i<Faces.size();i++){
              glNormal3f(normal_vertices[Faces[i]._0].x, normal_vertices[Faces[i]._0].y, normal_vertices[Faces[i]._0].z);
              glTexCoord2f(ctex[Faces[i]._0].x,ctex[Faces[i]._0].y);
              glVertex3f(Vertices[Faces[i]._0].x, Vertices[Faces[i]._0].y, Vertices[Faces[i]._0].z);
              glNormal3f(normal_vertices[Faces[i]._1].x, normal_vertices[Faces[i]._1].y, normal_vertices[Faces[i]._1].z);
              glTexCoord2f(ctex[Faces[i]._1].x,ctex[Faces[i]._1].y);
              glVertex3f(Vertices[Faces[i]._1].x, Vertices[Faces[i]._1].y, Vertices[Faces[i]._1].z);
              glNormal3f(normal_vertices[Faces[i]._2].x, normal_vertices[Faces[i]._2].y, normal_vertices[Faces[i]._2].z);
              glTexCoord2f(ctex[Faces[i]._2].x,ctex[Faces[i]._2].y);
              glVertex3f(Vertices[Faces[i]._2].x, Vertices[Faces[i]._2].y, Vertices[Faces[i]._2].z);
            }
            glEnd();
          }
          else
            {
              glBegin(GL_TRIANGLES);
              for (unsigned i=0;i<Faces.size();i++){
                glNormal3f(normal_vertices[Faces[i]._0].x, normal_vertices[Faces[i]._0].y, normal_vertices[Faces[i]._0].z);
                glVertex3f(Vertices[Faces[i]._0].x, Vertices[Faces[i]._0].y, Vertices[Faces[i]._0].z);
                glNormal3f(normal_vertices[Faces[i]._1].x, normal_vertices[Faces[i]._1].y, normal_vertices[Faces[i]._1].z);
                glVertex3f(Vertices[Faces[i]._1].x, Vertices[Faces[i]._1].y, Vertices[Faces[i]._1].z);
                glNormal3f(normal_vertices[Faces[i]._2].x, normal_vertices[Faces[i]._2].y, normal_vertices[Faces[i]._2].z);
                glVertex3f(Vertices[Faces[i]._2].x, Vertices[Faces[i]._2].y, Vertices[Faces[i]._2].z);
              }
              glEnd();
            }
        }
        else{
            if(text>0){
              glBegin(GL_TRIANGLES);
              for (unsigned i=0;i<Faces.size();i++){
                    glTexCoord2f(ctex[Faces[i]._0].x,ctex[Faces[i]._0].y);
                    glVertex3f(Vertices[Faces[i]._0].x, Vertices[Faces[i]._0].y, Vertices[Faces[i]._0].z);
                    glTexCoord2f(ctex[Faces[i]._1].x,ctex[Faces[i]._1].y);
                    glVertex3f(Vertices[Faces[i]._1].x, Vertices[Faces[i]._1].y, Vertices[Faces[i]._1].z);
                    glTexCoord2f(ctex[Faces[i]._2].x,ctex[Faces[i]._2].y);
                    glVertex3f(Vertices[Faces[i]._2].x, Vertices[Faces[i]._2].y, Vertices[Faces[i]._2].z);
              }
            glEnd();
            }
            else
            {
              glBegin(GL_TRIANGLES);
              for (unsigned i=0;i<Faces.size();i++){
                glNormal3f(normal_caras[i].x, normal_caras[i].y, normal_caras[i].z);
                glVertex3f(Vertices[Faces[i]._0].x, Vertices[Faces[i]._0].y, Vertices[Faces[i]._0].z);
                glVertex3f(Vertices[Faces[i]._1].x, Vertices[Faces[i]._1].y, Vertices[Faces[i]._1].z);
                glVertex3f(Vertices[Faces[i]._2].x, Vertices[Faces[i]._2].y, Vertices[Faces[i]._2].z);
              }
            glEnd();
          }
        }
      }
    }
  else
    {
      glBegin(GL_TRIANGLES);
      for (unsigned i=0;i<Faces.size();i++){
          if(i%2==0)
            glColor3f(0,1,1);
          else
            glColor3f(1,1,0);
          glVertex3f(Vertices[Faces[i]._0].x, Vertices[Faces[i]._0].y, Vertices[Faces[i]._0].z);
          glVertex3f(Vertices[Faces[i]._1].x, Vertices[Faces[i]._1].y, Vertices[Faces[i]._1].z);
          glVertex3f(Vertices[Faces[i]._2].x, Vertices[Faces[i]._2].y, Vertices[Faces[i]._2].z);
      }
    glEnd();
    }
}

/******************************************/

void draw_without_cover(bool norm_car = false, bool norm_ver = false, bool ajedrez = false){
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
  glTexImage2D(GL_TEXTURE_2D,0,3,tamx,tamy,0,GL_RGB,GL_UNSIGNED_BYTE, texels);
  glPointSize(2);
  unsigned f = Faces.size()-rep, text=ctex.size();
  if(!ajedrez){
    if(norm_car){
        if(text>0){
          glBegin(GL_TRIANGLES);
          unsigned j=0;
          for (unsigned i=0;i<Faces.size();i++){
              if(i<f){
                glNormal3f(normal_caras[i].x, normal_caras[i].y, normal_caras[i].z);
                glTexCoord2f(ctex[Faces[i]._0].x,ctex[Faces[i]._0].y);
                glVertex3f(Vertices[Faces[i]._0].x, Vertices[Faces[i]._0].y, Vertices[Faces[i]._0].z);
                glTexCoord2f(ctex[Faces[i]._1].x,ctex[Faces[i]._1].y);
                glVertex3f(Vertices[Faces[i]._1].x, Vertices[Faces[i]._1].y, Vertices[Faces[i]._1].z);
                glTexCoord2f(ctex[Faces[i]._2].x,ctex[Faces[i]._2].y);
                glVertex3f(Vertices[Faces[i]._2].x, Vertices[Faces[i]._2].y, Vertices[Faces[i]._2].z);
              }
              else
              {
                  glNormal3f(normal_caras[i].x, normal_caras[i].y, normal_caras[i].z);
                  glVertex3f(Vertices[Faces[i]._0].x, Vertices[Faces[i]._0].y, Vertices[Faces[i]._0].z);
                  glVertex3f(Vertices[Faces[i]._1].x, Vertices[Faces[i]._1].y, Vertices[Faces[i]._1].z);
                  glVertex3f(Vertices[Faces[i]._2].x, Vertices[Faces[i]._2].y, Vertices[Faces[i]._2].z);
              }
          }
        glEnd();
        }
        else
          {
            glBegin(GL_TRIANGLES);
            for (unsigned i=0;i<Faces.size();i++){
              glNormal3f(normal_caras[i].x, normal_caras[i].y, normal_caras[i].z);
              glVertex3f(Vertices[Faces[i]._0].x, Vertices[Faces[i]._0].y, Vertices[Faces[i]._0].z);
              glVertex3f(Vertices[Faces[i]._1].x, Vertices[Faces[i]._1].y, Vertices[Faces[i]._1].z);
              glVertex3f(Vertices[Faces[i]._2].x, Vertices[Faces[i]._2].y, Vertices[Faces[i]._2].z);
            }
            glEnd();
          }
      }
    else{
      if(norm_ver){
          if(text>0){
            glBegin(GL_TRIANGLES);
            for (unsigned i=0;i<Faces.size();i++){
                if(i<f){
                  glNormal3f(normal_vertices[Faces[i]._0].x, normal_vertices[Faces[i]._0].y, normal_vertices[Faces[i]._0].z);
                  glTexCoord2f(ctex[Faces[i]._0].x,ctex[Faces[i]._0].y);
                  glVertex3f(Vertices[Faces[i]._0].x, Vertices[Faces[i]._0].y, Vertices[Faces[i]._0].z);
                  glNormal3f(normal_vertices[Faces[i]._1].x, normal_vertices[Faces[i]._1].y, normal_vertices[Faces[i]._1].z);
                  glTexCoord2f(ctex[Faces[i]._1].x,ctex[Faces[i]._1].y);
                  glVertex3f(Vertices[Faces[i]._1].x, Vertices[Faces[i]._1].y, Vertices[Faces[i]._1].z);
                  glNormal3f(normal_vertices[Faces[i]._2].x, normal_vertices[Faces[i]._2].y, normal_vertices[Faces[i]._2].z);
                  glTexCoord2f(ctex[Faces[i]._2].x,ctex[Faces[i]._2].y);
                  glVertex3f(Vertices[Faces[i]._2].x, Vertices[Faces[i]._2].y, Vertices[Faces[i]._2].z);
                }
                else
                {
                  glNormal3f(normal_vertices[Faces[i]._0].x, normal_vertices[Faces[i]._0].y, normal_vertices[Faces[i]._0].z);
                  glVertex3f(Vertices[Faces[i]._0].x, Vertices[Faces[i]._0].y, Vertices[Faces[i]._0].z);
                  glNormal3f(normal_vertices[Faces[i]._1].x, normal_vertices[Faces[i]._1].y, normal_vertices[Faces[i]._1].z);
                  glVertex3f(Vertices[Faces[i]._1].x, Vertices[Faces[i]._1].y, Vertices[Faces[i]._1].z);
                  glNormal3f(normal_vertices[Faces[i]._2].x, normal_vertices[Faces[i]._2].y, normal_vertices[Faces[i]._2].z);
                  glVertex3f(Vertices[Faces[i]._2].x, Vertices[Faces[i]._2].y, Vertices[Faces[i]._2].z);
                }
            }
            glEnd();
          }
          else
            {
              glBegin(GL_TRIANGLES);
              for (unsigned i=0;i<Faces.size();i++){
                glNormal3f(normal_vertices[Faces[i]._0].x, normal_vertices[Faces[i]._0].y, normal_vertices[Faces[i]._0].z);
                glVertex3f(Vertices[Faces[i]._0].x, Vertices[Faces[i]._0].y, Vertices[Faces[i]._0].z);
                glNormal3f(normal_vertices[Faces[i]._1].x, normal_vertices[Faces[i]._1].y, normal_vertices[Faces[i]._1].z);
                glVertex3f(Vertices[Faces[i]._1].x, Vertices[Faces[i]._1].y, Vertices[Faces[i]._1].z);
                glNormal3f(normal_vertices[Faces[i]._2].x, normal_vertices[Faces[i]._2].y, normal_vertices[Faces[i]._2].z);
                glVertex3f(Vertices[Faces[i]._2].x, Vertices[Faces[i]._2].y, Vertices[Faces[i]._2].z);
              }
              glEnd();
            }
        }
        else{
            if(text>0){
              glBegin(GL_TRIANGLES);
              for (unsigned i=0;i<Faces.size();i++){
                  if(i<f){
                    glTexCoord2f(ctex[Faces[i]._0].x,ctex[Faces[i]._0].y);
                    glVertex3f(Vertices[Faces[i]._0].x, Vertices[Faces[i]._0].y, Vertices[Faces[i]._0].z);
                    glTexCoord2f(ctex[Faces[i]._1].x,ctex[Faces[i]._1].y);
                    glVertex3f(Vertices[Faces[i]._1].x, Vertices[Faces[i]._1].y, Vertices[Faces[i]._1].z);
                    glTexCoord2f(ctex[Faces[i]._2].x,ctex[Faces[i]._2].y);
                    glVertex3f(Vertices[Faces[i]._2].x, Vertices[Faces[i]._2].y, Vertices[Faces[i]._2].z);
                  }
                  else
                    {
                      glVertex3f(Vertices[Faces[i]._0].x, Vertices[Faces[i]._0].y, Vertices[Faces[i]._0].z);
                      glVertex3f(Vertices[Faces[i]._1].x, Vertices[Faces[i]._1].y, Vertices[Faces[i]._1].z);
                      glVertex3f(Vertices[Faces[i]._2].x, Vertices[Faces[i]._2].y, Vertices[Faces[i]._2].z);
                    }
              }
            glEnd();
            }
            else
            {
              glBegin(GL_TRIANGLES);
              for (unsigned i=0;i<Faces.size();i++){
                glNormal3f(normal_caras[i].x, normal_caras[i].y, normal_caras[i].z);
                glVertex3f(Vertices[Faces[i]._0].x, Vertices[Faces[i]._0].y, Vertices[Faces[i]._0].z);
                glVertex3f(Vertices[Faces[i]._1].x, Vertices[Faces[i]._1].y, Vertices[Faces[i]._1].z);
                glVertex3f(Vertices[Faces[i]._2].x, Vertices[Faces[i]._2].y, Vertices[Faces[i]._2].z);
              }
            glEnd();
          }
        }
      }
    }
  else
    {
      glBegin(GL_TRIANGLES);
      for (unsigned i=0;i<Faces.size();i++){
          if(i%2==0)
            glColor3f(0,1,1);
          else
            glColor3f(1,1,0);
          glVertex3f(Vertices[Faces[i]._0].x, Vertices[Faces[i]._0].y, Vertices[Faces[i]._0].z);
          glVertex3f(Vertices[Faces[i]._1].x, Vertices[Faces[i]._1].y, Vertices[Faces[i]._1].z);
          glVertex3f(Vertices[Faces[i]._2].x, Vertices[Faces[i]._2].y, Vertices[Faces[i]._2].z);
      }
    glEnd();
    }
}

void apply_img(jpg::Imagen * pimg){
  tamx = pimg->tamX();
  tamy = pimg->tamY();
  texels = pimg->leerPixels();
}
/*
void adjust_texture(){
  float tam=Vertices.size(),last_tam=tam/rep;
  ctex.resize(tam);
  float x=last_tam, y=rep;
  float cy;
  for(unsigned i=0; i<y;i++){
    cy = i/(y-1);
    for(unsigned j=0; j<x; j++){
      ctex[j+i*x].x = cy;
      ctex[j+i*x].y = j/(x-1);
    }
  }
}*/

void adjust_texture(){
  float tam=Vertices.size(), last_tam=tam/rep;
  ctex.resize(tam);
  float x=last_tam, y=rep;
  float cy;
  for(unsigned i=0; i<y;i++){
    cy = i/(y-1);
    for(unsigned j=0; j<x; j++){
      ctex[j+i*x].x = cy;
      ctex[j+i*x].y = j/(x-1);
    }
  }
}


void crea_material(GLfloat material_a[], GLfloat material_d[], GLfloat material_s[], GLfloat e){
  if(texels == NULL){
  // hace M_A : = ( r, g, b ) , inicialmente (0.2,0.2,0.2)
    glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, material_a ) ;
    // hace M_D : = ( r, g, b ) , inicialmente (0.8,0.8,0.8)
    glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, material_d ) ;
    // hace M_S : = ( r, g, b ) , inicialmente (0,0,0)
    glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, material_s ) ;
    // hace e : = v, inicialmente 0.0 (debe estar entre 0.0 y 128.0)
    glMaterialf( GL_FRONT_AND_BACK, GL_SHININESS, e ) ;
  }
  else{
    GLfloat textura[4]={1.0,1.0,1.0,1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, textura );
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_s ) ;
    glMaterialf( GL_FRONT_AND_BACK, GL_SHININESS, e ) ;
    glLightModeli( GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR ) ;
  }
}

};
