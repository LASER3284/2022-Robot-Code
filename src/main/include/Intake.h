/******************************************************************************
	Description:	Defines the CIntake control class.
	Classes:		CIntake
	Project:		2022 Rapid React Robot Code
******************************************************************************/
#ifndef Intake_h
#define Intake_h

#include "IOMap.h"

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
    CIntake();
    ~CIntake();
	void CheckPneumaticPosition();


private:
	Compressor*	m_pCompressor;
	DigitalInput* m_pLimitSwitch;
	CANSparkMax* m_pFrontIntakeMotor1;
	CANSparkMax* m_pFrontIntakeMotor2;
	bool m_bIntakeDown;
};
///////////////////////////////////////////////////////////////////////////////
#endif