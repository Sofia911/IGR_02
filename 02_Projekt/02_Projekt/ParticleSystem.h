#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H
#include "Particle.h"

#pragma once

class ParticleSystem
{
private:
	std::vector<Particle> particleBuffer = {};
	Vector3f normal;
public:
	ParticleSystem() {}
	std::vector<Particle> generateParticle(int num);
	void deleteParticle(int index, Particle p, Vector3f corner1, Vector3f corner2);
	int getBufferSize() { return particleBuffer.size(); }
	Particle getParticle(int index) { return particleBuffer[index]; }
	void setParticle(int index, Particle p_) { particleBuffer[index] = p_; }
	int getSize() { return particleBuffer.size(); }
	bool particleHit(int index, Particle p);
	~ParticleSystem(){}
};
#endif // !PARTICLESYSTEM_H