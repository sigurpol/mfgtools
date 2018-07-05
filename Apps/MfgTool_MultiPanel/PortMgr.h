/*
 * Copyright 2012-2013, Freescale Semiconductor, Inc. All Rights Reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice, this
 * list of conditions and the following disclaimer in the documentation and/or
 * other materials provided with the distribution.
 *
 * Neither the name of the Freescale Semiconductor nor the names of its
 * contributors may be used to endorse or promote products derived from this
 * software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

#pragma once

#include "../MfgToolLib/MfgToolLib_Export.h"
#include "CommonDef.h"
#include <atomic>

class CPortMgr : public CWinThread
{
public:
	CPortMgr(int id);
	virtual ~CPortMgr();

	virtual BOOL InitInstance();
	virtual int ExitInstance();

	BOOL Open();
	void Close();

	void StartDownload();
	void StopDownload();
#ifdef AIRTAME
	// Expose APIs to set/get download status.
	// They are used to quit from the application automatically when all
	// the downloads are terminated and to print the results in output properly.
	enum class DownloadStatus; /* forward declaration */
	void SetDownloadStatus(const DownloadStatus& status);
	DownloadStatus GetDownloadStatus() const { return m_DownloadStatus; }
	// Add an API to retrieve the index
	int GetIndex() const { return m_Index; }
#endif

	TCHAR* GetCurrentDeviceDesc();

public:
	typedef struct
	{
		CString Hub;
		int HubIndex;
		int PortIndex;
		CString DeviceDesc;
		TCHAR DriverLetter;
		BOOL bDeviceConnected;
		MX_DEVICE_CHANGE_EVENT Event;
	}DEV_CHG_NOTIFY;

#ifdef AIRTAME
	// Enum class to store the current status of download
	enum class DownloadStatus
	{
		DOWNLOAD_NOT_STARTED,
		DOWNLOAD_IN_PROGRESS,
		DOWNLOAD_SUCCESS,
		DOWNLOAD_FAILED,
		DOWNLOAD_NOT_CONNECTED
	};
#endif

	int m_Index;
	UINT m_AllCmdSize;
	UINT m_AllPhaseNumbers;

	HANDLE m_hThreadStartEvent;

	int m_PreviousPhaseIndex;
#ifdef AIRTAME
	// Store current download satus, hub index and port
	std::atomic<DownloadStatus> m_DownloadStatus = DownloadStatus::DOWNLOAD_NOT_STARTED;
#endif
};

