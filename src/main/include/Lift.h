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
#include <frc/Solenoid.h>

using namespace rev;
using namespace frc;

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

private:
	// Declare class objects and variables.
	CFalconMotion*		m_pLiftMotor1;
	CFalconMotion*		m_pLiftMotor2;
	CFalconMotion*		m_pLiftMotor3;
	CFalconMotion*		m_pLiftMotor4;
};
///////////////////////////////////////////////////////////////////////////////
#endif