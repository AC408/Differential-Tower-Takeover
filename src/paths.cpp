#include "main.h"

void init_skills()
{
}

void init_pr()
{
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{2_ft, 0_ft, 0_deg}}, "A");
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{4_ft, 0_ft, 0_deg}}, "B");
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{6_ft, 2_ft, 0_deg}}, "C");
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{6_ft, 0_ft, 0_deg}}, "D");
}

void init_pb()
{
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{2_ft, 0_ft, 0_deg}}, "A");
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{4_ft, 0_ft, 0_deg}}, "B");
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{6_ft, -2_ft, 0_deg}}, "C");
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{6_ft, 0_ft, 0_deg}}, "D");
}

void init_upr()
{
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{4_ft, 0_ft, 0_deg}}, "A");
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{4_ft, 2_ft, 0_deg}}, "B");
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{4_ft, -2_ft, 95_deg}}, "C");
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{3_ft, 0_ft, 0_deg}}, "D");
}

void init_upb()
{
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{4_ft, 0_ft, 0_deg}}, "A");
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{4_ft, -2_ft, 0_deg}}, "B");
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{4_ft, 2_ft, 275_deg}}, "C");
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{3_ft, 0_ft, 0_deg}}, "D");
}

void skills()
{
}

//front is protect
//back is unprotected

void pro_red()
{
    set_intake(127);
    profileController.setTarget("A");
    profileController.waitUntilSettled();
    chassisController.turnAngle(270);
    profileController.setTarget("B");
    profileController.waitUntilSettled();
    set_intake(0);
    profileController.setTarget("C", true);
    profileController.waitUntilSettled();
    set_intake(127);
    profileController.setTarget("D");
    profileController.waitUntilSettled();
    set_intake(0);
}

void pro_blue()
{
    set_intake(127);
    profileController.setTarget("A");
    profileController.waitUntilSettled();
    chassisController.turnAngle(90);
    profileController.setTarget("B");
    profileController.waitUntilSettled();
    set_intake(0);
    profileController.setTarget("C", true);
    profileController.waitUntilSettled();
    set_intake(127);
    profileController.setTarget("D");
    profileController.waitUntilSettled();
    set_intake(0);
}

void unpro()
{
    //Set brakes
    drive_hold();
    diff_hold();
    intake_hold();

    //Deploy
    set_intake(-127);
    pros::delay(100);

    //First row
    set_intake(127);
    profileController.setTarget("A");
    profileController.waitUntilSettled();
    set_intake(0);

    //Sexy S curve
    profileController.setTarget("B", true);
    profileController.waitUntilSettled();
    chassisController.stop();
    profileController.flipDisable();

    //Align
    set_tank(-40, -40);
    pros::delay(500);
    profileController.flipDisable();
    profileController.removePath("B");

    //Second row
    set_intake(127);
    profileController.setTarget("A");
    profileController.waitUntilSettled();
    profileController.removePath("A");
    set_intake(0);

    //Turn owo
    profileController.setTarget("C", true);
    profileController.removePath("C");

    //Drive forward
    profileController.setTarget("D");
    profileController.removePath("D");

    //Deploy
    tray_outtake();
    set_tank(-70, -70);
    pros::delay(1000);
    tray_intake();
}