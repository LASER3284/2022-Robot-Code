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

enum Paths {
	eAutoStopped = 0,
	eAutoIdle,
	eTestPath,
	eDumbTaxi,
	eAdvancement1,
	eAdvancement2,
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

private:
	Trajectory* m_pSelectedPath;
};

#endif