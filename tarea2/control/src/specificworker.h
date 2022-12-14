/*
 *    Copyright (C) 2022 by YOUR NAME HERE
 *
 *    This file is part of RoboComp
 *
 *    RoboComp is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    RoboComp is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with RoboComp.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
	\brief
	@author authorname
*/



#ifndef SPECIFICWORKER_H
#define SPECIFICWORKER_H

#include <genericworker.h>
#include <innermodel/innermodel.h>

class SpecificWorker : public GenericWorker
{
Q_OBJECT
public:
	SpecificWorker(TuplePrx tprx, bool startup_check);
	~SpecificWorker();
	bool setParams(RoboCompCommonBehavior::ParameterList params);

    public slots:
	    void compute();
	    int startup_check();
	    void initialize(int period);

    private:
	    float umbral = 700;
	    bool startup_check_flag;

        enum class State {IDLE, TURN, FORWARD, SPIRAL, FOLLOW_WALL};
        State state = State::IDLE;

        struct Constants {
            const int partesLaser = 3;
        };

        Constants consts;

    tuple<float, float> forward_move(const RoboCompLaserMulti::TLaserData &ldata);

    tuple<float, float> follow_wall(const RoboCompLaserMulti::TLaserData &ldata);

    tuple<float, float> rotation_move(const RoboCompLaserMulti::TLaserData &ldata);

    tuple<float, float> spiral_move(const RoboCompLaserMulti::TLaserData &ldata);
};

#endif
