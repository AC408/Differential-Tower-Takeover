#include "main.h"

bool tray_mode = false;

void on_center_button()
{
	static bool pressed = false;
	pressed = !pressed;
	if (pressed)
		pros::lcd::set_text(2, "I was pressed!");
	else
		pros::lcd::clear_line(2);
}

void preauton(){
	//Set brakes
	drive_hold();
	diff_hold();
	intake_hold();

	//Deploy
	set_intake(-127);
	pros::delay(100);
}

//--------------------------------------------------------------------------------------------------

void initialize()
{
	pros::lcd::initialize();
	pros::lcd::register_btn1_cb(on_center_button);

	auto_selector();
/*
	if (selector == 1)
		init_pb();
	if (selector == 2)
		init_pr();
	if (selector == 3)
		init_upb();
	if (selector == 4)
		init_upr();
*/
	//Reset encoders
	reset_drive_encoder();
	reset_intake_encoder();
	reset_diff_encoder();
	//init_upb();

}

void disabled() {}

void competition_initialize() {}

//----------------------------------------------------------------------------

void autonomous() {
	
	//Reset encoders
	reset_drive_encoder();
	reset_intake_encoder();
	reset_diff_encoder();

	pros::Task tray_reset_t(tray_auto_reset, nullptr, "name");
	//preauton();
	//unpro();
	timeTime();
/*
	if (selector == 1)
		unpro();
	if (selector == 2)
		unpro();
	if (selector == 3)
		unpro();
	if (selector == 4)
		unpro();
*/
	//skills();
}

//-----------------------------------------------------------------------

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
		pros::lcd::set_text(3, "Number: " + std::to_string(get_auton_select()));

		pros::delay(20);
	}
}
