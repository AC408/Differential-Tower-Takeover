#include "main.h"

void tray_outtake()
{
    while (get_tray() < 3500)
        set_diff(-127);
    while (get_tray() < TRAY_OUT)
        set_diff(-40);
}

void tray_intake()
{
    while (!tray_pressed())
        set_diff(127);
    set_diff(0);
    reset_diff_encoder();
}

void intake_control(void *)
{
    pros::Controller master(CONTROLLER_MASTER);
    intake_hold();
    while (true)
    {
        if (master.get_digital(DIGITAL_X) && master.get_digital(DIGITAL_R1))
            set_intake(60);
        else if (master.get_digital(DIGITAL_X) && master.get_digital(DIGITAL_R2))
            set_intake(-60);
        else if (master.get_digital(DIGITAL_R1))
            set_intake(127); //Intake
        else if (master.get_digital(DIGITAL_R2))
            set_intake(-127); //Outtake
        else
            set_intake(0); //No movement
        pros::delay(20);
    }
}

void drive_control(void *)
{
    pros::Controller master(CONTROLLER_MASTER);
    drive_coast();
    while (true)
    {
        set_tank(master.get_analog(ANALOG_LEFT_Y), master.get_analog(ANALOG_RIGHT_Y));
        pros::delay(20);
    }
}

void tray_control(void *)
{
    pros::Controller master(CONTROLLER_MASTER);
    int counter = 0;
    diff_hold();
    while (true)
    {
        if (master.get_digital(DIGITAL_L1))
        {
            while (master.get_digital(DIGITAL_L1))
                pros::delay(10);
            switch (counter)
            {
            case 0:
                tray_intake();
                counter++;
                break;

            case 1:
                tray_outtake();
                counter = 0;
                break;
            }
        }
        pros::delay(20);
    }
}