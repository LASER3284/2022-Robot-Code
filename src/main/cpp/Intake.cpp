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
CIntake::CIntake(int nIntakeMotor1, int nIntakeMotor2, int nIntakeLimitSwitch)
{
	m_pIntakeMotor1	= new CANSparkMax(nIntakeMotor1, CANSparkMaxLowLevel::MotorType::kBrushless);
	m_pIntakeMotor2	= new CANSparkMax(nIntakeMotor2, CANSparkMaxLowLevel::MotorType::kBrushless);
	m_pLimitSwitch	= new DigitalInput(nIntakeLimitSwitch);
}

/******************************************************************************
	Description:	CIntake destructor, delete local class pointers
	Arguments:		None
	Derived from:	Nothing
******************************************************************************/
CIntake::~CIntake()
{
	delete m_pIntakeMotor1;
	delete m_pIntakeMotor2;
	delete m_pLimitSwitch;

	m_pIntakeMotor1	= nullptr;
	m_pIntakeMotor2	= nullptr;
	m_pLimitSwitch	= nullptr;
}
/******************************************************************************
	Description:	Thing
	Arguments:		idk
	Derived from:	something
******************************************************************************/
void CIntake::CheckPneumaticPosition()
{
	if(m_pLimitSwitch->Get()){
		m_pIntakeMotor1->Set(0.500);
		m_pIntakeMotor2->Set(0.500);
		m_bIntakeDown = true;
	} else{
		m_pIntakeMotor1->Set(0.000);
		m_pIntakeMotor2->Set(0.000);
		m_bIntakeDown = false;
	}
}