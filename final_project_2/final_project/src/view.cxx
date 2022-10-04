#include "view.hxx"

View::View(Model const& model)
        : model_(model),
          player_sprite({30, 30}, ge211::Color::medium_green()),
          vert_obstacle({10, 250}, ge211::Color::medium_yellow()),
          horiz_obstacle({250, 10}, ge211::Color::medium_yellow()),
          coin_sprite(10, ge211::Color::medium_yellow()),
          shield_sprite({30, 30}, ge211::Color::medium_blue()),
          collector_sprite({30, 30}, ge211::Color::medium_red()),
          collector_line({5, 2000}, ge211::Color::medium_red())

{ }

void
View::draw(ge211::Sprite_set& set)
{

    if(model_.get_shield()){
        player_sprite.recolor(ge211::Color::medium_blue());
        set.add_sprite(shield_sprite, model_.player().position().into<int>());

    } else {
        player_sprite.recolor(ge211::Color::medium_green());
        set.add_sprite(player_sprite, model_.player().position().into<int>());
    }

    if(model_.get_collector()){
        set.add_sprite(collector_line, {(int)(model_.player().position().x - 5), (int)(model_.player().position().y - 600)});
    } else {
        set.add_sprite(player_sprite, model_.player().position().into<int>());
    }

    ge211::Text_sprite::Builder letter_builder(sans30);
    letter_builder << "score: " << model_.get_distance();
    distance_sprite.reconfigure(letter_builder);
    set.add_sprite(distance_sprite, {30, 20});

    if(model_.player().game_over()){
        ge211::Text_sprite::Builder letter_builder(sans30);
        letter_builder << "Game Over";
        end_sprite.reconfigure(letter_builder);
        set.add_sprite(end_sprite, {300, 260}, 100);
    }

    if(model_.player().game_over()){
        ge211::Text_sprite::Builder letter_builder(sans30);
        letter_builder << "Press R to reset";
        reset_sprite.reconfigure(letter_builder);
        set.add_sprite(reset_sprite, {275, 320}, 100);
    }

    for(Obstacle c : model_.get_coins()){
        set.add_sprite(coin_sprite, c.position().into<int>());
    }

    for(Obstacle s : model_.get_shields()){
        set.add_sprite(shield_sprite, s.position().into<int>(), 75);
    }

    for(Obstacle c : model_.get_collectors()){
        set.add_sprite(collector_sprite, c.position().into<int>(), 74);
    }

    for(Obstacle o : model_.get_obstacles()){
        if(o.direction() == 0){
            set.add_sprite(horiz_obstacle, o.position().into<int>());
        } else if (o.direction() == 1) {
            set.add_sprite(vert_obstacle, o.position().into<int>());
        }
    }
}
