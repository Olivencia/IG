HEADERS = \
  *.h* \
    object.h

  
SOURCES = \
  *.c* \
    object.cc \
    Camara.cc

LIBS += -L/casa/dmartin/codigo/funciontecas/freeglut/lib \
    -lglut -ljpeg -lGLU

CONFIG += console
QT += opengl

