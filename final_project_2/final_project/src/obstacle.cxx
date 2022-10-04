#include<obstacle.hxx>

Obstacle::Obstacle(){}

Obstacle::Obstacle(ge211::Posn<float> position, ge211::Dims<float> velocity)
        :position_(position),
         velocity_(velocity)
{}

Obstacle Obstacle::next(double dt) {
    Obstacle result(*this);
    position_ += result.velocity_ * dt;
    return result;
}