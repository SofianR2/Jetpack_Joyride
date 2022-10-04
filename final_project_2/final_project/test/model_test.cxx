#include "model.hxx"
#include "player.hxx"
#include <catch.hxx>

TEST_CASE("correct player movement")
{
//test player movement
//test score is updated correctly
    Model m;
    // Make a copy of the player's position and score, which we'll use to compute
    // what we expect the player to do.
    ge211::Posn<float> expected_position = m.player().position();
    double expected_score = 0;

    // If the model advances by 0.5 s then we expect the center to move
    // accordingly:
    m.set_key('a');
    m.on_frame(0.5);

    //checks to make sure the player is alive after pressing space
    CHECK(m.player().alive());

    expected_position += 0.5 * m.player().velocity();
    expected_score += (0.5 * 12);
    CHECK(m.player().position() == expected_position);
    CHECK(m.get_distance() == (int)expected_score);

    // Again, but only 0.25 s this time.
    m.on_frame(0.25);
    expected_position += 0.25 * m.player().velocity();
    expected_score += 0.25 * 12;
    CHECK(m.player().position() == expected_position);
    CHECK(m.get_distance() == (int)expected_score);

    // Again, but 0.125 s this time.
    m.on_frame(0.125);
    expected_position += 0.125 * m.player().velocity();
    expected_score += 0.125 * 12;
    CHECK(m.player().position() == expected_position);
    CHECK(m.get_distance() == (int)expected_score);
}

//test that obstacles kill the player
TEST_CASE("Coin Collision"){
    //test coin collision
    Model m;
    m.set_key('a');

    std::vector<Obstacle> coins;
    CHECK(m.get_distance() == 0);
    coins.push_back(Obstacle({30, 240}, {0, 0}));
    m.set_coins(coins);
    m.on_frame(5);

    //player movement adds 60 points (dt:(5) * 12),
    //while coin adds 100 to distance (160)
    CHECK(m.get_distance() == 160);
}

TEST_CASE("Power-up collision"){
    Model m;
    m.set_key('a');

    std::vector<Obstacle> shield;
    std::vector<Obstacle> collector;
    CHECK(m.get_distance() == 0);
    shield.push_back(Obstacle({30, 240}, {0, 0}));
    collector.push_back(Obstacle({30, 240}, {0, 0}));
    m.set_shields(shield);
    m.set_collectors(collector);
    m.on_frame(5);

    CHECK(m.get_shield());
    CHECK(m.get_collector());

    //checks that the shield works
    std::vector<Obstacle> obstacle;
    obstacle.push_back(Obstacle({30, 170}, {0, 0}));
    m.set_obstacles(obstacle);
    m.on_frame(5);

    CHECK(!m.get_shield());
    CHECK(m.player().alive());

    //checks that the collector works
    std::vector<Obstacle> coins;
    coins.push_back(Obstacle({20, 240}, { 0, 0}));
    for(int i = 1; i < 400; i++){
        coins.push_back(Obstacle({5000, 0}, {0, 0}));
    }
    m.set_coins(coins);
    m.on_frame(5);

    //distance becomes 380 without coin, 480 with coin
    CHECK(m.get_distance() == 480);

    //runs the game for 15 seconds;
    //collector.clear();
    //m.set_collectors(collector);

    //CHECK(m.timer().elapsed_time().seconds() >= 15);
    //CHECK(!m.get_collector());

}

TEST_CASE("Player Death"){

    Model m;
    m.set_key('a');

    std::vector<Obstacle> obstacle;

    m.on_frame(1);
    CHECK(m.player().alive());
    CHECK(!m.player().game_over());
    obstacle.push_back(Obstacle({30, 250}, {0, 0}));
    m.set_obstacles(obstacle);
    m.on_frame(5);

    //checks to make sure the player is dead and the game is over
    CHECK(!m.player().alive());
    CHECK(m.player().game_over());

    //restarts the game
    m.set_key('r');
    m.on_frame(5);
    m.set_key('a');
    m.on_frame(5);

    CHECK(!m.player().game_over());
}

TEST_CASE("Obstacle Movement"){
    Model m;
    m.set_key('a');

    std::vector<Obstacle> obstacle;
    obstacle.push_back(Obstacle({1000, 250}, {-500, 0}));
    for(int i = 1; i < 10; i++){
        obstacle.push_back(Obstacle({5000, 0}, {0, 0}));
    }
    m.set_obstacles(obstacle);
    CHECK(m.get_obstacles().size() == 10);
    m.on_frame(10000);

    CHECK(m.get_obstacles().size() == 9);
}