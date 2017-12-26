/*
 * Copyright (c) 2018 [n/a] info@embeddora.com All rights reserved
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *        * Redistributions of source code must retain the above copyright
 *          notice, this list of conditions and the following disclaimer.
 *        * Redistributions in binary form must reproduce the above copyright
 *          notice, this list of conditions and the following disclaimer in the
 *          documentation and/or other materials provided with the distribution.
 *        * Neither the name of The Linux Foundation nor
 *          the names of its contributors may be used to endorse or promote
 *          products derived from this software without specific prior written
 *          permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NON-INFRINGEMENT ARE DISCLAIMED.    IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Abstract:  
 */


/* Macros <MODULE_LICENSE>, <MODULE_AUTHOR>, <MODULE_DESCRIPTION> */
#include <linux/module.h>

/* Own interface, definitions */
#include "modsim.h"

/* Data structures, mocros */
#include "datastruct.h"


/* Pointer to raw data file */
//+++FILE *fp = NULL;

/* Bufer to store scanned raw data */
char cBuf [LARGE_BUF_SZ];

float fltTM, fltDIn, fltDOut;

/* Pointer to a dynamic structure to store raw data to */
pTimepointType pTimeChain;

/* Aux. var to tell whether it's a first time we output a message for this 'second'  */
int iOldSec;


#if 0
/* Single operation names */
static struct option long_options[] =
{
	/* USB 1.1 on CPE#0 Gate */
	{"CPE#0",  no_argument, 		0,'1'},

	/* USB 2.0 on CPE#1 Gate */
	{"CPE#1",  no_argument, 		0,'2'},

	/* End of array */
	{0, 0, 0, 0}
};
#endif /* 0 */



static int __init modsim_init(void)
{
#if defined(HW_AD53_TEST)

	printk("[%s] %s: NOTIFICATION: doing test of AD53xx controllers. Will hang in this test. \n", __FILE__, __func__ );

	/* Open GPIO ports for output */
	AD5300_Init();

	AD5300_Test();

	/* not reached */
	AD5300_Deinit();

#endif /* (defined(HW_DUMB_TEST) ) */



#if 0

	/* Avoid dafault 0 value */
	iOperation=DO_NO_OP;

	/* Assign program name, requirted for output*/
	strcpy (cArg0, argv[0]);






	/* For each string of Raw Data file */
	while ( ! (feof (fp) ) ) 
	{
		/* Try to scan a whole string into temp. buffer */
		if (0 > fscanf (fp, "%s", cBuf ) )
		{
			/* EOF reached, or can't scan for some other reason (such as NFS conn. is down) */
		}
		else
		{
		/* Aux. buffer to keep results of parsing */
		char * cpTmp = cBuf;
#if defined(DEBUG_DATA)
			printk("[%s] %s: scanned: < %s >\n", __FILE__, __func__, cBuf);
#endif /* (DEBUG_DATA) */


			/* Set default values. MISRA RULE #TODO */
			fltTM = fltDIn = fltDOut = 0.0f;

			/* For each character in aux. buffer */
			while (*cpTmp)

				/* replace all commas with spaces, to let the <scanf()> parse it */
				{ if (',' == *cpTmp) *cpTmp = ' '; cpTmp++; }

#if defined(DEBUG_DATA)
			printk("[%s] %s: changed: < %s >\n", __FILE__, __func__, cBuf);
#endif /* (DEBUG_DATA) */


			/* Find 3 floats separated by spaces in aux. buffer */
			sscanf(cBuf, "%f %f %f,", &fltTM,     &fltDIn,   &fltDOut );

#if defined(DEBUG_DATA)
			printk("[%s] %s: parsed :  <%f> <%f> <%f>\n", __FILE__, __func__, fltTM, fltDIn, fltDOut );
#endif /* (DEBUG_DATA) */

			if (iOldSec!= (int)fltTM)
			{
				iOldSec=(int)fltTM;

				printk("sec: %d; ", iOldSec);

				fflush(stdout);
			}

			/* Attach just scanned data (three floats) to tail of dynamic structure */
			EnrollPoint(&pTimeChain, &fltTM, &fltDIn, &fltDOut, "N/A");
		}
	}

	/* Dispose pointer to Raw Data file */
	fclose(fp);

	/* Open GPIO ports for output */
	AD5300_Init();

	printk("\n[%s] %s: issuing USB-data on Port 'D'\n", __FILE__, __func__);

	/* Process data stored in dynamic structure pointed by 'pTimeChain' */
	ProcessPoints(pTimeChain);

	printk("\n[%s] %s: disposing memory allocations\n", __FILE__, __func__);

	/* Free memory occupied by dynamically stored raw data */
	DeletePoints(&pTimeChain);

	/* Close GPIO-port files, if needed  */
	AD5300_Deinit();

	printk("[%s] %s: done (success) \n", __FILE__, __func__); fflush(stdout);

#endif /* 0 */

	return P_SUCCESS;

} /*  static int __init satm_proc_init(void) */

/* Module removal from a kernel */
static void __exit modsim_exit(void)
{

	printk("'modsim' module removed\n");



} /* void exit satm_proc_exit() */


/* Module insertion into a kernel */
module_init(modsim_init);

/* Module removal from a kernel */
module_exit(modsim_exit);



/* To not 'taint' the kernel let's define 'GNU Public License v2 and more' */
MODULE_LICENSE("GPL and additional rights");

/* Author's badge */
MODULE_AUTHOR("<info@embeddora.com>, [n/a]");

/* For those inquisitive running 'modinfo' to learn what the module is purposed for */
MODULE_DESCRIPTION("Module to perform FOPS in kernel of SITARA ");
