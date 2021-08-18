#pragma once
#include <vector>
struct Charge {
    std::vector<double> pos;
    std::vector<double> vel;
};

struct Boundary {
    double maxX;
    double minX;
    double maxY;
    double minY;
};

class ChargeSystem {
    const double dampingConstant = 0.5;
    double deltaT = 0.05;
    Boundary bounds;
    void runBoundaries(int index);
    std::vector<double> getDistance(Charge c1, Charge c2);
public:
    std::vector<Charge> charges;
    ChargeSystem(std::vector<Charge>, Boundary bounds);
    void UpdateSystem();
};