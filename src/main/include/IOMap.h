/******************************************************************************
    Description:	Defines the 2022 Testboard I/O map.
    Classes:		None
    Project:		2022 Rapid React Robot Code
******************************************************************************/

#ifndef IOMap_h
#define IOMap_h
/////////////////////////////////////////////////////////////////////////////

// Global Motor Constants.
const double dMotorOpenLoopRampRate		= 0.650;

// Solenoid Channels.
const int nSolenoid1                    =   0;      // Solenoid channel for solenoid 1.
const int nSolenoid2                    =   1;      // Solenoid channel for solenoid 2.

// CAN Device IDs.
const int nLeadDriveMotor1              =   1;      // Right Lead Drive Motor   (TALON FX controller)
const int nLeadDriveMotor2              =   3;      // Left Lead Drive Motor    (TALON FX controller)
const int nFollowDriveMotor1            =   2;      // Right Follow Motor       (TALON FX controller)
const int nFollowDriveMotor2            =   4;      // Left Follow Motor        (TALON FX controller)
const int nFlywheelMotor1               =   5;      // Right flywheel motor     (TALON FX controller)
const int nFlywheelMotor2               =   6;      // Left flywheel motor      (TALON FX controller)
const int nLiftMotor1                   =   7;      // Far left lift motor      (TALON FX controller)
const int nLiftMotor2                   =   8;      // Far right lift motor     (TALON FX controller)
const int nPneumaticsHub                =   9;      // REV Pneumatics Hub       [MUST BE MANUALLY ASSIGNED]
const int nIntakeMotor1                 =  10;      // Intake motor one         (SPARK MAX controller)
const int nIntakeMotor2                 =  11;      // Intake motor three       (SPARK MAX controller)
const int nTurretMotor                  =  12;      // Turret rotation motor    (SPARK MAX controller)
const int nBeltMotor1                   =  13;      // Front belt motor         (SPARK MAX controller)
const int nBeltMotor2                   =  14;      // Back belt motor          (SPARK MAX controller)
const int nBeltMotor3                   =  15;      // Top belt motor           (SPARK MAX controller)
const int nIntakeDeployMotor1           =  16;      // Intake Deploy motor one  (TALON SRX controller)
const int nIntakeDeployMotor2           =  17;      // Intake Deploy motor two  (TALON SRX controller)
const int nIntakeDeployMotor3           =  18;
const int nIntakeDeployMotor4           =  19;      

// PWM Channels.
const int nBlinkinID					=	1;		// PWM channel for Blinkin LED driver

// Relay Channels.

// Analog Channels.

// Digital Channels.
const int nFrontIntakeDownLS            =   0;
const int nFrontIntakeUpLS              =   1;
const int nBackIntakeDownLS             =   2;
const int nBackIntakeUpLS               =   3;

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