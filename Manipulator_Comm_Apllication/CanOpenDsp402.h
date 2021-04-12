#pragma once
#include "CanOpenDef.h"
#include "CanOpenInterface.h"
#include "CanRobotroDef.h"

class CanOpenDsp402
{
public:
	CanOpenDsp402(HANDLE ch, CanOpenInterface *canOpen);
	virtual ~CanOpenDsp402(void);

protected:
	HANDLE _ch;
	CanOpenInterface *_canOpen;
	uint8_t _operationMode;

public:	
	int ResetNode(uint32_t id);
	
	int SetControlWord(uint32_t id, uint16_t control);								//	0x6040
	int GetControlWord(uint32_t id);

	int FaultReset(uint32_t id);
	int Shutdown(uint32_t id);
	int SwitchOn(uint32_t id);
	int EnableOperation(uint32_t id);
	int DisableOperation(uint32_t id);
	int Halt(uint32_t id);

	int SetModesOfOperation(uint32_t id, int8_t modesOfOperation);							//	0x6060
	int GetModesOfOperation(uint32_t id);

	int GetActualPosition(uint32_t id);								//	0x6064
	int GetActualVelocity(uint32_t id);								//	0x606C


	int SetTargetTorque(uint32_t id, int16_t targetTorque);									//	0x6071
	int GetTargetTorque(uint32_t id);

	int GetActualTorque(uint32_t id);						//	0x6077
	int GetActualCurrent(uint32_t id);								//	0x6078
	int GetRatedCurrent(uint32_t id);								//	0x6075

	int SetTargetPosition(uint32_t id, int32_t targetPosition);								//	0x607A
	int SetProfileTargetPosition(uint32_t id, int32_t targetPosition, int mode = 0);		//	0x607A
	int GetTargetPosition(uint32_t id);

	int SetProfileVelocity(uint32_t id, uint32_t profileVelocity);						//	0x6081
	int GetProfileVelocity(uint32_t id);
	int SetMotionProfileType(uint32_t id, int16_t motionProfileType);							//	0x6086
	int GetMotionProfileType(uint32_t id);

	int SetTargetVelocity(uint32_t id, int32_t targetVelocity);									//	0x60FF
	int GetTargetVelocity(uint32_t id);

	void MotorInitialize(uint32_t id);

	// ELMO command
	int HomeActivation_ELMO(uint32_t id, int8_t activationFlag);
	int HomeEventDEF_ELMO(uint32_t id, int8_t eventDescription);
	int GetPosition_ELMO(uint32_t id);

	//Method combination Robotro
	int SetControlRobotro(uint32_t id, uint32_t control);
	int ServoOFF(uint32_t id);
	int ServoOn(uint32_t id);
	int Stop(uint32_t id);

	int Homing(uint32_t id, uint32_t control);

	int GetPositionRobotro(uint32_t id);
	int GetVelocityRobotro(uint32_t id);
	int GetCurrentRobotro(uint32_t id);
	int GetVoltageRobotro(uint32_t id);
	int GetInternalTempRobotro(uint32_t id);
	int GetMotorTempRobotro(uint32_t id);
#ifdef JUNISERVO_R8
	int GetZeroFlagRobotro(uint32_t id);
#endif // JUNISERVO_R8

	int GetStatusRobotro(uint32_t id);

	int GetCmdVelRobotro(uint32_t  id);
	int SetCmdVelRobotro(uint32_t id, uint32_t cmdVel);

	int GetCmdToqRobotro(uint32_t id);
	int SetCmdToqRobotro(uint32_t id,uint32_t cmdToq);

	int GetCmdPosRobotro(uint32_t id);
	int SetCmdPosRobotro(uint32_t id, uint32_t cmdPos);

	int GetCmd360Robotro(uint32_t id);

	int GetEmgStopRobotro(uint32_t id);
	int SetEmgStopRobotro(uint32_t id, uint32_t BitsSet);

	int GetActionModeRobotro(uint32_t id);
	int SetActionModeRobotro(uint32_t id, uint32_t BitsSet);

	int GoPositionRobotro(uint32_t id,uint32_t torque);

	int ZogCCWRobotro(uint32_t id, uint32_t direction);
	int ZogCWRobotro(uint32_t id, uint32_t direction);


	int GetCmdRelPosRobotro(uint32_t id);
	int GetIDRobotro(uint32_t id);
	int SetIdRobotro(uint32_t id, uint32_t configId);

	int GetBaudRateRobotro(uint32_t id);
	int SetBaudRateRobotro(uint32_t id, uint32_t baudRate);

	int GetSignalModeRobotro(uint32_t id);
	int GetSimpleReturnDelay(uint32_t id);
	int SetSimpleReturnDelayRobotro(uint32_t id, uint32_t simpleReturnDelay);

	int GetNormalReturnDelay(uint32_t id);
	int SetNormalReturnDelayRobotro(uint32_t id, uint32_t normalReturnDelay);

	int GetID2Robotro(uint32_t id);
	int SetId2Robotro(uint32_t id, uint32_t configId2);

	int GetPowConfigRobotro(uint32_t id);

	int GetSlopeRobotro(uint32_t id);
	int SetPosSlopeRobotro(uint32_t id, uint32_t posSlope);

	int GetDeadBandRobotro(uint32_t id);
	int SetDeadBandRobotro(uint32_t id, uint32_t deadBand);	
	
	int GetPosMaxRobotro(uint32_t id);
	int SetPosMaxRobotro(uint32_t id, uint32_t posMax);

	int GetPosMinRobotro(uint32_t id);
	int SetPosMinRobotro(uint32_t id, uint32_t posMin);

	int GetVelMaxRobotro(uint32_t id);
	int SetVelMaxRobotro(uint32_t id, uint32_t velMax);

	int GetToqMaxRobotro(uint32_t id);
	int SetToqMaxRobotro(uint32_t id, uint32_t toqMax);

	int GetVoltageMaxRobotro(uint32_t id);
	int SetVoltageMaxRobotro(uint32_t id, uint32_t voltageMin);

	int GetVoltageMinRobotro(uint32_t id);
	int SetVoltageMinRobotro(uint32_t id, uint32_t voltageMin);

	int GetTempMaxRobotro(uint32_t id);
	int SetTempMaxRobotro(uint32_t id, uint32_t tempMax);

	int GetEncConfigRobotro(uint32_t id);
	int SetEncConfigRobotro(uint32_t id, uint32_t encConfig);

	int GetEncOffsetRobotro(uint32_t id);
	int SetEncOffsetRobotro(uint32_t id, uint32_t endOffset);

	int GetZeroForceRobotro(uint32_t id);
	int SetZeroForceRobotro(uint32_t id, uint32_t zeroForce);

	int GetZeroForcePosRobotro(uint32_t id);
	int SetZeroForcePosRobotro(uint32_t id, uint32_t zeroForcePos);

	int GetZeroToqRobotro(uint32_t id);
	int SetZeroToqRobotro(uint32_t id, uint32_t zeroToq);

	int GetZeroConfigRobotro(uint32_t id);
	int SetZeroConfigRobotro(uint32_t id, uint32_t zeroConfig);

	int GetFactoryDefaultRobotro(uint32_t id);
	int SetFactoryDefaultRobotro(uint32_t id, uint32_t factoryDefault);

	int GetConfigSaveRobotro(uint32_t id);
	int SetConfigSaveRobotro(uint32_t id, uint32_t configSave);

	int GetConfigLockRobotro(uint32_t id);
	int SetConfigLockRobotro(uint32_t id, uint32_t configLock);

	void PDO_MAP_Setting(uint32_t id);
	int Starting_Remote_Node(uint32_t id);
};

