/******************************************************************************
    Description:	CRobotMain implementation
	Classes:		CRobotMain
	Project:		2022 Rapid React Robot Code
******************************************************************************/

#ifndef RobotMain_h
#define RobotMain_h

#include "Drive.h"
#include "Intake.h"
#include "Vision.h"
#include "Shooter.h"
#include "Lift.h"
#include "Transfer.h"

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
	enum TeleopStates {
		eTeleopStopped = 0,
		eTeleopIdle,
		eTeleopFindingBall,
		eTeleopHomingBall,
		eTeleopClimbing,
		eTeleopIntake,
		eTeleopFiring
	};

	SendableChooser<Paths>*				m_pAutoChooser;
	std::string							m_strAutoSelected;
	Joystick*							m_pDriveController;
	Joystick*							m_pAuxController;
	CDrive*								m_pDrive;
	Timer*								m_pTimer;
	CIntake*							m_pBackIntake;
	CShooter*							m_pShooter;
	CLift*								m_pLift;
	CVisionPacket*						m_pPrevVisionPacket;
	CTransfer*							m_pTransfer;

	double	m_dStartTime;							// A double representing start time
	Paths	m_nAutoState;							// Current Auto state
	int		m_nTeleopState;							// Current Teleop state
	int		m_nPreviousState;						// Previous state
};
#endif