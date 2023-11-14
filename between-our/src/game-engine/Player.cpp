#include "Player.h"
#include "types.h"
#include "InteractableWorldObject.h"
#include "string"
#include <iostream>
#include "ui/uiHeader.h"
#include "PolyTexture.h"
#include "Rectangle.h"
#include "ColorSquare.h"
#include "Texture.h"
#include "AnimatedTexture.h"

using namespace std;

namespace gameEngine {
    void Player::onStartMoving()
    {
        setTexture(createWalkingPlayerTexture(color));
    }
    void Player::onStopMoving()
    {
        setTexture(createAlivePlayerTexture(color));
    }
    Player::Player() : InteractableWorldObject() {
        Player("");
    }

    Player::Player(string name) : InteractableWorldObject() {
        setPlayerColor(RED);
        setName(name);
        setSize(Dimensionf(40, 50));
    }

    void Player::gameTick(double delta) {
        Dimensionf moved;
        if (moving.up) moved.height += moveSpeed * delta;
        if (moving.down) moved.height -= moveSpeed * delta;
        if (moving.left) moved.width -= moveSpeed * delta;
        if (moving.right) moved.width += moveSpeed * delta;
        move(moved);
    }

    PlayerColor Player::getPlayerColor() {
        return color;
    }

    void Player::setPlayerColor(PlayerColor color) {
        this->color = color;
        setTexture(createAlivePlayerTexture(color));
    }

    string Player::getName() {
        return name;
    }

    void Player::setName(string name) {
        this->name = name;
        setLabel(name);
    }

    void Player::setMovingUp(bool b) {
        if (dead) return;
        
        moving.up = b;

        if (moving.down || moving.left || moving.right) return;

        bool flipped = getTexture()->isFlipped();
        if (b) setTexture(createWalkingPlayerTexture(color));
        else setTexture(createAlivePlayerTexture(color));
        getTexture()->setFlipped(flipped);
    }
    void Player::setMovingDown(bool b) {
        if (dead) return;
        
        moving.down = b;

        if (moving.up || moving.left || moving.right) return;

        bool flipped = getTexture()->isFlipped();
        if (b) setTexture(createWalkingPlayerTexture(color));
        else setTexture(createAlivePlayerTexture(color));
        getTexture()->setFlipped(flipped);
    }
    void Player::setMovingLeft(bool b) {
        if (dead) return;

        moving.left = b;
        if (b) getTexture()->setFlipped(true);

        if (moving.down || moving.up || moving.right) return;

        if (b) setTexture(createWalkingPlayerTexture(color));
        else setTexture(createAlivePlayerTexture(color));
        getTexture()->setFlipped(true);
    }
    void Player::setMovingRight(bool b) {
        if (dead) return;

        moving.right = b;
        if (b) getTexture()->setFlipped(false);

        if (moving.down || moving.left || moving.up) return;

        if (b) setTexture(createWalkingPlayerTexture(color));
        else setTexture(createAlivePlayerTexture(color));
    }

    float Player::getMoveSpeed() {
        return moveSpeed;
    }

    void Player::setMoveSpeed(float s) {
        moveSpeed = s;
    }

    void Player::kill() {
        dead = true;
        setTexture(createDeadPlayerTexture(color));
        moving.up = false, moving.down = false, moving.left = false, moving.right = false;
    }

    void Player::canKill(Player* p) {

    }

    void Player::attemptToKill(Player* p) {
        if (p->isDead()) return;

        p->kill();
        float dx = p->getPosition().x - position.x;
        float dy = p->getPosition().y - position.y;
        move(dx * 2, dy * 2);
    }

    bool Player::isDead() {
        return dead;
    }

    bool Player::isInRange(InteractableWorldObject* w) {
        BoundingBox pBounds = this->getBoundingBox();
        BoundingBox wBounds = w->getBoundingBox();
        float interactRange = w->getInteractRange();

        return wBounds.left - interactRange < pBounds.right
            && wBounds.right + interactRange > pBounds.left
            && wBounds.bottom - interactRange < pBounds.top
            && wBounds.top + interactRange > pBounds.bottom;
    }

    void Player::onInRange() {

    }

    void Player::interact() {

    }

    Color3f getColor3f(PlayerColor c) {
        Color3f color3f;

        switch (c) {
            case RED:
                color3f = Color3f(1, 0, 0);
                break;
            case GREEN:
                color3f = Color3f(0, 1, 0);
                break;
            case BLUE:
                color3f = Color3f(0, 0, 1);
                break;
            case PURPLE:
                color3f = Color3f(1, 0, 1);
                break;
            case CYAN:
                color3f = Color3f(0, 1, 1);
                break;
            case PINK:
                color3f = Color3f(1, 0.5, 0.5);
                break;
            case DARK_GREEN:
                color3f = Color3f(0, 0.5, 0);
                break;
            case DARK_BLUE:
                color3f = Color3f(0, 0, 0.5);
                break;
            case ORANGE:
                color3f = Color3f(1, 0.5, 0);
                break;
        }

        return color3f;
    }

    Texture* createAlivePlayerTexture(PlayerColor color)
    {
        return new ColorSquare(Color3f(0, 0, 0));

        PolyTexture* texture = new PolyTexture();
        Color3f color3f = getColor3f(color);

        texture->addPoly(new Rectangle(Pointf(0, 0.15), Dimensionf(1, 0.85), color3f));
        texture->addPoly(new Rectangle(Pointf(0, 0), Dimensionf(0.4, 0.15), color3f));
        texture->addPoly(new Rectangle(Pointf(0.6, 0), Dimensionf(0.4, 0.15), color3f));
        texture->addPoly(new Rectangle(Pointf(-0.2, 0.25), Dimensionf(0.2, 0.5), color3f));
        texture->addPoly(new Rectangle(Pointf(0.25, 0.5), Dimensionf(0.75, 0.25), Color3f(0.5, 0.5, 0.5)));

        return texture;
    }
    Texture* createWalkingPlayerTexture(PlayerColor color)
    {
        return new ColorSquare(Color3f(0, 0, 0));

        AnimatedTexture* texture = new AnimatedTexture();
        PolyTexture* t1 = new PolyTexture(); 
        PolyTexture* t2 = new PolyTexture();
        Color3f color3f = getColor3f(color);

        t1->addPoly(new Rectangle(Pointf(0, 0.15), Dimensionf(1, 0.85), color3f));
        t1->addPoly(new Rectangle(Pointf(0, 0.05), Dimensionf(0.4, 0.1), color3f));
        t1->addPoly(new Rectangle(Pointf(0.6, 0), Dimensionf(0.4, 0.15), color3f));
        t1->addPoly(new Rectangle(Pointf(-0.2, 0.25), Dimensionf(0.2, 0.5), color3f));
        t1->addPoly(new Rectangle(Pointf(0.25, 0.5), Dimensionf(0.75, 0.25), Color3f(0.5, 0.5, 0.5)));

        t2->addPoly(new Rectangle(Pointf(0, 0.15 + 0.05), Dimensionf(1, 0.85), color3f));
        t2->addPoly(new Rectangle(Pointf(0, 0), Dimensionf(0.4, 0.15 + 0.05), color3f));
        t2->addPoly(new Rectangle(Pointf(0.6, 0.05 + 0.05), Dimensionf(0.4, 0.1), color3f));
        t2->addPoly(new Rectangle(Pointf(-0.2, 0.25 + 0.05), Dimensionf(0.2, 0.5), color3f));
        t2->addPoly(new Rectangle(Pointf(0.25, 0.5 + 0.05), Dimensionf(0.75, 0.25), Color3f(0.5, 0.5, 0.5)));

        texture->addFrame(t1);
        texture->addFrame(t2);

        return texture;
    }
    Texture* createDeadPlayerTexture(PlayerColor color)
    {
        return new ColorSquare(Color3f(0, 0, 0));

        PolyTexture* texture = new PolyTexture();
        Color3f color3f = getColor3f(color);

        for (int i = 0; i < 20; i++)
            texture->addPoly(new Rectangle(Pointf((float) (rand() % 30) / 20 - 0.25, (float) (rand() % 15) / 20 - 0.32), Dimensionf((float) (rand() % 10) / 40, (float) (rand() % 10) / 40), Color3f(1, 0, 0)));
        texture->addPoly(new Rectangle(Pointf(0, 0), Dimensionf(1, 0.5), color3f));
        texture->addPoly(new Rectangle(Pointf(0.25, 0.5), Dimensionf(0.2, 0.4), Color3f(0.8, 0.8, 0.8)));
        texture->addPoly(new Rectangle(Pointf(0.13, 0.8), Dimensionf(0.2, 0.2), Color3f(0.8, 0.8, 0.8)));
        texture->addPoly(new Rectangle(Pointf(0.37, 0.8), Dimensionf(0.2, 0.2), Color3f(0.8, 0.8, 0.8)));

        return texture;
    }
}

