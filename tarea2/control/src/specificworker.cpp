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
#include "specificworker.h"

/**
* \brief Default constructor
*/
SpecificWorker::SpecificWorker(TuplePrx tprx, bool startup_check) : GenericWorker(tprx)
{
	this->startup_check_flag = startup_check;
	// Uncomment if there's too many debug messages
	// but it removes the possibility to see the messages
	// shown in the console with qDebug()
//	QLoggingCategory::setFilterRules("*.debug=false\n");
}

/**
* \brief Default destructor
*/
SpecificWorker::~SpecificWorker()
{
	std::cout << "Destroying SpecificWorker" << std::endl;
}

bool SpecificWorker::setParams(RoboCompCommonBehavior::ParameterList params)
{
//	THE FOLLOWING IS JUST AN EXAMPLE
//	To use innerModelPath parameter you should uncomment specificmonitor.cpp readConfig method content
//	try
//	{
//		RoboCompCommonBehavior::Parameter par = params.at("InnerModelPath");
//		std::string innermodel_path = par.value;
//		innerModel = std::make_shared(innermodel_path);
//	}
//	catch(const std::exception &e) { qFatal("Error reading config params"); }

	return true;
}

void SpecificWorker::initialize(int period)
{
	std::cout << "Initialize worker" << std::endl;
	this->Period = period;
	if(this->startup_check_flag)
	{
		this->startup_check();
	}
	else
	{
		timer.start(Period);
	}

}

void SpecificWorker::compute()
{
    RoboCompLaserMulti::TLaserData ldata;
    try
    { ldata = lasermulti_proxy->getLaserData(0);}
    catch(const Ice::Exception &e) {
        std::cout << e.what() << " " << "laser failed" << std::endl;
        return;
    }
    std::tuple<float, float> vels{0.f,0.f};   // vel[0] = adv && vel[1] = rot

    switch(state)
    {
        case State::IDLE:
            state = State::FORWARD;
            break;
        case State::FORWARD:   // avanzar recto
            vels = forward_move(ldata);
            break;
        case State::FOLLOW_WALL:
            vels = follow_wall(ldata);
            break;
        case State::TURN:
            vels = rotation_move(ldata);
            break;
        case State::SPIRAL:
            vels = spiral_move(ldata);
            break;
    }

    try
    {
            differentialrobotmulti_proxy->setSpeedBase(0, get<0>(vels), get<1>(vels));
    }
    catch(const Ice::Exception &e) { std::cout << e.what() << " " << "laser failed" << std::endl;}
}

///////////////////////////7// PARTE DE LOS SECTORES
std::tuple<float, float> SpecificWorker::forward_move(const RoboCompLaserMulti::TLaserData &ldata)
{
    // exit conditions
    // sobre ldata extraes franja central
    RoboCompLaserMulti::TLaserData copy(ldata.begin()+ldata.size()/3, ldata.end()-ldata.size()/3);
    std::ranges::sort(copy, {},&RoboCompLaserMulti::TData::dist);
    if(copy.front().dist < umbral)
    {
        state = State::TURN;
        return std::make_tuple(0, 1.0);
    }



    // si campo laser es mayor que 80% del campo laser nominal, entonces state == State::SPIRAL

   if (auto suma = std::accumulate(ldata.begin(), ldata.end(), 0.f, [](auto s, auto a){return s+=a.dist; }); suma > (ldata.size()*4000)*0.8){
       state = State::SPIRAL;
       return std::make_tuple(5, 1.2);
   }



    return std::make_tuple(700, 0);
}



std::tuple<float, float> SpecificWorker::follow_wall(const RoboCompLaserMulti::TLaserData &ldata){
    return std::make_tuple(700, 0);
}

std::tuple<float, float> SpecificWorker::rotation_move(const RoboCompLaserMulti::TLaserData &ldata) {
    RoboCompLaserMulti::TLaserData copy(ldata.begin()+ldata.size()/3, ldata.end()-ldata.size()/3);
    std::ranges::sort(copy, {},&RoboCompLaserMulti::TData::dist);

    if (copy.front().dist > umbral) {
        state = State::FORWARD;
        return std::make_tuple(700, 0);
    }

        // si campo laser es mayor que 80% del campo laser nominal, entonces state == State::SPIRAL
    return std::make_tuple(0, 1.0);


    // comprobar que sea mayor que el umbral

}

std::tuple<float, float> SpecificWorker::spiral_move(const RoboCompLaserMulti::TLaserData &ldata){

    RoboCompLaserMulti::TLaserData copy(ldata.begin()+ldata.size()/3, ldata.end()-ldata.size()/3);
    std::ranges::sort(copy, {},&RoboCompLaserMulti::TData::dist);

    float spiral_ADV=5.0, spiral_ROT=1.2;
    std::make_tuple(spiral_ADV,spiral_ROT);
    if (copy.front().dist < umbral) {
        state = State::TURN;
        return std::make_tuple(0, 0.8);
    }
    if(1000<spiral_ADV){
        spiral_ADV = spiral_ADV+50;
        spiral_ROT = spiral_ROT-0.02;
    }else{
        state = State::FORWARD;

        return std::make_tuple(700, 0);
    }


    return std::make_tuple(700, 0);
}

///////////////////////////////
int SpecificWorker::startup_check()
{
	std::cout << "Startup check" << std::endl;
	QTimer::singleShot(200, qApp, SLOT(quit()));
	return 0;
}




/**************************************/
// From the RoboCompDifferentialRobot you can call this methods:
// this->differentialrobot_proxy->correctOdometer(...)
// this->differentialrobot_proxy->getBasePose(...)
// this->differentialrobot_proxy->getBaseState(...)
// this->differentialrobot_proxy->resetOdometer(...)
// this->differentialrobot_proxy->setOdometer(...)
// this->differentialrobot_proxy->setOdometerPose(...)
// this->differentialrobot_proxy->setSpeedBase(...)
// this->differentialrobot_proxy->stopBase(...)

/**************************************/
// From the RoboCompDifferentialRobot you can use this types:
// RoboCompDifferentialRobot::TMechParams

/**************************************/
// From the RoboCompLaser you can call this methods:
// this->laser_proxy->getLaserAndBStateData(...)
// this->laser_proxy->getLaserConfData(...)
// this->laser_proxy->getLaserData(...)

/**************************************/
// From the RoboCompLaser you can use this types:
// RoboCompLaser::LaserConfData
// RoboCompLaser::TData

