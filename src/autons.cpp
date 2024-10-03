#include "vex.h"
const int ARM_MAX = 600;


/**
 * Resets the constants for auton movement.
 * Modify these to change the default behavior of functions like
 * drive_distance(). For explanations of the difference between
 * drive, heading, turning, and swinging, as well as the PID and
 * exit conditions, check the docs.
 */

void default_constants(){
  // Each constant set is in the form of (maxVoltage, kP, kI, kD, startI).
  chassis.set_drive_constants(12, 0.52, 0, 0, 0);
  chassis.set_heading_constants(12, .155, 0, 0, 0);
  chassis.set_turn_constants(12, 0.074, 0, 0, 0);



  // Per Degree  (180, 0.0581) (90, 0.074)(45, 0.1045)



  chassis.set_swing_constants(12, .175 , 0, 0, 0);

  // Each exit condition set is in the form of (settle_error, settle_time, timeout).
  chassis.set_drive_exit_conditions(1, 75, 1500);
  chassis.set_turn_exit_conditions(5, 75, 1500);
  chassis.set_swing_exit_conditions(1, 75, 1500);
}

/**
 * Sets constants to be more effective for odom movements.
 * For functions like drive_to_point(), it's often better to have
 * a slower max_voltage and greater settle_error than you would otherwise.
 */

void odom_constants(){
  default_constants();
  chassis.heading_max_voltage = 10;
  chassis.drive_max_voltage = 12;
  //chassis.boomerang_lead = .5;
  //chassis.drive_min_voltage = 0;
}


void red_leftside() {
  odom_constants();
  chassis.set_coordinates(0, 0, 0);

  // first launch to far goal
  chassis.drive_distance(-34);

  // turn to face goal
  chassis.set_turn_constants(12, 0.1375, 0, 0, 0);
  chassis.set_turn_exit_conditions(5, 75, 1500);
  chassis.turn_to_angle(-30);

  // approach goal
  chassis.drive_distance(-15);

  // clamp goal
  clampA.set(true);
  clampB.set(true);
  wait(100, msec);

  // turn to second ring
  chassis.set_turn_constants(12, 0.11, 0, 0, 0);
  chassis.set_turn_exit_conditions(5, 75, 1500);
  chassis.turn_to_angle(15);

  // score preload
  intake.spin(reverse, 11, voltageUnits::volt);
  wait(250, msec);

  // score second ring
  chassis.drive_distance(15);
  wait(500, msec);

  // turn to let go off mogo
  chassis.set_turn_constants(12, 0.064, 0, 0, 0);
  chassis.set_turn_exit_conditions(5, 75, 1500);
  chassis.turn_to_angle(135);
  clampA.set(false);
  clampB.set(false);

  // move for angle to second mogo
  chassis.drive_distance(-16);

  // turn to face second mogo
  chassis.set_turn_constants(12, 0.0635, 0, 0, 0);
  chassis.set_turn_exit_conditions(5, 75, 1500);
  chassis.turn_to_angle(-90);

  // approach second mogo
  chassis.drive_distance(-21);

  // clamp goal
  intake.spin(reverse, 0, voltageUnits::volt);
  clampA.set(true);
  clampB.set(true);
  wait(150, msec);

  // turn to face second ring
  intake.spin(reverse, 11, voltageUnits::volt);
  chassis.turn_to_angle(-45);

  chassis.drive_distance(14);

  // // raise intake
  // arm.set(true);
  // intake.spin(reverse, 11, voltageUnits::volt);

  // chassis.drive_distance(28);

  // arm.set(false);

  // chassis.drive_distance(5);

  // wait(450, msec);

  // chassis.set_turn_constants(12, 0.06, 0, 0, 0);
  // chassis.turn_to_angle(90);








  while (true) {
    Brain.Screen.printAt(5,60, "Heading: %f", chassis.get_absolute_heading());
  }










}

/**
 * The expected behavior is to return to the start position.
 */

void drive_test(){
  default_constants();
  chassis.turn_to_angle(45);
}

/**
 * The expected behavior is to return to the start angle, after making a complete turn.
 */

void turn_test(){
  chassis.turn_to_angle(5);
  chassis.turn_to_angle(30);
  chassis.turn_to_angle(90);
  chassis.turn_to_angle(225);
  chassis.turn_to_angle(0);
}

/**
 * Should swing in a fun S shape.
 */

void swing_test(){
  chassis.left_swing_to_angle(90);
  chassis.right_swing_to_angle(0);
}

/**
 * A little of this, a little of that; it should end roughly where it started.
 */

void full_test(){
  chassis.drive_distance(24);
}

/**
 * Doesn't drive the robot, but just prints coordinates to the Brain screen
 * so you can check if they are accurate to life. Push the robot around and
 * see if the coordinates increase like you'd expect.
 */

void odom_test(){
  chassis.set_coordinates(0, 0, 0);
  while(1){
    Brain.Screen.clearScreen();
    Brain.Screen.printAt(5,20, "X: %f", chassis.get_X_position());
    Brain.Screen.printAt(5,40, "Y: %f", chassis.get_Y_position());
    Brain.Screen.printAt(5,60, "Heading: %f", chassis.get_absolute_heading());
    Brain.Screen.printAt(5,80, "ForwardTracker: %f", chassis.get_ForwardTracker_position());
    Brain.Screen.printAt(5,100, "SidewaysTracker: %f", chassis.get_SidewaysTracker_position());
    task::sleep(20);
  }
}

/**
 * Should end in the same place it began, but the second movement
 * will be curved while the first is straight.
 */

void tank_odom_test(){
  odom_constants();
  chassis.set_coordinates(0, 0, 0);
  chassis.turn_to_point(24, 24);
  chassis.drive_to_point(24,24);
  chassis.drive_to_point(0,0);
  chassis.turn_to_angle(0);
}

/**
 * Drives in a square while making a full turn in the process. Should
 * end where it started.
 */

void holonomic_odom_test(){
  odom_constants();
  chassis.set_coordinates(0, 0, 0);
  chassis.holonomic_drive_to_pose(0, 18, 90);
  chassis.holonomic_drive_to_pose(18, 0, 180);
  chassis.holonomic_drive_to_pose(0, 18, 270);
  chassis.holonomic_drive_to_pose(0, 0, 0);
}
