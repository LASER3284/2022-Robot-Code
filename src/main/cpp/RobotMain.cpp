/******************************************************************************
    Description:	CRobotMain implementation
	Classes:		CRobotMain
	Project:		2022 Rapid React Robot Code
******************************************************************************/

#include "RobotMain.h"

#include <fmt/core.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/DriverStation.h>
#include <wpi/StringExtras.h>
#include <iostream>

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
	m_pFrontIntake				= new CIntake(nIntakeMotor1, 0, 1, nIntakeDeployMotor1, true);
	m_pBackIntake				= new CIntake(nIntakeMotor2, 2, 3, nIntakeDeployMotor2, false);
	m_pShooter					= new CShooter();
	m_nAutoState				= eAutoStopped;
	m_dStartTime				= 0.0;
	//m_nPreviousState			= eTeleopStopped;
	m_pPrevVisionPacket         = new CVisionPacket();
	m_pTransfer					= new CTransfer();
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
	delete m_pBackIntake;
	delete m_pPrevVisionPacket;
	delete m_pTransfer;

	m_pDriveController	= nullptr;
	m_pAuxController	= nullptr;
	m_pDrive			= nullptr;
	m_pTimer			= nullptr;
	m_pAutoChooser		= nullptr;
	m_pFrontIntake		= nullptr;
	m_pBackIntake		= nullptr;
	m_pPrevVisionPacket = nullptr;
	m_pTransfer			= nullptr;
}

/******************************************************************************
    Description:	Global robot initialization function
	Arguments:		None
	Returns:		Nothing
******************************************************************************/
void CRobotMain::RobotInit()
{
	m_pDrive->Init();
	m_pTransfer->Init();

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
	m_pShooter->Tick();
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
	m_pFrontIntake->Init();
	m_pBackIntake->Init();
	m_pShooter->SetSafety(false);
	m_pShooter->Init();
	m_pPrevVisionPacket = new CVisionPacket();
	m_pTransfer->Init();
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
	m_pDrive->Tick();

	/**************************************************************************
	    Description:	Manual ticks
	**************************************************************************/

	// Manually tick intake
	if (!m_pFrontIntake->IsGoalPressed() && m_pDriveController->GetRawButtonPressed(eButtonLB))
	{
		// Stop the intake just to be safe (:
		m_pFrontIntake->StopIntake();
		m_pFrontIntake->ToggleIntake();
	}
	if (m_pFrontIntake->IsGoalPressed())
	{
		if (!m_pFrontIntake->m_bGoal) m_pFrontIntake->StartIntake();
		else m_pFrontIntake->StopIntake();
		
		m_pFrontIntake->StopDeploy();
		m_pFrontIntake->m_bGoal = !m_pFrontIntake->m_bGoal;
	}

	if (!m_pBackIntake->IsGoalPressed() && m_pDriveController->GetRawButtonPressed(eButtonRB))
	{
		// Stop the intake just to be safe (:
		m_pBackIntake->StopIntake();
		m_pBackIntake->ToggleIntake();
	}
	if (m_pBackIntake->IsGoalPressed())
	{
		if (!m_pBackIntake->m_bGoal) m_pBackIntake->StartIntake();
		else m_pBackIntake->StopIntake();
		
		m_pBackIntake->StopDeploy();
		m_pBackIntake->m_bGoal = !m_pBackIntake->m_bGoal;
	}
	
	// Manually tick transfer system
	m_pTransfer->UpdateLocations();

	// We need to do some jankiness in order to lock the value of the vertical transfer sensor for shooting...
	if(!m_pShooter->m_bShooterOn && m_pTransfer->m_aBallLocations[0]) {
		m_pTransfer->m_bBallLocked = true;
	}

	// If the front/back intake is on, and we don't have a ball in the vertical, start the front/back transfer
	if ( ( m_pFrontIntake->m_bIntakeOn || m_pBackIntake->m_bIntakeOn ) && !m_pTransfer->m_aBallLocations[0]) {
		m_pTransfer->StartFront();
		m_pTransfer->StartBack();
	}

	// You could use a chunky if statement for this logic, but that'd be horrible, so, no (:
	int iBallCount = 0;
	for(int i = 0; i < 3; i++) {
		if(m_pTransfer->m_aBallLocations[i]) iBallCount += 1;
	}

	// If we don't have a ball in the vertical transfer, start it
	if (!m_pTransfer->m_aBallLocations[0]) {
		m_pTransfer->StartVertical();
		// We need to feed the balls in the horizontal into the vertical and let them sit there.
		if(iBallCount >= 1) {
			m_pTransfer->StartFront();
			m_pTransfer->StartBack();
		}
	}
	// If the shooter isn't on and we have a ball in the transfer, stop the vertical to try and stop the ball in it.
	else if(!m_pShooter->m_bShooterOn) {
		m_pTransfer->StopVertical();
	}
	// If the shooter IS on and we have a ball in the transfer, start the vertical transfer to send it to the flywheel.
	else if(m_pShooter->m_bShooterFullSpeed) {
		m_pTransfer->StartVerticalShot();
		m_pTransfer->m_bBallLocked = false;
		/*
		if(m_pAuxController->GetRawButtonPressed(eButtonA) && !m_pAuxController->GetRawButtonReleased(eButtonA)) {
			m_pTransfer->StartVerticalShot();
			m_pTransfer->m_bBallLocked = false;
		}
		*/
	}

	// If we have more than two balls at a time, we need to stop the intakes that we're running AND transfers to avoid shuffling the balls.
	if( (m_pFrontIntake->m_bIntakeOn || m_pBackIntake->m_bIntakeOn) && iBallCount >= 2) {
		// Stop either of the intakes
		if(m_pFrontIntake->m_bIntakeOn) {
			m_pFrontIntake->StopIntake();
			m_pFrontIntake->StopDeploy();
		}
		if(m_pBackIntake->m_bIntakeOn) {
			m_pBackIntake->StopIntake();
			m_pBackIntake->StopDeploy();
		}

		// We need to stop the horizontal transfers as well.
		m_pTransfer->StopFront();
		m_pTransfer->StopBack();
	}

	// Toggle on and off the flywheel with right trigger
	if (m_pAuxController->GetRawButtonPressed(eButtonA) && !m_pAuxController->GetRawButtonReleased(eButtonA)) m_pShooter->StartFlywheel();
	if (m_pAuxController->GetRawButtonPressed(eButtonB) && m_pAuxController->GetRawButtonReleased(eButtonA)) m_pShooter->Stop();

	/**************************************************************************
	    Description:	Vision processing and ball trackings
	**************************************************************************/

	// TODO: Implement vision into Teleop



	// Infrared updates
	SmartDashboard::PutBoolean("Vertical Transfer Infrared", m_pTransfer->m_aBallLocations[0]);
	SmartDashboard::PutBoolean("Front Transfer Infrared", m_pTransfer->m_aBallLocations[1]);
	SmartDashboard::PutBoolean("Back Transfer Infrared", m_pTransfer->m_aBallLocations[2]);
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
		const char* pVisionPacketArr = processed_vision.c_str();
		CVisionPacket* pVisionPacket = new CVisionPacket(pVisionPacketArr, processed_vision.length());

		if(pVisionPacket->m_nRandVal != 0xFF) {
			if(m_pPrevVisionPacket->m_nRandVal != pVisionPacket->m_nRandVal) {
				// Parse out the detections now that we know that it's a different packet 
				pVisionPacket->ParseDetections();
				DetectionClass kDetectClass = (DriverStation::GetAlliance() == DriverStation::Alliance::kBlue ? eBlueCargo : eRedCargo);
				
				// ostringstream oss;
				for(int i = 0; i < pVisionPacket->m_nDetectionCount; i++) {
					CVisionPacket::sObjectDetection* pObjDetection = pVisionPacket->m_pDetections[i];
					// oss << "[" << i << "] - Conf: " << std::hex << (int)pObjDetection->m_nConfidence;
					// oss << " - Depth: " << std::hex << (int)pObjDetection->m_nDepth << " ";
					if(pObjDetection->m_kClass == kDetectClass) {
						const double dTheta = (pObjDetection->m_nX - 160) * dAnglePerPixel;
						const double dHalfWidthAngle = (pObjDetection->m_nWidth / 2) * dAnglePerPixel;
						// Go forward
						if (-dHalfWidthAngle < dTheta && dTheta < dHalfWidthAngle) {
							wpi::outs() << "Going forward...\r\n";
							m_pDrive->GoForwardUntuned(); 
						}
						// Turn to center the detected object
						else {
							wpi::outs() << "Turning...\r\n";
							m_pDrive->TurnByAngle(dTheta);
						}
					}
				}
				wpi::outs().flush();

			} else m_pDrive->Tick();
			m_pPrevVisionPacket = pVisionPacket;
		}
		else m_pDrive->Tick();
	}
	else m_pDrive->Tick();
}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<CRobotMain>();
}
#endif