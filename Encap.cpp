#include "SDL.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>
using namespace std;
#include <iostream>
#include "SDL_wrapper.h"
int win_height = 1000;int win_width = 1000;

// Fonction pour dessiner un cercle
class Circle {
private:
    int xc = 200; int yc = 200; int r = 40; int vcx; int vcy; Uint8 red, green, blue;
public:
    Circle(int pos_x, int pos_y, int t_r, int speed_x, int speed_y, Uint8 r_color, Uint8 g_color, Uint8 b_color) {
        xc = pos_x, yc = pos_y, r = t_r, vcx = speed_x, vcy = speed_y, red = r_color,green = g_color, blue = b_color;
    }
    void drawCircle(SDL_Renderer* renderer) {
        SDL_SetRenderDrawColor(renderer, red, green, blue,255);
        for (int w = 0; w < r * 2; w++) {
            for (int h = 0; h < r * 2; h++) {
                int dcx = r - w;  // distance horizontale au centre
                int dcy = r - h;  // distance verticale au centre
                if ((dcx * dcx + dcy * dcy) <= (r * r)) {
                    SDL_RenderDrawPoint(renderer, xc + dcx, yc + dcy);
                }
            }
        }
    }

    void deplacement_cercle(int win_width, int win_height) {

           xc += vcx;
           yc += vcy;

        // Collision cercle 1 avec les bords de la fenêtre
        if (xc - r <= 0 || xc + r >= win_width) vcx = -vcx;
        if (yc - r <= 0 || yc + r >= win_height) vcy = -vcy;
    }

        // Fonction pour vérifier la collision entre deux cercles
    bool checkCollision(const Circle& other) const{
        // Calcul de la distance entre les centres des deux cercles
        int dx = other.xc - xc;
        int dy = other.yc - yc;
        int distanceSquared = dx * dx + dy * dy; // Distance au carré

        int sumRadii = r + other.r; // Somme des rayons
        return distanceSquared <= (sumRadii * sumRadii);  // Vérification collision
    }
    void inverser_vitesse() {
        vcx = -vcx;
        vcy = -vcy;
    }

};

    bool isOverlapping(const Circle& newCircle, const vector<Circle>& circles) {
        for (const auto& circle : circles) {
            if (newCircle.checkCollision(circle)) {
                return true;  // Il y a une collision
            }
        }
        return false;  // Pas de collision
    }

int main(int argc, char* argv[]) {

    SDLWrapper sdlApp("Projet encapsulation Cohen Salomon", win_width, win_height);

    //Circle circle_1(200, 200, 40, 5, 3, 255, 255, 0);
    //Circle circle_2(400, 400, 40, -4, -2, 0, 0, 255);

    vector<Circle> circles;

    int frame_count = 0;

    // Boucle principale pour garder la fenêtre ouverte
    while (sdlApp.running()) {
        if (!sdlApp.processEvents()) break;
        
        int win_width, win_height;
        sdlApp.getWindowSize(win_width, win_height);
        
        //random
        if (/*sdlApp.running()*/ frame_count % 30 == 0) {
            int random_radius = rand() % 25 + 10;
            int random_x, random_y, random_vx, random_vy;
            Uint8 random_r, random_g, random_b;
            bool positionValide = false;
            while (!positionValide) {
                random_x = rand() % (win_width - 2 * random_radius) + random_radius;
                random_y = rand() % (win_width - 2 * random_radius) + random_radius;
                random_vx = rand() % 7 - 3;
                random_vy = rand() % 7 - 3;
                //random color
                random_r = rand() % 256;
                random_g = rand() % 256;
                random_b = rand() % 256;
                Circle newCircle(random_x, random_y, random_radius, random_vx, random_vy, random_r, random_g, random_b);

                if (!isOverlapping(newCircle, circles)) {
                    circles.push_back(newCircle);
                    positionValide = true;
                }

                //circles.push_back(Circle(random_x, random_y, random_radius, random_vx, random_vy, random_r, random_g, random_b));

            }
            

        }
        sdlApp.clearScreen(0, 0, 0);

        for (size_t i = 0; i < circles.size(); i++) {
            circles[i].deplacement_cercle(win_width, win_height);
            circles[i].drawCircle(sdlApp.getRenderer());
            // Vérification des collisions avec les autres cercles
            for (size_t j = i + 1; j < circles.size(); j++) {
                if (circles[i].checkCollision(circles[j])) {
                    circles[i].inverser_vitesse();
                    circles[j].inverser_vitesse();
                }
            }
        }
        sdlApp.updateFPS();
        sdlApp.renderFPS();

        sdlApp.updateScreen();
        // Attendre un court moment (10ms)
        frame_count++;
    }
    return 0;   
}
