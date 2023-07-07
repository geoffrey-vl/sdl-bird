#include "texture.h"
#include <SDL2/SDL_image.h>
#include "logger/logger.h"

static const char* TAG = "GAME";

Texture::Texture(const std::string& filename) :
    _filename(filename),
    _texture(nullptr),
    _size(),
    _flip(SDL_FLIP_NONE)
{
}

Texture::~Texture()
{
    unload();
}

bool Texture::load(SDL_Renderer* renderer)
{
    if (_filename.empty()) {
        Logger::error(TAG, "Texture filename empty");
        return false;
    }
    SDL_Surface* surface = IMG_Load(_filename.c_str());
    if (surface == nullptr) {
        Logger::error(TAG, "Loading surface failed: %s", SDL_GetError());
        return false;
    }
    _texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (_texture == nullptr) {
        Logger::error(TAG, "Creating texture failed: %s", SDL_GetError());
        return false;
    }

    int w, h, access;
    unsigned int format;
    SDL_QueryTexture(_texture, &format, &access, &w, &h);
    _size.w = w;
    _size.h = h;
    Logger::debug(TAG, "Created texture %s (%dx%d)", _filename.c_str(), w ,h);
    return true;
}

void Texture::unload()
{
    if (_texture) {
        SDL_DestroyTexture(_texture);
        _texture = NULL;
    }
}

void Texture::render(SDL_Renderer* renderer)
{
    SDL_RenderCopyEx(renderer, _texture, NULL, &_size, 0, 0, _flip);
}

void Texture::setX(int x)
{
    _size.x = x;
}

void Texture::setY(int y)
{
    _size.y = y;
}

void Texture::setPos(int x, int y)
{
    _size.x = x;
    _size.y = y;
}

void Texture::setWidth(int width)
{
    _size.w = width;
}

void Texture::setHeight(int height)
{
    _size.h = height;
}

void Texture::setSize(int width, int height)
{
    _size.w = width;
    _size.h = height;
}

void Texture::setFlip(SDL_RendererFlip flip)
{
    _flip = flip;
}