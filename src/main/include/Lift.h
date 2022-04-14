/******************************************************************************
	Description:	Defines the CLift control class.
	Classes:		CLift
	Project:		2022 Rapid React Robot Code
******************************************************************************/
#ifndef Lift_h
#define Lift_h

#include "IOMap.h"
#include <ctre/phoenix/motorcontrol/can/WPI_TalonFX.h>
#include <frc/DoubleSolenoid.h>

using namespace ctre::phoenix::motorcontrol::can;
using namespace ctre::phoenix::motorcontrol;
using namespace frc;
///////////////////////////////////////////////////////////////////////////////

enum ClimbStates {
	eNoClimb = 0,
	eMid,
	eHigh,
	eTraverse,
	eHang
};

/******************************************************************************
	Description:	CLift class definition.
	Arguments:		None
	Derived From:	Nothing
******************************************************************************/
class CLift
{
public:
	// Declare class methods.
	CLift(bool bInverse);
	~CLift();
	void Tick(ClimbStates kStage);
	void Init();
	bool GoMid();
	bool GoHigh();
	bool Traverse();
	void Hang();
	void ReleaseMid();
	void ReleaseHigh();

	bool m_bReady; // Bool on whether the Lift mechanism is ready for the next stage

private:
	// Declare class objects and variables.
	WPI_TalonFX*		m_pLiftMotor1;
	DoubleSolenoid*		m_pMidClaw;
	DoubleSolenoid*		m_pHighClaw;

	// Multiply motor counts per rev by inverse of gear ratio
	// then divide by 360 degrees
	const double m_dEncoderCountsPerRev = 2048.0 * 248.830;
	const double m_dCountsPerDegree		= m_dEncoderCountsPerRev / 360.000;

	// Constant degree measurements for each climbing stage
	// NOTE: these may need to be inverted
	const double m_dDefaultMid		= m_dCountsPerDegree * 90.000;
	const double m_dDefaultHigh		= m_dCountsPerDegree * 122.600 + m_dDefaultMid;
	const double m_dDefaultTraverse	= m_dCountsPerDegree * 180.000 + m_dDefaultHigh;
	const double m_dDefaultHang		= m_dCountsPerDegree * 57.400 + m_dDefaultTraverse;

	bool m_bInverted;

};
///////////////////////////////////////////////////////////////////////////////
#endif