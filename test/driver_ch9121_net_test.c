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
 * @file      driver_ch9121_net_test.c
 * @brief     driver ch9121 net test source file
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

#include "driver_ch9121_net_test.h"

static ch9121_handle_t gs_handle;        /**< ch9121 handle */

/**
 * @brief     net test
 * @param[in] mode is the net mode
 * @param[in] timeout in ms
 * @return    status code
 *            - 0 success
 *            - 1 test failed
 * @note      none
 */
uint8_t ch9121_net_test(ch9121_mode_t mode, uint32_t timeout)
{
    uint8_t res;
    uint8_t reg;
    uint8_t ip[4] = CH9121_NET_TEST_IP;
    uint8_t dst_ip[4] = CH9121_NET_TEST_DST_IP;
    uint8_t mask[4] = CH9121_NET_TEST_MASK;
    uint8_t gateway[4] = CH9121_NET_TEST_GATEWAY;
    char str[] = "LibDriver";
    ch9121_info_t info;

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

    /* start net test */
    ch9121_interface_debug_print("ch9121: start net test.\n");

    /* ch9121 init */
    res = ch9121_init(&gs_handle);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: init failed.\n");

        return 1;
    }

    /* disable dhcp */
    res = ch9121_set_dhcp(&gs_handle, CH9121_BOOL_FALSE);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: set dhcp failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* set ip */
    res = ch9121_set_ip(&gs_handle, ip);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: set ip failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* set subnet mask */
    res = ch9121_set_subnet_mask(&gs_handle, mask);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: set subnet mask failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* set gateway */
    res = ch9121_set_gateway(&gs_handle, gateway);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: set gateway failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* set source port */
    res = ch9121_set_source_port(&gs_handle, CH9121_PORT1, CH9121_NET_TEST_PORT);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: set source port failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* set dest ip */
    res = ch9121_set_dest_ip(&gs_handle, CH9121_PORT1, dst_ip);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: set dest ip failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* set dest port */
    res = ch9121_set_dest_port(&gs_handle, CH9121_PORT1, CH9121_NET_TEST_DST_PORT);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: set dest port failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* set 9600 */
    res = ch9121_set_uart_baud(&gs_handle, CH9121_PORT1, 9600);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: set uart baud failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* set uart 8 data bit, parity none, 1 stop bit */
    res = ch9121_set_uart_config(&gs_handle, CH9121_PORT1, 8, CH9121_PARITY_NONE, 1);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: set uart config failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* 10ms */
    res = ch9121_uart_timeout_convert_to_register(&gs_handle, 10, &reg);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: uart timeout convert to register failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* set uart timeout */
    res = ch9121_set_uart_timeout(&gs_handle, CH9121_PORT1, reg);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: set uart timeout failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* disable source port random */
    res = ch9121_set_source_port_random(&gs_handle, CH9121_PORT1, CH9121_BOOL_FALSE);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: set source port random failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* set uart buffer length */
    res = ch9121_set_uart_buffer_length(&gs_handle, CH9121_PORT1, 1024);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: set uart buffer length failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* false uart flush */
    res = ch9121_set_uart_flush(&gs_handle, CH9121_PORT1, CH9121_BOOL_FALSE);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: set uart flush failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* disable port2 */
    res = ch9121_set_port2(&gs_handle, CH9121_BOOL_FALSE);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: set port2 failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* enable disconnect with no rj45 */
    res = ch9121_set_disconnect_with_no_rj45(&gs_handle, CH9121_BOOL_TRUE);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: set disconnect with no rj45 failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* set mode */
    res = ch9121_set_mode(&gs_handle, CH9121_PORT1, mode);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: set mode failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* save to eeprom */
    res = ch9121_save_to_eeprom(&gs_handle);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: save to eeprom failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* config and reset */
    res = ch9121_config_and_reset(&gs_handle);
    if (res != 0)
    {
        ch9121_interface_debug_print("ch9121: config and reset failed.\n");
        (void)ch9121_deinit(&gs_handle);

        return 1;
    }

    /* tcp server */
    if (mode == CH9121_MODE_TCP_SERVER)
    {
        uint8_t ip_tmp[4];
        uint16_t num;
        uint32_t t = timeout;

        /* get ip */
        res = ch9121_get_ip(&gs_handle, ip_tmp);
        if (res != 0)
        {
            ch9121_interface_debug_print("ch9121: get ip failed.\n");
            (void)ch9121_deinit(&gs_handle);

            return 1;
        }

        /* get source port */
        res = ch9121_get_source_port(&gs_handle, CH9121_PORT1, &num);
        if (res != 0)
        {
            ch9121_interface_debug_print("ch9121: get source port failed.\n");
            (void)ch9121_deinit(&gs_handle);

            return 1;
        }

        /* output */
        ch9121_interface_debug_print("ch9121: tcp server src port %d, src ip %d.%d.%d.%d.\n", num, ip_tmp[0], ip_tmp[1], ip_tmp[2], ip_tmp[3]);

        /* loop */
        while (t != 0)
        {
            uint8_t buf[16];
            uint16_t l;

            /* init */
            memset(buf, 0, sizeof(uint8_t) * 16);
            l = 16;

            /* read data */
            res = ch9121_read(&gs_handle, buf, &l);
            if (res != 0)
            {
                ch9121_interface_debug_print("ch9121: read failed.\n");
                (void)ch9121_deinit(&gs_handle);

                return 1;
            }

            if (l != 0)
            {
                /* output */
                ch9121_interface_debug_print("ch9121: read %s.\n", buf);

                break;
            }

            /* delay 1ms */
            ch9121_interface_delay_ms(1);
            t--;
        }

        /* check timeout */
        if (t == 0)
        {
            ch9121_interface_debug_print("ch9121: timeout.\n");
            (void)ch9121_deinit(&gs_handle);

            return 1;
        }
    }
    /* tcp client */
    else if (mode == CH9121_MODE_TCP_CLIENT)
    {
        uint8_t ip_tmp[4];
        uint16_t num;

        /* get ip */
        res = ch9121_get_dest_ip(&gs_handle, CH9121_PORT1, ip_tmp);
        if (res != 0)
        {
            ch9121_interface_debug_print("ch9121: get ip failed.\n");
            (void)ch9121_deinit(&gs_handle);

            return 1;
        }

        /* get dest port */
        res = ch9121_get_dest_port(&gs_handle, CH9121_PORT1, &num);
        if (res != 0)
        {
            ch9121_interface_debug_print("ch9121: get dest port failed.\n");
            (void)ch9121_deinit(&gs_handle);

            return 1;
        }

        /* output */
        ch9121_interface_debug_print("ch9121: tcp client dest port %d, dest ip %d.%d.%d.%d.\n", num, ip_tmp[0], ip_tmp[1], ip_tmp[2], ip_tmp[3]);

        /* write data */
        res = ch9121_write(&gs_handle, (uint8_t *)str, (uint16_t)strlen(str));
        if (res != 0)
        {
            ch9121_interface_debug_print("ch9121: write failed.\n");
            (void)ch9121_deinit(&gs_handle);

            return 1;
        }

        /* output */
        ch9121_interface_debug_print("ch9121: write %s.\n", str);
    }
    /* udp server */
    else if (mode == CH9121_MODE_UDP_SERVER)
    {
        uint8_t ip_tmp[4];
        uint16_t num;
        uint32_t t = timeout;

        /* get ip */
        res = ch9121_get_ip(&gs_handle, ip_tmp);
        if (res != 0)
        {
            ch9121_interface_debug_print("ch9121: get ip failed.\n");
            (void)ch9121_deinit(&gs_handle);

            return 1;
        }

        /* get source port */
        res = ch9121_get_source_port(&gs_handle, CH9121_PORT1, &num);
        if (res != 0)
        {
            ch9121_interface_debug_print("ch9121: get source port failed.\n");
            (void)ch9121_deinit(&gs_handle);

            return 1;
        }

        /* output */
        ch9121_interface_debug_print("ch9121: udp server src port %d, src ip %d.%d.%d.%d.\n", num, ip_tmp[0], ip_tmp[1], ip_tmp[2], ip_tmp[3]);

        /* loop */
        while (t != 0)
        {
            uint8_t buf[16];
            uint16_t l;

            /* init */
            memset(buf, 0, sizeof(uint8_t) * 16);
            l = 16;

            /* read data */
            res = ch9121_read(&gs_handle, buf, &l);
            if (res != 0)
            {
                ch9121_interface_debug_print("ch9121: read failed.\n");
                (void)ch9121_deinit(&gs_handle);

                return 1;
            }

            if (l != 0)
            {
                /* output */
                ch9121_interface_debug_print("ch9121: read %s.\n", buf);

                break;
            }

            /* delay 1ms */
            ch9121_interface_delay_ms(1);
            t--;
        }

        /* check timeout */
        if (t == 0)
        {
            ch9121_interface_debug_print("ch9121: timeout.\n");
            (void)ch9121_deinit(&gs_handle);

            return 1;
        }
    }
    /* udp client */
    else
    {
        uint8_t ip_tmp[4];
        uint16_t i;
        uint16_t num;

        /* get ip */
        res = ch9121_get_dest_ip(&gs_handle, CH9121_PORT1, ip_tmp);
        if (res != 0)
        {
            ch9121_interface_debug_print("ch9121: get ip failed.\n");
            (void)ch9121_deinit(&gs_handle);

            return 1;
        }

        /* get dest port */
        res = ch9121_get_dest_port(&gs_handle, CH9121_PORT1, &num);
        if (res != 0)
        {
            ch9121_interface_debug_print("ch9121: get dest port failed.\n");
            (void)ch9121_deinit(&gs_handle);

            return 1;
        }

        /* output */
        ch9121_interface_debug_print("ch9121: udp client dest port %d, dest ip %d.%d.%d.%d.\n", num, ip_tmp[0], ip_tmp[1], ip_tmp[2], ip_tmp[3]);

        /* run 10 times */
        for (i = 0; i < 10; i++)
        {
            /* write data */
            res = ch9121_write(&gs_handle, (uint8_t *)str, (uint16_t)strlen(str));
            if (res != 0)
            {
                ch9121_interface_debug_print("ch9121: write failed.\n");
                (void)ch9121_deinit(&gs_handle);

                return 1;
            }

            /* output */
            ch9121_interface_debug_print("ch9121: write %s.\n", str);

            /* delay 1000ms */
            ch9121_interface_delay_ms(1000);
        }
    }

    /* finish net test */
    ch9121_interface_debug_print("ch9121: finish net test.\n");

    return 0;
}
