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

// CAN Device IDs.
const int nLeadDriveMotor1              =   1;      // Left LD motor            (TALON FX/FALCON 500)
const int nFollowDriveMotor1            =   2;      // Left FD motor            (TALON FX/FALCON 500)
const int nLeadDriveMotor2              =   3;      // Right LD motor           (TALON FX/FALCON 500)
const int nFollowDriveMotor2            =   4;      // Right FD motor           (TALON FX/FALCON 500)
const int nFlywheelMotor1               =   5;      // First flywheel motor     (TALON FX/FALCON 500)
const int nFlywheelMotor2               =   6;      // Second flywheel motor    (TALON FX/FALCON 500)
const int nLiftMotor1                   =   7;      // 
const int nLiftMotor2                   =   8;      // 
//const int nPneumatics                   =   9;      // REV Pneumatics Hub
//const int nIntakeMotor1                 =  10;      // Front intake motor       (SPARK MAX)
const int nIntakeMotor2                 =  11;      // Back intake motor        (SPARK MAX)
const int nTransferFront                =  12;      // Front transfer motor     (SPARK MAX)
const int nTransferBack                 =  13;      // Back transfer motor      (SPARK MAX)
const int nTransferVertical             =  14;      // Vertical transfer motor  (SPARK MAX)
//const int nIntakeDeployMotor1           =  16;      // Front intake deploy BAGs (TALON SRX)
const int nIntakeDeployMotor2           =  17;      // Back intake deploy BAGs  (TALON SRX)
const int nHoodMotor                    =  20;      // Hood motor ID            (SPARK MAX)

// PWM Channels.

// Relay Channels.

// Analog Channels.

// Digital Channels.
const int nBackIntakeDownLS             =   0;
const int nBackIntakeUpLS               =   1;
const int nBackTransferInfrared         =   2;
const int nTopTransferInfrared          =   3;

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