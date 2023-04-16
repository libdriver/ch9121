/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 * 
 * The MIT License (MIT)
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
 *
 * @file      driver_ch9121.c
 * @brief     driver ch9121 source file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2023-04-15
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2023/04/15  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#include "driver_ch9121.h"

/**
 * @brief chip information definition
 */
#define CHIP_NAME                 "WCH CH9121"        /**< chip name */
#define MANUFACTURER_NAME         "WCH"               /**< manufacturer name */
#define SUPPLY_VOLTAGE_MIN        2.7f                /**< chip min supply voltage */
#define SUPPLY_VOLTAGE_MAX        3.6f                /**< chip max supply voltage */
#define MAX_CURRENT               190.0f              /**< chip max current */
#define TEMPERATURE_MIN           -40.0f              /**< chip min operating temperature */
#define TEMPERATURE_MAX           85.0f               /**< chip max operating temperature */
#define DRIVER_VERSION            1000                /**< driver version */

/**
 * @brief chip basic command definition
 */
#define CH9121_CMD_CHIP_VERSION                 0x01        /**< get chip version command */
#define CH9121_CMD_RESET                        0x02        /**< reset chip command */
#define CH9121_CMD_SAVE_TO_EEPROM               0x0D        /**< save to eeprom command */
#define CH9121_CMD_RUN_AND_RESET                0x0E        /**< run the config and reset command */
#define CH9121_CMD_EXIT                         0x5E        /**< exit command */
#define CH9121_CMD_DHCP                         0x33        /**< dhcp command */
#define CH9121_CMD_MAC                          0x81        /**< mac command */
#define CH9121_CMD_SET_IP                       0x11        /**< set ip command */
#define CH9121_CMD_SET_NETMASK                  0x12        /**< set netmask command */
#define CH9121_CMD_SET_GATEWAY                  0x13        /**< set gateway command */
#define CH9121_CMD_GET_IP                       0x61        /**< get ip command */
#define CH9121_CMD_GET_NETMASK                  0x62        /**< get netmask command */
#define CH9121_CMD_GET_GATEWAY                  0x63        /**< get gateway command */
#define CH9121_CMD_DISCONNECT                   0x24        /**< set disconnect command */

/**
 * @brief chip port command definition
 */
#define CH9121_CMD_PORT1_GET_STATUS             0x03        /**< check port1 status command */
#define CH9121_CMD_PORT1_SET_MODE               0x10        /**< set port1 mode command */
#define CH9121_CMD_PORT1_SET_PORT               0x14        /**< set port1 port command */
#define CH9121_CMD_PORT1_SET_DST_IP             0x15        /**< set port1 dest ip command */
#define CH9121_CMD_PORT1_SET_DST_PORT           0x16        /**< set port1 dest port command */
#define CH9121_CMD_PORT1_SET_BAUD               0x21        /**< set port1 baud command */
#define CH9121_CMD_PORT1_SET_CONFIG             0x22        /**< set port1 config command */
#define CH9121_CMD_PORT1_SET_TIMEOUT            0x23        /**< set port1 timeout command */
#define CH9121_CMD_PORT1_GET_MODE               0x60        /**< get port1 mode command */
#define CH9121_CMD_PORT1_GET_PORT               0x64        /**< get port1 port command */
#define CH9121_CMD_PORT1_GET_DST_IP             0x65        /**< get port1 dest ip command */
#define CH9121_CMD_PORT1_GET_DST_PORT           0x66        /**< get port1 dest port command */
#define CH9121_CMD_PORT1_GET_BAUD               0x71        /**< get port1 baud command */
#define CH9121_CMD_PORT1_GET_CONFIG             0x72        /**< get port1 config command */
#define CH9121_CMD_PORT1_GET_TIMEOUT            0x73        /**< get port1 timeout command */
#define CH9121_CMD_PORT2_GET_STATUS             0x04        /**< check port2 status command */
#define CH9121_CMD_PORT2_SET_MODE               0x40        /**< set port2 mode command */
#define CH9121_CMD_PORT2_SET_PORT               0x41        /**< set port2 port command */
#define CH9121_CMD_PORT2_SET_DST_IP             0x42        /**< set port2 dest ip command */
#define CH9121_CMD_PORT2_SET_DST_PORT           0x43        /**< set port2 dest port command */
#define CH9121_CMD_PORT2_SET_BAUD               0x44        /**< set port2 baud command */
#define CH9121_CMD_PORT2_SET_CONFIG             0x45        /**< set port2 config command */
#define CH9121_CMD_PORT2_SET_TIMEOUT            0x46        /**< set port2 timeout command */
#define CH9121_CMD_PORT2_GET_MODE               0x90        /**< get port2 mode command */
#define CH9121_CMD_PORT2_GET_PORT               0x91        /**< get port2 port command */
#define CH9121_CMD_PORT2_GET_DST_IP             0x92        /**< get port2 dest ip command */
#define CH9121_CMD_PORT2_GET_DST_PORT           0x93        /**< get port2 dest port command */
#define CH9121_CMD_PORT2_GET_BAUD               0x94        /**< get port2 baud command */
#define CH9121_CMD_PORT2_GET_CONFIG             0x95        /**< get port2 config command */
#define CH9121_CMD_PORT2_GET_TIMEOUT            0x96        /**< get port2 timeout command */

/**
 * @brief chip port extern command definition
 */
#define CH9121_CMD_PORT1_RANDOM_PORT            0x17        /**< set port1 random port command */
#define CH9121_CMD_PORT1_LEN                    0x25        /**< set port1 package length command */
#define CH9121_CMD_PORT1_FLUSH                  0x26        /**< set port1 flush command */
#define CH9121_CMD_PORT1_DOMAIN                 0x34        /**< set port1 domain command */
#define CH9121_CMD_PORT2_ENABLE                 0x39        /**< enable port2 command */
#define CH9121_CMD_PORT2_RANDOM_PORT            0x47        /**< set port2 random port command */
#define CH9121_CMD_PORT2_LEN                    0x48        /**< set port2 package length command */
#define CH9121_CMD_PORT2_FLUSH                  0x49        /**< set port2 flush command */

/**
 * @brief     write and check
 * @param[in] *handle points to a ch9121 handle structure
 * @param[in] *param points to a param buffer
 * @param[in] len is the param len
 * @param[in] pre_delay is the pre delay in ms
 * @param[in] timeout is the wait timeout in ms
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 *            - 2 len is invalid
 *            - 3 error
 *            - 4 timeout
 * @note      none
 */
static uint8_t a_ch9121_write_check(ch9121_handle_t *handle,
                                    uint8_t *param, uint16_t len,
                                    uint16_t pre_delay, uint16_t timeout)
{
    uint16_t t;
    uint8_t res;
    
    if (len > 126)                                            /* check length */
    {
        handle->debug_print("ch9121: len is invalid.\n");     /* len is invalid */
        
        return 2;                                             /* return error */
    }
    
    handle->buf[0] = 0x57;                                    /* set header 0 */
    handle->buf[1] = 0xAB;                                    /* set header 1 */
    memcpy(&handle->buf[2], param, len);                      /* copy param */
    handle->cfg_gpio_write(0);                                /* set low */
    handle->uart_flush();                                     /* uart flush */
    if (handle->uart_write(handle->buf, 2 + len) != 0)        /* write command */
    {
        handle->debug_print("ch9121: write failed.\n");       /* write failed */
        handle->cfg_gpio_write(1);                            /* set high */
        
        return 1;                                             /* return error */
    }
    if (pre_delay != 0)                                       /* check pre_delay */
    {
        handle->delay_ms(pre_delay);                          /* delay pre_delay */
    }
    
    t = timeout / 10;                                         /* 10ms */
    while (t != 0)                                            /* check timeout */
    {
        if (handle->uart_read(&res, 1) == 1)                  /* read data */
        {
            if (res == 0xAA)                                  /* check 0xAA */
            {
                handle->cfg_gpio_write(1);                    /* set high */
                
                return 0;                                     /* success return 0 */
            }
            else
            {
                handle->debug_print("ch9121: error.\n");      /* error */
                handle->cfg_gpio_write(1);                    /* set high */
                
                return 3;                                     /* return error */
            }
        }
        handle->delay_ms(10);                                 /* delay 10ms */
        t--;                                                  /* timeout-- */
    }
    
    handle->debug_print("ch9121: timeout.\n");                /* timeout */
    handle->cfg_gpio_write(1);                                /* set high */
    
    return 4;                                                 /* return error */
}

/**
 * @brief      write and read
 * @param[in]  *handle points to a ch9121 handle structure
 * @param[in]  *param points to a param buffer
 * @param[in]  len is the param len
 * @param[out] *out points to an out buffer
 * @param[in]  out_len is the out len
 * @param[in]  pre_delay is the pre delay in ms
 * @param[in]  timeout is the wait timeout in ms
 * @return     status code
 *             - 0 success
 *             - 1 write failed
 *             - 2 len is invalid
 *             - 3 timeout
 * @note       none
 */
static uint8_t a_ch9121_write_read(ch9121_handle_t *handle,
                                   uint8_t *param, uint16_t len,
                                   uint8_t *out, uint16_t out_len,
                                   uint16_t pre_delay, uint16_t timeout)
{
    uint16_t t;
    uint16_t point;
    
    if (len > 126)                                            /* check length */
    {
        handle->debug_print("ch9121: len is invalid.\n");     /* len is invalid */
        
        return 2;                                             /* return error */
    }
    
    handle->buf[0] = 0x57;                                    /* set header 0 */
    handle->buf[1] = 0xAB;                                    /* set header 1 */
    memcpy(&handle->buf[2], param, len);                      /* copy param */
    handle->cfg_gpio_write(0);                                /* set low */
    handle->uart_flush();                                     /* uart flush */
    if (handle->uart_write(handle->buf, 2 + len) != 0)        /* write command */
    {
        handle->debug_print("ch9121: write failed.\n");       /* write failed */
        handle->cfg_gpio_write(1);                            /* set high */
        
        return 1;                                             /* return error */
    }
    if (pre_delay != 0)                                       /* check pre_delay */
    {
        handle->delay_ms(pre_delay);                          /* delay pre_delay */
    }
    
    point = 0;                                                /* init 0 */
    t = timeout / 10;                                         /* 10ms */
    while (t != 0)                                            /* check timeout */
    {
        uint16_t l;
        
        l = handle->uart_read(&out[point], out_len - point);  /* read data */
        if (l != 0)
        {
            point += l;                                       /* point += l*/
            if (point >= out_len)                             /* check length */
            {
                handle->cfg_gpio_write(1);                    /* set high */
                
                return 0;                                     /* success return 0 */
            }
        }
        handle->delay_ms(10);                                 /* delay 10ms */
        t--;                                                  /* timeout-- */
    }
    
    handle->debug_print("ch9121: timeout.\n");                /* timeout */
    handle->cfg_gpio_write(1);                                /* set high */
    
    return 3;                                                 /* return error */
}

/**
 * @brief      get version
 * @param[in]  *handle points to a ch9121 handle structure
 * @param[out] *version points to a version buffer
 * @return     status code
 *             - 0 success
 *             - 1 get version failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ch9121_get_version(ch9121_handle_t *handle, uint8_t *version)
{
    uint8_t cmd;
    
    if (handle == NULL)                                             /* check handle */
    {
        return 2;                                                   /* return error */
    }
    if (handle->inited != 1)                                        /* check handle initialization */
    {
        return 3;                                                   /* return error */
    }
    
    cmd = CH9121_CMD_CHIP_VERSION;                                  /* set chip version */
    if (a_ch9121_write_read(handle, &cmd, 1, version, 1,
                            CH9121_UART_PRE_DELAY, 1000) != 0)      /* get version */
    {
        return 1;                                                   /* return error */
    }
    
    return 0;                                                       /* success return 0 */
}

/**
 * @brief     reset the chip
 * @param[in] *handle points to a ch9121 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 reset failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ch9121_reset(ch9121_handle_t *handle)
{
    uint8_t cmd;
    
    if (handle == NULL)                                               /* check handle */
    {
        return 2;                                                     /* return error */
    }
    if (handle->inited != 1)                                          /* check handle initialization */
    {
        return 3;                                                     /* return error */
    }
    
    cmd = CH9121_CMD_RESET;                                           /* set reset */
    if (a_ch9121_write_check(handle, &cmd, 1,
                             CH9121_UART_PRE_DELAY, 1000) != 0)       /* reset */
    {
        return 1;                                                     /* return error */
    }
    handle->delay_ms(1000);                                           /* delay 1000ms */
    
    return 0;                                                         /* success return 0 */
}

/**
 * @brief     save to eeprom
 * @param[in] *handle points to a ch9121 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 save to eeprom failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ch9121_save_to_eeprom(ch9121_handle_t *handle)
{
    uint8_t cmd;
    
    if (handle == NULL)                                               /* check handle */
    {
        return 2;                                                     /* return error */
    }
    if (handle->inited != 1)                                          /* check handle initialization */
    {
        return 3;                                                     /* return error */
    }
    
    cmd = CH9121_CMD_SAVE_TO_EEPROM;                                  /* set save to eeprom */
    if (a_ch9121_write_check(handle, &cmd, 1,
                             CH9121_UART_PRE_DELAY, 1000) != 0)       /* save to eeprom */
    {
        return 1;                                                     /* return error */
    }
    
    return 0;                                                         /* success return 0 */
}

/**
 * @brief     config and reset the chip
 * @param[in] *handle points to a ch9121 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 config and reset failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ch9121_config_and_reset(ch9121_handle_t *handle)
{
    uint8_t cmd;
    
    if (handle == NULL)                                               /* check handle */
    {
        return 2;                                                     /* return error */
    }
    if (handle->inited != 1)                                          /* check handle initialization */
    {
        return 3;                                                     /* return error */
    }
    
    cmd = CH9121_CMD_RUN_AND_RESET;                                   /* set run config reset */
    if (a_ch9121_write_check(handle, &cmd, 1,
                             CH9121_UART_PRE_DELAY, 1000) != 0)       /* run config reset */
    {
        return 1;                                                     /* return error */
    }
    handle->delay_ms(1000);                                           /* delay 1000ms */
    
    return 0;                                                         /* success return 0 */
}

/**
 * @brief     exit
 * @param[in] *handle points to a ch9121 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 exit failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ch9121_exit(ch9121_handle_t *handle)
{
    uint8_t cmd;
    
    if (handle == NULL)                                               /* check handle */
    {
        return 2;                                                     /* return error */
    }
    if (handle->inited != 1)                                          /* check handle initialization */
    {
        return 3;                                                     /* return error */
    }
    
    cmd = CH9121_CMD_EXIT;                                            /* set exit */
    if (a_ch9121_write_check(handle, &cmd, 1,
                             CH9121_UART_PRE_DELAY, 1000) != 0)       /* exit */
    {
        return 1;                                                     /* return error */
    }
    
    return 0;                                                         /* success return 0 */
}

/**
 * @brief     enable or disable dhcp
 * @param[in] *handle points to a ch9121 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set dhcp failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ch9121_set_dhcp(ch9121_handle_t *handle, ch9121_bool_t enable)
{
    uint8_t cmd[2];
    
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->inited != 1)                                         /* check handle initialization */
    {
        return 3;                                                    /* return error */
    }
    
    cmd[0] = CH9121_CMD_DHCP;                                        /* set dhcp */
    cmd[1] = enable;                                                 /* set bool */
    if (a_ch9121_write_check(handle, cmd, 2,
                             CH9121_UART_PRE_DELAY, 1000) != 0)      /* dhcp */
    {
        return 1;                                                    /* return error */
    }
    
    return 0;                                                        /* success return 0 */
}

/**
 * @brief      get chip mac
 * @param[in]  *handle points to a ch9121 handle structure
 * @param[out] *mac points to a mac buffer
 * @return     status code
 *             - 0 success
 *             - 1 get mac failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ch9121_get_mac(ch9121_handle_t *handle, uint8_t mac[6])
{
    uint8_t cmd;
    
    if (handle == NULL)                                             /* check handle */
    {
        return 2;                                                   /* return error */
    }
    if (handle->inited != 1)                                        /* check handle initialization */
    {
        return 3;                                                   /* return error */
    }
    
    cmd = CH9121_CMD_MAC;                                           /* set mac */
    if (a_ch9121_write_read(handle, &cmd, 1, mac, 6,
                            CH9121_UART_PRE_DELAY, 1000) != 0)      /* mac*/
    {
        return 1;                                                   /* return error */
    }
    
    return 0;                                                       /* success return 0 */
}

/**
 * @brief      get status
 * @param[in]  *handle points to a ch9121 handle structure
 * @param[in]  port is the set port
 * @param[out] *status points to a status buffer
 * @return     status code
 *             - 0 success
 *             - 1 get status failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ch9121_get_status(ch9121_handle_t *handle, ch9121_port_t port, ch9121_status_t *status)
{
    uint8_t cmd;
    uint8_t param;
    
    if (handle == NULL)                                               /* check handle */
    {
        return 2;                                                     /* return error */
    }
    if (handle->inited != 1)                                          /* check handle initialization */
    {
        return 3;                                                     /* return error */
    }
    
    if (port == CH9121_PORT1)                                         /* port1 */
    {
        cmd = CH9121_CMD_PORT1_GET_STATUS;                            /* get port1 status */
    }
    else                                                              /* port2 */
    {
        cmd = CH9121_CMD_PORT2_GET_STATUS;                            /* get port2 status */
    }
    if (a_ch9121_write_read(handle, &cmd, 1, &param, 1,
                            CH9121_UART_PRE_DELAY, 1000) != 0)        /* get status */
    {
        return 1;                                                     /* return error */
    }
    *status = (ch9121_status_t)(param);                               /* get the status */
    
    return 0;                                                         /* success return 0 */
}

/**
 * @brief     set mode
 * @param[in] *handle points to a ch9121 handle structure
 * @param[in] port is the set port
 * @param[in] mode is the set mode
 * @return    status code
 *            - 0 success
 *            - 1 set mode failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ch9121_set_mode(ch9121_handle_t *handle, ch9121_port_t port, ch9121_mode_t mode)
{
    uint8_t cmd[2];
    
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->inited != 1)                                         /* check handle initialization */
    {
        return 3;                                                    /* return error */
    }
    
    if (port == CH9121_PORT1)                                        /* port1 */
    {
        cmd[0] = CH9121_CMD_PORT1_SET_MODE;                          /* set port1 mode */
    }
    else                                                             /* port2 */
    {
        cmd[0] = CH9121_CMD_PORT2_SET_MODE;                          /* set port2 mode */
    }
    cmd[1] = mode;                                                   /* set mode */
    if (a_ch9121_write_check(handle, cmd, 2,
                             CH9121_UART_PRE_DELAY, 1000) != 0)      /* write mode */
    {
        return 1;                                                    /* return error */
    }
    
    return 0;                                                        /* success return 0 */
}

/**
 * @brief      get mode
 * @param[in]  *handle points to a ch9121 handle structure
 * @param[in]  port is the set port
 * @param[out] *mode points to a mode buffer
 * @return     status code
 *             - 0 success
 *             - 1 get mode failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ch9121_get_mode(ch9121_handle_t *handle, ch9121_port_t port, ch9121_mode_t *mode)
{
    uint8_t cmd;
    uint8_t param;
    
    if (handle == NULL)                                               /* check handle */
    {
        return 2;                                                     /* return error */
    }
    if (handle->inited != 1)                                          /* check handle initialization */
    {
        return 3;                                                     /* return error */
    }
    
    if (port == CH9121_PORT1)                                         /* port1 */
    {
        cmd = CH9121_CMD_PORT1_GET_MODE;                              /* get port1 mode */
    }
    else                                                              /* port2 */
    {
        cmd = CH9121_CMD_PORT2_GET_MODE;                              /* get port2 mode */
    }
    if (a_ch9121_write_read(handle, &cmd, 1, &param, 1,
                            CH9121_UART_PRE_DELAY, 1000) != 0)        /* get mode */
    {
        return 1;                                                     /* return error */
    }
    *mode = (ch9121_mode_t)(param);                                   /* get mode */
    
    return 0;                                                         /* success return 0 */
}

/**
 * @brief     set ip address
 * @param[in] *handle points to a ch9121 handle structure
 * @param[in] *ip points to an ip buffer
 * @return    status code
 *            - 0 success
 *            - 1 set ip failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ch9121_set_ip(ch9121_handle_t *handle, uint8_t ip[4])
{
    uint8_t cmd[5];
    
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->inited != 1)                                         /* check handle initialization */
    {
        return 3;                                                    /* return error */
    }
    
    cmd[0] = CH9121_CMD_SET_IP;                                      /* set ip  */
    cmd[1] = ip[0];                                                  /* set ip[0] */
    cmd[2] = ip[1];                                                  /* set ip[1] */
    cmd[3] = ip[2];                                                  /* set ip[2] */
    cmd[4] = ip[3];                                                  /* set ip[3] */
    if (a_ch9121_write_check(handle, cmd, 5,
                             CH9121_UART_PRE_DELAY, 1000) != 0)      /* write ip */
    {
        return 1;                                                    /* return error */
    }
    
    return 0;                                                        /* success return 0 */
}

/**
 * @brief      get ip address
 * @param[in]  *handle points to a ch9121 handle structure
 * @param[out] *ip points to an ip buffer
 * @return     status code
 *             - 0 success
 *             - 1 get ip failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ch9121_get_ip(ch9121_handle_t *handle, uint8_t ip[4])
{
    uint8_t cmd;
    
    if (handle == NULL)                                               /* check handle */
    {
        return 2;                                                     /* return error */
    }
    if (handle->inited != 1)                                          /* check handle initialization */
    {
        return 3;                                                     /* return error */
    }
    
    cmd = CH9121_CMD_GET_IP;                                          /* get ip */
    if (a_ch9121_write_read(handle, &cmd, 1, ip, 4,
                            CH9121_UART_PRE_DELAY, 1000) != 0)        /* read ip */
    {
        return 1;                                                     /* return error */
    }
    
    return 0;                                                         /* success return 0 */
}

/**
 * @brief     set subnet mask
 * @param[in] *handle points to a ch9121 handle structure
 * @param[in] *mask points to a mask buffer
 * @return    status code
 *            - 0 success
 *            - 1 set subnet mask failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ch9121_set_subnet_mask(ch9121_handle_t *handle, uint8_t mask[4])
{
    uint8_t cmd[5];
    
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->inited != 1)                                         /* check handle initialization */
    {
        return 3;                                                    /* return error */
    }
    
    cmd[0] = CH9121_CMD_SET_NETMASK ;                                /* set sub mask  */
    cmd[1] = mask[0];                                                /* set mask[0] */
    cmd[2] = mask[1];                                                /* set mask[1] */
    cmd[3] = mask[2];                                                /* set mask[2] */
    cmd[4] = mask[3];                                                /* set mask[3] */
    if (a_ch9121_write_check(handle, cmd, 5,
                             CH9121_UART_PRE_DELAY, 1000) != 0)      /* write subnet mask */
    {
        return 1;                                                    /* return error */
    }
    
    return 0;                                                        /* success return 0 */
}

/**
 * @brief      get subnet mask
 * @param[in]  *handle points to a ch9121 handle structure
 * @param[out] *mask points to a mask buffer
 * @return     status code
 *             - 0 success
 *             - 1 get subnet mask failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ch9121_get_subnet_mask(ch9121_handle_t *handle, uint8_t mask[4])
{
    uint8_t cmd;
    
    if (handle == NULL)                                             /* check handle */
    {
        return 2;                                                   /* return error */
    }
    if (handle->inited != 1)                                        /* check handle initialization */
    {
        return 3;                                                   /* return error */
    }
    
    cmd = CH9121_CMD_GET_NETMASK ;                                  /* get mask */
    if (a_ch9121_write_read(handle, &cmd, 1, mask, 4,
                            CH9121_UART_PRE_DELAY, 1000) != 0)      /* read subnet mask */
    {
        return 1;                                                   /* return error */
    }
    
    return 0;                                                       /* success return 0 */
}

/**
 * @brief     set gateway
 * @param[in] *handle points to a ch9121 handle structure
 * @param[in] *ip points to an ip buffer
 * @return    status code
 *            - 0 success
 *            - 1 set gateway failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ch9121_set_gateway(ch9121_handle_t *handle, uint8_t ip[4])
{
    uint8_t cmd[5];
    
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->inited != 1)                                         /* check handle initialization */
    {
        return 3;                                                    /* return error */
    }
    
    cmd[0] = CH9121_CMD_SET_GATEWAY ;                                /* set gateway  */
    cmd[1] = ip[0];                                                  /* set ip[0] */
    cmd[2] = ip[1];                                                  /* set ip[1] */
    cmd[3] = ip[2];                                                  /* set ip[2] */
    cmd[4] = ip[3];                                                  /* set ip[3] */
    if (a_ch9121_write_check(handle, cmd, 5,
                             CH9121_UART_PRE_DELAY, 1000) != 0)      /* write ip */
    {
        return 1;                                                    /* return error */
    }
    
    return 0;                                                        /* success return 0 */
}

/**
 * @brief      get gateway
 * @param[in]  *handle points to a ch9121 handle structure
 * @param[out] *ip points to an ip buffer
 * @return     status code
 *             - 0 success
 *             - 1 get gateway failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ch9121_get_gateway(ch9121_handle_t *handle, uint8_t ip[4])
{
    uint8_t cmd;
    
    if (handle == NULL)                                             /* check handle */
    {
        return 2;                                                   /* return error */
    }
    if (handle->inited != 1)                                        /* check handle initialization */
    {
        return 3;                                                   /* return error */
    }
    
    cmd = CH9121_CMD_GET_GATEWAY;                                   /* get gateway */
    if (a_ch9121_write_read(handle, &cmd, 1, ip, 4,
                            CH9121_UART_PRE_DELAY, 1000) != 0)      /* read gateway */
    {
        return 1;                                                   /* return error */
    }
    
    return 0;                                                       /* success return 0 */
}

/**
 * @brief     set source port
 * @param[in] *handle points to a ch9121 handle structure
 * @param[in] port is the set port
 * @param[in] num is the source port
 * @return    status code
 *            - 0 success
 *            - 1 set source port failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ch9121_set_source_port(ch9121_handle_t *handle, ch9121_port_t port, uint16_t num)
{
    uint8_t cmd[3];
    
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->inited != 1)                                         /* check handle initialization */
    {
        return 3;                                                    /* return error */
    }
    
    if (port == CH9121_PORT1)                                        /* port1 */
    {
        cmd[0] = CH9121_CMD_PORT1_SET_PORT;                          /* set port1 port */
    }
    else                                                             /* port2 */
    {
        cmd[0] = CH9121_CMD_PORT2_SET_PORT;                          /* set port2 port */
    }
    cmd[1] = (num >> 0) & 0xFF;                                      /* set port msb */
    cmd[2] = (num >> 8) & 0xFF;                                      /* set port lsb */
    if (a_ch9121_write_check(handle, cmd, 3,
                             CH9121_UART_PRE_DELAY, 1000) != 0)      /* write port */
    {
        return 1;                                                    /* return error */
    }
    
    return 0;                                                        /* success return 0 */
}

/**
 * @brief      get source port
 * @param[in]  *handle points to a ch9121 handle structure
 * @param[in]  port is the set port
 * @param[out] *num points to a source port buffer
 * @return     status code
 *             - 0 success
 *             - 1 get source port failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ch9121_get_source_port(ch9121_handle_t *handle, ch9121_port_t port, uint16_t *num)
{
    uint8_t cmd;
    uint8_t buf[2];
    
    if (handle == NULL)                                               /* check handle */
    {
        return 2;                                                     /* return error */
    }
    if (handle->inited != 1)                                          /* check handle initialization */
    {
        return 3;                                                     /* return error */
    }
    
    if (port == CH9121_PORT1)                                         /* port1 */
    {
        cmd = CH9121_CMD_PORT1_GET_PORT;                              /* get port1 port */
    }
    else                                                              /* port2 */
    {
        cmd = CH9121_CMD_PORT2_GET_PORT;                              /* get port2 port */
    }
    if (a_ch9121_write_read(handle, &cmd, 1, buf, 2,
                            CH9121_UART_PRE_DELAY, 1000) != 0)        /* get port */
    {
        return 1;                                                     /* return error */
    }
    *num= (uint16_t)((uint16_t)buf[1] << 8 | buf[0]);                 /* get port */
    
    return 0;                                                         /* success return 0 */
}

/**
 * @brief     set dest ip
 * @param[in] *handle points to a ch9121 handle structure
 * @param[in] port is the set port
 * @param[in] *ip points to an ip buffer
 * @return    status code
 *            - 0 success
 *            - 1 set dest ip failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ch9121_set_dest_ip(ch9121_handle_t *handle, ch9121_port_t port, uint8_t ip[4])
{
    uint8_t cmd[5];
    
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->inited != 1)                                         /* check handle initialization */
    {
        return 3;                                                    /* return error */
    }
    
    if (port == CH9121_PORT1)                                        /* port1 */
    {
        cmd[0] = CH9121_CMD_PORT1_SET_DST_IP;                        /* set port1 dest ip */
    }
    else                                                             /* port2 */
    {
        cmd[0] = CH9121_CMD_PORT2_SET_DST_IP;                        /* set port2 dest ip */
    }
    cmd[1] = ip[0];                                                  /* set ip[0] */
    cmd[2] = ip[1];                                                  /* set ip[1] */
    cmd[3] = ip[2];                                                  /* set ip[0] */
    cmd[4] = ip[3];                                                  /* set ip[1] */
    if (a_ch9121_write_check(handle, cmd, 5,
                             CH9121_UART_PRE_DELAY, 1000) != 0)      /* write dest ip */
    {
        return 1;                                                    /* return error */
    }
    
    return 0;                                                        /* success return 0 */
}

/**
 * @brief      get dest ip
 * @param[in]  *handle points to a ch9121 handle structure
 * @param[in]  port is the set port
 * @param[out] *ip points to an ip buffer
 * @return     status code
 *             - 0 success
 *             - 1 get dest ip failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ch9121_get_dest_ip(ch9121_handle_t *handle, ch9121_port_t port, uint8_t ip[4])
{
    uint8_t cmd;
    
    if (handle == NULL)                                               /* check handle */
    {
        return 2;                                                     /* return error */
    }
    if (handle->inited != 1)                                          /* check handle initialization */
    {
        return 3;                                                     /* return error */
    }
    
    if (port == CH9121_PORT1)                                         /* port1 */
    {
        cmd = CH9121_CMD_PORT1_GET_DST_IP;                            /* get port1 dest ip */
    }
    else                                                              /* port2 */
    {
        cmd = CH9121_CMD_PORT2_GET_DST_IP;                            /* get port2 dest ip */
    }
    if (a_ch9121_write_read(handle, &cmd, 1, ip, 4,
                            CH9121_UART_PRE_DELAY, 1000) != 0)        /* get dest ip */
    {
        return 1;                                                     /* return error */
    }
    
    
    return 0;                                                         /* success return 0 */
}

/**
 * @brief     set dest port
 * @param[in] *handle points to a ch9121 handle structure
 * @param[in] port is the set port
 * @param[in] num is the dest port
 * @return    status code
 *            - 0 success
 *            - 1 set dest port failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ch9121_set_dest_port(ch9121_handle_t *handle, ch9121_port_t port, uint16_t num)
{
    uint8_t cmd[3];
    
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->inited != 1)                                         /* check handle initialization */
    {
        return 3;                                                    /* return error */
    }
    
    if (port == CH9121_PORT1)                                        /* port1 */
    {
        cmd[0] = CH9121_CMD_PORT1_SET_DST_PORT;                      /* set port1 dest port */
    }
    else                                                             /* port2 */
    {
        cmd[0] = CH9121_CMD_PORT2_SET_DST_PORT;                      /* set port2 dest port */
    }
    cmd[1] = (num >> 0) & 0xFF;                                      /* set port msb */
    cmd[2] = (num >> 8) & 0xFF;                                      /* set port lsb */
    if (a_ch9121_write_check(handle, cmd, 3,
                             CH9121_UART_PRE_DELAY, 1000) != 0)      /* write dest port */
    {
        return 1;                                                    /* return error */
    }
    
    return 0;                                                        /* success return 0 */
}

/**
 * @brief      get dest port
 * @param[in]  *handle points to a ch9121 handle structure
 * @param[in]  port is the set port
 * @param[out] *num points to a dest port buffer
 * @return     status code
 *             - 0 success
 *             - 1 get dest port failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ch9121_get_dest_port(ch9121_handle_t *handle, ch9121_port_t port, uint16_t *num)
{
    uint8_t cmd;
    uint8_t buf[2];
    
    if (handle == NULL)                                               /* check handle */
    {
        return 2;                                                     /* return error */
    }
    if (handle->inited != 1)                                          /* check handle initialization */
    {
        return 3;                                                     /* return error */
    }
    
    if (port == CH9121_PORT1)                                         /* port1 */
    {
        cmd = CH9121_CMD_PORT1_GET_DST_PORT;                          /* get port1 dest port */
    }
    else                                                              /* port2 */
    {
        cmd = CH9121_CMD_PORT2_GET_DST_PORT;                          /* get port2 dest port */
    }
    if (a_ch9121_write_read(handle, &cmd, 1, buf, 2,
                            CH9121_UART_PRE_DELAY, 1000) != 0)        /* get dest port */
    {
        return 1;                                                     /* return error */
    }
    *num= (uint16_t)((uint16_t)buf[1] << 8 | buf[0]);                 /* get port */
    
    return 0;                                                         /* success return 0 */
}

/**
 * @brief     set uart baud
 * @param[in] *handle points to a ch9121 handle structure
 * @param[in] port is the set port
 * @param[in] baud is the set baud
 * @return    status code
 *            - 0 success
 *            - 1 set uart baud failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ch9121_set_uart_baud(ch9121_handle_t *handle, ch9121_port_t port, uint32_t baud)
{
    uint8_t cmd[5];
    
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->inited != 1)                                         /* check handle initialization */
    {
        return 3;                                                    /* return error */
    }
    
    if (port == CH9121_PORT1)                                        /* port1 */
    {
        cmd[0] = CH9121_CMD_PORT1_SET_BAUD;                          /* set port1 baud */
    }
    else                                                             /* port2 */
    {
        cmd[0] = CH9121_CMD_PORT2_SET_BAUD;                          /* set port2 baud */
    }
    cmd[1] = (baud >> 0) & 0xFF;                                     /* set baud[0] */
    cmd[2] = (baud >> 8) & 0xFF;                                     /* set baud[8] */
    cmd[3] = (baud >> 16) & 0xFF;                                    /* set baud[16] */
    cmd[4] = (baud >> 24) & 0xFF;                                    /* set baud[24] */
    if (a_ch9121_write_check(handle, cmd, 5,
                             CH9121_UART_PRE_DELAY, 1000) != 0)      /* write dest port */
    {
        return 1;                                                    /* return error */
    }
    
    return 0;                                                        /* success return 0 */
}

/**
 * @brief      get uart baud
 * @param[in]  *handle points to a ch9121 handle structure
 * @param[in]  port is the set port
 * @param[out] *baud points to a baud buffer
 * @return     status code
 *             - 0 success
 *             - 1 get uart baud failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ch9121_get_uart_baud(ch9121_handle_t *handle, ch9121_port_t port, uint32_t *baud)
{
    uint8_t cmd;
    uint8_t buf[4];
    
    if (handle == NULL)                                                      /* check handle */
    {
        return 2;                                                            /* return error */
    }
    if (handle->inited != 1)                                                 /* check handle initialization */
    {
        return 3;                                                            /* return error */
    }
    
    if (port == CH9121_PORT1)                                                /* port1 */
    {
        cmd = CH9121_CMD_PORT1_GET_BAUD;                                     /* get port1 baud */
    }
    else                                                                     /* port2 */
    {
        cmd = CH9121_CMD_PORT2_GET_BAUD;                                     /* get port2 baud */
    }
    if (a_ch9121_write_read(handle, &cmd, 1, buf, 4,
                            CH9121_UART_PRE_DELAY, 1000) != 0)               /* get dest port */
    {
        return 1;                                                            /* return error */
    }
    *baud = (uint32_t)(((uint32_t)buf[0] << 0) | ((uint32_t)buf[1] << 8) |
            ((uint32_t)buf[2] << 16) | ((uint32_t)buf[3] << 24));            /* get baud */
    
    return 0;                                                                /* success return 0 */
}

/**
 * @brief     set uart config
 * @param[in] *handle points to a ch9121 handle structure
 * @param[in] port is the set port
 * @param[in] data_bit is the uart data bit
 * @param[in] parity is the uart parity
 * @param[in] stop_bit is the uart stop bit
 * @return    status code
 *            - 0 success
 *            - 1 set uart config failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ch9121_set_uart_config(ch9121_handle_t *handle, ch9121_port_t port, uint8_t data_bit, ch9121_parity_t parity, uint8_t stop_bit)
{
    uint8_t cmd[4];
    
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->inited != 1)                                         /* check handle initialization */
    {
        return 3;                                                    /* return error */
    }
    
    if (port == CH9121_PORT1)                                        /* port1 */
    {
        cmd[0] = CH9121_CMD_PORT1_SET_CONFIG;                        /* set port1 config */
    }
    else                                                             /* port2 */
    {
        cmd[0] = CH9121_CMD_PORT2_SET_CONFIG;                        /* set port2 config */
    }
    cmd[1] = stop_bit;                                               /* set stop bit */
    cmd[2] = parity;                                                 /* set parity */
    cmd[3] = data_bit;                                               /* set data bit */
    if (a_ch9121_write_check(handle, cmd, 4,
                             CH9121_UART_PRE_DELAY, 1000) != 0)      /* write dest port */
    {
        return 1;                                                    /* return error */
    }
    
    return 0;                                                        /* success return 0 */
}

/**
 * @brief      get uart config
 * @param[in]  *handle points to a ch9121 handle structure
 * @param[in]  port is the set port
 * @param[out] *data_bit points to a uart data bit buffer
 * @param[out] *parity points to a uart parity buffer
 * @param[out] *stop_bit points to a uart stop bit buffer
 * @return     status code
 *             - 0 success
 *             - 1 get uart config failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ch9121_get_uart_config(ch9121_handle_t *handle, ch9121_port_t port, uint8_t *data_bit, ch9121_parity_t *parity, uint8_t *stop_bit)
{
    uint8_t cmd;
    uint8_t buf[3];
    
    if (handle == NULL)                                               /* check handle */
    {
        return 2;                                                     /* return error */
    }
    if (handle->inited != 1)                                          /* check handle initialization */
    {
        return 3;                                                     /* return error */
    }
    
    if (port == CH9121_PORT1)                                         /* port1 */
    {
        cmd = CH9121_CMD_PORT1_GET_CONFIG;                            /* get port1 config */
    }
    else                                                              /* port2 */
    {
        cmd = CH9121_CMD_PORT2_GET_CONFIG;                            /* get port2 config */
    }
    if (a_ch9121_write_read(handle, &cmd, 1, buf, 3,
                            CH9121_UART_PRE_DELAY, 1000) != 0)        /* get dest port */
    {
        return 1;                                                     /* return error */
    }
    *stop_bit = buf[0];                                               /* get stop bit */
    *parity = (ch9121_parity_t)buf[1];                                /* get parity */
    *data_bit = buf[2];                                               /* get data bit */
    
    return 0;                                                         /* success return 0 */
}

/**
 * @brief     set uart timeout
 * @param[in] *handle points to a ch9121 handle structure
 * @param[in] port is the set port
 * @param[in] timeout is the uart timeout
 * @return    status code
 *            - 0 success
 *            - 1 set uart timeout failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ch9121_set_uart_timeout(ch9121_handle_t *handle, ch9121_port_t port, uint8_t timeout)
{
    uint8_t cmd[5];
    
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->inited != 1)                                         /* check handle initialization */
    {
        return 3;                                                    /* return error */
    }
    
    if (port == CH9121_PORT1)                                        /* port1 */
    {
        cmd[0] = CH9121_CMD_PORT1_SET_TIMEOUT;                       /* set port1 timeout */
    }
    else                                                             /* port2 */
    {
        cmd[0] = CH9121_CMD_PORT2_SET_TIMEOUT;                       /* set port2 timeout */
    }
    cmd[1] = timeout;                                                /* set timeout */
    cmd[2] = 0x00;                                                   /* set 0x00 */
    cmd[3] = 0x00;                                                   /* set 0x00 */
    cmd[4] = 0x00;                                                   /* set 0x00 */
    if (a_ch9121_write_check(handle, cmd, 5,
                             CH9121_UART_PRE_DELAY, 1000) != 0)      /* write uart timeout */
    {
        return 1;                                                    /* return error */
    }
    
    return 0;                                                        /* success return 0 */
}

/**
 * @brief      get uart timeout
 * @param[in]  *handle points to a ch9121 handle structure
 * @param[in]  port is the set port
 * @param[out] *timeout points to a uart timeout buffer
 * @return     status code
 *             - 0 success
 *             - 1 get uart timeout failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ch9121_get_uart_timeout(ch9121_handle_t *handle, ch9121_port_t port, uint8_t *timeout)
{
    uint8_t cmd;
    
    if (handle == NULL)                                           /* check handle */
    {
        return 2;                                                 /* return error */
    }
    if (handle->inited != 1)                                      /* check handle initialization */
    {
        return 3;                                                 /* return error */
    }
    
    if (port == CH9121_PORT1)                                     /* port1 */
    {
        cmd = CH9121_CMD_PORT1_GET_TIMEOUT;                       /* get port1 timeout */
    }
    else                                                          /* port2 */
    {
        cmd = CH9121_CMD_PORT2_GET_TIMEOUT;                       /* get port2 timeout */
    }
    if (a_ch9121_write_read(handle, &cmd, 1, timeout, 1,
                            CH9121_UART_PRE_DELAY, 1000) != 0)    /* get uart timeout */
    {
        return 1;                                                 /* return error */
    }
    
    return 0;                                                     /* success return 0 */
}

/**
 * @brief      convert the uart timeout to the register raw data
 * @param[in]  *handle points to a ch9121 handle structure
 * @param[in]  ms is the timeout
 * @param[out] *reg points to a register raw buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ch9121_uart_timeout_convert_to_register(ch9121_handle_t *handle, uint16_t ms, uint8_t *reg)
{
    if (handle == NULL)              /* check handle */
    {
        return 2;                    /* return error */
    }
    if (handle->inited != 1)         /* check handle initialization */
    {
        return 3;                    /* return error */
    }
    
    *reg = (uint8_t)(ms / 5);        /* convert real data to register data */
    
    return 0;                        /* success return 0 */
}

/**
 * @brief      convert the register raw data to the offset
 * @param[in]  *handle points to a ch9121 handle structure
 * @param[in]  reg is the register raw data
 * @param[out] *ms points to an ms buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ch9121_uart_timeout_convert_to_data(ch9121_handle_t *handle, uint8_t reg, uint16_t *ms)
{
    if (handle == NULL)             /* check handle */
    {
        return 2;                   /* return error */
    }
    if (handle->inited != 1)        /* check handle initialization */
    {
        return 3;                   /* return error */
    }
    
    *ms = reg * 5;                  /* convert raw data to real data */
    
    return 0;                       /* success return 0 */
}

/**
 * @brief     enable or disable random source port number
 * @param[in] *handle points to a ch9121 handle structure
 * @param[in] port is the set port
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set source port random failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ch9121_set_source_port_random(ch9121_handle_t *handle, ch9121_port_t port, ch9121_bool_t enable)
{
    uint8_t cmd[2];
    
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->inited != 1)                                         /* check handle initialization */
    {
        return 3;                                                    /* return error */
    }
    
    if (port == CH9121_PORT1)                                        /* port1 */
    {
        cmd[0] = CH9121_CMD_PORT1_RANDOM_PORT;                       /* set port1 random */
    }
    else                                                             /* port2 */
    {
        cmd[0] = CH9121_CMD_PORT2_RANDOM_PORT ;                      /* set port2 random */
    }
    cmd[1] = enable;                                                 /* set bool */
    if (a_ch9121_write_check(handle, cmd, 2,
                             CH9121_UART_PRE_DELAY, 1000) != 0)      /* write source port random */
    {
        return 1;                                                    /* return error */
    }
    
    return 0;                                                        /* success return 0 */
}

/**
 * @brief     set uart buffer length
 * @param[in] *handle points to a ch9121 handle structure
 * @param[in] port is the set port
 * @param[in] len is the buffer length
 * @return    status code
 *            - 0 success
 *            - 1 set uart buffer length failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ch9121_set_uart_buffer_length(ch9121_handle_t *handle, ch9121_port_t port, uint32_t len)
{
    uint8_t cmd[5];
    
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->inited != 1)                                         /* check handle initialization */
    {
        return 3;                                                    /* return error */
    }
    
    if (port == CH9121_PORT1)                                        /* port1 */
    {
        cmd[0] = CH9121_CMD_PORT1_LEN;                               /* set port1 uart buffer */
    }
    else                                                             /* port2 */
    {
        cmd[0] = CH9121_CMD_PORT2_LEN ;                              /* set port2 uart buffer */
    }
    cmd[1] = (len >> 0) & 0xFF;                                      /* set len[0] */
    cmd[2] = (len >> 8) & 0xFF;                                      /* set len[8] */
    cmd[3] = (len >> 16) & 0xFF;                                     /* set len[16] */
    cmd[4] = (len >> 24) & 0xFF;                                     /* set len[24] */
    if (a_ch9121_write_check(handle, cmd, 5,
                             CH9121_UART_PRE_DELAY, 1000) != 0)      /* write uart buffer */
    {
        return 1;                                                    /* return error */
    }
    
    return 0;                                                        /* success return 0 */
}

/**
 * @brief     enable or disable uart auto flush
 * @param[in] *handle points to a ch9121 handle structure
 * @param[in] port is the set port
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set uart flush failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ch9121_set_uart_flush(ch9121_handle_t *handle, ch9121_port_t port, ch9121_bool_t enable)
{
    uint8_t cmd[2];
    
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->inited != 1)                                         /* check handle initialization */
    {
        return 3;                                                    /* return error */
    }
    
    if (port == CH9121_PORT1)                                        /* port1 */
    {
        cmd[0] = CH9121_CMD_PORT1_FLUSH;                             /* set port1 flush */
    }
    else                                                             /* port2 */
    {
        cmd[0] = CH9121_CMD_PORT2_FLUSH ;                            /* set port2 flush */
    }
    cmd[1] = enable;                                                 /* set bool */
    if (a_ch9121_write_check(handle, cmd, 2,
                             CH9121_UART_PRE_DELAY, 1000) != 0)      /* write flush */
    {
        return 1;                                                    /* return error */
    }
    
    return 0;                                                        /* success return 0 */
}

/**
 * @brief     enable or disable uart port2
 * @param[in] *handle points to a ch9121 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set port2 failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ch9121_set_port2(ch9121_handle_t *handle, ch9121_bool_t enable)
{
    uint8_t cmd[2];
    
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->inited != 1)                                         /* check handle initialization */
    {
        return 3;                                                    /* return error */
    }
    
    cmd[0] = CH9121_CMD_PORT2_ENABLE;                                /* enable port2 */
    cmd[1] = enable;                                                 /* set bool */
    if (a_ch9121_write_check(handle, cmd, 2,
                             CH9121_UART_PRE_DELAY, 1000) != 0)      /* write enable */
    {
        return 1;                                                    /* return error */
    }
    
    return 0;                                                        /* success return 0 */
}

/**
 * @brief     enable or disable disconnect with no rj45
 * @param[in] *handle points to a ch9121 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set disconnect with no rj45 failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ch9121_set_disconnect_with_no_rj45(ch9121_handle_t *handle, ch9121_bool_t enable)
{
    uint8_t cmd[2];
    
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->inited != 1)                                         /* check handle initialization */
    {
        return 3;                                                    /* return error */
    }
    
    cmd[0] = CH9121_CMD_DISCONNECT;                                  /* set disconnect */
    cmd[1] = enable;                                                 /* set bool */
    if (a_ch9121_write_check(handle, cmd, 2,
                             CH9121_UART_PRE_DELAY, 1000) != 0)      /* write disconnect */
    {
        return 1;                                                    /* return error */
    }
    
    return 0;                                                        /* success return 0 */
}

/**
 * @brief     set chip domain
 * @param[in] *handle points to a ch9121 handle structure
 * @param[in] *domain points to a domain buffer
 * @return    status code
 *            - 0 success
 *            - 1 set domain failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ch9121_set_domain(ch9121_handle_t *handle, char *domain)
{
    uint8_t cmd[29];
    
    if (handle == NULL)                                            /* check handle */
    {
        return 2;                                                  /* return error */
    }
    if (handle->inited != 1)                                       /* check handle initialization */
    {
        return 3;                                                  /* return error */
    }
    if (strlen(domain) > 28)                                       /* check domain */
    {
        handle->debug_print("ch9121: domain > 28.\n");             /* domain > 28 */
        
        return 4;                                                  /* return error */
    }
    
    cmd[0] = CH9121_CMD_PORT1_DOMAIN ;                             /* set domain */
    memcpy(&cmd[1], (uint8_t *)domain, strlen(domain));
    if (a_ch9121_write_check(handle, cmd,
                            (uint16_t)(strlen(domain) + 1),
                             CH9121_UART_PRE_DELAY, 1000) != 0)    /* write domain */
    {
        return 1;                                                  /* return error */
    }
    
    return 0;                                                      /* success return 0 */
}

/**
 * @brief     initialize the chip
 * @param[in] *handle points to a ch9121 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 uart initialization failed
 *            - 2 handle is NULL
 *            - 3 linked functions is NULL
 *            - 4 reset gpio init failed
 *            - 5 cfg gpio init failed
 *            - 6 reset failed
 * @note      none
 */
uint8_t ch9121_init(ch9121_handle_t *handle)
{
    if (handle == NULL)                                                /* check handle */
    {
        return 2;                                                      /* return error */
    }
    if (handle->debug_print == NULL)                                   /* check debug_print */
    {
        return 3;                                                      /* return error */
    }
    if (handle->uart_init == NULL)                                     /* check uart_init */
    {
        handle->debug_print("ch9121: uart_init is null.\n");           /* uart_init is null */
        
        return 3;                                                      /* return error */
    }
    if (handle->uart_deinit == NULL)                                   /* check uart_deinit */
    {
        handle->debug_print("ch9121: uart_deinit is null.\n");         /* uart_deinit is null */
        
        return 3;                                                      /* return error */
    }
    if (handle->uart_read == NULL)                                     /* check uart_read */
    {
        handle->debug_print("ch9121: uart_read is null.\n");           /* uart_read is null */
        
        return 3;                                                      /* return error */
    }
    if (handle->uart_write == NULL)                                    /* check uart_write */
    {
        handle->debug_print("ch9121: uart_write is null.\n");          /* uart_write is null */
        
        return 3;                                                      /* return error */
    } 
    if (handle->uart_flush == NULL)                                    /* check uart_flush */
    {
        handle->debug_print("ch9121: uart_flush is null.\n");          /* uart_flush is null */
        
        return 3;                                                      /* return error */
    }
    if (handle->delay_ms == NULL)                                      /* check delay_ms */
    {
        handle->debug_print("ch9121: delay_ms is null.\n");            /* delay_ms is null */
        
        return 3;                                                      /* return error */
    }
    if (handle->reset_gpio_init == NULL)                               /* check reset_gpio_init */
    {
        handle->debug_print("ch9121: reset_gpio_init is null.\n");     /* reset_gpio_init is null */
        
        return 3;                                                      /* return error */
    }
    if (handle->reset_gpio_deinit == NULL)                             /* check reset_gpio_deinit */
    {
        handle->debug_print("ch9121: reset_gpio_deinit is null.\n");   /* reset_gpio_deinit is null */
        
        return 3;                                                      /* return error */
    }
    if (handle->reset_gpio_write == NULL)                              /* check reset_gpio_write */
    {
        handle->debug_print("ch9121: reset_gpio_write is null.\n");    /* reset_gpio_write is null */
        
        return 3;                                                      /* return error */
    }
    if (handle->cfg_gpio_init == NULL)                                 /* check cfg_gpio_init */
    {
        handle->debug_print("ch9121: cfg_gpio_init is null.\n");       /* cfg_gpio_init is null */
        
        return 3;                                                      /* return error */
    }
    if (handle->cfg_gpio_deinit == NULL)                               /* check cfg_gpio_deinit */
    {
        handle->debug_print("ch9121: cfg_gpio_deinit is null.\n");     /* cfg_gpio_deinit is null */
        
        return 3;                                                      /* return error */
    }
    if (handle->cfg_gpio_write == NULL)                                /* check cfg_gpio_write */
    {
        handle->debug_print("ch9121: cfg_gpio_write is null.\n");      /* cfg_gpio_write is null */
        
        return 3;                                                      /* return error */
    }
    
    if (handle->uart_init() != 0)                                      /* uart init */
    {
        handle->debug_print("ch9121: uart init failed.\n");            /* uart init failed */
        
        return 1;                                                      /* return error */
    }
    if (handle->reset_gpio_init() != 0)                                /* reset gpio init */
    {
        handle->debug_print("ch9121: reset gpio init failed.\n");      /* reset gpio init failed */
        (void)handle->uart_deinit();                                   /* uart deinit */
        
        return 4;                                                      /* return error */
    }
    if (handle->cfg_gpio_init() != 0)                                  /* cfg gpio init */
    {
        handle->debug_print("ch9121: cfg gpio init failed.\n");        /* cfg gpio init failed */
        (void)handle->uart_deinit();                                   /* uart deinit */
        (void)handle->reset_gpio_deinit();                             /* reset gpio deinit */
        
        return 5;                                                      /* return error */
    }
    if (handle->reset_gpio_write(0) != 0)                              /* set low */
    {
        handle->debug_print("ch9121: cfg gpio write failed.\n");       /* cfg gpio write failed */
        (void)handle->uart_deinit();                                   /* uart deinit */
        (void)handle->reset_gpio_deinit();                             /* reset gpio deinit */
        (void)handle->cfg_gpio_deinit();                               /* cfg gpio deinit */
        
        return 6;                                                      /* return error */
    }
    handle->delay_ms(10);                                              /* delay 10ms */
    if (handle->reset_gpio_write(1) != 0)                              /* set high */
    {
        handle->debug_print("ch9121: cfg gpio write failed.\n");       /* cfg gpio write failed */
        (void)handle->uart_deinit();                                   /* uart deinit */
        (void)handle->reset_gpio_deinit();                             /* reset gpio deinit */
        (void)handle->cfg_gpio_deinit();                               /* cfg gpio deinit */
        
        return 6;                                                      /* return error */
    }
    handle->delay_ms(1000);                                            /* delay 1000ms */
    handle->inited = 1;                                                /* flag finish initialization */
    
    return 0;                                                          /* success return 0 */
}

/**
 * @brief     close the chip
 * @param[in] *handle points to a ch9121 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 uart deinit failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 reset failed
 *            - 5 reset gpio deinit failed
 *            - 6 cfg gpio deinit failed
 * @note      none
 */
uint8_t ch9121_deinit(ch9121_handle_t *handle)
{
    uint8_t cmd;
    
    if (handle == NULL)                                               /* check handle */
    {
        return 2;                                                     /* return error */
    }
    if (handle->inited != 1)                                          /* check handle initialization */
    {
        return 3;                                                     /* return error */
    }
    
    cmd = CH9121_CMD_RESET;                                           /* set reset */
    if (a_ch9121_write_check(handle, &cmd, 1,
                             CH9121_UART_PRE_DELAY, 1000) != 0)       /* reset */
    {
        return 4;                                                     /* return error */
    }
    handle->delay_ms(10);                                             /* delay 10ms */
    if (handle->uart_deinit() != 0)                                   /* uart deinit */
    {
        handle->debug_print("ch9121: uart deinit failed.\n");         /* uart deinit failed */
        
        return 1;                                                     /* return error */
    }
    if (handle->reset_gpio_deinit() != 0)                             /* reset gpio deinit */
    {
        handle->debug_print("ch9121: reset gpio deinit failed.\n");   /* reset gpio deinit failed */
        
        return 5;                                                     /* return error */
    }
    if (handle->cfg_gpio_deinit() != 0)                               /* cfg gpio deinit */
    {
        handle->debug_print("ch9121: cfg gpio deinit failed.\n");     /* cfg gpio deinit failed */
        
        return 6;                                                     /* return error */
    }
    
    return 0;                                                         /* success return 0 */
}

/**
 * @brief     write data
 * @param[in] *handle points to a ch9121 handle structure
 * @param[in] *buf points to a data buffer
 * @param[in] len is the data length
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ch9121_write(ch9121_handle_t *handle, uint8_t *buf, uint16_t len)
{
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->inited != 1)                                         /* check handle initialization */
    {
        return 3;                                                    /* return error */
    }
    
    if (handle->cfg_gpio_write(1) != 0)                              /* cfg gpio write */
    {
        handle->debug_print("ch9121: cfg gpio write failed.\n");     /* cfg gpio write failed */
        
        return 1;                                                    /* return error */
    }
    if (handle->uart_write(buf, len) != 0)                           /* uart write */
    {
        handle->debug_print("ch9121:uart write failed.\n");          /* uart write failed */
        
        return 1;                                                    /* return error */
    }
    
    return 0;                                                        /* success return 0 */
}

/**
 * @brief         read data
 * @param[in]     *handle points to a ch9121 handle structure
 * @param[out]    *buf points to a data buffer
 * @param[in,out] *len points to a length buffer
 * @return        status code
 *                - 0 success
 *                - 1 read failed
 *                - 2 handle is NULL
 *                - 3 handle is not initialized
 * @note          none
 */
uint8_t ch9121_read(ch9121_handle_t *handle, uint8_t *buf, uint16_t *len)
{
    uint16_t l;
    
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->inited != 1)                                         /* check handle initialization */
    {
        return 3;                                                    /* return error */
    }
    
    if (handle->cfg_gpio_write(1) != 0)                              /* cfg gpio write */
    {
        handle->debug_print("ch9121: cfg gpio write failed.\n");     /* cfg gpio write failed */
        
        return 1;                                                    /* return error */
    }
    l = handle->uart_read(buf, *len);                                /* uart read */
    *len = l;                                                        /* set data */
    
    return 0;                                                        /* success return 0 */
}

/**
 * @brief      set command
 * @param[in]  *handle points to a ch9121 handle structure
 * @param[in]  *param points to a param buffer
 * @param[in]  len is the param len
 * @param[out] *out points to an out buffer
 * @param[in]  out_len is the out len
 * @param[in]  pre_delay is the pre delay in ms
 * @param[in]  timeout is the wait timeout in ms
 * @return     status code
 *             - 0 success
 *             - 1 set command failed
 *             - 2 handle is NULL
 *             - 3 linked functions is NULL
 * @note       none
 */
uint8_t ch9121_set_command(ch9121_handle_t *handle,
                           uint8_t *param, uint16_t len,
                           uint8_t *out, uint16_t out_len,
                           uint16_t pre_delay, uint16_t timeout)
{
    if (handle == NULL)                                      /* check handle */
    {
        return 2;                                            /* return error */
    }
    if (handle->inited != 1)                                 /* check handle initialization */
    {
        return 3;                                            /* return error */
    }
    
    if (a_ch9121_write_read(handle, param, len,
                            out, out_len,
                            pre_delay, timeout) != 0)        /* set command */
    {
        return 1;                                            /* return error */
    }
    
    return 0;                                                /* success return 0 */
}

/**
 * @brief      get chip's information
 * @param[out] *info points to a ch9121 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t ch9121_info(ch9121_info_t *info)
{
    if (info == NULL)                                              /* check handle */
    {
        return 2;                                                  /* return error */
    }
    
    memset(info, 0, sizeof(ch9121_info_t));                        /* initialize ch9121 info structure */
    strncpy(info->chip_name, CHIP_NAME, 32);                       /* copy chip name */
    strncpy(info->manufacturer_name, MANUFACTURER_NAME, 32);       /* copy manufacturer name */
    strncpy(info->interface, "UART", 8);                           /* copy interface name */
    info->supply_voltage_min_v = SUPPLY_VOLTAGE_MIN;               /* set minimal supply voltage */
    info->supply_voltage_max_v = SUPPLY_VOLTAGE_MAX;               /* set maximum supply voltage */
    info->max_current_ma = MAX_CURRENT;                            /* set maximum current */
    info->temperature_max = TEMPERATURE_MAX;                       /* set minimal temperature */
    info->temperature_min = TEMPERATURE_MIN;                       /* set maximum temperature */
    info->driver_version = DRIVER_VERSION;                         /* set driver version */
    
    return 0;                                                      /* success return 0 */
}
