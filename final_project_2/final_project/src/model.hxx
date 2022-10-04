#pragma once

#include <ge211.hxx>
#include "player.hxx"
#include "obstacle.hxx"

class Model
{
public:

    Model();

    Player player() const {
        return player_;
    }

    bool get_shield() const{
        return shield_;
    }

    bool get_collector() const{
        return collector_;
    }

    Obstacle obstacle() const {
        return obstacle_;
    }

    void on_frame(double dt);

    void refresh_all();

    void set_key(char c) {
        key_pressed = c;
    }

    double get_distance() const{
        return (int)distance_traveled;
    }

    std::vector<Obstacle> get_obstacles() const{
        return obstacles_;
    }

    std::vector<Obstacle> get_coins() const{
        return coins_;
    }

    std::vector<Obstacle> get_shields() const{
        return shields_;
    }

    std::vector<Obstacle> get_collectors() const{
        return collectors_;
    }

    void set_distance(double d){
        distance_traveled = d;
    }
    void set_coins(std::vector<Obstacle> c){
        coins_ = c;
    }

    void set_shields(std::vector<Obstacle> s){
        shields_ = s;
    }

    void set_collectors(std::vector<Obstacle> c){
        collectors_ = c;
    }

    void set_obstacles(std::vector<Obstacle> o){
        obstacles_ = o;
    }

    ge211::Timer timer(){
        return timer_;
    }

private:
    double distance_traveled;
    bool shield_;
    bool collector_;
    char key_pressed;
    Player player_;
    Obstacle obstacle_;
    std::vector<Obstacle> obstacles_;
    std::vector<Obstacle> coins_;
    std::vector<Obstacle> shields_;
    std::vector<Obstacle> collectors_;
    ge211::Timer timer_;
    ge211::Timer death_timer;

};
