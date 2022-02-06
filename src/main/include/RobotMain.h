/******************************************************************************
    Description:	CRobotMain implementation
	Classes:		CRobotMain
	Project:		2022 Rapid React Robot Code
******************************************************************************/

#ifndef RobotMain_h
#define RobotMain_h

#include "Drive.h"
#include "Intake.h"
#include "Shooter.h"

#include <string>
#include <frc/TimedRobot.h>
#include <frc/Timer.h>
#include <frc/smartdashboard/SendableChooser.h>
///////////////////////////////////////////////////////////////////////////////
using namespace frc;

class CRobotMain : public TimedRobot {
public:
	CRobotMain();
	~CRobotMain();
	void RobotInit() override;
	void RobotPeriodic() override;
	void AutonomousInit() override;
	void AutonomousPeriodic() override;
	void TeleopInit() override;
	void TeleopPeriodic() override;
	void DisabledInit() override;
	void DisabledPeriodic() override;
	void TestInit() override;
	void TestPeriodic() override;

private:
	enum AutoStates {
		eAutoStopped = 0,
		eAutoIdle,
		eAutoAiming,
		eAutoFiring,
		eAutoFollowing
	};

	enum TeleopStates {
		eTeleopStopped = 0,
		eTeleopIdle,
		eTeleopFindingBall,
		eTeleopHomingBall,
		eTeleopClimbing,
		eTeleopIntake,
		eTeleopFiring
	};

	SendableChooser<std::string>*		m_pAutoChooser;
	std::string							m_strAutoSelected;
	Joystick*							m_pDriveController;
	Joystick*							m_pAuxController;
	CDrive*								m_pDrive;
	Timer*								m_pTimer;
	CIntake*							m_pFrontIntake;
	CShooter*							m_pShooter;

	double	m_dStartTime;							// A double representing start time
	int		m_nAutoState;							// Current Auto state
	int		m_nPathState;							// Current Auto sub-path
	int		m_nTeleopState;							// Current Teleop state
	//int		m_nPreviousState;						// Previous state
};
#endif