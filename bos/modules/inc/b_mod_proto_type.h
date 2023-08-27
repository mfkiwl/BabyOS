/**
 *!
 * \file        b_mod_proto_type.h
 * \version     v0.1.0
 * \date        2020/03/15
 * \author      Bean(notrynohigh@outlook.com)
 *******************************************************************************
 * @attention
 *
 * Copyright (c) 2020 Bean
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *******************************************************************************
 */
#ifndef __B_MOD_PROTO_TYPE_H__
#define __B_MOD_PROTO_TYPE_H__

#ifdef __cplusplus
extern "C" {
#endif

/*Includes ----------------------------------------------*/
#include <stdint.h>

#include "b_section.h"

typedef enum
{
    B_XMODEM_CMD_START,
    B_XMODEM_CMD_STOP,
    B_YMODEM_CMD_START,
    B_YMODEM_CMD_STOP,
    B_MODBUS_CMD_READ_REG,
    B_MODBUS_CMD_WRITE_REG,
    B_PROTO_CMD_NUMBER,
} bProtoCmd_t;

typedef enum
{
    B_PROTO_INFO_DEVICE_ID,  // 获取设备id
    B_PROTO_INFO_NUMBER,
} bProtoInfoType_t;

typedef union
{
    struct
    {
        uint8_t  cmd;
        uint8_t *param;
        uint16_t param_len;
    } _bos;
    struct
    {
        uint8_t  seq;
        uint8_t *param;
        uint16_t param_len;
    } _xmodem;

    struct
    {
        uint8_t  seq;
        uint8_t *param;
        uint16_t param_len;
    } _ymodem;
    struct
    {
        uint8_t   slave_id;
        uint8_t   func_code;
        uint16_t  base_reg;
        uint16_t  reg_num;
        uint16_t *reg_value;
    } _modbus;
} bProtoCbParam_t;

typedef int (*bProtoCallback_t)(bProtoCbParam_t *param);
typedef int (*bProtoParse_t)(void *attr, uint8_t *in, uint16_t i_len, uint8_t *out, uint16_t o_len);
typedef int (*bProtoPackage_t)(void *attr, bProtoCmd_t cmd, uint8_t *buf, uint16_t buf_len);
typedef int (*bProtoGetInfo_t)(bProtoInfoType_t type, uint8_t *buf, uint16_t buf_len);

typedef struct
{
    bProtoParse_t    parse;
    bProtoPackage_t  package;
    bProtoGetInfo_t  get_info;
    bProtoCallback_t callback;
} bProtocolAttr_t;

typedef struct
{
    const char     *name;
    bProtoParse_t   parse;
    bProtoPackage_t package;
} bProtocolInstance_t;

#define bPROTOCOL_REG_INSTANCE(proto_name, _parse, _package)                                     \
    bSECTION_ITEM_REGISTER_FLASH(b_srv_protocol, bProtocolInstance_t, CONCAT_2(do_, _parse)) = { \
        .name = proto_name, .parse = _parse, .package = _package};

#ifdef __cplusplus
}
#endif

#endif

/************************ Copyright (c) 2019 Bean *****END OF FILE****/
