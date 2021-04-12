// can_comm_basicDlg.h : 헤더 파일

#pragma once

// CAN
#include "CanOpenComm.h"
#include "CanOpenDsp402.h"
#include "CanOpenCheckTask.h"
#include "TeleoperationCanOpenTask.h"
#include "CanOpenRead.h"
#include "CanOpenStatusTask.h"
#include "TeleoperationCanOpenStatus.h"
#include "afxcmn.h"
#include "afxwin.h"

// Ccan_comm_basicDlg 대화 상자
class Ccan_comm_basicDlg : public CDialogEx
{
// 생성입니다.
public:
	Ccan_comm_basicDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CAN_COMM_BASIC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;
	
	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCheckCanConnect();
	afx_msg void OnBnClickedCheckGripServoOnoff();
	afx_msg LRESULT OnReceiveCanData(WPARAM wParam, LPARAM lParam);

public: // user var
	CanOpenComm			_connect;
	CanOpenInterface	*_can;
	CanOpenDsp402		*_canDSP;

	CanOpenRead						*_canRead;
	TeleoperationCanOpenStatus		*_teleStatus;
	CanOpenStatusTask				*_canStatus;

	HANDLE ch; //CAN 통신 채널
	bool m_gripper_l_drive_u, m_gripper_l_drive_d;
	bool m_gripper_r_drive_u, m_gripper_r_drive_d;
	bool m_gripper_co_drive_u, m_gripper_co_drive_d;
	int m_servo_all_wait;
	float	Cnt2Deg[4];						// encoder count to degree 
	int m_gripper_l_pos_raw_data, m_gripper_r_pos_raw_data;

	int8_t m_nModeOfOperation;
	int32_t m_nActualPos;
	int32_t m_nActualVel;
	int32_t m_nActualToq;
	int32_t m_nActualCur;
	int32_t m_nRatedCur;
	int16_t m_nCmdToq;
	int32_t m_nCmdVel;
	int32_t m_nCmdPosAbs;
	int32_t m_nCmdPosRel;

	uint16_t m_nMotorID;

	bool m_bFlagVmode;
	bool m_bFlagPmode;
	bool m_bFlagCmode;


public: //control var
	CString m_strCANComm_packet_show;

	afx_msg void OnDestroy();
	BOOL m_bCANConnect;
};
