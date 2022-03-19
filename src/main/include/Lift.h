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
using namespace ctre::phoenix::motorcontrol;
using namespace frc;

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
	void Tick();
	void Init();
	void MoveArms(double dJoystickPosition);

private:
	// Declare class objects and variables.
	WPI_TalonFX*		m_pLiftMotor1;
	WPI_TalonFX*		m_pLiftMotor2;
};
///////////////////////////////////////////////////////////////////////////////
#endif