//
// Created by alumno on 13/12/22.
//

#ifndef FORCEFIELD_STATES_H
#define FORCEFIELD_STATES_H


#include <Eigen/Dense>
#include <QtGui>
#include <QGraphicsItem>
#include <abstract_graphic_viewer/abstract_graphic_viewer.h>
#include <genericworker.h>
#include <abstract_graphic_viewer/abstract_graphic_viewer.h>
#include <timer/timer.h>
#include <Eigen/Dense>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <dynamic_window.h>
#include <timer/timer.h>
#include "robot.h"
#include "camera.h"

class States {

    public:
       enum class State {IDLE, SEARCHING, APPROACHING, WAITING};
       State state = State::IDLE;
       void STATE_machine(const RoboCompYoloObjects::TObjects &objects, const std::vector<Eigen::Vector2f> &line);
       void SEARCHING_state(const RoboCompYoloObjects::TObjects &objects);
       void APPROACHING_state(const RoboCompYoloObjects::TObjects &objects, const std::vector<Eigen::Vector2f> &line);
       void WAITING_state();
       void detecting_doors(const std::vector<Eigen::Vector2f> &line);



};


#endif //FORCEFIELD_STATES_H
