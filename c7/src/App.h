#ifndef BAKUDAN_APP_H_
#define BAKUDAN_APP_H_

namespace Controller
{

class Game;
class NoState;

} // namespace Controller

class App
{
public:
    enum ControllerType
    {
        ControllerNoState,
        ControllerGame,
    };

private:
    Controller::Game* game_controller_;
    Controller::NoState* no_state_controller_;

public:
    App();
    ~App();
    void update();
    bool was_terminate_requested() const;
};

#endif
