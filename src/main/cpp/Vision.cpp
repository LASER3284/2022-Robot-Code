/******************************************************************************
    Description:	Vision implementation
	Class:			Vision
	Project:		2022 Rapid React Robot Code
******************************************************************************/

#include "Vision.h"
#include <frc/smartdashboard/SmartDashboard.h>
///////////////////////////////////////////////////////////////////////////////

CVisionPacket::CVisionPacket(const char* pPacketArr) {
	m_nRandVal			= pPacketArr[0];
	m_nDetectionCount	= pPacketArr[1];
	m_nX				= (pPacketArr[2] << 8) | pPacketArr[3];
	m_nY				= (pPacketArr[4] << 8) | pPacketArr[5];
	m_nWidth		    = (pPacketArr[6] << 8) | pPacketArr[7];
	m_dHalfWidthAngle	= (double)m_nWidth / 2 * dAnglePerPixel;
	m_nHeight			= (pPacketArr[8] << 8) | pPacketArr[9];
	m_dHalfHeightAngle	= (double)m_nHeight / 2 *dAnglePerPixel;
	m_nConfidence		= pPacketArr[10];
	m_uClass			= pPacketArr[11];
	m_nDepth			= *(int*)&pPacketArr[12];
}

CVisionPacket::CVisionPacket() { }

CVisionPacket::~CVisionPacket() {

}