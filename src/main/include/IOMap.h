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
const int nLeadDriveMotor1              =   1;      // Right Lead Drive Motor (Falcon 500)
const int nLeadDriveMotor2              =   2;      // Left Lead Drive Motor   |
const int nFollowDriveMotor1            =   3;      // Right Follow Motor      |
const int nFollowDriveMotor2            =   4;      // Left Follow Motor       |
const int nFlywheelMotor                =   5;      // flywheel motor         \|/
const int nBeltMotor1                   =   6;      // Front belt motor       (NEO)
const int nBeltMotor2                   =   7;      // Back belt motor        \|/

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