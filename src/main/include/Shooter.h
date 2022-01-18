/****************************************************************************
	Description:	Defines the CDrive control class.
	Classes:		CDrive
	Project:		2022 Rapid React Robot Code
****************************************************************************/
#ifndef Shooter_h
#define Shooter_h

#include "IOMap.h"

#include <rev/CANSparkMax.h>
#include <ctre/phoenix/motorcontrol/can/WPI_TalonFX.h>
#include <frc/Joystick.h>
#include <frc/smartdashboard/SmartDashboard.h>

using namespace rev;
using namespace frc;
using namespace units;
///////////////////////////////////////////////////////////////////////////////

/******************************************************************************
    Description:	CShooter class definition.
    Arguments:		None
    Derived From:	Nothing
******************************************************************************/
class CShooter
{
public:
    CShooter(Joystick* pShooterJoystick);
    ~CShooter();
	
private:
};
///////////////////////////////////////////////////////////////////////////////
#endif