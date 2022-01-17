/******************************************************************************
	Description:	Defines the CLift control class.
	Classes:		CLift
	Project:		2022 Rapid React Robot Code
******************************************************************************/
#ifndef Lift_h
#define Lift_h

#include "IOMap.h"
#include "SparkMotion.h"
#include "FalconMotion.h"

using namespace rev;
using namespace frc;
using namespace units;

// Declare constants
const double dJoystickDeadzone					= 0.100;

// LiftStates enumerator
enum LiftStates {eLiftIdle = 0};
///////////////////////////////////////////////////////////////////////////////

/******************************************************************************
	Description:	CLift class definition.
	Arguments:		None
	Derived From:	Nothing
******************************************************************************/
class CLift
{
public:
	// Declare class methods.
	CLift();
	~CLift();
	void UpdateIdleState();

	// One line methods
	int GetCurrentState()	{	return m_nCurrentState;	};

private:
	// Declare class objects and variables.
	int			m_nCurrentState;
	bool		m_bReady;
	bool		m_bIdle;
};
///////////////////////////////////////////////////////////////////////////////
#endif