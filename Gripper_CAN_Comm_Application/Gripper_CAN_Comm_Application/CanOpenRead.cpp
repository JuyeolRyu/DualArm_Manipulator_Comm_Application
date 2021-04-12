#include "StdAfx.h"
#include "CanOpenRead.h"

CanOpenRead::CanOpenRead(HWND m_hWnd, HANDLE ch)
{
	pdwNum= NULL;
	_hWnd = m_hWnd;
	_ch = ch;
	
	MOTORINFO _motor;

	for(int i=0; i<MOTORNUM; i++) {

		_motor.position[i] =0;
		_motor.current[i]=0;
		_motor.velocity[i]=0;
		_motor.status[i] =0;
		_motor.error[i] =0;
		_motor.operationMode[i] =0;

	}
}


CanOpenRead::~CanOpenRead(void)
{
}

void CanOpenRead::ReadFunc() 
{
	HRESULT hResult;

	motornum=RECIEVE_MSG_NUM;
	pdwNum= &motornum;

	CANMSG  rCanMsg[RECIEVE_MSG_NUM] = {};

	UINT8   i = 0;

	hResult = canChannelWaitRxEvent(_ch, 10);

	if ( hResult == VCI_OK) {
		canChannelReadMultipleMessages(_ch, 10, pdwNum, rCanMsg);
		
		for ( i = 0 ; i < motornum; i++ )	{
			rMsgProcessing(rCanMsg+i,&_motor);
		}		
	}
}



void CanOpenRead::rMsgProcessing(CANMSG *msg, MOTORINFO* motor)
{
	switch (msg->uMsgInfo.Bytes.bType)
	{
	case CAN_MSGTYPE_INFO:
		{
			switch (msg->abData[0])
			{
			case CAN_INFO_START:
				break;
			case CAN_INFO_STOP:
				break;
			case CAN_INFO_RESET:
				break;
			}
			break;
		}
	case CAN_MSGTYPE_ERROR:
		{
			switch (msg->abData[0])
			{
			case CAN_ERROR_STUFF:
				break;
			case CAN_ERROR_FORM:
				break;
			case CAN_ERROR_ACK :
				break;
			case CAN_ERROR_BIT:
				break;
			case CAN_ERROR_CRC:
				break;
			case CAN_ERROR_OTHER  :
				break;
			}
			break;
		}
	case CAN_MSGTYPE_DATA:
		{
			//////////////// Robotro ///////////////////
		::SendMessage(_hWnd,WM_RECEIVE_CAN_DATA,0, (LPARAM)msg);
			//if(msg->dwMsgId == 0x00)
			//{
			//	if (msg->abData[0]==105 )
			//	{
			//		//uint32_t rid = msg->dwMsgId - 0x00;
			//		uint32_t rid = msg->abData[1];
			//		//rid=rid;
			//		switch ( msg->abData[2]  )
			//		{
			//			case 0x10:			// GetActualPosition
			//			{
			//			//	memcpy(Rmotor->position + (rid-1), &(msg->abData[4]), 4);
			//				switch(msg->abData[3]) 
			//				{
			//					case 0x02:
			//						memcpy(motor->position + (rid-1), &(msg->abData[4]), 2);
			//						break;
			//					case 0x04:
			//						memcpy(motor->position + (rid-1), &(msg->abData[4]), 4);
			//						break;
			//				}
			//				break;
			//			}
			//		
			//			case 0x0C:		// GetActualVelocity
			//				{
			//					//memcpy(Rmotor->velocity + (rid-1), &(msg->abData[4]), 1);					
			//					switch(msg->abData[3]) 
			//				{
			//					case 0x02:
			//						memcpy(motor->velocity + (rid-1), &(msg->abData[4]), 2);
			//						break;
			//					case 0x04:
			//						memcpy(motor->velocity + (rid-1), &(msg->abData[4]), 4);
			//						break;
			//				}						
			//					break;
			//				}
			//			
			//			case 0x18:		// GetActualtorque??? GetActualcurrrent???
			//			{
			//				//memcpy(Rmotor->current + (rid-1), &(msg->abData[4]), 1);					
			//				switch(msg->abData[3]) 
			//				{
			//				case 0x02:
			//					memcpy(motor->current + (rid-1), &(msg->abData[4]), 2);
			//					break;
			//				case 0x04:
			//					memcpy(motor->current + (rid-1), &(msg->abData[4]), 4);
			//					break;
			//				}					
			//				break;
			//			}
			//		}
			//	}
			//}
		break;
		}
	}
}
