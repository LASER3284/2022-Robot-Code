/******************************************************************************
    Description:	Vision implementation
	Class:			Vision
	Project:		2022 Rapid React Robot Code
******************************************************************************/

#include "Vision.h"
#include <frc/smartdashboard/SmartDashboard.h>
///////////////////////////////////////////////////////////////////////////////

VisionPacket::VisionPacket(const char* pPacketArr) {
	m_randVal        = pPacketArr[0];
	m_detectionCount = pPacketArr[1];
	m_x              = (pPacketArr[2] << 8) | pPacketArr[3];
	m_y              = (pPacketArr[4] << 8) | pPacketArr[5];
	m_width          = (pPacketArr[6] << 8) | pPacketArr[7];
	m_height         = (pPacketArr[8] << 8) | pPacketArr[9];
	m_confidence     = pPacketArr[10];
	m_class          = pPacketArr[11];
	m_depth          = *(int*)&pPacketArr[12];
}

VisionPacket::VisionPacket() { }

VisionPacket::~VisionPacket() {

}