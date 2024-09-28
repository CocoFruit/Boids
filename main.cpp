#include <SFML/Graphics.hpp>
#include <vector>
#include <deque>
#include <cmath>
#include <iostream>
#include <list>

class Boid{
    sf::Vector2i pos;
    sf::Vector2f vel;
    sf::CircleShape circle;
    int size = 2;

    // Tunable Values
    int protectedRange = 40;
    int visibleRange = 140;
    float avoidFactor = 0.3;
    float matchingFactor = .005;
    float centeringFactor = 0.0003;
    float turnFactor = 0.5;
    float maxSpeed = 15;
    float minSpeed = 6;

    public:
        Boid(int pos_x, int pos_y, float vel_x, float vel_y) {
            pos.x = pos_x;
            pos.y = pos_y;
            vel.x = vel_x;
            vel.y = vel_y;

            circle.setRadius(size);
            circle.setFillColor(sf::Color::White);

        }


        void render(sf::RenderWindow& wind){
            wind.draw(circle);
        }
        void update(std::list<Boid> boids, int topMargin, int bottomMargin, int leftMargin, int rightMargin){

            // Seperation
            int close_dx = 0;
            int close_dy = 0;

            // Alignment
            float xvel_avg = 0;
            float yvel_avg = 0;
            int neighboring_boids = 0;

            //Cohesion
            float xpos_avg = 0;
            float ypos_avg = 0;

            for(const auto& curBoid : boids){
                if((abs(curBoid.pos.x - pos.x) < visibleRange) && (abs(curBoid.pos.y - pos.y) < visibleRange)){
                    neighboring_boids += 1;

                    // Alignment
                    xvel_avg += curBoid.vel.x;
                    yvel_avg += curBoid.vel.y;

                    //Cohesion
                    xpos_avg += curBoid.pos.x;
                    ypos_avg += curBoid.pos.y;
                }
                // Seperation
                else if((abs(curBoid.pos.x - pos.x) < protectedRange) && (abs(curBoid.pos.y - pos.y) < protectedRange)){
                    close_dx += pos.x - curBoid.pos.x;
                    close_dy += pos.y - curBoid.pos.y;
                }
            }

            if (neighboring_boids > 0) {
                xvel_avg = xvel_avg/neighboring_boids;
                yvel_avg = yvel_avg/neighboring_boids;

                xpos_avg = xpos_avg/neighboring_boids;
                ypos_avg = ypos_avg/neighboring_boids;
            }

            // Seperation
            vel.x += close_dx*avoidFactor;
            vel.y += close_dy*avoidFactor;

            // Alignment
            vel.x += (xvel_avg - vel.x)*matchingFactor;
            vel.y += (yvel_avg - vel.y)*matchingFactor;
 
            // Cohesion
            vel.x += (xpos_avg - pos.x)*centeringFactor;
            vel.y += (ypos_avg - pos.y)*centeringFactor;

            // Screen Edges
            if (pos.x < leftMargin) vel.x += turnFactor;
            if (pos.x > rightMargin) vel.x -= turnFactor;
            if (pos.y < topMargin) vel.y += turnFactor;
            if (pos.y > bottomMargin) vel.y -= turnFactor;

            // Speed Limit
            float speed = sqrt(vel.x*vel.x + vel.y*vel.y);
            if (speed > maxSpeed){
                vel.x = vel.x / speed * maxSpeed;
                vel.y = vel.y / speed * maxSpeed;
            }
            else if (speed < minSpeed){
                vel.x = vel.x / speed * minSpeed;
                vel.y = vel.y / speed * minSpeed;
            }

            // Update
            pos.x += vel.x;
            pos.y += vel.y;

            circle.setPosition(pos.x, pos.y);
        }


};

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 600), "Boids Algorithm");
    window.setFramerateLimit(60);

    int margin = 100;
    int top = margin;
    int bottom = window.getSize().y - margin;
    int left = margin;
    int right = window.getSize().x - margin;



    std::list<Boid> boids;
    for(int i = 0; i < 100; i++){
        boids.push_back(Boid(rand() % window.getSize().x, rand() % window.getSize().y, rand() % 5 - 2, rand() % 5 - 2));
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();
        }

        window.clear();
        // draw margin
        sf::RectangleShape margin_draw(sf::Vector2f(window.getSize().x-margin*2, window.getSize().y-margin*2));
        margin_draw.setFillColor(sf::Color{0,0,0,0});
        margin_draw.setOutlineColor(sf::Color{255,255,255,30});
        margin_draw.setOutlineThickness(1);
        margin_draw.setPosition(margin, margin);
        window.draw(margin_draw);

        for(auto& curBoid : boids){
            curBoid.update(boids, top, bottom, left, right);
            curBoid.render(window);
        }

        window.display();
    }

    return 0;
}