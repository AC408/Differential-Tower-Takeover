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
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{4_ft, -2_ft, 0_deg}}, "B");
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{4_ft, -2_ft, 275_deg}}, "C");
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{3_ft, 0_ft, 0_deg}}, "D");
}

void init_upb_maybe()
{
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{2_ft, 0_ft, 0_deg}}, "A");
    //25_in
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{4_ft, 2.2_ft, 0_deg}}, "B");
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{4_ft, -2_ft, 95_deg}}, "C");
    //53.5_in
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{2.55_ft, 0_ft, 0_deg}}, "D");
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{.458_ft, 0_ft, 0_deg}}, "E");
    //5.5_in
}

void init_upb(){
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{30.5_in, 0_ft, 0_deg}}, "A");
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{.458_ft, 0_ft, 0_deg}}, "B");
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{.916_ft, 0_ft, 0_deg}},"E");
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{43.5_in, 2_ft, 4.5_deg}}, "C");
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{4_ft, -1_ft, 95_deg}}, "D");
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{1_ft, 0_ft, 0_deg}}, "F");
    
    //intake, 
    //30.5_ft
    //E,E
    //s-curve (may need to chunk)
    //intake, A, E, E, E, intake, C, D, deploy
}

void skills()
{
}

void pro_red()
{
    //forward
    set_intake(127);
    profileController.setTarget("A");
    profileController.waitUntilSettled();
    profileController.removePath("A");
    
    //perpendicular row
    chassisController.turnAngle(270);
    profileController.setTarget("B");
    profileController.waitUntilSettled();
    profileController.removePath("B");
    set_intake(0);

    //s curve to second row
    profileController.setTarget("C", true);
    profileController.waitUntilSettled();
    profileController.removePath("C");
    set_intake(127);

    //second row
    profileController.setTarget("D");
    profileController.waitUntilSettled();
    profileController.removePath("D");
    set_intake(0);
}

void pro_blue()
{
    //forward
    set_intake(127);
    profileController.setTarget("A");
    profileController.waitUntilSettled();
    profileController.removePath("A");
    
    //perpendicular row
    chassisController.turnAngle(90);
    profileController.setTarget("B");
    profileController.waitUntilSettled();
    profileController.removePath("B");
    set_intake(0);

    //s curve to second row
    profileController.setTarget("C", true);
    profileController.waitUntilSettled();
    profileController.removePath("C");
    set_intake(127);

    //second row
    profileController.setTarget("D");
    profileController.waitUntilSettled();
    profileController.removePath("D");
    set_intake(0);
    
}

void unpro(){
    /*
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{30.5_in, 0_ft, 0_deg}}, "A");
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{.458_ft, 0_ft, 0_deg}}, "B");
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{.916_ft, 0_ft, 0_deg}},"E");
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{4_ft, 53.5_in, 0_deg}}, "C");
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{4_ft, 0_ft, 95_deg}}, "D");
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{1_ft, 0_ft, 95_deg}}, "F");
 */

    //drive forward
    set_intake(127);
    profileController.setTarget("A");
    profileController.waitUntilSettled();
    profileController.setTarget("B");
    profileController.waitUntilSettled();
    profileController.setTarget("E");
    profileController.waitUntilSettled();
    profileController.removePath("E");

    //s curve
    set_intake(0);
    profileController.setTarget("C",true);
    profileController.waitUntilSettled();
    profileController.removePath("C");
    
    //driv forward, second row
    set_intake(127);
    profileController.setTarget("A");
    profileController.waitUntilSettled();
    profileController.removePath("A");
    profileController.setTarget("B");
    profileController.waitUntilSettled();
    profileController.removePath("B");
    set_intake(0);

    //curve to face zone
    profileController.setTarget("D", true);
    profileController.waitUntilSettled();
    profileController.removePath("D");
    profileController.setTarget("F");
    profileController.waitUntilSettled();

    //outtake
    tray_outtake();
    profileController.setTarget("F", true);
    profileController.waitUntilSettled();
    profileController.removePath("F");
}




void unpro_maybe()
{
    //intake, 
    //30.5_ft
    //E,E
    //s-curve (may need to chunk)
    //intake, A, E, E, E, intake, C, D, deploy

    //First row
    set_intake(127);
    profileController.setTarget("A");
    profileController.waitUntilSettled();
    profileController.removePath("A");
    profileController.setTarget("E");
    profileController.waitUntilSettled();
    profileController.setTarget("E");
    profileController.waitUntilSettled();
    profileController.setTarget("E");
    profileController.waitUntilSettled();
    profileController.setTarget("E");
    profileController.waitUntilSettled();
    profileController.removePath("E");
    set_intake(0);

    //Turn owo
    profileController.setTarget("C", true);
    profileController.waitUntilSettled();
    profileController.removePath("C");


    //Drive forward
    profileController.setTarget("D");
    profileController.waitUntilSettled();
    profileController.removePath("D");
    set_intake(-50);
    pros::delay(300);
    
    //Deploy
    //make this a function
    pros::delay(300);
    set_intake(0);
    tray_outtake();
    set_tank(-70,-70);
    pros::delay(100);
    tray_intake();
    set_tank(0,0);
}

void full()
{
    //First row
    set_intake(127);
    profileController.setTarget("A");
    profileController.waitUntilSettled();
    profileController.setTarget("E");
    profileController.waitUntilSettled();
    profileController.setTarget("E");
    profileController.waitUntilSettled();
    profileController.setTarget("E");
    profileController.waitUntilSettled();
    profileController.setTarget("E");
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
    profileController.setTarget("E");
    profileController.waitUntilSettled();
    profileController.setTarget("E");
    profileController.waitUntilSettled();
    profileController.setTarget("E");
    profileController.waitUntilSettled();
    profileController.setTarget("E");
    profileController.waitUntilSettled();
    profileController.setTarget("E");
    profileController.waitUntilSettled();
    profileController.removePath("E");
    set_intake(0);

    //Turn 
    profileController.setTarget("C", true);
    profileController.waitUntilSettled();
    profileController.removePath("C");


    //Drive forward
    profileController.setTarget("D");
    profileController.waitUntilSettled();
    profileController.removePath("D");

    
    //Deploy
    tray_outtake();
    set_tank(-100,-100);
    pros::delay(100);
    tray_intake();
}

void blueTime(){
   /*
    set_intake(-127);
    pros::delay(200);
    set_intake(0);
    intake_hold();

    set_intake(127);
    set_tank(55, 55);
    pros::delay(440);

    set_tank(90, 90);
    pros::delay(1300);

    set_tank(-80, -80);
    pros::delay(1200);

    set_tank(80, -80);
    pros::delay(290);
    
    set_tank(-80, -80);
    pros::delay(900);
    
    set_tank(-80, 80);
    pros::delay(290);

    set_tank(-90, -90);
    pros::delay(900);
*/
    //Row of 4
    set_intake(-127);
    pros::delay(400);
    set_intake(127);
    intake_hold();

    set_tank(50, 50);
    pros::delay(2700);

    //Drive Back a Bit and Turn
    set_tank(-50, -50);
    pros::delay(1400);
    
    set_tank(-60, 60);
    pros::delay(950);

    //Drive towards zone 
    set_tank(50, 50);
    pros::delay(1500);
    set_tank(0,0);

    set_intake(-127);
    pros::delay(250);
    set_intake(0);

    //outtake
    tray_outtake();

    //drive back
    set_tank(-40, -40);
    pros::delay(800);
    set_tank(0,0);
}

void redTime()
{
    //Row of 4
    set_intake(-127);
    pros::delay(400);
    set_intake(127);
    intake_hold();

    set_tank(50, 50);
    pros::delay(2700);

    //Drive Back a Bit and Turn
    set_tank(-50, -50);
    pros::delay(1400);
    
    set_tank(60, -60);
    pros::delay(950);

    //Drive towards zone 
    set_tank(50, 50);
    pros::delay(1500);
    set_tank(0,0);

    set_intake(-127);
    pros::delay(250);
    set_intake(0);

    //outtake
    tray_outtake();

    //drive back
    set_tank(-40, -40);
    pros::delay(800);
    set_tank(0,0);
}