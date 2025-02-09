#include "SDL.h"
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <cstdlib>
using namespace std;
#include "SDL_wrapper.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_sdl2.h"
#include "ImGui/imgui_impl_sdlrenderer2.h"

int win_height = 1080;
int win_width = 1920;

class Circle {
public:
    int xc, yc, r, vcx, vcy, id;
    Uint8 red, green, blue;

    Circle(int pos_x, int pos_y, int t_r, int speed_x, int speed_y, Uint8 r_color, Uint8 g_color, Uint8 b_color, int circle_id)
        : xc(pos_x), yc(pos_y), r(t_r), vcx(speed_x), vcy(speed_y), red(r_color), green(g_color), blue(b_color), id(circle_id) {}

    void drawCircle(SDL_Renderer* renderer) {
        SDL_SetRenderDrawColor(renderer, red, green, blue, 255);
        for (int w = 0; w < r * 2; w++) {
            for (int h = 0; h < r * 2; h++) {
                int dx = r - w;
                int dy = r - h;
                if ((dx * dx + dy * dy) <= (r * r)) {
                    SDL_RenderDrawPoint(renderer, xc + dx, yc + dy);
                }
            }
        }
    }

    void deplacement_cercle(int win_width, int win_height) {
        xc += vcx;
        yc += vcy;
        if (xc - r <= 0 || xc + r >= win_width) vcx = -vcx;
        if (yc - r <= 0 || yc + r >= win_height) vcy = -vcy;
    }
};

int main(int argc, char* argv[]) {
    SDLWrapper sdlApp("Project : Encapsulation circles rendering & collisions Cohen Salomon", win_width, win_height);
    vector<Circle> circles;
    int frame_count = 0;
    int selectedCircleIndex = -1;
    int nextCircleId = 0;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui_ImplSDL2_InitForSDLRenderer(sdlApp.get_fenetre(), sdlApp.getRenderer());
    ImGui_ImplSDLRenderer2_Init(sdlApp.getRenderer());

    while (sdlApp.running()) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)) {
                return 0;
            }
        }

        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("UI Window");
        ImGui::Text("Modifier un cercle");

        if (!circles.empty()) {
            vector<string> circleLabels;
            for (const auto& circle : circles) {
                circleLabels.push_back("Cercle " + to_string(circle.id));
            }
            vector<const char*> circleLabelPtrs;
            for (const auto& label : circleLabels) {
                circleLabelPtrs.push_back(label.c_str());
            }
            ImGui::Combo("Choisir un cercle", &selectedCircleIndex, circleLabelPtrs.data(), circles.size());
        }

        if (selectedCircleIndex >= 0 && selectedCircleIndex < circles.size()) {
            Circle& selectedCircle = circles[selectedCircleIndex];
            ImGui::SliderInt("Taille", &selectedCircle.r, 5, 100);
            ImGui::SliderInt("Vitesse X", &selectedCircle.vcx, -10, 10);
            ImGui::SliderInt("Vitesse Y", &selectedCircle.vcy, -10, 10);
            float color[3] = { selectedCircle.red / 255.0f, selectedCircle.green / 255.0f, selectedCircle.blue / 255.0f };
            if (ImGui::ColorEdit3("Couleur", color)) {
                selectedCircle.red = static_cast<Uint8>(color[0] * 255);
                selectedCircle.green = static_cast<Uint8>(color[1] * 255);
                selectedCircle.blue = static_cast<Uint8>(color[2] * 255);
            }
        }

        ImGui::End();

        int win_width, win_height;
        sdlApp.getWindowSize(win_width, win_height);

        if (frame_count % 40 == 0) {
            int random_radius = rand() % 20 + 10;
            int random_x = rand() % (win_width - 2 * random_radius) + random_radius;
            int random_y = rand() % (win_height - 2 * random_radius) + random_radius;
            int random_vx = rand() % 8 - 2;
            int random_vy = rand() % 8 - 2;
            Uint8 random_r = rand() % 256;
            Uint8 random_g = rand() % 256;
            Uint8 random_b = rand() % 256;
            circles.emplace_back(random_x, random_y, random_radius, random_vx, random_vy, random_r, random_g, random_b, nextCircleId++);
        }

        sdlApp.clearScreen(0, 0, 0);
        for (auto& circle : circles) {
            circle.deplacement_cercle(win_width, win_height);
            circle.drawCircle(sdlApp.getRenderer());
        }
        sdlApp.updateFPS();
        sdlApp.renderFPS();

        ImGui::Render();
        ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), sdlApp.getRenderer());

        sdlApp.updateScreen();
        frame_count++;
    }

    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    return 0;
}
