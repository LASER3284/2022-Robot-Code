/******************************************************************************
	Description:	Defines the CLift control class.
	Classes:		CLift
	Project:		2022 Rapid React Robot Code
******************************************************************************/
#ifndef Lift_h
#define Lift_h

#include "IOMap.h"
#include <ctre/phoenix/motorcontrol/can/WPI_TalonFX.h>
#include <frc/Solenoid.h>

using namespace ctre::phoenix::motorcontrol::can;
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
	void Init();
	void ExtendArms();
	void SwingArms();
	void Retract();
	void Unswing();

private:
	// Declare class objects and variables.
	WPI_TalonFX*		m_pLiftMotor1;
	WPI_TalonFX*		m_pLiftMotor2;
	Solenoid*			m_pLeftSolenoid;
	Solenoid*			m_pRightSolenoid;

	bool		bExtended;
	bool		bSwingExtended;
};
///////////////////////////////////////////////////////////////////////////////
#endif