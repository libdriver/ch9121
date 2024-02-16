[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver CH9121

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/ch9121/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

CH9121は、ネットワークとUART間のトランスペアレント伝送を実現するチップです。 ネットワーク データ パケットとシリアル データ間の双方向透過伝送を実現できる TCP/IP プロトコル スタックを統合します。 TCP CLIENT、TCP SERVER、UDP CLIENT、UDP SERVER の 4 つの動作モードがあります。 シリアルボーレートは最大 921600bps です。 上位のコンピュータ ソフトウェアまたはシリアル コマンドで簡単に設定でき、便利で迅速です。

LibDriver CH9121 は、LibDriver が起動する CH9121 の全機能ドライバーです。tcp サーバー、tcp クライアント、udp サーバー、udp クライアントなどの機能を提供します。 LibDriver は MISRA に準拠しています。

### 目次

  - [説明](#説明)
  - [インストール](#インストール)
  - [使用](#使用)
    - [example basic](#example-basic)
  - [ドキュメント](#ドキュメント)
  - [貢献](#貢献)
  - [著作権](#著作権)
  - [連絡して](#連絡して)

### 説明

/ srcディレクトリには、LibDriver CH9121のソースファイルが含まれています。

/ interfaceディレクトリには、LibDriver CH9121用のプラットフォームに依存しないUARTバステンプレートが含まれています。

/ testディレクトリには、チップの必要な機能を簡単にテストできるLibDriver CH9121ドライバーテストプログラムが含まれています。

/ exampleディレクトリには、LibDriver CH9121プログラミング例が含まれています。

/ docディレクトリには、LibDriver CH9121オフラインドキュメントが含まれています。

/ datasheetディレクトリには、CH9121データシートが含まれています。

/ projectディレクトリには、一般的に使用されるLinuxおよびマイクロコントローラー開発ボードのプロジェクトサンプルが含まれています。 すべてのプロジェクトは、デバッグ方法としてシェルスクリプトを使用しています。詳細については、各プロジェクトのREADME.mdを参照してください。

/ misraはLibDriver misraコードスキャン結果を含む。

### インストール

/ interfaceディレクトリにあるプラットフォームに依存しないUARTバステンプレートを参照して、指定したプラットフォームのUARTバスドライバを完成させます。

/src ディレクトリ、プラットフォームのインターフェイス ドライバー、および独自のドライバーをプロジェクトに追加します。デフォルトのサンプル ドライバーを使用する場合は、/example ディレクトリをプロジェクトに追加します。

### 使用

/example ディレクトリ内のサンプルを参照して、独自のドライバーを完成させることができます。 デフォルトのプログラミング例を使用したい場合の使用方法は次のとおりです。

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

### ドキュメント

オンラインドキュメント: [https://www.libdriver.com/docs/ch9121/index.html](https://www.libdriver.com/docs/ch9121/index.html)。

オフラインドキュメント: /doc/html/index.html。

### 貢献

CONTRIBUTING.mdを参照してください。

### 著作権

著作権（c）2015-今 LibDriver 全著作権所有

MITライセンス（MIT）

このソフトウェアおよび関連するドキュメントファイル（「ソフトウェア」）のコピーを取得した人は、無制限の使用、複製、変更、組み込み、公開、配布、サブライセンスを含む、ソフトウェアを処分する権利を制限なく付与されます。ソフトウェアのライセンスおよび/またはコピーの販売、および上記のようにソフトウェアが配布された人の権利のサブライセンスは、次の条件に従うものとします。

上記の著作権表示およびこの許可通知は、このソフトウェアのすべてのコピーまたは実体に含まれるものとします。

このソフトウェアは「現状有姿」で提供され、商品性、特定目的への適合性、および非侵害の保証を含むがこれらに限定されない、明示または黙示を問わず、いかなる種類の保証もありません。 いかなる場合も、作者または著作権所有者は、契約、不法行為、またはその他の方法で、本ソフトウェアおよび本ソフトウェアの使用またはその他の廃棄に起因または関連して、請求、損害、またはその他の責任を負わないものとします。

### 連絡して

お問い合わせくださいlishifenging@outlook.com。