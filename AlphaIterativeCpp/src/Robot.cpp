//============================================================================
// Name        : Robot.cpp
// Author      :
// Version     :
// Copyright   :
// Description : Hello World in C++, Ansi-style
//============================================================================

//============================================================================
// Name        : Robot.cpp
// Author      :
// Version     :
// Copyright   :
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "WPILib.h"
#include "Joystick.h"


class Robot : public IterativeRobot {
private:
	LiveWindow *lw;
	
	//Joysticks Objects
	Joystick *Driver;
	Joystick *Operator;

	//Drive Moter Objects
	Talon *leftDrive;
	Talon *rightDrive;

	//Drive Shooter Objects
	Talon *shooterFWD;
	Talon *shooterRear;

	//Shooter Double Solenoid
	DoubleSolenoid *shooterFire;

	//Shooter Angle Solenoid
	DoubleSolenoid *shooterAngle;

	//Speed variables
	//double leftSpeed;
	//double rightSpeed;

	virtual void RobotInit() {

		/*
		 * PWM 1 is left drive
		 * PMW 2 is right drive
		 * PWM 3 is shooter moter forward
		 * PWM 4 is shooter moter rear.
		 * Relay Chanel 1 is shooter raise
		 * Relay Channel 2 is shooter lower
		 * Relay Channel 3 is fire extend
		 * Relay Channel 4 is fire retract.
		 *
		 */


		lw = LiveWindow::GetInstance();

		//Initialize joysticks
		Driver = new Joystick(1);
		Operator = new Joystick(2);

		//Initialize drive talons
		rightDrive = new Talon(1);
		leftDrive = new Talon(2);

		//initialize shooter talons
		shooterFWD = new Talon(3);
		shooterRear = new Talon(4);

		//initialize shooter angle
		// shooterAngle = new DoubleSolenoid(1,2);
	}
	
	virtual void AutonomousInit() {

	}
	
	virtual void AutonomousPeriodic() {

	}
	
	virtual void TeleopInit() {

	}
	
	virtual void TeleopPeriodic() {

		rightDrive->SetSpeed(-(Driver->GetRawAxis(2)));
		leftDrive->SetSpeed((Driver->GetRawAxis(5)));


		shooterFWD->SetSpeed(-(Operator->GetRawAxis(5)));
		shooterRear->SetSpeed(-(Operator->GetRawAxis(5)));




	}
	
	virtual void TestPeriodic() {
		lw->Run();
	}
};

START_ROBOT_CLASS(Robot);
