HEADERS = \
  *.h* \
    object.h

  
SOURCES = \
  *.c* \
    object.cc

LIBS += -L/casa/dmartin/codigo/funciontecas/freeglut/lib \
    -lglut -ljpeg

CONFIG += console
QT += opengl

