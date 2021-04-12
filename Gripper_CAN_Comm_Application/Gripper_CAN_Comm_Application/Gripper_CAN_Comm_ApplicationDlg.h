// can_comm_basicDlg.h : ��� ����

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

// Ccan_comm_basicDlg ��ȭ ����
class Ccan_comm_basicDlg : public CDialogEx
{
// �����Դϴ�.
public:
	Ccan_comm_basicDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CAN_COMM_BASIC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;
	
	// ������ �޽��� �� �Լ�
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

	HANDLE ch; //CAN ��� ä��
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
