#include "State.h"
#include <sstream>
#include <utility>
#include "GameLib/Framework.h"
#include "Constants.h"
#include "File.h"
#include "Game/Container/Bomb.h"
#include "Game/Container/Item.h"
#include "Game/Container/Wall.h"
#include "Game/InputManager.h"
#include "Game/Map.h"
#include "Game/Object/Enemy.h"
#include "Game/Object/Player.h"
#include "Image/Sprite.h"
#include "Piece.h"
#include "Point.h"
#include "collision.h"

namespace
{

const int MapSizeWidth      = 19;
const int MapSizeHeight     = 15;
const int SpriteImageWidth  = 4;
const int SpriteImageHeight = 4;
const int EnemyCount        = 8;
const int Player1StartX     = 1;
const int Player1StartY     = 1;
const int Player2StartX     = 17;
const int Player2StartY     = 13;
const int Enemy1GroupStartX = 17;
const int Enemy1GroupStartY = 1;
const int Enemy2GroupStartX = 1;
const int Enemy2GroupStartY = 13;
const int Enemy3GroupStartX = 17;
const int Enemy3GroupStartY = 13;
const int ItemBombCount     = 3;
const int ItemBurnCount     = 3;

} // namespace -

State::State()
:   play_mode_(Constants::PlayMode1P),
    bombs_(0),
    items_(0),
    walls_(0),
    map_(0),
    enemies_(0),
    player1p_(0), player2p_(0),
    object_image_(0)
{} // load will initialize all

State::~State()
{
    SAFE_DELETE(bombs_);
    SAFE_DELETE(items_);
    SAFE_DELETE(walls_);
    SAFE_DELETE(map_);
    SAFE_DELETE_ARRAY(enemies_);
    SAFE_DELETE(player1p_);
    SAFE_DELETE(player2p_);
    SAFE_DELETE(object_image_);
}

void State::load(Constants::PlayMode play_mode)
{
    play_mode_ = play_mode;

    ASSERT(!object_image_);
    object_image_ = new Image::Sprite(  File("data/image/BakudanBitoImage.dds"),
                                        SpriteImageWidth,
                                        SpriteImageHeight);

    ASSERT(!map_);
    map_ = new Game::Map(MapSizeWidth, MapSizeHeight);
    map_->load();
    map_->draw(*object_image_);

    ASSERT(!player1p_);
    player1p_ = new Game::Object::Player(   0,
                                            Point(  Player1StartX,
                                                    Player1StartY),
                                            *object_image_);

    if (play_mode_ == Constants::PlayMode2P)
    {
        ASSERT(!player2p_);
        player2p_ = new Game::Object::Player(   1,
                                                Point(  Player2StartX,
                                                        Player2StartY),
                                                *object_image_);
    }

    {
        ASSERT(!walls_);
        Point player1_point = player1p_->current_point();
        Point player2_point = player2p_
        ? player2p_->current_point()
        : player1p_->current_point();

        walls_ = new Game::Container::Wall(player1_point, player2_point, map_);
        walls_->draw(*object_image_);
    }

    {
        enemies_ = new Game::Object::Enemy[EnemyCount];

        Point* group_points = new Point[3 - !player2p_];
        group_points[0].set_xy(Enemy1GroupStartX, Enemy1GroupStartY);
        group_points[1].set_xy(Enemy2GroupStartX, Enemy2GroupStartY);

        if (player2p_)
        {
            group_points[2].set_xy(Enemy3GroupStartX, Enemy3GroupStartY);
        }

        Point* enemy_points = new Point[EnemyCount];
        Game::Object::Enemy::place_enemies( *map_,
                                            3 - !player2p_,
                                            group_points,
                                            EnemyCount,
                                            enemy_points);
        Game::Object::Enemy::setup_enemies( EnemyCount,
                                            enemy_points,
                                            *object_image_,
                                            enemies_);
        SAFE_DELETE_ARRAY(enemy_points);
        SAFE_DELETE_ARRAY(group_points);
    }

    {
        ASSERT(!bombs_);
        int max_bombs = Game::Object::Player::MaxBombs;
        bombs_ = new Game::Container::Bomb( (2 - !player2p_) * max_bombs,
                                            *object_image_);
    }

    {
        ASSERT(!items_);
        items_ = new Game::Container::Item( ItemBombCount,
                                            ItemBurnCount,
                                            *walls_);
    }
}

namespace
{

void prepare_for_each_enemies(Game::Object::Enemy* enemies)
{
    for (int i = 0; i < EnemyCount; ++i)
    {
        enemies[i].prepare();
    }
}

void set_each_enemies_direction(    const Game::Map& map,
                                    Game::Object::Enemy* enemies,
                                    unsigned now)
{
    for (int i = 0; i < EnemyCount; ++i)
    {
        if (enemies[i].did_die())
        {
            continue;
        }

        enemies[i].set_direction(map, EnemyCount, enemies, i, now);
    }
}

void stop_each_enemies_if_collision_occured(Game::Object::Enemy* enemies)
{
    bool can_skip_check[EnemyCount];

    for (int i = 0; i < EnemyCount; ++i)
    {
        can_skip_check[i] = false;
    }

    for (int i = 0; i < EnemyCount - 1; ++i)
    {
        if (can_skip_check[i])
        {
            continue;
        }

        if (enemies[i].did_die())
        {
            can_skip_check[i] = true;
            continue;
        }

        for (int j = i + 1; j < EnemyCount; ++j)
        {
            if (can_skip_check[j])
            {
                continue;
            }

            if (enemies[j].did_die())
            {
                can_skip_check[j] = true;
                continue;
            }

            unsigned ms_to_collision = 0;
            bool will_collision_occur
            = collision::set_ms_at_collision_occur( enemies[i].make_piece(),
                                                    enemies[j].make_piece(),
                                                    &ms_to_collision);

            if (will_collision_occur)
            {
                enemies[i].set_direction_at_collision();
                enemies[i].stop_after(ms_to_collision);

                enemies[j].set_direction_at_collision();
                enemies[j].stop_after(ms_to_collision);

                can_skip_check[j] = true;
            }
        }

        can_skip_check[i] = true;
    }
}

void tick_for_each_enemies(unsigned now, Game::Object::Enemy* enemies)
{
    for (int i = 0; i < EnemyCount; ++i)
    {
        enemies[i].tick(now);
    }
}

} // namespace -

void State::update()
{
    GameLib::Framework f = GameLib::Framework::instance();
    unsigned now = f.time();
    std::stringstream ss;
    ss << "FR: ";
    ss << f.frameRate();
    f.drawDebugString(0, 0, ss.str().c_str(), 0xff000000);

    player1p_->prepare();

    if (player2p_)
    {
        player2p_->prepare();
    }

    prepare_for_each_enemies(enemies_);

    bombs_->clean_up_all_garbage(map_);
    walls_->clean_up_all_garbage(map_);
    items_->clean_up_all_garbage();

    Game::InputManager player1_input = Game::InputManager::user1();

    Point player1p_point = player1p_->point();
    Point player1p_direction(0, 0);

    if (player1_input.is_left() && !map_->can_not_invade(Point(player1p_point, -1, 0)))
    {
        player1p_direction.set_xy(-1, 0);
    }
    else if (player1_input.is_right() && !map_->can_not_invade(Point(player1p_point, 1, 0)))
    {
        player1p_direction.set_xy(1, 0);
    }
    else if (player1_input.is_top() && !map_->can_not_invade(Point(player1p_point, 0, -1)))
    {
        player1p_direction.set_xy(0, -1);
    }
    else if (player1_input.is_bottom() && !map_->can_not_invade(Point(player1p_point, 0, 1)))
    {
        player1p_direction.set_xy(0, 1);
    }

    player1p_->move_to(player1p_direction, now);

    if (player2p_)
    {
        Point player2p_point = player2p_->point();
        Point player2p_direction(0, 0);

        Game::InputManager player2_input = Game::InputManager::user2();

        if (player2_input.is_left_triggered() && !map_->can_not_invade(Point(player2p_point, -1, 0)))
        {
            player2p_direction.set_xy(-1, 0);
        }
        else if (player2_input.is_right_triggered() && !map_->can_not_invade(Point(player2p_point, 0, 1)))
        {
            player2p_direction.set_xy(0, 1);
        }
        else if (player2_input.is_top_triggered() && !map_->can_not_invade(Point(player2p_point, 0, -1)))
        {
            player2p_direction.set_xy(0, -1);
        }
        else if (player2_input.is_bottom_triggered() && !map_->can_not_invade(Point(player2p_point, 1, 0)))
        {
            player2p_direction.set_xy(1, 0);
        }

        player2p_->move_to(player2p_direction, now);
    }

    if (player1_input.is_action_triggered())
    {
        player1p_->plant_a_bomb(now, bombs_, map_);
    }

    if (player2p_ && Game::InputManager::user2().is_action_triggered())
    {
        player2p_->plant_a_bomb(now, bombs_, map_);
    }

    set_each_enemies_direction(*map_, enemies_, now);

    if (player2p_)
    {
        unsigned ms_to_collision(0);
        bool will_collision_occur
        = collision::set_ms_at_collision_occur( player1p_->make_piece(),
                                                player2p_->make_piece(),
                                                &ms_to_collision);

        if (will_collision_occur)
        {
            if (!player1p_->does_direction_open(*player2p_, ms_to_collision))
            {
                player1p_->stop_after(ms_to_collision);
            }

            if (!player2p_->does_direction_open(*player1p_, ms_to_collision))
            {
                player2p_->stop_after(ms_to_collision);
            }
        }
    }

    stop_each_enemies_if_collision_occured(enemies_);

    if (player2p_)
    {
        Piece player1_piece = player1p_->make_piece();
        Piece player2_piece = player2p_->make_piece();

        for (int i = 0; i < EnemyCount; ++i)
        {
            if (enemies_[i].did_die())
            {
                continue;
            }

            Piece enemy_piece = enemies_[i].make_piece();

            if (enemy_piece.does_overlap(player1_piece))
            {
                enemies_[i].eat(now, player1p_);
            }

            if (enemy_piece.does_overlap(player2_piece))
            {
                enemies_[i].eat(now, player2p_);
            }
        }
    }
    else
    {
        Piece player1_piece = player1p_->make_piece();

        for (int i = 0; i < EnemyCount; ++i)
        {
            if (enemies_[i].make_piece().does_overlap(player1_piece))
            {
                if (enemies_[i].did_die())
                {
                    continue;
                }

                enemies_[i].eat(now, player1p_);
            }
        }
    }

    player1p_->tick(now);

    if (player2p_)
    {
        player2p_->tick(now);
    }

    player1p_->gain_item(items_);

    if (player2p_)
    {
        player2p_->gain_item(items_);
    }

    tick_for_each_enemies(now, enemies_);

    bombs_->tick(now, *map_);
    walls_->tick(now);
    walls_->burn_wall_to_map(map_);

    bombs_->kill_enemies_if_in_explosion(now, EnemyCount, enemies_);

    bombs_->kill_player_if_in_explosion(now, player1p_);

    if (player2p_)
    {
        bombs_->kill_player_if_in_explosion(now, player2p_);
    }

    bombs_->chain_explosion(now);
    bombs_->burn_out_walls_if_explosion_reaches(now, *map_, walls_);
}

void State::draw() const
{
    map_->draw(*object_image_);
    bombs_->draw(*object_image_);
    items_->draw(*object_image_, *map_);
    walls_->draw(*object_image_);

    player1p_->draw(*object_image_);

    if (player2p_)
    {
        player2p_->draw(*object_image_);
    }

    for (int i = 0; i < EnemyCount; ++i)
    {
        enemies_[i].draw(*object_image_);
    }
}

void State::pause()
{
    GameLib::Framework f = GameLib::Framework::instance();
    unsigned now(f.time());
    player1p_->pause(now);

    if (player2p_)
    {
        player2p_->pause(now);
    }

    for (int i = 0; i < EnemyCount; ++i)
    {
        enemies_[i].pause(now);
    }

    bombs_->pause(now);
    walls_->pause(now);
}

void State::resume()
{
    GameLib::Framework f = GameLib::Framework::instance();
    unsigned now(f.time());
    player1p_->resume(now);

    if (player2p_)
    {
        player2p_->resume(now);
    }

    for (int i = 0; i < EnemyCount; ++i)
    {
        enemies_[i].resume(now);
    }

    bombs_->resume(now);
    walls_->resume(now);
}

bool State::does_game_over() const
{
    if (!player2p_)
    {
        for (int i = 0; i < EnemyCount; ++i)
        {
            if (!enemies_[i].did_die())
            {
                return false;
            }
        }
    }
    else
    {
        return player1p_->did_die() ^ player2p_->did_die();
    }

    return true;
}

bool State::does_game_failure() const
{
    if (!player2p_)
    {
        return player1p_->did_die();
    }
    else
    {
        return player1p_->did_die() && player2p_->did_die();
    }
}
