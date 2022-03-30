EESchema Schematic File Version 5
EELAYER 36 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
Comment5 ""
Comment6 ""
Comment7 ""
Comment8 ""
Comment9 ""
$EndDescr
Connection ~ 2200 1850
Connection ~ 2350 1750
Connection ~ 2800 6650
Connection ~ 3900 5000
Connection ~ 3900 5700
Connection ~ 4450 2650
Connection ~ 4600 5000
Connection ~ 4600 5800
Connection ~ 4850 4800
Connection ~ 4850 5000
Connection ~ 5300 5000
Connection ~ 5300 6000
Connection ~ 5950 6100
Wire Wire Line
	750  2750 750  6000
Wire Wire Line
	750  2750 2350 2750
Wire Wire Line
	750  6000 2400 6000
Wire Wire Line
	950  2650 950  5900
Wire Wire Line
	950  2650 2350 2650
Wire Wire Line
	950  5900 2400 5900
Wire Wire Line
	1200 2550 1200 5800
Wire Wire Line
	1200 2550 2350 2550
Wire Wire Line
	1200 5800 2400 5800
Wire Wire Line
	1350 2450 1350 5600
Wire Wire Line
	1350 2450 2350 2450
Wire Wire Line
	1350 5600 2400 5600
Wire Wire Line
	1500 1450 2350 1450
Wire Wire Line
	1500 1600 1500 1450
Wire Wire Line
	1500 1900 1500 1950
Wire Wire Line
	1500 1950 2200 1950
Wire Wire Line
	1650 2350 1650 5500
Wire Wire Line
	1650 2350 2350 2350
Wire Wire Line
	1650 5500 2400 5500
Wire Wire Line
	1950 1850 1950 1800
Wire Wire Line
	1950 2250 1950 5400
Wire Wire Line
	1950 2250 2350 2250
Wire Wire Line
	2200 1850 1950 1850
Wire Wire Line
	2200 1950 2200 1850
Wire Wire Line
	2350 1450 2350 1750
Wire Wire Line
	2350 1850 2200 1850
Wire Wire Line
	2400 5400 1950 5400
Wire Wire Line
	2600 5200 2600 5100
Wire Wire Line
	2700 6600 2700 6650
Wire Wire Line
	2700 6650 2800 6650
Wire Wire Line
	2800 6650 2800 6600
Wire Wire Line
	2800 6650 3000 6650
Wire Wire Line
	3000 5200 2600 5200
Wire Wire Line
	3000 6650 3000 6600
Wire Wire Line
	3200 5000 3200 5200
Wire Wire Line
	3200 5200 3100 5200
Wire Wire Line
	3600 5700 3900 5700
Wire Wire Line
	3600 5800 4600 5800
Wire Wire Line
	3750 3550 3900 3550
Wire Wire Line
	3900 5000 3200 5000
Wire Wire Line
	3900 5150 3900 5000
Wire Wire Line
	3900 5550 3900 5700
Wire Wire Line
	3900 5700 3900 6400
Wire Wire Line
	4300 2650 4450 2650
Wire Wire Line
	4450 2450 4450 2650
Wire Wire Line
	4450 2650 4850 2650
Wire Wire Line
	4600 5000 3900 5000
Wire Wire Line
	4600 5000 4850 5000
Wire Wire Line
	4600 5150 4600 5000
Wire Wire Line
	4600 5800 4600 5550
Wire Wire Line
	4600 5800 4600 6400
Wire Wire Line
	4600 5800 6200 5800
Wire Wire Line
	4700 2550 4850 2550
Wire Wire Line
	4800 2150 3750 2150
Wire Wire Line
	4800 2250 3750 2250
Wire Wire Line
	4850 2050 3750 2050
Wire Wire Line
	4850 2350 3750 2350
Wire Wire Line
	4850 2450 4450 2450
Wire Wire Line
	4850 4600 4850 4800
Wire Wire Line
	4850 4800 4850 5000
Wire Wire Line
	4850 5000 5300 5000
Wire Wire Line
	4900 1950 3750 1950
Wire Wire Line
	5050 4800 4850 4800
Wire Wire Line
	5300 5000 5300 5150
Wire Wire Line
	5300 5550 5300 6000
Wire Wire Line
	5300 6000 3600 6000
Wire Wire Line
	5300 6000 5300 6400
Wire Wire Line
	5300 6000 6200 6000
Wire Wire Line
	5950 5000 5300 5000
Wire Wire Line
	5950 5150 5950 5000
Wire Wire Line
	5950 5550 5950 6100
Wire Wire Line
	5950 6100 3600 6100
Wire Wire Line
	5950 6100 5950 6400
Wire Wire Line
	5950 6100 6200 6100
Wire Wire Line
	6200 5700 3900 5700
Text GLabel 4800 2150 2    50   Input ~ 0
MOSI
Text GLabel 4800 2250 2    50   Input ~ 0
MISO
Text GLabel 4850 2050 2    50   Input ~ 0
SCK
Text GLabel 4850 2350 2    50   Input ~ 0
IRQ
Text GLabel 4850 2450 2    50   Input ~ 0
RST
Text GLabel 4850 2550 2    50   Input ~ 0
GND
Text GLabel 4850 2650 2    50   Input ~ 0
VCC
Text GLabel 4900 1950 2    50   Input ~ 0
SS
Text GLabel 6200 5700 2    50   Input ~ 0
OUT1
Text GLabel 6200 5800 2    50   Input ~ 0
OUT2
Text GLabel 6200 6000 2    50   Input ~ 0
OUT3
Text GLabel 6200 6100 2    50   Input ~ 0
OUT4
$Comp
L power:+3.3V #PWR?
U 1 1 620D9825
P 1950 1800
F 0 "#PWR?" H 1950 1650 50  0001 C CNN
F 1 "+3.3V" H 1965 1973 50  0000 C CNN
F 2 "" H 1950 1800 50  0001 C CNN
F 3 "" H 1950 1800 50  0001 C CNN
	1    1950 1800
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 62121966
P 2600 5100
F 0 "#PWR?" H 2600 4950 50  0001 C CNN
F 1 "+3.3V" H 2615 5273 50  0000 C CNN
F 2 "" H 2600 5100 50  0001 C CNN
F 3 "" H 2600 5100 50  0001 C CNN
	1    2600 5100
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 6215A41A
P 4300 2650
F 0 "#PWR?" H 4300 2500 50  0001 C CNN
F 1 "+3.3V" H 4315 2823 50  0000 C CNN
F 2 "" H 4300 2650 50  0001 C CNN
F 3 "" H 4300 2650 50  0001 C CNN
	1    4300 2650
	0    -1   -1   0   
$EndComp
$Comp
L power:+9V #PWR?
U 1 1 6211F96A
P 4850 4600
F 0 "#PWR?" H 4850 4450 50  0001 C CNN
F 1 "+9V" H 4865 4773 50  0000 C CNN
F 2 "" H 4850 4600 50  0001 C CNN
F 3 "" H 4850 4600 50  0001 C CNN
	1    4850 4600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 620E005A
P 2350 1750
F 0 "#PWR?" H 2350 1500 50  0001 C CNN
F 1 "GND" H 2355 1577 50  0000 C CNN
F 2 "" H 2350 1750 50  0001 C CNN
F 3 "" H 2350 1750 50  0001 C CNN
	1    2350 1750
	0    1    -1   0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 620EA7CF
P 2350 3150
F 0 "#PWR?" H 2350 2900 50  0001 C CNN
F 1 "GND" V 2355 3022 50  0000 R CNN
F 2 "" H 2350 3150 50  0001 C CNN
F 3 "" H 2350 3150 50  0001 C CNN
	1    2350 3150
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 6211F091
P 2800 6650
F 0 "#PWR?" H 2800 6400 50  0001 C CNN
F 1 "GND" H 2805 6477 50  0000 C CNN
F 2 "" H 2800 6650 50  0001 C CNN
F 3 "" H 2800 6650 50  0001 C CNN
	1    2800 6650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 620EC314
P 3750 3450
F 0 "#PWR?" H 3750 3200 50  0001 C CNN
F 1 "GND" V 3755 3322 50  0000 R CNN
F 2 "" H 3750 3450 50  0001 C CNN
F 3 "" H 3750 3450 50  0001 C CNN
	1    3750 3450
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 620EE29C
P 3900 3550
F 0 "#PWR?" H 3900 3300 50  0001 C CNN
F 1 "GND" V 3905 3422 50  0000 R CNN
F 2 "" H 3900 3550 50  0001 C CNN
F 3 "" H 3900 3550 50  0001 C CNN
	1    3900 3550
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 6210BCDA
P 3900 6800
F 0 "#PWR?" H 3900 6550 50  0001 C CNN
F 1 "GND" H 3905 6627 50  0000 C CNN
F 2 "" H 3900 6800 50  0001 C CNN
F 3 "" H 3900 6800 50  0001 C CNN
	1    3900 6800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 6210CC87
P 4600 6800
F 0 "#PWR?" H 4600 6550 50  0001 C CNN
F 1 "GND" H 4605 6627 50  0000 C CNN
F 2 "" H 4600 6800 50  0001 C CNN
F 3 "" H 4600 6800 50  0001 C CNN
	1    4600 6800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 6215B10B
P 4700 2550
F 0 "#PWR?" H 4700 2300 50  0001 C CNN
F 1 "GND" H 4705 2377 50  0000 C CNN
F 2 "" H 4700 2550 50  0001 C CNN
F 3 "" H 4700 2550 50  0001 C CNN
	1    4700 2550
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 6210D6D8
P 5300 6800
F 0 "#PWR?" H 5300 6550 50  0001 C CNN
F 1 "GND" H 5305 6627 50  0000 C CNN
F 2 "" H 5300 6800 50  0001 C CNN
F 3 "" H 5300 6800 50  0001 C CNN
	1    5300 6800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 620F3602
P 5350 4800
F 0 "#PWR?" H 5350 4550 50  0001 C CNN
F 1 "GND" H 5355 4627 50  0000 C CNN
F 2 "" H 5350 4800 50  0001 C CNN
F 3 "" H 5350 4800 50  0001 C CNN
	1    5350 4800
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 6210E006
P 5950 6800
F 0 "#PWR?" H 5950 6550 50  0001 C CNN
F 1 "GND" H 5955 6627 50  0000 C CNN
F 2 "" H 5950 6800 50  0001 C CNN
F 3 "" H 5950 6800 50  0001 C CNN
	1    5950 6800
	1    0    0    -1  
$EndComp
$Comp
L Device:C 100nF
U 1 1 620E6461
P 1500 1750
F 0 "100nF" H 1615 1796 50  0000 L CNN
F 1 "C" H 1615 1705 50  0000 L CNN
F 2 "" H 1538 1600 50  0001 C CNN
F 3 "~" H 1500 1750 50  0001 C CNN
	1    1500 1750
	1    0    0    -1  
$EndComp
$Comp
L Device:C 100nF
U 1 1 6212EC34
P 5200 4800
F 0 "100nF" V 4948 4800 50  0000 C CNN
F 1 "C" V 5039 4800 50  0000 C CNN
F 2 "" H 5238 4650 50  0001 C CNN
F 3 "~" H 5200 4800 50  0001 C CNN
	1    5200 4800
	0    1    1    0   
$EndComp
$Comp
L pspice:DIODE D?
U 1 1 620F9F8E
P 3900 5350
F 0 "D?" V 3946 5222 50  0000 R CNN
F 1 "DIODE" V 3855 5222 50  0000 R CNN
F 2 "" H 3900 5350 50  0001 C CNN
F 3 "~" H 3900 5350 50  0001 C CNN
	1    3900 5350
	0    -1   -1   0   
$EndComp
$Comp
L pspice:DIODE D?
U 1 1 62107A01
P 3900 6600
F 0 "D?" V 3946 6472 50  0000 R CNN
F 1 "DIODE" V 3855 6472 50  0000 R CNN
F 2 "" H 3900 6600 50  0001 C CNN
F 3 "~" H 3900 6600 50  0001 C CNN
	1    3900 6600
	0    -1   -1   0   
$EndComp
$Comp
L pspice:DIODE D?
U 1 1 620FC985
P 4600 5350
F 0 "D?" V 4646 5222 50  0000 R CNN
F 1 "DIODE" V 4555 5222 50  0000 R CNN
F 2 "" H 4600 5350 50  0001 C CNN
F 3 "~" H 4600 5350 50  0001 C CNN
	1    4600 5350
	0    -1   -1   0   
$EndComp
$Comp
L pspice:DIODE D?
U 1 1 62107A09
P 4600 6600
F 0 "D?" V 4646 6472 50  0000 R CNN
F 1 "DIODE" V 4555 6472 50  0000 R CNN
F 2 "" H 4600 6600 50  0001 C CNN
F 3 "~" H 4600 6600 50  0001 C CNN
	1    4600 6600
	0    -1   -1   0   
$EndComp
$Comp
L pspice:DIODE D?
U 1 1 620FE2B2
P 5300 5350
F 0 "D?" V 5346 5222 50  0000 R CNN
F 1 "DIODE" V 5255 5222 50  0000 R CNN
F 2 "" H 5300 5350 50  0001 C CNN
F 3 "~" H 5300 5350 50  0001 C CNN
	1    5300 5350
	0    -1   -1   0   
$EndComp
$Comp
L pspice:DIODE D?
U 1 1 62107A11
P 5300 6600
F 0 "D?" V 5346 6472 50  0000 R CNN
F 1 "DIODE" V 5255 6472 50  0000 R CNN
F 2 "" H 5300 6600 50  0001 C CNN
F 3 "~" H 5300 6600 50  0001 C CNN
	1    5300 6600
	0    -1   -1   0   
$EndComp
$Comp
L pspice:DIODE D?
U 1 1 620FFA45
P 5950 5350
F 0 "D?" V 5996 5222 50  0000 R CNN
F 1 "DIODE" V 5905 5222 50  0000 R CNN
F 2 "" H 5950 5350 50  0001 C CNN
F 3 "~" H 5950 5350 50  0001 C CNN
	1    5950 5350
	0    -1   -1   0   
$EndComp
$Comp
L pspice:DIODE D?
U 1 1 62107A18
P 5950 6600
F 0 "D?" V 5996 6472 50  0000 R CNN
F 1 "DIODE" V 5905 6472 50  0000 R CNN
F 2 "" H 5950 6600 50  0001 C CNN
F 3 "~" H 5950 6600 50  0001 C CNN
	1    5950 6600
	0    -1   -1   0   
$EndComp
$Comp
L Regulator_Linear:LM317_TO-220 U?
U 1 1 00000000
P 7350 3000
F 0 "U?" H 7350 3300 50  0000 C CNN
F 1 "LM317_TO-220" H 7350 3200 50  0000 C CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 7350 3250 50  0001 C CIN
F 3 "http://www.ti.com/lit/ds/symlink/lm317.pdf" H 7350 3000 50  0001 C CNN
	1    7350 3000
	1    0    0    -1  
$EndComp
$Comp
L Driver_Motor:L298HN U?
U 1 1 620EFA9C
P 3000 5900
F 0 "U?" H 3000 6781 50  0000 C CNN
F 1 "L298HN" H 3000 6690 50  0000 C CNN
F 2 "Package_TO_SOT_THT:TO-220-15_P2.54x2.54mm_StaggerOdd_Lead4.58mm_Vertical" H 3050 5250 50  0001 L CNN
F 3 "http://www.st.com/st-web-ui/static/active/en/resource/technical/document/datasheet/CD00000240.pdf" H 3150 6150 50  0001 C CNN
	1    3000 5900
	1    0    0    -1  
$EndComp
$Comp
L SamacSys_Parts:ESP32-SOLO-1 IC?
U 1 1 620D3002
P 2350 1750
F 0 "IC?" H 3050 2015 50  0000 C CNN
F 1 "ESP32-SOLO-1" H 3050 1924 50  0000 C CNN
F 2 "ESP32SOLO1" H 3600 1850 50  0001 L CNN
F 3 "https://www.espressif.com/sites/default/files/documentation/esp32-solo-1_datasheet_en.pdf" H 3600 1750 50  0001 L CNN
F 4 "WiFi Modules (802.11) SMD Module, ESP32-S0WD, 32Mbits SPI flash, UART mode," H 3600 1650 50  0001 L CNN "Description"
F 5 "" H 3600 1550 50  0001 L CNN "Height"
F 6 "Espressif Systems" H 3600 1450 50  0001 L CNN "Manufacturer_Name"
F 7 "ESP32-SOLO-1" H 3600 1350 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "356-ESP32-SOLO-1" H 3600 1250 50  0001 L CNN "Mouser Part Number"
F 9 "https://www.mouser.co.uk/ProductDetail/Espressif-Systems/ESP32-SOLO-1?qs=w%2Fv1CP2dgqpIFRWX9FvikA%3D%3D" H 3600 1150 50  0001 L CNN "Mouser Price/Stock"
F 10 "" H 3600 1050 50  0001 L CNN "Arrow Part Number"
F 11 "" H 3600 950 50  0001 L CNN "Arrow Price/Stock"
	1    2350 1750
	1    0    0    -1  
$EndComp
$EndSCHEMATC