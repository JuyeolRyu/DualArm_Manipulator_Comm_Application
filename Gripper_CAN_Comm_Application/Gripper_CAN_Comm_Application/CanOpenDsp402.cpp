#include "stdafx.h"
#include "CanOpenDsp402.h"


CanOpenDsp402::CanOpenDsp402(HANDLE ch, CanOpenInterface *canOpen)
{
	_ch = ch;
	_canOpen = canOpen;
}

CanOpenDsp402::~CanOpenDsp402(void)
{	
	_canOpen = NULL;
}

int CanOpenDsp402::ResetNode(uint32_t id)
{
	return _canOpen->WriteNMT(_ch, id, coReset_Node, 2);
}

int CanOpenDsp402::Starting_Remote_Node(uint32_t id)
{
	return _canOpen->WriteNMT(_ch, id, Start_Remote_Node, 2);
}

int CanOpenDsp402::SetControlWord(uint32_t id, uint16_t control)
{
	return _canOpen->WriteSDO(_ch, id, CAN_OPEN_CONTROL, (uint8_t *)&control, 2);
}

int CanOpenDsp402::GetControlWord(uint32_t id)
{
	return _canOpen->ReadSDO(_ch, id, CAN_OPEN_CONTROL, 4);
}

void CanOpenDsp402::PDO_MAP_Setting(uint32_t id)
{
	uint32_t data; 
	// RPDO 3번 설정
	data = 0xFF;
	_canOpen->WriteSDO(_ch, id, 0x1402, 0x02, (uint8_t *)&data, 0x08);  //3rd receive pdo communication parameter 1402.02h - data type : uint8_t
	data = 0x00;
	_canOpen->WriteSDO(_ch, id, CIA_301_RX_PDO_MAPPING3, (uint8_t *)&data, 0x08);	// only available in profile position mode
	data = 0x60600008;
	_canOpen->WriteSDO(_ch, id, CIA_301_RX_PDO_MAPPING3_OBJ1, (uint8_t *)&data, 0x08);	
	data = 0x01;
	_canOpen->WriteSDO(_ch, id, CIA_301_RX_PDO_MAPPING3, (uint8_t *)&data, 0x08);	


//		CANOPEN.ServiceDataObject.WriteObject(id, 0x1402, 0x02, 0xFF, 0x08);
//	CANOPEN.ServiceDataObject.WriteObject(id, 0x1602, 0x00, 0x00, 0x08);
//	CANOPEN.ServiceDataObject.WriteObject(id, 0x1602, 0x01, 0x60600008, 0x08); //Control Mode
//	CANOPEN.ServiceDataObject.WriteObject(id, 0x1602, 0x00, 0x01, 0x08);

	// TPDO 3번 설정 
	data = 0xFF;
	_canOpen->WriteSDO(_ch, id, 0x1802, 0x02, (uint8_t *)&data, 0x08);//third transmit pdo conmmunication parameter 1802.02h - data type : uint8_t
	data = 0x64;
	_canOpen->WriteSDO(_ch, id, 0x1802, 0x05, (uint8_t *)&data, 0x08);
	data = 0x00;
	_canOpen->WriteSDO(_ch, id, CIA_301_TX_PDO_MAPPING3, (uint8_t *)&data, 0x08);
	data = 0x60780010;
	_canOpen->WriteSDO(_ch, id, CIA_301_TX_PDO_MAPPING3_OBJ1, (uint8_t *)&data, 0x08);
	data = 0x1;
	_canOpen->WriteSDO(_ch, id, CIA_301_TX_PDO_MAPPING3, (uint8_t *)&data, 0x08);
	//	CANOPEN.ServiceDataObject.WriteObject(id, 0x1802, 0x02, 0xFF, 0x08);
	//CANOPEN.ServiceDataObject.WriteObject(id, 0x1802, 0x05, 0x64, 0x08); //F0
	//CANOPEN.ServiceDataObject.WriteObject(id, 0x1A02, 0x00, 0x00, 0x08);
	//CANOPEN.ServiceDataObject.WriteObject(id, 0x1A02, 0x01, 0x60780010, 0x08); //Current Actual value
	//CANOPEN.ServiceDataObject.WriteObject(id, 0x1A02, 0x00, 0x1, 0x08);

	// RPDO 4번 설정
	data = 0xFF;
	_canOpen->WriteSDO(_ch, id, 0x1403, 0x02, (uint8_t *)&data, 0x08);  //3rd receive pdo communication parameter 1402.02h - data type : uint8_t
	data = 0x00;
	_canOpen->WriteSDO(_ch, id, CIA_301_RX_PDO_MAPPING4, (uint8_t *)&data, 0x08);	// only available in profile position mode
	data = 0x607A0020;
	_canOpen->WriteSDO(_ch, id, CIA_301_RX_PDO_MAPPING4_OBJ1, (uint8_t *)&data, 0x08);
	data = 0x60810020;
	_canOpen->WriteSDO(_ch, id, CIA_301_RX_PDO_MAPPING4_OBJ2, (uint8_t *)&data, 0x08);
	data = 0x02;
	_canOpen->WriteSDO(_ch, id, CIA_301_RX_PDO_MAPPING4, (uint8_t *)&data, 0x08);
	//CANOPEN.ServiceDataObject.WriteObject(id, 0x1403, 0x02, 0xFF, 0x08);
	//CANOPEN.ServiceDataObject.WriteObject(id, 0x1603, 0x00, 0x00, 0x08);
	//CANOPEN.ServiceDataObject.WriteObject(id, 0x1603, 0x01, 0x607A0020, 0x08);//Target Position
	//CANOPEN.ServiceDataObject.WriteObject(id, 0x1603, 0x02, 0x60810020, 0x08);//Velocity
	//CANOPEN.ServiceDataObject.WriteObject(id, 0x1603, 0x00, 0x02, 0x08);

	// TPDO 4번 설정
	data = 0xFF;
	_canOpen->WriteSDO(_ch, id, 0x1803, 0x02, (uint8_t *)&data, 0x08);//third transmit pdo conmmunication parameter 1802.02h - data type : uint8_t
	data = 0x64;
	_canOpen->WriteSDO(_ch, id, 0x1803, 0x05, (uint8_t *)&data, 0x08);
	data = 0x00;
	_canOpen->WriteSDO(_ch, id, CIA_301_TX_PDO_MAPPING4, (uint8_t *)&data, 0x08);
	data = 0x60640020;
	_canOpen->WriteSDO(_ch, id, CIA_301_TX_PDO_MAPPING4_OBJ1, (uint8_t *)&data, 0x08);
	data = 0x606C0020;
	_canOpen->WriteSDO(_ch, id, CIA_301_TX_PDO_MAPPING4_OBJ1, (uint8_t *)&data, 0x08);
	data = 0x2;
	_canOpen->WriteSDO(_ch, id, CIA_301_TX_PDO_MAPPING4, (uint8_t *)&data, 0x08);
	//CANOPEN.ServiceDataObject.WriteObject(id, 0x1803, 0x02, 0xFF, 0x08);
	//CANOPEN.ServiceDataObject.WriteObject(id, 0x1803, 0x05, 0x64, 0x08); //F0
	//CANOPEN.ServiceDataObject.WriteObject(id, 0x1A03, 0x00, 0x0, 0x08);
	//CANOPEN.ServiceDataObject.WriteObject(id, 0x1A03, 0x01, 0x60640020, 0x08);
	//CANOPEN.ServiceDataObject.WriteObject(id, 0x1A03, 0x02, 0x606C0020, 0x08);
	//CANOPEN.ServiceDataObject.WriteObject(id, 0x1A03, 0x00, 0x2, 0x08);
}

int CanOpenDsp402::FaultReset(uint32_t id)
{
	return SetControlWord(id, CIA_402_CONTROL_FAULT_RESET);
}

int CanOpenDsp402::Shutdown(uint32_t id)
{
	return SetControlWord(id, CIA_402_CONTROL_SHUTDONW);
}

int CanOpenDsp402::SwitchOn(uint32_t id)
{
	return SetControlWord(id, CIA_402_CONTROL_SWITCH_ON);
}

int CanOpenDsp402::EnableOperation(uint32_t id)
{
	return SetControlWord(id, CIA_402_CONTROL_ENABLE_OPERATION);
}

int CanOpenDsp402::DisableOperation(uint32_t id)
{
	return SetControlWord(id, CIA_402_CONTROL_DISABLE_OPERATION);
}

int CanOpenDsp402::Halt(uint32_t id)
{
	return SetControlWord(id, CIA_402_CONTROL_HALT_BIT | CIA_402_CONTROL_ENABLE_OPERATION);
}

int CanOpenDsp402::SetModesOfOperation(uint32_t id, int8_t modesOfOperation)
{
	return _canOpen->WriteSDO(_ch, id, CAN_OPEN_MODES_OF_OPERATION, (uint8_t *)&modesOfOperation, 2);
}

int CanOpenDsp402::GetModesOfOperation(uint32_t id)
{
	return _canOpen->ReadSDO(_ch, id, CAN_OPEN_MODES_OF_OPERATION, 4);
}

int CanOpenDsp402::GetActualPosition(uint32_t id)
{
	return _canOpen->ReadSDO(_ch, id, CAN_OPEN_ACTUAL_POSITION, 4);
}

int CanOpenDsp402::GetActualVelocity(uint32_t id)
{
	return _canOpen->ReadSDO(_ch, id, CAN_OPEN_ACTUAL_VELOCITY, 4);
}

int CanOpenDsp402::GetActualTorque(uint32_t id)
{
	return _canOpen->ReadSDO(_ch, id, CIA_402_ACTUAL_TORQUE, 4);
}

int CanOpenDsp402::GetActualCurrent(uint32_t id)
{
	return _canOpen->ReadSDO(_ch, id, CAN_OPEN_ACTUAL_CURRENT, 4);
}

int CanOpenDsp402::GetRatedCurrent(uint32_t id)
{
	return _canOpen->ReadSDO(_ch, id, CIA_402_MOTOR_RATED_CURRENT, 4);
}

int CanOpenDsp402::SetTargetTorque(uint32_t id, int16_t targetTorque)
{
	return _canOpen->WriteSDO(_ch, id, CIA_402_TARGET_TORQUE, (uint8_t *)&targetTorque, 2);
}

int CanOpenDsp402::GetTargetTorque(uint32_t id)
{
	return _canOpen->ReadSDO(_ch, id, CIA_402_TARGET_TORQUE, 2);
}
int CanOpenDsp402::SetTargetPosition(uint32_t id, int32_t targetPosition)
{
	return _canOpen->WriteSDO(_ch, id, CAN_OPEN_TARGET_POSITION, (uint8_t *)&targetPosition, 4);
}

int CanOpenDsp402::SetProfileTargetPosition(uint32_t id, int32_t targetPosition, int mode)
{
	if (SetTargetPosition(id, targetPosition) < 0) {
		return -1;
	}
	Sleep(1);
	if (mode == 0) {
		//	Absolte/Immediately
		return SetControlWord(id, CIA_402_CONTROL_ENABLE_OPERATION | CIA_402_CONTROL_NEW_SETPOINT | CIA_402_CONTROL_CHANGE_SET_IMMEDIATELY);
	}
	else if (mode == 1) {
		//	Relative/Immediately
		return SetControlWord(id, CIA_402_CONTROL_ENABLE_OPERATION | CIA_402_CONTROL_NEW_SETPOINT | CIA_402_CONTROL_CHANGE_SET_IMMEDIATELY | CIA_402_CONTROL_RELATIVE_BIT);
	}
	else if (mode == 2) {
		//	Absolte
		return SetControlWord(id, CIA_402_CONTROL_ENABLE_OPERATION | CIA_402_CONTROL_NEW_SETPOINT);
	}
	else if (mode == 3) {
		//	Relative
		return SetControlWord(id, CIA_402_CONTROL_ENABLE_OPERATION | CIA_402_CONTROL_NEW_SETPOINT | CIA_402_CONTROL_RELATIVE_BIT);
	}
	else {
		return -1;
	}

	return 0;
}

int CanOpenDsp402::GetTargetPosition(uint32_t id)
{
	return _canOpen->ReadSDO(_ch, id, CAN_OPEN_TARGET_POSITION, 4);
}

int CanOpenDsp402::SetProfileVelocity(uint32_t id, uint32_t profileVelocity)
{
	return _canOpen->WriteSDO(_ch, id, CIA_402_PROFILE_VELOCITY, (uint8_t *)&profileVelocity, 4);
}

int CanOpenDsp402::GetProfileVelocity(uint32_t id)
{
	return _canOpen->ReadSDO(_ch, id, CIA_402_PROFILE_VELOCITY, 4);
}

int CanOpenDsp402::SetMotionProfileType(uint32_t id, int16_t motionProfileType)
{
	return _canOpen->WriteSDO(_ch, id, CIA_402_MOTION_PROFILE_TYPE, (uint8_t *)&motionProfileType, 2);
}

int CanOpenDsp402::GetMotionProfileType(uint32_t id)
{
	return _canOpen->ReadSDO(_ch, id, CIA_402_MOTION_PROFILE_TYPE, 2);
}

int CanOpenDsp402::SetTargetVelocity(uint32_t id, int32_t targetVelocity)
{

	//if (_operationMode != CIA_402_PROFILE_VELOCITY_MODE) {
	//	if (SetModesOfOperation(id, CIA_402_PROFILE_VELOCITY_MODE) < 0)	return -1;
	//	_operationMode = CIA_402_PROFILE_VELOCITY_MODE;
	//}

	return _canOpen->WriteSDO(_ch, id, CAN_OPEN_TARGET_VELOCITY, (uint8_t *)&targetVelocity, 4);
}

int CanOpenDsp402::GetTargetVelocity(uint32_t id)
{
	return _canOpen->ReadSDO(_ch, id, CAN_OPEN_TARGET_VELOCITY, 4);
}

int  CanOpenDsp402::HomeActivation_ELMO(uint32_t id, int8_t activationFlag)
{
	//hm[1]=1, H=0x48, M =0x4d , activationFlag = 0 or 1
	uint16_t index = 0x4d48;
//	uint16_t index = 0x6d68;
	uint8_t subIndex = 0x01;
	return _canOpen->RPDO2_ELMO(_ch, id, index, subIndex, (uint8_t *)&activationFlag, 4);
}

int CanOpenDsp402::HomeEventDEF_ELMO(uint32_t id, int8_t eventDescription)
{
	//hm[1]=1, H=0x48, M =0x4d h=0x68,m=6d, eventDescription = 0 ~ 28, 0 - immediately, 1-home switch, 5-fls switch, 7-rls switch
	uint16_t index = 0x4d48;
//	uint16_t index = 0x6d68;
	uint8_t subIndex = 0x03;
	return _canOpen->RPDO2_ELMO(_ch, id, index, subIndex, (uint8_t *)&eventDescription, 4);
}
//
//
//void TransmitSetHomingProcedure(int id, int subidx, int act)
//{
//	char data[8];
//	data[0] = 0x48;			data[1] = 0x4d;				data[2] = subidx & 0xff;		data[3] = 0x00;
//	data[4] = act & 0xff;		data[5] = 0x00;				data[6] = 0x00;				data[7] = 0x00;
//	TransmitData8(0x300 + id, 8, data);
//}
//
//void TransmitHomingProcedureSetValue(int id, int subidx, int val)
//{
//	char data[8];
//	data[0] = 0x48;			data[1] = 0x4d;				data[2] = subidx & 0xff;		data[3] = 0x00;
//	data[4] = val & 0xff;		data[5] = (val >> 8) & 0xff;		data[6] = (val >> 16) & 0xff;		data[7] = (val >> 24) & 0xff;
//	TransmitData8(0x300 + id, 8, data);
//}
///////////////////////////// Robotro //////////////////////////


int CanOpenDsp402::SetControlRobotro(uint32_t id, uint32_t control)
{
	return _canOpen->WriteRobotro(_ch, id, CAN_ROBOTRO_CONTROL, control);
}

int CanOpenDsp402::ServoOFF(uint32_t id) 
{
	return SetControlRobotro(id, SERVO_OFF);
}
int CanOpenDsp402::ServoOn(uint32_t id)
{
	return SetControlRobotro(id, SERVO_ON);
}
int CanOpenDsp402::Stop(uint32_t id)
{
	return SetControlRobotro(id, STOP);
}

int CanOpenDsp402::GetStatusRobotro(uint32_t id)
{
	return _canOpen->ReadRobotro(_ch, id, CAN_ROBOTRO_STATUS, 4);
}

int CanOpenDsp402::GetVelocityRobotro(uint32_t id) 
{
	return _canOpen->ReadRobotro(_ch, id, CAN_ROBOTRO_ACTUAL_VELOCITY, 4);
}

int CanOpenDsp402::GetPositionRobotro(uint32_t id) 
{
	return _canOpen->ReadRobotro(_ch, id, CAN_ROBOTRO_ACTUAL_POSITION, 4);
}
	
int CanOpenDsp402::GetCurrentRobotro(uint32_t id) 
{
	return _canOpen->ReadRobotro(_ch, id, CAN_ROBOTRO_ACTUAL_CURRENT, 4);
}

int CanOpenDsp402::GetVoltageRobotro(uint32_t id)
{
	return _canOpen->ReadRobotro(_ch, id, CAN_ROBOTRO_VOLTAGE, 4);
}

int CanOpenDsp402::GetInternalTempRobotro(uint32_t id)
{
	return _canOpen->ReadRobotro(_ch, id, CAN_ROBOTRO_INTERNAL_TEMP, 4);
}

int CanOpenDsp402::GetMotorTempRobotro(uint32_t id)
{
	return _canOpen->ReadRobotro(_ch, id, CAN_ROBOTRO_MOTOR_TEMP, 4);
}

#ifdef JUNISERVO_R8
int CanOpenDsp402::GetZeroFlagRobotro(uint32_t id)
{
	return _canOpen->ReadRobotro(_ch, id, CAN_ROBOTRO_ZEROR_FLAG, 4);
}
#endif // JUNISERVO_R8

int CanOpenDsp402::GetCmdVelRobotro(uint32_t  id)
{
	return _canOpen->ReadRobotro(_ch, id, CAN_ROBOTRO_CMD_VEL, 4);
}
int CanOpenDsp402::SetCmdVelRobotro(uint32_t id, uint32_t cmdVel)
{
	return _canOpen->WriteRobotro(_ch, id, CAN_ROBOTRO_CMD_VEL + 0x0200, cmdVel);
}

int CanOpenDsp402::GetCmdToqRobotro(uint32_t id)
{
	return _canOpen->ReadRobotro(_ch, id, CAN_ROBOTRO_CMD_TOQ, 4);
}
int CanOpenDsp402::SetCmdToqRobotro(uint32_t id, uint32_t cmdToq)
{
	return _canOpen->WriteRobotro(_ch, id, CAN_ROBOTRO_CMD_TOQ + 0x0200, cmdToq);
}

int CanOpenDsp402::GetCmdPosRobotro(uint32_t id)
{
	return _canOpen->ReadRobotro(_ch, id, CAN_ROBOTRO_CMD_POS, 4);
}
int CanOpenDsp402::SetCmdPosRobotro(uint32_t id, uint32_t cmdPos)
{
	return _canOpen->WriteRobotro(_ch, id, CAN_ROBOTRO_CMD_POS + 0x0200, cmdPos);
}

int CanOpenDsp402::GetCmd360Robotro(uint32_t id)
{
	return _canOpen->ReadRobotro(_ch, id, CAN_ROBOTRO_CMD_360, 4);
}

int CanOpenDsp402::GetCmdRelPosRobotro(uint32_t id)
{
	return _canOpen->ReadRobotro(_ch, id, CAN_ROBOTRO_CMD_REL_POS, 4);
}

int CanOpenDsp402::GetIDRobotro(uint32_t id)
{
	return _canOpen->ReadRobotro(_ch, id, CAN_ROBOTRO_ID, 4);
}
int CanOpenDsp402::SetIdRobotro(uint32_t id, uint32_t configId)
{
	return _canOpen->WriteRobotro(_ch, id, CAN_ROBOTRO_ID + 0x0200, configId);
}

int CanOpenDsp402::GetBaudRateRobotro(uint32_t id)
{
	return _canOpen->ReadRobotro(_ch, id, CAN_ROBOTRO_BAUD_RATE, 4);
}
int CanOpenDsp402::SetBaudRateRobotro(uint32_t id, uint32_t baudRate)
{
	return _canOpen->WriteRobotro(_ch, id, CAN_ROBOTRO_BAUD_RATE + 0x0200, baudRate);
}

int CanOpenDsp402::GetSignalModeRobotro(uint32_t id)
{
	return _canOpen->ReadRobotro(_ch, id, CAN_ROBOTRO_SIGNAL_MODE, 4);
}

int CanOpenDsp402::GetSimpleReturnDelay(uint32_t id)
{
	return _canOpen->ReadRobotro(_ch, id, CAN_ROBOTRO_SIMPLE_RETURN_DELAY, 4);
}
int CanOpenDsp402::SetSimpleReturnDelayRobotro(uint32_t id, uint32_t simpleReturnDelay)
{
	return _canOpen->WriteRobotro(_ch, id, CAN_ROBOTRO_SIMPLE_RETURN_DELAY + 0x0200, simpleReturnDelay);
}

int CanOpenDsp402::GetNormalReturnDelay(uint32_t id)
{
	return _canOpen->ReadRobotro(_ch, id, CAN_ROBOTRO_NORMAL_RETURN_DELAY, 4);
}
int CanOpenDsp402::SetNormalReturnDelayRobotro(uint32_t id, uint32_t normalReturnDelay)
{
	return _canOpen->WriteRobotro(_ch, id, CAN_ROBOTRO_NORMAL_RETURN_DELAY + 0x0200, normalReturnDelay);
}

int CanOpenDsp402::GetID2Robotro(uint32_t id)
{
	return _canOpen->ReadRobotro(_ch, id, CAN_ROBOTRO_ID2, 4);
}

int CanOpenDsp402::SetId2Robotro(uint32_t id, uint32_t configId2)
{
	return _canOpen->WriteRobotro(_ch, id, CAN_ROBOTRO_ID2 + 0x0200, configId2);
}

int CanOpenDsp402::GetPowConfigRobotro(uint32_t id)
{
	return _canOpen->ReadRobotro(_ch, id, CAN_ROBOTRO_POW_CONFIG, 4);
}

int CanOpenDsp402::GetEmgStopRobotro(uint32_t id)
{
	return _canOpen->ReadRobotro(_ch, id, CAN_ROBOTRO_EMG_STOP, 4);
}
int CanOpenDsp402::SetEmgStopRobotro(uint32_t id, uint32_t BitsSet)
{
	return _canOpen->WriteRobotro(_ch, id, CAN_ROBOTRO_EMG_STOP + 0x0200, BitsSet);
}

int CanOpenDsp402::GetActionModeRobotro(uint32_t id)
{
	return _canOpen->ReadRobotro(_ch, id, CAN_ROBOTRO_ACTION_MODE, 4);
}
int CanOpenDsp402::SetActionModeRobotro(uint32_t id, uint32_t BitsSet)
{
	return _canOpen->WriteRobotro(_ch, id, CAN_ROBOTRO_ACTION_MODE + 0x0200, BitsSet);
}

int CanOpenDsp402::GetSlopeRobotro(uint32_t id)
{
	return _canOpen->ReadRobotro(_ch, id, CAN_ROBOTRO_SLOPE, 4);
}
int CanOpenDsp402::SetPosSlopeRobotro(uint32_t id, uint32_t posSlope)
{
	return _canOpen->WriteRobotro(_ch, id, CAN_ROBOTRO_SLOPE + 0x0200, posSlope);
}

int CanOpenDsp402::GetDeadBandRobotro(uint32_t id)
{
	return _canOpen->ReadRobotro(_ch, id, CAN_ROBOTRO_DEADBAND, 4);
}
int CanOpenDsp402::SetDeadBandRobotro(uint32_t id, uint32_t deadBand)
{
	return _canOpen->WriteRobotro(_ch, id, CAN_ROBOTRO_DEADBAND + 0x0200, deadBand);
}

int CanOpenDsp402::GetPosMaxRobotro(uint32_t id)
{
	return _canOpen->ReadRobotro(_ch, id, CAN_ROBOTRO_POS_MAX, 4);
}
int CanOpenDsp402::SetPosMaxRobotro(uint32_t id, uint32_t posMax)
{
	return _canOpen->WriteRobotro(_ch, id, CAN_ROBOTRO_POS_MAX + 0x0200, posMax);
}

int CanOpenDsp402::GetPosMinRobotro(uint32_t id)
{
	return _canOpen->ReadRobotro(_ch, id, CAN_ROBOTRO_POS_MIN, 4);
}
int CanOpenDsp402::SetPosMinRobotro(uint32_t id, uint32_t posMin)
{
	return _canOpen->WriteRobotro(_ch, id, CAN_ROBOTRO_POS_MIN + 0x0200, posMin);
}

int CanOpenDsp402::GetVelMaxRobotro(uint32_t id)
{
	return _canOpen->ReadRobotro(_ch, id, CAN_ROBOTRO_VEL_MAX, 4);
}
int CanOpenDsp402::SetVelMaxRobotro(uint32_t id, uint32_t velMax)
{
	return _canOpen->WriteRobotro(_ch, id, CAN_ROBOTRO_VEL_MAX + 0x0200, velMax);
}


int CanOpenDsp402::GetToqMaxRobotro(uint32_t id)
{
	return _canOpen->ReadRobotro(_ch, id, CAN_ROBOTRO_TOQ_MAX, 4);
}
int CanOpenDsp402::SetToqMaxRobotro(uint32_t id, uint32_t toqMax)
{
	return _canOpen->WriteRobotro(_ch, id, CAN_ROBOTRO_TOQ_MAX + 0x0200, toqMax);
}

int CanOpenDsp402::GetVoltageMaxRobotro(uint32_t id)
{
	return _canOpen->ReadRobotro(_ch, id, CAN_ROBOTRO_VOLTAGE_MAX, 4);
}
int CanOpenDsp402::SetVoltageMaxRobotro(uint32_t id, uint32_t voltageMin)
{
	return _canOpen->WriteRobotro(_ch, id, CAN_ROBOTRO_VOLTAGE_MAX + 0x0200, voltageMin);
}

int CanOpenDsp402::GetVoltageMinRobotro(uint32_t id)
{
	return _canOpen->ReadRobotro(_ch, id, CAN_ROBOTRO_VOLTAGE_MIN, 4);
}
int CanOpenDsp402::SetVoltageMinRobotro(uint32_t id, uint32_t voltageMin)
{
	return _canOpen->WriteRobotro(_ch, id, CAN_ROBOTRO_VOLTAGE_MIN + 0x0200, voltageMin);
}

int CanOpenDsp402::GetTempMaxRobotro(uint32_t id)
{
	return _canOpen->ReadRobotro(_ch, id, CAN_ROBOTRO_TEMP_MAX, 4);
}
int CanOpenDsp402::SetTempMaxRobotro(uint32_t id, uint32_t tempMax)
{
	return _canOpen->WriteRobotro(_ch, id, CAN_ROBOTRO_TEMP_MAX + 0x0200, tempMax);
}

int CanOpenDsp402::GetEncConfigRobotro(uint32_t id)
{
	return _canOpen->ReadRobotro(_ch, id, CAN_ROBOTRO_ENC_CONFIG, 4);
}
int CanOpenDsp402::SetEncConfigRobotro(uint32_t id, uint32_t encConfig)
{
	return _canOpen->WriteRobotro(_ch, id, CAN_ROBOTRO_ENC_CONFIG + 0x0200, encConfig);
}

int CanOpenDsp402::GetEncOffsetRobotro(uint32_t id)
{
	return _canOpen->ReadRobotro(_ch, id, CAN_ROBOTRO_ENC_OFFSET, 4);
}
int CanOpenDsp402::SetEncOffsetRobotro(uint32_t id, uint32_t endOffset)
{
	return _canOpen->WriteRobotro(_ch, id, CAN_ROBOTRO_ENC_OFFSET + 0x0200, endOffset);
}

int CanOpenDsp402::GetZeroForceRobotro(uint32_t id)
{
	return _canOpen->ReadRobotro(_ch, id, CAN_ROBOTRO_ZERO_FORCE, 4);
}
int CanOpenDsp402::SetZeroForceRobotro(uint32_t id, uint32_t zeroForce)
{
	return _canOpen->WriteRobotro(_ch, id, CAN_ROBOTRO_ZERO_FORCE + 0x0200, zeroForce);
}

int CanOpenDsp402::GetZeroForcePosRobotro(uint32_t id)
{
	return _canOpen->ReadRobotro(_ch, id, CAN_ROBOTRO_ZERO_FORCE_POS, 4);
}
int CanOpenDsp402::SetZeroForcePosRobotro(uint32_t id, uint32_t zeroForcePos)
{
	return _canOpen->WriteRobotro(_ch, id, CAN_ROBOTRO_ZERO_FORCE_POS + 0x0200, zeroForcePos);
}

int CanOpenDsp402::GetZeroToqRobotro(uint32_t id)
{
	return _canOpen->ReadRobotro(_ch, id, CAN_ROBOTRO_ZERO_TOQ, 4);
}
int CanOpenDsp402::SetZeroToqRobotro(uint32_t id, uint32_t zeroToq)
{
	return _canOpen->WriteRobotro(_ch, id, CAN_ROBOTRO_ZERO_TOQ + 0x0200, zeroToq);
}

int CanOpenDsp402::GetZeroConfigRobotro(uint32_t id)
{
	return _canOpen->ReadRobotro(_ch, id, CAN_ROBOTRO_ZERO_CONFIG, 4);
}
int CanOpenDsp402::SetZeroConfigRobotro(uint32_t id, uint32_t zeroConfig)
{
	return _canOpen->WriteRobotro(_ch, id, CAN_ROBOTRO_ZERO_CONFIG + 0x0200, zeroConfig);
}

int CanOpenDsp402::GetFactoryDefaultRobotro(uint32_t id)
{
	return _canOpen->ReadRobotro(_ch, id, CAN_ROBOTRO_FACTORY_DEFAULT, 4);
}
int CanOpenDsp402::SetFactoryDefaultRobotro(uint32_t id, uint32_t factoryDefault)
{
	return _canOpen->WriteRobotro(_ch, id, CAN_ROBOTRO_FACTORY_DEFAULT + 0x0200, factoryDefault);
}

int CanOpenDsp402::GetConfigSaveRobotro(uint32_t id)
{
	return _canOpen->ReadRobotro(_ch, id, CAN_ROBOTRO_CONFIG_SAVE, 4);
}
int CanOpenDsp402::SetConfigSaveRobotro(uint32_t id, uint32_t configSave)
{
	return _canOpen->WriteRobotro(_ch, id, CAN_ROBOTRO_CONFIG_SAVE + 0x0200, configSave);
}

int CanOpenDsp402::GetConfigLockRobotro(uint32_t id)
{
	return _canOpen->ReadRobotro(_ch, id, CAN_ROBOTRO_CONFIG_LOCK, 4);
}
int CanOpenDsp402::SetConfigLockRobotro(uint32_t id, uint32_t configLock)
{
	return _canOpen->WriteRobotro(_ch, id, CAN_ROBOTRO_CONFIG_LOCK + 0x0200, configLock);
}

int CanOpenDsp402::Homing(uint32_t id, uint32_t control)
{
	return _canOpen->WriteRobotro(_ch, id, CAN_ROBOTRO_HOMING, control);
}
		
int CanOpenDsp402::GoPositionRobotro(uint32_t id, uint32_t pos)
{
	return _canOpen->WriteRobotro(_ch, id, CAN_ROBOTRO_GO_POSISION, pos);
}
	
int CanOpenDsp402::ZogCCWRobotro(uint32_t id, uint32_t direction)
{
	return _canOpen->WriteRobotro(_ch, id, CAN_ROBOTRO_ZOG, direction);
}
		
int CanOpenDsp402::ZogCWRobotro(uint32_t id, uint32_t direction)
{
	return _canOpen->WriteRobotro(_ch, id, CAN_ROBOTRO_ZOG, direction);
}

void CanOpenDsp402::MotorInitialize(uint32_t id)
{
	FaultReset(id);
	Sleep(1);
	Shutdown(id);
	Sleep(1);
	SwitchOn(id);
	Sleep(1);
	EnableOperation(id);
	Sleep(1);
}
