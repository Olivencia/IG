//**************************************************************************
// Práctica 3
//
// Domingo Martin Perandres 2013
//
// GPL
//**************************************************************************

#include "stdlib.h"
#include "stdio.h"
#include <GL/glut.h>
#include <ctype.h>
#include "user_code.h"
#include "Camara.cc"
#include "object.cc"

// tamaño de los ejes
const int AXIS_SIZE=5000;
const int BUFFER_SIZE=2048;
bool inicio=true, color = false, ajedrez = false, normal = false, idle=false, noc=false, nov=false, ang=false, pulsado_derecho=false, pulsado_izquierda=false, modo=true, begin=true;
_vertex2f angles;
int valor=4, gl=-1, ObjetoSel=0;
unsigned zoom=5;
_vertex2f coord = 0;
enum Figuras { cube=0, sphere=1, semisphere=2, cylinder=3, cylinder_2 = 4, cylinder_3 = 5, semicylinder=6, tetrahedron=7 };

  GLuint selectBuf[100]={0};

unsigned MAX_SEL = 64;
  GLuint Selection_buffer[BUFFER_SIZE];
  int yant=0, xant=0, camaraActiva=0;
  Camara camaras[3];

  Object esfera, cubo, beethoven1;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Window_width,Window_height,Front_plane,Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int UI_window_pos_x=50,UI_window_pos_y=50,UI_window_width=1400,UI_window_height=1000;

//**************************************************************************
//
//***************************************************************************

void clear_window()
{

glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}


//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void change_projection()
{

glMatrixMode(GL_PROJECTION);
glLoadIdentity();

// formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_traser)
//  Front_plane>0  Back_plane>PlanoDelantero)
glFrustum(-Window_width,Window_width,-Window_height,Window_height,Front_plane,Back_plane);
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void change_observer()
{

// posicion del observador
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
camaras[camaraActiva].setObservador();
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void draw_axis()
{
glBegin(GL_LINES);
// eje X, color rojo
glColor3f(1,0,0);
glVertex3f(-AXIS_SIZE,0,0);
glVertex3f(AXIS_SIZE,0,0);
// eje Y, color verde
glColor3f(0,1,0);
glVertex3f(0,-AXIS_SIZE,0);
glVertex3f(0,AXIS_SIZE,0);
// eje Z, color azul
glColor3f(0,0,1);
glVertex3f(0,0,-AXIS_SIZE);
glVertex3f(0,0,AXIS_SIZE);
glEnd();
}


//**************************************************************************
// Funcion que dibuja los objetos
//***************************************************************************
void draw();

void draw_objects()
{
    draw();
}

void load_obj(){
  cubo.load_form(cube);
  esfera.load_form(sphere);
  beethoven1.load_ply("ply/beethoven.ply");
}

void draw(){
    if(inicio){
        menu();
        inicio=false;
    }
  glLoadName(1);
  // Pito ahora el cubo con nombre 1.
  glTranslatef(-10,0,0);
  if(ObjetoSel==1)
    glColor3f(1,0,0);
  else
    glColor3f(0,0,1);
  beethoven1.draw();
  // Muevo el siguiente cubo.
  glTranslatef(10,0,0);
  // Cambio el nombre del objeto,
  // ahora sera 2.
  glLoadName(2);
  // Pinto el cubo que tendra el nombre 2.
  if(ObjetoSel==2)
    glColor3f(1,0,0);
  else
    glColor3f(0,0,1);
  beethoven1.draw();
  // Muevo el siguiente cubo.
  glTranslatef(10,0,0);
  // Cambio el nombre del objeto,
  // ahora sera 3.
  glLoadName(3);
  // Pinto el cubo que tendra el nombre 3.
  if(ObjetoSel==3)
    glColor3f(1,0,0);
  else
    glColor3f(0,0,1);
  beethoven1.draw();
  // Muevo el siguiente cubo.
  glTranslatef(10,0,0);
  // Cambio el nombre del objeto,
  // ahora sera 4.
  glLoadName(4);
  // Pinto el cubo que tendra el nombre 4.
  if(ObjetoSel==4)
    glColor3f(1,0,0);
  else
    glColor3f(0,0,1);
  beethoven1.draw();

  glTranslatef(-30,0,20);
  glLoadName(5);
  // Pinto el cubo que tendra el nombre 4.
  if(ObjetoSel==5)
    glColor3f(1,0,0);
  else
    glColor3f(0,0,1);
  beethoven1.draw();

  glTranslatef(10,0,0);
  glLoadName(6);
  // Pinto el cubo que tendra el nombre 4.
  if(ObjetoSel==6)
    glColor3f(1,0,0);
  else
    glColor3f(0,0,1);
  beethoven1.draw();


  glTranslatef(10,0,0);
  glLoadName(7);
  // Pinto el cubo que tendra el nombre 4.
  if(ObjetoSel==7)
    glColor3f(1,0,0);
  else
    glColor3f(0,0,1);
  beethoven1.draw();

  glTranslatef(10,0,0);
  glLoadName(8);
  // Pinto el cubo que tendra el nombre 4.
  if(ObjetoSel==8)
    glColor3f(1,0,0);
  else
    glColor3f(0,0,1);
  beethoven1.draw();


  glPopName();
  // Restablezco la matriz modelo.
  glPopMatrix();
  // Selecciono la matriz proyeccion
  glMatrixMode(GL_PROJECTION);
  // La restablezco.
  glPopMatrix();
  // Dejo la de matriz modelo.
  glMatrixMode(GL_MODELVIEW);
}

//**************************************************************************
//
//***************************************************************************

void draw_scene(void)
{

clear_window();
change_observer();
draw_axis();
draw_objects();
glutSwapBuffers();
}


//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size(int Ancho1,int Alto1)
{
change_projection();
glViewport(0,0,Ancho1,Alto1);
glutPostRedisplay();
}

//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************




void normal_keys(unsigned char Tecla1,int x,int y)
{

int mod;

  switch (toupper(Tecla1)) {

    case 'A':camaras[camaraActiva].Observer_angle_y--;break;
    case 'D':camaras[camaraActiva].Observer_angle_y++;break;
    case 'W':camaras[camaraActiva].Observer_angle_x--;break;
    case 'S':camaras[camaraActiva].Observer_angle_x++;break;


    case 'P':
      glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
      color=false;
      ajedrez=false;
      draw_scene();
    break;
    case 'L':
      glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
      color=false;
      ajedrez=false;
      draw_scene();
    break;
    case 'O':
      glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
      color=true;
      ajedrez=false;
      draw_scene();
    break;
    case 'I':
      glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
      color=true;
      ajedrez=true;
      glDisable(GL_LIGHTING);
      glDisable(GL_LIGHT0);
      glDisable(GL_NORMALIZE);
      draw_scene();
    break;
    case 'B':
      mod = glutGetModifiers();
      if(mod != GLUT_ACTIVE_SHIFT){
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
        color=true;
        ajedrez=false;
        noc=true;
        nov=false;
        glShadeModel(GL_FLAT);
        glEnable(GL_LIGHTING);
        if(valor!=2){
            glEnable(GL_LIGHT0);
            glEnable(GL_LIGHT1);
          }
        else
          glEnable(GL_LIGHT0);
        glEnable(GL_NORMALIZE);
        draw_scene();
      }
      else{
          glDisable(GL_LIGHTING);
          if(valor!=2){
              glDisable(GL_LIGHT0);
              glDisable(GL_LIGHT1);
            }
          else
            glDisable(GL_LIGHT0);
          glDisable(GL_NORMALIZE);
          draw_scene();
        }
    break;
    case 'N':
      mod = glutGetModifiers();
      if(mod != GLUT_ACTIVE_SHIFT){
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
        color=true;
        ajedrez=false;
        noc=false;
        nov=true;
        glShadeModel(GL_SMOOTH);
        glEnable(GL_LIGHTING);
        if(valor!=2){
            glEnable(GL_LIGHT0);
            glEnable(GL_LIGHT1);
          }
        else
          glEnable(GL_LIGHT0);
        glEnable(GL_NORMALIZE);
        draw_scene();
      }
      else{
          glDisable(GL_LIGHTING);
          if(valor!=2){
              glDisable(GL_LIGHT0);
              glDisable(GL_LIGHT1);
            }
          else
            glDisable(GL_LIGHT0);
          glDisable(GL_NORMALIZE);
          draw_scene();
        }
    break;
    case 'T':
      mod = glutGetModifiers();
      if(mod != GLUT_ACTIVE_SHIFT){
          glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
          glEnable(GL_TEXTURE_2D);
          draw_scene();
      }
      else{
           glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
        glDisable(GL_TEXTURE_2D);
        draw_scene();
      }
    break;

    case 'J':
      mod = glutGetModifiers();
      if(mod != GLUT_ACTIVE_SHIFT){
          angles.x+=1;
          draw_scene();
      }
      else{
          angles.x-=1;
          draw_scene();
      }
    break;

    case 'K':
      mod = glutGetModifiers();
      if(mod != GLUT_ACTIVE_SHIFT){
          angles.y+=1;
          draw_scene();
      }
      else{
          angles.y-=1;
          draw_scene();
      }
    break;

    case '1':
      valor=0;
      draw_scene();
    break;
    case '2':
      valor=1;
      zoom=5;
      draw_scene();
    break;
    case '3':
      glColorMaterial(GL_FRONT, GL_DIFFUSE);
      glEnable(GL_COLOR_MATERIAL);
      glEnable(GL_LIGHT0);
      glDisable(GL_LIGHT1);
      valor=2;
      draw_scene();
    break;
    case '4':
      glEnable(GL_LIGHT0);
      glEnable(GL_LIGHT1);
      valor=3;
      draw_scene();
    break;

    case '5':
      valor=4;
      draw_scene();
    break;

  case 'V':
      mod = glutGetModifiers();
      if(mod != GLUT_ACTIVE_SHIFT){
          gl=0;
          draw_scene();
      }
      else{
          gl=1;
          draw_scene();
      }
  break;
  case 'Z':
      mod = glutGetModifiers();
      if(mod != GLUT_ACTIVE_SHIFT){
          gl=2;
          draw_scene();
      }
      else{
          gl=3;
          draw_scene();
      }
  break;
    case 'X':
      mod = glutGetModifiers();
      if(mod != GLUT_ACTIVE_SHIFT){
          gl=4;
          draw_scene();
      }
      else{
          gl=5;
          draw_scene();
      }
    break;
    case 'C':
      mod = glutGetModifiers();
      if(mod != GLUT_ACTIVE_SHIFT){
          gl=6;
          draw_scene();
      }
      else{
          gl=7;
          draw_scene();
      }
    break;
    case GLUT_KEY_PAGE_UP:
      camaras[camaraActiva].Observer_distance=zoom*Front_plane+ Front_plane*2;
      camaras[camaraActiva].Observer_angle_x=0;
      camaras[camaraActiva].Observer_angle_y=0;
    break;
    case GLUT_KEY_PAGE_DOWN:
      camaras[camaraActiva].Observer_distance=zoom*Front_plane - Front_plane*2;
      camaras[camaraActiva].Observer_angle_x=0;
      camaras[camaraActiva].Observer_angle_y=0;
    break;
  }
glutPostRedisplay();
}

//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************

void special_keys(int Tecla1,int x,int y)
{

switch (Tecla1){
  case GLUT_KEY_LEFT:camaras[camaraActiva].Observer_angle_y--;break;
  case GLUT_KEY_RIGHT:camaras[camaraActiva].Observer_angle_y++;break;
  case GLUT_KEY_UP:camaras[camaraActiva].Observer_angle_x--;break;
  case GLUT_KEY_DOWN:camaras[camaraActiva].Observer_angle_x++;break;
  case GLUT_KEY_PAGE_UP:camaras[camaraActiva].Observer_distance*=1.2;break;
  case GLUT_KEY_PAGE_DOWN:camaras[camaraActiva].Observer_distance/=1.2;break;
	}
 gl=-1;
glutPostRedisplay();
}



//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(void)
{
// se inicalizan la ventana y los planos de corte
Window_width=.7;
Window_height=.5;
Front_plane=1;
Back_plane=1000;

// se inicia la posicion del observador, en el eje z
camaras[camaraActiva].Observer_distance=zoom*Front_plane;
camaras[camaraActiva].Observer_angle_x=0;
camaras[camaraActiva].Observer_angle_y=0;

// se indica cual sera ecolor para limpiar la ventana	(r,v,a,al)
// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
glClearColor(0,0,0,1);

// se habilita el z-bufer
glEnable(GL_DEPTH_TEST);
change_projection();
glViewport(0,0,UI_window_width,UI_window_height);
}


void timer_func(int velocidad)           // NEW FUNCTION
{
	// Update the object positions, etc.
	draw_scene(); // spin the square

	glutTimerFunc(velocidad, timer_func, velocidad); // recursively call timer_func
}


void moveMouse(int x, int y){

  if(pulsado_derecho){
      camaras[camaraActiva].Observer_angle_y=x+xant;
      camaras[camaraActiva].Observer_angle_x=y+yant;
      yant= y;
      xant=x;
  }

glutPostRedisplay();
}

void procesar_hits(GLint hits, GLuint *names)
{

  // Si el numero de objetos seleccionados supera
  // el que permite nuestro buffer de seleccion,
  // OpenGL retornara -1.
  // Si es asi hago que el numero de objetos
  // seleccionados sea el maximo.
  if(hits==-1) hits=MAX_SEL;
  // Si ha habido algun objeto seleccionado.
  if(hits > 0)
  {
          // Seleccionare el que esta mas cerca en caso
          // de haber mas de 1.
          // Una variable para guardar dato de profundidad.
          GLuint z1;
          // Guardo el nombre del primer objeto seleccionado.
          ObjetoSel=selectBuf[(0*4)+3];
          // Guardo en z el dato de profundidad del
          // primer objeto seleccionado.
          GLfloat z=(float)selectBuf[(0*4)+1];
          // Un bucle para recorrer todos los objetos
          // seleccionados e ir comparando sus profundidades.
          for(GLuint i=0; i<hits; i++)
          {
                  // Obtengo la profundidad del objeto en curso...
                  z1=selectBuf[(i*4)+1];
                  // ... y si es menos que z ...
                  if(z1 < z)
                  {	// ... la pongo en z...
                          z=z1;
                          // ... y el nombre del objeto en la variable para eso.
                          ObjetoSel=selectBuf[(i*4)+3];
                  }
          }
  }
  // Si no hay ninguno seleccionado pongo 0 en la variable
  // con el nombre del objeto seleccionado.
  else ObjetoSel=0;

}


void pick(unsigned int x, unsigned int y)
{
  GLint viewport[4], hits=0;
  glSelectBuffer(100, selectBuf);

  glGetIntegerv (GL_VIEWPORT, viewport);
  glRenderMode (GL_SELECT);

  glInitNames(); glPushName(0);
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();

  gluPickMatrix (x,(viewport[3] - y),5.0, 5.0, viewport);
  glFrustum(-Window_width,Window_width,-Window_height,Window_height,Front_plane,Back_plane);

  draw_scene();

  hits = glRenderMode (GL_RENDER);

  glMatrixMode (GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-Window_width,Window_width,-Window_height
  ,Window_height,Front_plane,Back_plane);

  procesar_hits(hits, selectBuf);
}

void mouseClick( int button, int state, int x, int y ){
  if(button == GLUT_RIGHT_BUTTON){
      if(state == GLUT_DOWN){
          pick(x,y);
          pulsado_derecho=true;
        }
    }
  else
    {
      if(button == GLUT_LEFT_BUTTON){
          if(state == GLUT_DOWN){
            pulsado_derecho=false;
            pick(x,y);
          }
        }

      else
        {
          if(button == 3)
              camaras[camaraActiva].Observer_distance/=1.2;
          else if(button==4)
            camaras[camaraActiva].Observer_distance*=1.2;
          pulsado_derecho=false;
        }
    }
glutPostRedisplay();
}




//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************

int main(int argc, char **argv)
{
    // se llama a la inicialización de glut
    glutInit(&argc, argv);

    // se indica las caracteristicas que se desean para la visualización con OpenGL
    // Las posibilidades son:
    // GLUT_SIMPLE -> memoria de imagen simple
    // GLUT_DOUBLE -> memoria de imagen doble
    // GLUT_INDEX -> memoria de imagen con color indizado
    // GLUT_RGB -> memoria de imagen con componentes rojo, verde y azul para cada pixel
    // GLUT_RGBA -> memoria de imagen con componentes rojo, verde, azul y alfa para cada pixel
    // GLUT_DEPTH -> memoria de profundidad o z-bufer
    // GLUT_STENCIL -> memoria de estarcido
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    // posicion de la esquina inferior izquierdad de la ventana
    glutInitWindowPosition(UI_window_pos_x,UI_window_pos_y);

    // tamaño de la ventana (ancho y alto)
    glutInitWindowSize(UI_window_width,UI_window_height);

    // llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
    // al bucle de eventos)
    glutCreateWindow("Práctica 3");

    // asignación de la funcion llamada "dibujar" al evento de dibujo
    glutDisplayFunc(draw_scene);
    // asignación de la funcion llamada "cambiar_tamanio_ventana" al evento correspondiente
    glutReshapeFunc(change_window_size);
    //Redibujados


    // asignación de la funcion llamada "tecla_normal" al evento correspondiente
    glutKeyboardFunc(normal_keys);
    // asignación de la funcion llamada "tecla_Especial" al evento correspondiente
    glutSpecialFunc(special_keys);

    // funcion de inicialización
    initialize();
    //Animación
    if(idle){
        glutIdleFunc(draw_scene);
      }
    if(begin){
      load_obj();
      begin=false;
    }

    glutMouseFunc( mouseClick );
    glutMotionFunc(moveMouse);
    // inicio del bucle de eventos
    glutMainLoop();
    return 0;
}
