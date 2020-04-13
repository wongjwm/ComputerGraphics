#include <QtCore>
#include <QtGui>
#include <QtOpenGL>
#include <iostream>
#include <Application.h>
#include "Renderable.h"
using namespace std;

class Particle {

protected:
  Renderable* modelToRender_;
  QMatrix4x4 particleTransform_;
  QVector3D velocity_;
  float secondsLeftToLive_;

public:
  Particle(Renderable* model, const QVector3D& velocity, float lifespan);

  void updateAndDraw(unsigned int msSinceLastFrame);
  bool isDead() const {return secondsLeftToLive_ > 0.0;}
};