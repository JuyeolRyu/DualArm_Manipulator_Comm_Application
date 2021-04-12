#pragma once

// 로보트로 명령어 0(0x00)~202(0xCA), 앞에 붙는 00 -> 2바이트 읽기, 01 -> 4바이트 읽기,
//												02 -> 2바이트 쓰기, 04 -> 4바이트 쓰기
#define JUNISERVO_R7
//#define JUNISERVO_R8

#define CAN_ROBOTRO_RETURNHEADER							0x0069
#define	CAN_ROBOTRO_CONTROL									0x0250
	#define	STOP									0x0008
	#define	SERVO_ON								0x0001
	#define	SERVO_OFF								0x0000

#define CAN_ROBOTRO_HOMING									0x026C
	#define	START									0x0001

#define CAN_ROBOTRO_STATUS									0x000A
#ifdef JUNISERVO_R7
/* STATUS */
	#define CAN_ROBOTRO_ACTUAL_POSITION							0x000C
	#define CAN_ROBOTRO_ACTUAL_VELOCITY							0x000E
	#define CAN_ROBOTRO_ACTUAL_CURRENT							0x0010
	#define CAN_ROBOTRO_VOLTAGE									0x0012 //voltage_addr
	#define CAN_ROBOTRO_INTERNAL_TEMP							0x0014 //internal_temp_addr 22
	#define CAN_ROBOTRO_MOTOR_TEMP								0x0016 //motor_temp_addr

/* ACTION */
	#define CAN_ROBOTRO_CMD_POS									0x001E // 2바이트 읽기, 쓰기에도 사용 -> 확인필요 180616 setting 함수에서 +0x0200을 해준다.
	#define CAN_ROBOTRO_CMD_VEL									0x0020  
	#define CAN_ROBOTRO_CMD_TOQ									0x0022
	#define CAN_ROBOTRO_CMD_360									0x0024
	#define CAN_ROBOTRO_CMD_REL_POS								0x0026  //38
	#define CAN_ROBOTRO_CMD_CONTINUE_POS						0X002C  //44    /* 44  컨트롤러에서 연속적인 새로운 위치 설정(절대값 사용) */
	#define CAN_ROBOTRO_CMD_CONTINUE_REL_POS					0X002E  //46	/* 48  컨트롤러에서 연속적인 새로운 위치 설정(상대값) */
/* CONFIG COMMUNICATION */
	#define CAN_ROBOTRO_ID										0X0032  // 50         
	#define CAN_ROBOTRO_BAUD_RATE								0X0034  // 52      
	#define CAN_ROBOTRO_SIGNAL_MODE								0x0036 //54
	#define CAN_ROBOTRO_SIMPLE_RETURN_DELAY						0x0038 //56
	#define CAN_ROBOTRO_NORMAL_RETURN_DELAY						0x003A //58
	#define CAN_ROBOTRO_ID2										0X003C // 60  reserved   
//	#define CAN_ROBOTRO_RESERVED_60								0X003C // 60     
/* CONFIG ACTION */
	#define CAN_ROBOTRO_POW_CONFIG								0X0046 // 70     
	#define CAN_ROBOTRO_EMG_STOP								0x0048 //72
	#define CAN_ROBOTRO_ACTION_MODE								0x004A //74
	#define CAN_ROBOTRO_SLOPE									0X004C // 76     
	#define CAN_ROBOTRO_DEADBAND								0X004E // 78     
	#define CAN_ROBOTRO_POS_MAX									0X0050 // 80     
	#define CAN_ROBOTRO_POS_MIN									0X0052 // 82     
	#define CAN_ROBOTRO_VEL_MAX									0X0054 // 84     
	#define CAN_ROBOTRO_TOQ_MAX									0X0056 // 86     
	#define CAN_ROBOTRO_VOLTAGE_MAX								0X0058 // 88     
	#define CAN_ROBOTRO_VOLTAGE_MIN								0X005A // 90     
	#define CAN_ROBOTRO_TEMP_MAX								0X005C // 92     
	#define CAN_ROBOTRO_ENC_CONFIG								0X005E // 94     
	#define CAN_ROBOTRO_ENC_OFFSET								0X0060 // 96     
	#define CAN_ROBOTRO_ZERO_FORCE								0X0062 // 98    reserved 
	#define CAN_ROBOTRO_ZERO_FORCE_POS							0X0064 // 100   reserved
	#define CAN_ROBOTRO_ZERO_TOQ								0X0066 // 102   reserved  
	#define CAN_ROBOTRO_ZERO_CONFIG								0X0068 // 104   reserved  
/* CONFIG SETTING */	
	#define CAN_ROBOTRO_FACTORY_DEFAULT							0X006E // 110     
	#define CAN_ROBOTRO_CONFIG_SAVE								0X0070 // 112     
	#define CAN_ROBOTRO_CONFIG_LOCK								0X0072 // 114     


#else JUNISERVO_R8
/* STATUS */
	#define CAN_ROBOTRO_ACTUAL_POSITION							0x0010
	#define CAN_ROBOTRO_ACTUAL_VELOCITY							0x000C
	#define CAN_ROBOTRO_ACTUAL_CURRENT							0x000E
	#define CAN_ROBOTRO_VOLTAGE									0x0014 //voltage_addr
	#define CAN_ROBOTRO_INTERNAL_TEMP							0x0016 //internal_temp_addr 22
	#define CAN_ROBOTRO_MOTOR_TEMP								0x0018 //motor_temp_addr
	#define CAN_ROBOTRO_ZEROR_FLAG								0x001A //zero_flag_addr
/* ACTION */
	#define CAN_ROBOTRO_CMD_VEL									0x001E  //30 2바이트 읽기
	#define CAN_ROBOTRO_CMD_TOQ									0x0020  //32
	#define CAN_ROBOTRO_CMD_POS									0x0022  //34
	#define CAN_ROBOTRO_CMD_POS_EXT								0x0024  //36
	#define CAN_ROBOTRO_CMD_360									0x0026	//38
	#define CAN_ROBOTRO_CMD_REL_POS								0x0028  //40
	#define CAN_ROBOTRO_CMD_CONTINUE_POS						0X002C  // 44    /* 44  컨트롤러에서 연속적인 새로운 위치 설정(절대값 사용) */
	#define CAN_ROBOTRO_CMD_CONTINUE_POS_EXT					0X002E  //46	/* 46  컨트롤러에서 연속적인 새로운 위치 설정(절대값 사용) */
	#define CAN_ROBOTRO_CMD_CONTINUE_REL_POS					0X0030  //48	/* 48  컨트롤러에서 연속적인 새로운 위치 설정(상대값) */
	#define CAN_ROBOTRO_CMD_CONTINUE_REL_POS_EXT				0X0032  //50 /* 50  컨트롤러에서 연속적인 새로운 위치 설정(상대값) */
	#define CAN_ROBOTRO_CMD_STOP								0X0036  //54				 /* 54  100 - 감속 정지, 200 - 즉시정지 */
/* CONFIG COMMUNICATION */
	#define CAN_ROBOTRO_ID										0X003C  // 60      
	#define CAN_ROBOTRO_BAUD_RATE								0X003E  // 62
	#define CAN_ROBOTRO_SIGNAL_MODE								0x0040 //64
	#define CAN_ROBOTRO_SIMPLE_RETURN_DELAY						0x0042 //66
	#define CAN_ROBOTRO_NORMAL_RETURN_DELAY						0x0044 //68
	#define CAN_ROBOTRO_ID2										0X0046 // 70        
	#define CAN_ROBOTRO_ID_NOW									0X00D0 // 208        
/* CONFIG ACTION */
	#define CAN_ROBOTRO_POW_CONFIG								0X0050 // 80     
	#define CAN_ROBOTRO_EMG_STOP								0x0052 //82
	#define CAN_ROBOTRO_ACTION_MODE								0x0054 //84
	#define CAN_ROBOTRO_SLOPE									0X0056 // 86     
	#define CAN_ROBOTRO_DEADBAND								0X0058 // 88     
	#define CAN_ROBOTRO_POS_MAX									0X005A // 90     
	#define CAN_ROBOTRO_POS_MIN									0X005C // 92     
	#define CAN_ROBOTRO_VEL_MAX									0X005E // 94     
	#define CAN_ROBOTRO_TOQ_MAX									0X0060 // 96     
	#define CAN_ROBOTRO_VOLTAGE_MAX								0X0062 // 98     
	#define CAN_ROBOTRO_VOLTAGE_MIN								0X0064 // 100     
	#define CAN_ROBOTRO_TEMP_MAX								0X0066 // 102     
	#define CAN_ROBOTRO_ENC_CONFIG								0X0068 // 104     
	#define CAN_ROBOTRO_ENC_OFFSET								0X006A // 106     
	#define CAN_ROBOTRO_ZERO_FORCE								0X006C // 108     
	#define CAN_ROBOTRO_ZERO_FORCE_POS							0X006E // 110     
	#define CAN_ROBOTRO_ZERO_TOQ								0X0070 // 112     
	#define CAN_ROBOTRO_ZERO_CONFIG								0X0072 // 114     
/* CONFIG SETTING */
	#define CAN_ROBOTRO_FACTORY_DEFAULT							0X0078 // 120     
	#define CAN_ROBOTRO_CONFIG_SAVE								0X007A // 122     
	#define CAN_ROBOTRO_CONFIG_LOCK								0X007C // 124    
#endif

#define	CAN_ROBOTRO_GO_POSISION								0x0422 //0x0222 170814수정
#define	CAN_ROBOTRO_SET_TORQUE								0x0260
#define	CAN_ROBOTRO_ZOG										0x0226

#define	CAN_OPEN_STATUS										0x6041,	0x00	//	Unsigned 16bit,	RO
	#define	CAN_OPEN_READY_TO_SWITCH_ON							0x0001
	#define	CAN_OPEN_SWITCHED_ON								0x0002
	#define	CAN_OPEN_OPERATION_ENABLE							0x0004
	#define	CAN_OPEN_FAULT										0x0008
	#define	CAN_OPEN_VOLTAGE_ENABLED							0x0010
	#define	CAN_OPEN_IS_QUICK_STOP								0x0020
	#define	CAN_OPEN_SWITCH_ON_DISABLE							0x0040
	#define	CAN_OPEN_WARNING									0x0080
	#define	CAN_OPEN_OFFSET_CURRENT_MEASURED					0x0100
	#define	CAN_OPEN_TARGET_REACHED								0x0200
	#define	CAN_OPEN_REFRESH_CYCLE_OF_POWER_STAGE				0x4000
	#define	CAN_OPEN_POSITION_REFERECED_TO_HOME_POSITION		0x8000

	#define	CAN_OPEN_STATUS_BOOTUP								0x0000			//	Bootup
	#define	CAN_OPEN_STATUS_NOT_READY_TO_SWITCH_ON				0x0100			//	The current offset will be measured. The drive function is disabled.
	#define	CAN_OPEN_STATUS_SWITCH_ON_DISABLED					0x0140			//	The drive initialization is complete. The driver parameters may be changed. The driver function is disabled.
	#define	CAN_OPEN_STATUS_READY_TO_SWITCH_ON					0x0121			//	The drive parameters may be changed. The drive function is disabled.
	#define	CAN_OPEN_STATUS_SWITCH_ON							0x0123			//	The drive function is disabled.
	#define	CAN_OPEN_STATUS_REFRESH								0x4123			//	Refresh power stage.
	#define	CAN_OPEN_STATUS_MEASURE_INIT						0x4133			//	The power is applied to motor. The motor resistance or the communtation delay is measured.
	#define	CAN_OPEN_STATUS_OPERATION_ENABLE					0x0137			//	No faults have been detected. The drive function is enabled and power is applied to motor.
	#define	CAN_OPEN_STATUS_QUICK_STOP_ACTIVE					0x0117			//	The quick stop function is being executed. The drive function is enabled and power is applied to motor.
	#define	CAN_OPEN_STATUS_FAULT_REACTION_ACTIVE_DISABLED		0x010F			//	A fault has occurred in the drive. The drive function is disabled.
	#define	CAN_OPEN_STATUS_FAULT_REACTION_ACTIVE_ENABLED		0x011F			//	A fault has occurred in the drive. The quick stop function is being executed. The drive function is enabled and power is applied to motor
	#define	CAN_OPEN_STATUS_FAULT								0x0108			//	A fault has occurred in the drive. The drive parameters may be changed. The drive function is disabled.


#define pos_lock_time_addr 168                  /* 168  Position Lock이 넘어갔을 때 정지하기 까지의 시간. 65535이면 Check 안함 */
#define toq_lock_time_addr 172                 /* 172  Torque_Lock이 넘어갔을 때 정지하기 까지의 시간. 65535이면 Check 안함 */

#define temp_lock_time_addr 176               /* 176  Temper_Lock이 넘어갔을 때 정지하기 까지의 시간 */


// R8
// #define CAN_ROBOTRO_ACTUAL_POSITION							0x0110
