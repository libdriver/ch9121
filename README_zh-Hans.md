[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver CH9121

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/ch9121/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

CH9121是一款网络串口透传芯片。CH9121内部集成TCP/IP协议栈，可实现网络数据包和串口数据的双向透明传输，具有TCP CLIENT、TCP SERVER、UDP CLIENT、UDP SERVER4 种工作模式，串口波特率最高可支持到 921600bps，可通过上位机软件或者串口命令轻松配置，方便快捷。

LibDriver CH9121是LibDriver推出的CH9121全功能驱动，该驱动提供TCP服务器、TCP客户端、UDP服务器、UDP客户端等功能并且它符合MISRA标准。

### 目录

  - [说明](#说明)
  - [安装](#安装)
  - [使用](#使用)
    - [example basic](#example-basic)
  - [文档](#文档)
  - [贡献](#贡献)
  - [版权](#版权)
  - [联系我们](#联系我们)

### 说明

/src目录包含了LibDriver CH9121的源文件。

/interface目录包含了LibDriver CH9121与平台无关的UART模板。

/test目录包含了LibDriver CH9121驱动测试程序，该程序可以简单的测试芯片必要功能。

/example目录包含了LibDriver CH9121编程范例。

/doc目录包含了LibDriver CH9121离线文档。

/datasheet目录包含了CH9121数据手册。

/project目录包含了常用Linux与单片机开发板的工程样例。所有工程均采用shell脚本作为调试方法，详细内容可参考每个工程里面的README.md。

/misra目录包含了LibDriver MISRA代码扫描结果。

### 安装

参考/interface目录下与平台无关的UART模板，完成指定平台的UART驱动。

将/src目录，您使用平台的接口驱动和您开发的驱动加入工程，如果您想要使用默认的范例驱动，可以将/example目录加入您的工程。

### 使用

您可以参考/example目录下的编程范例完成适合您的驱动，如果您想要使用默认的编程范例，以下是它们的使用方法。

#### example basic

```C
#include "driver_ch9121_basic.h"

char data[49];
uint16_t l;
uint8_t dest_ip[4] = {192, 168, 1, 10};
uint16_t dest_port = 1000;
uint8_t gateway[4] = {192, 168, 1, 1};
uint8_t mask[4] = {255, 255, 255, 0};
ch9121_mode_t mode = CH9121_MODE_TCP_CLIENT;
uint8_t source_ip[4] = {192, 168, 1, 230};
uint16_t source_port = 2000;
ch9121_port_t uart_port = CH9121_PORT1;

/* net init */
if (ch9121_basic_init() != 0)
{
    return 1;
}

...
    
/* this is optional */
if (ch9121_basic_config(uart_port, mode,
                        source_ip, source_port, 
                        mask, gateway,
                        dest_ip, dest_port) != 0)
{
    (void)ch9121_basic_deinit();
    
    return 1;
}

...
    
/* net write */
if (ch9121_basic_write((uint8_t *)"LibDriver", strlen((char*)"LibDriver")) != 0)
{
    (void)ch9121_basic_deinit();
    
    return 1;
}

...

/* 48 byte */
l = 48;
memset(data, 0, sizeof(char) * 48);

/* net read */
if (ch9121_basic_read((uint8_t *)data, &l) != 0)
{
    (void)ch9121_basic_deinit();
    
    return 1;
}

/* output */
ch9121_interface_debug_print("ch9121: net read %s.\n", data);

...
    
/* net deinit */
if (ch9121_basic_deinit() != 0)
{
    return 1;
}

return 0;
```

### 文档

在线文档: [https://www.libdriver.com/docs/ch9121/index.html](https://www.libdriver.com/docs/ch9121/index.html)。

离线文档: /doc/html/index.html。

### 贡献

请参考CONTRIBUTING.md。

### 版权

版权 (c) 2015 - 现在 LibDriver 版权所有

MIT 许可证（MIT）

特此免费授予任何获得本软件副本和相关文档文件（下称“软件”）的人不受限制地处置该软件的权利，包括不受限制地使用、复制、修改、合并、发布、分发、转授许可和/或出售该软件副本，以及再授权被配发了本软件的人如上的权利，须在下列条件下：

上述版权声明和本许可声明应包含在该软件的所有副本或实质成分中。

本软件是“如此”提供的，没有任何形式的明示或暗示的保证，包括但不限于对适销性、特定用途的适用性和不侵权的保证。在任何情况下，作者或版权持有人都不对任何索赔、损害或其他责任负责，无论这些追责来自合同、侵权或其它行为中，还是产生于、源于或有关于本软件以及本软件的使用或其它处置。

### 联系我们

请联系lishifenging@outlook.com。