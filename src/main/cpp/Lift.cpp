/******************************************************************************
	Description:	Implements the CLift control class.
	Classes:		CLift
	Project:		2022 Rapid React Robot Code
******************************************************************************/

#include "Lift.h"
///////////////////////////////////////////////////////////////////////////////

/******************************************************************************
	Description:	CLift constructor - init local variables/classes
	Arguments:		bool bInverted - whether this instance is referencing 
					left (false) or right (true)
	Returns:		Nothing
******************************************************************************/
CLift::CLift(bool bInverted)
{
	if (!bInverted)
	{
		m_pLiftMotor1	= new WPI_TalonFX(nLiftMotor1);
		m_pMidClaw		= new DoubleSolenoid(nPneumatics, PneumaticsModuleType::CTREPCM, nLeftMidClaw1, nLeftMidClaw2);
		m_pHighClaw		= new DoubleSolenoid(nPneumatics, PneumaticsModuleType::CTREPCM, nLeftHighClaw1, nLeftHighClaw2);
	} else {
		m_pLiftMotor1	= new WPI_TalonFX(nLiftMotor2);
		m_pMidClaw		= new DoubleSolenoid(nPneumatics, PneumaticsModuleType::CTREPCM, nRightMidClaw1, nRightMidClaw2);
		m_pHighClaw		= new DoubleSolenoid(nPneumatics, PneumaticsModuleType::CTREPCM, nRightHighClaw1, nRightHighClaw2);
	}
	m_bInverted			= bInverted;
}

/******************************************************************************
	Description:	CLift destructor - delete local variables/classes
	Arguments:		None
	Returns:		Nothing
******************************************************************************/
CLift::~CLift()
{
	delete m_pLiftMotor1;
	delete m_pMidClaw;
	delete m_pHighClaw;

	m_pLiftMotor1	= nullptr;
	m_pMidClaw		= nullptr;
	m_pHighClaw		= nullptr;
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

	// Clear sticky faults
	m_pLiftMotor1->ClearStickyFaults();

	// Set the motors to brake mode.
	m_pLiftMotor1->SetNeutralMode(NeutralMode::Brake);

	// Configure rotary encoder for Lift Motor
	m_pLiftMotor1->ConfigSelectedFeedbackSensor(FeedbackDevice::IntegratedSensor);
	m_pLiftMotor1->ConfigClosedloopRamp(0.650);

	// Set inverted based on the constructor input
	m_pLiftMotor1->SetInverted(m_bInverted);

	// Set both claws to open (assuming reverse is open :) )
	m_pHighClaw->Set(DoubleSolenoid::Value::kReverse);
	m_pMidClaw->Set(DoubleSolenoid::Value::kReverse);
}

/******************************************************************************
	Description:	Tick CLift
	Arguments:		None
	Returns:		Nothing
******************************************************************************/
void CLift::Tick(ClimbStates kStage)
{
	switch (kStage)
	{
		case eNoClimb:
			m_bReady = true;
			break;

		case ClimbStates::eMid:
			m_bReady = GoMid();
			break;

		case ClimbStates::eHigh:
			m_bReady = GoHigh();
			break;

		case ClimbStates::eTraverse:
			m_bReady = Traverse();
			break;
		
		case ClimbStates::eHang:
			Hang();
			break;
	}
}

/******************************************************************************
	Description:	Activate motors and solenoids for mid bar
	Arguments:		None
	Returns:		bool - whether it has completed the routine
******************************************************************************/
bool CLift::GoMid()
{
	// Check if the encoder counts match the default mid bar position
	if (m_pLiftMotor1->GetSelectedSensorPosition() < m_dDefaultMid)
	{
		// Rotate arm 90 degrees to prepare for mid bar
		m_pLiftMotor1->Set(0.100);
		return false;
	} else {
		// Stop rotating arm and grab bar with claw
		m_pLiftMotor1->Set(0.000);
		m_pMidClaw->Set(DoubleSolenoid::Value::kForward);
		return true;
	}
}

/******************************************************************************
	Description:	Activate motors and solenoids for high bar
	Arguments:		None
	Returns:		bool - whether it has completed the routine
******************************************************************************/
bool CLift::GoHigh()
{
	// Check if the encoder counts match the default high bar position
	if (m_pLiftMotor1->GetSelectedSensorPosition() < m_dDefaultHigh)
	{
		// Rotate arm up 122.6 degrees
		m_pLiftMotor1->Set(0.100);
		return false;
	} else {
		// Stop rotation and grab bar with claw
		m_pLiftMotor1->Set(0.000);
		m_pHighClaw->Set(DoubleSolenoid::Value::kForward);
		return true;
	}
}

/******************************************************************************
	Description:	Activate motors and solenoids for traversal bar
	Arguments:		None
	Returns:		bool - whether it has completed the routine
******************************************************************************/
bool CLift::Traverse()
{
	// Check if encoder counts match default traversal bar position
	if (m_pLiftMotor1->GetSelectedSensorPosition() < m_dDefaultTraverse)
	{
		// Open mid claw and begin rotating arm 180 degrees
		m_pMidClaw->Set(DoubleSolenoid::Value::kReverse);
		m_pLiftMotor1->Set(0.100);
		return false;
	} else {
		// Stop rotation and grab bar with mid claw
		m_pLiftMotor1->Set(0.000);
		m_pMidClaw->Set(DoubleSolenoid::Value::kForward);
		return true;
	}
}

/******************************************************************************
	Description:	Activate motors and solenoids for hanging
	Arguments:		None
	Returns:		Nothing
******************************************************************************/
void CLift::Hang()
{
	// Check if encoder counts match default hanging position
	if (m_pLiftMotor1->GetSelectedSensorPosition() < m_dDefaultHang)
	{
		// Release high bar and begin rotating 57.4 degrees
		m_pHighClaw->Set(DoubleSolenoid::Value::kReverse);
		m_pLiftMotor1->Set(0.100);
	} else {
		// Stop rotation
		m_pLiftMotor1->Set(0.000);
	}
}