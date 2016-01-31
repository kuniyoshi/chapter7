#ifndef BAKUDAN_STATE_H_
#define BAKUDAN_STATE_H_
#include "Constants.h"
#include "Controller/Game.h"

namespace Game { class Map; }
namespace Game { namespace Container { class Bomb; } }
namespace Game { namespace Container { class Item; } }
namespace Game { namespace Container { class Wall; } }
namespace Game { namespace Object { class Enemy; } }
namespace Game { namespace Object { class Player; } }
namespace Image { class Sprite; }

class State
{
public:
    enum ObjectImage
    {
        OBJECT_IMAGE_PLAYER1 = 0,
        OBJECT_IMAGE_PLAYER2,
        OBJECT_IMAGE_BOMB_ITEM,
        OBJECT_IMAGE_SOTRM_ITEM,
        OBJECT_IMAGE_HORIZONTAL_STORM,
        OBJECT_IMAGE_VERTICAL_STORM,
        OBJECT_IMAGE_ENEMY,
        OBJECT_IMAGE_BLOCK,
        OBJECT_IMAGE_WALL,
        OBJECT_IMAGE_FLOOR,
        OBJECT_IMAGE_BOMB,
        OBJECT_IMAGE_CROSS_STORM,
        OBJECT_IMAGE_BURNING_WALL = 12,
        OBJECT_IMAGE_NOTHING,
    };

private:
    Constants::PlayMode play_mode_;
    Game::Container::Bomb* bombs_;
    Game::Container::Item* items_;
    Game::Container::Wall* walls_;
    Game::Map* map_;
    Game::Object::Enemy* enemies_;
    Game::Object::Player* player1p_;
    Game::Object::Player* player2p_;
    Image::Sprite* object_image_;

public:
    State();
    ~State();
    void load(Constants::PlayMode play_mode);
    void update();
    void draw() const;
    void pause();
    void resume();
    bool does_game_over() const;
    bool does_game_failure() const;
};

#endif
