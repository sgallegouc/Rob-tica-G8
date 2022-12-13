//
// Created by alumno on 13/12/22.
//

#ifndef FORCEFIELD_DOOR_H
#define FORCEFIELD_DOOR_H

#include <Eigen/Dense>
#include <QtGui>
#include <QGraphicsItem>
#include <abstract_graphic_viewer/abstract_graphic_viewer.h>

class Door {

    public:

        Eigen::Vector2f p0, p1, center;


        std::vector<Door>detector(const std::vector<Eigen::Vector2f> &line);
};


#endif //FORCEFIELD_DOOR_H
