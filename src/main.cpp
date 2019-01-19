#include <iostream>
#include <SDL2/SDL.h>

const static uint16_t width = 1920 / 6; // = 320
const static uint16_t height = 1080 / 6; // = 180
const static uint16_t contentWidth = 160;
const static uint16_t contentHeight = 144;
const static uint16_t contentSpaceX = (width - contentWidth) / 2;
const static uint16_t contentSpaceY = (height - contentHeight) / 2;
const static uint16_t contentScale = 6;

using namespace std;

int main() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) != 0) {
        cout << "SDL init failed with error: " << SDL_GetError() << endl;
        exit(1337);
    }
    SDL_Window *window = SDL_CreateWindow("nana", 0, 0, width * contentScale, height * contentScale, 0);
    if (window == nullptr) {
        cout << "SDL create window failed with error: " << SDL_GetError() << endl;
        exit(1337);
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        cout << "SDL create renderer failed with error: " << SDL_GetError() << endl;
        exit(1337);
    }
    SDL_RenderSetScale(renderer, contentScale, contentScale);
    SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, width, height);
    uint32_t format;
    SDL_QueryTexture(texture, &format, nullptr, nullptr, nullptr);
    while (true) {
        uint32_t *pixels = nullptr;
        int pitch = 0;
        if (SDL_LockTexture(texture, nullptr, (void**)&pixels, &pitch) != 0) {
            cout << "SDL lock texture failed with error: " << SDL_GetError() << endl;
            exit(1337);
        }
        for (int x = contentSpaceX; x < width - contentSpaceX; x++) {
            for (int y = contentSpaceY; y < height - contentSpaceY; y++) {
                int32_t pixelPosition = y * (pitch / sizeof(unsigned int)) + x;
                uint8_t r = 0xFF;
                uint8_t g = 0xFF;
                uint8_t b = 0xFF;
                uint8_t rgb[4] = {r, g, b, 0xFF};
                uint32_t color = 0;
                memcpy(&color, rgb, sizeof(rgb));
                pixels[pixelPosition] = color;
            }
        }
        SDL_UnlockTexture(texture);
        if (SDL_RenderClear(renderer) != 0) {
            cout << "SDL render clear failed with error: " << SDL_GetError() << endl;
            exit(1337);
        }
        if (SDL_RenderCopy(renderer, texture, nullptr, nullptr) != 0) {
            cout << "SDL render clear failed with error: " << SDL_GetError() << endl;
            exit(1337);
        }
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
