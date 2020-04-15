#include "Particle.h"

#include <iostream>

using namespace std;

Particle::Particle(Renderable* ren, const QMatrix4x4& transform, const QVector3D& velocity, float ttl) {
    renderable_ = ren;
    transform_ = transform;
    velocity_ = velocity;
    timeToLive_ = ttl;
}

void Particle::update(unsigned int msSinceLastUpdate) {
    float seconds = msSinceLastUpdate / 1000.0;
    timeToLive_ -= seconds;
    transform_.translate(velocity_);
    velocity_ -= seconds * QVector3D(0, 2., 0.);
}

void Particle::draw(const QMatrix4x4& projection, const QMatrix4x4& view) {
    if (isDead()) {
        return;
    }

    renderable_->setModelMatrix(transform_);
    renderable_->draw(view, projection);
}

bool Particle::isDead() {
    return timeToLive_ < 0;
}

Particle::~Particle() {}