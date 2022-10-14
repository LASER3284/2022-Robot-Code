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
	m_pAutoChooser				= new SendableChooser<Paths>();
	m_pLift					    = new CLift();
	m_pBackIntake				= new CIntake(nIntakeMotor2, nBackIntakeDownLS, nBackIntakeUpLS, nIntakeDeployMotor2, false);
	m_pShooter					= new CShooter();
	m_nAutoState				= eAutoStopped;
	m_dStartTime				= 0.0;
	m_nPreviousState			= eTeleopStopped;
	m_kClimbState				= eNoClimb;
	m_pPrevVisionPacket         = new CVisionPacket();
	m_pTransfer					= new CTransfer();
	m_pCompressor				= new Compressor(0, PneumaticsModuleType::CTREPCM);
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
	delete m_pLift;
	delete m_pAutoChooser;
	delete m_pBackIntake;
	delete m_pPrevVisionPacket;
	delete m_pTransfer;
	delete m_pCompressor;

	m_pDriveController	= nullptr;
	m_pAuxController	= nullptr;
	m_pDrive			= nullptr;
	m_pTimer			= nullptr;
	m_pLift			    = nullptr;
	m_pAutoChooser		= nullptr;
	m_pBackIntake		= nullptr;
	m_pPrevVisionPacket = nullptr;
	m_pTransfer			= nullptr;
	m_pCompressor		= nullptr;
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
	
	m_pLift->Init();

	// Setup autonomous chooser.
	m_pAutoChooser->SetDefaultOption("Autonomous Idle", eAutoIdle);
	m_pAutoChooser->AddOption("Test Path", eTestPath);
	m_pAutoChooser->AddOption("Dumb Taxi", eDumbTaxi);
	m_pAutoChooser->AddOption("Taxi Shot", eTaxiShot);
	m_pAutoChooser->AddOption("Taxi 2 Shot", eTaxi2Shot);
	// m_pAutoChooser->AddOption("Less Dumb Taxi", eLessDumbTaxi1);

	m_pAutoChooser->AddOption("Far Gremlin Ball", eFarGremlinBall1);
	m_pAutoChooser->AddOption("Hangar Gremlin Ball", eHangarGremlinBall1);
	m_pAutoChooser->AddOption("Magic 4 Ball", eMagic4Ball1);

	m_pAutoChooser->AddOption("YOLO Terminator", eTerminator);
	SmartDashboard::PutData(m_pAutoChooser);

	SmartDashboard::PutBoolean("bTeleopVision", false);
	SmartDashboard::PutBoolean("bAutoClimb", false);
	m_pTimer->Start();
}

/******************************************************************************
    Description:	Global robot 20ms periodic function
	Arguments:		None
	Returns:		Nothing
******************************************************************************/
void CRobotMain::RobotPeriodic()
{
	// Tick the shooter
	m_pShooter->Tick();

	// Tick the transfer system
	m_pTransfer->UpdateLocations();

	// Update the odometry & Field2D on dashboard
	m_pDrive->Tick();

	// Update SmartDashboard for easy checking.
	SmartDashboard::PutBoolean("Vertical Transfer Infrared", m_pTransfer->m_aBallLocations[0]);
	SmartDashboard::PutBoolean("Back Transfer Infrared", m_pTransfer->m_aBallLocations[1]);
	SmartDashboard::PutBoolean("Back-Down Limit Switch", m_pBackIntake->GetLimitSwitchState(false));
	SmartDashboard::PutBoolean("Back-Up Limit Switch", m_pBackIntake->GetLimitSwitchState(true));

	SmartDashboard::PutNumber("m_nAutoState", (double)m_nAutoState);
	SmartDashboard::PutNumber("m_nPreviousState", (double)m_nPreviousState);
}

/******************************************************************************
    Description:	Autonomous initialization function
	Arguments:		None
	Returns:		Nothing
******************************************************************************/
void CRobotMain::AutonomousInit()
{
	// Make sure we disable the joystick
	m_pDrive->SetDriveSafety(false);
	m_pDrive->SetJoystickControl(false);

	m_pBackIntake->Init();
	m_pShooter->SetSafety(false);
	m_pShooter->Init();
	m_pShooter->StartFlywheelShot();
	m_pTransfer->Init();

	// Record start time
	m_dStartTime = (double)m_pTimer->Get();

	// Get selected option and switch m_nAutoState based on that
	m_nAutoState = m_pAutoChooser->GetSelected();
	
	// We don't need to set the trajectory/odometry for these paths.
	if(m_nAutoState == eDumbTaxi || m_nAutoState == eTaxiShot || m_nAutoState == eTaxi2Shot || m_nAutoState == eAutoIdle || m_nAutoState == eTerminator) 
		return;
	
	m_pDrive->SetTrajectory(m_nAutoState);
	m_pDrive->ResetOdometry();
}

/******************************************************************************
    Description:	Autonomous 20ms periodic function
	Arguments:		None
	Returns:		Nothing
******************************************************************************/
void CRobotMain::AutonomousPeriodic() 
{
	double dElapsed = ((double)m_pTimer->Get() - m_dStartTime);

	switch (m_nAutoState) 
	{
		// Force stop everything
		case eAutoStopped:
			m_pDrive->ForceStop();
			m_nPreviousState = eAutoStopped;
			break;

		// Do nothing
		case eAutoIdle:
			switch (m_nPreviousState)
			{
				case eTestPath:
					m_nAutoState = eAutoStopped;
					break;
				default:
					m_nAutoState = eAutoIdle;
					break;
			}
			break;
		
		// Test Path
		case eTestPath:
			m_pDrive->FollowTrajectory();
			if (m_pDrive->IsTrajectoryFinished()) 
			{
				m_nPreviousState = eTestPath;
				m_nAutoState = eAutoIdle;
			}
			break;

		// Dumb Taxi
		case eDumbTaxi:
			if(dElapsed < 1.250) 
				m_pDrive->SetDriveSpeeds(-6.000, -6.000);
			else 
				m_nAutoState = eAutoStopped;
			break;

		case eTaxiShot:
			m_pShooter->StartFlywheelShot();

			// Drive backwards for 0.5s
			if(dElapsed < 1.00) {
				m_pDrive->SetDriveSpeeds(-3.000, -3.000);
			}
			// Rev up the shooter for shooting
			else {
				m_pDrive->ForceStop();

				bool bShoot = ((double)m_pTimer->Get() - m_dStartTime) > 4.5;
				if(m_pShooter->m_bShooterFullSpeed || bShoot) {
					m_pTransfer->StartVerticalShot();
				}

				// If we don't have a ball in the vertical anymore, shut off the shooter.
				if(!m_pTransfer->m_aBallLocations[0]) {
					m_pShooter->IdleStop();
					m_pTransfer->StopVertical();
					m_nAutoState = eAutoStopped;
				}
			}
			break;
		case eTaxi2Shot:
			m_pShooter->StartFlywheelShot();

			// Pull the intake down and then start it			
			if(dElapsed < 0.125) {
				m_pBackIntake->MoveIntake(false);
				m_pTransfer->StopVertical();
			}

			if(m_pBackIntake->GetLimitSwitchState(false)) {
				m_pBackIntake->StartIntake();
				m_pBackIntake->StopDeploy();
				if(!m_pTransfer->m_aBallLocations[1]) m_pTransfer->StartBack();
			}


			if(dElapsed < 6.50 && m_pTransfer->m_aBallLocations[1]) m_pTransfer->StopBack();

			// Drive backwards for 0.5s
			if(dElapsed < 1.00) {
				m_pDrive->SetDriveSpeeds(-3.000, -3.000);
			}
			// Rev up the shooter for shooting
			else {
				m_pDrive->ForceStop();

				// Drive forward for .5s
				if(dElapsed > 1.25) m_pDrive->SetDriveSpeeds(1.250, 1.250);
				if(dElapsed > 1.50) m_pDrive->ForceStop();

				if(m_pShooter->m_bShooterFullSpeed) {
					if(dElapsed > 4.50) {
						m_pTransfer->StartVerticalShot();
					}

					if(dElapsed < 6.50 && m_pTransfer->m_aBallLocations[0] && m_pTransfer->m_aBallLocations[1]) m_pTransfer->StopBack();
					else if(dElapsed >= 6.50 && !m_pTransfer->m_aBallLocations[0]) m_pTransfer->StartBack();
				}
			}
			break;
		// Less Dumb Taxi
		case eLessDumbTaxi1:
			if( ((double)m_pTimer->Get() - m_dStartTime) < 0.750) {
				// Drop the intake down and then start it.
				m_pBackIntake->ToggleIntake();
				m_pBackIntake->StartIntake();
				// Drive backwards for a bit
				m_pDrive->SetDriveSpeeds(-6.000, -6.000);
				
				// Start/Stop the back transfer depending on if we've picked up the ball already.
				if(!m_pTransfer->m_aBallLocations[1]) m_pTransfer->StartBack();
				else m_pTransfer->StopBack();
			}
			else {
				m_nPreviousState = eLessDumbTaxi1;
				m_nAutoState = eLessDumbTaxi2;
				// Stop the intake to avoid picking up more than 2 balls
				m_pBackIntake->StopIntake();
			}
			break;
		case eLessDumbTaxi2:
			if( ((double)m_pTimer->Get() - m_dStartTime) < 1.750) {
				// Drive backwards more
				m_pDrive->SetDriveSpeeds(-6.000, -6.000);
			}
			else {
				m_nPreviousState = eLessDumbTaxi2;
				m_nAutoState = eLessDumbTaxi3;
			}
			break;
		case eLessDumbTaxi3:
			if(!m_pShooter->m_bShooterFullSpeed && m_pTransfer->m_aBallLocations[0]) {
				// Start the flywheel since the shooter isn't full speed yet.
				m_pShooter->StartFlywheelShot();
			}
			// The flywheel has spun up to full speed, now we start the vertical transfer to feed the ball in.
			if(m_pShooter->m_bShooterFullSpeed) {
				m_pTransfer->StartVerticalShot();
				if (!m_pTransfer->m_aBallLocations[0]) {
					// Spin the vertical transfer to "full" speed just to make sure the back ball is ready.
					m_pTransfer->StartVerticalShot();
					// We need to feed the balls in the horizontal into the vertical and let them sit there.
					m_pTransfer->StartBack();
				}
			}
			// We don't have any balls in the robot, time to stop the autonomous.
			if(!m_pTransfer->m_aBallLocations[0] && !m_pTransfer->m_aBallLocations[1]) {
				m_nAutoState = eAutoStopped;
			}
			break;

		// Both the far/hangar gremlin ball autos function the same way, so just let the case fall through
		case eHangarGremlinBall1:
		case eFarGremlinBall1:
			if( ((double)m_pTimer->Get() - m_dStartTime) < 0.750) {
				// Drop the intake down and then start it.
				m_pBackIntake->MoveIntake(false);

				// Start the flywheel now so that way the flywheel can get up to speed (hopefully) in time for us to shoot.
				if(!m_pShooter->m_bShooterFullSpeed) {
					m_pShooter->StartFlywheelShot();
				}
			}
			
			if(m_pBackIntake->GetLimitSwitchState(false)) {
				m_pBackIntake->StartIntake();
			}

			// Start/Stop the back transfer depending on if we've picked up the ball already.
			if(!m_pTransfer->m_aBallLocations[1]) m_pTransfer->StartBack();
			else m_pTransfer->StopBack();

			if (m_pDrive->IsTrajectoryFinished()) 
			{
				// If we've finished the trajectory, stop driving so we can shoot the ball.
				m_pDrive->ForceStop();

				// Shoot out the allied balls that we picked up (preload + behind)
				// The flywheel has spun up to full speed, now we start the vertical transfer to feed the ball in.
				if(m_pShooter->m_bShooterFullSpeed) {
					m_pTransfer->StartVerticalShot();
					if (!m_pTransfer->m_aBallLocations[0]) {
						// Spin the vertical transfer to "full" speed just to make sure the back ball is ready.
						m_pTransfer->StartVerticalShot();
						// We need to feed the balls in the horizontal into the vertical and let them sit there.
						m_pTransfer->StartBack();
					}
				}

				// Now that we've shot all of the allied balls out, change our auto state and go be a gremlin.
				if(!m_pTransfer->m_aBallLocations[0] && !m_pTransfer->m_aBallLocations[1]) {
					if(m_nAutoState == eFarGremlinBall1) {
						m_nPreviousState = eFarGremlinBall1;
						m_nAutoState = eFarGremlinBall2;
					}
					else if(m_nAutoState == eHangarGremlinBall1) {
						m_nPreviousState = eHangarGremlinBall1;
						m_nAutoState = eHangarGremlinBall2;
					}
					
					// Update the trajectory and move on to the next auto state
					m_pDrive->SetTrajectory(m_nAutoState);
				}
			}
			else {
				m_pDrive->FollowTrajectory();
			}

			break;
		case eHangarGremlinBall2:
		case eFarGremlinBall2:
			// If we've finished following the trajectory, go ahead and shoot/spit out the opposite ball.
			if (m_pDrive->IsTrajectoryFinished()) {
				// For the "far gremlin ball", we want to *shoot* the ball
				if(m_nAutoState == eFarGremlinBall2) {
					m_pTransfer->StartVerticalShot();
				}
				// But for the hangar gremlin ball, we want to *spit* the ball out avoid chucking it out of the field
				else if(m_nAutoState == eHangarGremlinBall2) {
					m_pShooter->AdjustVelocity(-0.75);
					m_pTransfer->StartVertical();
					m_pShooter->AdjustVelocity(0.75);
				}
				m_pDrive->ForceStop();
				
				// We don't have any balls in the robot, time to stop the autonomous.
				if(!m_pTransfer->m_aBallLocations[0] && !m_pTransfer->m_aBallLocations[1]) {
					m_nPreviousState = eFarGremlinBall2;
					m_nAutoState = eAutoStopped;
				}
			}
			else {
				m_pDrive->FollowTrajectory();
			}

			break;
		// Magic 3 Ball - Step #1: Drive back + pick up prestation ball
		case eMagic4Ball1:
			if( ((double)m_pTimer->Get() - m_dStartTime) < 0.750) {
				// Drop the intake down and then start it.
				m_pBackIntake->ToggleIntake();
				m_pBackIntake->StartIntake();

				// Start the flywheel now so that way the flywheel can get up to speed (hopefully) in time for us to shoot.
				if(!m_pShooter->m_bShooterFullSpeed) {
					m_pShooter->StartFlywheelShot();
				}
			}

			// Start/Stop the back transfer depending on if we've picked up the ball already.
			if(!m_pTransfer->m_aBallLocations[1]) m_pTransfer->StartBack();
			else m_pTransfer->StopBack();

			m_pDrive->FollowTrajectory();

			if (m_pDrive->IsTrajectoryFinished()) {
				// If we've finished the trajectory, stop driving so we can shoot the ball.
				m_pDrive->ForceStop();

				// Shoot out the blue balls that we picked up (preload + behind)
				// The flywheel has spun up to full speed, now we start the vertical transfer to feed the ball in.
				if(m_pShooter->m_bShooterFullSpeed) {
					m_pTransfer->StartVerticalShot();
					if (!m_pTransfer->m_aBallLocations[0]) {
						// Spin the vertical transfer to "full" speed just to make sure the back ball is ready.
						m_pTransfer->StartVerticalShot();
						// We need to feed the balls in the horizontal into the vertical and let them sit there.
						m_pTransfer->StartBack();
					}
				}

				// We don't have any balls in the robot, time to move onto the next set of balls
				if(!m_pTransfer->m_aBallLocations[0] && !m_pTransfer->m_aBallLocations[1]) {
					m_nPreviousState = eMagic4Ball1;
					m_nAutoState = eMagic4Ball2;
				}
			}

			break;

		// Magic 4 Ball - Step #2: Pick up 2 balls from human player station (preload + HP)
		case eMagic4Ball2:
			// The intake should already be down because of Step #1 so we can skip that.
			
			// Start/Stop the back transfer depending on if we've picked up the ball already.
			if(!m_pTransfer->m_aBallLocations[1]) m_pTransfer->StartBack();
			else m_pTransfer->StopBack();

			m_pDrive->FollowTrajectory();
			if (m_pDrive->IsTrajectoryFinished()) {
				// Shoot out the blue balls that we picked up (preload + behind)
				// The flywheel has spun up to full speed, now we start the vertical transfer to feed the ball in.
				if(m_pShooter->m_bShooterFullSpeed) {
					m_pTransfer->StartVerticalShot();
					if (!m_pTransfer->m_aBallLocations[0]) {
						// Spin the vertical transfer to "full" speed just to make sure the back ball is ready.
						m_pTransfer->StartVerticalShot();
						// We need to feed the balls in the horizontal into the vertical and let them sit there.
						m_pTransfer->StartBack();
					}
				}

				// We don't have any balls in the robot, time to move onto the next set of balls
				if(!m_pTransfer->m_aBallLocations[0] && !m_pTransfer->m_aBallLocations[1]) {
					m_nPreviousState = eMagic4Ball2;
					m_nAutoState = eAutoStopped;
				}
			}

			break;

		case eTerminator:
			// Deploy the intake (similar logic to Teleop)
			if (m_pBackIntake->IsGoalPressed())
			{
				if (!m_pBackIntake->m_bGoal) m_pBackIntake->StartIntake();
				else m_pBackIntake->StopIntake();
				
				m_pBackIntake->StopDeploy();
				m_pBackIntake->m_bGoal = !m_pBackIntake->m_bGoal;
			}
			/*
			// Get the vision packet from the coprocessor.
			CVisionPacket* pVisionPacket = CVisionPacket::GetReceivedPacket();
			if(pVisionPacket != nullptr) {
				if(m_pPrevVisionPacket->m_nRandVal != pVisionPacket->m_nRandVal) {
					pVisionPacket->ParseDetections();
					DetectionClass kDetectClass = (DriverStation::GetAlliance() == DriverStation::Alliance::kBlue ? eBlueCargo : eRedCargo);
					DetectionClass kIgnoreClass = (DriverStation::GetAlliance() == DriverStation::Alliance::kBlue ? eRedCargo  : eBlueCargo);
					
					// Get the amount of balls inside the robot
					int iBallCount = 0;
					for(int i = 0; i < 3; i++) {
						if(m_pTransfer->m_aBallLocations[i]) iBallCount += 1;
					}
					bool bBallHunting = false;
					for(int i = 0; i < pVisionPacket->m_nDetectionCount; i++) {
						CVisionPacket::sObjectDetection* pObjDetection = pVisionPacket->m_pDetections[i];
						
						// Go ball hunting if we don't have 2 balls.
						if(iBallCount < 2) {
							// Check if we detected any balls (luckily the detection information is sorted by depth on the Pi)
							if(pObjDetection->m_kClass == kDetectClass) {
								double dTheta = (pObjDetection->m_nX - 160) * dAnglePerPixel;
								const double dHalfWidthAngle = (pObjDetection->m_nWidth / 2) * dAnglePerPixel;

								// Go forward and head towards the ball
								if (-dHalfWidthAngle < dTheta && dTheta < dHalfWidthAngle) {
									if(pVisionPacket->m_kDetectionLocation == DetectionLocation::eFrontCamera) 
										m_pDrive->SetDriveSpeeds(6.000, 6.000); 
									else if(pVisionPacket->m_kDetectionLocation == DetectionLocation::eBackCamera)
										m_pDrive->SetDriveSpeeds(-6.000, -6.000);
								}
								// Turn to center the detected object
								else {
									dTheta = dTheta * (pVisionPacket->m_kDetectionLocation == DetectionLocation::eFrontCamera ? 1 : -1);
									m_pDrive->TurnByAngle(dTheta);
								}
								bBallHunting = true;
								break;
							}
						}
						else if(iBallCount >= 2) {
							// Stop the drive
							m_pDrive->SetDriveSpeeds(0.000, 0.000);

							// We've grabbed atleast 2 balls, now lets try and shoot them...
							if(pObjDetection->m_kClass == DetectionClass::eHub) {
								// TODO: Drive odometry to determine the side we are on of the hub.
								const units::degree_t driveRotation = m_pDrive->m_pOdometry->GetPose().Rotation().Degrees();
								
								// We're in range
								if(CTrajectoryConstants::IsInShootingRange(pObjDetection->m_nDepth)) {

								}
								// Move closer to the hub
								else if(pObjDetection->m_nDepth < (CTrajectoryConstants::m_dAutoShootingDistance - CTrajectoryConstants::m_dAutoShootingRange)) {
									if(pVisionPacket->m_kDetectionLocation == DetectionLocation::eFrontCamera) m_pDrive->SetDriveSpeeds(6.000, 6.000); 
									else if(pVisionPacket->m_kDetectionLocation == DetectionLocation::eBackCamera) m_pDrive->SetDriveSpeeds(-6.000, -6.000);
								}
								// Move farther from the hub
								else if(pObjDetection->m_nDepth > (CTrajectoryConstants::m_dAutoShootingDistance + CTrajectoryConstants::m_dAutoShootingRange)) {
									if(pVisionPacket->m_kDetectionLocation == DetectionLocation::eFrontCamera) m_pDrive->SetDriveSpeeds(-6.000, -6.000); 
									else if(pVisionPacket->m_kDetectionLocation == DetectionLocation::eBackCamera) m_pDrive->SetDriveSpeeds(6.000, 6.000);
								}
							}
						}
					}

					// We aren't on the hunt for a ball *AND* we don't have 2 balls in yet.
					// This means there's not a ball
					if(iBallCount < 2 && !bBallHunting) {
						// Spin 90deg in order to hopefully try and find a ball in either of the directions.
						m_pDrive->TurnByAngle(90);
					}
				}
			}
			*/
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
	m_pDrive->SetJoystickControl(true);
	m_pDrive->SetDriveSafety(false);
	m_pBackIntake->Init();
	m_pLift->Init();
	m_pLift->Init();
	m_pShooter->SetSafety(false);
	m_pShooter->Init();
	m_pShooter->ResetVelocity();
	m_pShooter->StartFlywheelShot();
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

	/**************************************************************************
	    Description:	Manual ticks
	**************************************************************************/

	// You could use a chunky if statement for this logic, but that'd be horrible, so, no (:
	int iBallCount = 0;
	for(int i = 0; i < 2; i++) {
		if(m_pTransfer->m_aBallLocations[i]) iBallCount += 1;
	}
	
	if(m_pDriveController->GetRawButtonPressed(eButtonRB)) {
		// If the intake isn't down, move the intake down
		if(!m_pBackIntake->GetLimitSwitchState(false)) {
			m_pBackIntake->MoveIntake(false);
			m_pBackIntake->m_bGoal = false;
			// Start the intakes on the way down...
			m_pBackIntake->StartIntake(false);
		}
	}
	else if(m_pDriveController->GetRawButtonReleased(eButtonRB)) {
		// If the intake isn't up, move the intake up
		if(!m_pBackIntake->GetLimitSwitchState(true)) {
			m_pBackIntake->StopIntake();
			m_pBackIntake->MoveIntake(true);
			m_pBackIntake->m_bGoal = true;
		}
	}

	// When we've hit our goal, stop the motors (or start the intake in case of going down)
	if (m_pBackIntake->IsGoalPressed())
	{
		if (!m_pBackIntake->m_bGoal) m_pBackIntake->StartIntake();
		else m_pBackIntake->StopIntake();
		
		m_pBackIntake->StopDeploy();
		m_pBackIntake->m_bGoal = !m_pBackIntake->m_bGoal;
	}
	
	// Stop the horizontal transfer if we've got 2 balls
	if(iBallCount >= 2) m_pTransfer->StopBack();
	else m_pTransfer->StartBack();

	// Send balls into the flywheel with the trigger (even if we don't technically have a ball in the vertical)
	if (m_pAuxController->GetRawAxis(eRightTrigger) >= 0.95) {
		m_pTransfer->StartVerticalShot();
	}
	// Drop the shooter velocity (it'll be a bit off but that's ok), and then start the vertical transfer at a slow speed
	// Then reset the shooter velocity back up
	else if (m_pAuxController->GetRawAxis(eLeftTrigger) >= 0.95) {
		m_pShooter->AdjustVelocity(-0.75);
		m_pTransfer->StartVertical();
		m_pShooter->AdjustVelocity(0.75);
	}
	else if (m_pAuxController->GetRawButtonPressed(eButtonLB)) {
		// TODO: Check and see if this works with the ramp
		// If not, just remove it and then do the baby shot instead ^^^
		m_pTransfer->ReverseVertical();
		
		m_pTransfer->ReverseBack();
		// TODO: Check and see how the intake works if we can reverse it or not to spit out balls at a higher RPM
	}
	// If a ball is in the vertical and RT isn't fully pressed, stop the vertical transfer
	else if(m_pTransfer->m_aBallLocations[0]) {
		m_pTransfer->StopVertical();
	}
	else if(!m_pTransfer->m_aBallLocations[0]) {
		m_pTransfer->StartVertical();
		// We need to feed the balls in the horizontal into the vertical and let them sit there.
		if(iBallCount >= 1) {
			m_pTransfer->StartBack();
		}
	}

	// Check if climb is meant to be automated or not
	if (SmartDashboard::GetBoolean("bAutoClimb", false)) {
		// If both Lift mechanisms are ready, proceed to each stage based on button presses
		if (m_pLift->m_bReady) {
			if (m_pAuxController->GetRawButton(eButtonRB) && m_pAuxController->GetRawButton(eButtonA) && m_kClimbState == eNoClimb) m_kClimbState = eMid;
			if (m_pAuxController->GetRawButton(eButtonRB) && m_pAuxController->GetRawButton(eButtonB) && m_kClimbState == eMid) m_kClimbState = eHigh;
			if (m_pAuxController->GetRawButton(eButtonRB) && m_pAuxController->GetRawButton(eButtonY) && m_kClimbState == eHigh) m_kClimbState = eTraverse;
			if (m_pAuxController->GetRawButton(eButtonRB) && m_pAuxController->GetRawButton(eButtonX) && m_kClimbState == eTraverse) m_kClimbState = eHang;
		}
	} 
	else {

		// If the POV is up, spin the arms up
		if (m_pAuxController->GetPOV() == 0) 
		{
			m_pLift->ManualAdjust(0.950);
		}

		// If the D-PAD is not being pressed, stop the arms.
		if (m_pAuxController->GetPOV() == -1) {
			m_pLift->ManualAdjust(0.000);
		}

		// If the POV is down, spin the arms down.
		if (m_pAuxController->GetPOV() == 180) {
			m_pLift->ManualAdjust(-0.950);
		}

		if (m_pAuxController->GetRawButton(eButtonA)) m_pLift->SetFrontHook(true);
		if (m_pAuxController->GetRawButton(eButtonB)) m_pLift->SetFrontHook(false);

		if (m_pAuxController->GetRawButton(eButtonX)) m_pLift->SetBackHook(true);
		if (m_pAuxController->GetRawButton(eButtonY)) m_pLift->SetBackHook(false);
	}
	
	m_pLift->Tick(m_kClimbState);
	
	/**************************************************************************
	    Description:	Vision processing and ball trackings
	**************************************************************************/

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
	/*
	// Retrieve most recent vision packet
	CVisionPacket* pVisionPacket = CVisionPacket::GetReceivedPacket();
	// If it's not a nullptr, then continue, otherwise tick Drive
	if(pVisionPacket != nullptr && m_pDriveController->GetRawButton(eButtonA))
	{
		// If it's not the same as the last, continue, otherwise tick Drive
		if(m_pPrevVisionPacket->m_nRandVal != pVisionPacket->m_nRandVal)
		{
			// Parse detections and determine appropriate color alliance
			pVisionPacket->ParseDetections();
			DetectionClass kBallClass = (DriverStation::GetAlliance() == DriverStation::Alliance::kBlue ? eBlueCargo : eRedCargo);

			// Loop through the detections until the first correctly colored ball is found
			int* n = new int();
			for (*n = 0; (pVisionPacket->m_pDetections[*n]->m_kClass != kBallClass) && (*n < 15); *n += 1);

			// If n is a nullptr (i.e. wasn't looped through), tick drive instead of following ball
			if (n != nullptr)
			{
				CVisionPacket::sObjectDetection* pValidBall = pVisionPacket->m_pDetections[*n];

				// Find the angle from the center of the FoV and the amount of FoV it takes up
				const double dTheta = (pValidBall->m_nX - 160) * dAnglePerPixel;
				const double dHalfWidthAngle = (pValidBall->m_nWidth / 2) * dAnglePerPixel;

				// If dTheta is not within the angle taken up by the ball, then turn at 15% power
				// NOTE: TurnByPower(double) requests the value in percent form, not decimal
				if (fabs(dTheta) > dHalfWidthAngle) m_pDrive->TurnByPower(15.000);
			}
			else m_pDrive->Tick();
		}
		else m_pDrive->Tick();
	}
	else m_pDrive->Tick();
	m_pPrevVisionPacket = pVisionPacket;
	*/
}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<CRobotMain>();
}
#endif