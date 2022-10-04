#include "controller.hxx"

Controller::Controller()
        : view_(model_)
{ }

void
Controller::draw(ge211::Sprite_set& set)
{
    view_.draw(set);
}

void Controller::on_frame(double dt) {
    model_.on_frame(dt);
}

void Controller::on_key(ge211::Key key){
    if(key == ge211::Key::code(' ')){
        model_.set_key('a');
    }
    if(key == ge211::Key::code('r')){
        model_.set_key('r');
    }
}

void Controller::on_key_up(ge211::Key key){
    if(key == ge211::Key::code(' ')) {
        model_.set_key('b');
    }
}

