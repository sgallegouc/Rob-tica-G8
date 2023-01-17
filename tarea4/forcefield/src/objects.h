//
// Created by alumno on 16/01/23.
//
#ifndef FORCEFIELD_OBJECTS_H
#define FORCEFIELD_OBJECTS_H

#include <YoloObjects.h>
#include <Eigen/Dense>
#include "door_detector.h"

namespace rc
{
    class Objects
    {
    public:
        int id = 0;
        int type;
        int left;
        int top;
        int right;
        int bot;
        float score;
        float depth;
        float x;
        float y;
        float z;
        float rx;
        float ry;
        float rz;

        Objects() = default;
        Objects(const DoorDetector::Door &d);
        Objects(const RoboCompYoloObjects::TBox &box);
        Eigen::Vector3f get_robot_coordinates() const;
        Eigen::Vector3f get_local_coordinates() const;
        void print() const;
        static std::vector<Objects> add_doors(const std::vector<DoorDetector::Door> &doors);
        static std::vector<Objects> add_yolo(const std::vector<RoboCompYoloObjects::TBox> &boxes);

    };

} // rc

#endif