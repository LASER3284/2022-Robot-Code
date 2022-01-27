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
CIntake::CIntake(int nIntakeMotor1, int nIntakeMotor2, int nIntakeDownLimitSwitch, int nIntakeUpLimitSwitch, int nDeployController, bool bIntakePosition = false)

{
	m_pIntakeMotor1					= new CANSparkMax(nIntakeMotor1, CANSparkMaxLowLevel::MotorType::kBrushless);
	m_pIntakeMotor2					= new CANSparkMax(nIntakeMotor2, CANSparkMaxLowLevel::MotorType::kBrushless);
	m_pIntakeDeployMotorController	= new WPI_TalonSRX(nDeployController);
	m_pLimitSwitchDown				= new DigitalInput(nIntakeDownLimitSwitch);
	m_pLimitSwitchUp				= new DigitalInput(nIntakeUpLimitSwitch);
	m_bIntakeUp						= bIntakePosition;
	m_bIntakeDown					= !bIntakePosition;
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
	delete m_pLimitSwitchDown;
	delete m_pLimitSwitchUp;

	m_pIntakeMotor1		= nullptr;
	m_pIntakeMotor2		= nullptr;
	m_pLimitSwitchDown	= nullptr;
	m_pLimitSwitchUp	= nullptr;
}

/******************************************************************************
	Description:	Check intake position
	Arguments:		None
	Returns:		IntakePosition
******************************************************************************/
void CIntake::CheckIntakePosition()
{
	m_bIntakeUp		= m_pLimitSwitchUp->Get();
	m_bIntakeDown	= m_pLimitSwitchDown->Get();

	if (m_bIntakeDown || m_bIntakeUp) m_pIntakeDeployMotorController->Set(0.000);
}
/******************************************************************************
	Description:	None
	Arguments:		None
	Returns:		None
******************************************************************************/
void CIntake::ToggleIntake()
{
	CheckIntakePosition();

	if (m_bIntakeDown || m_bIntakeUp)
	{
		if (m_bIntakeDown)	IntakeUp();
		if (m_bIntakeUp)	IntakeDown();
	}
}
/******************************************************************************
	Description:	None	
	Arguments:		None
	Returns:		None
******************************************************************************/
void CIntake::IntakeUp()
{
	if (!m_bIntakeUp)
	{
		m_pIntakeDeployMotorController->Set(-0.250);
	} else {
		m_pIntakeDeployMotorController->Set(0.000);
	}
}
/******************************************************************************
	Description:	None	
	Arguments:		None
	Returns:		None
******************************************************************************/
void CIntake::IntakeDown()
{
	if(!m_bIntakeDown)
	{
		m_pIntakeDeployMotorController->Set(0.250);
	} else {
		m_pIntakeDeployMotorController->Set(0.000);
	}
}