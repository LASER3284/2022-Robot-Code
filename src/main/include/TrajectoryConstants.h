/****************************************************************************
	Description:	Defines the Poses used for autonomous.
	Classes:		CTrajectoryConstants
	Project:		2022 Rapid React Robot Code
****************************************************************************/
#ifndef TrajectoryConstants_h
#define TrajectoryConstants_h

#include <frc/geometry/Pose2d.h>
#include <frc/geometry/Translation2d.h>
#include <frc/trajectory/TrajectoryConfig.h>
#include <frc/trajectory/Trajectory.h>
#include <frc/trajectory/TrajectoryUtil.h>

using namespace frc;
using namespace units;
using namespace std;
using namespace wpi;

enum Paths : int {
	eAutoStopped = 0,
	eAutoIdle,
	eTestPath,
	
	eDumbTaxi,
	eTaxiShot,
	
	eLessDumbTaxi1,
	eLessDumbTaxi2,
	eLessDumbTaxi3,
	
	eAdvancement1,
	eAdvancement2,

	eTerminator,
};
///////////////////////////////////////////////////////////////////////////////

class CTrajectoryConstants
{
public:
	void SelectTrajectory(int nSelection);
	void SelectTrajectory(Trajectory Path);

	// One-line methods.
	Pose2d GetSelectedTrajectoryStartPoint()	{	return m_pSelectedPath->InitialPose();		};
	Trajectory GetSelectedTrajectory()			{	return *m_pSelectedPath;						};
	double GetSelectedTrajectoryTotalTime()		{	return (double)m_pSelectedPath->TotalTime();	};
	static bool IsInShootingRange(double depth) {
		
		/*return (
			(depth > (CTrajectoryConstants::m_dAutoShootingDistance - CTrajectoryConstants::m_dAutoShootingRange)) &&
			(depth < (CTrajectoryConstants::m_dAutoShootingDistance + CTrajectoryConstants::m_dAutoShootingRange))
		);*/
		return false;
	}

	// Average shooting distance in mm
	//const double m_dAutoShootingDistance = 5180;
	//const double m_dAutoShootingRange = 600;

private:
	Trajectory* m_pSelectedPath;
};

#endif