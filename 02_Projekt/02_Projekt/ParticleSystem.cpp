#include "ParticleSystem.h"

std::vector<Particle> ParticleSystem::generateParticle(int num) {
	for (int i = 0; i < num; i++) {
		Vector3f x;
		x = x.randPoint();
		Particle p(x, Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.0f, 0.0f, 0.0f), 1.0f, 3.0f);
		particleBuffer.push_back(p); // add particle to buffer
	}
	return particleBuffer;
}

void ParticleSystem::deleteParticle(int index, Particle p, Vector3f corner1, Vector3f corner2) {
	const float EPSILON = 0.01f;
	std::vector<Vector3f> p_state = p.getState();
	Vector3f pos = p_state[0];
	float max_z = std::max(corner1.getZ(), corner2.getZ());
	if (pos.getZ() > max_z + max_z * 0.001f) {
		particleBuffer.erase(particleBuffer.begin() + index); // delete particle from buffer if it is out of the plane
	}
}

bool ParticleSystem::particleHit(int index, Particle p1)
{
	const float EPSILON = p1.getRadius(); // get radius of particle
	Vector3f p1_pos = p1.getPos();
	Vector3f p1_v = p1.getV();
	for (unsigned int j = 0; j < particleBuffer.size(); j++) // over all particles
	{
		if (index == j) { continue; }
		Particle p2 = particleBuffer[j];
		Vector3f p2_pos = p2.getPos();
		if (p1_pos.getX() > (p2_pos.getX() - EPSILON) && p1_pos.getX() < (p2_pos.getX() + EPSILON)) { // check if x values are equal
			if ((p1_pos.getY() > p2_pos.getY() - EPSILON) && p1_pos.getY() < (p2_pos.getY() + EPSILON)){ // check if y values are equal
				if ((p1_pos.getZ() > p2_pos.getZ() - EPSILON) && p1_pos.getZ() < (p2_pos.getZ() + EPSILON)) { // check if z values are equal
					// calculate new velocities
					Vector3f p2_n = p2.getV().uminus();
					Vector3f p1_v_neu = p1_v - p2_n * (p1_v.dot_product(p2_n)) * 2.0f; // reflection: dir_new = dir - 2 * (dir * normal) * normal
					
					Vector3f p1_n = p1.getV().uminus();
					Vector3f p2_v_neu = p2.getV() - p1_n * (p2.getV().dot_product(p1_n)) * 2.0f; // reflection

					p1.setState(p1_pos, p1_v_neu);
					p2.setState(p2_pos, p2_v_neu);
					return true;
				}		
			}
		}		
	}
	return false;
}
