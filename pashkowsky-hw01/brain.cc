
#include <iostream>
#include <math.h>

#include "robot.hh"

using std::cout;
using std::endl;

const double goal_x = 20.0;
const double goal_y = 0.0;
bool done = false;
bool towardsgoal = false;
bool halfway = false;
double prevdist = 0.0;

void
callback(Robot* robot)
{
    /*
    cout << endl;
    cout << "robot x =" << robot->pos_x << endl;
    cout << "robot y =" << robot->pos_y << endl;
    */
    double dx = goal_x - robot->pos_x;
    double dy = goal_y - robot->pos_y; 
    double theta = robot->pos_t;   
    double goaltheta = atan(dy/dx);
    double dist = pow(pow(dx,2)+pow(dy,2),0.5);
    cout << dist <<endl;
    if (abs(dx) < 0.75 && abs(dy) < 0.75) {
        cout << "we win!" << endl;
        robot->set_vel(0.0);
        robot->set_turn(0.0);
        robot->done();
        return;
    }

    bool turn = false;
    bool rightturn = false;
    bool leftturn = false;
    bool norelevanthit = true;
    //bool towardsgoal = false;

    for (LaserHit hit : robot->hits) {
        if (hit.range < 1.5) {
            if (hit.angle < 0.5 || hit.angle > (6.2 - 0.5)) {
                turn = true;
                norelevanthit = false;
            }
        }
    }
    if (dist < 20){
    	halfway = true;
    }
    
     if (norelevanthit && halfway) {
    	if (dist - prevdist > 0) {
    		towardsgoal = true;
    	}
    }
  
    if (towardsgoal) {
    	if (goaltheta - theta > 0.0){
    		leftturn = true;
    	}
    	else if (goaltheta - theta < 0.0){
    		rightturn = true;
    	}
    }	

	prevdist = dist;
    if (turn) {
        robot->set_vel(5.0);
        robot->set_turn(0.5);
    }
    else if (rightturn) {
        robot->set_vel(10.0);
        robot->set_turn(0.5);
    }
    else if (leftturn) {
        robot->set_vel(10.0);
        robot->set_turn(-0.5);
    }
    else {
        robot->set_vel(10.0);
        robot->set_turn(0.0);
    }
}

int
main(int argc, char* argv[])
{
    cout << "making robot" << endl;
    Robot robot(argc, argv, callback);
    robot.do_stuff();

    return 0;
}
