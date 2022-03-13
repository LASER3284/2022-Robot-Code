
/******************************************************************************
    Description:		CTransfer implementation
	Classes:		CTransfer
	Project:		2022 Rapid React Robot Code
******************************************************************************/

#include "Transfer.h"

#include <frc/smartdashboard/SmartDashboard.h>

///////////////////////////////////////////////////////////////////////////////

/******************************************************************************
	Description:	CTransfer constructor, init variables
	Arguments:		None
	Derived from:	Nothing
******************************************************************************/
CTransfer::CTransfer()
{
	m_pTopMotor			= new CANSparkMax(nTransferVertical, CANSparkMaxLowLevel::MotorType::kBrushless);
	m_pFrontMotor		= new CANSparkMax(nTransferFront, CANSparkMaxLowLevel::MotorType::kBrushless);
	m_pBackMotor		= new CANSparkMax(nTransferBack, CANSparkMaxLowLevel::MotorType::kBrushless);

	m_pTopInfrared		= new DigitalInput(nTopTransferInfrared);
	m_pFrontInfrared	= new DigitalInput(nFrontTransferInfrared);
	m_pBackInfrared		= new DigitalInput(nBackTransferInfrared);

	m_pFrontDebouncer = new Debouncer {
		80_ms,
		Debouncer::DebounceType::kBoth
	}; 
	m_pBackDebouncer = new Debouncer {
		20_ms,
		Debouncer::DebounceType::kBoth
	};
	m_pTopDebouncer = new Debouncer {
		220_ms,
		Debouncer::DebounceType::kBoth
	};
}

/******************************************************************************
	Description:	CTransfer destructor, delete variables
	Arguments:		None
	Derived from:	Nothing
******************************************************************************/
CTransfer::~CTransfer()
{
	delete m_pTopMotor;
	delete m_pFrontMotor;
	delete m_pBackMotor;
	delete m_pTopInfrared;
	delete m_pFrontInfrared;
	delete m_pBackInfrared;
	delete m_pFrontDebouncer;
	delete m_pBackDebouncer;
	delete m_pTopDebouncer;

	m_pTopMotor			= nullptr;
	m_pFrontMotor		= nullptr;
	m_pBackMotor		= nullptr;
	m_pTopInfrared		= nullptr;
	m_pFrontInfrared	= nullptr;
	m_pBackInfrared		= nullptr;
	m_pFrontDebouncer	= nullptr;
	m_pBackDebouncer	= nullptr;
	m_pTopDebouncer		= nullptr;
}

/******************************************************************************
	Description:	Initialization function for CTransfer, init motors
	Arguments:		None
	Returns:		Nothing
******************************************************************************/
void CTransfer::Init()
{
	m_pTopMotor->SetOpenLoopRampRate(0.250);
	m_pFrontMotor->SetOpenLoopRampRate(0.750);
	m_pBackMotor->SetOpenLoopRampRate(0.750);
	m_bBallLocked = false;
	UpdateLocations();
}

/******************************************************************************
	Description:	Start vertical transfer motor
	Arguments:		None
	Returns:		Nothing
******************************************************************************/
void CTransfer::StartVertical()
{
	m_pTopMotor->Set(-0.225);
}

/******************************************************************************
	Description:	Start vertical transfer motor for shooting (higher RPM)
	Arguments:		None
	Returns:		Nothing
******************************************************************************/
void CTransfer::StartVerticalShot() {
	m_pTopMotor->Set(-0.950);
}

/******************************************************************************
	Description:	Start front transfer motor
	Arguments:		None
	Returns:		Nothing
******************************************************************************/
void CTransfer::StartFront()
{
	m_pFrontMotor->Set(-0.850);
}

/******************************************************************************
	Description:	Start back transfer motor
	Arguments:		None
	Returns:		Nothing
******************************************************************************/
void CTransfer::StartBack()
{
	m_pBackMotor->Set(0.850);
}

/******************************************************************************
	Description:	Stop vertical motor
	Arguments:		None
	Returns:		Nothing
******************************************************************************/
void CTransfer::StopVertical()
{
	m_pTopMotor->Set(0.000);
}

/******************************************************************************
	Description:	Stop front transfer motor
	Arguments:		None
	Returns:		Nothing
******************************************************************************/
void CTransfer::StopFront()
{
	m_pFrontMotor->Set(0.000);
}

/******************************************************************************
	Description:	Stop back transfer motor
	Arguments:		None
	Returns:		Nothing
******************************************************************************/
void CTransfer::StopBack()
{
	m_pBackMotor->Set(0.000);
}

/******************************************************************************
	Description:	Update locations of balls in the robot
	Arguments:		None
	Returns:		Nothing
******************************************************************************/
void CTransfer::UpdateLocations()
{
	// Due to flutter in the sensor, we use a variable to "lock" the sensor until the shooter has shot the ball.
	if(m_bBallLocked) m_aBallLocations[0] = true;
	else m_aBallLocations[0] = m_pTopDebouncer->Calculate(m_pTopInfrared->Get());

	m_aBallLocations[1] = !m_pFrontDebouncer->Calculate(m_pFrontInfrared->Get());
	m_aBallLocations[2] = m_pBackDebouncer->Calculate(m_pBackInfrared->Get());
}