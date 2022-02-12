/******************************************************************************
    Description:	CRobotMain implementation
	Classes:		CRobotMain
	Project:		2022 Rapid React Robot Code
******************************************************************************/

#include "RobotMain.h"

#include <fmt/core.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/DriverStation.h>
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
	m_pTimer					= new Timer();
	m_pDrive					= new CDrive(m_pDriveController);
	m_pAutoChooser				= new SendableChooser<string>();
	//m_pLift 					= new CLift();
	//m_pFrontIntake				= new CIntake(4, 9, 8, 0, 5, false);
	//m_pShooter					= new CShooter();
	m_nAutoState				= eAutoStopped;
	m_dStartTime				= 0.0;
	//m_nPreviousState			= eTeleopStopped;
	m_pPrevVisionPacket         = new CVisionPacket();
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
	delete m_pTimer;
	delete m_pAutoChooser;
	delete m_pFrontIntake;
	delete m_pPrevVisionPacket;

	m_pDriveController	= nullptr;
	m_pAuxController	= nullptr;
	m_pDrive			= nullptr;
	m_pTimer			= nullptr;
	m_pAutoChooser		= nullptr;
	m_pFrontIntake		= nullptr;
	m_pPrevVisionPacket = nullptr;
}

/******************************************************************************
    Description:	Global robot initialization function
	Arguments:		None
	Returns:		Nothing
******************************************************************************/
void CRobotMain::RobotInit()
{
	m_pDrive->Init();

	// Setup autonomous chooser.
	m_pAutoChooser->SetDefaultOption("Autonomous Idle", "Autonomous Idle");
	m_pAutoChooser->AddOption("Advancement", "Advancement");
	SmartDashboard::PutData(m_pAutoChooser);

	m_pTimer->Start();
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
	// Init Drive and disable joystick
	m_pDrive->Init();
	m_pDrive->SetJoystickControl(false);

	// TODO: deploy intake for all of auto period

	// Record start time
	//m_dStartTime = (double)m_pTimer->Get();

	// Get selected option and switch m_nPathState based on that
	m_strAutoSelected = m_pAutoChooser->GetSelected();
	m_nAutoState = eAutoIdle;
	m_nPathState = -1;
	if (m_strAutoSelected == "Advancement")
	{
		m_nPathState = eAdvancement1;
		m_nAutoState = eAutoFollowing;
	}
	
	// Set selected trajectory
	m_pDrive->SetTrajectory(m_nPathState);
}

/******************************************************************************
    Description:	Autonomous 20ms periodic function
	Arguments:		None
	Returns:		Nothing
******************************************************************************/
void CRobotMain::AutonomousPeriodic() 
{
	switch (m_nAutoState) 
	{
		// Force stop everything
		case eAutoStopped:
			m_pDrive->ForceStop();
			m_nAutoState = eAutoIdle;
			break;

		// Do nothing
		case eAutoIdle:
			break;

		// Aim robot based on vision
		case eAutoAiming:
			// TODO: apply Vision to this
			break;

		// Fire ball towards Hub
		case eAutoFiring:
			// TODO: add firing routines with shooter
			break;

		// Follow selected trajectory
		case eAutoFollowing:
			m_pDrive->FollowTrajectory();
			if (m_pDrive->IsTrajectoryFinished()) m_nAutoState = eAutoAiming;
			break;
	}
}

/******************************************************************************
    Description:	Teleop initialization function
	Arguments:		None
	Returns:		Nothing
******************************************************************************/
void CRobotMain::TeleopInit()
{
	m_pDrive->Init();
	m_pDrive->SetJoystickControl(true);
	//m_pFrontIntake->Init();
	//m_pShooter->SetSafety(false);
	//m_pShooter->Init();
	m_pPrevVisionPacket = new CVisionPacket();
}

/******************************************************************************
    Description:	Teleop 20ms periodic function
	Arguments:		None
	Returns:		Nothing
******************************************************************************/
void CRobotMain::TeleopPeriodic()
{
	/**************************************************************************
	    Description:	Drive stop and Joystick handling
	**************************************************************************/

	// If the drive controller is pressing Select, stop the drive train
	if (m_pDriveController->GetRawButtonPressed(eBack))
	{
		m_pDrive->ForceStop();
	}
	if (m_pDriveController->GetRawButtonReleased(eBack))
	{
		m_pDrive->SetJoystickControl(true);
	}

	/**************************************************************************
	    Description:	Vision processing and ball trackings
	**************************************************************************/

	// Retrive the processed vision packet from our coprocessor.
	string processed_vision = SmartDashboard::GetRaw("processed_vision", "");
	// If the processed_vision is empty, then the vision code isn't running (?);
	// Button A on drive controller must also have been pressed
	if(!processed_vision.empty() && m_pDriveController->GetRawButtonPressed(eButtonA))
	{
		const char* pVisionPacketArr = processed_vision.c_str();
		CVisionPacket* pVisionPacket = new CVisionPacket(pVisionPacketArr);

		// First byte being equal to 0xFF means that the packet is a "null" packet (i.e no detections)
		if(pVisionPacket->m_nRandVal != 0xFF)
		{
			// Check if we received a different packet from the last packet
			if(pVisionPacket->m_nRandVal != m_pPrevVisionPacket->m_nRandVal)
			{
				DetectionClass kDetectClass = (DriverStation::GetAlliance() == DriverStation::Alliance::kBlue ? eBlueCargo : eRedCargo);
				if (pVisionPacket->m_uClass == kDetectClass) {
					const double dTheta = (pVisionPacket->m_nX - 160) * dAnglePerPixel;
					if (-pVisionPacket->m_dHalfWidthAngle < dTheta && dTheta < pVisionPacket->m_dHalfWidthAngle) m_pDrive->GoForwardUntuned();
    				else m_pDrive->TurnByAngle(dTheta);
    				m_pPrevVisionPacket = pVisionPacket;
   				}
			}
		}
		else m_pDrive->Tick();
	}
	else m_pDrive->Tick();

	/**************************************************************************
	    Description:	Manual ticks
	**************************************************************************/
/*
	// Manually tick intake
	if (!m_pFrontIntake->IsGoalPressed() && m_pDriveController->GetRawButtonPressed(eButtonRB))
	{
		m_pFrontIntake->ToggleIntake();
	}
	if (m_pFrontIntake->IsGoalPressed())
	{
		if (!m_pFrontIntake->m_bGoal) m_pFrontIntake->StartIntake();
		else m_pFrontIntake->StopIntake();
		m_pFrontIntake->StopDeploy();
		m_pFrontIntake->m_bGoal = !m_pFrontIntake->m_bGoal;
	}

	// Manually tick shooter
	if (m_pAuxController->GetRawButtonPressed(eButtonA) && !m_pAuxController->GetRawButtonReleased(eButtonA)) m_pShooter->StartFlywheel();
	if (m_pAuxController->GetRawButtonPressed(eButtonB) && m_pAuxController->GetRawButtonReleased(eButtonA)) m_pShooter->Stop();*/
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
	m_pDrive->Init();
	m_pDrive->SetJoystickControl(true);
	m_pPrevVisionPacket = new CVisionPacket();
}

/******************************************************************************
    Description:	Test 20ms periodic function
	Arguments:		None
	Returns:		Nothing
******************************************************************************/
void CRobotMain::TestPeriodic()
{
	/**************************************************************************
	    Description:	Vision processing and ball trackings
	**************************************************************************/

	// Retrive the processed vision packet from our coprocessor.
	string processed_vision = SmartDashboard::GetRaw("processed_vision", "");
	// If the processed_vision is empty, then the vision code isn't running (?);
	// Button A on drive controller must also have been pressed
	if (!processed_vision.empty() /*&& m_pDriveController->GetRawButtonPressed(eButtonA)*/)
	{
		const char* pVisionPacketArr = string(processed_vision).c_str();
		CVisionPacket* pVisionPacket = new CVisionPacket(pVisionPacketArr);

		wpi::outs() << "Retrieved vision packet\n";

		// First byte being equal to 0xFF means that the packet is a "null" packet (i.e no detections)
		if (pVisionPacket->m_nRandVal != 0xFF)
		{
			wpi::outs() << "Not null packet\n";
			// Check if we received a different packet from the last packet
			if (pVisionPacket->m_nRandVal != m_pPrevVisionPacket->m_nRandVal)
			{
				wpi::outs() << "New vision packet\n";
				DetectionClass kDetectClass = (DriverStation::GetAlliance() == DriverStation::Alliance::kBlue ? eBlueCargo : eRedCargo);
				if (pVisionPacket->m_uClass == kDetectClass) {
					const double dTheta = (pVisionPacket->m_nX - 160) * dAnglePerPixel;
					if (-pVisionPacket->m_dHalfWidthAngle < dTheta && dTheta < pVisionPacket->m_dHalfWidthAngle) m_pDrive->GoForwardUntuned();
    				else m_pDrive->TurnByAngle(dTheta);
   				}
			}
		}
		else m_pDrive->Tick();
		m_pPrevVisionPacket = pVisionPacket;
	}
	else m_pDrive->Tick();
}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<CRobotMain>();
}
#endif