/******************************************************************************
    Description:	CRobotMain implementation
	Classes:		CRobotMain
	Project:		2022 Rapid React Robot Code
******************************************************************************/

#ifndef RobotMain_h
#define RobotMain_h

#include "Drive.h"

#include <string>
#include <frc/TimedRobot.h>
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
	frc::SendableChooser<std::string>*	m_pAutoChooser;
	std::string							m_strAutoSelected;
	Joystick*							m_pDriveController;
	Joystick*							m_pAuxController;
	CDrive*								m_pDrive;
};
#endif