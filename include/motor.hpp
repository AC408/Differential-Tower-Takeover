#ifndef MOTOR_HPP
#define MOTOR_HPP

#include "okapi/api.hpp"
using namespace okapi;

extern ChassisControllerPID chassisController;
extern AsyncMotionProfileController profileController;

extern int selector;

int sgn(int input);
int clipnum(int input, int clip);
void set_tank(int input_l, int input_r);
void set_intake(int input);
void set_diff(int input);
void set_diff(int input_l, int input_r);
void intake_hold();
void intake_coast();
void diff_coast();
void diff_hold();
void drive_coast();
void drive_hold();
void reset_drive_encoder();
void reset_intake_encoder();
void reset_diff_encoder();
int get_left_drive_pos();
int get_right_drive_pos();
int get_left_drive_spe();
int get_right_drive_spe();
int get_diff_spe();
int get_tray();
int get_auton_select();
bool tray_pressed();
void auto_selector();
void tray_auto_reset(void *);

#define TRAY_OUT 6100

#endif