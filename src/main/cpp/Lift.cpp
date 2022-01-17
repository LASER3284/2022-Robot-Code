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
	// Init local classes

	// Init local variables
	m_bReady			= true;
	m_bIdle				= true;
	m_nCurrentState		= eIdle;
}

/******************************************************************************
	Description:	CLift destructor - delete local variables/classes
	Arguments:		None
	Returns:		Nothing
******************************************************************************/
CLift::~CLift(){}

/******************************************************************************
	Description:	Update m_bIdle to either true or false based on 
					m_nCurrentLiftStep
	Arguments:		None
	Returns:		Nothing
******************************************************************************/
void CLift::UpdateIdleState() 
{
	if (m_nCurrentState == eIdle)
	{
		m_bIdle = true;
	}
	else
	{
		m_bIdle = false;
	}
}