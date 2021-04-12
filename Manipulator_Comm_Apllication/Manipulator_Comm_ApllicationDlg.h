
// MFC_Ryu_ClientPgrDlg.h : 헤더 파일
//

#pragma once
//CAN
#include "CanOpenComm.h"
#include "CanOpenDsp402.h"
#include "CanOpenCheckTask.h"
#include "TeleoperationCanOpenTask.h"
#include "CanOpenRead.h"
#include "CanOpenStatusTask.h"
#include "TeleoperationCanOpenStatus.h"
#include "afxcmn.h"
#include "afxwin.h"

#include "./inc/opencv2/opencv.hpp"
using namespace cv;
#pragma comment(lib, "./lib/opencv_world420d.lib")

#include "ClientSock.h" 

#define CAM_TIMER      1000
#define GRIPPER_TIMER  2000
//그리퍼 모터 정의
#define INIT_POS					2047
#define MAX_POS						2467
#define MIN_POS						1657

#define MOTOR_01					31 //9
#define MOTOR_02					32 
#define MOTOR_03					41 
#define MOTOR_04					42 
#define MOTOR_05					51 
#define MOTOR_06					52
#define MOTOR_07					101 //51 
#define MOTOR_08					102 //52
#define MOTOR_09					61
#define MOTOR_10					9

#define MOTOR_GRIP_L				MOTOR_05
#define MOTOR_GRIP_R				MOTOR_06

#define MOTOR_SAW					MOTOR_09

//매니퓰레이터 값 저장될 구조체
typedef struct robot_var {
	double location[6];
}ROBOT_VAR;
//서버에 매니퓰레이터 값 전송할 때 사용할 공용체
union ROBOT_PACKET {
	ROBOT_VAR PACKET;
	double    D_VARIABLE[6];
	byte      byte[sizeof(ROBOT_VAR)];
};


// CMFC_Ryu_ClientPgrDlg 대화 상자
class CMFC_Ryu_ClientPgrDlg : public CDialogEx
{
public://클라이언트 소켓
	CClientSock *m_pClientSock;
	HWND m_phwnd;
// 생성입니다.
public:
	CMFC_Ryu_ClientPgrDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.


// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_RYU_CLIENTPGR_DIALOG };
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

	afx_msg void OnBnClickedButtonConnect();
	afx_msg LRESULT OnReceive(WPARAM, LPARAM);
	afx_msg void OnBnClickedButtonArmDesiredMove();
	//gripper message recv
	afx_msg LRESULT OnReceiveCanData(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	//Camera
	CStatic m_camera;
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	VideoCapture *capture;
	Mat mat_frame;
	CImage *cimage_mfc;

	afx_msg void OnStnClickedCam();
	//Manipulator connect
	
	//Manipulator recv 
	afx_msg void OnEnChangeEditPoseAct1();
	afx_msg void OnEnChangeEditPoseAct2();
	afx_msg void OnEnChangeEditPoseAct3();
	afx_msg void OnEnChangeEditPoseAct4();
	afx_msg void OnEnChangeEditPoseAct5();
	afx_msg void OnEnChangeEditPoseAct6();
	afx_msg void OnEnChangeEditPoseAct7();
	
	double m_edit_recv_1;
	double m_edit_recv_2;
	double m_edit_recv_3;
	double m_edit_recv_4;
	double m_edit_recv_5;
	double m_edit_recv_6;
	//Manipulator send
	afx_msg void OnEnChangeEditPoseDesA1();
	afx_msg void OnEnChangeEditPoseDesA2();
	afx_msg void OnEnChangeEditPoseDesA3();
	afx_msg void OnEnChangeEditPoseDesA4();
	afx_msg void OnEnChangeEditPoseDesA5();
	afx_msg void OnEnChangeEditPoseDesA6();
	afx_msg void OnEnChangeEditPoseDesA7();
	double m_edit_send_1;
	double m_edit_send_2;
	double m_edit_send_3;
	double m_edit_send_4;
	double m_edit_send_5;
	double m_edit_send_6;
	afx_msg void OnBnClickedButtonArmAct2DesCopy();
	
	//m_connect
	BOOL m_connection_to_robot;
	CString m_edit_ip, m_edit_port;
	afx_msg void OnBnClickedGripConnect();

	//gripper can comm
	BOOL m_bConnect;
	bool m_bFlagVmode;
	bool m_bFlagPmode;
	bool m_bFlagCmode;
	bool m_bEachMotorOn;
	int m_servo_all_wait;

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

	int m_gripper_l_pos_raw_data, m_gripper_r_pos_raw_data;
	bool m_gripper_l_drive_u, m_gripper_l_drive_d;
	bool m_gripper_r_drive_u, m_gripper_r_drive_d;
	bool m_gripper_co_drive_u, m_gripper_co_drive_d;

	float	Cnt2Deg[4];
	float th1, th2;
	afx_msg void OnBnClickedCheckGripServo();
	
	//gripper can receive

	//CAN COMMUNICATE
	CanOpenComm			_connect;
	CanOpenInterface* _can;
	CanOpenDsp402* _canDSP;
	CanOpenRead* _canRead;
	TeleoperationCanOpenStatus* _teleStatus;
	CanOpenStatusTask* _canStatus;

	HANDLE ch; //CAN 통신 채널

	CString m_strCanCom;
	CSliderCtrl m_slider_grip_l;
	CSliderCtrl m_slider_grip_r;

	void CMFC_Ryu_ClientPgrDlg::OnReleasedcaptureSliderGripL(NMHDR *pNMHDR, LRESULT *pResult);
	void CMFC_Ryu_ClientPgrDlg::OnReleasedcaptureSliderGripR(NMHDR *pNMHDR, LRESULT *pResult);

	//for can USE 202011
	uint16_t m_nMotorID;
};
