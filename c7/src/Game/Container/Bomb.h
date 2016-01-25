#ifndef BAKUDAN_GAME_CONTAINER_BOMB_H_
#define BAKUDAN_GAME_CONTAINER_BOMB_H_
#include <vector>
#include "Game/Object/Bomb.h"
#include "Rect.h"

class Point;
namespace Game { class Map; }
namespace Game { namespace Container { class Wall; } }
namespace Game { namespace Object { class Enemy; } }
namespace Game { namespace Object { class Player; } }
namespace Image { class Sprite; }

namespace Game
{

namespace Container
{

class Bomb
{
private:
    std::vector< Object::Bomb* > bombs_;
    Rect< double > central_;
    Rect< double > horizontal_;
    Rect< double > vertical_;

public:
    Bomb(int max_count, const Image::Sprite& image);
    ~Bomb();
    void burn_out_walls_if_explosion_reaches(   unsigned now,
                                                const Map& map,
                                                Container::Wall* walls) const;
    int count(int player_index) const;
    void chain_explosion(unsigned now);
    void clean_up_all_garbage(Map* map);
    void create_one(    const Point& destination,
                        int power,
                        int player_index,
                        unsigned now,
                        Map* map);
    void draw(const Image::Sprite& image) const;
    void kill_enemies_if_in_explosion(  unsigned now,
                                        int enemies_size,
                                        Object::Enemy* enemies) const;
    void kill_player_if_in_explosion(   unsigned now,
                                        Object::Player* player) const;
    void pause(unsigned now);
    void resume(unsigned now);
    void tick(unsigned now, const Map& map);
};

} // namespace Container

} // namespace Game

#endif
