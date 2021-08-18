#include "ChargeSystem.h"
#include <vector>
#include <iostream>

ChargeSystem::ChargeSystem(std::vector<Charge> charges, Boundary bounds) {
	this->charges = charges;
    this->bounds = bounds;
}

void ChargeSystem::UpdateSystem() {
    for (int i = 0; i < this->charges.size(); i++) {
        for (int j = i + 1; j < this->charges.size(); j++) {

            std::vector<double> dist = getDistance(this->charges.at(i), this->charges.at(j));
            std::vector<double> force1 = { 10000 * dist[0] / pow((pow(dist[0], 2) + pow(dist[1], 2)),1.5) , 10000 * dist[1] / pow((pow(dist[0], 2) + pow(dist[1], 2)),1.5) };
            std::vector<double> force2 = { -force1[0], -force1[1] };

            force1[0] -= dampingConstant * this->charges[i].vel[0];
            force1[1] -= dampingConstant * this->charges[i].vel[1];
            force2[0] -= dampingConstant * this->charges[j].vel[0];
            force2[1] -= dampingConstant * this->charges[j].vel[1];

            charges[i].vel[0] = charges[i].vel[0] + deltaT * force1[0];
            charges[i].vel[1] = charges[i].vel[1] + deltaT * force1[1];
            charges[j].vel[0] = charges[j].vel[0] + deltaT * force2[0];
            charges[j].vel[1] = charges[j].vel[1] + deltaT * force2[1];
            
            charges[i].pos[0] = charges[i].pos[0] + deltaT * charges[i].vel[0];
            charges[i].pos[1] = charges[i].pos[1] + deltaT * charges[i].vel[1];
            charges[j].pos[0] = charges[j].pos[0] + deltaT * charges[j].vel[0];
            charges[j].pos[1] = charges[j].pos[1] + deltaT * charges[j].vel[1];

            runBoundaries(i);
            runBoundaries(j);
        }
    }
}

void ChargeSystem::runBoundaries(int index) {
    if (this->charges[index].pos[0] > bounds.maxX) {
        this->charges[index].pos[0] = bounds.maxX;
    }
    if (this->charges[index].pos[0] < bounds.minX) {
        this->charges[index].pos[0] = bounds.minX;
    }
    if (this->charges[index].pos[1] > bounds.maxY) {
        this->charges[index].pos[1] = bounds.maxY;
    }
    if (this->charges[index].pos[1] < bounds.minY) {
        this->charges[index].pos[1] = bounds.minY;
    }
}

std::vector<double> ChargeSystem::getDistance(Charge c1, Charge c2)
{
    return { c1.pos.at(0) - c2.pos.at(0), c1.pos.at(1) - c2.pos.at(1) };
}
