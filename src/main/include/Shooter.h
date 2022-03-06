/****************************************************************************
	Description:	Defines the CDrive control class.
	Classes:		CDrive
	Project:		2022 Rapid React Robot Code
****************************************************************************/
#ifndef Shooter_h
#define Shooter_h

#include "IOMap.h"
#include "FalconMotion.h"
#include <rev/CANSparkMax.h>
#include <ctre/phoenix/motorcontrol/can/WPI_TalonFX.h>
#include <frc/Joystick.h>
#include <frc/smartdashboard/SmartDashboard.h>

using namespace frc;
using namespace rev;
using namespace units;
using namespace ctre::phoenix::motorcontrol;

// Normal Speed: 0.700
const double dFlywheelMotorSpeed = -0.755;
const double dIdleMotorSpeed = -0.500;


// Calculate the expect peak sensor velocity (sensor units per 100ms) as:
// (kMaxRPM / 600) * (kSensorUnitsPerRotation / kGearRatio)
const double dPeakSensorVelocity = (6380 / 600) * (2048 / 1); 
const double dExpectedShotVelocity = dPeakSensorVelocity * dFlywheelMotorSpeed;
const double dExpectedIdleVelocity = dPeakSensorVelocity * dIdleMotorSpeed;

///////////////////////////////////////////////////////////////////////////////

/******************************************************************************
    Description:	CShooter class definition.
    Arguments:		None
    Derived From:	Nothing
******************************************************************************/
class CShooter
{
public:
    // Declare class methods.
    CShooter();
    ~CShooter();
    void Init();
    void Tick();
    void StartFlywheelShot();
    void IdleStop();
	void Stop();
    void SetSafety(bool bSafety);

    bool m_bShooterOn;
    bool m_bShooterFullSpeed;
private:
    // Declare class objects and variables.
    WPI_TalonFX*      m_pFlywheelMotor1;
    WPI_TalonFX*      m_pFlywheelMotor2;

    bool m_bSafety;

    double m_dPropotional = 2.51;
    double m_dIntegral = 1e-5;
    double m_dDerivative = 0.0011;
    double m_dFeedForward = 0.0465;
};
///////////////////////////////////////////////////////////////////////////////

#endif