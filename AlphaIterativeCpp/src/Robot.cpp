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
#include "Can/PDP.h"

class Robot : public IterativeRobot {
public:
	LiveWindow *lw;

	//Can Objects
	//PDP *canPDP;

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

	//Reference parms
	double Voltage;

	//FLAGS
	//bool autoFinished;

	UINT8 chan;

	//Robot(){
	//		canPDP = 0;
	//}

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

		//;can init
		Voltage = 0;

		//PDP objects
		//canPDP = new PDP();

		chan = 1;
	}

	virtual void AutonomousInit() {

		shooterAngle->Set(Relay::kForward);
		rightDrive->SetSpeed(0);
		leftDrive->SetSpeed(0);

		shooterFWD->SetSpeed(1);
		shooterRear->SetSpeed(1);
		sleep(4);
		cout << "BEGIN" << endl;
		shooterFire->Set(Relay::kForward);
		sleep(1);
		shooterFire->Set(Relay::kReverse);
		sleep(1);

		//nanosleep(6);

		shooterFire->Set(Relay::kForward);
		sleep(1);
		shooterFire->Set(Relay::kReverse);
		sleep(1);

		shooterFire->Set(Relay::kForward);
		sleep(1);
		shooterFire->Set(Relay::kReverse);
		sleep(1);

		shooterFire->Set(Relay::kForward);
		sleep(1);
		shooterFire->Set(Relay::kReverse);
		sleep(2);

		shooterFWD->SetSpeed(0);
		shooterRear->SetSpeed(0);

		sleep(2);
		shooterAngle->Set(Relay::kReverse);

		cout << "END" << endl;
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

		//if(canPDP == 0){
		//	cout << "NULL" << endl;
		//}else{
			//canPDP->GetVoltage(Voltage) ;
			//cout << "0" << endl;
		//}

	}

	virtual void TestPeriodic() {
		lw->Run();
	}
};

START_ROBOT_CLASS(Robot);
