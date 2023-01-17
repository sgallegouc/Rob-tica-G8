//
// Created by alumno on 13/12/22.


#include "states.h"
#include "specificworker.h"

///////////////////  State machine ////////////////////////////////////////////

    void States::STATE_machine(const std::vector<rc::Objects> &objects, const std::vector<Eigen::Vector2f> &line, const rc::Robot robot, AbstractGraphicViewer *viewer) {

    switch (state) {
        case State::IDLE:
            state = State::SEARCHING;
            break;
        case State::SEARCHING:
            qInfo()<< __FUNCTION__<<"searching";
            SEARCHING_state(objects, robot);
            break;
        case State::APPROACHING:
            qInfo()<< __FUNCTION__<<"aproaching";
            APPROACHING_state(objects, line, robot);
            break;
        case State::CROSS:
            qInfo()<< __FUNCTION__<<"cross";
            CROSS_state(robot, viewer);
            break;
    }
}

    void States::SEARCHING_state(const std::vector<rc::Objects> &objects, rc::Robot robot){

        if (auto it = std::find_if_not(objects.begin(), objects.end(),
                                            [r=robot](auto a) { return r.get_current_target().type == a.type; }); it != objects.end() && it->type == 80)
        {
            robot.set_pure_rotation(0);
            robot.set_current_target(*it);
            state = State::APPROACHING;
        }
        else
            robot.set_pure_rotation(0.5);
    }

    void States::APPROACHING_state(const std::vector<rc::Objects> &objects, const std::vector<Eigen::Vector2f> &line, rc::Robot robot){

        if(robot.get_distance_to_target() < 300){
            state = State::CROSS;
        }
        else if (auto it = std::find_if(objects.begin(), objects.end(),
                                        [r=robot](auto a) { return r.get_current_target().type == a.type; }); it != objects.end())
        {
            robot.set_current_target(*it);
        }
        else
            state = State::SEARCHING;

    }

    void States::CROSS_state(rc::Robot robot, AbstractGraphicViewer *viewer){

        static std::chrono::time_point<std::chrono::system_clock> start_chrono;
        static bool first=true;
        if (first)
        {
            start_chrono = std::chrono::system_clock::now();
            first = false;
        }

        auto end_chrono = std::chrono::system_clock::now();
        std::chrono::duration<float, std::milli> duration = end_chrono - start_chrono;

        if (duration.count() > 1400)
        {
            robot.set_has_target(false);
            state = State::SEARCHING;
            first = true;
        }
    }

