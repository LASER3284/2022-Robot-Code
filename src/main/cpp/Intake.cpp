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
	Derived from:	Intake.h
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
	Description:	Check Intake Positon, Then activate Motors Corasponding To the position of the intake
	Arguments:		None
	Derived from:	Inake.h
******************************************************************************/
void CIntake::CheckIntakePosition()
{
	m_bIntakeDown = m_pLimitSwitch->Get();
}
/******************************************************************************
	Description:	deploy intake in a toggle format
	Arguments:		bToggle
	Derived from:	Inake.h
******************************************************************************/
void CIntake::IntakeToggle()
{
	if(m_bIntakeDown){
		m_pIntakeDeployMotor1->Set(0.000);
		m_pIntakeMotor1->Set(0.500);
		m_pIntakeMotor2->Set(0.500);
	} else
	{
		m_pIntakeDeployMotor1->Set(0.250);
		m_pIntakeMotor1->Set(0.000);
		m_pIntakeMotor2->Set(0.000);
	}
}