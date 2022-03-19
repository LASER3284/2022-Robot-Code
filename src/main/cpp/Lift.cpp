/******************************************************************************
	Description:	Implements the CLift control class.
	Classes:		CLift
	Project:		2022 Rapid React Robot Code
	Robot Name:		Novum Tempus
******************************************************************************/

#include "Lift.h"
///////////////////////////////////////////////////////////////////////////////

/******************************************************************************
	Description:	CLift constructor - init local variables/classes
	Arguments:		None
	Returns:		Nothing
******************************************************************************/
CLift::CLift()
{
	m_pLiftMotor1	= new WPI_TalonFX(nLiftMotor1);
	m_pLiftMotor2	= new WPI_TalonFX(nLiftMotor2);
}

/******************************************************************************
	Description:	CLift destructor - delete local variables/classes
	Arguments:		None
	Returns:		Nothing
******************************************************************************/
CLift::~CLift()
{
	delete m_pLiftMotor1;
	delete m_pLiftMotor2;

	m_pLiftMotor1 = nullptr;
	m_pLiftMotor2 = nullptr;
}

void CLift::Tick() {

}

/******************************************************************************
	Description:	Initialize motor configurations
	Arguments:		None
	Returns:		Nothing
******************************************************************************/
void CLift::Init()
{
	// Configure open loop ramp rate
	m_pLiftMotor1->ConfigOpenloopRamp(dMotorOpenLoopRampRate);
	m_pLiftMotor2->ConfigOpenloopRamp(dMotorOpenLoopRampRate);

	// Clear sticky faults
	m_pLiftMotor1->ClearStickyFaults();
	m_pLiftMotor2->ClearStickyFaults();

	// Set the motors to brake mode.
	m_pLiftMotor1->SetNeutralMode(NeutralMode::Brake);
	m_pLiftMotor2->SetNeutralMode(NeutralMode::Brake);

	// Make second lift motor follow the first and invert it
	m_pLiftMotor2->Follow(*m_pLiftMotor1);
	m_pLiftMotor2->SetInverted(true);
}

/******************************************************************************
	Description:	Move arms up/down based on joystick input
	Arguments:		double dJoystickPosition
	Returns:		Nothing
******************************************************************************/
void CLift::MoveArms(double dJoystickPosition)
{	
	// Check if the joystick is in the deadzone.
	double dPosition = dJoystickPosition;
	if (fabs(dPosition) < 0.100) dPosition = 0.0;

	// If the joystick is positive, drive the arms down
	if(dPosition > 0.250) m_pLiftMotor1->Set(-0.100);
	else if(dPosition < -0.250) m_pLiftMotor1->Set(0.100);
	else m_pLiftMotor1->Set(0.000);
}