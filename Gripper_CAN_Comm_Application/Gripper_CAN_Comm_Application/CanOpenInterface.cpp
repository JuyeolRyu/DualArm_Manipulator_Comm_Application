
#include "stdafx.h"
#include "CanOpenInterface.h"

CanOpenInterface::CanOpenInterface(void)
{

}

CanOpenInterface::~CanOpenInterface(void)
{
}

int CanOpenInterface::WriteNMT(HANDLE ch, uint32_t id, uint8_t command, int len)
{
	uint8_t data[2] = { command, id };

	//motornum = MOTORNUM + 3;
	//pdwNum = &motornum;
	CANMSG sCanMsg;
	CANMSG rCanMsg[MOTORNUM + 3] = {};
	UINT8   i;

	sCanMsg.dwTime = 0;
	sCanMsg.dwMsgId = coNMT_Adress + id;    // CAN message identifier

	sCanMsg.uMsgInfo.Bytes.bType = CAN_MSGTYPE_DATA;
	sCanMsg.uMsgInfo.Bytes.bFlags = CAN_MAKE_MSGFLAGS(len, 0, 0, 0, 0);

	for (i = 0; i < sCanMsg.uMsgInfo.Bits.dlc; i++)
	{
		sCanMsg.abData[i] = data[i];
	}

	// write the CAN message into the transmit FIFO

	if (canChannelSendMessage(ch, 10, &sCanMsg) != VCI_OK) return -1;
	if (canChannelWaitTxEvent(ch, 10) != VCI_OK) return -1;

	//if (command = 0x81)
	//	//Sleep(100*MOTORNUM);

	//	if (canChannelWaitRxEvent(ch, 200) == VCI_OK)
	//		canChannelReadMultipleMessages(ch, 10, pdwNum, rCanMsg);

	return 0;
}

int CanOpenInterface::WriteSDO(HANDLE ch, uint32_t id, uint16_t index, uint8_t subIndex, uint8_t *object, int len)
{
	int8_t data[8] = { WRITE_REQUEST_MAX, (uint8_t)(index >> 0), (uint8_t)(index >> 8), (uint8_t)subIndex, 0x00, 0x00, 0x00, 0x00 };
	CANMSG  sCanMsg;
	UINT8   i;

	sCanMsg.dwTime = 0;
	sCanMsg.dwMsgId = coSDO_TX + id;    // CAN message identifier

	memcpy(&data[4], object, 4);


	sCanMsg.uMsgInfo.Bytes.bType = CAN_MSGTYPE_DATA;
	sCanMsg.uMsgInfo.Bytes.bFlags = CAN_MAKE_MSGFLAGS(len + 4, 0, 0, 0, 0);

	for (i = 0; i < sCanMsg.uMsgInfo.Bits.dlc; i++)
	{
		sCanMsg.abData[i] = data[i];
	}
	// write the CAN message into the transmit FIFO

	if (canChannelSendMessage(ch, 10, &sCanMsg) != VCI_OK) return -1;
	if (canChannelWaitTxEvent(ch, 10) != VCI_OK) return -1;
//	Sleep(2);

	return 0;
}
int CanOpenInterface::ReadSDO(HANDLE ch, uint32_t id, uint16_t index, uint8_t subIndex, int len)
{
	int8_t data[8] = { READ_REQUEST, (uint8_t)(index >> 0), (uint8_t)(index >> 8), (uint8_t)subIndex, 0, 0, 0, 0 };

	HRESULT hResult;
	CANMSG  sCanMsg;

	UINT8   i;
	sCanMsg.dwTime = 0;
	sCanMsg.dwMsgId = coSDO_TX + id;    // CAN message identifier

	sCanMsg.uMsgInfo.Bytes.bType = CAN_MSGTYPE_DATA;
	sCanMsg.uMsgInfo.Bytes.bFlags = CAN_MAKE_MSGFLAGS(8, 0, 0, 0, 0);

	for (i = 0; i < sCanMsg.uMsgInfo.Bits.dlc; i++)
	{
		sCanMsg.abData[i] = data[i];
	}
	// write the CAN message into the transmit FIFO
	canChannelSendMessage(ch, 10, &sCanMsg);

	return 0;
}

int CanOpenInterface::RPDO2_ELMO(HANDLE ch, uint32_t id, uint16_t index, uint8_t subIndex, uint8_t *object, int len)
{
	int8_t data[8] = { (uint8_t)(index >> 0), (uint8_t)(index >> 8), (uint8_t)subIndex, 0x00, 0x00, 0x00, 0x00, 0x00 };
	CANMSG  sCanMsg;
	UINT8   i;

	sCanMsg.dwTime = 0;
//	sCanMsg.dwMsgId = RPDO2_Adress + id;    // CAN message identifier
	sCanMsg.dwMsgId = RPDO2_Adress + id;    // CAN message identifier

	memcpy(&data[4], object, 4);


	sCanMsg.uMsgInfo.Bytes.bType = CAN_MSGTYPE_DATA;
	sCanMsg.uMsgInfo.Bytes.bFlags = CAN_MAKE_MSGFLAGS(len + 4, 0, 0, 0, 0);

	for (i = 0; i < sCanMsg.uMsgInfo.Bits.dlc; i++)
	{
		sCanMsg.abData[i] = data[i];
	}
	// write the CAN message into the transmit FIFO

	if (canChannelSendMessage(ch, 10, &sCanMsg) != VCI_OK) return -1;
	if (canChannelWaitTxEvent(ch, 10) != VCI_OK) return -1;
	//	Sleep(2);

	return 0;
}


int CanOpenInterface::WriteRobotro(HANDLE ch, uint32_t id,  uint16_t index, uint32_t object)
{
	return WriteRobotro(ch, id, index, (uint8_t*)&object, 4);
}

int CanOpenInterface::ReadRobotro(HANDLE ch, uint32_t id,  uint16_t index,int len)
{
	int8_t data[8] = {0x96, id, (uint8_t)(index>>0), (uint8_t)(index>>8), 0x00, 0x00, 0x00, 0x00};
	CANMSG  sCanMsg;
	
	UINT8   i;
	int16_t sum=0;
	
	PCANMSG pCanMsg=NULL;
	
	//HRESULT hResult;

	sCanMsg.dwTime   = 0;
	sCanMsg.dwMsgId  = id;    // CAN message identifier

	sCanMsg.uMsgInfo.Bytes.bType  = CAN_MSGTYPE_DATA;
//	sCanMsg.uMsgInfo.Bytes.bFlags = CAN_MAKE_MSGFLAGS(len, 0, 0, 0, 0);
	sCanMsg.uMsgInfo.Bytes.bFlags = CAN_MAKE_MSGFLAGS(len + 4, 0, 0, 0, 0);
	//sCanMsg.uMsgInfo.Bytes.bFlags = CAN_MAKE_MSGFLAGS(5,0,0,0,0);

	for (i = 0; i < sCanMsg.uMsgInfo.Bits.dlc; i++ )
	{
		sCanMsg.abData[i] = data[i];
		sum += data[i];
	}
	sCanMsg.abData[4] = (uint8_t)(sum-150);
	sCanMsg.abData[5] = 0;
	sCanMsg.abData[6] = 0;
	sCanMsg.abData[7] = 0;
	// write the CAN message into the transmit FIFO
	
	canChannelSendMessage(ch, 10, &sCanMsg) ;

	return 0;
}

int CanOpenInterface::WriteRobotro(HANDLE ch, uint32_t id,  uint16_t index, uint8_t *object, int len) {
	

	int8_t data[8] = {0x96, id, (uint8_t)(index>>0), (uint8_t)(index>>8), 0x00, 0x00, 0x00, 0x00};
	CANMSG  sCanMsg;
	UINT8   i;
	int16_t sum=0;;

	sCanMsg.dwTime   = 0;
	sCanMsg.dwMsgId = id; // 0;    // CAN message identifier

	sCanMsg.uMsgInfo.Bytes.bType  = CAN_MSGTYPE_DATA;
	sCanMsg.uMsgInfo.Bytes.bFlags = CAN_MAKE_MSGFLAGS(len+4,0,0,0,0);

	memcpy( &data[4] , object , 2);

	for (i = 0; i < sCanMsg.uMsgInfo.Bits.dlc; i++ )
	{
		sCanMsg.abData[i] = data[i];
		sum += data[i];
	}
		
	sCanMsg.abData[6] = (uint8_t)(sum-150);
	//
	//// write the CAN message into the transmit FIFO

	if ( canChannelSendMessage(ch, 10, &sCanMsg) != VCI_OK) return -1 ;
//	if ( canChannelWaitTxEvent(ch, 10) != VCI_OK) return -1 ;

	//if(data[3]==0x02){
	//	memcpy( &data[4] , object , 2);

	//	for (i = 0; i < sCanMsg.uMsgInfo.Bits.dlc; i++ )
	//	{
	//		sCanMsg.abData[i] = data[i];
	//		sum += data[i];
	//	}
	//	
	//	sCanMsg.abData[6] = (uint8_t)(sum-150);
	//	//
	//	//// write the CAN message into the transmit FIFO

	//	if ( canChannelSendMessage(ch, 10, &sCanMsg) != VCI_OK) return -1 ;
	//	if ( canChannelWaitTxEvent(ch, 10) != VCI_OK) return -1 ;
	//}

	//else if(data[3]==0x04){
	//	memcpy( &data[4] , object , 4);		
	//	
	//	for (i = 0; i < sCanMsg.uMsgInfo.Bits.dlc; i++ )
	//	{
	//		sCanMsg.abData[i] = data[i];
	//		sum += data[i];
	//	}

	//	if ( canChannelSendMessage(ch, 10, &sCanMsg) != VCI_OK) return -1 ;
	//	if ( canChannelWaitTxEvent(ch, 10) != VCI_OK) return -1 ;

	//	//for (i = 0; i < sCanMsg.uMsgInfo.Bits.dlc; i++ )
	//	for (i = 0; i < 8; i++ )
	//	{
	//		sCanMsg.abData[i] = 0;
	//	}
	//
	//	sCanMsg.abData[0] = (uint8_t)(sum-150);
	//	
	//	if ( canChannelSendMessage(ch, 10, &sCanMsg) != VCI_OK) return -1 ;
	//	if ( canChannelWaitTxEvent(ch, 10) != VCI_OK) return -1 ;
	//		
	//}
	return 0;
}

