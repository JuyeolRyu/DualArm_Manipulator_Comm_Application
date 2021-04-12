// can_comm_basicDlg.cpp : ���� ����

#include "stdafx.h"
#include "can_comm_basic.h"
#include "can_comm_basicDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define MOTOR_GRIP_L				51
#define MOTOR_GRIP_R		52
#define INIT_POS					2047
#define MAX_POS						2467
#define MIN_POS						1657


const float F_PI = 3.1416;
const float R2D = 180.0 / F_PI;
const float D2R = F_PI / 180.0;

// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Ccan_comm_basicDlg ��ȭ ����



Ccan_comm_basicDlg::Ccan_comm_basicDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CAN_COMM_BASIC_DIALOG, pParent)
	, m_bCANConnect(FALSE)
	, m_strCANComm_packet_show(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Ccan_comm_basicDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strCANComm_packet_show);
	DDX_Check(pDX, IDC_CHECK_CAN_CONNECT, m_bCANConnect);
}

BEGIN_MESSAGE_MAP(Ccan_comm_basicDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CHECK_CAN_CONNECT, &Ccan_comm_basicDlg::OnBnClickedCheckCanConnect)
	ON_BN_CLICKED(IDC_CHECK_GRIP_SERVO_ONOFF, &Ccan_comm_basicDlg::OnBnClickedCheckGripServoOnoff)
	ON_WM_DESTROY()
	ON_MESSAGE(WM_RECEIVE_CAN_DATA, &Ccan_comm_basicDlg::OnReceiveCanData)
END_MESSAGE_MAP()


// Ccan_comm_basicDlg �޽��� ó����

BOOL Ccan_comm_basicDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	m_gripper_l_drive_u = m_gripper_l_drive_d = m_gripper_r_drive_u = m_gripper_r_drive_d = m_gripper_co_drive_u = m_gripper_co_drive_d = false;
	m_servo_all_wait = 10;

	g_CanBitRate0 = CAN_BT0_1000KB;
	g_CanBitRate1 = CAN_BT1_1000KB;

	_can = NULL;
	_canDSP = NULL;
	_canRead = NULL; // 0810
	_canStatus = NULL; // 0810
	_teleStatus = NULL; // 0810

	m_nMotorID = MOTOR_GRIP_L; // 2;// 1;

	CString temp;

	Cnt2Deg[0] = 360.0 / 52953;
	Cnt2Deg[1] = 360.0 / 52953;
	Cnt2Deg[2] = 360.0 / 4096;
	Cnt2Deg[3] = 360.0 / 4096;

	UpdateData(FALSE);

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void Ccan_comm_basicDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void Ccan_comm_basicDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR Ccan_comm_basicDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Ccan_comm_basicDlg::OnBnClickedCheckCanConnect()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	//IDC_CHECK_CONNECT

	if (m_bCANConnect) {
		GetDlgItem(IDC_CHECK_CAN_CONNECT)->SetWindowText(TEXT("DisConnect"));
		ch = _connect.CanOpenConnect(0); // ù��°(0) ����� ��ſ� ���� ch ���� return���� �����ش�.

		_can = new CanOpenInterface();
		_canDSP = new CanOpenDsp402(ch, _can);

		_canRead = new CanOpenRead(this->m_hWnd, ch); // 180615 read ����
		_canStatus = new CanOpenStatusTask(_canRead); // 0810 read ���� PC �� ������ �޽����� �Ľ��ϴ� ������
		_teleStatus = new TeleoperationCanOpenStatus("CHECK_STATUS", TIME_CHECK_STATUS, _canStatus);// 0810 read ����

		_teleStatus->Start();// 0810 read ����

		GetDlgItem(IDC_CHECK_GRIP_SERVO_ONOFF)->EnableWindow(true);

		SetTimer(1000, 100, NULL);   //for slidetr btn // DRyu

		_canDSP->ResetNode(coNodeAll);

	}
	else {
		GetDlgItem(IDC_CHECK_CAN_CONNECT)->SetWindowText(TEXT("CONNECT"));
		GetDlgItem(IDC_CHECK_GRIP_SERVO_ONOFF)->EnableWindow(false);


		_teleStatus->Stop();// 180615 read ����
		_connect.CanOpenDisConnect();

		_can = NULL;
		_canDSP = NULL;
		_canRead = NULL; // 0810
		_canStatus = NULL; // 0810
		_teleStatus = NULL; // 0810

		KillTimer(1000);
	}
}


void Ccan_comm_basicDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	if (m_bCANConnect == true) {
		m_bCANConnect = false;
		OnBnClickedCheckCanConnect();
	}

	if (_can != NULL) _can = NULL;
	if (_canDSP != NULL) _canDSP = NULL;
	if (_canRead != NULL) _canRead = NULL; // 0810
	if (_canStatus != NULL) _canStatus = NULL; // 0810
	if (_teleStatus != NULL) _teleStatus = NULL; // 0810
}


void Ccan_comm_basicDlg::OnBnClickedCheckGripServoOnoff()
{
	if (IsDlgButtonChecked(IDC_CHECK_GRIP_SERVO_ONOFF))
	{
		GetDlgItem(IDC_CHECK_GRIP_SERVO_ONOFF)->SetWindowText(TEXT("Gripper Servo Off"));
		Sleep(1);
		_canDSP->SetModesOfOperation(MOTOR_GRIP_L, CIA_402_PROFILE_POSITION_MODE);
		Sleep(1);
		_canDSP->SetModesOfOperation(MOTOR_GRIP_R, CIA_402_PROFILE_POSITION_MODE);
		Sleep(1);

		m_bFlagPmode = true;
		m_bFlagVmode = false;
		m_bFlagCmode = false;

		_canDSP->MotorInitialize(MOTOR_GRIP_L);
		_canDSP->MotorInitialize(MOTOR_GRIP_R);

		_canDSP->GetActualPosition(MOTOR_GRIP_L);
		_canDSP->GetActualPosition(MOTOR_GRIP_R);

		m_servo_all_wait = 10;
		int init_vel_R8 = 8;

		_canDSP->SetProfileVelocity(MOTOR_GRIP_L, init_vel_R8);
		_canDSP->SetProfileVelocity(MOTOR_GRIP_R, init_vel_R8);
	}
	else
	{
		GetDlgItem(IDC_CHECK_GRIP_SERVO_ONOFF)->SetWindowText(TEXT("Gripper Servo On"));
		_canDSP->DisableOperation(MOTOR_GRIP_L); // operation mode �� �ٲ����� �ʴ´�
		_canDSP->DisableOperation(MOTOR_GRIP_R); // operation mode �� �ٲ����� �ʴ´�
	}
}


afx_msg LRESULT Ccan_comm_basicDlg::OnReceiveCanData(WPARAM wParam, LPARAM lParam)
{
	CANMSG  *sCanMsg;
	CString msg, str1;
	int val1;
	double openDistance;
	openDistance = 0;
	val1 = 0;
	sCanMsg = (CANMSG *)lParam;

	UINT8 p_data[8];
	for (int i = 0; i < 8; i++) p_data[i] = 0;

	if (sCanMsg->uMsgInfo.Bytes.bType == CAN_MSGTYPE_DATA)
	{
		uint32_t rid = sCanMsg->dwMsgId - coBootup_Message_Address;

		if ((sCanMsg->dwMsgId & coSDO_RX) == coSDO_RX)
		{
			uint32_t rid = sCanMsg->dwMsgId - coSDO_RX;
			switch (sCanMsg->abData[1])
			{

			case 0x64:			// GetActualPosition
			{
				//*
				switch (sCanMsg->abData[0])
				{
				case READ_RESPONSE_1BYTE:
					memcpy(&m_nActualPos, &(sCanMsg->abData[4]), 1);
					break;
				case READ_RESPONSE_2BYTE:
					memcpy(&m_nActualPos, &(sCanMsg->abData[4]), 2);
					break;
				case READ_RESPONSE_4BYTE:
				case READ_RESPONSE_MAX:
					memcpy(&m_nActualPos, &(sCanMsg->abData[4]), 4);
					break;
				}
				str1.Format(_T("%d"), m_nActualPos);
				SetDlgItemText(IDC_STATIC_GRIP_MOTOR_POSE, str1);
				///DRyu store the receive value
				switch (rid) // 20190621 ����
				{

				case MOTOR_GRIP_L:
					m_gripper_l_pos_raw_data = (int)((m_nActualPos - 2106) * 10 * Cnt2Deg[3]);
					str1.Format(_T("%d"), m_gripper_l_pos_raw_data);
					SetDlgItemText(IDC_EDIT_GRIP_L_POS, str1);
					break;
				case MOTOR_GRIP_R:
					m_gripper_r_pos_raw_data = (int)((2054 - m_nActualPos) * 10 * Cnt2Deg[3]);
					str1.Format(_T("%d"), m_gripper_r_pos_raw_data);
					SetDlgItemText(IDC_EDIT_GRIP_R_POS, str1);
					break;
				default:
					break;
				}
				///DRyu store the receive value
			}
			break;
			case 0x6C:		// GetActualVelocity
			{
				switch (sCanMsg->abData[0])
				{
				case READ_RESPONSE_1BYTE:
					memcpy(&m_nActualVel, &(sCanMsg->abData[4]), 1);
					break;
				case READ_RESPONSE_2BYTE:
					memcpy(&m_nActualVel, &(sCanMsg->abData[4]), 2);
					break;
				case READ_RESPONSE_4BYTE:
				case READ_RESPONSE_MAX:
					memcpy(&m_nActualVel, &(sCanMsg->abData[4]), 4);
					break;
				}
				str1.Format(_T("%d"), m_nActualVel);
				SetDlgItemText(IDC_STATIC_GRIP_MOTOR_VEL, str1);
			}
			break;
			case 0x75:			// GetRatedCurrent
			{
				switch (sCanMsg->abData[0])
				{
				case READ_RESPONSE_1BYTE:
					memcpy(&m_nRatedCur, &(sCanMsg->abData[4]), 1);
					break;
				case READ_RESPONSE_2BYTE:
					memcpy(&m_nRatedCur, &(sCanMsg->abData[4]), 2);
					break;
				case READ_RESPONSE_4BYTE:
				case READ_RESPONSE_MAX:
					memcpy(&m_nRatedCur, &(sCanMsg->abData[4]), 4);
					break;
				}
				str1.Format(_T("%d"), m_nRatedCur);
				SetDlgItemText(IDC_STATIC_GRIP_MOTOR_CUR_RATED, str1);
			}
			break;
			case 0x78:			// GetActualCurrent
			{
				switch (sCanMsg->abData[0])
				{
				case READ_RESPONSE_1BYTE:
					memcpy(&m_nActualCur, &(sCanMsg->abData[4]), 1);
					break;
				case READ_RESPONSE_2BYTE:
					memcpy(&m_nActualCur, &(sCanMsg->abData[4]), 2);
					break;
				case READ_RESPONSE_4BYTE:
				case READ_RESPONSE_MAX:
					memcpy(&m_nActualCur, &(sCanMsg->abData[4]), 4);
					break;
				}
				str1.Format(_T("%d"), m_nActualCur);
				SetDlgItemText(IDC_STATIC_GRIP_MOTOR_CUR_ACTUAL, str1);
			}
			break;
			case 0x60:			//getOperationMode
			{
				m_nModeOfOperation = sCanMsg->abData[4];
				str1.Format(_T("%d"), m_nModeOfOperation);
				SetDlgItemText(IDC_STATIC_GRIP_MOTOR_MODE, str1);
			}
			break;
			}
		}
		if (sCanMsg->dwMsgId > PDO_Statusword && sCanMsg->dwMsgId < PDO_Statusword + 40) {
			uint32_t rid = sCanMsg->dwMsgId - PDO_Statusword;
			uint32_t data_len = (uint32_t)(sCanMsg->uMsgInfo.Bits.dlc & 0xFF);
			uint8_t LB = sCanMsg->abData[0];
			uint8_t HB = sCanMsg->abData[1];
		}

		memcpy(&(p_data[0]), &(sCanMsg->abData[0]), 8);
		str1.Format(_T("%x %x %x %x %x %x %x %x %x \r\n"), rid, p_data[0], p_data[1], p_data[2], p_data[3], p_data[4], p_data[5], p_data[6], p_data[7]);
		m_strCANComm_packet_show.Append(str1);
		UpdateData(FALSE);

	}

	return 0;
}
