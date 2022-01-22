/******************************************************************************
	Description:	Implements the CIntake control class.
	Classes:		CIntake
	Project:		2022 Rapid React Robot Code
******************************************************************************/

#include "Intake.h"
///////////////////////////////////////////////////////////////////////////////

/******************************************************************************
	Description:	CIntake constructor, init local variables/classes
	Arguments:		None
	Derived from:	Nothing
******************************************************************************/
CIntake::CIntake()
{
	m_pCompressor			= new Compressor(2, PneumaticsModuleType::CTREPCM);
	m_pFrontIntakeMotor1	= new CANSparkMax(nIntakeMotor1, CANSparkMaxLowLevel::MotorType::kBrushless);
	m_pFrontIntakeMotor2	= new CANSparkMax(nIntakeMotor2, CANSparkMaxLowLevel::MotorType::kBrushless);
	m_pLimitSwitch			= new DigitalInput(nIntakeLimitSwitch1);
}

/******************************************************************************
	Description:	CIntake destructor, delete local class pointers
	Arguments:		None
	Derived from:	Nothing
******************************************************************************/
CIntake::~CIntake()
{
 delete m_pCompressor;
}
/******************************************************************************
	Description:	Thing
	Arguments:		idk
	Derived from:	something
******************************************************************************/
void CIntake::CheckPneumaticPosition()
{
	if(m_pLimitSwitch->Get()){
		m_pFrontIntakeMotor1->Set(0.500);
		m_pFrontIntakeMotor2->Set(0.500);
		m_bIntakeDown = true;
	} else{
		m_pFrontIntakeMotor1->Set(0.000);
		m_pFrontIntakeMotor2->Set(0.000);
		m_bIntakeDown = false;
	}
}