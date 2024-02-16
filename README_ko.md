[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver CH9121

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/ch9121/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

CH9121은 네트워크와 UART 간의 투명한 전송을 구현하는 칩입니다. 네트워크 데이터 패킷과 직렬 데이터 간의 양방향 투명 전송을 실현할 수 있는 TCP/IP 프로토콜 스택을 통합합니다. TCP CLIENT, TCP SERVER, UDP CLIENT 및 UDP SERVER의 4가지 작동 모드가 있습니다. 직렬 전송 속도는 최대 921600bps입니다. 그것은 편리하고 빠른 상위 컴퓨터 소프트웨어 또는 직렬 명령으로 쉽게 구성할 수 있습니다.

LibDriver CH9121은 LibDriver에 의해 시작된 CH9121의 전체 기능 드라이버입니다. 그것은 tcp 서버, tcp 클라이언트, udp 서버, udp 클라이언트 및 기타 기능을 제공합니다. LibDriver는 MISRA를 준수합니다.

### 콘텐츠

  - [설명](#설명)
  - [설치](#설치)
  - [사용](#사용)
    - [example basic](#example-basic)
  - [문서](#문서)
  - [기고](#기고)
  - [저작권](#저작권)
  - [문의하기](#문의하기)

### 설명

/src 디렉토리에는 LibDriver CH9121의 소스 파일이 포함되어 있습니다.

/interface 디렉토리에는 LibDriver CH9121용 플랫폼 독립적인 UART버스 템플릿이 포함되어 있습니다.

/test 디렉토리에는 LibDriver CH9121드라이버 테스트 프로그램이 포함되어 있어 칩의 필요한 기능을 간단히 테스트할 수 있습니다.

/example 디렉토리에는 LibDriver CH9121프로그래밍 예제가 포함되어 있습니다.

/doc 디렉토리에는 LibDriver CH9121오프라인 문서가 포함되어 있습니다.

/datasheet 디렉토리에는CH9121데이터시트가 있습니다.

/project 디렉토리에는 일반적으로 사용되는 Linux 및 마이크로컨트롤러 개발 보드의 프로젝트 샘플이 포함되어 있습니다. 모든 프로젝트는 디버깅 방법으로 셸 스크립트를 사용하며, 자세한 내용은 각 프로젝트의 README.md를 참조하십시오.

/misra 에는 LibDriver misra 코드 검색 결과가 포함됩니다.

### 설치

/interface 디렉토리에서 플랫폼 독립적인UART버스 템플릿을 참조하여 지정된 플랫폼에 대한 UART버스 드라이버를 완성하십시오.

/src 디렉터리, 플랫폼용 인터페이스 드라이버 및 자체 드라이버를 프로젝트에 추가합니다. 기본 예제 드라이버를 사용하려면 /example 디렉터리를 프로젝트에 추가합니다.

### 사용

/example 디렉터리의 예제를 참조하여 자신만의 드라이버를 완성할 수 있습니다. 기본 프로그래밍 예제를 사용하려는 경우 사용 방법은 다음과 같습니다.

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

### 문서

온라인 문서: [https://www.libdriver.com/docs/ch9121/index.html](https://www.libdriver.com/docs/ch9121/index.html).

오프라인 문서: /doc/html/index.html.

### 기고

CONTRIBUTING.md 를 참조하십시오.

### 저작권

저작권 (c) 2015 - 지금 LibDriver 판권 소유

MIT 라이선스(MIT)

이 소프트웨어 및 관련 문서 파일("소프트웨어")의 사본을 얻은 모든 사람은 이에 따라 무제한 사용, 복제, 수정, 통합, 출판, 배포, 2차 라이선스를 포함하여 소프트웨어를 처분할 수 있는 권리가 부여됩니다. 소프트웨어의 사본에 대한 라이선스 및/또는 판매, 그리고 소프트웨어가 위와 같이 배포된 사람의 권리에 대한 2차 라이선스는 다음 조건에 따릅니다.

위의 저작권 표시 및 이 허가 표시는 이 소프트웨어의 모든 사본 또는 내용에 포함됩니다.

이 소프트웨어는 상품성, 특정 목적에의 적합성 및 비침해에 대한 보증을 포함하되 이에 국한되지 않는 어떠한 종류의 명시적 또는 묵시적 보증 없이 "있는 그대로" 제공됩니다. 어떤 경우에도 저자 또는 저작권 소유자는 계약, 불법 행위 또는 기타 방식에 관계없이 소프트웨어 및 기타 소프트웨어 사용으로 인해 발생하거나 이와 관련하여 발생하는 청구, 손해 또는 기타 책임에 대해 책임을 지지 않습니다.

### 문의하기

연락주세요lishifenging@outlook.com.