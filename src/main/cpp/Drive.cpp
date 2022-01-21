/******************************************************************************
    Description:	CDrive implementation
	Class:			CDrive
	Project:		2022 Rapid React Robot Code
******************************************************************************/

#include "Drive.h"

#include <frc/smartdashboard/SmartDashboard.h>
///////////////////////////////////////////////////////////////////////////////

/******************************************************************************
    Description:	CRobotMain constructor, init variables
	Arguments:		Joystick* pDriveController
	Derived from:	Nothing
******************************************************************************/
CDrive::CDrive(Joystick* pDriveController) 
{
	m_pDriveController		= pDriveController;
	m_pTimer				= new Timer();
	m_pLeadDriveMotor1		= new CFalconMotion(nLeadDriveMotor1);
	m_pFollowMotor1			= new WPI_TalonFX(nFollowDriveMotor1);
	m_pLeadDriveMotor2		= new CFalconMotion(nLeadDriveMotor2);
	m_pFollowMotor2			= new WPI_TalonFX(nFollowDriveMotor2);
	m_pRobotDrive			= new DifferentialDrive(*m_pLeadDriveMotor1->GetMotorPointer(), *m_pLeadDriveMotor2->GetMotorPointer());

	m_bJoystickControl = false;
}

/******************************************************************************
    Description:	CDrive destructor, delete variables
	Arguments:		None
	Derived from:	Nothing
******************************************************************************/
CDrive::~CDrive() 
{
	delete m_pDriveController;
	delete m_pLeadDriveMotor1;
	delete m_pLeadDriveMotor2;
	delete m_pFollowMotor1;
	delete m_pFollowMotor2;
	delete m_pRobotDrive;
	
	m_pDriveController	= nullptr;
	m_pLeadDriveMotor1	= nullptr;
	m_pLeadDriveMotor2	= nullptr;
	m_pFollowMotor1		= nullptr;
	m_pFollowMotor2		= nullptr;
	m_pRobotDrive		= nullptr;
}

/******************************************************************************
    Description:	Initialization function for CDrive, init motors
	Arguments:		None
	Returns:		Nothing
******************************************************************************/
void CDrive::Init()
{
	m_pLeadDriveMotor1->SetOpenLoopRampRate(dMotorOpenLoopRampRate);
	m_pLeadDriveMotor2->SetOpenLoopRampRate(dMotorOpenLoopRampRate);
	m_pFollowMotor1->ConfigOpenloopRamp(dMotorOpenLoopRampRate);
	m_pFollowMotor2->ConfigOpenloopRamp(dMotorOpenLoopRampRate);

	// Reset sticky faults
	m_pLeadDriveMotor1->ClearStickyFaults();
	m_pLeadDriveMotor2->ClearStickyFaults();
	m_pFollowMotor1->ClearStickyFaults();
	m_pFollowMotor2->ClearStickyFaults();

	// Set follow motors to followers of Drive Motor 1 and 2 respectively
	m_pFollowMotor1->Follow(*m_pLeadDriveMotor1->GetMotorPointer());
	m_pFollowMotor2->Follow(*m_pLeadDriveMotor2->GetMotorPointer());

	// Reset encoders and odometry
	ResetOdometry();

	m_pTimer->Start();
	// Reset encoders and odometry>
}

/******************************************************************************
    Description:	Tick function, ran every 20ms in CRobotMain::Tick()
	Arguments:		None
	Returns:		Nothing
******************************************************************************/
void CDrive::Tick()
{
	if (m_bJoystickControl)
	{
		// Set variables to joystick values.
		double dXAxis = m_pDriveController->GetRawAxis(eRightAxisX);
		double dYAxis = -m_pDriveController->GetRawAxis(eLeftAxisY);

		// Check if joystick is in deadzone.
		if (fabs(dXAxis) < dJoystickDeadzone)
		{
			dXAxis = 0.0;
		}
		if (fabs(dYAxis) < dJoystickDeadzone)
		{
			dYAxis = 0.0;
		}

		// Set drivetrain powers to joystick controls.
		m_pRobotDrive->ArcadeDrive(dYAxis, dXAxis, false);
	}

	// Update Smartdashboard values.
    SmartDashboard::PutNumber("LeftMotorPower", m_pLeadDriveMotor2->GetMotorVoltage());
    SmartDashboard::PutNumber("RightMotorPower", m_pLeadDriveMotor1->GetMotorVoltage());
    SmartDashboard::PutNumber("Left Actual Velocity", (m_pLeadDriveMotor2->GetActual(false) / 39.3701));
    SmartDashboard::PutNumber("Right Actual Velocity", (m_pLeadDriveMotor1->GetActual(false) / 39.3701));
    SmartDashboard::PutNumber("Left Actual Position", m_pLeadDriveMotor2->GetActual(true));
    SmartDashboard::PutNumber("Right Actual Position", m_pLeadDriveMotor1->GetActual(true));
}

/******************************************************************************
    Description:	Tick function, ran every 20ms in CRobotMain::Tick()
	Arguments:		None
	Returns:		Nothing
******************************************************************************/
void CDrive::Stop()
{
	m_pLeadDriveMotor1->Stop();
	m_pLeadDriveMotor2->Stop();
	m_bJoystickControl = false;

	// Update Smartdashboard values.
    SmartDashboard::PutNumber("LeftMotorPower", m_pLeadDriveMotor2->GetMotorVoltage());
    SmartDashboard::PutNumber("RightMotorPower", m_pLeadDriveMotor1->GetMotorVoltage());
    SmartDashboard::PutNumber("Left Actual Velocity", (m_pLeadDriveMotor2->GetActual(false) / 39.3701));
    SmartDashboard::PutNumber("Right Actual Velocity", (m_pLeadDriveMotor1->GetActual(false) / 39.3701));
    SmartDashboard::PutNumber("Left Actual Position", m_pLeadDriveMotor2->GetActual(true));
    SmartDashboard::PutNumber("Right Actual Position", m_pLeadDriveMotor1->GetActual(true));
}

/******************************************************************************
    Description:	Reset encoders and odometry
	Arguments:		None
	Returns:		Nothing
******************************************************************************/
void CDrive::ResetOdometry()
{
	m_pLeadDriveMotor1->ResetEncoderPosition();
}

/******************************************************************************
    Description:	Sets m_bJoystickControl to bJoystickControl
	Arguments:		bool bJoystickControl
	Returns:		Nothing
******************************************************************************/
void CDrive::SetJoystickControl(bool bJoystickControl)
{
	m_bJoystickControl = bJoystickControl;
}

/******************************************************************************
    Description:	Tells m_pRobotDrive to enforce motor safety
	Arguments:		bool bDriveSafety
	Returns:		Nothing
******************************************************************************/
void CDrive::SetDriveSafety(bool bDriveSafety)
{
	m_pRobotDrive->SetSafetyEnabled(bDriveSafety);
}