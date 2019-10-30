#include "main.h"

// Otherwise, you should specify the gearset and scales for your robot
ChassisControllerPID chassisController = ChassisControllerFactory::create(
    {1, 2}, {-9, -10},
//    IterativePosPIDController::Gains{0.0076, 0, 0.0001}, //{0.001, 0, 0.0001}}   
    IterativePosPIDController::Gains{0.002, 0, 0.00005}, //{0.001, 0, 0.0001}}
    IterativePosPIDController::Gains{0.0005, 0, 0.0002},
    IterativePosPIDController::Gains{0.01725, 0.025, 0.0004}, //0.01, 0.000325, 0.01425, 0.0004
    AbstractMotor::gearset::green,                            //0.0175, 0.01, 0.000375
    {4.125_in, 9.0_in});

AsyncMotionProfileController profileController = AsyncControllerFactory::motionProfile(
    0.8,                // Maximum linear velocity of the Chassis in m/s
    1.75,               // Maximum linear acceleration of the Chassis in m/s/s
    15.0,               // Maximum linear jerk of the Chassis in m/s/s/s
    chassisController); // Chassis Controller

int selector = 0;

//Motors
pros::Motor lb_drive(1, MOTOR_GEARSET_18);
pros::Motor lf_drive(2, MOTOR_GEARSET_18);
pros::Motor rf_drive(9, MOTOR_GEARSET_18, true);
pros::Motor rb_drive(10, MOTOR_GEARSET_18, true);
pros::Motor l_diff(13, MOTOR_GEARSET_18);
pros::Motor r_diff(18, MOTOR_GEARSET_18);
pros::Motor l_intake(14, MOTOR_GEARSET_18);
pros::Motor r_intake(17, MOTOR_GEARSET_18, true);

//Sensors
//pros::ADIPotentiometer tray_pot('A');
pros::ADIDigitalIn tray_limit('A');
pros::ADIPotentiometer auton_selector('B');

//Math
int sgn(int input)
{
    if (input > 0)
        return 1;
    else if (input < 0)
        return -1;
    return 0;
}

int clipnum(int input, int clip)
{
    if (input > clip)
        return clip;
    else if (input < clip)
        return -clip;
    return input;
}

//Set Motors
void set_tank(int input_l, int input_r)
{
    lb_drive.move(input_l);
    lf_drive.move(input_l);
    rf_drive.move(input_r);
    rb_drive.move(input_r);
}

void set_intake(int input)
{
    l_intake.move(input);
    r_intake.move(input);
}

void set_diff(int input_l, int input_r)
{
    l_diff.move(input_l);
    r_diff.move(input_r);
}

void set_diff(int input)
{
    l_diff.move(input);
    r_diff.move(input);
}

//Stop Motors
void intake_hold()
{
    l_intake.set_brake_mode(MOTOR_BRAKE_HOLD);
    r_intake.set_brake_mode(MOTOR_BRAKE_HOLD);
}

void intake_coast()
{
    l_intake.set_brake_mode(MOTOR_BRAKE_COAST);
    r_intake.set_brake_mode(MOTOR_BRAKE_COAST);
}

void diff_coast()
{
    l_diff.set_brake_mode(MOTOR_BRAKE_COAST);
    r_diff.set_brake_mode(MOTOR_BRAKE_COAST);
}

void diff_hold()
{
    l_diff.set_brake_mode(MOTOR_BRAKE_HOLD);
    r_diff.set_brake_mode(MOTOR_BRAKE_HOLD);
}

void drive_coast()
{
    lb_drive.set_brake_mode(MOTOR_BRAKE_COAST);
    lf_drive.set_brake_mode(MOTOR_BRAKE_COAST);
    rf_drive.set_brake_mode(MOTOR_BRAKE_COAST);
    rb_drive.set_brake_mode(MOTOR_BRAKE_COAST);
}

void drive_hold()
{
    lb_drive.set_brake_mode(MOTOR_BRAKE_HOLD);
    lf_drive.set_brake_mode(MOTOR_BRAKE_HOLD);
    rf_drive.set_brake_mode(MOTOR_BRAKE_HOLD);
    rb_drive.set_brake_mode(MOTOR_BRAKE_HOLD);
}

//Sensors
void reset_drive_encoder()
{
    lb_drive.set_zero_position(0);
    rb_drive.set_zero_position(0);
}

void reset_intake_encoder()
{
    l_intake.set_zero_position(0);
    r_intake.set_zero_position(0);
}

void reset_diff_encoder()
{
    l_diff.set_zero_position(0);
    r_diff.set_zero_position(0);
}

int get_left_drive_pos()
{
    return lb_drive.get_position();
}

int get_right_drive_pos()
{
    return rb_drive.get_position();
}

int get_left_drive_spe()
{
    return lb_drive.get_actual_velocity() / 200 * 127;
}

int get_right_drive_spe()
{
    return rb_drive.get_actual_velocity() / 200 * 127;
}

int get_diff_spe()
{
    return l_diff.get_actual_velocity() / 200 * 127;
}

int get_tray()
{
    //return tray_pot.get_value();
    return -r_diff.get_position();
}

int get_auton_select()
{
    return auton_selector.get_value();
}

bool tray_pressed()
{
    if (tray_limit.get_value() == 1)
    {
        return true;
    }
    return false;
}

void auto_selector()
{
    pros::delay(300);

    //RED FRONT
    if (get_auton_select() > 0 && get_auton_select() < 1000)
    {
        selector = 1;
        return;
    }

    //BLUE FRONT
    else if (get_auton_select() > 1000 && get_auton_select() < 2000)
    {
        selector = 2;
        return;
    }

    //RED BACK
    else if (get_auton_select() > 2000 && get_auton_select() < 3000)
    {
        selector = 3;
        return;
    }

    //BLUE BACK
    else if (get_auton_select() > 3000 && get_auton_select() < 4096)
    {
        selector = 4;
        return;
    }
    return;
}

void tray_auto_reset(void *)
{
    while (true)
    {
        if (tray_pressed())
            reset_diff_encoder();
        pros::delay(10);    
    }
}