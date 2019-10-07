/**
 * \file nwkDataReq.h
 *
 * \brief NWK_DataReq() interface
 *
 * Copyright (C) 2014-2015 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 *
 */

/*
 * Copyright (c) 2014-2015 Atmel Corporation. All rights reserved.
 *
 * Licensed under Atmel's Limited License Agreement --> EULA.txt
 */

#ifndef _NWK_DATA_REQ_H_
#define _NWK_DATA_REQ_H_

#ifdef __cplusplus
extern "C" {
#endif

/*- Includes ---------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>
#include <sys\sysTypes.h>
#include <sys\sysConfig.h>

/*- Definitions ------------------------------------------------------------*/

#define FRAME_SUBTYPE_LL_BEACON				0x00
#define FRAME_SUBTYPE_LL_DATA					0x01
#define FRAME_SUBTYPE_LL_ACK					0x02
#define FRAME_SUBTYPE_LL_MAC_COMMAND	0x03

#define OPTIONS_CLEAR 0x0000

/*- Types ------------------------------------------------------------------*/

typedef struct NWK_DataReq_t {
	/* service fields */
	void *next;
	void *frame;
	uint8_t state;

	/* request parameters */
	uint16_t dstAddr;
	uint8_t dstEndpoint;
	uint8_t srcEndpoint;
	uint16_t options;
#ifdef NWK_ENABLE_MULTICAST
	uint8_t memberRadius;
	uint8_t nonMemberRadius;
#endif
	uint8_t *data;
	uint8_t size;
	void (*confirm)(struct NWK_DataReq_t *req);

	/* confirmation parameters */
	uint8_t status;
	uint8_t control;
} NWK_DataReq_t;

typedef struct DiscoveryResponse {
	uint8_t identifier;
	uint16_t macAddr;
	struct{
		uint8_t tsDuration	 : 7;
		uint8_t dirIndicator : 1;
	}ts_dir;
} DiscoveryResponse;

typedef struct ConfigStatus {
	uint8_t identifier;
	uint8_t s_macAddr;
	uint8_t assTimeSlot;
	uint16_t macAddr;
	struct{
		uint8_t tsDuration 		: 7;
		uint8_t dirIndicator 	: 1;
	}ts_dir;
} ConfigStatus;

typedef struct ConfigParms {
	uint8_t identifier;
	uint8_t s_macAddr;
	uint8_t tx_channel;
	uint8_t assTimeSlot;
	uint16_t macAddr;
	struct{
		uint8_t tsDuration	: 7;
		uint8_t mgmtFrames 	: 1;
	} conf;
} ConfigParams;


/*- Prototypes -------------------------------------------------------------*/
void NWK_DataReq(NWK_DataReq_t *req);

void nwkDataReqInit(void);
void nwkDataReqTaskHandler(void);

#ifdef __cplusplus
}
#endif

#endif /* _NWK_DATA_REQ_H_ */
