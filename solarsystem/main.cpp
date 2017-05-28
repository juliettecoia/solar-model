//sources for planetary information: https://nssdc.gsfc.nasa.gov/planetary/factsheet/
//mass: (in 10^24 kg)
//distance from sun: (in 10^6 km)

#include <iostream>
#include <math.h>
#include <time.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"

using namespace std;
using namespace sf;

int main()
{
    srand(time(NULL));
    
    RenderWindow window(VideoMode(600, 600), "SFML window");
    window.setFramerateLimit(60);

    // dimension vectors and input data
    vector<double>mass = {1988500e+24, 0.330e+24, 4.87e+24, 5.97e+24, 0.642e+24, 1898e+24, 568e+24, 86.8e+24, 102e+24, 0.0146e+24};
    vector<double>distance = {0.001, 57.9e+9, 108.2e+9, 149.6e+9, 227.9e+9, 778.6e+9, 1433.5e+9, 2872.5e+9, 4495.1e+9, 5906.4e+9};
    
    vector<float>radius;

    double pi = 3.141592653589;
    
    //coordinates before being scaled to the screen
    vector<double>xcoordinate;
    vector<double>ycoordinate;
    
    vector<double>xvelocity;
    vector<double>yvelocity;
    vector<double>orbitalVelocity = {0.00e+3, 47.4e+3, 35.0e+3, 29.8e+3, 24.1e+3, 13.1e+3, 9.7e+3, 6.8e+3, 5.4e+3, 4.70e+3};
    
    vector<double>F= {1,1,1,1,1,1,1,1,1,1};
    vector<double>Fx= {1,1,1,1,1,1,1,1,1,1};
    vector<double>Fy= {1,1,1,1,1,1,1,1,1,1};
    vector<double>deltax= {1,1,1,1,1,1,1,1,1,1};
    vector<double>deltay= {1,1,1,1,1,1,1,1,1,1};
    
    vector<CircleShape>planet;
    
    //push back CircleShapes into vector
    for (int i = 0; i < 10; i++)
    {
        radius.push_back(0/mass[i]);
        CircleShape circle (radius[i]);
        planet.push_back(circle);
    }
    
    planet[0].setPosition(300,300);
    xcoordinate.push_back(0.00);
    ycoordinate.push_back(0.00);
    xvelocity.push_back(0.00);
    yvelocity.push_back((0.00));
    double G = 6.67e-11;
    double dt = 400000;
    double force = 1;
    double forcex = 1;
    double forcey= 1;
    double Roi= 1;
    
    double A = (300/((6500e+9)+300)); //(w/2) / (actual dist to pluto + width/2)
    double B = (300); //width/2
    //double C = 1000;
    //double D = 2.519e-10;
    

    //this started at  0... but the sun does not need to move, should be at the center of the screen
    //planets in random initial positions
    for (int i = 1; i < 10; i++)
    {
        int range = rand()%6238; //random number between 1 and 6238 (2pi)
        float theta = (range / 1000.f); //divide number by 1000 to convert to double'
        
        xcoordinate.push_back(distance[i]*cos(theta)); //break down distance to components x and y
        ycoordinate.push_back(distance[i]*sin(theta));
        
        xvelocity.push_back(orbitalVelocity[i]*cos(theta+pi/2));
        yvelocity.push_back(orbitalVelocity[i]*sin(theta+pi/2));
        
        cout << xcoordinate[i] << " and " << ycoordinate[i] << endl;
    }
    for (int i = 0; i < 10; i++)
    {
        cout << i << ": " << B+(A*xcoordinate[i]) << " and " << B+(A*ycoordinate[i]) << endl;
    }
    
    //setting the colors of all the radius
    planet[0].setFillColor(Color::Yellow);
    planet[1].setFillColor(Color::Magenta);
    planet[2].setFillColor(Color::White);
    planet[3].setFillColor(Color::Blue);
    planet[4].setFillColor(Color::Red);
    planet[5].setFillColor(Color::Cyan);
    planet[6].setFillColor(Color::White);
    planet[7].setFillColor(Color::Green);
    planet[8].setFillColor(Color::Blue);
    planet[9].setFillColor(Color::Magenta);

    Font font;
    if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
        return EXIT_FAILURE;
    }
    Text text("Solar System Stimulation", font, 18);
    text.setFillColor(Color::White);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed) {
                window.close();
            }
        
        }
        // start at one?
        for (int i = 1; i < 10; i++)
        {
            Roi = sqrt(((xcoordinate[0]-xcoordinate[i])*(xcoordinate[0]-xcoordinate[i]))+((ycoordinate[0]-ycoordinate[i])*(ycoordinate[0]-ycoordinate[i])));
            //Roi = distance[i];
            force = -1.00 * G * mass[0] * mass[i] / (Roi * Roi);
            forcex = force * (xcoordinate[i]-xcoordinate[0])/Roi;
            forcey = force * (ycoordinate[i]-ycoordinate[0])/Roi;
            
            xvelocity[i] = xvelocity[i] + forcex / mass[i] * dt;
            yvelocity[i] = yvelocity[i] + forcey / mass[i] * dt;
            
            xcoordinate[i] = xcoordinate[i] + xvelocity[i] * dt;
            ycoordinate[i] = ycoordinate[i] + yvelocity[i] * dt;
            
            planet[i].setPosition(B+(A*xcoordinate[i]),B+(A*ycoordinate[i]));
            
        //    cout << ((A+xcoordinate[i])*B) << " +  " << ((A+xcoordinate[i])*B);
            
        }
        
        
        window.clear();
        window.draw(planet[0]);
        for (int i = 1; i < 10; i++)
        {
            window.draw(planet[i]);
            
        }
        window.draw(text);
        window.display();

    }

}

