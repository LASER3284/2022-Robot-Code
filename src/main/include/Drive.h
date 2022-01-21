/******************************************************************************
	Description:	Defines the CDrive control class.
	Classes:		CDrive
	Project:		2022 Rapid React Robot Code
******************************************************************************/
#ifndef Drive_h
#define Drive_h

#include "IOMap.h"
#include "SparkMotion.h"
#include "FalconMotion.h"

#include <rev/CANSparkMax.h>
#include <ctre/phoenix/motorcontrol/can/WPI_TalonFX.h>
#include <frc/controller/PIDController.h>
#include <frc/AnalogInput.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/Joystick.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/kinematics/DifferentialDriveOdometry.h>
#include <frc2/command/RamseteCommand.h>
#include <frc/trajectory/TrajectoryGenerator.h>
#include <frc/trajectory/TrajectoryConfig.h>
#include <frc/trajectory/Trajectory.h>
#include <frc/geometry/Pose2d.h>
#include <AHRS.h>
#include <frc/Timer.h>

using namespace rev;
using namespace frc;

// Declare constants
const double dJoystickDeadzone					= 0.100;
///////////////////////////////////////////////////////////////////////////////

/******************************************************************************
    Description:	CDrive class definition.
    Arguments:		None
    Derived From:	Nothing
******************************************************************************/
class CDrive
{
public:
	// Declare class methods.
	CDrive(Joystick* pDriveController);
	~CDrive();
	void Init();
	void Tick();
	void Stop();
	void ResetOdometry();
	void SetJoystickControl(bool bJoystickControl);
	void SetDriveSafety(bool bDriveSafety);

private:
	// Declare class objects and variables.
	bool									m_bJoystickControl;
	CFalconMotion*							m_pLeadDriveMotor1;
	WPI_TalonFX*							m_pFollowMotor1;
	CFalconMotion*							m_pLeadDriveMotor2;
	WPI_TalonFX*							m_pFollowMotor2;
	AHRS*									m_pGyro;
	Joystick*								m_pDriveController;
	DifferentialDrive*						m_pRobotDrive;
	Timer*									m_pTimer;
	//DifferentialDriveOdometry*				m_pOdometry;
	//Trajectory								m_Trajectory;
};
///////////////////////////////////////////////////////////////////////////////
#endif