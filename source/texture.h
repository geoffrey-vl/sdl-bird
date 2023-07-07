#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <SDL2/SDL.h>

class Texture
{
public:
    Texture(const std::string& filename);
    ~Texture();

    bool load(SDL_Renderer* renderer);
    void unload();
    void render(SDL_Renderer* renderer);
    void setX(int x);
    void setY(int y);
    void setPos(int x, int y);
    void setWidth(int width);
    void setHeight(int height);
    void setSize(int width, int height);
    void setFlip(SDL_RendererFlip flip);

private:
    std::string _filename;
    SDL_Texture* _texture;
    SDL_Rect _size;
    SDL_RendererFlip _flip;
};

#endif // TEXTURE_H