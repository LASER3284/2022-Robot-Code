
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

CTransfer::CTransfer(){
	m_pBeltMotor1		= new CSparkMotion(nBeltMotor1);
	m_pBeltMotor2		= new CSparkMotion(nBeltMotor2);
	m_pBeltMotor3		= new CSparkMotion(nBeltMotor3);
}

/******************************************************************************
	Description:	CTransfer destructor, delete variables
	Arguments:		None
	Derived from:	Nothing
******************************************************************************/

CTransfer::~CTransfer(){
	delete m_pBeltMotor1;
	delete m_pBeltMotor2;
	delete m_pBeltMotor3;
	
	m_pBeltMotor1		= nullptr;
	m_pBeltMotor2		= nullptr;
	m_pBeltMotor3		= nullptr;
}

/******************************************************************************
	Description:	Initialization function for CTransfer, init motors
	Arguments:		None
	Returns:		Nothing
******************************************************************************/

void CTransfer::Init(){
	// Reset sticky faults
	m_pBeltMotor1->ClearStickyFaults();
	m_pBeltMotor2->ClearStickyFaults();
	m_pBeltMotor3->ClearStickyFaults();
}

