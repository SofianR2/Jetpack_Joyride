#pragma once

#include "model.hxx"

class View
{
public:

    explicit View(Model const& model);

    void draw(ge211::Sprite_set& set);

private:
    Model const& model_;

    ge211::sprites::Rectangle_sprite player_sprite;
    ge211::sprites::Rectangle_sprite vert_obstacle;
    ge211::sprites::Rectangle_sprite horiz_obstacle;
    ge211::sprites::Circle_sprite coin_sprite;
    ge211::sprites::Rectangle_sprite shield_sprite;
    ge211::sprites::Rectangle_sprite collector_sprite;
    ge211::sprites::Rectangle_sprite collector_line;
    ge211::Font sans30{"sans.ttf", 30};
    ge211::Text_sprite distance_sprite;
    ge211::Text_sprite end_sprite;
    ge211::Text_sprite reset_sprite;
};
