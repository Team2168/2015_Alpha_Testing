
package com.first.team2168.robot;

import edu.wpi.first.wpilibj.DigitalInput;
import edu.wpi.first.wpilibj.IterativeRobot;
import edu.wpi.first.wpilibj.Joystick;
import edu.wpi.first.wpilibj.Relay;
import edu.wpi.first.wpilibj.Relay.Direction;
import edu.wpi.first.wpilibj.Relay.Value;
import edu.wpi.first.wpilibj.Talon;

/**
 * The VM is configured to automatically run this class, and to call the
 * functions corresponding to each mode, as described in the IterativeRobot
 * documentation. If you change the name of this class or the package after
 * creating this project, you must also update the manifest file in the resource
 * directory.
 */
public class Robot extends IterativeRobot {
	
	//Joysticks Objects
	Joystick Driver;
	Joystick Operator;

	//Drive Moter Objects
	Talon leftDrive;
	Talon rightDrive;

	//Drive Shooter Objects
	Talon shooterFWD;
	Talon shooterRear;

	//Shooter Double Solenoid
	Relay shooterFire;

	//Shooter Angle Solenoid
	Relay shooterAngle;
	Relay CompressorRelay;


	//Switches
	DigitalInput CompressorSwitch;
	
    /**
     * This function is run when the robot is first started up and should be
     * used for any initialization code.
     */
    public void robotInit() {
    	
    	//Driver = new Joystick(1);
		//Operator = new Joystick(2);
    	
		//rightDrive = new Talon(9);
		//leftDrive = new Talon(10);
    	
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
		 shooterAngle = new Relay(1, Direction.kBoth);
		 shooterFire = new Relay(2, Direction.kBoth);


		 CompressorRelay = new Relay(3,Direction.kForward);

		//initialize compressor switch
		CompressorSwitch = new DigitalInput(10);
    	
    }

    /**
     * This function is called periodically during autonomous
     */
    public void autonomousPeriodic() {

    }

    /**
     * This function is called periodically during operator control
     */
    public void teleopPeriodic() {
        rightDrive.set(-Driver.getRawAxis(2));
        leftDrive.set(Driver.getRawAxis(5));
        
        
        
        if(Operator.getRawButton(6))
		{
			//cout<<"Relay 1 forward"<<endl;
			shooterAngle.set(Value.kForward);
		}

		if(Operator.getRawButton(5))
		{
			//cout<<"Relay 1 Reverse"<<endl;
			shooterAngle.set(Value.kReverse);
		}


		//Fire button
		if(Operator.getRawButton(2))
		{
			//cout<<"Relay 1 forward"<<endl;
			shooterFire.set(Value.kForward);
		}

		if(Operator.getRawButton(1))
		{
			//cout<<"Relay 1 Reverse"<<endl;
			
			shooterFire.set(Value.kReverse);
		}

		//System.out.println(CompressorSwitch.get());
		if(!CompressorSwitch.get()){
			CompressorRelay.set(Value.kOn);
		}else{
			CompressorRelay.set(Value.kOff);
		}
        
    }
    
    /**
     * This function is called periodically during test mode
     */
    public void testPeriodic() {
    
    }
    
}
