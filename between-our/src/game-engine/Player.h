#pragma once
#include "types.h"
#include "InteractableWorldObject.h"
#include "string"
#include "PolyTexture.h"
#include "ColorSquare.h"
#include "Texture.h"

using namespace std;

namespace gameEngine {
    enum PlayerColor {
        RED,
        GREEN,
        BLUE,
        PURPLE,
        CYAN,
        PINK,
        DARK_GREEN,
        DARK_BLUE,
        ORANGE
    };

    Texture* createAlivePlayerTexture(PlayerColor color);
    Texture* createWalkingPlayerTexture(PlayerColor color);
    Texture* createDeadPlayerTexture(PlayerColor color);

    class Player : public InteractableWorldObject {
        private:
            PlayerColor color;
            string name;
            struct {
                bool up, down, left, right;
            } moving;
            float moveSpeed = 200;
            bool dead = false;
            void onStartMoving();
            void onStopMoving();
        public:
            Player();
            Player(string name);
            void gameTick(double delta);
            PlayerColor getPlayerColor();
            void setPlayerColor(PlayerColor color);
            string getName();
            void setName(string name);
            void setMovingUp(bool b);
            void setMovingDown(bool b);
            void setMovingLeft(bool b);
            void setMovingRight(bool b);
            float getMoveSpeed();
            void setMoveSpeed(float s);
            void kill();
            void canKill(Player* p);
            void attemptToKill(Player* p);
            bool isDead();
            bool isInRange(InteractableWorldObject* w);
            void onInRange();
            void interact();
    };
};