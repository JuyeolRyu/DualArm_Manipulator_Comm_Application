#pragma once
#include "stdafx.h"
#include "CanOpenDef.h"

class CanOpenInterface
{
public:
	CanOpenInterface(void);
	virtual ~CanOpenInterface(void);

public:
	int WriteNMT(HANDLE ch, uint32_t id, uint8_t command, int len);	
	int ReadSDO(HANDLE ch, uint32_t id, uint16_t index, uint8_t subIndex, int len);
	int WriteSDO(HANDLE ch, uint32_t id, uint16_t index, uint8_t subIndex, uint8_t *object, int len);

	// ELMO
	int RPDO2_ELMO(HANDLE ch, uint32_t id, uint16_t index, uint8_t subIndex, uint8_t *object, int len);

	// Robotro 
	int ReadRobotro(HANDLE ch, uint32_t id,  uint16_t index, int len);	
	int WriteRobotro(HANDLE ch, uint32_t id,  uint16_t index, uint32_t object);

	int GetRobotro(HANDLE ch, uint32_t id,  uint16_t index);

private:
	int WriteRobotro(HANDLE ch, uint32_t id,  uint16_t index, uint8_t *object, int len);

};
