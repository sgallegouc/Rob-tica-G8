// Created by alumno on 16/01/23.
//
#include "objects.h"

namespace rc {
    Objects::Objects(const RoboCompYoloObjects::TBox &box) :
            id(box.id), type(box.type), left(box.left), top(box.top),
            right(box.right), bot(box.bot), score(box.score), depth(box.depth),
            x(box.x), y(box.y), z(box.z) {
        Eigen::Vector3f rc = Eigen::Vector3f(box.x, box.y, box.z);
        rx = rc.x();
        ry = rc.y();
        rz = rc.z();

    }

    Objects::Objects(const DoorDetector::Door &d) {
        type = 80;  // door
        rx = d.center_floor.x();
        ry = d.center_floor.y();
        rz = 0.f;
        x = d.center_floor.x();
        y = d.center_floor.y();
        z = 0.f;
    }

    std::vector <Objects> Objects::add_yolo(const std::vector <RoboCompYoloObjects::TBox> &boxes) {
        std::vector <Objects> bobjs;
        for (const auto &b: boxes)
            bobjs.emplace_back(Objects(b));
        return bobjs;
    }

    std::vector <Objects> Objects::add_doors(const std::vector <DoorDetector::Door> &doors) {
        std::vector <Objects> bdoors;
        for (const auto &d: doors)
            bdoors.emplace_back(Objects(d));
        return bdoors;
    }

    Eigen::Vector3f Objects::get_local_coordinates() const {
        return Eigen::Vector3f(x, y, z);
    }

    Eigen::Vector3f Objects::get_robot_coordinates() const {
        return Eigen::Vector3f(rx, ry, rz);
    }

    void Objects::print() const {
        std::cout << "Object: " << std::endl;
        std::cout << "  type: " << type << std::endl;
        std::cout << "  rx: " << rx << std::endl;
        std::cout << "  ry: " << ry << std::endl;
        std::cout << "  rz: " << rz << std::endl;
        std::cout << "--------------" << std::endl;
    }
}