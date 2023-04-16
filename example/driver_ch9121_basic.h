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
 * @file      driver_ch9121_basic.h
 * @brief     driver ch9121 basic header file
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

#ifndef DRIVER_CH9121_BASIC_H
#define DRIVER_CH9121_BASIC_H

#include "driver_ch9121_interface.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup ch9121_example_driver ch9121 example driver function
 * @brief    ch9121 example driver modules
 * @ingroup  ch9121_driver
 * @{
 */

/**
 * @brief ch9121 basic example default definition
 */
#define CH9121_BASIC_DEFAULT_DHCP                       CH9121_BOOL_FALSE        /**< disable dhcp */
#define CH9121_BASIC_DEFAULT_UART_PORT                  9600                     /**< 9600 */
#define CH9121_BASIC_DEFAULT_UART_DATA_BIT              8                        /**< 8 bit */
#define CH9121_BASIC_DEFAULT_UART_STOP_BIT              1                        /**< 1 bit */
#define CH9121_BASIC_DEFAULT_UART_PARITY                CH9121_PARITY_NONE       /**< no parity */
#define CH9121_BASIC_DEFAULT_UART_TIMEOUT               10                       /**< 10ms */
#define CH9121_BASIC_DEFAULT_UART_SOURCE_PORT_RANDOM    CH9121_BOOL_FALSE        /**< disable random */
#define CH9121_BASIC_DEFAULT_UART_BUFFER_LENGTH         1024                     /**< 1024 bytes */
#define CH9121_BASIC_DEFAULT_UART_FLUSH                 CH9121_BOOL_FALSE        /**< disable flush */
#define CH9121_BASIC_DEFAULT_UART_PORT2                 CH9121_BOOL_FALSE        /**< disable uart2 */
#define CH9121_BASIC_DEFAULT_DISCONNECT_WITH_NO_RJ45    CH9121_BOOL_TRUE         /**< enable */

/**
 * @brief  basic example init
 * @return status code
 *         - 0 success
 *         - 1 init failed
 * @note   none
 */
uint8_t ch9121_basic_init(void);

/**
 * @brief  basic example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t ch9121_basic_deinit(void);

/**
 * @brief         basic example read data
 * @param[out]    *buf points to a data buffer
 * @param[in,out] *len points to a length buffer
 * @return        status code
 *                - 0 success
 *                - 1 read failed
 * @note          none
 */
uint8_t ch9121_basic_read(uint8_t *buf, uint16_t *len);

/**
 * @brief     basic example write data
 * @param[in] *buf points to a data buffer
 * @param[in] len is the data length
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
uint8_t ch9121_basic_write(uint8_t *buf, uint16_t len);

/**
 * @brief     basic example config
 * @param[in] uart_port is the uart port
 * @param[in] mode is the set mode
 * @param[in] *ip points to an ip buffer
 * @param[in] port is the local port
 * @param[in] *mask points to a mask buffer
 * @param[in] *gateway points to a gateway buffer
 * @param[in] *dest_ip points to a dest ip buffer
 * @param[in] dest_port is the dest port
 * @return    status code
 *            - 0 success
 *            - 1 config failed
 * @note      none
 */
uint8_t ch9121_basic_config(ch9121_port_t uart_port, ch9121_mode_t mode,
                            uint8_t ip[4], uint16_t port, 
                            uint8_t mask[4], uint8_t gateway[4],
                            uint8_t dest_ip[4], uint16_t dest_port);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
