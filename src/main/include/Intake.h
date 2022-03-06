/******************************************************************************
	Description:	Defines the CIntake control class.
	Classes:		CIntake
	Project:		2022 Rapid React Robot Code
******************************************************************************/
#ifndef Intake_h
#define Intake_h

#include <frc/Compressor.h>
#include <frc/DigitalInput.h>
#include <rev/CANSparkMax.h>
#include <ctre/phoenix/motorcontrol/can/WPI_TalonSRX.h>

using namespace frc;
using namespace rev;
using namespace ctre::phoenix::motorcontrol::can;
///////////////////////////////////////////////////////////////////////////////

/******************************************************************************
	Description:	CIntake class definition.
	Arguments:		None
	Derived From:	Nothing
******************************************************************************/
class CIntake
{
public:
	// Public methods
    CIntake(int nIntakeMotor1, int nIntakeDownLimitSwitch, int nIntakeUpLimitSwitch, int nDeployController, bool IntakePosition);
    ~CIntake();
	void Init();
	bool IsGoalPressed();
	void ToggleIntake();
	void StopDeploy();
	void StartIntake(bool bSafe = true);
	void StopIntake();

	// Public members
	bool m_bGoal;		// If true, up; else, down
	bool m_bIntakeOn;

private:
	// Private members
	DigitalInput*	m_pLimitSwitchDown;
	DigitalInput*	m_pLimitSwitchUp;
	CANSparkMax*	m_pIntakeMotor1;
	WPI_TalonSRX*	m_pIntakeDeployMotorController1;
	WPI_TalonSRX*	m_pIntakeDeployMotorController2;

	bool m_bIntakeUp;
	bool m_bIntakeDown;
};
///////////////////////////////////////////////////////////////////////////////
#endif