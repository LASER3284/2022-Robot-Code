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
CIntake::CIntake(int nIntakeMotor1, int nIntakeMotor2, int nIntakeDownLimitSwitch, int nIntakeUpLimitSwitch, int nDeployController)
{
	m_pIntakeMotor1					= new CANSparkMax(nIntakeMotor1, CANSparkMaxLowLevel::MotorType::kBrushless);
	m_pIntakeMotor2					= new CANSparkMax(nIntakeMotor2, CANSparkMaxLowLevel::MotorType::kBrushless);
	m_pIntakeDeployMotorController	= new WPI_TalonSRX(nDeployController);
	m_pLimitSwitchDown				= new DigitalInput(nIntakeDownLimitSwitch);
	m_pLimitSwitchUp				= new DigitalInput(nIntakeUpLimitSwitch);
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
	Returns:		Nothing
******************************************************************************/
void CIntake::CheckIntakePosition()
{
	m_bIntakeDown	= m_pLimitSwitchDown->Get();
	m_bIntakeUp		= m_pLimitSwitchUp->Get();
}

/******************************************************************************
	Description:	Retract intake
	Arguments:		None
	Returns:		Nothing
******************************************************************************/
void CIntake::IntakeUp()
{
	// Check Intake Position
	CheckIntakePosition();

	// If not intake up, then set motor to pull up
	if (!m_bIntakeUp)
	{
		m_pIntakeDeployMotorController->Set(-0.250);
	}
	else
	{
		m_pIntakeDeployMotorController->Set(0.000);
	}
}

/******************************************************************************
	Description:	Deploy intake
	Arguments:		None
	Returns:		Nothing
******************************************************************************/
void CIntake::IntakeDown()
{
	// Check Intake Position
	CheckIntakePosition();

	// If not intake up, then set motor to release motor down
	if (!m_bIntakeDown)
	{
		m_pIntakeDeployMotorController->Set(0.250);
	}
	else
	{
		m_pIntakeDeployMotorController->Set(0.000);
	}
}

/******************************************************************************
	Description:	Stop intake motors
	Arguments:		None
	Returns:		Nothing
******************************************************************************/
void CIntake::StopMotorOnDownSwitch()
{
	// Check Intake Position
	CheckIntakePosition();

	// If not intake up, then set motor to release motor down
	if (m_bIntakeDown) m_pIntakeDeployMotorController->Set(0.000);
}

/******************************************************************************
	Description:	Stop intake motors
	Arguments:		None
	Returns:		Nothing
******************************************************************************/
void CIntake::StopMotorOnUpSwitch()
{
	// Check Intake Position
	CheckIntakePosition();

	// If not intake up, then set motor to release motor down
	if (m_bIntakeUp) m_pIntakeDeployMotorController->Set(0.000);
}