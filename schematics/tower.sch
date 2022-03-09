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
L power:GND #PWR010
U 1 1 62097EC1
P 6000 1750
F 0 "#PWR010" H 6000 1500 50  0001 C CNN
F 1 "GND" H 6005 1577 50  0000 C CNN
F 2 "" H 6000 1750 50  0001 C CNN
F 3 "" H 6000 1750 50  0001 C CNN
	1    6000 1750
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR011
U 1 1 620AA4E8
P 8100 3900
F 0 "#PWR011" H 8100 3650 50  0001 C CNN
F 1 "GND" H 8105 3727 50  0000 C CNN
F 2 "" H 8100 3900 50  0001 C CNN
F 3 "" H 8100 3900 50  0001 C CNN
	1    8100 3900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR09
U 1 1 620AB4E7
P 6400 3950
F 0 "#PWR09" H 6400 3700 50  0001 C CNN
F 1 "GND" H 6405 3777 50  0000 C CNN
F 2 "" H 6400 3950 50  0001 C CNN
F 3 "" H 6400 3950 50  0001 C CNN
	1    6400 3950
	1    0    0    -1  
$EndComp
Text GLabel 6700 2200 0    50   Input ~ 0
IO34
Text GLabel 6700 2300 0    50   Input ~ 0
IO35
Text GLabel 6700 2400 0    50   Input ~ 0
IO32
Text GLabel 6700 2500 0    50   Input ~ 0
IO33
Text GLabel 8100 3100 2    50   Input ~ 0
TX
Text GLabel 8100 3000 2    50   Input ~ 0
RX
$Comp
L Connector_Generic:Conn_01x06 J2
U 1 1 621305FA
P 3750 4650
F 0 "J2" V 3622 4930 50  0000 L CNN
F 1 "Conn_01x06" V 3713 4930 50  0000 L CNN
F 2 "Connector_PinSocket_1.00mm:PinSocket_1x06_P1.00mm_Vertical" H 3750 4650 50  0001 C CNN
F 3 "~" H 3750 4650 50  0001 C CNN
	1    3750 4650
	0    1    1    0   
$EndComp
Text GLabel 3650 4450 1    50   Input ~ 0
TX
Text GLabel 3550 4450 1    50   Input ~ 0
RX
Text GLabel 3850 4450 1    50   Input ~ 0
CTS
Text GLabel 3450 4450 1    50   Input ~ 0
DTR
Text GLabel 3750 4450 1    50   Input ~ 0
Vcc
$Comp
L power:GND #PWR06
U 1 1 62130F50
P 3950 4400
F 0 "#PWR06" H 3950 4150 50  0001 C CNN
F 1 "GND" H 3955 4227 50  0000 C CNN
F 2 "" H 3950 4400 50  0001 C CNN
F 3 "" H 3950 4400 50  0001 C CNN
	1    3950 4400
	-1   0    0    1   
$EndComp
Wire Notes Line
	4700 4000 4700 5000
Wire Notes Line
	4700 5000 3150 5000
Wire Notes Line
	3150 5000 3150 4000
Wire Notes Line
	3150 4000 4700 4000
Text Notes 4050 4000 0    50   ~ 0
UART connectors\n
Wire Wire Line
	3950 4450 3950 4400
Text GLabel 6700 3200 0    50   Input ~ 0
CS
Text GLabel 8100 2600 2    50   Input ~ 0
SCK
Text GLabel 8100 2700 2    50   Input ~ 0
MISO
Text GLabel 8100 3300 2    50   Input ~ 0
MOSI
Wire Wire Line
	8100 3400 8100 3500
Wire Wire Line
	6700 3100 6400 3100
$Comp
L tower-rescue:ESP32-SOLO-1-ESP-SOLO-1-controller-rescue IC1
U 1 1 6209664C
P 6700 1700
F 0 "IC1" H 7400 1965 50  0000 C CNN
F 1 "ESP32-SOLO-1" H 7400 1874 50  0000 C CNN
F 2 "Mouser:ESP32SOLO1" H 7950 1800 50  0001 L CNN
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
L power:GND #PWR013
U 1 1 621989B3
P 10750 3100
F 0 "#PWR013" H 10750 2850 50  0001 C CNN
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
L Device:C C6
U 1 1 62199683
P 10100 2650
F 0 "C6" V 9848 2650 50  0000 C CNN
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
L power:GND #PWR012
U 1 1 6219D4F9
P 10350 4350
F 0 "#PWR012" H 10350 4100 50  0001 C CNN
F 1 "GND" H 10355 4177 50  0000 C CNN
F 2 "" H 10350 4350 50  0001 C CNN
F 3 "" H 10350 4350 50  0001 C CNN
	1    10350 4350
	1    0    0    -1  
$EndComp
$Comp
L Device:C C7
U 1 1 6219D99F
P 10550 4150
F 0 "C7" V 10298 4150 50  0000 C CNN
F 1 "100nF" V 10389 4150 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 10588 4000 50  0001 C CNN
F 3 "~" H 10550 4150 50  0001 C CNN
	1    10550 4150
	0    -1   -1   0   
$EndComp
Text GLabel 10700 3900 2    50   Input ~ 0
5V
$Comp
L Connector_Generic:Conn_02x10_Odd_Even J5
U 1 1 621955FB
P 10050 3500
F 0 "J5" H 10100 4117 50  0000 C CNN
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
Text GLabel 8100 2200 2    50   Input ~ 0
GPIO1
Text GLabel 8100 2000 2    50   Input ~ 0
GPIO2
Text GLabel 8100 2300 2    50   Input ~ 0
GPIO3
Text GLabel 5300 1750 0    50   Input ~ 0
Vcc
$Comp
L Device:C C5
U 1 1 621D55FD
P 5650 1750
F 0 "C5" V 5398 1750 50  0000 C CNN
F 1 "100nF" V 5489 1750 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 5688 1600 50  0001 C CNN
F 3 "~" H 5650 1750 50  0001 C CNN
	1    5650 1750
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R2
U 1 1 621D8EBD
P 1500 3750
F 0 "R2" V 1707 3750 50  0000 C CNN
F 1 "10k" V 1616 3750 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 1430 3750 50  0001 C CNN
F 3 "~" H 1500 3750 50  0001 C CNN
	1    1500 3750
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R3
U 1 1 621DD475
P 1500 4700
F 0 "R3" V 1707 4700 50  0000 C CNN
F 1 "10k" V 1616 4700 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 1430 4700 50  0001 C CNN
F 3 "~" H 1500 4700 50  0001 C CNN
	1    1500 4700
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1650 4700 1850 4700
Wire Wire Line
	1650 3750 1850 3750
Wire Wire Line
	1200 4350 1200 3750
Wire Wire Line
	1200 3750 1350 3750
Wire Wire Line
	1300 4100 1300 4700
Wire Wire Line
	1300 4700 1350 4700
Connection ~ 1300 4700
Wire Wire Line
	1200 3750 1000 3750
Connection ~ 1200 3750
Wire Wire Line
	1000 4700 1300 4700
Text GLabel 2250 3450 2    50   Input ~ 0
EN
Text GLabel 2250 5000 2    50   Input ~ 0
GPIO0
Text GLabel 1000 3750 0    50   Input ~ 0
DTR
Text GLabel 1000 4700 0    50   Input ~ 0
CTS
Text Notes 2250 3350 0    50   ~ 0
Program circuitry\n
Text GLabel 8100 2100 2    50   Input ~ 0
GPIO0
Text GLabel 6700 1900 0    50   Input ~ 0
EN
Wire Notes Line
	11050 4650 11050 2250
Wire Notes Line
	11050 2250 9000 2250
Wire Notes Line
	9000 2250 9000 4650
Wire Notes Line
	9000 4650 11050 4650
Text Notes 10050 2250 0    50   ~ 0
IDC Box Header to display\n
$Comp
L Switch:SW_Push SW1
U 1 1 6220C472
P 1250 5800
F 0 "SW1" H 1250 6085 50  0000 C CNN
F 1 "SW_Push" H 1250 5994 50  0000 C CNN
F 2 "Button_Switch_SMD:SW_SPST_CK_KXT3" H 1250 6000 50  0001 C CNN
F 3 "~" H 1250 6000 50  0001 C CNN
	1    1250 5800
	1    0    0    -1  
$EndComp
$Comp
L Device:C C1
U 1 1 6220CBE7
P 1250 6150
F 0 "C1" V 998 6150 50  0000 C CNN
F 1 "0.1uF" V 1089 6150 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 1288 6000 50  0001 C CNN
F 3 "~" H 1250 6150 50  0001 C CNN
	1    1250 6150
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR01
U 1 1 6220D2BC
P 850 6300
F 0 "#PWR01" H 850 6050 50  0001 C CNN
F 1 "GND" H 855 6127 50  0000 C CNN
F 2 "" H 850 6300 50  0001 C CNN
F 3 "" H 850 6300 50  0001 C CNN
	1    850  6300
	1    0    0    -1  
$EndComp
Wire Wire Line
	1100 6150 850  6150
Wire Wire Line
	850  6150 850  6300
Wire Wire Line
	1050 5800 850  5800
Wire Wire Line
	850  5800 850  6150
Connection ~ 850  6150
Wire Wire Line
	1400 6150 1650 6150
Wire Wire Line
	1650 6150 1650 5800
Wire Wire Line
	1650 5800 1450 5800
Wire Wire Line
	1650 5800 1950 5800
Connection ~ 1650 5800
Text GLabel 1950 5800 2    50   Input ~ 0
GPIO0
$Comp
L Switch:SW_Push SW2
U 1 1 62214B1E
P 3050 5800
F 0 "SW2" H 3050 6085 50  0000 C CNN
F 1 "SW_Push" H 3050 5994 50  0000 C CNN
F 2 "Button_Switch_SMD:SW_SPST_CK_KXT3" H 3050 6000 50  0001 C CNN
F 3 "~" H 3050 6000 50  0001 C CNN
	1    3050 5800
	1    0    0    -1  
$EndComp
$Comp
L Device:C C2
U 1 1 6221566F
P 3050 6150
F 0 "C2" V 2798 6150 50  0000 C CNN
F 1 "0.1uF" V 2889 6150 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 3088 6000 50  0001 C CNN
F 3 "~" H 3050 6150 50  0001 C CNN
	1    3050 6150
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR03
U 1 1 62215DC5
P 2550 6250
F 0 "#PWR03" H 2550 6000 50  0001 C CNN
F 1 "GND" H 2555 6077 50  0000 C CNN
F 2 "" H 2550 6250 50  0001 C CNN
F 3 "" H 2550 6250 50  0001 C CNN
	1    2550 6250
	1    0    0    -1  
$EndComp
Wire Wire Line
	2900 6150 2550 6150
Wire Wire Line
	2550 6150 2550 6250
Wire Wire Line
	2850 5800 2550 5800
Wire Wire Line
	2550 5800 2550 6150
Connection ~ 2550 6150
Wire Wire Line
	3200 6150 3500 6150
Wire Wire Line
	3500 6150 3500 5800
Wire Wire Line
	3500 5800 3250 5800
Wire Wire Line
	3500 5800 3800 5800
Connection ~ 3500 5800
Text GLabel 3800 5800 2    50   Input ~ 0
EN
Wire Notes Line
	700  6700 700  5400
Wire Notes Line
	2350 5400 2350 6700
Wire Notes Line
	4050 5400 4050 6700
Wire Notes Line
	700  5400 4050 5400
Wire Notes Line
	700  6700 4050 6700
Text Notes 3400 5400 0    50   ~ 0
Reset PushButton
Text Notes 1700 5400 0    50   ~ 0
Boot PushButton
$Comp
L Device:C C4
U 1 1 622232AB
P 5650 1350
F 0 "C4" V 5398 1350 50  0000 C CNN
F 1 "22uF" V 5489 1350 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 5688 1200 50  0001 C CNN
F 3 "~" H 5650 1350 50  0001 C CNN
	1    5650 1350
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6000 1750 5800 1750
Wire Wire Line
	5800 1750 5800 1350
Connection ~ 5800 1750
Wire Wire Line
	5500 1350 5500 1750
Wire Wire Line
	5300 1750 5500 1750
Connection ~ 5500 1750
Text GLabel 5450 2450 1    50   Input ~ 0
Vcc
$Comp
L Device:R R5
U 1 1 6222B3D3
P 5450 2800
F 0 "R5" H 5520 2846 50  0000 L CNN
F 1 "10k" H 5520 2755 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 5380 2800 50  0001 C CNN
F 3 "~" H 5450 2800 50  0001 C CNN
	1    5450 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	5450 2450 5450 2650
Wire Wire Line
	5450 2950 5450 3050
Wire Wire Line
	5450 3050 5750 3050
Text GLabel 5750 3050 2    50   Input ~ 0
EN
$Comp
L Device:C C3
U 1 1 62232319
P 5450 3200
F 0 "C3" V 5198 3200 50  0000 C CNN
F 1 "100nF" V 5289 3200 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 5488 3050 50  0001 C CNN
F 3 "~" H 5450 3200 50  0001 C CNN
	1    5450 3200
	1    0    0    -1  
$EndComp
Connection ~ 5450 3050
$Comp
L power:GND #PWR08
U 1 1 622332A0
P 5450 3400
F 0 "#PWR08" H 5450 3150 50  0001 C CNN
F 1 "GND" H 5455 3227 50  0000 C CNN
F 2 "" H 5450 3400 50  0001 C CNN
F 3 "" H 5450 3400 50  0001 C CNN
	1    5450 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	5450 3350 5450 3400
Text GLabel 2550 1250 2    50   Input ~ 0
5V
$Comp
L power:GND #PWR02
U 1 1 6224C1E7
P 1200 2950
F 0 "#PWR02" H 1200 2700 50  0001 C CNN
F 1 "GND" H 1205 2777 50  0000 C CNN
F 2 "" H 1200 2950 50  0001 C CNN
F 3 "" H 1200 2950 50  0001 C CNN
	1    1200 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	1200 2750 1200 2950
Wire Notes Line
	700  3200 700  850 
Wire Notes Line
	700  850  2800 850 
Wire Notes Line
	2800 850  2800 3200
Wire Notes Line
	2800 3200 700  3200
Text Notes 1800 850  0    50   ~ 0
USB-C Power connector\n
Wire Notes Line
	5000 5000 8500 5000
Wire Notes Line
	8500 5000 8500 1000
Wire Notes Line
	8500 1000 5000 1000
Wire Notes Line
	5000 1000 5000 5000
Text Notes 7850 950  0    50   ~ 0
ESP32 module
$Comp
L Connector:SD_Card J4
U 1 1 6225C423
P 5900 6100
F 0 "J4" H 5900 6765 50  0000 C CNN
F 1 "SD_Card" H 5900 6674 50  0000 C CNN
F 2 "Connector_Card:SD_Kyocera_145638109211859+" H 5900 6100 50  0001 C CNN
F 3 "http://portal.fciconnect.com/Comergent//fci/drawing/10067847.pdf" H 5900 6100 50  0001 C CNN
	1    5900 6100
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x05 J3
U 1 1 6226446B
P 3550 1650
F 0 "J3" V 3422 1930 50  0000 L CNN
F 1 "Conn_01x05" V 3513 1930 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x05_P2.54mm_Vertical" H 3550 1650 50  0001 C CNN
F 3 "~" H 3550 1650 50  0001 C CNN
	1    3550 1650
	0    1    1    0   
$EndComp
Text GLabel 3350 1450 1    50   Input ~ 0
PG
Text GLabel 3450 1450 1    50   Input ~ 0
SHDN
Text GLabel 3550 1450 1    50   Input ~ 0
VIN
Text GLabel 3750 1450 1    50   Input ~ 0
VOUT
Text GLabel 3500 2000 0    50   Input ~ 0
VOUT
Text GLabel 3650 2000 2    50   Input ~ 0
Vcc
Wire Wire Line
	3500 2000 3650 2000
Text GLabel 3500 1800 0    50   Input ~ 0
5V
Text GLabel 3650 1800 2    50   Input ~ 0
VIN
Wire Wire Line
	3500 1800 3650 1800
$Comp
L power:GND #PWR05
U 1 1 6226BD1F
P 3650 1100
F 0 "#PWR05" H 3650 850 50  0001 C CNN
F 1 "GND" H 3655 927 50  0000 C CNN
F 2 "" H 3650 1100 50  0001 C CNN
F 3 "" H 3650 1100 50  0001 C CNN
	1    3650 1100
	-1   0    0    1   
$EndComp
Wire Wire Line
	3650 1450 3650 1100
Text GLabel 3650 2450 2    50   Input ~ 0
IO34
Text GLabel 3350 2250 1    50   Input ~ 0
PG
$Comp
L Device:R R4
U 1 1 622709B8
P 3500 2450
F 0 "R4" V 3293 2450 50  0000 C CNN
F 1 "10k" V 3384 2450 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 3430 2450 50  0001 C CNN
F 3 "~" H 3500 2450 50  0001 C CNN
	1    3500 2450
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR04
U 1 1 6227155C
P 3350 2750
F 0 "#PWR04" H 3350 2500 50  0001 C CNN
F 1 "GND" H 3355 2577 50  0000 C CNN
F 2 "" H 3350 2750 50  0001 C CNN
F 3 "" H 3350 2750 50  0001 C CNN
	1    3350 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	3350 2250 3350 2450
Wire Notes Line
	2950 850  4450 850 
Wire Notes Line
	4450 850  4450 3100
Wire Notes Line
	4450 3100 2950 3100
Wire Notes Line
	2950 3100 2950 850 
Text Notes 3650 850  0    50   ~ 0
Switching Regulator
Text GLabel 5000 6100 0    50   Input ~ 0
Vcc
$Comp
L power:GND #PWR07
U 1 1 6227B808
P 4600 6300
F 0 "#PWR07" H 4600 6050 50  0001 C CNN
F 1 "GND" H 4605 6127 50  0000 C CNN
F 2 "" H 4600 6300 50  0001 C CNN
F 3 "" H 4600 6300 50  0001 C CNN
	1    4600 6300
	0    1    1    0   
$EndComp
Wire Wire Line
	5000 6300 4650 6300
Wire Wire Line
	5000 6000 4650 6000
Wire Wire Line
	4650 6000 4650 6300
Connection ~ 4650 6300
Wire Wire Line
	4650 6300 4600 6300
Text GLabel 5000 5900 0    50   Input ~ 0
SDMOSI
Text GLabel 5000 6400 0    50   Input ~ 0
SDMISO
Text GLabel 5000 6200 0    50   Input ~ 0
SDCLK
Text GLabel 6700 2700 0    50   Input ~ 0
SDCLK
Text GLabel 6700 2600 0    50   Input ~ 0
SDMOSI
Text GLabel 6700 2800 0    50   Input ~ 0
SDMISO
Wire Notes Line
	6900 6700 4200 6700
Wire Notes Line
	4200 6700 4200 5350
Wire Notes Line
	4200 5350 6900 5350
Wire Notes Line
	6900 5350 6900 6700
Text Notes 6300 5350 0    50   ~ 0
SD Card Reader\n
Wire Wire Line
	850  2200 750  2200
Wire Wire Line
	750  2200 750  1700
Wire Wire Line
	750  1700 850  1700
Wire Wire Line
	750  1700 750  1250
Connection ~ 750  1700
Wire Wire Line
	850  1600 800  1600
Wire Wire Line
	800  1600 800  2300
Wire Wire Line
	800  2300 850  2300
Wire Wire Line
	800  2300 800  2750
Wire Wire Line
	800  2750 1200 2750
Connection ~ 800  2300
$Comp
L Device:R R1
U 1 1 622C41CF
P 1300 1250
F 0 "R1" V 1093 1250 50  0000 C CNN
F 1 "20" V 1184 1250 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 1230 1250 50  0001 C CNN
F 3 "~" H 1300 1250 50  0001 C CNN
	1    1300 1250
	0    1    1    0   
$EndComp
Wire Wire Line
	750  1250 1150 1250
Wire Wire Line
	1450 1250 1950 1250
$Comp
L Mouser:SS8050-G Q1
U 1 1 622D23DC
P 1850 3750
F 0 "Q1" H 2388 3796 50  0000 L CNN
F 1 "SS8050-G" H 2388 3705 50  0000 L CNN
F 2 "Mouser:SOT95P240X115-3N" H 2400 3600 50  0001 L CNN
F 3 "https://datasheet.datasheetarchive.com/originals/distributors/DKDS-12/229454.pdf" H 2400 3500 50  0001 L CNN
F 4 "Bipolar Transistors - BJT NPN TRANSISTOR 1.5A 40V" H 2400 3400 50  0001 L CNN "Description"
F 5 "1.15" H 2400 3300 50  0001 L CNN "Height"
F 6 "750-SS8050-G" H 2400 3200 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.co.uk/ProductDetail/Comchip-Technology/SS8050-G?qs=LLUE9lz1YbcHg%252BWLMAtcrQ%3D%3D" H 2400 3100 50  0001 L CNN "Mouser Price/Stock"
F 8 "Comchip Technology" H 2400 3000 50  0001 L CNN "Manufacturer_Name"
F 9 "SS8050-G" H 2400 2900 50  0001 L CNN "Manufacturer_Part_Number"
	1    1850 3750
	1    0    0    -1  
$EndComp
$Comp
L Mouser:SS8050-G Q2
U 1 1 622D33B7
P 1850 4700
F 0 "Q2" H 2388 4654 50  0000 L CNN
F 1 "SS8050-G" H 2388 4745 50  0000 L CNN
F 2 "Mouser:SOT95P240X115-3N" H 2400 4550 50  0001 L CNN
F 3 "https://datasheet.datasheetarchive.com/originals/distributors/DKDS-12/229454.pdf" H 2400 4450 50  0001 L CNN
F 4 "Bipolar Transistors - BJT NPN TRANSISTOR 1.5A 40V" H 2400 4350 50  0001 L CNN "Description"
F 5 "1.15" H 2400 4250 50  0001 L CNN "Height"
F 6 "750-SS8050-G" H 2400 4150 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.co.uk/ProductDetail/Comchip-Technology/SS8050-G?qs=LLUE9lz1YbcHg%252BWLMAtcrQ%3D%3D" H 2400 4050 50  0001 L CNN "Mouser Price/Stock"
F 8 "Comchip Technology" H 2400 3950 50  0001 L CNN "Manufacturer_Name"
F 9 "SS8050-G" H 2400 3850 50  0001 L CNN "Manufacturer_Part_Number"
	1    1850 4700
	1    0    0    1   
$EndComp
Wire Wire Line
	2250 4100 2250 4050
Wire Wire Line
	1300 4100 2250 4100
Wire Wire Line
	2250 4350 2250 4400
Wire Wire Line
	1200 4350 2250 4350
Wire Notes Line
	2900 5100 700  5100
Wire Notes Line
	700  3350 2900 3350
Wire Notes Line
	700  3350 700  5100
Wire Notes Line
	2900 3350 2900 5100
$Comp
L Mouser:216990-0003 J1
U 1 1 622E8087
P 850 1600
F 0 "J1" H 1450 1865 50  0000 C CNN
F 1 "216990-0003" H 1450 1774 50  0000 C CNN
F 2 "Mouser:2169900003" H 1900 1700 50  0001 L CNN
F 3 "https://www.molex.com/pdm_docs/sd/2169900003_sd.pdf" H 1900 1600 50  0001 L CNN
F 4 "USB Connectors Mid-Mnt SMT CH0.58 16Ckt Type C Rec." H 1900 1500 50  0001 L CNN "Description"
F 5 "3.36" H 1900 1400 50  0001 L CNN "Height"
F 6 "538-216990-0003" H 1900 1300 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.co.uk/ProductDetail/Molex/216990-0003?qs=DRkmTr78QASn0GILUGAYCA%3D%3D" H 1900 1200 50  0001 L CNN "Mouser Price/Stock"
F 8 "Molex" H 1900 1100 50  0001 L CNN "Manufacturer_Name"
F 9 "216990-0003" H 1900 1000 50  0001 L CNN "Manufacturer_Part_Number"
	1    850  1600
	1    0    0    -1  
$EndComp
$Comp
L Mouser:BAT760-7 D1
U 1 1 622E9BBA
P 2650 1250
F 0 "D1" H 3050 983 50  0000 C CNN
F 1 "BAT760-7" H 3050 1074 50  0000 C CNN
F 2 "Mouser:SOD2513X120N" H 3150 1400 50  0001 L CNN
F 3 "https://www.diodes.com/assets/Datasheets/ds30498.pdf" H 3150 1300 50  0001 L CNN
F 4 "Diode Schottky 30V 1A 2Pin SOD323 Diodes Inc BAT760-7, SMT Schottky Diode, 30V 1A, 2-Pin SOD-323" H 3150 1200 50  0001 L CNN "Description"
F 5 "1.2" H 3150 1100 50  0001 L CNN "Height"
F 6 "621-BAT760-7" H 3150 1000 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.co.uk/ProductDetail/Diodes-Incorporated/BAT760-7?qs=JV7lzlMm3yKDDyO09xoRbQ%3D%3D" H 3150 900 50  0001 L CNN "Mouser Price/Stock"
F 8 "Diodes Inc." H 3150 800 50  0001 L CNN "Manufacturer_Name"
F 9 "BAT760-7" H 3150 700 50  0001 L CNN "Manufacturer_Part_Number"
	1    2650 1250
	-1   0    0    1   
$EndComp
$Comp
L Device:LED D2
U 1 1 621F003D
P 5500 4450
F 0 "D2" V 5539 4332 50  0000 R CNN
F 1 "LED" V 5448 4332 50  0000 R CNN
F 2 "Mouser:APHCM2012QBCDF01" H 5500 4450 50  0001 C CNN
F 3 "~" H 5500 4450 50  0001 C CNN
	1    5500 4450
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR014
U 1 1 621F0C2D
P 5500 4600
F 0 "#PWR014" H 5500 4350 50  0001 C CNN
F 1 "GND" H 5505 4427 50  0000 C CNN
F 2 "" H 5500 4600 50  0001 C CNN
F 3 "" H 5500 4600 50  0001 C CNN
	1    5500 4600
	1    0    0    -1  
$EndComp
$Comp
L Device:R R6
U 1 1 621F10C3
P 5500 4150
F 0 "R6" H 5570 4196 50  0000 L CNN
F 1 "0" H 5570 4105 50  0000 L CNN
F 2 "Resistor_SMD:R_0201_0603Metric" V 5430 4150 50  0001 C CNN
F 3 "~" H 5500 4150 50  0001 C CNN
	1    5500 4150
	1    0    0    -1  
$EndComp
Text GLabel 5500 4000 1    50   Input ~ 0
Vcc
$Comp
L Device:R R7
U 1 1 621F3C14
P 3350 2600
F 0 "R7" V 3143 2600 50  0000 C CNN
F 1 "0" V 3234 2600 50  0000 C CNN
F 2 "Resistor_SMD:R_0201_0603Metric" V 3280 2600 50  0001 C CNN
F 3 "~" H 3350 2600 50  0001 C CNN
	1    3350 2600
	-1   0    0    1   
$EndComp
Connection ~ 3350 2450
$Comp
L power:GND #PWR?
U 1 1 622062DD
P 6550 1550
F 0 "#PWR?" H 6550 1300 50  0001 C CNN
F 1 "GND" H 6555 1377 50  0000 C CNN
F 2 "" H 6550 1550 50  0001 C CNN
F 3 "" H 6550 1550 50  0001 C CNN
	1    6550 1550
	-1   0    0    1   
$EndComp
Wire Wire Line
	6550 1550 6550 1700
Wire Wire Line
	6550 1700 6700 1700
Text GLabel 6700 1800 0    50   Input ~ 0
Vcc
Wire Wire Line
	6400 3100 6400 3950
Wire Wire Line
	8100 3500 8100 3900
Connection ~ 8100 3500
Wire Notes Line
	5000 3700 6050 3700
Wire Notes Line
	6050 2100 6050 5000
Wire Notes Line
	6300 2100 6300 1000
Wire Notes Line
	5000 2100 6300 2100
Text Notes 5450 1100 0    50   ~ 0
MCU Power capacitor\n
Text Notes 5400 2200 0    50   ~ 0
Reset stabilizing
Text Notes 5600 3800 0    50   ~ 0
Power LED
$EndSCHEMATC
