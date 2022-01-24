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

using namespace frc;
using namespace rev;
///////////////////////////////////////////////////////////////////////////////

/******************************************************************************
	Description:	CIntake class definition.
	Arguments:		None
	Derived From:	Nothing
******************************************************************************/
class CIntake
{
public:
    CIntake(int nIntakeMotor1, int nIntakeMotor2, int nIntakeLimitSwitch);
    ~CIntake();
	void CheckPneumaticPosition();


private:
	DigitalInput* m_pLimitSwitch;
	CANSparkMax* m_pIntakeMotor1;
	CANSparkMax* m_pIntakeMotor2;
	bool m_bIntakeDown;
};
///////////////////////////////////////////////////////////////////////////////
#endif