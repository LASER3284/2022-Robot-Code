/****************************************************************************
    Description:	Defines the 2022 Testboard I/O map.
    Classes:		None
    Project:		2022 Rapid React Robot Code
****************************************************************************/

#ifndef IOMap_h
#define IOMap_h
/////////////////////////////////////////////////////////////////////////////

// Global Motor Constants.
const double dMotorOpenLoopRampRate		= 0.650;

// Solenoid Channels.
const int nSolenoid1                    =   0;      // Solenoid channel for solenoid 1.
const int nSolenoid2                    =   1;      // Solenoid channel for solenoid 2.

// CAN Device IDs.
const int nLeadDriveMotor1              =   1;      // Right Lead Drive Motor (TALON FX controller)
const int nLeadDriveMotor2              =   2;      // Left Lead Drive Motor   |
const int nFollowDriveMotor1            =   3;      // Right Follow Motor      |
const int nFollowDriveMotor2            =   4;      // Left Follow Motor       |
const int nFlywheelMotor1               =   5;      // Right flywheel motor    |
const int nFlywheelMotor2               =   6;      // Left flywheel motor     |
const int nLiftMotor1                   =   7;      // Far left lift motor     |
const int nLiftMotor2                   =   8;      // Far right lift motor    |
const int nLiftMotor3                   =   9;      // Inner left lift motor  \|/
const int nLiftMotor4                   =  10;      // Inner right lift motor (TALON FX controller)
const int nIntakeMotor1                 =  11;      // Intake motor one       (SPARK MAX controller) NOTE: config unkown, labels will be determined later
const int nIntakeMotor2                 =  12;      // Intake motor two        |
const int nIntakeMotor3                 =  13;      // Intake motor three      |
const int nIntakeMotor4                 =  14;      // Intake motor four      \|/
const int nTurretMotor                  =  15;      // Turret rotation motor  (SPARK MAX controller)
const int nBeltMotor1                   =  16;      // Front belt motor       (SPARK MAX controller)
const int nBeltMotor2                   =  17;      // Back belt motor        \|/
const int nBeltMotor3                   =  18;      // Top belt motor         (SPARK MX controller)

// PWM Channels.
const int nBlinkinID					=	1;		// PWM channel for Blinkin LED driver

// Relay Channels.

// Analog Channels.

// Digital Channels.

// Xbox Controller Button Assignments.
enum XboxButtons 		{eButtonA = 1, eButtonB, eButtonX, eButtonY, eButtonLB, eButtonRB, eBack, eStart, eButtonLS, eButtonRS};
// Xbox Controller Axis Assignments.
enum XboxAxis			{eLeftAxisX = 0, eLeftAxisY, eLeftTrigger, eRightTrigger, eRightAxisX, eRightAxisY};
// Logitech Flight Stick Button Assignments.
enum LogButtons	 		{eButtonTrigger = 1, eButton2, eButton3, eButton4, eButton5, eButton6, eButton7, eButton8, eButton9, eButton10, eButton11, eButton12};
// Shared Robot states for Motion.
enum State              {eIdle, eHomingReverse, eHomingForward, eFinding, eManualForward, eManualReverse};
/////////////////////////////////////////////////////////////////////////////
#endif