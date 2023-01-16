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
#include "objects.h"

class States {

    public:
       enum class State {IDLE, SEARCHING, APPROACHING, WAITING};
       State state = State::IDLE;
       void STATE_machine(const std::vector<rc::Objects> &objects, const std::vector<Eigen::Vector2f> &line, const rc::Robot robot);
       void SEARCHING_state(const std::vector<rc::Objects> &objects, rc::Robot robot);
       void APPROACHING_state(const std::vector<rc::Objects> &objects, const std::vector<Eigen::Vector2f> &line, rc::Robot robot);
       void WAITING_state();

};


#endif //FORCEFIELD_STATES_H
