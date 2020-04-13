#include <QtCore>
#include <QtGui>
#include <QtOpenGL>
#include <iostream>
#include "Renderable.h"
using namespace std;

class ParticleSystem {
  protected:
  QVector<Emitter*> emitters_;
  QVector<Particle*> particles_;


}