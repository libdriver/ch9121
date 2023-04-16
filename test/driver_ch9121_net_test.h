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
 * @file      driver_ch9121_net_test.h
 * @brief     driver ch9121 net test header file
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

#ifndef DRIVER_CH9121_NET_TEST_H
#define DRIVER_CH9121_NET_TEST_H

#include "driver_ch9121_interface.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @addtogroup ch9121_test_driver
 * @{
 */

/**
 * @brief ch9121 net test ip definition
 */
#ifndef CH9121_NET_TEST_IP
    #define CH9121_NET_TEST_IP    {192, 168, 1, 230}          /**< local ip */
#endif

/**
 * @brief ch9121 net test dest ip definition
 */
#ifndef CH9121_NET_TEST_DST_IP
    #define CH9121_NET_TEST_DST_IP    {192, 168, 1, 10}       /**< dest ip */
#endif

/**
 * @brief ch9121 net test subnet mask definition
 */
#ifndef CH9121_NET_TEST_MASK
    #define CH9121_NET_TEST_MASK    {255, 255, 255, 0}        /**< subnet mask */
#endif

/**
 * @brief ch9121 net test gateway definition
 */
#ifndef CH9121_NET_TEST_GATEWAY
    #define CH9121_NET_TEST_GATEWAY    {192, 168, 1, 1}       /**< gateway */
#endif

/**
 * @brief ch9121 net test port definition
 */
#ifndef CH9121_NET_TEST_PORT
    #define CH9121_NET_TEST_PORT        1000                  /**< 1000 */
#endif

/**
 * @brief ch9121 net test dest port definition
 */
#ifndef CH9121_NET_TEST_DST_PORT
    #define CH9121_NET_TEST_DST_PORT    2000                  /**< 2000 */
#endif

/**
 * @brief     net test
 * @param[in] mode is the net mode
 * @param[in] timeout in ms
 * @return    status code
 *            - 0 success
 *            - 1 test failed
 * @note      none
 */
uint8_t ch9121_net_test(ch9121_mode_t mode, uint32_t timeout);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
