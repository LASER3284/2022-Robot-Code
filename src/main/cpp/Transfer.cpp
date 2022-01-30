
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
	m_pTopBeltMotor		= new CANSparkMax(nBeltMotor1, CANSparkMaxLowLevel::MotorType::kBrushless);
	m_pFrontBeltMotor	= new CANSparkMax(nBeltMotor2, CANSparkMaxLowLevel::MotorType::kBrushless);
	m_pBackBeltMotor	= new CANSparkMax(nBeltMotor3, CANSparkMaxLowLevel::MotorType::kBrushless);
}

/******************************************************************************
	Description:	CTransfer destructor, delete variables
	Arguments:		None
	Derived from:	Nothing
******************************************************************************/

CTransfer::~CTransfer()
{
	delete m_pTopBeltMotor;
	delete m_pFrontBeltMotor;
	delete m_pBackBeltMotor;
	
	m_pTopBeltMotor		= nullptr;
	m_pFrontBeltMotor	= nullptr;
	m_pBackBeltMotor	= nullptr;
}

/******************************************************************************
	Description:	Initialization function for CTransfer, init motors
	Arguments:		None
	Returns:		Nothing
******************************************************************************/

void CTransfer::Init()
{
	
}

