/*
 * Licensee agrees that the example code provided to Licensee has been
 * developed and released by Bosch solely as an example to be used as a
 * potential reference for Licensee´s application development.
 * Fitness and suitability of the example code for any use within Licensee´s
 * applications need to be verified by Licensee on its own authority by taking
 * appropriate state of the art actions and measures (e.g. by means of quality
 * assurance measures).
 * Licensee shall be responsible for conducting the development of its
 * applications as well as integration of parts of the example code into such
 * applications, taking into account the state of the art of technology and any
 * statutory regulations and provisions applicable for such applications.
 * Compliance with the functional system requirements and testing there of
 * (including validation of information/data security aspects and functional
 * safety) and release shall be solely incumbent upon Licensee.
 * For the avoidance of doubt, Licensee shall be responsible and fully liable
 * for the applications and any distribution of such applications into the
 * market.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *     (1) Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *
 *     (2) Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in
 *     the documentation and/or other materials provided with the
 *     distribution.
 *
 *     (3)The name of the author may not be used to
 *     endorse or promote products derived from this software without
 *     specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
 * IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#include "XdkApp.h"
#undef BCDS_MODULE_ID
#define BCDS_MODULE_ID APP_MODULE_MAIN

#include <stdio.h>

#include "BCDS_Basics.h"

#include "BCDS_Assert.h"
#include "BCDS_CmdProcessor.h"
#include "FreeRTOS.h"
#include "task.h"
#include "XdkSystemStartup.h"

#include "XdkHeadTrack.h"

static CmdProcessor_T MainCmdProcessor;

int main(void)
{
	Retcode_T rc = Retcode_Initialize(DefaultErrorHandlingFunc);
	if (RETCODE_OK == rc)
	{
		rc = systemStartup();
	}
	if (RETCODE_OK == rc)
	{
		rc = CmdProcessor_Initialize(&MainCmdProcessor,
				(char*) "MainCmdProcessor", APP_CMD_PROCESSOR_PRIO,
				APP_CMD_PROCESSOR_STACK, APP_CMD_PROCESSOR_QUEUE_LEN);
	}
	if (RETCODE_OK == rc)
	{
		rc = CmdProcessor_Enqueue(&MainCmdProcessor,
				HeadTrack_InitSystem, &MainCmdProcessor, 0);
	}
	if (RETCODE_OK != rc)
	{
		printf("System Startup failed!\n");
		assert(false);
	}
	vTaskStartScheduler();
}
