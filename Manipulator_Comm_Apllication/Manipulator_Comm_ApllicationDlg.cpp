
// MFC_Ryu_ClientPgrDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "MFC_Ryu_ClientPgr.h"
#include "MFC_Ryu_ClientPgrDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CMFC_Ryu_ClientPgrDlg 대화 상자



CMFC_Ryu_ClientPgrDlg::CMFC_Ryu_ClientPgrDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFC_RYU_CLIENTPGR_DIALOG, pParent)
	, m_edit_send_1(0)
	, m_edit_send_2(0)
	, m_edit_send_3(0)
	, m_edit_send_4(0)
	, m_edit_send_5(0)
	, m_edit_send_6(0)
	, m_edit_recv_1(0)
	, m_edit_recv_2(0)
	, m_edit_recv_3(0)
	, m_edit_recv_4(0)
	, m_edit_recv_5(0)
	, m_edit_recv_6(0)
	//gripper
	, m_bConnect(FALSE)
	, m_bFlagVmode(false)
	, m_bFlagPmode(false)
	, m_bFlagCmode(false)
	, m_nActualPos(0)
	, m_strCanCom(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFC_Ryu_ClientPgrDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//camera
	DDX_Control(pDX, IDC_CAM, m_camera);
	//manipulator send&recv
	DDX_Text(pDX, IDC_EDIT_POSE_DES_A1, m_edit_send_1);
	DDX_Text(pDX, IDC_EDIT_POSE_DES_A2, m_edit_send_2);
	DDX_Text(pDX, IDC_EDIT_POSE_DES_A3, m_edit_send_3);
	DDX_Text(pDX, IDC_EDIT_POSE_DES_A4, m_edit_send_4);
	DDX_Text(pDX, IDC_EDIT_POSE_DES_A5, m_edit_send_5);
	DDX_Text(pDX, IDC_EDIT_POSE_DES_A6, m_edit_send_6);
	DDX_Text(pDX, IDC_EDIT_POSE_ACT1, m_edit_recv_1);
	DDX_Text(pDX, IDC_EDIT_POSE_ACT2, m_edit_recv_2);
	DDX_Text(pDX, IDC_EDIT_POSE_ACT3, m_edit_recv_3);
	DDX_Text(pDX, IDC_EDIT_POSE_ACT4, m_edit_recv_4);
	DDX_Text(pDX, IDC_EDIT_POSE_ACT5, m_edit_recv_5);
	DDX_Text(pDX, IDC_EDIT_POSE_ACT6, m_edit_recv_6);
	//manipulator ip & port address
	DDX_Text(pDX, IDC_EDIT_IP, m_edit_ip);
	DDX_Text(pDX, IDC_EDIT_PORT, m_edit_port);
	//gripper connect
	DDX_Check(pDX, IDC_GRIP_CONNECT, m_bConnect);
	//gripper recv
	DDX_Text(pDX, IDC_EDIT1, m_strCanCom);
	DDX_Control(pDX, IDC_SLIDER_GRIP_L, m_slider_grip_l);
	DDX_Control(pDX, IDC_SLIDER_GRIP_R, m_slider_grip_r);
}

BEGIN_MESSAGE_MAP(CMFC_Ryu_ClientPgrDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_STN_CLICKED(IDC_CAM, &CMFC_Ryu_ClientPgrDlg::OnStnClickedCam)
	//manipulator event
	ON_EN_CHANGE(IDC_EDIT_POSE_ACT1, &CMFC_Ryu_ClientPgrDlg::OnEnChangeEditPoseAct1)
	ON_EN_CHANGE(IDC_EDIT_POSE_ACT2, &CMFC_Ryu_ClientPgrDlg::OnEnChangeEditPoseAct2)
	ON_EN_CHANGE(IDC_EDIT_POSE_ACT3, &CMFC_Ryu_ClientPgrDlg::OnEnChangeEditPoseAct3)
	ON_EN_CHANGE(IDC_EDIT_POSE_ACT4, &CMFC_Ryu_ClientPgrDlg::OnEnChangeEditPoseAct4)
	ON_EN_CHANGE(IDC_EDIT_POSE_ACT5, &CMFC_Ryu_ClientPgrDlg::OnEnChangeEditPoseAct5)
	ON_EN_CHANGE(IDC_EDIT_POSE_ACT6, &CMFC_Ryu_ClientPgrDlg::OnEnChangeEditPoseAct6)
	ON_EN_CHANGE(IDC_EDIT_POSE_ACT7, &CMFC_Ryu_ClientPgrDlg::OnEnChangeEditPoseAct7)
	ON_EN_CHANGE(IDC_EDIT_POSE_DES_A1, &CMFC_Ryu_ClientPgrDlg::OnEnChangeEditPoseDesA1)
	ON_EN_CHANGE(IDC_EDIT_POSE_DES_A2, &CMFC_Ryu_ClientPgrDlg::OnEnChangeEditPoseDesA2)
	ON_EN_CHANGE(IDC_EDIT_POSE_DES_A3, &CMFC_Ryu_ClientPgrDlg::OnEnChangeEditPoseDesA3)
	ON_EN_CHANGE(IDC_EDIT_POSE_DES_A4, &CMFC_Ryu_ClientPgrDlg::OnEnChangeEditPoseDesA4)
	ON_EN_CHANGE(IDC_EDIT_POSE_DES_A5, &CMFC_Ryu_ClientPgrDlg::OnEnChangeEditPoseDesA5)
	ON_EN_CHANGE(IDC_EDIT_POSE_DES_A6, &CMFC_Ryu_ClientPgrDlg::OnEnChangeEditPoseDesA6)
	ON_EN_CHANGE(IDC_EDIT_POSE_DES_A7, &CMFC_Ryu_ClientPgrDlg::OnEnChangeEditPoseDesA7)
	ON_BN_CLICKED(IDC_BUTTON_ARM_ACT_2_DES_COPY, &CMFC_Ryu_ClientPgrDlg::OnBnClickedButtonArmAct2DesCopy)
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CMFC_Ryu_ClientPgrDlg::OnBnClickedButtonConnect)
	ON_MESSAGE(WM_RECEIVE_DATA, OnReceive)
	ON_BN_CLICKED(IDC_BUTTON_ARM_DESIRED_MOVE, &CMFC_Ryu_ClientPgrDlg::OnBnClickedButtonArmDesiredMove)
	//gripper event
	ON_BN_CLICKED(IDC_GRIP_CONNECT, &CMFC_Ryu_ClientPgrDlg::OnBnClickedGripConnect)
	ON_BN_CLICKED(IDC_CHECK_GRIP_SERVO, &CMFC_Ryu_ClientPgrDlg::OnBnClickedCheckGripServo)
	ON_MESSAGE(WM_RECEIVE_CAN_DATA, &CMFC_Ryu_ClientPgrDlg::OnReceiveCanData)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_GRIP_R, &CMFC_Ryu_ClientPgrDlg::OnReleasedcaptureSliderGripR)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_GRIP_L, &CMFC_Ryu_ClientPgrDlg::OnReleasedcaptureSliderGripL)
END_MESSAGE_MAP()


// CMFC_Ryu_ClientPgrDlg 메시지 처리기

BOOL CMFC_Ryu_ClientPgrDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	//ip & port 주소 초기화
	SetDlgItemText(IDC_EDIT_IP, _T("127.0.0.1"));
	SetDlgItemText(IDC_EDIT_PORT, _T("8888"));

	//m_connection
	m_connection_to_robot = false;

	//웹캠 띄우기=========================================================================
	//*
	capture = new VideoCapture(0);
	if (!capture->isOpened())
	{
		MessageBox(_T("캠을 열수 없습니다. \n"));
	}

	//웹캠 크기를  320x240으로 지정    
	capture->set(CAP_PROP_FRAME_WIDTH, 320);
	capture->set(CAP_PROP_FRAME_HEIGHT, 240);
	cimage_mfc = NULL;
	SetTimer(CAM_TIMER, 30, NULL);
	//*/

	/////////////////////////
	//for can USE 202011
	
	CString temp;
	
	g_CanBitRate0 = CAN_BT0_1000KB;
	g_CanBitRate1 = CAN_BT1_1000KB;
	
	_can = NULL;
	_canDSP = NULL;
	_canRead = NULL; // 0810
	_canStatus = NULL; // 0810
	_teleStatus = NULL; // 0810

	m_nMotorID = MOTOR_01; // 2;// 1;
	

	//for can USE 202011
	/////////////////////////




	//gripper init
	m_servo_all_wait = 10;
	m_gripper_l_drive_u = m_gripper_l_drive_d = m_gripper_r_drive_u = m_gripper_r_drive_d = m_gripper_co_drive_u = m_gripper_co_drive_d = false; //그리퍼 움직이는 flag
	m_gripper_l_pos_raw_data = m_gripper_r_pos_raw_data = 0;

	Cnt2Deg[0] = 360.0 / 52953;
	Cnt2Deg[1] = 360.0 / 52953;
	Cnt2Deg[2] = 360.0 / 4096;
	Cnt2Deg[3] = 360.0 / 4096;

	th1 = 0.0;
	th2 = 0.0;
	//그리퍼 슬라이더 초기화

	m_slider_grip_l.SetRange(-600, 300);
	m_slider_grip_l.SetRangeMin(-600);
	m_slider_grip_l.SetRangeMax(300);
	m_slider_grip_l.SetPos(0);
	m_slider_grip_l.SetTicFreq(10);
	m_slider_grip_l.SetLineSize(1);
	m_slider_grip_l.SetPageSize(10);

	m_slider_grip_r.SetRange(-600, 300);
	m_slider_grip_r.SetRangeMin(-600);
	m_slider_grip_r.SetRangeMax(300);
	m_slider_grip_r.SetPos(0);
	m_slider_grip_r.SetTicFreq(10);
	m_slider_grip_r.SetLineSize(1);
	m_slider_grip_r.SetPageSize(10);

	temp.Format(_T("%d"), m_slider_grip_l.GetPos());
	SetDlgItemText(IDC_EDIT_SLIDER_GRIP_L, temp);

	temp.Format(_T("%d"), m_slider_grip_r.GetPos());

	SetDlgItemText(IDC_EDIT_SLIDER_GRIP_R, temp);


	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFC_Ryu_ClientPgrDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFC_Ryu_ClientPgrDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFC_Ryu_ClientPgrDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFC_Ryu_ClientPgrDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	//타이머 종료
	capture->release();
	KillTimer(CAM_TIMER);

	if (_can != NULL) _can = NULL;
	if (_canDSP != NULL) _canDSP = NULL;
	if (_canRead != NULL) _canRead = NULL; // 0810
	if (_canStatus != NULL) _canStatus = NULL; // 0810
	if (_teleStatus != NULL) _teleStatus = NULL; // 0810

}

void CMFC_Ryu_ClientPgrDlg::OnTimer(UINT_PTR nIDEvent)
{
	int temp_step_size = 20;
	int temp_step_size_R8 = 10;
	int temp_int_val;
	CString temp;
	float f_temp;

	switch (nIDEvent)
	{
	case CAM_TIMER:
	{
		//*
		capture->read(mat_frame);

		int bpp = 8 * mat_frame.elemSize();
		assert((bpp == 8 || bpp == 24 || bpp == 32));

		int padding = 0;
		//32 bit image is always DWORD aligned because each pixel requires 4 bytes
		if (bpp < 32)
			padding = 4 - (mat_frame.cols % 4);

		if (padding == 4)
			padding = 0;

		int border = 0;
		//32 bit image is always DWORD aligned because each pixel requires 4 bytes
		if (bpp < 32)
		{
			border = 4 - (mat_frame.cols % 4);
		}



		Mat mat_temp;
		if (border > 0 || mat_frame.isContinuous() == false)
		{
			// Adding needed columns on the right (max 3 px)
			cv::copyMakeBorder(mat_frame, mat_temp, 0, 0, 0, border, cv::BORDER_CONSTANT, 0);
		}
		else
		{
			mat_temp = mat_frame;
		}


		RECT r;
		m_camera.GetClientRect(&r);
		cv::Size winSize(r.right, r.bottom);



		if (cimage_mfc)
		{
			cimage_mfc->ReleaseDC();
			delete cimage_mfc;
			cimage_mfc = nullptr;
		}

		cimage_mfc = new CImage();
		cimage_mfc->Create(winSize.width, winSize.height, 24);


		BITMAPINFO bitInfo;
		bitInfo.bmiHeader.biBitCount = bpp;
		bitInfo.bmiHeader.biWidth = mat_temp.cols;
		bitInfo.bmiHeader.biHeight = -mat_temp.rows;
		bitInfo.bmiHeader.biPlanes = 1;
		bitInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bitInfo.bmiHeader.biCompression = BI_RGB;
		bitInfo.bmiHeader.biClrImportant = 0;
		bitInfo.bmiHeader.biClrUsed = 0;
		bitInfo.bmiHeader.biSizeImage = 0;
		bitInfo.bmiHeader.biXPelsPerMeter = 0;
		bitInfo.bmiHeader.biYPelsPerMeter = 0;


		// Image is bigger or smaller than into destination rectangle
		// we use stretch in full rect

		if (mat_temp.cols == winSize.width  && mat_temp.rows == winSize.height)
		{
			// source and destination have same size
			// transfer memory block
			// NOTE: the padding border will be shown here. Anyway it will be max 3px width

			SetDIBitsToDevice(cimage_mfc->GetDC(),
				//destination rectangle
				0, 0, winSize.width, winSize.height,
				0, 0, 0, mat_temp.rows,
				mat_temp.data, &bitInfo, DIB_RGB_COLORS);
		}
		else
		{
			// destination rectangle
			int destx = 0, desty = 0;
			int destw = winSize.width;
			int desth = winSize.height;

			// rectangle defined on source bitmap
			// using imgWidth instead of mat_temp.cols will ignore the padding border
			int imgx = 0, imgy = 0;
			int imgWidth = mat_temp.cols - border;
			int imgHeight = mat_temp.rows;

			StretchDIBits(cimage_mfc->GetDC(),
				destx, desty, destw, desth,
				imgx, imgy, imgWidth, imgHeight,
				mat_temp.data, &bitInfo, DIB_RGB_COLORS, SRCCOPY);
		}

		cimage_mfc->BitBlt(::GetDC(m_camera.m_hWnd), 0, 0);

		if (cimage_mfc)
		{
			cimage_mfc->ReleaseDC();
			delete cimage_mfc;
			cimage_mfc = nullptr;
		}

		break;
			//*/
	}

	default:
		break;
	}
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	


	CDialogEx::OnTimer(nIDEvent);
}


void CMFC_Ryu_ClientPgrDlg::OnStnClickedCam()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CMFC_Ryu_ClientPgrDlg::OnEnChangeEditPoseAct1()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
void CMFC_Ryu_ClientPgrDlg::OnEnChangeEditPoseAct2()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
void CMFC_Ryu_ClientPgrDlg::OnEnChangeEditPoseAct3()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
void CMFC_Ryu_ClientPgrDlg::OnEnChangeEditPoseAct4()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
void CMFC_Ryu_ClientPgrDlg::OnEnChangeEditPoseAct5()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
void CMFC_Ryu_ClientPgrDlg::OnEnChangeEditPoseAct6()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
void CMFC_Ryu_ClientPgrDlg::OnEnChangeEditPoseAct7()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
void CMFC_Ryu_ClientPgrDlg::OnEnChangeEditPoseDesA1()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
void CMFC_Ryu_ClientPgrDlg::OnEnChangeEditPoseDesA2()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
void CMFC_Ryu_ClientPgrDlg::OnEnChangeEditPoseDesA3()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
void CMFC_Ryu_ClientPgrDlg::OnEnChangeEditPoseDesA4()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
void CMFC_Ryu_ClientPgrDlg::OnEnChangeEditPoseDesA5()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
void CMFC_Ryu_ClientPgrDlg::OnEnChangeEditPoseDesA6()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
void CMFC_Ryu_ClientPgrDlg::OnEnChangeEditPoseDesA7()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


//매니퓰레이터 connect
void CMFC_Ryu_ClientPgrDlg::OnBnClickedButtonConnect()
{
	UpdateData(TRUE);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString temp_show_str;

	//connect ==> close
	if (m_connection_to_robot)
	{
		m_pClientSock->Close();
		m_connection_to_robot = false;

		temp_show_str.Format(_T("Connect"));
		GetDlgItem(IDC_BUTTON_CONNECT)->SetWindowText(temp_show_str);

	}//close ==> connect
	else
	{
		m_pClientSock = new CClientSock;
		CString ip_buffer,port;
		GetDlgItem(IDC_EDIT_IP) ->GetWindowText(ip_buffer);
		GetDlgItem(IDC_EDIT_PORT)->GetWindowText(port);
		
		char* ip = LPSTR(LPCTSTR(ip_buffer));

		m_pClientSock->Create();

		if (m_pClientSock->Connect((LPCTSTR)ip, _ttoi(port)))
		//if(m_pClientSock->Connect((LPSTR)ip, _ttoi(port)))
			MessageBox(_T("connect failed. \n"));
		else
			MessageBox(_T("connect.\n"));

		m_pClientSock->SetWnd(this->m_hWnd);

		m_connection_to_robot = true;

		temp_show_str.Format(_T("Close"));
		GetDlgItem(IDC_BUTTON_CONNECT)->SetWindowText(temp_show_str);
	}

	UpdateData(FALSE);
}

void CMFC_Ryu_ClientPgrDlg::OnBnClickedButtonArmAct2DesCopy()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	m_edit_send_1 = m_edit_recv_1;
	m_edit_send_2 = m_edit_recv_2;
	m_edit_send_3 = m_edit_recv_3;
	m_edit_send_4 = m_edit_recv_4;
	m_edit_send_5 = m_edit_recv_5;
	m_edit_send_6 = m_edit_recv_6;
	//m_edit_pose_des7 = m_edit_rcv_7;

	UpdateData(FALSE);
}

void CMFC_Ryu_ClientPgrDlg::OnBnClickedButtonArmDesiredMove()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//TRUE ==> 컨트롤값을 변수로 전달
	UpdateData(TRUE);
	//CString m_strSend = (_T(""));
	ROBOT_PACKET m_robot_packet;
	m_robot_packet.PACKET.location[0] = m_edit_send_1;
	m_robot_packet.PACKET.location[1] = m_edit_send_2;
	m_robot_packet.PACKET.location[2] = m_edit_send_3;
	m_robot_packet.PACKET.location[3] = m_edit_send_4;
	m_robot_packet.PACKET.location[4] = m_edit_send_5;
	m_robot_packet.PACKET.location[5] = m_edit_send_6;

	m_pClientSock->Send(m_robot_packet.byte, 48);

	//lstrcpy((LPWSTR)m_strSend.operator const char* (), (LPWSTR)m_robot_packet.byte);
	UpdateData(FALSE);
}

LRESULT CMFC_Ryu_ClientPgrDlg::OnReceive(WPARAM wParam, LPARAM lParam)
{


	char temp[48];
	ROBOT_PACKET m_robot_packet;

	m_pClientSock->Receive((LPSTR)m_robot_packet.byte, 48);

	m_edit_recv_1 = m_robot_packet.D_VARIABLE[0];
	m_edit_recv_2 = m_robot_packet.D_VARIABLE[1];
	m_edit_recv_3 = m_robot_packet.D_VARIABLE[2];
	m_edit_recv_4 = m_robot_packet.D_VARIABLE[3];
	m_edit_recv_5 = m_robot_packet.D_VARIABLE[4];
	m_edit_recv_6 = m_robot_packet.D_VARIABLE[5];


	UpdateData(FALSE);


	return TRUE;
}


void CMFC_Ryu_ClientPgrDlg::OnBnClickedGripConnect()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	if (m_bConnect) {
		GetDlgItem(IDC_GRIP_CONNECT)->SetWindowText(TEXT("DisConnect"));
		ch = _connect.CanOpenConnect(0); // 첫번째(0) 연결된 통신에 대한 ch 값을 return으로 돌려준다.

		_can = new CanOpenInterface();
		_canDSP = new CanOpenDsp402(ch, _can);

		// 이부분은 필요 없는 것 같다. 20180614
		//_canTask = new CanOpenCheckTask(_canDSP);                                 //여기서 동작이나 데이터를 보내라고 하는 명령을 기술하고
		//_canTele = new TeleoperationCanOpenTask("GETDATA", TIME_GETDATA, _canTask); //이것을 실행하라는 쓰레드

		_canRead = new CanOpenRead(this->m_hWnd, ch); // 180615 read 수정
		_canStatus = new CanOpenStatusTask(_canRead); // 0810 read 수정 PC 에 도착한 메시지를 파싱하는 쓰레드
		_teleStatus = new TeleoperationCanOpenStatus("CHECK_STATUS", TIME_CHECK_STATUS, _canStatus);// 0810 read 수정

		//_canTele->Start();

		_teleStatus->Start();// 0810 read 수정

		//JRyu 20201125
		//GetDlgItem(IDC_CHECK_SERVO)->EnableWindow(true);
		GetDlgItem(IDC_CHECK_GRIP_SERVO)->EnableWindow(true);
		//GetDlgItem(IDC_CHECK_STAGE_SERVO)->EnableWindow(true);
		
		//ItemEnable_OperationMode(true);
		//ItemEnable_ReadStatus(true);

		SetTimer(GRIPPER_TIMER, 100, NULL);   //for slidetr btn // DRyu

		_canDSP->ResetNode(coNodeAll);
	}
	else {
		GetDlgItem(IDC_GRIP_CONNECT)->SetWindowText(TEXT("CONNECT"));

		//if (m_bEachMotorOn == true) OnBnClickedBtnEachMotorOff();
		//((CButton*)GetDlgItem(IDC_CK_DRIVER_STATUS1))->SetCheck(FALSE);
		
		//JRyu 20201125
		//GetDlgItem(IDC_CHECK_SERVO)->EnableWindow(false);
		GetDlgItem(IDC_CHECK_GRIP_SERVO)->EnableWindow(false);
		//GetDlgItem(IDC_CHECK_STAGE_SERVO)->EnableWindow(false);

		//ItemEnable_OperationMode(false);
		//ItemEnable_ReadStatus(false);

		_teleStatus->Stop();// 180615 read 수정
		_connect.CanOpenDisConnect();

		_can = NULL;

		_canDSP = NULL;

		_canRead = NULL; // 0810
		_canStatus = NULL; // 0810
		_teleStatus = NULL; // 0810

		KillTimer(GRIPPER_TIMER);
	}
}

void CMFC_Ryu_ClientPgrDlg::OnBnClickedCheckGripServo()
{
	if (IsDlgButtonChecked(IDC_CHECK_GRIP_SERVO))
	{
		GetDlgItem(IDC_CHECK_GRIP_SERVO)->SetWindowText(TEXT("Gripper Servo Off"));
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

		//_canDSP->GetModesOfOperation(MOTOR_GRIP_L);
		//_canDSP->GetModesOfOperation(MOTOR_GRIP_R);
		//_canDSP->GetRatedCurrent(MOTOR_GRIP_L);
		//_canDSP->GetRatedCurrent(MOTOR_GRIP_R);
		_canDSP->GetActualPosition(MOTOR_GRIP_L);
		_canDSP->GetActualPosition(MOTOR_GRIP_R);

		m_servo_all_wait = 10;
		int init_vel_R8 = 8;

		_canDSP->SetProfileVelocity(MOTOR_GRIP_L, init_vel_R8);
		_canDSP->SetProfileVelocity(MOTOR_GRIP_R, init_vel_R8);
		//ItemEnable_GripServoOn(true);
		//ItemEnable_OperationMode(false);
		//ItemEnable_ReadStatus(false);
	}
	else
	{
		GetDlgItem(IDC_CHECK_GRIP_SERVO)->SetWindowText(TEXT("Gripper Servo On"));
		_canDSP->DisableOperation(MOTOR_GRIP_L); // operation mode 가 바뀌지는 않는다
		_canDSP->DisableOperation(MOTOR_GRIP_R); // operation mode 가 바뀌지는 않는다
												 //ItemEnable_GripServoOn(false);
												 //ItemEnable_OperationMode(true);
												 //ItemEnable_ReadStatus(true);
	}

}

afx_msg LRESULT CMFC_Ryu_ClientPgrDlg::OnReceiveCanData(WPARAM wParam, LPARAM lParam)
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

		/*
		if ((sCanMsg->dwMsgId & (UINT32)coBootup_Message_Address) == (UINT32)coBootup_Message_Address) {
		//		if ( (sCanMsg->dwMsgId & 0x700) == 0x700) {

		switch (rid)
		{
		case MOTOR_GRIP_L:
		//((CButton*)GetDlgItem(IDC_CK_DRIVER_STATUS1))->SetCheck(TRUE);
		//_canDSP->PDO_MAP_Setting(rid);       // 테스트 하기 위해서 맵핑을 잠시 꺼두자 20180818
		_canDSP->Starting_Remote_Node(rid);  // mapping 후에 start를 해주어야 mapping이 작동한다.
		// 301명령어를 쓰려면 resetnode를 해 주어야 한다.
		break;
		default:
		break;
		}
		}
		*/
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
				SetDlgItemText(IDC_STATIC_GRIP_MOTOR_POS, str1);
				//*/

				///DRyu store the receive value
				switch (rid) // 20190621 수정
				{

				case MOTOR_GRIP_L:
					m_gripper_l_pos_raw_data = (int)((m_nActualPos - 2106) * 10 * Cnt2Deg[3]);
					str1.Format(_T("%d"), m_gripper_l_pos_raw_data);
					SetDlgItemText(IDC_EDIT_SLIDER_GRIP_L, str1);
					break;
				case MOTOR_GRIP_R:
					m_gripper_r_pos_raw_data = (int)((2054 - m_nActualPos) * 10 * Cnt2Deg[3]);
					str1.Format(_T("%d"), m_gripper_r_pos_raw_data);
					SetDlgItemText(IDC_EDIT_SLIDER_GRIP_R, str1);
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
			//case 0x41:			// getStatus
			//{
			//	switch (msg->abData[0])
			//	{
			//	case READ_RESPONSE_1BYTE:
			//		memcpy(motor->status + (rid - 1), &(msg->abData[4]), 1);
			//		break;
			//	case READ_RESPONSE_2BYTE:
			//		memcpy(motor->status + (rid - 1), &(msg->abData[4]), 2);
			//		break;
			//	case READ_RESPONSE_4BYTE:
			//	case READ_RESPONSE_MAX:
			//		memcpy(motor->status + (rid - 1), &(msg->abData[4]), 4);
			//		break;
			//	}
			//}
			//break;
			case 0x60:			//getOperationMode
			{
				m_nModeOfOperation = sCanMsg->abData[4];
				str1.Format(_T("%d"), m_nModeOfOperation);
				SetDlgItemText(IDC_STATIC_GRIP_MOTOR_MODE, str1);
			}
			break;
			//case 0x78:			// GetActualCurrent
			//{
			//	switch (msg->abData[0])
			//	{
			//	case READ_RESPONSE_1BYTE:
			//		memcpy(motor->current + (rid - 1), &(msg->abData[4]), 1);
			//		break;
			//	case READ_RESPONSE_2BYTE:
			//		memcpy(motor->current + (rid - 1), &(msg->abData[4]), 2);
			//		break;
			//	case READ_RESPONSE_4BYTE:
			//	case READ_RESPONSE_MAX:
			//		memcpy(motor->current + (rid - 1), &(msg->abData[4]), 4);
			//		break;
			//	}
			//}
			//break;
			}
		}
		if (sCanMsg->dwMsgId > PDO_Statusword && sCanMsg->dwMsgId < PDO_Statusword + 40) {
			uint32_t rid = sCanMsg->dwMsgId - PDO_Statusword;
			uint32_t data_len = (uint32_t)(sCanMsg->uMsgInfo.Bits.dlc & 0xFF);
			uint8_t LB = sCanMsg->abData[0];
			uint8_t HB = sCanMsg->abData[1];
			if (data_len == 2)
			{
				//if (rid == m_nMotorID) CheckStatus(LB, HB);
			}
		}
		//if (sCanMsg->dwMsgId == GRIPPER_ID1 || sCanMsg->dwMsgId == GRIPPER_ID2) // 0x00) 280620 수정
		//{
		//	if (sCanMsg->abData[0] == 0x69) // CAN_ROBOTRO_RETURNHEADER
		//	{
		//		uint32_t rid = sCanMsg->abData[1];
		//		val1 = ((int)sCanMsg->abData[5] << 8) + sCanMsg->abData[4]; //180704 누락 발견
		//		if (sCanMsg->abData[2] != toq_lock_time_addr && sCanMsg->abData[2] != temp_lock_time_addr && sCanMsg->abData[2] != pos_lock_time_addr) val1 = (short)val1;
		//		str1.Format(_T("%d"), val1);
		//		switch (sCanMsg->abData[2])
		//		{
		//			/* STATUS */
		//		case CAN_ROBOTRO_CMD_TOQ://cur_toq_addr:
		//			if (rid == GRIPPER_ID1) SetDlgItemText(IDC_EDIT_GripSetCur, str1);//m_nSetToq = val1;
		//			if (rid == GRIPPER_ID2) SetDlgItemText(IDC_EDIT_GripSetCur, str1);//m_nSetToq = val1;
		//			break;
		//		case CAN_ROBOTRO_CMD_VEL:
		//			if (rid == GRIPPER_ID1) SetDlgItemText(IDC_EDIT_GripSetVel, str1);// m_nSetVel = val1;
		//			if (rid == GRIPPER_ID2) SetDlgItemText(IDC_EDIT_GripSetVel, str1);//m_nSetVel = val1;
		//			break;
		//		case CAN_ROBOTRO_ACTUAL_POSITION:		//0x10	// GetActualPosition
		//			if (val1 < 0) {
		//				if (rid == GRIPPER_ID1) SetDlgItemText(IDC_STATIC_POS_GUIDE, _T("?"));
		//				if (rid == GRIPPER_ID2) SetDlgItemText(IDC_STATIC_Motor1_Pos, _T("?"));
		//			}
		//			else {
		//				//if (rid == GRIPPER_ID1) SetDlgItemText(IDC_STATIC_POS_GUIDE, str1);
		//				//if (rid == GRIPPER_ID2) SetDlgItemText(IDC_STATIC_Motor1_Pos, str1);
		//				if (rid == GRIPPER_ID1) 
		//					openDistance = 2 * (19.7-6.37+70*cos(70.0883075*3.141592/180+(val1- INIT_POS)*3.141592/2048 ));
		//				str1.Format(_T("%5.2f"), openDistance);
		//				SetDlgItemText(IDC_STATIC_Motor1_Pos, str1);

		//			}
		//			break;
		//		default:
		//			break;
		//		}
		//	}
		//}
		memcpy(&(p_data[0]), &(sCanMsg->abData[0]), 8);
		str1.Format(_T("%x %x %x %x %x %x %x %x %x \r\n"), rid, p_data[0], p_data[1], p_data[2], p_data[3], p_data[4], p_data[5], p_data[6], p_data[7]);
		m_strCanCom.Append(str1);
		UpdateData(FALSE);

	}


	return 0;
}

void CMFC_Ryu_ClientPgrDlg::OnReleasedcaptureSliderGripL(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	CString temp;
	temp.Format(_T("%d"), m_slider_grip_l.GetPos());
	SetDlgItemText(IDC_EDIT_SLIDER_GRIP_L, temp);
	m_nActualPos = m_slider_grip_l.GetPos() * 4096 / 3600 + 2054;

	_canDSP->SetProfileTargetPosition(MOTOR_GRIP_L, m_nActualPos, POSITION_ABSOLUTE);
	_canDSP->EnableOperation(MOTOR_GRIP_L);
	

	*pResult = 0;
}

void CMFC_Ryu_ClientPgrDlg::OnReleasedcaptureSliderGripR(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	CString temp;
	temp.Format(_T("%d"), m_slider_grip_r.GetPos());
	SetDlgItemText(IDC_EDIT_SLIDER_GRIP_R, temp);
	m_nActualPos = 2054 - m_slider_grip_r.GetPos() * 4096 / 3600;
	_canDSP->SetProfileTargetPosition(MOTOR_GRIP_R, m_nActualPos, POSITION_ABSOLUTE);
	_canDSP->EnableOperation(MOTOR_GRIP_R);
	
	*pResult = 0;
}