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

const double dFlywheelMotorSpeed = 1.000;
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
    void StartFlywheel();
	void Stop();
    void SetSafety(bool bSafety);
private:
    // Declare class objects and variables.
    WPI_TalonFX*      m_pFlywheelMotor1;
    WPI_TalonFX*      m_pFlywheelMotor2;

    bool m_bSafety;
};
///////////////////////////////////////////////////////////////////////////////

#endif