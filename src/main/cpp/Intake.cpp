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
CIntake::CIntake(int nIntakeMotor1, int nIntakeDownLimitSwitch, int nIntakeUpLimitSwitch, int nDeployController, bool bIntakePosition = false)
{
	m_pIntakeMotor1					= new CANSparkMax(nIntakeMotor1, CANSparkMaxLowLevel::MotorType::kBrushless);
	m_pIntakeDeployMotorController1	= new WPI_TalonSRX(nDeployController);
	m_pLimitSwitchDown				= new DigitalInput(nIntakeDownLimitSwitch);
	m_pLimitSwitchUp				= new DigitalInput(nIntakeUpLimitSwitch);
	m_pIntakeDeployMotorController1->SetInverted(bIntakePosition);
	m_pIntakeMotor1->SetInverted(bIntakePosition);
}

/******************************************************************************
	Description:	CIntake destructor, delete local class pointers
	Arguments:		None
	Derived from:	Nothing
******************************************************************************/
CIntake::~CIntake()
{
	delete m_pIntakeMotor1;
	delete m_pLimitSwitchDown;
	delete m_pLimitSwitchUp;

	m_pIntakeMotor1		= nullptr;
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
	m_pIntakeDeployMotorController1->ConfigOpenloopRamp(0.500);

	// Set open loop ramp rate for NEO 550
	m_pIntakeMotor1->SetOpenLoopRampRate(0.500);
	m_bIntakeOn = false;
}

/******************************************************************************
	Description:	Determines if the goal switch (m_bGoal) is pressed
	Arguments:		None
	Returns:		bool
******************************************************************************/
bool CIntake::IsGoalPressed()
{
	if (m_bGoal)	{	return !m_pLimitSwitchUp->Get();	}
	else			{	return !m_pLimitSwitchDown->Get();	}	// Inverted to make it work, idk why it does
}

/******************************************************************************
	Description:	Toggles intake based on goal switch (m_bGoal)
	Arguments:		None
	Returns:		Nothing
******************************************************************************/
void CIntake::ToggleIntake()
{
	if (m_bGoal)	{	m_pIntakeDeployMotorController1->Set(-0.350);	}		// Reverse to take it up
	else			{	m_pIntakeDeployMotorController1->Set(0.350);	}		// Forward to take it down
}

/******************************************************************************
	Description:	Stops the deploy motor 
	Arguments:		None
	Returns:		Nothing
******************************************************************************/
void CIntake::StopDeploy()
{
	int idleAmount = 0;

	// If the goal is up, then we want to set a bit of negative motion
	if(m_bGoal) idleAmount = -0.05;
	else idleAmount = 0.10;

	m_pIntakeDeployMotorController1->Set(idleAmount);
}

/******************************************************************************
	Description:	Starts NEO 550 Intake motors
	Arguments:		None
	Returns:		Nothing
******************************************************************************/
void CIntake::StartIntake(bool bSafe)
{
	if(bSafe) {
		if (IsGoalPressed() && !m_bGoal) {
			m_pIntakeMotor1->Set(0.700);
			m_bIntakeOn = true;
		}
	}
	else {
		m_pIntakeMotor1->Set(0.700);
		m_bIntakeOn = true;
	}
}

/******************************************************************************
	Description:	Stops NEO 550 Intake motors
	Arguments:		None
	Returns:		Nothing
******************************************************************************/
void CIntake::StopIntake()
{
	m_pIntakeMotor1->Set(0.000);
	m_bIntakeOn = false;
}