/******************************************************************************
    Description:	CRobotMain implementation
	Classes:		CRobotMain
	Project:		2022 Rapid React Robot Code
******************************************************************************/

#include "RobotMain.h"

#include <fmt/core.h>
#include <frc/smartdashboard/SmartDashboard.h>
///////////////////////////////////////////////////////////////////////////////
using namespace frc;
using namespace std;

/******************************************************************************
    Description:	CRobotMain constructor - initialize local variables
	Arguments:		None
	Derived from:	TimedRobot
******************************************************************************/
CRobotMain::CRobotMain()
{
	m_pDriveController			= new Joystick(0);
	m_pAuxController			= new Joystick(1);
	m_pDrive					= new CDrive(m_pDriveController);
	m_pAutoChooser				= new SendableChooser<string>();
}

/******************************************************************************
    Description:	CRobotMain destructor - delete local variables
	Arguments:		None
	Derived from:	TimedRobot
******************************************************************************/
CRobotMain::~CRobotMain()
{
	delete m_pDriveController;
	delete m_pAuxController;
	delete m_pDrive;
	delete m_pAutoChooser;


	m_pDriveController	= nullptr;
	m_pAuxController	= nullptr;
	m_pDrive			= nullptr;
	m_pAutoChooser		= nullptr;
}

/******************************************************************************
    Description:	Global robot initialization function
	Arguments:		None
	Returns:		Nothing
******************************************************************************/
void CRobotMain::RobotInit()
{
	// Setup autonomous chooser.
	m_pAutoChooser->SetDefaultOption("Autonomous Idle", "Autonomous Idle");
	m_pAutoChooser->AddOption("Alliance Trench", "Alliance Trench");
	m_pAutoChooser->AddOption("Front Shield Generator", "Front Shield Generator");
	m_pAutoChooser->AddOption("Side Shield Generator", "Side Sheild Generator");
	m_pAutoChooser->AddOption("Opposing Trench", "Opposing Trench");
	m_pAutoChooser->AddOption("Power Port", "Power Port");
	m_pAutoChooser->AddOption("Test Path", "Test Path");
	SmartDashboard::PutData(m_pAutoChooser);
}

/******************************************************************************
    Description:	Global robot 20ms periodic function
	Arguments:		None
	Returns:		Nothing
******************************************************************************/
void CRobotMain::RobotPeriodic()
{

}

/******************************************************************************
    Description:	Autonomous initialization function
	Arguments:		None
	Returns:		Nothing
******************************************************************************/
void CRobotMain::AutonomousInit()
{
	m_pDrive->Init();
	m_pDrive->SetJoystickControl(false);
}

/******************************************************************************
    Description:	Autonomous 20ms periodic function
	Arguments:		None
	Returns:		Nothing
******************************************************************************/
void CRobotMain::AutonomousPeriodic() 
{

}

/******************************************************************************
    Description:	Teleop initialization function
	Arguments:		None
	Returns:		Nothing
******************************************************************************/
void CRobotMain::TeleopInit()
{

}

/******************************************************************************
    Description:	Teleop 20ms periodic function
	Arguments:		None
	Returns:		Nothing
******************************************************************************/
void CRobotMain::TeleopPeriodic()
{

}

/******************************************************************************
    Description:	Disabled initialization function
	Arguments:		None
	Returns:		Nothing
******************************************************************************/
void CRobotMain::DisabledInit()
{
	m_pDrive->SetJoystickControl(false);
	m_pDrive->SetDriveSafety(true);
}

/******************************************************************************
    Description:	Disabled 20ms periodic function
	Arguments:		None
	Returns:		Nothing
******************************************************************************/
void CRobotMain::DisabledPeriodic()
{

}

/******************************************************************************
    Description:	Test initialization function
	Arguments:		None
	Returns:		Nothing
******************************************************************************/
void CRobotMain::TestInit()
{

}

/******************************************************************************
    Description:	Test 20ms periodic function
	Arguments:		None
	Returns:		Nothing
******************************************************************************/
void CRobotMain::TestPeriodic()
{

}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<CRobotMain>();
}
#endif