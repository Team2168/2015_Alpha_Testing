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

	//Compressor Relay
	Relay *CompressorRelay;

	//Switches
	DigitalInput *CompressorSwitch;


	virtual void RobotInit() {

		/*
		 * PWM 9 = left drive
		 * PMW 10 =  right drive
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
		rightDrive = new Talon(9);
		leftDrive = new Talon(10);

		//initialize shooter talons
		shooterFWD = new Talon(3);
		shooterRear = new Talon(4);


		//initialize shooter angle
		 shooterAngle = new Relay(1,Relay::kBothDirections);
		 shooterFire = new Relay(2,Relay::kBothDirections);


		 CompressorRelay = new Relay(3,Relay::kForwardOnly);

		//initialize compressor switch
		CompressorSwitch = new DigitalInput(10);
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


		shooterFWD->SetSpeed(-(Operator->GetRawAxis(2)));
		shooterRear->SetSpeed(-(Operator->GetRawAxis(2)));


		//shoioter angle
		if(Operator->GetRawButton(5))
		{
			cout<<"Relay 1 forward"<<endl;
			shooterAngle->Set(Relay::kForward);
		}

		if(Operator->GetRawButton(6))
		{
			cout<<"Relay 1 Reverse"<<endl;
			shooterAngle->Set(Relay::kReverse);
		}


		//Fire button
		if(Operator->GetRawButton(1))
		{
			cout<<"Relay 1 forward"<<endl;
			shooterFire->Set(Relay::kForward);
		}

		if(Operator->GetRawButton(2))
		{
			cout<<"Relay 1 Reverse"<<endl;
			shooterFire->Set(Relay::kReverse);
		}

		if(CompressorSwitch->Get() == 0){
			CompressorRelay->Set(Relay::kForward);
		}else{
			CompressorRelay->Set(Relay::kOff);
		}

	}

	virtual void TestPeriodic() {
		lw->Run();
	}
};

START_ROBOT_CLASS(Robot);
