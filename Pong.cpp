#include <SFML/Graphics.hpp>
#include <iostream>
#include <iomanip>
#include <cmath>

int main()
{
    srand(time(0));

    //Variables
    double PI = 22.0/7.0;
    double speed = .1;
    int s1 = 0;
    int s2 = 0;
    int miss1 = 0;
    int miss2 = 0;
    int hits = 0;
    double xSpeed, ySpeed;
    double angle = (rand()%40+25)*PI/180.0;
    bool left = false;
    bool right = true;
    bool end = false;

    xSpeed = speed * cos(angle);
    ySpeed = speed * sin(angle);

    //Create main window
    sf::RenderWindow app(sf::VideoMode(800, 600), "PONG!");

    //load a rectangle
    sf::RectangleShape p1(sf::Vector2f(10, 100));
    p1.setOrigin(10,50);
    p1.setFillColor(sf::Color(225, 0, 0));
    p1.setPosition(30, 300);

    sf::RectangleShape p2(sf::Vector2f(10, 100));
    p2.setOrigin(0,50);
    p2.setFillColor(sf::Color(0, 0, 255));
    p2.setPosition(750, 300);

    sf::RectangleShape r1(sf::Vector2f(800, 600));
    r1.setFillColor(sf::Color(0, 0, 0));
    r1.setPosition(0, 0);

    //load a circle
    sf::CircleShape ball(10);
    ball.setOrigin(10,10);
    ball.setFillColor(sf::Color(0, 255, 0));
    ball.setPosition(400, 400);

    //loading text
    sf::Font myfont;
    myfont.loadFromFile("arial.ttf");

    sf::Text score1;
    score1.setFont(myfont);
    score1.setPosition(30,50);
    score1.setFillColor(sf::Color(255,0,0));
    score1.setString(std::to_string(s1));

    sf::Text score2;
    score2.setFont(myfont);
    score2.setPosition(750,50);
    score2.setFillColor(sf::Color(0,0,255));
    score2.setString(std::to_string(s2));

    sf:: Text blue;
    blue.setFont(myfont);
    blue.setPosition(330,200);
    blue.setFillColor(sf::Color(0,0,255));
    blue.setString("Blue Wins!");

    sf:: Text red;
    red.setFont(myfont);
    red.setPosition(330,200);
    red.setFillColor(sf::Color(255,0,0));
    red.setString("Red Wins!");




    //Game loop
    while (app.isOpen())
    {
        //Process events
        sf::Event event;
        while (app.pollEvent(event))
        {   
            //Close window : exit
            if (event.type == sf::Event::Closed)
                app.close();
        }
        if (miss1 != 10 && miss2 != 10) {
            //Game logic
            ball.move(xSpeed, ySpeed);
            
            // if ball hits paddle
            if (ball.getPosition().x >800 || ball.getPosition().x<0){
                xSpeed *= -1;
            }
            if (ball.getPosition().y >600 || ball.getPosition().y<0){
                ySpeed *= -1;
            }

            // moving paddles
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && p1.getPosition().y<550)
            {
                p1.move(0,.2);
            }   
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && p1.getPosition().y>50)
            {
                p1.move(0,-.2);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && p2.getPosition().y<550)
            {
                p2.move(0,.2);
            }   
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && p2.getPosition().y>50)
            {
                p2.move(0,-.2);
            }

            //if paddle hits ball
            if(p1.getGlobalBounds().intersects(ball.getGlobalBounds())){
                ySpeed = (ball.getPosition().y-p1.getPosition().y)/60 * speed;
                xSpeed = sqrt(speed*speed - ySpeed*ySpeed);
                right = true;
                left = false;

            }
            if(p2.getGlobalBounds().intersects(ball.getGlobalBounds())){
                ySpeed = (ball.getPosition().y-p2.getPosition().y)/60 * speed;
                xSpeed = (-sqrt(speed*speed - ySpeed*ySpeed));
                left = true;
                right = false;

            }

            // Moving ball to other side of screen when it goes out
            if (xSpeed > 0 && left) {
                if (ball.getPosition().x < 0){
                    ball.move (800,0);
                    miss2 ++;
                    score2.setString(std:: to_string(miss2));

                }
            }
            if (xSpeed < 0 && right) {
                if (ball.getPosition().x > 800){
                    ball.move (-800,0);
                    miss1 ++;
                    score1.setString(std:: to_string(miss1));

                }
            }

            app.clear();
            app.draw(ball);
            app.draw(p1);
            app.draw(p2);
            app.draw(score1);
            app.draw(score2);
        }

        // to determine winner
        if (miss1 == 10) {
            app.draw(r1);
            app.draw(red);
            // "red wins";
        }
        else if (miss2 == 10) {
            app.draw(r1);
            app.draw(blue);

            //"blue wins";
        }
        app.display();

    }

    return 0;
}