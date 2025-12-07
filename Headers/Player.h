#ifndef PLAYER_H
#define PLAYER_H
#include "raylib.h"

enum PlayerState {IDLE, WALK};

struct Player {

    Texture2D playerTexture_idle;
    Texture2D playerTexture_walk;
    Color playerColor;
    float playerSpeed;
    PlayerState currentState;

    Vector2 playerPosition;
    Rectangle playerRect;
    Vector2 playerDirection;
    float lastHorizontalDirection;

    void loading();
    void Boundaries();
    void Draw(Rectangle sourceRect, Texture2D texture) const;
    void Movement();
};

#endif //PLAYER_H