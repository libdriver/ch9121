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
 * @file      driver_ch9121_basic.c
 * @brief     driver ch9121 basic source file
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

#include "driver_ch9121_basic.h"

static ch9121_handle_t gs_handle;        /**< ch9121 handle */

/**
 * @brief  basic example init
 * @return status code
 *         - 0 success
 *         - 1 init failed
 * @note   none
 */
uint8_t ch9121_basic_init(void)
{
    uint8_t res;
    
    /* link interface function */
    DRIVER_CH9121_LINK_INIT(&gs_handle, ch9121_handle_t);
    DRIVER_CH9121_LINK_UART_INIT(&gs_handle, ch9121_interface_uart_init);
    DRIVER_CH9121_LINK_UART_DEINIT(&gs_handle, ch9121_interface_uart_deinit);
    DRIVER_CH9121_LINK_UART_READ(&gs_handle, ch9121_interface_uart_read);
    DRIVER_CH9121_LINK_UART_WRITE(&gs_handle, ch9121_interface_uart_write);
    DRIVER_CH9121_LINK_UART_FLUSH(&gs_handle, ch9121_interface_uart_flush);
    DRIVER_CH9121_LINK_RESET_GPIO_INIT(&gs_handle, ch9121_interface_reset_gpio_init);
    DRIVER_CH9121_LINK_RESET_GPIO_DEINIT(&gs_handle, ch9121_interface_reset_gpio_deinit);
    DRIVER_CH9121_LINK_RESET_GPIO_WRITE(&gs_handle, ch9121_interface_reset_gpio_write);
    DRIVER_CH9121_LINK_CFG_GPIO_INIT(&gs_handle, ch9121_interface_cfg_gpio_init);
    DRIVER_CH9121_LINK_CFG_GPIO_DEINIT(&gs_handle, ch9121_interface_cfg_gpio_deinit);
    DRIVER_CH9121_LINK_CFG_GPIO_WRITE(&gs_handle, ch9121_interface_cfg_gpio_write);
    DRIVER_CH9121_LINK_DELAY_MS(&gs_handle, ch9121_interface_delay_ms);
    DRIVER_CH9121_LINK_DEBUG_PRINT(&gs_handle, ch9121_interface_debug_print);
    
    /* ch9121 init */
    res = ch9121_init(&gs_handle);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: init failed.\n");

        return 1;
    }
    
    return 0;
}

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
                            uint8_t dest_ip[4], uint16_t dest_port)
{
    uint8_t res;
    uint8_t reg;
    
    /* set default dhcp */
    res = ch9121_set_dhcp(&gs_handle, CH9121_BASIC_DEFAULT_DHCP);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: set dhcp failed.\n");
        
        return 1;
    }
    
    /* set local ip */
    res = ch9121_set_ip(&gs_handle, ip);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: set ip failed.\n");
        
        return 1;
    }
    
    /* set subnet mask */
    res = ch9121_set_subnet_mask(&gs_handle, mask);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: set subnet mask failed.\n");
        
        return 1;
    }
    
    /* set gateway */
    res = ch9121_set_gateway(&gs_handle, gateway);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: set gateway failed.\n");
        
        return 1;
    }

    /* set source port */
    res = ch9121_set_source_port(&gs_handle, uart_port, port);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: set source port failed.\n");
        
        return 1;
    }
    
    /* set dest ip */
    res = ch9121_set_dest_ip(&gs_handle, uart_port, dest_ip);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: set dest ip failed.\n");
        
        return 1;
    }
    
    /* set dest port */
    res = ch9121_set_dest_port(&gs_handle, uart_port, dest_port);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: set dest port failed.\n");
        
        return 1;
    }
    
    /* set default uart baud */
    res = ch9121_set_uart_baud(&gs_handle, uart_port, CH9121_BASIC_DEFAULT_UART_PORT);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: set uart baud failed.\n");
        
        return 1;
    }
    
    /* set default uart config */
    res = ch9121_set_uart_config(&gs_handle, uart_port, CH9121_BASIC_DEFAULT_UART_DATA_BIT,
                                 CH9121_BASIC_DEFAULT_UART_PARITY, CH9121_BASIC_DEFAULT_UART_STOP_BIT);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: set uart config failed.\n");
        
        return 1;
    }
    
    /* set default uart timeout */
    res = ch9121_uart_timeout_convert_to_register(&gs_handle, CH9121_BASIC_DEFAULT_UART_TIMEOUT, &reg);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: uart timeout convert to register failed.\n");
        
        return 1;
    }
    
    /* set uart timeout */
    res = ch9121_set_uart_timeout(&gs_handle, uart_port, reg);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: set uart timeout failed.\n");
        
        return 1;
    }
    
    /* set default source port random */
    res = ch9121_set_source_port_random(&gs_handle, uart_port, CH9121_BASIC_DEFAULT_UART_SOURCE_PORT_RANDOM);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: set source port random failed.\n");
        
        return 1;
    }
    
    /* set default uart buffer length */
    res = ch9121_set_uart_buffer_length(&gs_handle, uart_port, CH9121_BASIC_DEFAULT_UART_BUFFER_LENGTH);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: set uart buffer length failed.\n");
        
        return 1;
    }
    
    /* set default uart flush */
    res = ch9121_set_uart_flush(&gs_handle, uart_port, CH9121_BASIC_DEFAULT_UART_FLUSH);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: set uart flush failed.\n");
        
        return 1;
    }
    
    /* set default port2 */
    res = ch9121_set_port2(&gs_handle, CH9121_BASIC_DEFAULT_UART_PORT2);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: set port2 failed.\n");
        
        return 1;
    }
    
    /* set default disconnect with no rj45 */
    res = ch9121_set_disconnect_with_no_rj45(&gs_handle, CH9121_BASIC_DEFAULT_DISCONNECT_WITH_NO_RJ45);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: set disconnect with no rj45 failed.\n");
        
        return 1;
    }
    
    /* set mode */
    res = ch9121_set_mode(&gs_handle, uart_port, mode);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: set mode failed.\n");
        
        return 1;
    }
    
    /* save to eeprom */
    res = ch9121_save_to_eeprom(&gs_handle);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: save to eeprom failed.\n");
        
        return 1;
    }
    
    /* config and reset */
    res = ch9121_config_and_reset(&gs_handle);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: config and reset failed.\n");
        
        return 1;
    }
    
    return 0;
}

/**
 * @brief         basic example read data
 * @param[out]    *buf points to a data buffer
 * @param[in,out] *len points to a length buffer
 * @return        status code
 *                - 0 success
 *                - 1 read failed
 * @note          none
 */
uint8_t ch9121_basic_read(uint8_t *buf, uint16_t *len)
{
    if (ch9121_read(&gs_handle, buf, len) != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief     basic example write data
 * @param[in] *buf points to a data buffer
 * @param[in] len is the data length
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
uint8_t ch9121_basic_write(uint8_t *buf, uint16_t len)
{
    if (ch9121_write(&gs_handle, buf, len) != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief  basic example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t ch9121_basic_deinit(void)
{
    /* deinit ch9121 */
    if (ch9121_deinit(&gs_handle) != 0)
    {
        return 1;
    }
    
    return 0;
}
