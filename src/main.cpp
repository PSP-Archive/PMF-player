/*
 *	PMF Player Module
 *	Copyright (c) 2006 by Sorin P. C. <magik@hypermagik.com>
 */
#include <pspkernel.h>

#include <stdio.h>
#include <malloc.h>
#include <string.h>

#include "pmfplayer.h"

PSP_MODULE_INFO(pmfPlayer, 0, 1, 1);

int main_thread(SceSize _argc, void* _argp)
{

	CPMFPlayer *MpegDecoder = new CPMFPlayer();

	if(MpegDecoder->Initialize() < 0)
	{
		pspDebugScreenInit();
		pspDebugScreenPrintf(MpegDecoder->GetLastError());
		sceKernelDelayThread(5000000);
		return -1;
	}

	if(MpegDecoder->Load((char*)_argp) < 0)
	{
		pspDebugScreenInit();
		pspDebugScreenPrintf(MpegDecoder->GetLastError());
		sceKernelDelayThread(5000000);
		return -1;
	}

	if(MpegDecoder->Play() < 0)
	{
		pspDebugScreenInit();
		pspDebugScreenPrintf(MpegDecoder->GetLastError());
		sceKernelDelayThread(5000000);
		return -1;
	}

	MpegDecoder->Shutdown();

	return 0;
}

extern "C" int module_start(SceSize _argc, char* _argp)
{
	char* arg = _argp + strlen(_argp) + 1;

	SceUID T = sceKernelCreateThread("pmfplayer_thread", main_thread, 0x20, 0xFA0, THREAD_ATTR_USER, NULL);

	sceKernelStartThread(T, strlen(arg)+1, arg);

	sceKernelWaitThreadEnd(T, 0);

	return 0;
}
