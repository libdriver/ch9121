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
 * @file      driver_ch9121.h
 * @brief     driver ch9121 header file
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

#ifndef DRIVER_CH9121_H
#define DRIVER_CH9121_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup ch9121_driver ch9121 driver function
 * @brief    ch9121 driver modules
 * @{
 */

/**
 * @addtogroup ch9121_base_driver
 * @{
 */

/**
 * @brief ch9121 uart pre delay definition
 */
#ifndef CH9121_UART_PRE_DELAY
    #define CH9121_UART_PRE_DELAY    50        /**< 50ms */
#endif

/**
 * @brief ch9121 port enumeration definition
 */
typedef enum
{
    CH9121_PORT1 = 0x00,        /**< port1 */
    CH9121_PORT2 = 0x01,        /**< port2 */
} ch9121_port_t;

/**
 * @brief ch9121 bool enumeration definition
 */
typedef enum
{
    CH9121_BOOL_FALSE = 0x00,        /**< false */
    CH9121_BOOL_TRUE  = 0x01,        /**< true */
} ch9121_bool_t;

/**
 * @brief ch9121 status enumeration definition
 */
typedef enum
{
    CH9121_STATUS_DISCONNECT = 0x00,        /**< disconnect */
    CH9121_STATUS_CONNECT    = 0x01,        /**< connect */
} ch9121_status_t;

/**
 * @brief ch9121 mode enumeration definition
 */
typedef enum
{
    CH9121_MODE_TCP_SERVER = 0x00,        /**< tcp server */
    CH9121_MODE_TCP_CLIENT = 0x01,        /**< tcp client */
    CH9121_MODE_UDP_SERVER = 0x02,        /**< udp server */
    CH9121_MODE_UDP_CLIENT = 0x03,        /**< udp client */
} ch9121_mode_t;

/**
 * @brief ch9121 parity enumeration definition
 */
typedef enum
{
    CH9121_PARITY_EVEN  = 0x00,        /**< even parity */
    CH9121_PARITY_ODD   = 0x01,        /**< odd parity */
    CH9121_PARITY_MARK  = 0x02,        /**< mark */
    CH9121_PARITY_SPACE = 0x03,        /**< space */
    CH9121_PARITY_NONE  = 0x04,        /**< none */
} ch9121_parity_t;

/**
 * @brief ch9121 handle structure definition
 */
typedef struct ch9121_handle_s
{
    uint8_t (*uart_init)(void);                               /**< point to a uart_init function address */
    uint8_t (*uart_deinit)(void);                             /**< point to a uart_deinit function address */
    uint16_t (*uart_read)(uint8_t *buf, uint16_t len);        /**< point to a uart_read function address */
    uint8_t (*uart_flush)(void);                              /**< point to a uart_flush function address */
    uint8_t (*uart_write)(uint8_t *buf, uint16_t len);        /**< point to a uart_write function address */
    uint8_t (*reset_gpio_init)(void);                         /**< point to a reset_gpio_init function address */
    uint8_t (*reset_gpio_deinit)(void);                       /**< point to a reset_gpio_deinit function address */
    uint8_t (*reset_gpio_write)(uint8_t data);                /**< point to a reset_gpio_write function address */
    uint8_t (*cfg_gpio_init)(void);                           /**< point to a cfg_gpio_init function address */
    uint8_t (*cfg_gpio_deinit)(void);                         /**< point to a cfg_gpio_deinit function address */
    uint8_t (*cfg_gpio_write)(uint8_t data);                  /**< point to a cfg_gpio_write function address */
    void (*delay_ms)(uint32_t ms);                            /**< point to a delay_ms function address */
    void (*debug_print)(const char *const fmt, ...);          /**< point to a debug_print function address */
    uint8_t inited;                                           /**< inited flag */
    uint8_t buf[128];                                         /**< inner buffer */
} ch9121_handle_t;

/**
 * @brief ch9121 information structure definition
 */
typedef struct ch9121_info_s
{
    char chip_name[32];                /**< chip name */
    char manufacturer_name[32];        /**< manufacturer name */
    char interface[8];                 /**< chip interface name */
    float supply_voltage_min_v;        /**< chip min supply voltage */
    float supply_voltage_max_v;        /**< chip max supply voltage */
    float max_current_ma;              /**< chip max current */
    float temperature_min;             /**< chip min operating temperature */
    float temperature_max;             /**< chip max operating temperature */
    uint32_t driver_version;           /**< driver version */
} ch9121_info_t;

/**
 * @}
 */

/**
 * @defgroup ch9121_link_driver ch9121 link driver function
 * @brief    ch9121 link driver modules
 * @ingroup  ch9121_driver
 * @{
 */

/**
 * @brief     initialize ch9121 structure
 * @param[in] HANDLE points to a ch9121 handle structure
 * @param[in] STRUCTURE is ch9121_handle_t
 * @note      none
 */
#define DRIVER_CH9121_LINK_INIT(HANDLE, STRUCTURE)          memset(HANDLE, 0, sizeof(STRUCTURE))

/**
 * @brief     link uart_init function
 * @param[in] HANDLE points to a ch9121 handle structure
 * @param[in] FUC points to a uart_init function address
 * @note      none
 */
#define DRIVER_CH9121_LINK_UART_INIT(HANDLE, FUC)           (HANDLE)->uart_init = FUC

/**
 * @brief     link uart_deinit function
 * @param[in] HANDLE points to a ch9121 handle structure
 * @param[in] FUC points to a uart_deinit function address
 * @note      none
 */
#define DRIVER_CH9121_LINK_UART_DEINIT(HANDLE, FUC)         (HANDLE)->uart_deinit = FUC

/**
 * @brief     link uart_read function
 * @param[in] HANDLE points to a ch9121 handle structure
 * @param[in] FUC points to a uart_read function address
 * @note      none
 */
#define DRIVER_CH9121_LINK_UART_READ(HANDLE, FUC)           (HANDLE)->uart_read = FUC

/**
 * @brief     link uart_write function
 * @param[in] HANDLE points to a ch9121 handle structure
 * @param[in] FUC points to a uart_write function address
 * @note      none
 */
#define DRIVER_CH9121_LINK_UART_WRITE(HANDLE, FUC)          (HANDLE)->uart_write = FUC

/**
 * @brief     link uart_flush function
 * @param[in] HANDLE points to a ch9121 handle structure
 * @param[in] FUC points to a uart_flush function address
 * @note      none
 */
#define DRIVER_CH9121_LINK_UART_FLUSH(HANDLE, FUC)          (HANDLE)->uart_flush = FUC

/**
 * @brief     link reset_gpio_init function
 * @param[in] HANDLE points to a ch9121 handle structure
 * @param[in] FUC points to a reset_gpio_init function address
 * @note      none
 */
#define DRIVER_CH9121_LINK_RESET_GPIO_INIT(HANDLE, FUC)     (HANDLE)->reset_gpio_init = FUC

/**
 * @brief     link reset_gpio_deinit function
 * @param[in] HANDLE points to a ch9121 handle structure
 * @param[in] FUC points to a reset_gpio_deinit function address
 * @note      none
 */
#define DRIVER_CH9121_LINK_RESET_GPIO_DEINIT(HANDLE, FUC)   (HANDLE)->reset_gpio_deinit = FUC

/**
 * @brief     link reset_gpio_write function
 * @param[in] HANDLE points to a ch9121 handle structure
 * @param[in] FUC points to a reset_gpio_write function address
 * @note      none
 */
#define DRIVER_CH9121_LINK_RESET_GPIO_WRITE(HANDLE, FUC)    (HANDLE)->reset_gpio_write = FUC

/**
 * @brief     link cfg_gpio_init function
 * @param[in] HANDLE points to a ch9121 handle structure
 * @param[in] FUC points to a cfg_gpio_init function address
 * @note      none
 */
#define DRIVER_CH9121_LINK_CFG_GPIO_INIT(HANDLE, FUC)       (HANDLE)->cfg_gpio_init = FUC

/**
 * @brief     link cfg_gpio_deinit function
 * @param[in] HANDLE points to a ch9121 handle structure
 * @param[in] FUC points to a cfg_gpio_deinit function address
 * @note      none
 */
#define DRIVER_CH9121_LINK_CFG_GPIO_DEINIT(HANDLE, FUC)     (HANDLE)->cfg_gpio_deinit = FUC

/**
 * @brief     link cfg_gpio_write function
 * @param[in] HANDLE points to a ch9121 handle structure
 * @param[in] FUC points to a cfg_gpio_write function address
 * @note      none
 */
#define DRIVER_CH9121_LINK_CFG_GPIO_WRITE(HANDLE, FUC)      (HANDLE)->cfg_gpio_write = FUC

/**
 * @brief     link delay_ms function
 * @param[in] HANDLE points to a ch9121 handle structure
 * @param[in] FUC points to a delay_ms function address
 * @note      none
 */
#define DRIVER_CH9121_LINK_DELAY_MS(HANDLE, FUC)            (HANDLE)->delay_ms = FUC

/**
 * @brief     link debug_print function
 * @param[in] HANDLE points to a ch9121 handle structure
 * @param[in] FUC points to a debug_print function address
 * @note      none
 */
#define DRIVER_CH9121_LINK_DEBUG_PRINT(HANDLE, FUC)         (HANDLE)->debug_print = FUC

/**
 * @}
 */

/**
 * @defgroup ch9121_base_driver ch9121 base driver function
 * @brief    ch9121 base driver modules
 * @ingroup  ch9121_driver
 * @{
 */

/**
 * @brief      get chip's information
 * @param[out] *info points to a ch9121 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t ch9121_info(ch9121_info_t *info);

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
uint8_t ch9121_init(ch9121_handle_t *handle);

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
uint8_t ch9121_deinit(ch9121_handle_t *handle);

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
uint8_t ch9121_read(ch9121_handle_t *handle, uint8_t *buf, uint16_t *len);

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
uint8_t ch9121_write(ch9121_handle_t *handle, uint8_t *buf, uint16_t len);

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
uint8_t ch9121_get_version(ch9121_handle_t *handle, uint8_t *version);

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
uint8_t ch9121_reset(ch9121_handle_t *handle);

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
uint8_t ch9121_save_to_eeprom(ch9121_handle_t *handle);

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
uint8_t ch9121_config_and_reset(ch9121_handle_t *handle);

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
uint8_t ch9121_exit(ch9121_handle_t *handle);

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
uint8_t ch9121_set_dhcp(ch9121_handle_t *handle, ch9121_bool_t enable);

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
uint8_t ch9121_get_mac(ch9121_handle_t *handle, uint8_t mac[6]);

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
uint8_t ch9121_set_ip(ch9121_handle_t *handle, uint8_t ip[4]);

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
uint8_t ch9121_get_ip(ch9121_handle_t *handle, uint8_t ip[4]);

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
uint8_t ch9121_set_subnet_mask(ch9121_handle_t *handle, uint8_t mask[4]);

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
uint8_t ch9121_get_subnet_mask(ch9121_handle_t *handle, uint8_t mask[4]);

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
uint8_t ch9121_set_gateway(ch9121_handle_t *handle, uint8_t ip[4]);

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
uint8_t ch9121_get_gateway(ch9121_handle_t *handle, uint8_t ip[4]);


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
uint8_t ch9121_get_status(ch9121_handle_t *handle, ch9121_port_t port, ch9121_status_t *status);

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
uint8_t ch9121_set_mode(ch9121_handle_t *handle, ch9121_port_t port, ch9121_mode_t mode);

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
uint8_t ch9121_get_mode(ch9121_handle_t *handle, ch9121_port_t port, ch9121_mode_t *mode);

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
uint8_t ch9121_set_source_port(ch9121_handle_t *handle, ch9121_port_t port, uint16_t num);

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
uint8_t ch9121_get_source_port(ch9121_handle_t *handle, ch9121_port_t port, uint16_t *num);

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
uint8_t ch9121_set_dest_ip(ch9121_handle_t *handle, ch9121_port_t port, uint8_t ip[4]);

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
uint8_t ch9121_get_dest_ip(ch9121_handle_t *handle, ch9121_port_t port, uint8_t ip[4]);

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
uint8_t ch9121_set_dest_port(ch9121_handle_t *handle, ch9121_port_t port, uint16_t num);

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
uint8_t ch9121_get_dest_port(ch9121_handle_t *handle, ch9121_port_t port, uint16_t *num);

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
uint8_t ch9121_set_uart_baud(ch9121_handle_t *handle, ch9121_port_t port, uint32_t baud);

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
uint8_t ch9121_get_uart_baud(ch9121_handle_t *handle, ch9121_port_t port, uint32_t *baud);

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
uint8_t ch9121_set_uart_config(ch9121_handle_t *handle, ch9121_port_t port, uint8_t data_bit, ch9121_parity_t parity, uint8_t stop_bit);

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
uint8_t ch9121_get_uart_config(ch9121_handle_t *handle, ch9121_port_t port, uint8_t *data_bit, ch9121_parity_t *parity, uint8_t *stop_bit);

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
uint8_t ch9121_set_uart_timeout(ch9121_handle_t *handle, ch9121_port_t port, uint8_t timeout);

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
uint8_t ch9121_get_uart_timeout(ch9121_handle_t *handle, ch9121_port_t port, uint8_t *timeout);

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
uint8_t ch9121_uart_timeout_convert_to_register(ch9121_handle_t *handle, uint16_t ms, uint8_t *reg);

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
uint8_t ch9121_uart_timeout_convert_to_data(ch9121_handle_t *handle, uint8_t reg, uint16_t *ms);

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
uint8_t ch9121_set_source_port_random(ch9121_handle_t *handle, ch9121_port_t port, ch9121_bool_t enable);

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
uint8_t ch9121_set_uart_buffer_length(ch9121_handle_t *handle, ch9121_port_t port, uint32_t len);

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
uint8_t ch9121_set_uart_flush(ch9121_handle_t *handle, ch9121_port_t port, ch9121_bool_t enable);

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
uint8_t ch9121_set_port2(ch9121_handle_t *handle, ch9121_bool_t enable);

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
uint8_t ch9121_set_disconnect_with_no_rj45(ch9121_handle_t *handle, ch9121_bool_t enable);

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
uint8_t ch9121_set_domain(ch9121_handle_t *handle, char *domain);

/**
 * @}
 */

/**
 * @defgroup ch9121_extend_driver ch9121 extend driver function
 * @brief    ch9121 extend driver modules
 * @ingroup  ch9121_driver
 * @{
 */

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
                           uint16_t pre_delay, uint16_t timeout);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
