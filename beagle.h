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

#ifndef _BEAGLE_H_
#define _BEAGLE_H_

#define NUM_PORTS	6

#if defined(SH_FOPS)

	/* Definitions for shell file operatoins */

	/* CPE#1 */
	#define _30 "30"
	#define _31 "31"
	#define _48 "48"
	#define _5 "5"
	#define _3 "3"
	#define _49 "49"

	/* CPE#2 */
	#define _117 "117"
	#define _115 "115"
	#define _60 "60"
	#define _50 "50"
	#define _51 "51"
	#define _4 "4"

	/* CPE#3 */
	#define _2 "2"
	#define _15 "15"
	#define _14 "14"
	#define _112 "112"
	#define _66 "66"
	#define _69 "69"

	/* CPE#4 */
	#define _45 "45"
	#define _23 "23"
	#define _47 "47"
	#define _27 "27"
	#define _22 "22"
	#define _67 "67"

	/* CPE#5*/
	#define _68 "68"
	#define _44 "44"
	#define _26 "26"
	#define _46 "46"
	#define _65 "65"
	#define _61 "61"
#else
	/* Definitions for GLIBC API file operations */

	/* CPE#1 */
	FILE * _30;
	FILE * _31;
	FILE * _48;
	FILE * _5;
	FILE * _3;
	FILE * _49;

	/* CPE#2 */
	FILE * _117;
	FILE * _115;
	FILE * _60;
	FILE * _50;
	FILE * _51;
	FILE * _4;

	/* CPE#3 */
	FILE * _2;
	FILE * _15;
	FILE * _14;
	FILE * _112;
	FILE * _66;
	FILE * _69;

	/* CPE#4 */
	FILE * _45;
	FILE * _23;
	FILE * _47;
	FILE * _27;
	FILE * _22;
	FILE * _67;

	/* CPE#5 */
	FILE * _68;
	FILE * _44;
	FILE * _26;
	FILE * _46;
	FILE * _65;
	FILE * _61;

#endif /* (SH_FOPS) */


#if defined(SH_FOPS)
typedef void (*GPIOHandler)(char *);
typedef char * GPIOTarget;
#else
typedef void (*GPIOHandler)(FILE *);
typedef FILE * GPIOTarget;
#endif

FILE * GPIO_VALUE_FILES[30];

#if defined(SH_FOPS)

/* GPIOs connected to SCKL with 'white' wire */
GPIOTarget SCLK_i_W[NUM_PORTS] = {_30, _117, _2, _45, _68, NULL};
/* GPIOs connected to MOSI with 'white' wire */
GPIOTarget MOSI_i_W[NUM_PORTS] = {_31, _115, _15, _23, _44, NULL};
/* GPIOs connected to SYNC with 'white' wire */
GPIOTarget SYNC_i_W[NUM_PORTS] = {_48, _60, _14, _47, _26, NULL};
/* GPIOs connected to SCKL with 'green' wire */
GPIOTarget SCLK_i_G[NUM_PORTS] = {_5, _50, _112, _27, _46, NULL};
/* GPIOs connected to MOSI with 'green' wire */
GPIOTarget MOSI_i_G[NUM_PORTS] = {_3, _51, _66, _22, _65, NULL};
/* GPIOs connected to SYNC with 'green' wire */
GPIOTarget SYNC_i_G[NUM_PORTS] = {_49, _4, _69, _67, _61, NULL};

#else

/* GPIOs connected to SCKL with 'white' wire */
GPIOTarget SCLK_i_W[NUM_PORTS];
/* GPIOs connected to MOSI with 'white' wire */
GPIOTarget MOSI_i_W[NUM_PORTS];
/* GPIOs connected to SYNC with 'white' wire */
GPIOTarget SYNC_i_W[NUM_PORTS];
/* GPIOs connected to SCKL with 'green' wire */
GPIOTarget SCLK_i_G[NUM_PORTS];
/* GPIOs connected to MOSI with 'green' wire */
GPIOTarget MOSI_i_G[NUM_PORTS];
/* GPIOs connected to SYNC with 'green' wire */
GPIOTarget SYNC_i_G[NUM_PORTS];

/* TODO: rem as workaround */
GPIOTarget __fpWRKND[NUM_PORTS];  

#endif /* defined(SH_FOPS) */


/* Toggle down SCKL on 'white' converter */
#define _i_SCLK_LO_W(x)		OffGPIO(x)
/* Toggle up SCKL on 'white' converter */
#define _i_SCLK_HI_W(x)		OnGPIO(x)
/* Toggle down MOSI on 'white' converter */
#define _i_MOSI_LO_W(x)		OffGPIO(x)
/* Toggle up MOSI on 'white' converter */
#define _i_MOSI_HI_W(x)		OnGPIO(x)
/* Activate 'white' converter */
#define _i_AD5300_ACT_W(x) 	OffGPIO(x)
/* Deactivate 'white' converter */
#define _i_AD5300_DEACT_W(x) 	OnGPIO(x)

/* Toggle down SCKL on 'green' converter */
#define _i_SCLK_LO_G(x)		OffGPIO(x)
/* Toggle up SCKL on 'green' converter */
#define _i_SCLK_HI_G(x)		OnGPIO(x)
/* Toggle down MOSI on 'green' converter */
#define _i_MOSI_LO_G(x)		OffGPIO(x)
/* Toggle up MOSI on 'green' converter */
#define _i_MOSI_HI_G(x)		OnGPIO(x)
/* Activate 'green' converter */
#define _i_AD5300_ACT_G(x) 	OffGPIO(x)
/* Deactivate 'green' converter */
#define _i_AD5300_DEACT_G(x) 	OnGPIO(x)


#endif /* _BEAGLE_H_ */
