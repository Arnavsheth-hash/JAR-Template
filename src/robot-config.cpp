#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen.
brain  Brain;

//The motor constructor takes motors as (port, ratio, reversed), so for example
//motor LeftFront = motor(PORT1, ratio6_1, false);

//Add your devices below, and don't forget to do the same in robot-config.h:
controller controller1;

motor rf = motor(PORT14, ratio6_1, false);
motor rm = motor(PORT20, ratio6_1, false);
motor rb = motor(PORT17, ratio6_1, false);

motor lf = motor(PORT13, ratio6_1, true);
motor lm = motor(PORT18, ratio6_1, true);
motor lb = motor(PORT11, ratio6_1, true);

motor intake = motor(PORT7, ratio6_1, false);

motor arm = motor(PORT2, ratio36_1, true);

digital_out clampA = digital_out(Brain.ThreeWirePort.H);
digital_out clampB = digital_out(Brain.ThreeWirePort.G);

digital_out pto = digital_out(Brain.ThreeWirePort.F);

digital_out armSecond = digital_out(Brain.ThreeWirePort.E);

distance ringDistance = distance(PORT8);

void vexcodeInit( void ) {
  // nothing to initialize
}

// left  = 8 , 2, 1

// right = 9 , 10 , 20
