//
// Created by alumno on 13/12/22.


#include "states.h"
#include "specificworker.h"

///////////////////  State machine ////////////////////////////////////////////

    void States::STATE_machine(const RoboCompYoloObjects::TObjects &objects, const std::vector<Eigen::Vector2f> &line, const rc::Robot robot) {

    switch (state) {
        case State::IDLE:
            state = State::SEARCHING;
            break;
        case State::SEARCHING:
            SEARCHING_state(objects, robot);
            break;
        case State::APPROACHING:
            APPROACHING_state(objects, line, robot);
            break;
        case State::WAITING:
            WAITING_state();
            break;
    }
}

    void States::SEARCHING_state(const RoboCompYoloObjects::TObjects &objects, rc::Robot robot){

        if(objects.empty()) return;
        if(robot.get_current_target().type == -1)
        {
            robot.set_current_target(objects.front());
            robot.set_pure_rotation(0);
            state = State::APPROACHING;
        }

        else if (auto it = std::find_if_not(objects.begin(), objects.end(),
                                            [r=robot](auto a) { return r.get_current_target().type == a.type; }); it != objects.end()) /// primer elemento distinto al tipo del robot
        {
            robot.set_pure_rotation(0);
            robot.set_current_target(*it);
            state = State::APPROACHING;
        }
        else
            robot.set_pure_rotation(0.5);
    }

    void States::APPROACHING_state(const RoboCompYoloObjects::TObjects &objects, const std::vector<Eigen::Vector2f> &line, rc::Robot robot){

        if(robot.get_distance_to_target() < 400){
            state = State::SEARCHING;
        }
            // el find con el igual, si me da true reemplazo el target con el target que me ha dado el iterador.
        else if (auto it = std::find_if(objects.begin(), objects.end(),
                                        [r=robot](auto a) { return r.get_current_target().type == a.type; }); it != objects.end())
        {
            robot.set_current_target(*it);
        }
        else
            state = State::SEARCHING;

    }

    void States::WAITING_state(){
        sleep(3);
        state = State::SEARCHING;
    }

