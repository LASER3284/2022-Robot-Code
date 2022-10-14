/****************************************************************************
	Description:	Implements the Poses used for autonomous.
	Classes:		CTrajectoryConstants
	Project:		2022 Rapid React Robot Code
****************************************************************************/

#include "TrajectoryConstants.h"

using namespace pathplanner;

CTrajectoryConstants::CTrajectoryConstants() {
	for(auto it = m_mpPathFileName.begin(); it != m_mpPathFileName.end(); it++) {
		Paths path = it->first;
		TrajectoryContainer sTrajectory = it->second;

		PathPlannerTrajectory pathplannerTrajectory = PathPlanner::loadPath(sTrajectory.m_sPathName, 3_mps, 3.0_mps_sq, sTrajectory.m_bReversed);
		m_mpPathFileName[path].m_pSelectedTrajectory = new Trajectory(pathplannerTrajectory.asWPILibTrajectory());
	}
}

///////////////////////////////////////////////////////////////////////////////

/******************************************************************************
    Description:	Set selected trajectory based on enumerator
	Arguments:		int nSelection
	Derived from:	Nothing
******************************************************************************/
void CTrajectoryConstants::SelectTrajectory(int nSelection)
{
	Paths eSelection = (Paths)nSelection;
	
	if(m_mpPathFileName.count(eSelection)) {
		m_pSelectedPath = m_mpPathFileName.at(eSelection);
	}
}