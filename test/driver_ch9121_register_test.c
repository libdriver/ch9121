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
 * @file      driver_ch9121_register_test.c
 * @brief     driver ch9121 register test source file
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

#include "driver_ch9121_register_test.h"
#include <stdlib.h>

static ch9121_handle_t gs_handle;        /**< ch9121 handle */

/**
 * @brief  register test
 * @return status code
 *         - 0 success
 *         - 1 test failed
 * @note   none
 */
uint8_t ch9121_register_test(void)
{
    uint8_t res;
    uint8_t version;
    uint8_t timeout;
    uint8_t timeout_check;
    uint8_t mac[6];
    uint8_t ip[4];
    uint8_t ip_check[4];
    uint8_t mask[4];
    uint8_t mask_check[4];
    uint16_t num;
    uint16_t num_check;
    uint32_t baud;
    uint32_t baud_check;
    uint32_t len;
    uint8_t data_bit;
    uint8_t stop_bit;
    uint16_t ms;
    uint16_t ms_check;
    uint8_t reg;
    ch9121_parity_t parity;
    ch9121_info_t info;
    ch9121_status_t status;
    ch9121_mode_t mode;
    char domain[] = "www.ch9121.com";

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

    /* get ch9121 information */
    res = ch9121_info(&info);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: get info failed.\n");

        return 1;
    }
    else
    {
        /* print chip information */
        ch9121_interface_debug_print("ch9121: chip is %s.\n", info.chip_name);
        ch9121_interface_debug_print("ch9121: manufacturer is %s.\n", info.manufacturer_name);
        ch9121_interface_debug_print("ch9121: interface is %s.\n", info.interface);
        ch9121_interface_debug_print("ch9121: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        ch9121_interface_debug_print("ch9121: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        ch9121_interface_debug_print("ch9121: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        ch9121_interface_debug_print("ch9121: max current is %0.2fmA.\n", info.max_current_ma);
        ch9121_interface_debug_print("ch9121: max temperature is %0.1fC.\n", info.temperature_max);
        ch9121_interface_debug_print("ch9121: min temperature is %0.1fC.\n", info.temperature_min);
    }

    /* start register test */
    ch9121_interface_debug_print("ch9121: start register test.\n");

    /* ch9121 init */
    res = ch9121_init(&gs_handle);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: init failed.\n");

        return 1;
    }

    /* ch9121_get_version test */
    ch9121_interface_debug_print("ch9121: ch9121_get_version test.\n");

    /* get version */
    res = ch9121_get_version(&gs_handle, &version);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: get version failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121_interface_debug_print("ch9121: version is 0x%02X.\n", version);

    /* ch9121_save_to_eeprom test */
    ch9121_interface_debug_print("ch9121: ch9121_save_to_eeprom test.\n");

    /* save to eeprom */
    res = ch9121_save_to_eeprom(&gs_handle);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: save to eeprom failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121_interface_debug_print("ch9121: check save to eeprom %s.\n", res == 0 ? "ok" : "error");

    /* ch9121_exit test */
    ch9121_interface_debug_print("ch9121: ch9121_exit test.\n");

    /* exit */
    res = ch9121_exit(&gs_handle);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: exit failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121_interface_debug_print("ch9121: check exit %s.\n", res == 0 ? "ok" : "error");

    /* ch9121_set_port2 test */
    ch9121_interface_debug_print("ch9121: ch9121_set_port2 test.\n");

    /* disable port2 */
    res = ch9121_set_port2(&gs_handle, CH9121_BOOL_FALSE);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: set port2 failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* disable port2 */
    ch9121_interface_debug_print("ch9121: disable port2.\n");

    /* output */
    ch9121_interface_debug_print("ch9121: check port2 %s.\n", res == 0 ? "ok" : "error");

    /* enable port2 */
    res = ch9121_set_port2(&gs_handle, CH9121_BOOL_TRUE);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: set port2 failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* enable port2 */
    ch9121_interface_debug_print("ch9121: enable port2.\n");

    /* output */
    ch9121_interface_debug_print("ch9121: check port2 %s.\n", res == 0 ? "ok" : "error");

    /* ch9121_set_disconnect_with_no_rj45 test */
    ch9121_interface_debug_print("ch9121: ch9121_set_disconnect_with_no_rj45 test.\n");

    /* disable */
    res = ch9121_set_disconnect_with_no_rj45(&gs_handle, CH9121_BOOL_FALSE);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: set disconnect with no rj45 failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* disable disconnect with no rj45 */
    ch9121_interface_debug_print("ch9121: disable disconnect with no rj45.\n");

    /* output */
    ch9121_interface_debug_print("ch9121: check disconnect with no rj45 %s.\n", res == 0 ? "ok" : "error");

    /* enable */
    res = ch9121_set_disconnect_with_no_rj45(&gs_handle, CH9121_BOOL_TRUE);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: set disconnect with no rj45 failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* enable disconnect with no rj45 */
    ch9121_interface_debug_print("ch9121: enable disconnect with no rj45.\n");

    /* output */
    ch9121_interface_debug_print("ch9121: check disconnect with no rj45 %s.\n", res == 0 ? "ok" : "error");

    /* ch9121_set_domain test */
    ch9121_interface_debug_print("ch9121: ch9121_set_domain test.\n");

    /* set domain */
    res = ch9121_set_domain(&gs_handle, domain);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: set domain failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* set domain */
    ch9121_interface_debug_print("ch9121: set domain %s.\n", domain);

    /* output */
    ch9121_interface_debug_print("ch9121: check domain %s.\n", res == 0 ? "ok" : "error");

    /* ch9121_set_dhcp test */
    ch9121_interface_debug_print("ch9121: ch9121_set_dhcp test.\n");

    /* disable dhcp */
    res = ch9121_set_dhcp(&gs_handle, CH9121_BOOL_FALSE);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: set dhcp failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* disable dhcp */
    ch9121_interface_debug_print("ch9121: disable dhcp.\n");

    /* output */
    ch9121_interface_debug_print("ch9121: check dhcp %s.\n", res == 0 ? "ok" : "error");

    /* enable dhcp */
    res = ch9121_set_dhcp(&gs_handle, CH9121_BOOL_TRUE);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: set dhcp failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* enable dhcp */
    ch9121_interface_debug_print("ch9121: enable dhcp.\n");

    /* output */
    ch9121_interface_debug_print("ch9121: check dhcp %s.\n", res == 0 ? "ok" : "error");

    /* ch9121_get_mac test */
    ch9121_interface_debug_print("ch9121: ch9121_get_mac test.\n");

    /* get mac */
    res = ch9121_get_mac(&gs_handle, mac);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: get mac failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121_interface_debug_print("ch9121: mac is 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X.\n",
                                 mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

    /* ch9121_set_ip/ch9121_get_ip test */
    ch9121_interface_debug_print("ch9121: ch9121_set_ip/ch9121_get_ip test.\n");

    /* random ip */
    ip[0] = rand() % 0xFF;
    ip[1] = rand() % 0xFF;
    ip[2] = rand() % 0xFF;
    ip[3] = rand() % 0xFF;

    /* set ip */
    res = ch9121_set_ip(&gs_handle, ip);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: set ip failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121_interface_debug_print("ch9121: set ip %d.%d.%d.%d.\n",
                                 ip[0], ip[1], ip[2], ip[3]);

    /* get ip */
    res = ch9121_get_ip(&gs_handle, ip_check);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: get ip failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121_interface_debug_print("ch9121: check ip %s.\n", memcmp(ip, ip_check, 4) == 0 ? "ok" : "error");

    /* ch9121_set_subnet_mask/ch9121_get_subnet_mask test */
    ch9121_interface_debug_print("ch9121: ch9121_set_subnet_mask/ch9121_get_subnet_mask test.\n");

    /* random mask */
    mask[0] = rand() % 0xFF;
    mask[1] = rand() % 0xFF;
    mask[2] = rand() % 0xFF;
    mask[3] = rand() % 0xFF;

    /* set subnet mask */
    res = ch9121_set_subnet_mask(&gs_handle, mask);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: set subnet mask failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121_interface_debug_print("ch9121: set subnet mask %d.%d.%d.%d.\n",
                                 mask[0], mask[1], mask[2], mask[3]);

    /* get subnet mask */
    res = ch9121_get_subnet_mask(&gs_handle, mask_check);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: get subnet mask failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121_interface_debug_print("ch9121: check subnet mask %s.\n", memcmp(mask, mask_check, 4) == 0 ? "ok" : "error");

    /* ch9121_set_gateway/ch9121_get_gateway test */
    ch9121_interface_debug_print("ch9121: ch9121_set_gateway/ch9121_get_gateway test.\n");

    /* random ip */
    ip[0] = rand() % 0xFF;
    ip[1] = rand() % 0xFF;
    ip[2] = rand() % 0xFF;
    ip[3] = rand() % 0xFF;

    /* set gateway */
    res = ch9121_set_gateway(&gs_handle, ip);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: set gateway failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121_interface_debug_print("ch9121: set gateway %d.%d.%d.%d.\n",
                                 ip[0], ip[1], ip[2], ip[3]);

    /* get gateway */
    res = ch9121_get_gateway(&gs_handle, ip_check);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: get gateway failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121_interface_debug_print("ch9121: check gateway %s.\n", memcmp(ip, ip_check, 4) == 0 ? "ok" : "error");

    /* ch9121_get_status test */
    ch9121_interface_debug_print("ch9121: ch9121_get_status test.\n");

    /* port1 */
    res = ch9121_get_status(&gs_handle, CH9121_PORT1, &status);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: get status failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121_interface_debug_print("ch9121: get port1 status %s.\n", status == CH9121_STATUS_CONNECT ? "connect" : "disconnect");

    /* port2 */
    res = ch9121_get_status(&gs_handle, CH9121_PORT2, &status);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: get status failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121_interface_debug_print("ch9121: get port2 status %s.\n", status == CH9121_STATUS_CONNECT ? "connect" : "disconnect");

    /* ch9121_set_mode/ch9121_get_mode test */
    ch9121_interface_debug_print("ch9121: ch9121_set_mode/ch9121_get_mode test.\n");

    /* tcp server */
    res = ch9121_set_mode(&gs_handle, CH9121_PORT1, CH9121_MODE_TCP_SERVER);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: set mode failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121_interface_debug_print("ch9121: set port1 tcp server mode.\n");

    res = ch9121_get_mode(&gs_handle, CH9121_PORT1, &mode);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: get mode failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121_interface_debug_print("ch9121: check mode %s.\n", mode == CH9121_MODE_TCP_SERVER ? "ok" : "error");

    /* tcp client */
    res = ch9121_set_mode(&gs_handle, CH9121_PORT1, CH9121_MODE_TCP_CLIENT);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: set mode failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121_interface_debug_print("ch9121: set port1 tcp client mode.\n");

    res = ch9121_get_mode(&gs_handle, CH9121_PORT1, &mode);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: get mode failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121_interface_debug_print("ch9121: check mode %s.\n", mode == CH9121_MODE_TCP_CLIENT ? "ok" : "error");

    /* udp server */
    res = ch9121_set_mode(&gs_handle, CH9121_PORT1, CH9121_MODE_UDP_SERVER);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: set mode failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121_interface_debug_print("ch9121: set port1 udp server mode.\n");

    res = ch9121_get_mode(&gs_handle, CH9121_PORT1, &mode);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: get mode failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121_interface_debug_print("ch9121: check mode %s.\n", mode == CH9121_MODE_UDP_SERVER ? "ok" : "error");

    /* udp client */
    res = ch9121_set_mode(&gs_handle, CH9121_PORT1, CH9121_MODE_UDP_CLIENT);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: set mode failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121_interface_debug_print("ch9121: set port1 udp client mode.\n");

    res = ch9121_get_mode(&gs_handle, CH9121_PORT1, &mode);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: get mode failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121_interface_debug_print("ch9121: check mode %s.\n", mode == CH9121_MODE_UDP_CLIENT ? "ok" : "error");

    /* tcp server */
    res = ch9121_set_mode(&gs_handle, CH9121_PORT2, CH9121_MODE_TCP_SERVER);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: set mode failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121_interface_debug_print("ch9121: set port2 tcp server mode.\n");

    res = ch9121_get_mode(&gs_handle, CH9121_PORT2, &mode);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: get mode failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121_interface_debug_print("ch9121: check mode %s.\n", mode == CH9121_MODE_TCP_SERVER ? "ok" : "error");

    /* tcp client */
    res = ch9121_set_mode(&gs_handle, CH9121_PORT2, CH9121_MODE_TCP_CLIENT);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: set mode failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121_interface_debug_print("ch9121: set port2 tcp client mode.\n");

    res = ch9121_get_mode(&gs_handle, CH9121_PORT2, &mode);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: get mode failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121_interface_debug_print("ch9121: check mode %s.\n", mode == CH9121_MODE_TCP_CLIENT ? "ok" : "error");

    /* udp server */
    res = ch9121_set_mode(&gs_handle, CH9121_PORT2, CH9121_MODE_UDP_SERVER);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: set mode failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121_interface_debug_print("ch9121: set port2 udp server mode.\n");

    res = ch9121_get_mode(&gs_handle, CH9121_PORT2, &mode);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: get mode failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121_interface_debug_print("ch9121: check mode %s.\n", mode == CH9121_MODE_UDP_SERVER ? "ok" : "error");

    /* udp client */
    res = ch9121_set_mode(&gs_handle, CH9121_PORT2, CH9121_MODE_UDP_CLIENT);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: set mode failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121_interface_debug_print("ch9121: set port2 udp client mode.\n");

    res = ch9121_get_mode(&gs_handle, CH9121_PORT2, &mode);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: get mode failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121_interface_debug_print("ch9121: check mode %s.\n", mode == CH9121_MODE_UDP_CLIENT ? "ok" : "error");

    /* ch9121_set_source_port/ch9121_get_source_port test */
    ch9121_interface_debug_print("ch9121: ch9121_set_source_port/ch9121_get_source_port test.\n");

    /* random */
    num = rand() % 0xFFFFU;

    /* port1 */
    res = ch9121_set_source_port(&gs_handle, CH9121_PORT1, num);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: set source port failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121_interface_debug_print("ch9121: set source port1 %d.\n", num);

    /* get source port */
    res = ch9121_get_source_port(&gs_handle, CH9121_PORT1, &num_check);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: get source port failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121_interface_debug_print("ch9121: check source port %s.\n", num_check == num ? "ok" : "error");

    /* random */
    num = rand() % 0xFFFFU;

    /* port2 */
    res = ch9121_set_source_port(&gs_handle, CH9121_PORT2, num);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: set source port failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121_interface_debug_print("ch9121: set source port2 %d.\n", num);

    /* get source port */
    res = ch9121_get_source_port(&gs_handle, CH9121_PORT2, &num_check);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: get source port failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121_interface_debug_print("ch9121: check source port %s.\n", num_check == num ? "ok" : "error");

    /* ch9121_set_dest_ip/ch9121_get_dest_ip test */
    ch9121_interface_debug_print("ch9121: ch9121_set_dest_ip/ch9121_get_dest_ip test.\n");

    /* random ip */
    ip[0] = rand() % 0xFF;
    ip[1] = rand() % 0xFF;
    ip[2] = rand() % 0xFF;
    ip[3] = rand() % 0xFF;

    /* port1 */
    res = ch9121_set_dest_ip(&gs_handle, CH9121_PORT1, ip);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: set dest ip failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121_interface_debug_print("ch9121: set port1 dest ip %d.%d.%d.%d.\n", ip[0], ip[1], ip[2], ip[3]);

    /* get dest ip */
    res = ch9121_get_dest_ip(&gs_handle, CH9121_PORT1, ip_check);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: get dest ip failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121_interface_debug_print("ch9121: check dest ip %s.\n", memcmp(ip, ip_check, 4) == 0 ? "ok" : "error");

    /* random ip */
    ip[0] = rand() % 0xFF;
    ip[1] = rand() % 0xFF;
    ip[2] = rand() % 0xFF;
    ip[3] = rand() % 0xFF;

    /* port2 */
    res = ch9121_set_dest_ip(&gs_handle, CH9121_PORT2, ip);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: set dest ip failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121_interface_debug_print("ch9121: set port2 dest ip %d.%d.%d.%d.\n", ip[0], ip[1], ip[2], ip[3]);

    /* get dest ip */
    res = ch9121_get_dest_ip(&gs_handle, CH9121_PORT2, ip_check);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: get dest ip failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121_interface_debug_print("ch9121: check dest ip %s.\n", memcmp(ip, ip_check, 4) == 0 ? "ok" : "error");

    /* ch9121_set_dest_port/ch9121_get_dest_port test */
    ch9121_interface_debug_print("ch9121: ch9121_set_dest_port/ch9121_get_dest_port test.\n");

    /* random */
    num = rand() % 0xFFFFU;

    /* port1 */
    res = ch9121_set_dest_port(&gs_handle, CH9121_PORT1, num);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: set dest port failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121_interface_debug_print("ch9121: set dest port1 %d.\n", num);

    /* get dest port */
    res = ch9121_get_dest_port(&gs_handle, CH9121_PORT1, &num_check);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: get dest port failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121_interface_debug_print("ch9121: check dest port %s.\n", num_check == num ? "ok" : "error");

    /* random */
    num = rand() % 0xFFFFU;

    /* port2 */
    res = ch9121_set_dest_port(&gs_handle, CH9121_PORT2, num);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: set dest port failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121_interface_debug_print("ch9121: set dest port2 %d.\n", num);

    /* get dest port */
    res = ch9121_get_dest_port(&gs_handle, CH9121_PORT2, &num_check);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: get dest port failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121_interface_debug_print("ch9121: check dest port %s.\n", num_check == num ? "ok" : "error");

    /* ch9121_set_uart_baud/ch9121_get_uart_baud test */
    ch9121_interface_debug_print("ch9121: ch9121_set_uart_baud/ch9121_get_uart_baud test.\n");

    /* 9600 */
    baud = 9600;

    /* port1 */
    res = ch9121_set_uart_baud(&gs_handle, CH9121_PORT1, baud);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: set uart baud failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121_interface_debug_print("ch9121: set port1 uart baud %d.\n", baud);

    /* get uart baud */
    res = ch9121_get_uart_baud(&gs_handle, CH9121_PORT1, &baud_check);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: get uart baud failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121_interface_debug_print("ch9121: check uart baud %s.\n", baud_check == baud ? "ok" : "error");

    /* 9600 */
    baud = 9600;

    /* port2 */
    res = ch9121_set_uart_baud(&gs_handle, CH9121_PORT2, baud);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: set uart baud failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121_interface_debug_print("ch9121: set port2 uart baud %d.\n", baud);

    /* get uart baud */
    res = ch9121_get_uart_baud(&gs_handle, CH9121_PORT2, &baud_check);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: get uart baud failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121_interface_debug_print("ch9121: check uart baud %s.\n", baud_check == baud ? "ok" : "error");

    /* ch9121_set_uart_config/ch9121_get_uart_config test */
    ch9121_interface_debug_print("ch9121: ch9121_set_uart_config/ch9121_get_uart_config test.\n");

    /* set uart config */
    res = ch9121_set_uart_config(&gs_handle, CH9121_PORT1, 8, CH9121_PARITY_NONE, 1);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: set uart config failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121_interface_debug_print("ch9121: set port1 data_bit 8, parity none, stop_bit 1.\n");

    /* get uart config */
    res = ch9121_get_uart_config(&gs_handle, CH9121_PORT1, &data_bit, &parity, &stop_bit);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: get uart config failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121_interface_debug_print("ch9121: check uart data bit %s.\n", data_bit == 8 ? "ok" : "error");
    ch9121_interface_debug_print("ch9121: check uart parity %s.\n", parity == CH9121_PARITY_NONE ? "ok" : "error");
    ch9121_interface_debug_print("ch9121: check uart stop bit %s.\n", stop_bit == 1 ? "ok" : "error");

    /* set uart config */
    res = ch9121_set_uart_config(&gs_handle, CH9121_PORT2, 8, CH9121_PARITY_NONE, 1);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: set uart config failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121_interface_debug_print("ch9121: set port2 data_bit 8, parity none, stop_bit 1.\n");

    /* get uart config */
    res = ch9121_get_uart_config(&gs_handle, CH9121_PORT2, &data_bit, &parity, &stop_bit);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: get uart config failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121_interface_debug_print("ch9121: check uart data bit %s.\n", data_bit == 8 ? "ok" : "error");
    ch9121_interface_debug_print("ch9121: check uart parity %s.\n", parity == CH9121_PARITY_NONE ? "ok" : "error");
    ch9121_interface_debug_print("ch9121: check uart stop bit %s.\n", stop_bit == 1 ? "ok" : "error");

    /* ch9121_set_uart_timeout/ch9121_get_uart_timeout test */
    ch9121_interface_debug_print("ch9121: ch9121_set_uart_timeout/ch9121_get_uart_timeout test.\n");

    /* random timeout */
    timeout = rand() % 0xFF;

    /* set uart timeout */
    res = ch9121_set_uart_timeout(&gs_handle, CH9121_PORT1, timeout);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: set uart timeout failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121_interface_debug_print("ch9121: set port1 uart timeout %d.\n", timeout);

    /* get uart timeout */
    res = ch9121_get_uart_timeout(&gs_handle, CH9121_PORT1, &timeout_check);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: get uart timeout failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121_interface_debug_print("ch9121: check uart timeout %s.\n", timeout_check == timeout ? "ok" : "error");

    /* random timeout */
    timeout = rand() % 0xFF;

    /* set uart timeout */
    res = ch9121_set_uart_timeout(&gs_handle, CH9121_PORT2, timeout);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: set uart timeout failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121_interface_debug_print("ch9121: set port2 uart timeout %d.\n", timeout);

    /* get uart timeout */
    res = ch9121_get_uart_timeout(&gs_handle, CH9121_PORT2, &timeout_check);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: get uart timeout failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121_interface_debug_print("ch9121: check uart timeout %s.\n", timeout_check == timeout ? "ok" : "error");

    /* ch9121_set_source_port_random test */
    ch9121_interface_debug_print("ch9121: ch9121_set_source_port_random test.\n");

    /* port1 */
    res = ch9121_set_source_port_random(&gs_handle, CH9121_PORT1, CH9121_BOOL_TRUE);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: set source port random failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121_interface_debug_print("ch9121: enable port1 source port random.\n");

    /* output */
    ch9121_interface_debug_print("ch9121: check source port random %s.\n", res == 0 ? "ok" : "error");

    /* port1 */
    res = ch9121_set_source_port_random(&gs_handle, CH9121_PORT1, CH9121_BOOL_FALSE);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: set source port random failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121_interface_debug_print("ch9121: disable port1 source port random.\n");

    /* output */
    ch9121_interface_debug_print("ch9121: check source port random %s.\n", res == 0 ? "ok" : "error");

    /* port2 */
    res = ch9121_set_source_port_random(&gs_handle, CH9121_PORT2, CH9121_BOOL_TRUE);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: set source port random failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121_interface_debug_print("ch9121: enable port2 source port random.\n");

    /* output */
    ch9121_interface_debug_print("ch9121: check source port random %s.\n", res == 0 ? "ok" : "error");

    /* port2 */
    res = ch9121_set_source_port_random(&gs_handle, CH9121_PORT2, CH9121_BOOL_FALSE);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: set source port random failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121_interface_debug_print("ch9121: disable port2 source port random.\n");

    /* output */
    ch9121_interface_debug_print("ch9121: check source port random %s.\n", res == 0 ? "ok" : "error");

    /* ch9121_set_uart_buffer_length test */
    ch9121_interface_debug_print("ch9121: ch9121_set_uart_buffer_length test.\n");

    /* random len */
    len = 128 + rand() % 50;

    /* set_uart_buffer_length */
    res = ch9121_set_uart_buffer_length(&gs_handle, CH9121_PORT1, len);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: set uart buffer length failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121_interface_debug_print("ch9121: set port1 uart buffer length %d.\n", len);

    /* output */
    ch9121_interface_debug_print("ch9121: check uart buffer length %s.\n", res == 0 ? "ok" : "error");

    /* random len */
    len = 128 + rand() % 50;

    /* set_uart_buffer_length */
    res = ch9121_set_uart_buffer_length(&gs_handle, CH9121_PORT2, len);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: set uart buffer length failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121_interface_debug_print("ch9121: set port2 uart buffer length %d.\n", len);

    /* output */
    ch9121_interface_debug_print("ch9121: check uart buffer length %s.\n", res == 0 ? "ok" : "error");

    /* ch9121_set_uart_flush test */
    ch9121_interface_debug_print("ch9121: ch9121_set_uart_flush test.\n");

    /* enable uart flush */
    res = ch9121_set_uart_flush(&gs_handle, CH9121_PORT1, CH9121_BOOL_TRUE);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: set uart flush failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121_interface_debug_print("ch9121: enable port1 uart flush.\n");

    /* output */
    ch9121_interface_debug_print("ch9121: check uart flush %s.\n", res == 0 ? "ok" : "error");

    /* enable uart flush */
    res = ch9121_set_uart_flush(&gs_handle, CH9121_PORT2, CH9121_BOOL_TRUE);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: set uart flush failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121_interface_debug_print("ch9121: enable port2 uart flush.\n");

    /* output */
    ch9121_interface_debug_print("ch9121: check uart flush %s.\n", res == 0 ? "ok" : "error");

    /* ch9121_uart_timeout_convert_to_register/ch9121_uart_timeout_convert_to_data test */
    ch9121_interface_debug_print("ch9121: ch9121_uart_timeout_convert_to_register/ch9121_uart_timeout_convert_to_data test.\n");

    /* random ms */
    ms = (rand() % 10) * 5;

    /* uart timeout convert to register */
    res = ch9121_uart_timeout_convert_to_register(&gs_handle, ms, &reg);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: uart timeout convert to register failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121_interface_debug_print("ch9121: uart timeout convert to register %d.\n", ms);

    /* uart timeout convert to data */
    res = ch9121_uart_timeout_convert_to_data(&gs_handle, reg, &ms_check);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: uart timeout convert to data failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121_interface_debug_print("ch9121: check uart timeout convert %s.\n", ms == ms_check ? "ok" : "error");

    /* finish register test */
    ch9121_interface_debug_print("ch9121: finish register test.\n");
    (void)ch9121_deinit(&gs_handle);

    return 0;
}
