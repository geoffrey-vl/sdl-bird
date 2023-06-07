#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace Const {

static constexpr int CGA_WIDTH = 320;
static constexpr int CGA_HEIGHT = 200;

static constexpr int GAME_WIDTH = CGA_WIDTH*2;
static constexpr int GAME_HEIGHT = CGA_HEIGHT*2;
static constexpr int NR_OF_BOXES = 28;
static constexpr int OBJ_WIDTH = 640/10;
static constexpr int OBJ_HEIGHT = OBJ_WIDTH;

const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

};

#endif // CONSTANTS_H