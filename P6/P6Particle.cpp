#include "P6Particle.hpp"

using namespace P6;
//Convert formula P2=P1+Vt into a function
void P6Particle::UpdatePosition(float time) {
	//P2     =    P1    +     V        t
	//this->Position = this->Position + (this->Velocity * time) + ((1.f / 2.f) * (this->Acceleration * time * time));
	MyVector temp = this->Acceleration * time * time;
	temp = temp * (1.f / 2.f);
	this->Position = this->Position + (this->Velocity * time) + temp;
}

void P6Particle::UpdateVelocity(float time) {
	//Vf           =     Vi                      A           t
	this->Velocity = this->Velocity + (this->Acceleration * time);
}

void P6Particle::Update(float time) {
	this->UpdatePosition(time);
	this->UpdateVelocity(time);
}