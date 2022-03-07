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
	m_pLiftMotor1 		= new WPI_TalonFX(nLiftMotor1);
	m_pLiftMotor2 		= new WPI_TalonFX(nLiftMotor2);
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
	
	m_pLiftMotor1		= nullptr;
	m_pLiftMotor2		= nullptr;
}