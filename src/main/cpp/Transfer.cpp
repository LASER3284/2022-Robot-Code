
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
	m_pBackMotor		= new CANSparkMax(nTransferBack, CANSparkMaxLowLevel::MotorType::kBrushless);
	m_pTopInfrared		= new DigitalInput(nTopTransferInfrared);
	m_pBackInfrared		= new DigitalInput(nBackTransferInfrared);

	m_pBackDebouncer = new Debouncer {
		20_ms,
		Debouncer::DebounceType::kBoth
	};
	m_pTopDebouncer = new Debouncer {
		20_ms,
		Debouncer::DebounceType::kRising
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
	delete m_pBackMotor;
	delete m_pTopInfrared;
	delete m_pBackInfrared;
	delete m_pBackDebouncer;
	delete m_pTopDebouncer;

	m_pTopMotor			= nullptr;
	m_pBackMotor		= nullptr;
	m_pTopInfrared		= nullptr;
	m_pBackInfrared		= nullptr;
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
	m_pTopMotor->SetOpenLoopRampRate(0.000);
	m_pTopMotor->SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
	m_pBackMotor->SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
	m_pBackMotor->SetOpenLoopRampRate(0.000);
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
	// Note: originally 0.750 
	// (:
	m_pTopMotor->Set(-0.750);
}

/******************************************************************************
	Description:	Start the vertical transfer motor reversed
	Arguments:		None
	Returns:		Nothing
******************************************************************************/
void CTransfer::ReverseVertical() {
	m_pTopMotor->Set(0.225);
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
	Description:	Start back transfer motor
	Arguments:		None
	Returns:		Nothing
******************************************************************************/
void CTransfer::StartBack()
{
	m_pBackMotor->Set(0.500);
}


/******************************************************************************
	Description:	Start the back transfer motor reversed for spitting out balls
	Arguments:		None
	Returns:		Nothing
******************************************************************************/
void CTransfer::ReverseBack()
{
	m_pBackMotor->Set(-0.500);
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
	m_aBallLocations[0] = m_pTopDebouncer->Calculate(!m_pTopInfrared->Get());	
	m_aBallLocations[1] = m_pBackDebouncer->Calculate(!m_pBackInfrared->Get());
}