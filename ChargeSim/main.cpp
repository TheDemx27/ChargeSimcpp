#include <SFML/Graphics.hpp>
#include <math.h>
#include "ChargeSystem.h"
#include <iostream>

int main() {

    // create the window
    sf::RenderWindow window(sf::VideoMode(1200, 720), "ChargeSim");
    //window.setFramerateLimit(60);

    // INITITAL VALUES
    std::vector<Charge> charges;
    sf::Vector2u size = window.getSize();
    double cx = size.x / 2;
    double cy = size.y / 2;

    Boundary bounds;
    bounds.maxX = cx + 200;
    bounds.maxY = cy + 200;
    bounds.minX = cx - 200;
    bounds.minY = cy - 200;

    for (int i = -100; i <= 100; i+= 20) {
        for (int j = -100; j <= 100; j += 20) {
            Charge charge;
            charge.pos = { cx + i, cy + j };
            charge.vel = { 0.0f, 0.0f };
            charges.push_back(charge);
        }
    }

    ChargeSystem sys(charges, bounds);

    // run the program as long as the window is open
    while (window.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        // window.draw(...);        
        for (int i = 0; i < sys.charges.size(); i++) {
            sf::CircleShape circle = sf::CircleShape(1);
            circle.setPosition(sys.charges[i].pos[0], sys.charges[i].pos[1]);
            window.draw(circle);
        }

        sys.UpdateSystem();
        // end the current frame
        window.display();
    }

    return 0;
}

