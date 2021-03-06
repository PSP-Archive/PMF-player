/*
*	PMF Player Test
*	Copyright (c) 2006 by Sorin P. C. <magik@hypermagik.com>
*/
#include <pspsdk.h>
#include <pspkernel.h>
#include <pspdebug.h>

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <malloc.h>

PSP_MODULE_INFO("PMFTest", 0x1000, 1, 1);
PSP_MAIN_THREAD_ATTR(0);

int main_thread(SceSize _argc, ScePVoid _argp)
{
	char *arg = *(char**)_argp;
	char pmfPlayPrx[256] = { 0 };

	if(arg)
	{
		char *p = strrchr(arg, '/');
		if (p != NULL)
		{
			*(p+1) = 0;
			strcpy(pmfPlayPrx, arg);
		}
	}

	strcat(pmfPlayPrx, "pmfPlayer.prx");


	
	pspDebugScreenInit();



	if(pspSdkLoadStartModule("flash0:/kd/audiocodec.prx", PSP_MEMORY_PARTITION_KERNEL) < 0)
	{
		pspDebugScreenPrintf("Error loading module audiocodec.prx\n");
		return -1;
	}

	if(pspSdkLoadStartModule("flash0:/kd/videocodec.prx", PSP_MEMORY_PARTITION_KERNEL) < 0)
	{
		pspDebugScreenPrintf("Error loading module videocodec.prx\n");
		return -1;
	}

	if(pspSdkLoadStartModule("flash0:/kd/mpegbase.prx", PSP_MEMORY_PARTITION_KERNEL) < 0)
	{
		pspDebugScreenPrintf("Error loading module mpegbase.prx\n");
		return -1;
	}

	if(pspSdkLoadStartModule("flash0:/kd/mpeg_vsh.prx", PSP_MEMORY_PARTITION_USER) < 0)
	{
		pspDebugScreenPrintf("Error loading module mpeg_vsh.prx\n");
		return -1;
	}

	char* file = "ms0:/movie.pmf";
	if(pspSdkLoadStartModuleWithArgs(pmfPlayPrx, PSP_MEMORY_PARTITION_USER, 1, &file) < 0)
	{
		pspDebugScreenPrintf("Error loading module pmfPlayer.prx\n");
		return -1;
	}

	sceKernelExitGame();

	return 0;
}

int main(int _argc, char** _argp)
{
	SceUID thread;

	thread = sceKernelCreateThread("main_thread", main_thread, 0x20, 0x10000, 0, NULL);

	if (thread >= 0)
		sceKernelStartThread(thread, sizeof(char*), _argp);	

	return 0;
}
