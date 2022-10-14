/******************************************************************************
	Description:	Defines the CDrive control class.
	Classes:		CDrive
	Project:		2022 Rapid React Robot Code
******************************************************************************/
#ifndef Drive_h
#define Drive_h

#include "IOMap.h"
#include "FalconMotion.h"
#include "TrajectoryConstants.h"

#include <ctre/phoenix/motorcontrol/can/WPI_TalonFX.h>
#include <frc/controller/PIDController.h>
#include <frc/AnalogInput.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/Joystick.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/kinematics/DifferentialDriveOdometry.h>
#include <frc/kinematics/DifferentialDriveWheelSpeeds.h>
#include <frc2/command/RamseteCommand.h>
#include <frc/trajectory/TrajectoryGenerator.h>
#include <frc/trajectory/TrajectoryConfig.h>
#include <frc/trajectory/Trajectory.h>
#include <frc/geometry/Pose2d.h>
#include <frc/smartdashboard/Field2d.h>
#include <AHRS.h>
#include <frc/Timer.h>

using namespace ctre::phoenix::motorcontrol::can;
using namespace frc;
using namespace frc2;
using namespace std;
using namespace units;

// Declare constants
const double	dJoystickDeadzone						= 0.100;
const double	dDefaultProportional					= 0.43485;	// Left drive proportional value. // 0.000179
const double	dDefaultIntegral						= 0.000;	// Left drive integral value.
const double	dDefaultDerivative						= 0.000;	// Left drive derivative value.
const auto		kDefaultS								= 0.59652_V;								        //	|	Drive characterization constants.
const auto		kDefaultV								= 0.06051 * 1_V * 1_s / 1_m;			        //	|	Drive characterization constants.
const auto		kDefaultA								= 0.01027 * 1_V * 1_s * 1_s / 1_m;				//	|	Drive characterization constants.
const DifferentialDriveKinematics	kDriveKinematics	= DifferentialDriveKinematics(inch_t(26.000));	//  |	Drive characterization constants.

static const double kOffBalanceThresholdDegrees = 170.0f;
static const double kOnBalanceThresholdDegrees  = 175.0f;
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
	void ForceStop();
	void ResetOdometry();
	void SetJoystickControl(bool bJoystickControl);
	void SetDriveSafety(bool bDriveSafety);
	void SetTrajectory(Paths nPath);
	void FollowTrajectory();
	DifferentialDriveWheelSpeeds GetWheelSpeeds();
	void SetDrivePowers(volt_t dLeftVoltage, volt_t dRightVoltage);
	void SetDriveSpeeds(double dLeftVoltage, double dRightVoltage);
	bool IsTrajectoryFinished();
	void GoForwardUntuned();				// NOTE: this is untuned and shouldn't be used in non-beta versions
	void TurnByPower(double dPower);

	DifferentialDriveOdometry*				m_pOdometry;

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
	CTrajectoryConstants*					m_pTrajectoryConstants;
	RamseteCommand*							m_pRamseteCommand;
	Trajectory								m_Trajectory;
	Field2d*								m_pField;
	const double							m_dOpenLoopRampRate = 0.650;

	bool									m_bAutoBalanceXMode = false;
    bool									m_bAutoBalanceYMode = false;
};
///////////////////////////////////////////////////////////////////////////////
#endif