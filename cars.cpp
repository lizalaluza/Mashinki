#include <SFML/Graphics.hpp>
#include <ctime>
#include <random>
const int window_length = 900;
const int window_width = 1350;
const float dt = 0.01;

int main()
{
    sf::RenderWindow window(sf::VideoMode(window_length, window_width), "Game");
    sf::View view = window.getView();
    int k = 0;
    float x = 0;
    float speed0 = 1500;
    float x_car = 330;
    float y_car = 730;
    float vx_car = 0;
    float y = dt*(k-1)*speed0;
    int x_cars[40];
    int y_cars[40];
    int r[40];
    for (int i = 0; i < 40; i++)
    {
        std::random_device rd;
        std::mt19937 mersenne(rd());
        std::uniform_int_distribution<> un_distrib(0, 3);

        int randomx = un_distrib(mersenne);
        y_cars[i] = 300 - 400*i;
        x_cars[i] = -230 + 190*randomx;
        r[i] = rand()%2;
    }
    float vy_cars = - 500;
   
    while (window.isOpen())
    {
        k += 1;
        sf::Event event;

        window.clear();
        window.setView(view); 
        
        y = dt*(k-1)*speed0;
        x_car += vx_car*dt;
        speed0 += 5;
        vx_car = 0;
        for (int i = 0; i < 40; i++)
        {
            y_cars[i] += (vy_cars + speed0)*dt;
        }
        
        //рисуем дорогу//
        sf::Texture t;
        sf::Sprite s1;
        sf::Sprite s2;
        t.loadFromFile("road.jpg");
        s1.scale(0.624f, 0.624);
        s2.scale(0.624f, 0.624);
        s1.setTexture(t);
        s2.setTexture(t);
        s1.setPosition(x, y);
        s2.setPosition(x, y-1345);
        window.draw(s1);
        window.draw(s2);
        if (y-1345 > 0)
        {
            k = 0;
        }
        
        //рисуем главную машинку//
        sf::Image im; 
        im.loadFromFile("car0.png");
        im.createMaskFromColor(sf::Color(0, 0, 0));
        sf::Texture t0;
        t0.loadFromImage(im);
        sf::Sprite s3;
        s3.setTexture(t0);
        s3.scale(0.33f, 0.33);
        s3.setPosition(x_car, y_car);
        
        window.draw(s3);

        //рисуем остальные машинки//
        sf::Image ims1; 
        ims1.loadFromFile("car1.png");
        ims1.createMaskFromColor(sf::Color(0, 0, 0));
        sf::Texture t1;
        t1.loadFromImage(ims1);
        sf::Sprite s4;
        s4.setTexture(t1);
        s4.scale(0.55f, 0.60);

        sf::Image ims2; 
        ims2.loadFromFile("car2.png");
        ims2.createMaskFromColor(sf::Color(0, 0, 0));
        sf::Texture t2;
        t2.loadFromImage(ims2);
        sf::Sprite s5;
        s5.setTexture(t2);
        s5.scale(0.60f, 0.60);
        for (int i = 0; i < 40; i++)
        {   
            if (y_cars[i]>-350 and y_cars[i]<1350)
            {
                if (r[i] == 1)
                {
                    s4.setPosition(x_cars[i], y_cars[i]);
                    window.draw(s4); 
                }
                else
                {
                    s5.setPosition(x_cars[i]-30, y_cars[i]);
                    window.draw(s5);
                }   
            }
        }

        //изменяем положение машинки кнопками право-лево//

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			vx_car = -1200;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			vx_car = 1200;
		}


        while (window.pollEvent(event))
        {
            if ((event.type == sf::Event::Closed) || (event.key.code == sf::Keyboard::Escape))
            {
                window.close();
                break;
            }
        }
        window.display();
    }
    return 0;
}