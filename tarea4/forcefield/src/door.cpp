//
// Created by alumno on 13/12/22.
//

#include "door.h"
#include <cppitertools/range.hpp>
#include <cppitertools/enumerate.hpp>
#include <cppitertools/filter.hpp>
#include <cppitertools/chunked.hpp>
#include <cppitertools/sliding_window.hpp>
#include <cppitertools/combinations_with_replacement.hpp>

std::vector<Door>detector(const std::vector<Eigen::Vector2f> &points)
{


    std::vector<float> derivada(points.size()-1);

    for(auto &&[i,p]:points | iter::sliding_window(2) | iter::enumerate)
        derivada[i] = p[1].norm()-p[0].norm();

        ///derivada.emplace_back(d);

    std::vector<std::tuple<int,bool>> peaks;
        for(auto &&[i,d]:derivada | iter::enumerate)
        {
            if (d > 500) // Umbral
                peaks.push_back(std::make_tuple(i, true));
            else if (d < -500)
                peaks.push_back(std::make_tuple(i+1, false));
    }
        std::vector<Door> doors;

        for(auto &&p:peaks | iter::combinations_with_replacement(2))
        {
            auto &[p1, pos1] = p[0];
            auto &[p2, pos2] = p[1];
            auto v1 = points[p1];
            auto v2 = points[p2];

            if(((pos1 and !pos2) or (pos2 and !pos1)) and ((v1 - v2).norm() < 1200 and (v1 - v2).norm() > 600))
            {
                Door door{.point1=v1, .point2=v2, .center=(v1 + v2)/2};
                doors.push_back(door);
            }
        }
        return doors;
    }

void Door::draw_doors(const std::vector<Door> &doors_v, AbstractGraphicViewer *viewer)
{
    static std::vector<QGraphicsItem *> items;
    for(const auto &item: items)
        viewer->scene.removeItem(item);
    items.clear();

    for(auto &&[k, doors]: doors_v | iter::enumerate)
    {
        QColor color("red");
        QBrush brush(color);
        QPen pen(color);
        for(const auto &p: doors_v)
        {
            auto item = viewer->scene.addEllipse(-100, -100, 200, 200, pen, brush);
            item->setPos(p.center.x(), p.center.y());
            items.push_back(item);
        }
    }
}
void Door::draw_peaks(std::vector<std::tuple<int, bool>> pecks, const std::vector<Eigen::Vector2f> &line,
                               AbstractGraphicViewer *viewer)
{
    static std::vector<QGraphicsItem *> items;
    for(const auto &item: items)
        viewer->scene.removeItem(item);
    items.clear();
    QColor color("blue");
    QBrush brush(color);
    QPen pen(color);

    for(auto &[p, b]: pecks)
    {
        auto item = viewer->scene.addEllipse(-100, -100, 200, 200, pen, brush);
        item->setPos(line[p].x(), line[p].y());
        items.push_back(item);
    }
}
