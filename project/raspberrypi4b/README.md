### 1. Board

#### 1.1 Board Info

Board Name: Raspberry Pi 4B.

UART Pin: TX/RX GPIO14/GPIO15.

GPIO Pin: RESET/CFG GPIO27/GPIO17.

### 2. Install

#### 2.1 Dependencies

Install the necessary dependencies.

```shell
sudo apt-get install libgpiod-dev pkg-config cmake -y
```

#### 2.2 Makefile

Build the project.

```shell
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

#### 2.3 CMake

Build the project.

```shell
mkdir build && cd build 
cmake .. 
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

Test the project and this is optional.

```shell
# open another terminal
./ch9121_server 

# use the CMake terminal
make test
```

Find the compiled library in CMake. 

```cmake
find_package(ch9121 REQUIRED)
```

### 3. CH9121

#### 3.1 Command Instruction

1. Show ch9121 chip and driver information.

   ```shell
   ch9121 (-i | --information)
   ```

2. Show ch9121 help.

   ```shell
   ch9121 (-h | --help)
   ```

3. Show ch9121 pin connections of the current board.

   ```shell
   ch9121 (-p | --port)
   ```

4. Run ch9121 register test.

   ```shell
   ch9121 (-t reg | --test=reg)
   ```

5. Run ch9121 net test.

   ```shell
   ch9121 (-t net | --test=net) [--mode=<TCP_CLIENT | TCP_SERVER | UDP_CLIENT | UDP_SERVER>]
   ```

6. Run ch9121 net init function.

   ```shell
   ch9121 (-e net-init | --example=net-init)
   ```

7. Run ch9121 net deinit function.

   ```shell
   ch9121 (-e net-deinit | --example=net-deinit)
   ```

8. Run ch9121 config function, sip is the source ip, sport is the source port, mask is the subnet mask, gateway is the gateway, dip is the dest ip and dport is the dest port.

   ```shell
   ch9121 (-e net-cfg | --example=net-cfg) [--uport=<1 | 2>] [--mode=<TCP_CLIENT | TCP_SERVER | UDP_CLIENT | UDP_SERVER>] [--sip=<sip>] [--sport=<sport>] [--mask=<mask>] [--gateway=<gateway>] [--dip=<dip>] [--dport=<dport>]
   ```

9. Run ch9121 net write function, str is the write data.

   ```shell
   ch9121 (-e net-write | --example=net-write) [--data=<str>]
   ```

10. Run ch9121 net read function.

    ```shell
    ch9121 (-e net-read | --example=net-read)
    ```
    
#### 3.2 How to run

```shell
# open one terminal and run the server
./ch9121_server 
```
```shell
# open another terminal and sent the command
./ch9121 xxx xxx xxx ...
```

#### 3.3 Command Example

```shell
./ch9121 -i

ch9121: chip is WCH CH9121.
ch9121: manufacturer is WCH.
ch9121: interface is UART.
ch9121: driver version is 1.0.
ch9121: min supply voltage is 2.7V.
ch9121: max supply voltage is 3.6V.
ch9121: max current is 190.00mA.
ch9121: max temperature is 85.0C.
ch9121: min temperature is -40.0C.
```

```shell
./ch9121 -p

ch9121: TX connected to GPIO15(BCM).
ch9121: RX connected to GPIO14(BCM).
```

```shell
./ch9121 -t reg

ch9121: chip is WCH CH9121.
ch9121: manufacturer is WCH.
ch9121: interface is UART.
ch9121: driver version is 1.0.
ch9121: min supply voltage is 2.7V.
ch9121: max supply voltage is 3.6V.
ch9121: max current is 190.00mA.
ch9121: max temperature is 85.0C.
ch9121: min temperature is -40.0C.
ch9121: start register test.
ch9121: ch9121_get_version test.
ch9121: version is 0x27.
ch9121: ch9121_save_to_eeprom test.
ch9121: check save to eeprom ok.
ch9121: ch9121_exit test.
ch9121: check exit ok.
ch9121: ch9121_set_port2 test.
ch9121: disable port2.
ch9121: check port2 ok.
ch9121: enable port2.
ch9121: check port2 ok.
ch9121: ch9121_set_disconnect_with_no_rj45 test.
ch9121: disable disconnect with no rj45.
ch9121: check disconnect with no rj45 ok.
ch9121: enable disconnect with no rj45.
ch9121: check disconnect with no rj45 ok.
ch9121: ch9121_set_domain test.
ch9121: set domain www.ch9121.com.
ch9121: check domain ok.
ch9121: ch9121_set_dhcp test.
ch9121: disable dhcp.
ch9121: check dhcp ok.
ch9121: enable dhcp.
ch9121: check dhcp ok.
ch9121: ch9121_get_mac test.
ch9121: mac is 0x84 0xC2 0xE4 0x5D 0x97 0x43.
ch9121: ch9121_set_ip/ch9121_get_ip test.
ch9121: set ip 163.151.162.85.
ch9121: check ip ok.
ch9121: ch9121_set_subnet_mask/ch9121_get_subnet_mask test.
ch9121: set subnet mask 83.190.241.252.
ch9121: check subnet mask ok.
ch9121: ch9121_set_gateway/ch9121_get_gateway test.
ch9121: set gateway 249.121.107.82.
ch9121: check gateway ok.
ch9121: ch9121_get_status test.
ch9121: get port1 status disconnect.
ch9121: get port2 status disconnect.
ch9121: ch9121_set_mode/ch9121_get_mode test.
ch9121: set port1 tcp server mode.
ch9121: check mode ok.
ch9121: set port1 tcp client mode.
ch9121: check mode ok.
ch9121: set port1 udp server mode.
ch9121: check mode ok.
ch9121: set port1 udp client mode.
ch9121: check mode ok.
ch9121: set port2 tcp server mode.
ch9121: check mode ok.
ch9121: set port2 tcp client mode.
ch9121: check mode ok.
ch9121: set port2 udp server mode.
ch9121: check mode ok.
ch9121: set port2 udp client mode.
ch9121: check mode ok.
ch9121: ch9121_set_source_port/ch9121_get_source_port test.
ch9121: set source port1 28835.
ch9121: check source port ok.
ch9121: set source port2 24754.
ch9121: check source port ok.
ch9121: ch9121_set_dest_ip/ch9121_get_dest_ip test.
ch9121: set port1 dest ip 233.226.45.81.
ch9121: check dest ip ok.
ch9121: set port2 dest ip 142.31.86.8.
ch9121: check dest ip ok.
ch9121: ch9121_set_dest_port/ch9121_get_dest_port test.
ch9121: set dest port1 57207.
ch9121: check dest port ok.
ch9121: set dest port2 43644.
ch9121: check dest port ok.
ch9121: ch9121_set_uart_baud/ch9121_get_uart_baud test.
ch9121: set port1 uart baud 9600.
ch9121: check uart baud ok.
ch9121: set port2 uart baud 9600.
ch9121: check uart baud ok.
ch9121: ch9121_set_uart_config/ch9121_get_uart_config test.
ch9121: set port1 data_bit 8, parity none, stop_bit 1.
ch9121: check uart data bit ok.
ch9121: check uart parity ok.
ch9121: check uart stop bit ok.
ch9121: set port2 data_bit 8, parity none, stop_bit 1.
ch9121: check uart data bit ok.
ch9121: check uart parity ok.
ch9121: check uart stop bit ok.
ch9121: ch9121_set_uart_timeout/ch9121_get_uart_timeout test.
ch9121: set port1 uart timeout 167.
ch9121: check uart timeout ok.
ch9121: set port2 uart timeout 5.
ch9121: check uart timeout ok.
ch9121: ch9121_set_source_port_random test.
ch9121: enable port1 source port random.
ch9121: check source port random ok.
ch9121: disable port1 source port random.
ch9121: check source port random ok.
ch9121: enable port2 source port random.
ch9121: check source port random ok.
ch9121: disable port2 source port random.
ch9121: check source port random ok.
ch9121: ch9121_set_uart_buffer_length test.
ch9121: set port1 uart buffer length 140.
ch9121: check uart buffer length ok.
ch9121: set port2 uart buffer length 151.
ch9121: check uart buffer length ok.
ch9121: ch9121_set_uart_flush test.
ch9121: enable port1 uart flush.
ch9121: check uart flush ok.
ch9121: enable port2 uart flush.
ch9121: check uart flush ok.
ch9121: ch9121_uart_timeout_convert_to_register/ch9121_uart_timeout_convert_to_data test.
ch9121: uart timeout convert to register 35.
ch9121: check uart timeout convert ok.
ch9121: finish register test.
```

```shell
./ch9121 -t net --mode=TCP_CLIENT

ch9121: chip is WCH CH9121.
ch9121: manufacturer is WCH.
ch9121: interface is UART.
ch9121: driver version is 1.0.
ch9121: min supply voltage is 2.7V.
ch9121: max supply voltage is 3.6V.
ch9121: max current is 190.00mA.
ch9121: max temperature is 85.0C.
ch9121: min temperature is -40.0C.
ch9121: start net test.
ch9121: tcp client dest port 2000, dest ip 192.168.1.10.
ch9121: write LibDriver.
ch9121: finish net test.
```

```shell
./ch9121 -t net --mode=TCP_SERVER

ch9121: chip is WCH CH9121.
ch9121: manufacturer is WCH.
ch9121: interface is UART.
ch9121: driver version is 1.0.
ch9121: min supply voltage is 2.7V.
ch9121: max supply voltage is 3.6V.
ch9121: max current is 190.00mA.
ch9121: max temperature is 85.0C.
ch9121: min temperature is -40.0C.
ch9121: start net test.
ch9121: tcp server src port 1000, src ip 192.168.1.230.
ch9121: read L.
ch9121: finish net test.
```

```shell
./ch9121 -t net --mode=UDP_CLIENT

ch9121: chip is WCH CH9121.
ch9121: manufacturer is WCH.
ch9121: interface is UART.
ch9121: driver version is 1.0.
ch9121: min supply voltage is 2.7V.
ch9121: max supply voltage is 3.6V.
ch9121: max current is 190.00mA.
ch9121: max temperature is 85.0C.
ch9121: min temperature is -40.0C.
ch9121: start net test.
ch9121: udp client dest port 2000, dest ip 192.168.1.10.
ch9121: write LibDriver.
ch9121: write LibDriver.
ch9121: write LibDriver.
ch9121: write LibDriver.
ch9121: write LibDriver.
ch9121: write LibDriver.
ch9121: write LibDriver.
ch9121: write LibDriver.
ch9121: write LibDriver.
ch9121: write LibDriver.
ch9121: finish net test.
```

```shell
./ch9121 -t net --mode=UDP_SERVER

ch9121: chip is WCH CH9121.
ch9121: manufacturer is WCH.
ch9121: interface is UART.
ch9121: driver version is 1.0.
ch9121: min supply voltage is 2.7V.
ch9121: max supply voltage is 3.6V.
ch9121: max current is 190.00mA.
ch9121: max temperature is 85.0C.
ch9121: min temperature is -40.0C.
ch9121: start net test.
ch9121: udp server src port 1000, src ip 192.168.1.230.
ch9121: read L.
ch9121: finish net test.
```

```shell
./ch9121 -e net-init

ch9121: net init.
```

```shell
./ch9121 -e net-deinit

ch9121: net deinit.
```

```shell
./ch9121 -e net-cfg --uport=1 --mode=TCP_CLIENT --sip=192.168.1.230 --sport=1000 --mask=255.255.255.0 --gateway=192.168.1.1 --dip=192.168.1.10 --dport=2000

ch9121: source ip 192.168.1.230.
ch9121: source port 1000.
ch9121: subnet mask 255.255.255.0.
ch9121: gateway 192.168.1.1.
ch9121: dest ip 192.168.1.10.
ch9121: dest port 2000.
```

```shell
./ch9121 -e net-write --data=LibDriver

ch9121: net write LibDriver.
```

```shell
./ch9121 -e net-read

ch9121: net read LibDriver.
```

```shell
./ch9121 -h

Usage:
  ch9121 (-i | --information)
  ch9121 (-h | --help)
  ch9121 (-p | --port)
  ch9121 (-t reg | --test=reg)
  ch9121 (-t net | --test=net) [--mode=<TCP_CLIENT | TCP_SERVER | UDP_CLIENT | UDP_SERVER>]
  ch9121 (-e net-init | --example=net-init)
  ch9121 (-e net-deinit | --example=net-deinit)
  ch9121 (-e net-cfg | --example=net-cfg) [--uport=<1 | 2>] [--mode=<TCP_CLIENT | TCP_SERVER | UDP_CLIENT | UDP_SERVER>]
         [--sip=<sip>] [--sport=<sport>] [--mask=<mask>] [--gateway=<gateway>] [--dip=<dip>] [--dport=<dport>]
  ch9121 (-e net-write | --example=net-write) [--data=<str>]
  ch9121 (-e net-read | --example=net-read)

Options:
  -e <net-init | net-deinit | net-cfg | net-write | net-read>, --example=<net-init | net-deinit | net-cfg | net-write | net-read>
                             Run the driver example.
      --data=<str>           Set write data.([default: LibDriver])
      --dip=<dip>            Set the dest ip.([default: 192.168.1.10])
      --dport=<dport>        Set dest port.([default: 1000])
      --gateway=<gateway>    Set the gateway.([default: 192.168.1.1])
  -h, --help                 Show the help.
  -i, --information          Show the chip information.
      --mask=<mask>          Set the subnet mask.([default: 255.255.255.0])
      --mode=<TCP_CLIENT | TCP_SERVER | UDP_CLIENT | UDP_SERVER
                             Set the chip mode.([default: TCP_CLIENT])
  -p, --port                 Display the pin connections of the current board.
      --sip=<sip>            Set the source ip.([default: 192.168.1.230])
      --sport=<sport>        Set source port.([default: 2000])
  -t <reg | net>, --test=<reg | net>
                             Run the driver test.
      --uport=<1 | 2>        Set the uart port.([default: 1])
```
