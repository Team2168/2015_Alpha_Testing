
package com.first.team2168.robot;

import edu.wpi.first.wpilibj.DigitalInput;
import edu.wpi.first.wpilibj.IterativeRobot;
import edu.wpi.first.wpilibj.Joystick;
import edu.wpi.first.wpilibj.Relay;
import edu.wpi.first.wpilibj.Relay.Direction;
import edu.wpi.first.wpilibj.Relay.Value;
import edu.wpi.first.wpilibj.Victor;
import edu.wpi.first.wpilibj.Talon;


/**
 * The VM is configured to automatically run this class, and to call the
 * functions corresponding to each mode, as described in the IterativeRobot
 * documentation. If you change the name of this class or the package after
 * creating this project, you must also update the manifest file in the resource
 * directory.
 */
public class Robot extends IterativeRobot {

	// Joysticks Objects
	Joystick driver;
	Joystick operator;

	// Drive Moter Objects
	Victor leftDrive;
	Victor rightDrive;

	// Drive Shooter Objects
	Talon shooterFWD;
	Talon shooterRear;

	// Shooter Double Solenoid
	Relay shooterFire;

	// Shooter Angle Solenoid
	Relay shooterAngle;
	Relay CompressorRelay;

	// Switches
	DigitalInput CompressorSwitch;

	/**
	 * This function is run when the robot is first started up and should be
	 * used for any initialization code.
	 */
	public void robotInit() {

		// Initialize joysticks
		driver = new Joystick(1);
		operator = new Joystick(2);

		// Initialize drive talons
		rightDrive = new Victor(4);
		leftDrive = new Victor(3);

		// initialize shooter talons
		shooterFWD = new Talon(1);
		shooterRear = new Talon(2);

		// initialize shooter angle
		shooterAngle = new Relay(2, Direction.kBoth);
		shooterFire = new Relay(3, Direction.kBoth);

		CompressorRelay = new Relay(4, Direction.kForward);

		// initialize compressor switch
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
		if(Math.abs(driver.getRawAxis(5)) > 0.35) {
			rightDrive.set(driver.getRawAxis(5));
		} else {
			rightDrive.set(0.0);
		}
		if(Math.abs(driver.getRawAxis(2)) > 0.28) {
			leftDrive.set(-driver.getRawAxis(2));
		} else {
			leftDrive.set(0.0);
		}

		if (operator.getRawButton(6)) {
			shooterAngle.set(Value.kForward);
		} else if (operator.getRawButton(5)) {
			shooterAngle.set(Value.kReverse);
		}

		if (operator.getRawButton(2)) {
			shooterFire.set(Value.kForward);
		} else if (operator.getRawButton(1)) {
			shooterFire.set(Value.kReverse);
		}

		//Shooter Wheel - Left stick
		if(operator.getRawAxis(2) <= 0) {
			shooterFWD.set(-operator.getRawAxis(2));
			shooterRear.set(-operator.getRawAxis(2));
		}
		
		
		if (!CompressorSwitch.get()) {
			CompressorRelay.set(Value.kOn);
		} else {
			CompressorRelay.set(Value.kOff);
		}
	}

	/**
	 * This function is called periodically during test mode
	 */
	public void testPeriodic() {

	}

