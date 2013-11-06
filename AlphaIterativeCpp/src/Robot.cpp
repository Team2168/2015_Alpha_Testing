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
	Relay *shooterFire;

	//Shooter Angle Solenoid
	Relay *shooterAngle;



	virtual void RobotInit() {

		/*
		 * PWM 1 = left drive
		 * PMW 2 =  right drive
		 * PWM 3 = shooter moter forward
		 * PWM 4 = shooter moter rear.
		 * Relay 1 is shooter raise
		 * Relay 2 is shooter lower
		 * Relay 3 is fire extend
		 * Relay 4 is fire retract.
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
		 shooterAngle = new Relay(1,Relay::kBothDirections);
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

		if(Driver->GetRawButton(5))
			shooterAngle->Set(Relay::kForward);
		else
			shooterAngle->Set(Relay::kReverse);




	}

	virtual void TestPeriodic() {
		lw->Run();
	}
};

START_ROBOT_CLASS(Robot);
