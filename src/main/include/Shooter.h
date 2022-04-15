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
    void AdjustVelocity(double dVelocityPercent);

    bool m_bShooterOn;
    bool m_bShooterFullSpeed;

    double m_dFlywheelMotorSpeed = 0.400;
    double m_dIdleMotorSpeed = 0.375;
private:
    // Declare class objects and variables.
    WPI_TalonFX*      m_pFlywheelMotor1;
    WPI_TalonFX*      m_pFlywheelMotor2;

    bool m_bSafety;
    bool m_bIdle;
    double m_dPropotional = 2.51575;
    double m_dIntegral = 1e-4795;
    double m_dDerivative = 0.00155;
    double m_dFeedForward = 0.0465;


    // Calculate the expect peak sensor velocity (sensor units per 100ms) as:
    // (kMaxRPM / 600) * (kSensorUnitsPerRotation / kGearRatio)
    const double m_dPeakSensorVelocity = (6380 / 600) * (2048 / 1); 
    double m_dExpectedShotVelocity = m_dPeakSensorVelocity * m_dFlywheelMotorSpeed;
    double m_dExpectedIdleVelocity = m_dPeakSensorVelocity * m_dIdleMotorSpeed;
};
///////////////////////////////////////////////////////////////////////////////

#endif