#include "model.hxx"
Model::Model()
        :distance_traveled(0),
        shield_(false),
        collector_(false)
{
    
    //create obstacle list
        int start_point = 750;
        for(int i = 0; i < 500; i++) {
            int num = rand() % 2;
            int x_pos = rand() %  500 + start_point;

            //generates either horizontal or vertical obstacle
            obstacles_.push_back(Obstacle());
            obstacles_[i].change_velocity({-500, 0});
            if (num == 0) {
                //Determine direction - horizontal
                obstacles_[i].change_direction(0);
                obstacles_[i].change_position({(float)x_pos, (float)((rand()
                % 200) + 100)});
            }
            if (num == 1) {
                //determine direction - vertical
                obstacles_[i].change_direction(1);
                obstacles_[i].change_position({(float)x_pos, (float) (rand()
                % 567)});
            }
            start_point += 600;
        }

        //make coins
        int start_point2 = 800;
        for(int i = 0; i < 400; i++) {
            coins_.push_back(Obstacle({(float)(rand() % 100 + start_point2),
                                       (float)(rand() % 567)}, {-500, 0}));
            start_point2 += 300;
        }

        //make shields
        int start_point3 = 2000;
        for(int i = 0; i < 100; i++) {
            shields_.push_back(Obstacle({(float)(rand() % 8000 +
            start_point3), (float)(rand() % 567)}, {-300, 0}));
            start_point3 += 10000;
        }

        //make coin collectors
        int start_point4 = 2000;
        for(int i = 0; i < 100; i++) {
            collectors_.push_back(Obstacle({(float)(rand() % 7000 +
            start_point4), (float)(rand() % 567)}, {-300, 0}));
            start_point4 += 10000;
        }

}

void Model::refresh_all() {
    //refresh obstacles
    if (obstacles_.size() < 2) {
        int start_point1 = 1000;
        for (int i = 0; i < 500; i++) {
            int num = rand() % 2;
            int x_pos = rand() % 500 + start_point1;

            //generates either horizontal or vertical obstacle
            obstacles_.push_back(Obstacle());
            obstacles_[i].change_velocity({-500, 0});
            if (num == 0) {
                //Determine direction - horizontal
                obstacles_[i].change_direction(0);
                obstacles_[i].change_position({(float) x_pos, (float) ((rand
                () % 200) + 100)});
            }
            if (num == 1) {
                //determine direction - vertical
                obstacles_[i].change_direction(1);
                obstacles_[i].change_position({(float) x_pos, (float) (rand()
                % 567)});
            }
            start_point1 += 600;
        }
    }
    //refresh coins
    if(coins_.size() < 2){
        int start_point2 = 1000;
        for(int i = 0; i < 400; i++) {
            coins_.push_back(Obstacle({(float)(rand() % 100 + start_point2),
                                       (float)(rand() % 567)}, {-500, 0}));
            start_point2 += 600;
        }
    }

    //refresh shields
    if(shields_.size() < 2){
        int start_point3 = 2000;
        for(int i = 0; i < 100; i++) {
            shields_.push_back(Obstacle({(float)(rand() % 20000 +
            start_point3),(float)(rand() % 567)}, {-300, 0}));
            start_point3 += 10000;
        }
    }

    //refresh collectors
    if(collectors_.size() < 2){
        int start_point4 = 2000;
        for(int i = 0; i < 100; i++) {
            collectors_.push_back(Obstacle({(float)(rand() % 10000 +
            start_point4),  (float)(rand() % 567)}, {-300, 0}));
            start_point4 += 10000;
        }
    }
}

void Model::on_frame(double dt) {

    if(player_.game_over()){
        refresh_all();
            if(key_pressed == 'r'){
                obstacles_.clear();
                coins_.clear();
                shields_.clear();
                collectors_.clear();
                player_.update_position({30, 250});
                player_.update_velocity({0, 0});
                distance_traveled = 0;
                player_.update_game(false);
            }
        }
    if(!player_.game_over()) {
        if (key_pressed == 'a') {
            player_.update_alive(true);
        }
    }
    if(player_.alive()) {
        //collision
        ge211::Posn<float> p_top_front = {player_.position().x + 30, player_
                                          .position().y};
        ge211::Posn<float> p_top_back = {player_.position().x, player_
                                         .position().y};
        ge211::Posn<float> p_bottom_front = {player_.position().x + 30,
                                             player_.position().y + 30};
        //check if front of player is below top, above bottom, left of right,
        // and right of left (of obstacle)
        for (int i = 0; i < 500; i++) {
            ge211::Posn<float> obstacle_top_left = {obstacles_[i].position()
                                                    .x, obstacles_[i].position().y};
            ge211::Posn<float> obstacle_bottom_right = {obstacles_[i]
                                                        .position().x,
                                                        obstacles_[i]
                                                        .position().y};
            //horizontal
            if (obstacles_[i].direction() == 0) {
                obstacle_bottom_right = {obstacles_[i].position().x + 250,
                                         obstacles_[i].position().y + 10};
            } else {
                obstacle_bottom_right = {obstacles_[i].position().x + 10,
                                         obstacles_[i].position().y + 250};
            }
            if (!(p_top_front.x < obstacle_top_left.x || p_top_back.x >
                    obstacle_bottom_right.x ||
                p_top_front.y > obstacle_bottom_right.y || p_bottom_front.y <
                        obstacle_top_left.y)) {
                if(shield_){
                    shield_ = false;
                    obstacles_.erase(obstacles_.begin() + i);
                } else {
                    //death_timer.reset();
                    player_.update_alive(false);
                    player_.update_game(true);
                }
            }
        }

        //coin collision
        for (int i = 0; i < 400; i++) {
            ge211::Posn<float> coin_top_left = {coins_[i].position().x,
                                                coins_[i].position().y};
            ge211::Posn<float> coin_bottom_right = {coins_[i].position().x +
                                                    10, coins_[i].position().y + 10};
            if(get_collector()){
                if(coin_top_left.x < p_top_back.x){
                    set_distance(distance_traveled + 100);
                    coins_.erase(coins_.begin() + i);
                }
            }
            if (!(p_top_front.x < coin_top_left.x || p_top_back.x >
                    coin_bottom_right.x ||
                  p_top_front.y > coin_bottom_right.y || p_bottom_front.y <
                  coin_top_left.y)) {
                set_distance(distance_traveled + 100);
                coins_.erase(coins_.begin() + i);
            }
        }

        //shield collision
        for (int i = 0; i < 100; i++) {
            ge211::Posn<float> shield_top_left = {shields_[i].position().x,
                                                  shields_[i].position().y};
            ge211::Posn<float> shield_bottom_right = {shields_[i].position()
                                                      .x + 30, shields_[i].position().y + 30};
            if (!(p_top_front.x < shield_top_left.x || p_top_back.x > shield_bottom_right.x ||
                  p_top_front.y > shield_bottom_right.y ||  p_bottom_front.y
                          < shield_top_left.y)) {
                shield_ = true;
                shields_.erase(shields_.begin() + i);
            }
        }

        //collector collision
        if(timer_.elapsed_time().seconds() > 15){
            collector_ = false;
        }
        for (int i = 0; i < 100; i++) {
            ge211::Posn<float> collector_top_left = {collectors_[i].position
                                                     ().x,  collectors_[i]
                                                     .position().y};
            ge211::Posn<float> collector_bottom_right = {collectors_[i]
                                                         .position().x + 30,
                                                         collectors_[i].position().y + 30};
            if (!(p_top_front.x < collector_top_left.x || p_top_back.x  >
                    collector_bottom_right.x ||
                  p_top_front.y > collector_bottom_right.y  || p_bottom_front
                  .y < collector_top_left.y)) {
                collector_ = true;
                timer_.reset();
                collectors_.erase(collectors_.begin() + i);
            }
        }

    }

    refresh_all();

    //controls movement of player
    if(player_.alive()){
        if (key_pressed == 'a') {
            player_.update_velocity(player_.velocity() +
                                    ge211::Dims<float>{0, -9.8 * 1.5});
        }

        //if the space bar is released, make the player fall
        if (key_pressed == 'b') {
            player_.update_velocity(player_.velocity() +
                                    ge211::Dims<float>{0, 9.8});
        }

        //makes sure that the player can't go off-screen
        if (player_.position().y < 0){
            player_.update_velocity({0, 0});
            player_.update_position({30, 0});
        } else if (player_.position().y > 569){
            player_.update_velocity({0, 0});
            player_.update_position({30, 569});
        }

        //updates player and obstacle
        player_ = player_.next(dt);
        obstacle_ = obstacle_.next(dt);

        for(int i = 0; i < 500; i++){
            obstacles_[i].next(dt);
            int j = obstacles_.begin()->position().x;
            if((j + 250) < 0){
                obstacles_.erase(obstacles_.begin());
            }
        }

        //coin movement
        for(int i = 0; i < 400; i++){
            coins_[i].next(dt);
            if(coins_.begin()->position().x < 0){
                coins_.erase(coins_.begin());
            }
        }

        //shield movement
        for(int i = 0; i < 100; i++){
            shields_[i].next(dt);
            if(shields_.begin()->position().x < 0){
                shields_.erase(shields_.begin());
            }
        }

        //collector movement
        for(int i = 0; i < 100; i++){
            collectors_[i].next(dt);
            if(collectors_.begin()->position().x < 0){
                collectors_.erase(collectors_.begin());
            }
        }
        distance_traveled += dt * 12;
    }
}