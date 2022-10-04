#pragma once

#include <ge211.hxx>

class Player
{
public:
    Player();

    ge211::Posn<float> position() {
        return position_;
    }

    ge211::Dims<float> velocity() {
        return velocity_;
    }

    bool alive(){
        return alive_;
    }

    bool game_over(){
        return game_over_;
    }

    void update_alive(bool update){
        alive_ = update;
    }


    void update_velocity(ge211::Dims<float> update) {
        velocity_ = update;
    }

    void update_position(ge211::Posn<float> update) {
        position_ = update;
    }

    void update_game(bool g) {
        game_over_ = g;
    }

    Player next(double dt);

private:
    ge211::Posn<float> position_;
    ge211::Dims<float> velocity_;
    bool alive_;
    bool game_over_;
};