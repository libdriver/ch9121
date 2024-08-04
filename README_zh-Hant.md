[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver CH9121

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/ch9121/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

CH9121是一款網絡串口透傳晶片。 CH9121內部集成TCP/IP協議棧，可實現網絡數据包和串口數據的雙向透明傳輸，具有TCP CLIENT、TCP SERVER、UDP CLIENT、UDP SERVER4種工作模式，串口串列傳輸速率最高可支持到921600bps，可通過上位機軟件或者串口命令輕鬆配寘，方便快捷。

LibDriver CH9121是LibDriver推出的CH9121全功能驅動，該驅動提供TCP服務器、TCP用戶端、UDP服務器、UDP用戶端等功能並且它符合MISRA標準。

### 目錄

  - [說明](#說明)
  - [安裝](#安裝)
  - [使用](#使用)
    - [example basic](#example-basic)
  - [文檔](#文檔)
  - [貢獻](#貢獻)
  - [版權](#版權)
  - [聯繫我們](#聯繫我們)

### 說明

/src目錄包含了LibDriver CH9121的源文件。

/interface目錄包含了LibDriver CH9121與平台無關的UART模板。

/test目錄包含了LibDriver CH9121驅動測試程序，該程序可以簡單的測試芯片必要功能。

/example目錄包含了LibDriver CH9121編程範例。

/doc目錄包含了LibDriver CH9121離線文檔。

/datasheet目錄包含了CH9121數據手冊。

/project目錄包含了常用Linux與單片機開發板的工程樣例。所有工程均採用shell腳本作為調試方法，詳細內容可參考每個工程裡面的README.md。

/misra目錄包含了LibDriver MISRA程式碼掃描結果。

### 安裝

參考/interface目錄下與平台無關的UART模板，完成指定平台的UART驅動。

將/src目錄，您使用平臺的介面驅動和您開發的驅動加入工程，如果您想要使用默認的範例驅動，可以將/example目錄加入您的工程。

### 使用

您可以參考/example目錄下的程式設計範例完成適合您的驅動，如果您想要使用默認的程式設計範例，以下是它們的使用方法。

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

### 文檔

在線文檔: [https://www.libdriver.com/docs/ch9121/index.html](https://www.libdriver.com/docs/ch9121/index.html)。

離線文檔: /doc/html/index.html。

### 貢獻

請參攷CONTRIBUTING.md。

### 版權

版權 (c) 2015 - 現在 LibDriver 版權所有

MIT 許可證（MIT）

特此免費授予任何獲得本軟件副本和相關文檔文件（下稱“軟件”）的人不受限制地處置該軟件的權利，包括不受限制地使用、複製、修改、合併、發布、分發、轉授許可和/或出售該軟件副本，以及再授權被配發了本軟件的人如上的權利，須在下列條件下：

上述版權聲明和本許可聲明應包含在該軟件的所有副本或實質成分中。

本軟件是“如此”提供的，沒有任何形式的明示或暗示的保證，包括但不限於對適銷性、特定用途的適用性和不侵權的保證。在任何情況下，作者或版權持有人都不對任何索賠、損害或其他責任負責，無論這些追責來自合同、侵權或其它行為中，還是產生於、源於或有關於本軟件以及本軟件的使用或其它處置。

### 聯繫我們

請聯繫lishifenging@outlook.com。