#include "main.h"

#include "main.h"

bool tray_mode = false;

/*void tray_outtake(void*){
	pros::Controller master(CONTROLLER_MASTER);
	drive_hold();
		if (get_tray() > TRAY_OUT)
		{
			while (get_tray() > TRAY_OUT)
			{
				if (get_tray() > 2670)
					set_diff(127);
				else if (get_tray() > TRAY_OUT)
				{
					set_diff(40);
					pros::delay(5);
					set_diff(20);
					pros::delay(120);
				}
				pros::delay(1);
			}
			diff_hold();
			set_diff(0);
		}
		else if (get_tray() < TRAY_BACK)
		{
			while (get_tray() < TRAY_BACK)
			{
				set_diff(-120);
				pros::delay(1);
			}
			diff_hold();
			set_diff(0);
		}
}
*/

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
		if (!tray_mode)
			set_tank(master.get_analog(ANALOG_LEFT_Y), master.get_analog(ANALOG_RIGHT_Y));
		pros::delay(20);
	}
}

const int TRAY_OUT = 5900;

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
			switch(counter)
			{
				case 0:
					while (!tray_pressed())
					{
						set_diff(127);
					}
					set_diff(0);
					reset_diff_encoder();
					counter++;
					break;
				case 1:
					while (get_tray() < 3500)
					{
						set_diff(-127);
					}
					while (get_tray() < TRAY_OUT)
						set_diff(-40);
					set_diff(0);
					counter = 0;
					break;
			}
		}
		pros::delay(20);
	}
}

/* void drive_control(void *)
{
	pros::Controller master(CONTROLLER_MASTER);

	drive_hold();
	diff_coast();

	//Sensor value for tray being back
	const int TRAY_BACK = 3000; //It's actually 0 but slight tolerance
	const int TRAY_OUT = 1760;

	//States
	const int DRIVE = 1;
	const int TRAY = 2;
	const int MOVING = 3;
	int state = DRIVE;

	while (true)
	{
		//Find the current state of the differential
		if (master.get_digital(DIGITAL_L1))
			state = TRAY;
		else if (abs(master.get_analog(ANALOG_LEFT_Y)) > 5 && abs(master.get_analog(ANALOG_RIGHT_Y)) > 5 && state != MOVING)
			state = DRIVE;

		//DRIVE STATE
		if (state == DRIVE)
		{
			pros::lcd::set_text(4, "WOAH WE'RE IN DRIVE MODE");
			set_tank(master.get_analog(ANALOG_LEFT_Y), master.get_analog(ANALOG_RIGHT_Y));
			set_diff(get_left_drive_spe(), get_right_drive_spe());
		}

		//TRAY STATE
		if (state == TRAY)
		{
			pros::lcd::set_text(4, "WOAH WE'RE IN TRAY MODE");
			drive_hold();
			if (get_tray() > TRAY_OUT)
			{
				while (get_tray() > TRAY_OUT)
				{
					if (get_tray() > 2670)
						set_diff(127);
					else if (get_tray() > TRAY_OUT)
					{
						set_diff(40);
						pros::delay(5);
						set_diff(20);
						pros::delay(120);
					}
					pros::delay(1);
				}
				diff_hold();
				set_diff(0);
			}
			else if (get_tray() < TRAY_BACK)
			{
				while (get_tray() < TRAY_BACK)
				{
					set_diff(-120);
					pros::delay(1);
				}
				diff_hold();
				set_diff(0);
			}
			state = MOVING;
		}

		if (state == MOVING)
		{
			if (get_diff_spe() == 0)
				state = DRIVE;
		}

		pros::delay(1);
	}
} */

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

void initialize() {
	pros::lcd::initialize();

	pros::lcd::register_btn1_cb(on_center_button);

	reset_drive_encoder();
	reset_intake_encoder();
	reset_diff_encoder();
}



void disabled() {}

void competition_initialize() {}

void autonomous() {
//move generate path to initialize
//this is for the left side of the field
	profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{4_ft, 0_ft, 0_deg}}, "A");
	profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{4_ft, 2_ft, 0_deg}}, "B");
	profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{3_ft, 0_ft, 180_deg}}, "C");

	drive_hold();

	profileController.setTarget("A");
	set_intake(-127);
	pros::delay(100);
	set_intake(127);
	profileController.waitUntilSettled();
	
	profileController.setTarget("B", true);
	set_intake(0);
	profileController.waitUntilSettled();
	chassisController.stop();
	profileController.flipDisable();
	set_tank(-40,-40);
	pros::delay(500);
	profileController.flipDisable();
	profileController.removePath("B");

	profileController.setTarget("A");
	set_intake(127);
	profileController.waitUntilSettled();
	profileController.removePath("A");
	
	profileController.setTarget("C", true);
	set_intake(0);
//	tray_outtake();
	profileController.removePath("C");

//s turn back to the first function
//curve to turn to the wall
//left motor higher		
}


void opcontrol() {
	pros::Controller master(CONTROLLER_MASTER);

	master.set_text(0, 0, "#ThankYou448X");

	pros::Task intake_control_t(intake_control, nullptr, "name");
	pros::Task drive_control_t(drive_control, nullptr, "name");
	pros::Task tray_control_t(tray_control, nullptr, "name");

	while (true)
	{
		pros::lcd::set_text(1, "Selector Value: " + std::to_string(selector));
		pros::lcd::set_text(2, "Tray Sensor:" + std::to_string(get_tray()));
		if(!tray_pressed())
		{
			pros::lcd::clear_line(3);
			pros::lcd::set_text(3, "Not pressed btw");
		}
		else if(tray_pressed())
		{
			pros::lcd::clear_line(3);
			pros::lcd::set_text(3, "Pressed btw");
		}
		else
		{
			pros::lcd::clear_line(3);
			pros::lcd::set_text(3, "Condition not true");
		}
		
		

		pros::delay(20);
	}
}
