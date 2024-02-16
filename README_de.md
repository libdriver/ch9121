[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver CH9121

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/ch9121/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE) 

CH9121 ist ein Chip, der eine transparente Übertragung zwischen Netzwerk und UART realisiert. Es integriert den TCP/IP-Protokollstapel, der eine bidirektionale transparente Übertragung zwischen Netzwerkdatenpaketen und seriellen Daten realisieren kann. Es hat 4 Arbeitsmodi: TCP CLIENT, TCP SERVER, UDP CLIENT und UDP SERVER. Die serielle Baudrate kann bis zu 921600 bps betragen. Es kann einfach durch obere Computersoftware oder serielle Befehle konfiguriert werden, was bequem und schnell ist.

LibDriver CH9121 ist der Treiber mit vollem Funktionsumfang von CH9121, der von LibDriver gestartet wurde. Er bietet TCP-Server, TCP-Client, UDP-Server, UDP-Client und andere Funktionen. LibDriver ist MISRA-konform.

### Inhaltsverzeichnis

  - [Anweisung](#Anweisung)
  - [Installieren](#Installieren)
  - [Nutzung](#Nutzung)
    - [example basic](#example-basic)
  - [Dokument](#Dokument)
  - [Beitrag](#Beitrag)
  - [Lizenz](#Lizenz)
  - [Kontaktieren Sie uns](#Kontaktieren-Sie-uns)

### Anweisung

/src enthält LibDriver CH9121-Quelldateien.

/interface enthält die plattformunabhängige Vorlage LibDriver CH9121 UART.

/test enthält den Testcode des LibDriver CH9121-Treibers und dieser Code kann die erforderliche Funktion des Chips einfach testen.

/example enthält LibDriver CH9121-Beispielcode.

/doc enthält das LibDriver CH9121-Offlinedokument.

/Datenblatt enthält CH9121-Datenblatt.

/project enthält den allgemeinen Beispielcode für Linux- und MCU-Entwicklungsboards. Alle Projekte verwenden das Shell-Skript, um den Treiber zu debuggen, und die detaillierten Anweisungen finden Sie in der README.md jedes Projekts.

/misra enthält die Ergebnisse des LibDriver MISRA Code Scans.

### Installieren

Verweisen Sie auf eine plattformunabhängige UART-Schnittstellenvorlage und stellen Sie Ihren Plattform-UART-Treiber fertig.

Fügen Sie das Verzeichnis /src, den Schnittstellentreiber für Ihre Plattform und Ihre eigenen Treiber zu Ihrem Projekt hinzu. Wenn Sie die Standardbeispieltreiber verwenden möchten, fügen Sie das Verzeichnis /example zu Ihrem Projekt hinzu.

### Nutzung

Sie können auf die Beispiele im Verzeichnis /example zurückgreifen, um Ihren eigenen Treiber zu vervollständigen. Wenn Sie die Standardprogrammierbeispiele verwenden möchten, erfahren Sie hier, wie Sie diese verwenden.

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

### Dokument

Online-Dokumente: [https://www.libdriver.com/docs/ch9121/index.html](https://www.libdriver.com/docs/ch9121/index.html).

Offline-Dokumente: /doc/html/index.html.

### Beitrag

Bitte beachten Sie CONTRIBUTING.md.

### Lizenz

Urheberrechte © (c) 2015 - Gegenwart LibDriver Alle Rechte vorbehalten



Die MIT-Lizenz (MIT)



Hiermit wird jeder Person kostenlos die Erlaubnis erteilt, eine Kopie zu erhalten

dieser Software und zugehörigen Dokumentationsdateien (die „Software“) zu behandeln

in der Software ohne Einschränkung, einschließlich, aber nicht beschränkt auf die Rechte

zu verwenden, zu kopieren, zu modifizieren, zusammenzuführen, zu veröffentlichen, zu verteilen, unterzulizenzieren und/oder zu verkaufen

Kopien der Software und Personen, denen die Software gehört, zu gestatten

dazu eingerichtet werden, unter folgenden Bedingungen:



Der obige Urheberrechtshinweis und dieser Genehmigungshinweis müssen in allen enthalten sein

Kopien oder wesentliche Teile der Software.



DIE SOFTWARE WIRD "WIE BESEHEN" BEREITGESTELLT, OHNE JEGLICHE GEWÄHRLEISTUNG, AUSDRÜCKLICH ODER

STILLSCHWEIGEND, EINSCHLIESSLICH, ABER NICHT BESCHRÄNKT AUF DIE GEWÄHRLEISTUNG DER MARKTGÄNGIGKEIT,

EIGNUNG FÜR EINEN BESTIMMTEN ZWECK UND NICHTVERLETZUNG VON RECHTEN DRITTER. IN KEINEM FALL DARF DAS

AUTOREN ODER URHEBERRECHTSINHABER HAFTEN FÜR JEGLICHE ANSPRÜCHE, SCHÄDEN ODER ANDERE

HAFTUNG, OB AUS VERTRAG, DELIKT ODER ANDERWEITIG, ENTSTEHEND AUS,

AUS ODER IM ZUSAMMENHANG MIT DER SOFTWARE ODER DER VERWENDUNG ODER ANDEREN HANDLUNGEN MIT DER

SOFTWARE.

### Kontaktieren Sie uns

Bitte senden Sie eine E-Mail an lishifenging@outlook.com.