EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 "Tower PCB"
Comment2 "Project: Mario Kart"
Comment3 "Purdue University ECE477: Senior Design"
Comment4 "Author: Andre Hatushikano"
$EndDescr
$Comp
L power:GND #PWR06
U 1 1 62097EC1
P 6400 1450
F 0 "#PWR06" H 6400 1200 50  0001 C CNN
F 1 "GND" H 6405 1277 50  0000 C CNN
F 2 "" H 6400 1450 50  0001 C CNN
F 3 "" H 6400 1450 50  0001 C CNN
	1    6400 1450
	-1   0    0    1   
$EndComp
Wire Wire Line
	6700 1800 6100 1800
Wire Wire Line
	6400 1700 6400 1450
$Comp
L power:GND #PWR09
U 1 1 620AA4E8
P 8100 4300
F 0 "#PWR09" H 8100 4050 50  0001 C CNN
F 1 "GND" H 8105 4127 50  0000 C CNN
F 2 "" H 8100 4300 50  0001 C CNN
F 3 "" H 8100 4300 50  0001 C CNN
	1    8100 4300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR07
U 1 1 620AB4E7
P 6400 4350
F 0 "#PWR07" H 6400 4100 50  0001 C CNN
F 1 "GND" H 6405 4177 50  0000 C CNN
F 2 "" H 6400 4350 50  0001 C CNN
F 3 "" H 6400 4350 50  0001 C CNN
	1    6400 4350
	1    0    0    -1  
$EndComp
Wire Wire Line
	6400 3100 6400 4350
$Comp
L Regulator_Linear:NCP1117-3.3_SOT223 U1
U 1 1 620D9726
P 3650 1800
F 0 "U1" H 3650 2042 50  0000 C CNN
F 1 "NCP1117-3.3_SOT223" H 3650 1951 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-223-3_TabPin2" H 3650 2000 50  0001 C CNN
F 3 "http://www.onsemi.com/pub_link/Collateral/NCP1117-D.PDF" H 3750 1550 50  0001 C CNN
	1    3650 1800
	1    0    0    -1  
$EndComp
Wire Wire Line
	3950 1800 4550 1800
Wire Wire Line
	4550 1800 4550 1550
$Comp
L power:GND #PWR02
U 1 1 620DE31F
P 3650 2100
F 0 "#PWR02" H 3650 1850 50  0001 C CNN
F 1 "GND" H 3655 1927 50  0000 C CNN
F 2 "" H 3650 2100 50  0001 C CNN
F 3 "" H 3650 2100 50  0001 C CNN
	1    3650 2100
	1    0    0    -1  
$EndComp
Text GLabel 3350 1800 0    50   Input ~ 0
5V
$Comp
L Device:C C2
U 1 1 6210AA37
P 6250 1700
F 0 "C2" V 5998 1700 50  0000 C CNN
F 1 "100nF" V 6089 1700 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 6288 1550 50  0001 C CNN
F 3 "~" H 6250 1700 50  0001 C CNN
	1    6250 1700
	0    1    1    0   
$EndComp
Connection ~ 6400 1700
Wire Wire Line
	6100 1700 6100 1800
Text GLabel 6700 2200 0    50   Input ~ 0
IO34
Text GLabel 6700 2300 0    50   Input ~ 0
IO35
Text GLabel 6700 2400 0    50   Input ~ 0
IO32
Text GLabel 6700 2500 0    50   Input ~ 0
IO33
Text GLabel 6700 2600 0    50   Input ~ 0
IO25
Text GLabel 6700 2700 0    50   Input ~ 0
IO26
Text GLabel 6700 2800 0    50   Input ~ 0
IO27
Text GLabel 4550 1550 1    50   Input ~ 0
Vcc
$Comp
L Connector_Generic:Conn_01x09 J3
U 1 1 6210FE94
P 3800 3300
F 0 "J3" V 3925 3296 50  0000 C CNN
F 1 "Conn_01x09" V 4016 3296 50  0000 C CNN
F 2 "Connector_PinSocket_1.00mm:PinSocket_1x09_P1.00mm_Vertical" H 3800 3300 50  0001 C CNN
F 3 "~" H 3800 3300 50  0001 C CNN
	1    3800 3300
	0    1    1    0   
$EndComp
Text GLabel 4000 3100 1    50   Input ~ 0
IO34
Text GLabel 3900 3100 1    50   Input ~ 0
IO35
Text GLabel 3800 3100 1    50   Input ~ 0
IO32
Text GLabel 3700 3100 1    50   Input ~ 0
IO33
Text GLabel 3600 3100 1    50   Input ~ 0
IO25
Text GLabel 3500 3100 1    50   Input ~ 0
IO26
Text GLabel 3400 3100 1    50   Input ~ 0
IO27
Text GLabel 4200 3100 1    50   Input ~ 0
Vcc
$Comp
L power:GND #PWR04
U 1 1 62110F59
P 4100 2850
F 0 "#PWR04" H 4100 2600 50  0001 C CNN
F 1 "GND" H 4105 2677 50  0000 C CNN
F 2 "" H 4100 2850 50  0001 C CNN
F 3 "" H 4100 2850 50  0001 C CNN
	1    4100 2850
	-1   0    0    1   
$EndComp
Wire Wire Line
	4100 3100 4100 2850
$Comp
L Connector_Generic:Conn_01x02 J1
U 1 1 6211281E
P 1750 2450
F 0 "J1" V 1622 2530 50  0000 L CNN
F 1 "Conn_01x02" V 1713 2530 50  0000 L CNN
F 2 "Connector_PinHeader_1.00mm:PinHeader_1x02_P1.00mm_Vertical" H 1750 2450 50  0001 C CNN
F 3 "~" H 1750 2450 50  0001 C CNN
	1    1750 2450
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR01
U 1 1 62112F4D
P 1750 2250
F 0 "#PWR01" H 1750 2000 50  0001 C CNN
F 1 "GND" H 1755 2077 50  0000 C CNN
F 2 "" H 1750 2250 50  0001 C CNN
F 3 "" H 1750 2250 50  0001 C CNN
	1    1750 2250
	-1   0    0    1   
$EndComp
Text GLabel 1650 2250 1    50   Input ~ 0
5V
$Comp
L Device:R R1
U 1 1 62115A53
P 5750 2050
F 0 "R1" V 5543 2050 50  0000 C CNN
F 1 "10k" V 5634 2050 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 5680 2050 50  0001 C CNN
F 3 "~" H 5750 2050 50  0001 C CNN
	1    5750 2050
	0    1    1    0   
$EndComp
Wire Wire Line
	6350 2050 6350 1900
Wire Wire Line
	6350 1900 6700 1900
$Comp
L power:GND #PWR05
U 1 1 621177AC
P 5050 2200
F 0 "#PWR05" H 5050 1950 50  0001 C CNN
F 1 "GND" H 5055 2027 50  0000 C CNN
F 2 "" H 5050 2200 50  0001 C CNN
F 3 "" H 5050 2200 50  0001 C CNN
	1    5050 2200
	1    0    0    -1  
$EndComp
Connection ~ 5450 2050
Wire Wire Line
	5450 2050 5600 2050
Connection ~ 5450 1800
Wire Wire Line
	5450 1800 5450 2050
$Comp
L Switch:SW_Push SW1
U 1 1 621137FF
P 5250 2050
F 0 "SW1" H 5250 2335 50  0000 C CNN
F 1 "SW_Push" H 5250 2244 50  0000 C CNN
F 2 "Button_Switch_THT:SW_TH_Tactile_Omron_B3F-10xx" H 5250 2250 50  0001 C CNN
F 3 "~" H 5250 2250 50  0001 C CNN
	1    5250 2050
	1    0    0    -1  
$EndComp
Text GLabel 5450 1500 1    50   Input ~ 0
Vcc
Wire Wire Line
	5450 1800 5450 1500
$Comp
L Device:R R2
U 1 1 62123A94
P 8350 1300
F 0 "R2" H 8280 1254 50  0000 R CNN
F 1 "10k" H 8280 1345 50  0000 R CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 8280 1300 50  0001 C CNN
F 3 "~" H 8350 1300 50  0001 C CNN
	1    8350 1300
	-1   0    0    1   
$EndComp
Wire Wire Line
	8100 2100 8350 2100
$Comp
L power:GND #PWR08
U 1 1 621259D0
P 8050 1150
F 0 "#PWR08" H 8050 900 50  0001 C CNN
F 1 "GND" H 8055 977 50  0000 C CNN
F 2 "" H 8050 1150 50  0001 C CNN
F 3 "" H 8050 1150 50  0001 C CNN
	1    8050 1150
	1    0    0    -1  
$EndComp
Text GLabel 8150 750  1    50   Input ~ 0
Vcc
Wire Wire Line
	5450 1800 6100 1800
Connection ~ 6100 1800
Wire Wire Line
	8350 1450 8350 2100
Text GLabel 8100 3100 2    50   Input ~ 0
TX
Text GLabel 8100 3000 2    50   Input ~ 0
RX
Text GLabel 8100 2500 2    50   Input ~ 0
CTS
Text GLabel 8100 2400 2    50   Input ~ 0
DTR
$Comp
L Connector_Generic:Conn_01x06 J2
U 1 1 621305FA
P 3750 5050
F 0 "J2" V 3622 5330 50  0000 L CNN
F 1 "Conn_01x06" V 3713 5330 50  0000 L CNN
F 2 "Connector_PinSocket_1.00mm:PinSocket_1x06_P1.00mm_Vertical" H 3750 5050 50  0001 C CNN
F 3 "~" H 3750 5050 50  0001 C CNN
	1    3750 5050
	0    1    1    0   
$EndComp
Text GLabel 3650 4850 1    50   Input ~ 0
TX
Text GLabel 3550 4850 1    50   Input ~ 0
RX
Text GLabel 3850 4850 1    50   Input ~ 0
CTS
Text GLabel 3450 4850 1    50   Input ~ 0
DTR
Text GLabel 3750 4850 1    50   Input ~ 0
Vcc
$Comp
L power:GND #PWR03
U 1 1 62130F50
P 3950 4800
F 0 "#PWR03" H 3950 4550 50  0001 C CNN
F 1 "GND" H 3955 4627 50  0000 C CNN
F 2 "" H 3950 4800 50  0001 C CNN
F 3 "" H 3950 4800 50  0001 C CNN
	1    3950 4800
	-1   0    0    1   
$EndComp
Wire Notes Line
	4700 4400 4700 5400
Wire Notes Line
	4700 5400 3150 5400
Wire Notes Line
	3150 5400 3150 4400
Wire Notes Line
	3150 4400 4700 4400
Text Notes 4050 4400 0    50   ~ 0
UART connectors\n
Wire Wire Line
	3950 4850 3950 4800
Wire Notes Line
	3150 3650 4700 3650
Wire Notes Line
	4700 3650 4700 2600
Wire Notes Line
	4700 2600 3150 2600
Wire Notes Line
	3150 2600 3150 3650
Text Notes 4050 2600 0    50   ~ 0
Extra Connectors\n
Wire Notes Line
	1400 1900 2400 1900
Wire Notes Line
	2400 1900 2400 2650
Wire Notes Line
	2400 2650 1400 2650
Wire Notes Line
	1400 2650 1400 1900
Text Notes 1400 1900 0    50   ~ 0
Wall charger connections
Wire Notes Line
	3050 2400 4700 2400
Wire Notes Line
	4700 2400 4700 1250
Wire Notes Line
	4700 1250 3050 1250
Wire Notes Line
	3050 1250 3050 2400
Text Notes 4100 1250 0    50   ~ 0
Linear regulator\n
Wire Notes Line
	4900 2400 4900 1250
Wire Notes Line
	4900 1250 6050 1250
Wire Notes Line
	6050 2400 4900 2400
Wire Notes Line
	6050 1250 6050 2400
Text Notes 5700 1250 0    50   ~ 0
Reset pin\n
Wire Notes Line
	8650 1450 7800 1450
Wire Notes Line
	7800 1450 7800 550 
Wire Notes Line
	7800 550  8650 550 
Wire Notes Line
	8650 550  8650 1450
Text Notes 8350 550  0    50   ~ 0
Boot pin
Wire Wire Line
	5900 2050 5950 2050
$Comp
L Device:C C1
U 1 1 62144925
P 5950 2200
F 0 "C1" H 5835 2154 50  0000 R CNN
F 1 "100nF" H 5835 2245 50  0000 R CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 5988 2050 50  0001 C CNN
F 3 "~" H 5950 2200 50  0001 C CNN
	1    5950 2200
	-1   0    0    1   
$EndComp
Connection ~ 5950 2050
Wire Wire Line
	5950 2050 6350 2050
Wire Wire Line
	5050 2050 5050 2200
Wire Wire Line
	5950 2350 5350 2350
Wire Wire Line
	5350 2350 5350 2200
Wire Wire Line
	5350 2200 5050 2200
Connection ~ 5050 2200
$Comp
L Switch:SW_SPDT SW2
U 1 1 62171098
P 8150 950
F 0 "SW2" V 8104 1098 50  0000 L CNN
F 1 "SW_SPDT" V 8195 1098 50  0000 L CNN
F 2 "Button_Switch_THT:SW_Slide_1P2T_CK_OS102011MS2Q" H 8150 950 50  0001 C CNN
F 3 "~" H 8150 950 50  0001 C CNN
	1    8150 950 
	0    1    1    0   
$EndComp
Wire Wire Line
	8350 1150 8250 1150
Text GLabel 6700 3200 0    50   Input ~ 0
CS
Text GLabel 6700 2900 0    50   Input ~ 0
PDN
Text GLabel 8100 2600 2    50   Input ~ 0
SCK
Text GLabel 8100 2700 2    50   Input ~ 0
MISO
Text GLabel 8100 3300 2    50   Input ~ 0
MOSI
Connection ~ 8100 3500
Wire Wire Line
	8100 3500 8100 4300
Wire Wire Line
	8100 3400 8100 3500
Wire Wire Line
	6700 3100 6400 3100
Wire Wire Line
	6700 1700 6400 1700
$Comp
L controller-rescue:ESP32-SOLO-1-ESP-SOLO-1 IC1
U 1 1 6209664C
P 6700 1700
F 0 "IC1" H 7400 1965 50  0000 C CNN
F 1 "ESP32-SOLO-1" H 7400 1874 50  0000 C CNN
F 2 "RF_Module:ESP32-WROOM-32" H 7950 1800 50  0001 L CNN
F 3 "https://www.espressif.com/sites/default/files/documentation/esp32-solo-1_datasheet_en.pdf" H 7950 1700 50  0001 L CNN
F 4 "WiFi Modules (802.11) SMD Module, ESP32-S0WD, 32Mbits SPI flash, UART mode," H 7950 1600 50  0001 L CNN "Description"
F 5 "" H 7950 1500 50  0001 L CNN "Height"
F 6 "Espressif Systems" H 7950 1400 50  0001 L CNN "Manufacturer_Name"
F 7 "ESP32-SOLO-1" H 7950 1300 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "356-ESP32-SOLO-1" H 7950 1200 50  0001 L CNN "Mouser Part Number"
F 9 "https://www.mouser.co.uk/ProductDetail/Espressif-Systems/ESP32-SOLO-1?qs=w%2Fv1CP2dgqpIFRWX9FvikA%3D%3D" H 7950 1100 50  0001 L CNN "Mouser Price/Stock"
F 10 "" H 7950 1000 50  0001 L CNN "Arrow Part Number"
F 11 "" H 7950 900 50  0001 L CNN "Arrow Price/Stock"
	1    6700 1700
	1    0    0    -1  
$EndComp
Text GLabel 9300 3100 0    50   Input ~ 0
Vcc
$Comp
L power:GND #PWR011
U 1 1 621989B3
P 10750 3100
F 0 "#PWR011" H 10750 2850 50  0001 C CNN
F 1 "GND" H 10755 2927 50  0000 C CNN
F 2 "" H 10750 3100 50  0001 C CNN
F 3 "" H 10750 3100 50  0001 C CNN
	1    10750 3100
	0    -1   -1   0   
$EndComp
Text GLabel 10350 3300 2    50   Input ~ 0
CS
Text GLabel 10350 3400 2    50   Input ~ 0
PDN
Text GLabel 9850 3200 0    50   Input ~ 0
SCK
Text GLabel 9850 3300 0    50   Input ~ 0
MOSI
Text GLabel 10350 3200 2    50   Input ~ 0
MISO
$Comp
L Device:C C3
U 1 1 62199683
P 10100 2650
F 0 "C3" V 9848 2650 50  0000 C CNN
F 1 "100nF" V 9939 2650 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 10138 2500 50  0001 C CNN
F 3 "~" H 10100 2650 50  0001 C CNN
	1    10100 2650
	0    1    1    0   
$EndComp
Wire Wire Line
	9850 3100 9550 3100
Wire Wire Line
	10350 3100 10600 3100
Wire Wire Line
	10600 3100 10600 2650
Wire Wire Line
	10600 2650 10250 2650
Connection ~ 10600 3100
Wire Wire Line
	10600 3100 10750 3100
Wire Wire Line
	9950 2650 9550 2650
Wire Wire Line
	9550 2650 9550 3100
Connection ~ 9550 3100
Wire Wire Line
	9550 3100 9300 3100
Text GLabel 9850 3400 0    50   Input ~ 0
INT
Text GLabel 9850 3500 0    50   Input ~ 0
AUDIO_L
Text GLabel 10350 3500 2    50   Input ~ 0
NC
Text GLabel 9850 3600 0    50   Input ~ 0
GPIO0
Text GLabel 10350 3600 2    50   Input ~ 0
GPIO1
Text GLabel 9850 3700 0    50   Input ~ 0
GPIO2
Text GLabel 10350 3700 2    50   Input ~ 0
GPIO3
Text GLabel 10350 3800 2    50   Input ~ 0
NC
Text GLabel 9850 3800 0    50   Input ~ 0
NC
$Comp
L power:GND #PWR010
U 1 1 6219D4F9
P 10350 4350
F 0 "#PWR010" H 10350 4100 50  0001 C CNN
F 1 "GND" H 10355 4177 50  0000 C CNN
F 2 "" H 10350 4350 50  0001 C CNN
F 3 "" H 10350 4350 50  0001 C CNN
	1    10350 4350
	1    0    0    -1  
$EndComp
$Comp
L Device:C C4
U 1 1 6219D99F
P 10550 4150
F 0 "C4" V 10298 4150 50  0000 C CNN
F 1 "100nF" V 10389 4150 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 10588 4000 50  0001 C CNN
F 3 "~" H 10550 4150 50  0001 C CNN
	1    10550 4150
	0    -1   -1   0   
$EndComp
Text GLabel 10700 3900 2    50   Input ~ 0
5V
$Comp
L Connector_Generic:Conn_02x10_Odd_Even J4
U 1 1 621955FB
P 10050 3500
F 0 "J4" H 10100 4117 50  0000 C CNN
F 1 "Conn_02x10_Odd_Even" H 10100 4026 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_2x10_P2.54mm_Vertical" H 10050 3500 50  0001 C CNN
F 3 "~" H 10050 3500 50  0001 C CNN
	1    10050 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	10350 4000 10350 4150
Wire Wire Line
	10700 3900 10350 3900
Wire Wire Line
	10400 4150 10350 4150
Connection ~ 10350 4150
Wire Wire Line
	10350 4150 10350 4350
Wire Wire Line
	10700 3900 10700 4150
Wire Wire Line
	10350 4150 9850 4150
Wire Wire Line
	9850 4150 9850 4000
Text GLabel 9850 3900 0    50   Input ~ 0
NC
Text GLabel 8100 2900 2    50   Input ~ 0
GPIO0
Text GLabel 8100 3200 2    50   Input ~ 0
GPIO1
Text GLabel 8100 1900 2    50   Input ~ 0
GPIO2
Text GLabel 8100 2300 2    50   Input ~ 0
GPIO3
$EndSCHEMATC
