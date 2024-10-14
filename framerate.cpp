//#include <SDL_ttf.h>
//#include <string>
//#include <iostream>
//using namespace std;
//// Fonction pour rendre du texte en SDL
//SDL_Texture* RenderText(const  string& message, const  string& fontFile, SDL_Color color, int fontSize, SDL_Renderer* renderer) {
//    TTF_Font* font = TTF_OpenFont(fontFile.c_str(), fontSize);
//    if (!font) {
//         cerr << "Failed to load font: " << TTF_GetError() <<  endl;
//        return nullptr;
//    }
//    SDL_Surface* surface = TTF_RenderText_Solid(font, message.c_str(), color);
//    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
//    SDL_FreeSurface(surface);
//    TTF_CloseFont(font);
//    return texture;
//}
//
//// Fonction pour calculer les FPS
//float calculateFPS(Uint32& lastFrameTime, int& frameCount) {
//    Uint32 currentTime = SDL_GetTicks();
//    frameCount++;
//
//    if (currentTime - lastFrameTime >= 1000) {
//        float fps = frameCount / ((currentTime - lastFrameTime) / 1000.0f);
//        lastFrameTime = currentTime;
//        frameCount = 0;
//        return fps;
//    }
//    return -1.0f;  // Retourne -1 si moins d'une seconde est passée (pour ne pas recréer inutilement la texture)
//}
//
//int main(int argc, char* argv[]) {
//    // Initialisation de SDL et SDL_ttf
//    if (SDL_Init(SDL_INIT_VIDEO) != 0 || TTF_Init() != 0) {
//         cerr << "Error initializing SDL or TTF: " << SDL_GetError() <<  endl;
//        return -1;
//    }
//
//    SDL_Window* window = SDL_CreateWindow("SDL2 FPS Counter", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
//    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
//
//    if (!window || !renderer) {
//         cerr << "Error creating window or renderer: " << SDL_GetError() <<  endl;
//        return -1;
//    }
//
//    // Variables pour FPS
//    Uint32 lastFrameTime = SDL_GetTicks();
//    int frameCount = 0;
//    float fps = 0.0f;
//     string fontPath = "./impact.ttf";
//
//    // Texture pour les FPS
//    SDL_Texture* fpsTexture = nullptr;
//    int texW = 0, texH = 0;
//
//    bool running = true;
//    SDL_Event event;
//
//    while (running) {
//        while (SDL_PollEvent(&event)) {
//            if (event.type == SDL_QUIT) {
//                running = false;
//            }
//        }
//
//        // Calcul des FPS
//        float newFPS = calculateFPS(lastFrameTime, frameCount);
//
//        // Si les FPS changent (toutes les secondes), recréer la texture
//        if (newFPS >= 0) {
//            fps = newFPS;
//            if (fpsTexture) {
//                SDL_DestroyTexture(fpsTexture);  // Détruire l'ancienne texture
//            }
//
//            SDL_Color white = { 255, 255, 255, 255 };  // Couleur blanche
//            fpsTexture = RenderText("FPS: " +  to_string(static_cast<int>(fps)), fontPath, white, 24, renderer);
//
//            if (fpsTexture) {
//                SDL_QueryTexture(fpsTexture, nullptr, nullptr, &texW, &texH);
//            }
//        }
//
//        // Efface l'écran
//        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Couleur noire
//        SDL_RenderClear(renderer);
//
//        // Affichage de la texture FPS (si elle existe)
//        if (fpsTexture) {
//            SDL_Rect dstRect = { 10, 10, texW, texH };  // Position dans le coin supérieur gauche
//            SDL_RenderCopy(renderer, fpsTexture, nullptr, &dstRect);
//        }
//
//        // Affiche le rendu final
//        SDL_RenderPresent(renderer);
//
//        // Limiter la vitesse de la boucle pour éviter de consommer trop de ressources
//        SDL_Delay(15.5);  // 16ms = environ 60 FPS
//    }
//
//    // Nettoyage
//    SDL_DestroyTexture(fpsTexture);
//    SDL_DestroyRenderer(renderer);
//    SDL_DestroyWindow(window);
//    TTF_Quit();
//    SDL_Quit();
//
//    return 0;
//}
//
////FPSCounter fpsCounter(renderer, "./impact.ttf", 24);
////fpsCounter.updateFPS();
////fpsCounter.render();
