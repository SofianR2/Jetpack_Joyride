#pragma once

#include <ge211.hxx>
class Obstacle{

public:

    Obstacle();

    Obstacle(ge211::Posn<float> position, ge211::Dims<float> velocity);

    Obstacle next(double dt);

    ge211::Posn<float> position() {
        return position_;
    }

    void change_position(ge211::Posn<float> posn){
        position_ = posn;
    }

    int direction(){
        return direction_;
    }

    void change_direction(int num){
        direction_ = num;
    }

    void change_velocity(ge211::Dims<float> velocity){
        velocity_ = velocity;
    }

    bool on_screen(){
        return on_screen_;
    }

private:
    //Starts on the right side of the screen at a random position
    //Determine right side of screen
    ge211::Posn<float> position_{700, 0};
    ge211::Dims<float> velocity_{0, 0};
    bool on_screen_ = false;
    int direction_;

};

