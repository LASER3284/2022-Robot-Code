 /******************************************************************************
	Description:	Implements the CLift control class.
	Classes:		CLift
	Project:		2022 Rapid React Robot Code
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
	m_pLiftMotor1		= new CFalconMotion(nLiftMotor1);
	m_pLiftMotor2		= new CFalconMotion(nLiftMotor2);
	m_pLiftMotor3		= new CFalconMotion(nLiftMotor3);
	m_pLiftMotor4		= new CFalconMotion(nLiftMotor4);
	
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
	delete m_pLiftMotor3;
	delete m_pLiftMotor4;
	
	m_pLiftMotor1		= nullptr;
	m_pLiftMotor2		= nullptr;
	m_pLiftMotor3		= nullptr;
	m_pLiftMotor4		= nullptr;
}