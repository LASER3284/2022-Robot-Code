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
#include <frc/Filesystem.h>
#include <wpi/fs.h>
#include <map>
#include "pathplanner/lib/PathPlanner.h"

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
	eTaxi2Shot,
	
	eLessDumbTaxi1,
	eLessDumbTaxi2,
	eLessDumbTaxi3,

	eTerminator,

	eFarGremlinBall1,
	eFarGremlinBall2,

	eHangarGremlinBall1,
	eHangarGremlinBall2,

	eMagic4Ball1,
	eMagic4Ball2,
};
///////////////////////////////////////////////////////////////////////////////

class CTrajectoryConstants
{
public:
	struct TrajectoryContainer {
		string m_sPathName = "";
		bool m_bReversed = false;
		Trajectory* m_pSelectedTrajectory = nullptr;
	};

	CTrajectoryConstants();
	void SelectTrajectory(int nSelection);

	// One-line methods.
	Pose2d GetSelectedTrajectoryStartPoint()	{	return m_pSelectedPath.m_pSelectedTrajectory->InitialPose();		};
	Trajectory GetSelectedTrajectory()			{	return *(m_pSelectedPath.m_pSelectedTrajectory);					};
	TrajectoryContainer GetSelectedContainer() {
		return m_pSelectedPath;
	};
	double GetSelectedTrajectoryTotalTime()		{	return (double)m_pSelectedPath.m_pSelectedTrajectory->TotalTime();	};
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
	TrajectoryContainer m_pSelectedPath;

	map<Paths, TrajectoryContainer> m_mpPathFileName = {

		{ eTestPath, { "FarGremlinBall_Pt1", true }},

		{ eFarGremlinBall1, { "FarGremlinBall_Pt1", true }},
		{ eFarGremlinBall2, { "FarGremlinBall_Pt2" }},

		{ eHangarGremlinBall1, { "HangarGremlinBall_Pt1", true}},
		{ eHangarGremlinBall2, { "HangarGremlinBall_Pt2", true}},
				
		{ eMagic4Ball1, { "Magic4Ball_Pt1"}},
		{ eMagic4Ball2, { "Magic4Ball_Pt2"}},

	};
};

#endif