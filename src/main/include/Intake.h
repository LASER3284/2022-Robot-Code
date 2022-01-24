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
    CIntake(int nIntakeMotor1, int nIntakeMotor2, int nIntakeDownLimitSwitch, int nIntakeUpLimitSwitch, int nDeployController);
    ~CIntake();
	void CheckIntakePosition();
	void IntakeUp();
	void IntakeDown();
	void StopMotorOnUpSwitch();
	void StopMotorOnDownSwitch();

private:
	DigitalInput*	m_pLimitSwitchDown;
	DigitalInput*	m_pLimitSwitchUp;
	CANSparkMax*	m_pIntakeMotor1;
	CANSparkMax*	m_pIntakeMotor2;
	WPI_TalonSRX*	m_pIntakeDeployMotorController;

	bool m_bIntakeDown;
	bool m_bIntakeUp;
	bool m_bToggled;
};
///////////////////////////////////////////////////////////////////////////////
#endif