/******************************************************************************
	Description:	Implements the CLift control class.
	Classes:		CLift
	Project:		2022 Rapid React Robot Code
******************************************************************************/

#include "Lift.h"
///////////////////////////////////////////////////////////////////////////////

/******************************************************************************
	Description:	CLift constructor - init local variables/classes
	Returns:		Nothing
******************************************************************************/
CLift::CLift()
{
	m_pLiftMotor1	= new WPI_TalonFX(nLiftMotor1);
	m_pLiftMotor2	= new WPI_TalonFX(nLiftMotor2);

	m_pBackClaw = new Solenoid(0, PneumaticsModuleType::CTREPCM, nBackClaw1);
	m_pFrontClaw = new Solenoid(0, PneumaticsModuleType::CTREPCM, nFrontClaw1);
	
	m_pMedianFilter1 = new MedianFilter<double>(60);
	m_pMedianFilter2 = new MedianFilter<double>(60);
}

/******************************************************************************
	Description:	CLift destructor - delete local variables/classes
	Arguments:		None
	Returns:		Nothing
******************************************************************************/
CLift::~CLift()
{
	delete m_pLiftMotor1;
	delete m_pMedianFilter1;

	delete m_pLiftMotor2;
	delete m_pMedianFilter2;

	delete m_pBackClaw;
	delete m_pFrontClaw;
	
	m_pLiftMotor1	 = nullptr;
	m_pMedianFilter1 = nullptr;
	m_pMedianFilter2 = nullptr;
	m_pBackClaw      = nullptr;
	m_pFrontClaw     = nullptr;
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

	// Configure rotary encoder for Lift Motor
	m_pLiftMotor1->ConfigSelectedFeedbackSensor(FeedbackDevice::IntegratedSensor);
	m_pLiftMotor2->ConfigSelectedFeedbackSensor(FeedbackDevice::IntegratedSensor);

	m_pLiftMotor1->ConfigClosedloopRamp(0.650);
	m_pLiftMotor2->ConfigClosedloopRamp(0.650);

	// Invert one of the falcons from the other one
	m_pLiftMotor1->SetInverted(false);
	m_pLiftMotor2->SetInverted(true);

	m_pFrontClaw->Set(true);
	m_pBackClaw->Set(true);
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

	// Add in some form of "stall detection" to check if the motors are stalling out.
	const double dFilteredCurrent1 = m_pMedianFilter1->Calculate(m_pLiftMotor1->GetSupplyCurrent());
	const double dFilteredCurrent2 = m_pMedianFilter2->Calculate(m_pLiftMotor2->GetSupplyCurrent());

	// Check if the filtered currents are greater than the minimum stall current
	const double currentSeconds = (double)Timer::GetFPGATimestamp();
	const double elapsedTime = (currentSeconds - m_dLastCalculateTime) / 1000.0;

	// If any of the motors are stalling, increment our elapsed stall time.
	if(dFilteredCurrent1 > m_dMinStallCurrent || dFilteredCurrent2 > m_dMinStallCurrent) 
		m_dElapsedStallTime += elapsedTime;
	else 
		m_dElapsedStallTime -= elapsedTime;

	m_dLastCalculateTime = (double)Timer::GetFPGATimestamp();
	m_bMotorStalling = (m_dElapsedStallTime >= m_dMinStallMilliseconds);
	
	// Update the dashboard
	SmartDashboard::PutBoolean("bLiftStalling", m_bMotorStalling);
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
		ManualAdjust(0.850);
		return false;
	} else {
		// Stop rotating arm and grab bar with claw
		ManualAdjust(0.000);
		m_pFrontClaw->Set(false);
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
		ManualAdjust(0.850);
		m_pBackClaw->Set(false);
		return false;
	} else {
		// Stop rotation and grab bar with claw
		ManualAdjust(0.000);
		m_pBackClaw->Set(true);
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
		m_pFrontClaw->Set(false);
		ManualAdjust(0.850);
		return false;
	} else {
		// Stop rotation and grab bar with mid claw
		ManualAdjust(0.000);
		m_pFrontClaw->Set(true);
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
		m_pBackClaw->Set(false);
		ManualAdjust(0.850);
	} else {
		// Stop rotation
		ManualAdjust(0.000);
	}
}

/******************************************************************************
	Description:	Manual adjustment for climbing arms
	Arguments:		double dSpeed - the speed at which to adjust the arms
	Returns:		Nothing
******************************************************************************/
void CLift::ManualAdjust(double dSpeed)
{
	m_pLiftMotor1->Set(dSpeed);
	m_pLiftMotor2->Set(dSpeed);
}

/******************************************************************************
	Description:	Manual set or release of mid hook
	Arguments:		bool bValue - whether to set or release mid hook
	Returns:		Nothing
******************************************************************************/
void CLift::SetFrontHook(bool bValue)
{
	m_pFrontClaw->Set(bValue);
}
/******************************************************************************
	Description:	Manual set or release of High hook
	Arguments:		bool bValue - whether to set or release High hook
	Returns:		Nothing
******************************************************************************/
void CLift::SetBackHook(bool bValue)
{
	m_pBackClaw->Set(bValue);
}