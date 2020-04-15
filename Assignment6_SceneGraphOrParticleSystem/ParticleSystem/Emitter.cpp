#include "Emitter.h"
#include "Renderable.h"
#include <iostream>

using namespace std;

Emitter::Emitter(const QVector3D& position, const QVector3D& orientation, unsigned int pps, Renderable* particleModel) {
    location_ = position;
    orientation_ = orientation;
    particleModel_ = particleModel;
    pps_ = pps;
    msSinceEmit_ = 0;
}

void Emitter::update(unsigned int msSinceLastFrame) {

    for (auto particle: particles_) {
        particle->update(msSinceLastFrame);
    }

    msSinceEmit_ += msSinceLastFrame;
    int numParticles = pps_ * (msSinceEmit_ / 1000.);

    for (int i = 0; i < numParticles; i++) {
        msSinceEmit_ = 0;
        particles_.push_back(emitParticle());
    }

    for (int i = 0; i < particles_.count(); i++) {

        Particle* p = particles_.at(i);

        if (p->isDead()) {
            delete p;
            particles_.remove(i);
            i -= 1;
        }
    }

}

float getOffset(float a, float b) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

Particle* Emitter::emitParticle() {

    float offsetX = getOffset(-1.0, 1.0);
    float offsetY = getOffset(-1.0, 1.0);

    QVector3D velocity(orientation_.x() + offsetX, orientation_.y() + offsetY, orientation_.z());

    QMatrix4x4 transform;
    transform.translate(location_);

    float lifetime = 10;

    return new Particle(particleModel_, transform, velocity, lifetime);
}

void Emitter::draw(const QMatrix4x4& projection, const QMatrix4x4& view) {
    for (auto particle: particles_) {
        particle->draw(projection, view);
    }
}
