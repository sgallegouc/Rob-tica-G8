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

        Eigen::Vector2f point1, point2, center;
        std::vector<Door>detector(const std::vector<Eigen::Vector2f> &line);
        void draw_doors(const std::vector<Door> &doors_v, AbstractGraphicViewer *viewer);
        void draw_peaks(std::vector<std::tuple<int, bool>> pecks, const std::vector<Eigen::Vector2f> &line, AbstractGraphicViewer *viewer);
};


#endif //FORCEFIELD_DOOR_H
