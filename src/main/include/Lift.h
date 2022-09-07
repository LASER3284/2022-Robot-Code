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
#include <frc/filter/MedianFilter.h>
#include <frc/Timer.h>
#include <frc/smartdashboard/SmartDashboard.h>

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
	CLift();
	~CLift();
	void Tick(ClimbStates kStage);
	void Init();
	bool GoMid();
	bool GoHigh();
	bool Traverse();
	void Hang();
	void ReleaseMid();
	void ReleaseHigh();
	void ManualAdjust(double dSpeed);
	void SetFrontHook(bool bValue);
	void SetBackHook(bool bValue);

	bool m_bReady; // Bool on whether the Lift mechanism is ready for the next stage

private:
	// Declare class objects and variables.
	WPI_TalonFX*		    m_pLiftMotor1;
	WPI_TalonFX*			m_pLiftMotor2;
	Solenoid*				m_pFrontClaw;
	Solenoid*				m_pBackClaw;

	// A median filter is used to easily filter out outliers.
	// See WPILib docs: https://docs.wpilib.org/en/stable/docs/software/advanced-controls/filters/median-filter.html
	MedianFilter<double>*   m_pMedianFilter1;
	MedianFilter<double>*   m_pMedianFilter2;

	// Elapsed time (in ms) that either of the lift motors have been stalled.
	double m_dElapsedStallTime           = 0;
	double m_dLastCalculateTime          = 0;

	// Whether or not any of the motors for lift are stalled out.
	bool   m_bMotorStalling				 = false;

	// Minimum amount of milliseconds for the motor to be stalling in order to consider it "stalling"
	const double m_dMinStallMilliseconds = 250;
	const double m_dMinStallCurrent      = 20; // TODO: Fix this assumption; No idea if 20A is reasonable

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