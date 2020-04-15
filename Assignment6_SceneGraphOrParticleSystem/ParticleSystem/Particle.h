#pragma once

#include <QtCore>
#include <QtGui>
#include "Renderable.h"

class Particle {
    protected:
        Renderable* renderable_;
        QVector3D velocity_;
        QMatrix4x4 transform_;
        float timeToLive_;
    public:
        Particle(Renderable* ren, const QMatrix4x4& transform, const QVector3D& velocity, float ttl);
        void update(unsigned int msSinceLastUpdate);
        void draw(const QMatrix4x4& projection, const QMatrix4x4& view);
        virtual ~Particle();
        bool isDead();
};