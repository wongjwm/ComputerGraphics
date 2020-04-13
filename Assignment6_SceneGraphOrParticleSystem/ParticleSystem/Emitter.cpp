#include <QtCore>
#include <QtGui>
#include <QtOpenGL>
#include <iostream>
#include <Application.h>
using namespace std;
#include "Renderable.h"

class Emitter {

protected:
  QVector<Particle> particles_;
  QVector3D position_;
  QVector3D orientation_;
  unsigned int particlesPerSecond_;
  Renderable* particleModel_;
  
public:
  Emitter(const QVector3D& position, const QVector3D& orientation, unsigned int pps, Renderable* particleModel);

  void update(unsigned int msSinceLastFrame) {
    // First, loop through all particles and update/draw them
	// Then, determine how many particles must be emitted
	// Then emit them one at a time.
	// Then, clean up our particle vector by removing dead particles
	
  }
  void emitParticle();
};