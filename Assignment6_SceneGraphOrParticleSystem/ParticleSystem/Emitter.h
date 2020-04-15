#pragma once

#include <QtCore>
#include <QtGui>

#include "Particle.h"
#include "Renderable.h"

class Emitter {
    protected:
        QVector<Particle*> particles_;
        QVector3D location_;
        QVector3D orientation_;
        unsigned int pps_;
        unsigned int msSinceEmit_;
        Renderable* particleModel_;
    public:
        Emitter(const QVector3D& location, const QVector3D& orientation, unsigned int pps, Renderable* particleModel);
        void update(unsigned int msSinceLastFrame);
        void draw(const QMatrix4x4& projection, const QMatrix4x4& view);
        Particle* emitParticle();
};