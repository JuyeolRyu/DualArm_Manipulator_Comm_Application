#include "stdafx.h"
#include "CanOpenComm.h"

int g_CanID;
UINT16 g_CanBitRate0;
UINT16 g_CanBitRate1;

#define wRxFifoSize			4096
#define wRxThreshold		1
#define wTxFifoSize			2048
#define wTxThreshold		1

CanOpenComm::CanOpenComm(void)
{
};



CanOpenComm::~CanOpenComm(void)
{
}

HANDLE CanOpenComm::CanOpenConnect(uint32_t dwCanNo)
{
	HANDLE			hEnum;   // enumerator handle
	VCIDEVICEINFO	sInfo;   // device info
	HRESULT			hResult;

	//UpdateData( true );

	hResult = vciEnumDeviceOpen(&hEnum);

	// retrieve information about the first device within the device list
	if (hResult == VCI_OK)
	{
		hResult = vciEnumDeviceNext(hEnum, &sInfo);
	}
	// close the device list (no longer needed)
	vciEnumDeviceClose(hEnum);

	// open the device
	if (hResult == VCI_OK)
	{
		hResult = vciDeviceOpen(sInfo.VciObjectId, &hDevice);
	}
	else 
	{
		MessageBox(NULL,TEXT("Can't open a device !"),
			TEXT("kArm2"), MB_OK | MB_ICONSTOP);
		return NULL;
	}

	// create a message channel
	if (hDevice != NULL)
	{
		// create and initialize a message channel
		hResult = canChannelOpen(hDevice, dwCanNo, FALSE, &hCanChn);
		// initialize the message channel
		if (hResult == VCI_OK)
		{
			/*UINT16 wRxFifoSize  = 2048;
			UINT16 wRxThreshold = 1;
			UINT16 wTxFifoSize  = 2048;
			UINT16 wTxThreshold = 1;*/


			hResult = canChannelInitialize( hCanChn,
				wRxFifoSize, wRxThreshold,
				wTxFifoSize, wTxThreshold);
		}

		// activate the CAN channel
		if (hResult == VCI_OK)
		{
			hResult = canChannelActivate(hCanChn, TRUE);
		}

		// open the CAN controller
		if (hResult == VCI_OK)
		{
			hResult = canControlOpen(hDevice, dwCanNo, &hCanCtl);
			// this function fails if the controller is in use by another application.
		}

		// initialize the CAN controller
		if (hResult == VCI_OK)
		{ 
			hResult = canControlInitialize(hCanCtl, CAN_OPMODE_STANDARD,
				g_CanBitRate0, g_CanBitRate1);							//20180612 ¼öÁ¤
			//				CAN_BT0_1000KB, CAN_BT1_1000KB);

		}
		// set the acceptance filter
		if (hResult == VCI_OK)
		{ 
			hResult = canControlSetAccFilter( hCanCtl, CAN_FILTER_STD,
				CAN_ACC_CODE_ALL, CAN_ACC_MASK_ALL);
		}

		// start the CAN controller
		if (hResult == VCI_OK)
		{
			hResult = canControlStart(hCanCtl, TRUE);
		}

	}
	else
	{
		hResult = VCI_E_INVHANDLE;
	}



	return hCanChn;
}

int CanOpenComm::CanOpenDisConnect()
{
	HRESULT hResult;
	hResult = canControlClose(hCanCtl);
	if (hResult == VCI_OK ) hResult = canChannelClose(hCanChn);
	if (hResult == VCI_OK ) hResult = vciDeviceClose(hDevice);
	return 0;
}