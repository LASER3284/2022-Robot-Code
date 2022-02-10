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
	Description:	Init local variables and motors
	Arguments:		None
	Returns:		Nothing
******************************************************************************/
void CIntake::Init()
{
	// Set the goal switch to down
	m_bGoal			= false;
	m_bIntakeUp		= m_pLimitSwitchUp->Get();
	m_bIntakeDown	= m_pLimitSwitchDown->Get();

	// Set right motor to follow the left
	m_pIntakeMotor2->Follow(*m_pIntakeMotor1);
}

/******************************************************************************
	Description:	Determines if the goal switch (m_bGoal) is pressed
	Arguments:		None
	Returns:		bool
******************************************************************************/
bool CIntake::IsGoalPressed()
{
	if (m_bGoal)	{	return m_pLimitSwitchUp->Get();		}
	else			{	return !m_pLimitSwitchDown->Get();	}	// Inverted to make it work, idk why it does
}

/******************************************************************************
	Description:	Toggles intake based on goal switch (m_bGoal)
	Arguments:		None
	Returns:		Nothing
******************************************************************************/
void CIntake::ToggleIntake()
{
	if (m_bGoal)	{	m_pIntakeDeployMotorController->Set(-0.250);	}		// Reverse to take it up
	else			{	m_pIntakeDeployMotorController->Set(0.250);		}		// Forward to take it down
}

/******************************************************************************
	Description:	Stops the deploy motor 
	Arguments:		None
	Returns:		Nothing
******************************************************************************/
void CIntake::StopDeploy()
{
	m_pIntakeDeployMotorController->Set(0.000);
}

/******************************************************************************
	Description:	Starts NEO 550 Intake motors
	Arguments:		None
	Returns:		Nothing
******************************************************************************/
void CIntake::StartIntake()
{
	if (IsGoalPressed() && !m_bGoal) m_pIntakeMotor1->Set(1.000);
}

/******************************************************************************
	Description:	Stops NEO 550 Intake motors
	Arguments:		None
	Returns:		Nothing
******************************************************************************/
void CIntake::StopIntake()
{
	m_pIntakeMotor1->Set(0.000);
}