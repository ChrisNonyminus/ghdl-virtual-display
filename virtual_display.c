#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


int s;
typedef uint32_t uint;
SDL_Window* w;
SDL_Renderer* r;
SDL_Texture* pixmap;
SDL_Event e;

static uint xres;
static uint yres;


void sim_init(uint32_t width, uint32_t height) {
    SDL_Init(SDL_INIT_EVERYTHING);
    xres = width;
    yres = height;
    
    SDL_CreateWindowAndRenderer(xres, yres, SDL_WINDOW_OPENGL, &w, &r);
    if (w == NULL) {
       fprintf(stderr, "Cannot open display.\n");
       exit(EXIT_FAILURE);
    }
    SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
    SDL_SetWindowTitle(w, "Virtual Display");
    
    while (1) {
      SDL_PollEvent(&e);
      if (e.type == SDL_QUIT) { break; }
   }
}


void save_screenshot(int32_t *ptr, uint32_t width, uint32_t height, int id) {
    assert(ptr != NULL);
    pixmap = SDL_CreateTexture(r, SDL_GetWindowPixelFormat(w), SDL_TEXTUREACCESS_STREAMING, width, height);
    int x_pos = (xres-width)/2;
    int y_pos = (yres-height)/2;
    int p = 0;
            SDL_SetTextureUserData(pixmap, ptr);
    SDL_RenderCopy(r, pixmap, NULL, NULL);
    SDL_DestroyTexture(pixmap);
}


void sim_cleanup(void) {
    SDL_DestroyWindow(w);
}

