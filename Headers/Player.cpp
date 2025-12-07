#include "Player.h"
#include "raylib.h"
#include "raymath.h"


void Player::loading(){
    playerTexture_idle = LoadTexture("../assets/Characters/Soldier/Soldier/Soldier-Idle.png");
    playerTexture_walk = LoadTexture("../assets/Characters/Soldier/Soldier/Soldier-Walk.png");
    playerColor = WHITE;
    playerSpeed = 240.0f;

    playerPosition = {0.0f, 0.0f};
    playerRect = {playerPosition.x, playerPosition.y, 18, 14};
    currentState = IDLE;

}

void Player::Draw(Rectangle sourceRect, Texture2D texture) const {
    const float hitboxWidth = playerRect.width;
    const float hitboxHeight = playerRect.height;
    const float frameWidth = 100.0f;
    const float frameHeight = 100.0f;

    const float offsetX = (frameWidth - hitboxWidth) / 2.0f;
    const float offsetY = (frameHeight - hitboxHeight) / 2.0f;

    Vector2 drawPosition = {playerPosition.x - offsetX,playerPosition.y - offsetY};

    DrawTextureRec(texture, sourceRect, drawPosition, playerColor);
}

void Player::Movement() {
    playerDirection = {0.0f, 0.0f};
    if (IsKeyDown(KEY_W)) playerDirection.y -= 1.0f;
    if (IsKeyDown(KEY_S)) playerDirection.y += 1.0f;
    if (IsKeyDown(KEY_A)) playerDirection.x -= 1.0f;
    if (IsKeyDown(KEY_D)) playerDirection.x += 1.0f;

    if (playerDirection.x != 0 || playerDirection.y != 0) {
        playerDirection = Vector2Normalize(playerDirection);
        currentState = WALK;
        if (playerDirection.x != 0.0f) {
            lastHorizontalDirection = (playerDirection.x > 0) ? 1.0f : -1.0f;
        }
    }
    else {
        currentState = IDLE;
        playerDirection = {0.0f, 0.0f};
    }

    playerPosition.x += playerDirection.x * playerSpeed * GetFrameTime();
    playerPosition.y += playerDirection.y * playerSpeed * GetFrameTime();

    //playerRect.x = playerPosition.x;
    //playerRect.y = playerPosition.y;
}

void Player::Boundaries() {

    playerRect.x = playerPosition.x;
    playerRect.y = playerPosition.y;
    const float worldW = 1920.0f;
    const float worldH = 1080.0f;

    if (playerRect.x < 0) {
        playerPosition.x = 0;
    }

    float rightLimit = worldW - playerRect.width;
    if (playerRect.x > rightLimit) {
        playerPosition.x = rightLimit;
    }
    if (playerRect.y < 0) {
        playerPosition.y = 0;
    }

    float downLimit = worldH - playerRect.height;
    if (playerRect.y > downLimit) {
        playerPosition.y = downLimit;
    }

    playerRect.x = playerPosition.x;
    playerRect.y = playerPosition.y;
}