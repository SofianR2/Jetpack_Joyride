#include<player.hxx>

Player::Player()
        :position_{30, 250},
        velocity_({0, 0}),
        alive_(false),
        game_over_(false)

{}

Player Player::next(double dt) {
    Player result(*this);
    result.position_ += result.velocity() * dt;
    return result;

}