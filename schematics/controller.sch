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
L power:GND #PWR09
U 1 1 62097EC1
P 5950 1350
F 0 "#PWR09" H 5950 1100 50  0001 C CNN
F 1 "GND" H 5955 1177 50  0000 C CNN
F 2 "" H 5950 1350 50  0001 C CNN
F 3 "" H 5950 1350 50  0001 C CNN
	1    5950 1350
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR010
U 1 1 620AA4E8
P 8100 4000
F 0 "#PWR010" H 8100 3750 50  0001 C CNN
F 1 "GND" H 8105 3827 50  0000 C CNN
F 2 "" H 8100 4000 50  0001 C CNN
F 3 "" H 8100 4000 50  0001 C CNN
	1    8100 4000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR08
U 1 1 620AB4E7
P 6550 4000
F 0 "#PWR08" H 6550 3750 50  0001 C CNN
F 1 "GND" H 6555 3827 50  0000 C CNN
F 2 "" H 6550 4000 50  0001 C CNN
F 3 "" H 6550 4000 50  0001 C CNN
	1    6550 4000
	1    0    0    -1  
$EndComp
Text GLabel 8100 2800 2    50   Input ~ 0
TX
Text GLabel 8100 2700 2    50   Input ~ 0
RX
$Comp
L Connector_Generic:Conn_01x06 J3
U 1 1 621305FA
P 3900 4350
F 0 "J3" V 3772 4630 50  0000 L CNN
F 1 "Conn_01x06" V 3863 4630 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x06_P2.54mm_Vertical" H 3900 4350 50  0001 C CNN
F 3 "~" H 3900 4350 50  0001 C CNN
	1    3900 4350
	0    1    1    0   
$EndComp
Text GLabel 3800 4150 1    50   Input ~ 0
TX
Text GLabel 3700 4150 1    50   Input ~ 0
RX
Text GLabel 4000 4150 1    50   Input ~ 0
CTS
Text GLabel 3600 4150 1    50   Input ~ 0
DTR
Text GLabel 3900 4150 1    50   Input ~ 0
Vcc
$Comp
L power:GND #PWR06
U 1 1 62130F50
P 4100 4100
F 0 "#PWR06" H 4100 3850 50  0001 C CNN
F 1 "GND" H 4105 3927 50  0000 C CNN
F 2 "" H 4100 4100 50  0001 C CNN
F 3 "" H 4100 4100 50  0001 C CNN
	1    4100 4100
	-1   0    0    1   
$EndComp
Wire Notes Line
	4850 3700 4850 4700
Wire Notes Line
	4850 4700 3300 4700
Wire Notes Line
	3300 4700 3300 3700
Wire Notes Line
	3300 3700 4850 3700
Text Notes 4200 3700 0    50   ~ 0
UART connectors\n
Wire Wire Line
	4100 4150 4100 4100
Text GLabel 5250 1350 0    50   Input ~ 0
Vcc
$Comp
L Device:C C5
U 1 1 621D55FD
P 5600 1350
F 0 "C5" V 5348 1350 50  0000 C CNN
F 1 "100nF" V 5439 1350 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 5638 1200 50  0001 C CNN
F 3 "~" H 5600 1350 50  0001 C CNN
	1    5600 1350
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R1
U 1 1 621D8EBD
P 1800 4100
F 0 "R1" V 2007 4100 50  0000 C CNN
F 1 "10k" V 1916 4100 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 1730 4100 50  0001 C CNN
F 3 "~" H 1800 4100 50  0001 C CNN
	1    1800 4100
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R2
U 1 1 621DD475
P 1800 5050
F 0 "R2" V 2007 5050 50  0000 C CNN
F 1 "10k" V 1916 5050 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 1730 5050 50  0001 C CNN
F 3 "~" H 1800 5050 50  0001 C CNN
	1    1800 5050
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1950 5050 2150 5050
Wire Wire Line
	1950 4100 2150 4100
Wire Wire Line
	1500 4700 1500 4100
Wire Wire Line
	1500 4100 1650 4100
Wire Wire Line
	1600 4450 1600 5050
Wire Wire Line
	1600 5050 1650 5050
Connection ~ 1600 5050
Wire Wire Line
	1500 4100 1300 4100
Connection ~ 1500 4100
Wire Wire Line
	1300 5050 1600 5050
Text GLabel 2550 3800 2    50   Input ~ 0
EN
Text GLabel 2550 5350 2    50   Input ~ 0
GPIO0
Text GLabel 1300 4100 0    50   Input ~ 0
DTR
Text GLabel 1300 5050 0    50   Input ~ 0
CTS
Text Notes 2550 3700 0    50   ~ 0
Program circuitry\n
Text GLabel 6700 1600 0    50   Input ~ 0
EN
$Comp
L Switch:SW_Push SW1
U 1 1 6220C472
P 1850 6000
F 0 "SW1" H 1850 6285 50  0000 C CNN
F 1 "SW_Push" H 1850 6194 50  0000 C CNN
F 2 "Button_Switch_SMD:SW_SPST_CK_KXT3" H 1850 6200 50  0001 C CNN
F 3 "~" H 1850 6200 50  0001 C CNN
	1    1850 6000
	1    0    0    -1  
$EndComp
$Comp
L Device:C C1
U 1 1 6220CBE7
P 1850 6350
F 0 "C1" V 1598 6350 50  0000 C CNN
F 1 "0.1uF" V 1689 6350 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 1888 6200 50  0001 C CNN
F 3 "~" H 1850 6350 50  0001 C CNN
	1    1850 6350
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR01
U 1 1 6220D2BC
P 1450 6500
F 0 "#PWR01" H 1450 6250 50  0001 C CNN
F 1 "GND" H 1455 6327 50  0000 C CNN
F 2 "" H 1450 6500 50  0001 C CNN
F 3 "" H 1450 6500 50  0001 C CNN
	1    1450 6500
	1    0    0    -1  
$EndComp
Wire Wire Line
	1700 6350 1450 6350
Wire Wire Line
	1450 6350 1450 6500
Wire Wire Line
	1650 6000 1450 6000
Wire Wire Line
	1450 6000 1450 6350
Connection ~ 1450 6350
Wire Wire Line
	2000 6350 2250 6350
Wire Wire Line
	2250 6350 2250 6000
Wire Wire Line
	2250 6000 2050 6000
Wire Wire Line
	2250 6000 2550 6000
Connection ~ 2250 6000
Text GLabel 2550 6000 2    50   Input ~ 0
GPIO0
$Comp
L Switch:SW_Push SW2
U 1 1 62214B1E
P 3650 6000
F 0 "SW2" H 3650 6285 50  0000 C CNN
F 1 "SW_Push" H 3650 6194 50  0000 C CNN
F 2 "Button_Switch_SMD:SW_SPST_CK_KXT3" H 3650 6200 50  0001 C CNN
F 3 "~" H 3650 6200 50  0001 C CNN
	1    3650 6000
	1    0    0    -1  
$EndComp
$Comp
L Device:C C2
U 1 1 6221566F
P 3650 6350
F 0 "C2" V 3398 6350 50  0000 C CNN
F 1 "0.1uF" V 3489 6350 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 3688 6200 50  0001 C CNN
F 3 "~" H 3650 6350 50  0001 C CNN
	1    3650 6350
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR03
U 1 1 62215DC5
P 3150 6450
F 0 "#PWR03" H 3150 6200 50  0001 C CNN
F 1 "GND" H 3155 6277 50  0000 C CNN
F 2 "" H 3150 6450 50  0001 C CNN
F 3 "" H 3150 6450 50  0001 C CNN
	1    3150 6450
	1    0    0    -1  
$EndComp
Wire Wire Line
	3500 6350 3150 6350
Wire Wire Line
	3150 6350 3150 6450
Wire Wire Line
	3450 6000 3150 6000
Wire Wire Line
	3150 6000 3150 6350
Connection ~ 3150 6350
Wire Wire Line
	3800 6350 4100 6350
Wire Wire Line
	4100 6350 4100 6000
Wire Wire Line
	4100 6000 3850 6000
Wire Wire Line
	4100 6000 4400 6000
Connection ~ 4100 6000
Text GLabel 4400 6000 2    50   Input ~ 0
EN
Wire Notes Line
	1300 6900 1300 5600
Wire Notes Line
	2950 5600 2950 6900
Wire Notes Line
	4650 5600 4650 6900
Wire Notes Line
	1300 5600 4650 5600
Wire Notes Line
	1300 6900 4650 6900
Text Notes 3950 5600 0    50   ~ 0
Reset PushButton
Text Notes 2300 5600 0    50   ~ 0
Boot PushButton
$Comp
L Device:C C4
U 1 1 622232AB
P 5600 950
F 0 "C4" V 5348 950 50  0000 C CNN
F 1 "22uF" V 5439 950 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 5638 800 50  0001 C CNN
F 3 "~" H 5600 950 50  0001 C CNN
	1    5600 950 
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5950 1350 5750 1350
Wire Wire Line
	5750 1350 5750 950 
Connection ~ 5750 1350
Wire Wire Line
	5450 950  5450 1350
Wire Wire Line
	5250 1350 5450 1350
Connection ~ 5450 1350
Text GLabel 5450 2100 1    50   Input ~ 0
Vcc
$Comp
L Device:R R3
U 1 1 6222B3D3
P 5450 2450
F 0 "R3" H 5520 2496 50  0000 L CNN
F 1 "10k" H 5520 2405 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 5380 2450 50  0001 C CNN
F 3 "~" H 5450 2450 50  0001 C CNN
	1    5450 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	5450 2100 5450 2300
Wire Wire Line
	5450 2600 5450 2700
Wire Wire Line
	5450 2700 5750 2700
Text GLabel 5750 2700 2    50   Input ~ 0
EN
$Comp
L Device:C C3
U 1 1 62232319
P 5450 2850
F 0 "C3" V 5198 2850 50  0000 C CNN
F 1 "100nF" V 5289 2850 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 5488 2700 50  0001 C CNN
F 3 "~" H 5450 2850 50  0001 C CNN
	1    5450 2850
	1    0    0    -1  
$EndComp
Connection ~ 5450 2700
$Comp
L power:GND #PWR07
U 1 1 622332A0
P 5450 3050
F 0 "#PWR07" H 5450 2800 50  0001 C CNN
F 1 "GND" H 5455 2877 50  0000 C CNN
F 2 "" H 5450 3050 50  0001 C CNN
F 3 "" H 5450 3050 50  0001 C CNN
	1    5450 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	5450 3000 5450 3050
Wire Notes Line
	5000 4700 8500 4700
Wire Notes Line
	8500 4700 8500 700 
Wire Notes Line
	8500 700  5000 700 
Wire Notes Line
	5000 700  5000 4700
Text Notes 7900 700  0    50   ~ 0
ESP32 module
Wire Wire Line
	2550 4450 2550 4400
Wire Wire Line
	1600 4450 2550 4450
Wire Wire Line
	2550 4700 2550 4750
Wire Wire Line
	1500 4700 2550 4700
Wire Notes Line
	3200 5450 1000 5450
Wire Notes Line
	1000 3700 3200 3700
Wire Notes Line
	1000 3700 1000 5450
Wire Notes Line
	3200 3700 3200 5450
$Comp
L ESP-SOLO-1:ESP32-SOLO-1 IC2
U 1 1 621E7CD6
P 6700 1400
F 0 "IC2" H 7400 1665 50  0000 C CNN
F 1 "ESP32-SOLO-1" H 7400 1574 50  0000 C CNN
F 2 "Mouser:ESP32SOLO1" H 7950 1500 50  0001 L CNN
F 3 "https://www.espressif.com/sites/default/files/documentation/esp32-solo-1_datasheet_en.pdf" H 7950 1400 50  0001 L CNN
F 4 "WiFi Modules (802.11) SMD Module, ESP32-S0WD, 32Mbits SPI flash, UART mode," H 7950 1300 50  0001 L CNN "Description"
F 5 "" H 7950 1200 50  0001 L CNN "Height"
F 6 "Espressif Systems" H 7950 1100 50  0001 L CNN "Manufacturer_Name"
F 7 "ESP32-SOLO-1" H 7950 1000 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "356-ESP32-SOLO-1" H 7950 900 50  0001 L CNN "Mouser Part Number"
F 9 "https://www.mouser.co.uk/ProductDetail/Espressif-Systems/ESP32-SOLO-1?qs=w%2Fv1CP2dgqpIFRWX9FvikA%3D%3D" H 7950 800 50  0001 L CNN "Mouser Price/Stock"
F 10 "" H 7950 700 50  0001 L CNN "Arrow Part Number"
F 11 "" H 7950 600 50  0001 L CNN "Arrow Price/Stock"
	1    6700 1400
	1    0    0    -1  
$EndComp
Wire Wire Line
	8100 3200 8100 4000
$Comp
L Switch:SW_Push_Dual SW3
U 1 1 621F5F8F
P 9450 1200
F 0 "SW3" H 9450 1485 50  0000 C CNN
F 1 "SW_Push_Dual" H 9450 1394 50  0000 C CNN
F 2 "Button_Switch_THT:SW_TH_Tactile_Omron_B3F-10xx" H 9450 1400 50  0001 C CNN
F 3 "~" H 9450 1400 50  0001 C CNN
	1    9450 1200
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push_Dual SW4
U 1 1 621F6E64
P 9450 2050
F 0 "SW4" H 9450 2335 50  0000 C CNN
F 1 "SW_Push_Dual" H 9450 2244 50  0000 C CNN
F 2 "Button_Switch_THT:SW_TH_Tactile_Omron_B3F-10xx" H 9450 2250 50  0001 C CNN
F 3 "~" H 9450 2250 50  0001 C CNN
	1    9450 2050
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push_Dual SW5
U 1 1 621F750F
P 9450 2950
F 0 "SW5" H 9450 3235 50  0000 C CNN
F 1 "SW_Push_Dual" H 9450 3144 50  0000 C CNN
F 2 "Button_Switch_THT:SW_TH_Tactile_Omron_B3F-10xx" H 9450 3150 50  0001 C CNN
F 3 "~" H 9450 3150 50  0001 C CNN
	1    9450 2950
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push_Dual SW6
U 1 1 621F81C8
P 9450 3850
F 0 "SW6" H 9450 4135 50  0000 C CNN
F 1 "SW_Push_Dual" H 9450 4044 50  0000 C CNN
F 2 "Button_Switch_THT:SW_TH_Tactile_Omron_B3F-10xx" H 9450 4050 50  0001 C CNN
F 3 "~" H 9450 4050 50  0001 C CNN
	1    9450 3850
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push_Dual SW7
U 1 1 621F8B59
P 9450 4850
F 0 "SW7" H 9450 5135 50  0000 C CNN
F 1 "SW_Push_Dual" H 9450 5044 50  0000 C CNN
F 2 "Button_Switch_THT:SW_TH_Tactile_Omron_B3F-10xx" H 9450 5050 50  0001 C CNN
F 3 "~" H 9450 5050 50  0001 C CNN
	1    9450 4850
	1    0    0    -1  
$EndComp
Text GLabel 10250 950  1    50   Input ~ 0
Vcc
Wire Wire Line
	10250 950  10250 1200
Wire Wire Line
	10250 4850 9650 4850
Wire Wire Line
	9650 3850 10250 3850
Connection ~ 10250 3850
Wire Wire Line
	10250 3850 10250 4850
Wire Wire Line
	9650 2950 10250 2950
Connection ~ 10250 2950
Wire Wire Line
	10250 2950 10250 3850
Wire Wire Line
	9650 2050 10250 2050
Connection ~ 10250 2050
Wire Wire Line
	10250 2050 10250 2950
Wire Wire Line
	9650 1200 10250 1200
Connection ~ 10250 1200
Wire Wire Line
	10250 1200 10250 2050
$Comp
L Device:R R4
U 1 1 621FE266
P 9000 1550
F 0 "R4" H 9070 1596 50  0000 L CNN
F 1 "10k" H 9070 1505 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 8930 1550 50  0001 C CNN
F 3 "~" H 9000 1550 50  0001 C CNN
	1    9000 1550
	1    0    0    -1  
$EndComp
$Comp
L Device:R R5
U 1 1 621FEA88
P 9000 2400
F 0 "R5" H 9070 2446 50  0000 L CNN
F 1 "10k" H 9070 2355 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 8930 2400 50  0001 C CNN
F 3 "~" H 9000 2400 50  0001 C CNN
	1    9000 2400
	1    0    0    -1  
$EndComp
$Comp
L Device:R R6
U 1 1 621FF00E
P 9000 3300
F 0 "R6" H 9070 3346 50  0000 L CNN
F 1 "10k" H 9070 3255 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 8930 3300 50  0001 C CNN
F 3 "~" H 9000 3300 50  0001 C CNN
	1    9000 3300
	1    0    0    -1  
$EndComp
$Comp
L Device:R R7
U 1 1 621FF549
P 9000 4200
F 0 "R7" H 9070 4246 50  0000 L CNN
F 1 "10k" H 9070 4155 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 8930 4200 50  0001 C CNN
F 3 "~" H 9000 4200 50  0001 C CNN
	1    9000 4200
	1    0    0    -1  
$EndComp
$Comp
L Device:R R8
U 1 1 621FFB06
P 9000 5200
F 0 "R8" H 9070 5246 50  0000 L CNN
F 1 "10k" H 9070 5155 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 8930 5200 50  0001 C CNN
F 3 "~" H 9000 5200 50  0001 C CNN
	1    9000 5200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR015
U 1 1 6220033E
P 9000 5350
F 0 "#PWR015" H 9000 5100 50  0001 C CNN
F 1 "GND" H 9005 5177 50  0000 C CNN
F 2 "" H 9000 5350 50  0001 C CNN
F 3 "" H 9000 5350 50  0001 C CNN
	1    9000 5350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR014
U 1 1 62200944
P 9000 4350
F 0 "#PWR014" H 9000 4100 50  0001 C CNN
F 1 "GND" H 9005 4177 50  0000 C CNN
F 2 "" H 9000 4350 50  0001 C CNN
F 3 "" H 9000 4350 50  0001 C CNN
	1    9000 4350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR013
U 1 1 62200FCA
P 9000 3450
F 0 "#PWR013" H 9000 3200 50  0001 C CNN
F 1 "GND" H 9005 3277 50  0000 C CNN
F 2 "" H 9000 3450 50  0001 C CNN
F 3 "" H 9000 3450 50  0001 C CNN
	1    9000 3450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR012
U 1 1 62201549
P 9000 2550
F 0 "#PWR012" H 9000 2300 50  0001 C CNN
F 1 "GND" H 9005 2377 50  0000 C CNN
F 2 "" H 9000 2550 50  0001 C CNN
F 3 "" H 9000 2550 50  0001 C CNN
	1    9000 2550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR011
U 1 1 622019F6
P 9000 1700
F 0 "#PWR011" H 9000 1450 50  0001 C CNN
F 1 "GND" H 9005 1527 50  0000 C CNN
F 2 "" H 9000 1700 50  0001 C CNN
F 3 "" H 9000 1700 50  0001 C CNN
	1    9000 1700
	1    0    0    -1  
$EndComp
Wire Wire Line
	9250 1400 9000 1400
Wire Wire Line
	9250 2250 9000 2250
Wire Wire Line
	9250 3150 9000 3150
Wire Wire Line
	9250 4050 9000 4050
Wire Wire Line
	9250 5050 9000 5050
Text GLabel 9000 1400 0    50   Input ~ 0
S1
Text GLabel 9000 2250 0    50   Input ~ 0
S2
Text GLabel 9000 3150 0    50   Input ~ 0
S3
Text GLabel 9000 4050 0    50   Input ~ 0
S4
Text GLabel 9000 5050 0    50   Input ~ 0
S5
Text GLabel 6700 2400 0    50   Input ~ 0
S1
Text GLabel 6700 2500 0    50   Input ~ 0
S2
Text GLabel 8100 2400 2    50   Input ~ 0
S3
Text GLabel 8100 2300 2    50   Input ~ 0
S4
Text GLabel 8100 2200 2    50   Input ~ 0
S5
Text GLabel 8100 1800 2    50   Input ~ 0
GPIO0
$Comp
L Mouser:AZ1117CD-3.3TRG1 IC1
U 1 1 62208E3A
P 3100 1300
F 0 "IC1" H 3800 1565 50  0000 C CNN
F 1 "AZ1117CD-3.3TRG1" H 3800 1474 50  0000 C CNN
F 2 "Mouser:AZ1117CD33TRG1" H 4350 1400 50  0001 L CNN
F 3 "https://www.diodes.com/assets/Datasheets/AZ1117C.pdf" H 4350 1300 50  0001 L CNN
F 4 "LDO Regulator Pos 3.3V 0.8A 3-Pin(2+Tab) TO-252 T/R" H 4350 1200 50  0001 L CNN "Description"
F 5 "2.38" H 4350 1100 50  0001 L CNN "Height"
F 6 "621-AZ1117CD-3.3TRG1" H 4350 1000 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.co.uk/ProductDetail/Diodes-Incorporated/AZ1117CD-33TRG1?qs=FKu9oBikfSnei3n4%2FTBoVg%3D%3D" H 4350 900 50  0001 L CNN "Mouser Price/Stock"
F 8 "Diodes Inc." H 4350 800 50  0001 L CNN "Manufacturer_Name"
F 9 "AZ1117CD-3.3TRG1" H 4350 700 50  0001 L CNN "Manufacturer_Part_Number"
	1    3100 1300
	1    0    0    -1  
$EndComp
Text GLabel 4500 1300 2    50   Input ~ 0
Vcc
$Comp
L power:GND #PWR04
U 1 1 62209564
P 3100 1100
F 0 "#PWR04" H 3100 850 50  0001 C CNN
F 1 "GND" H 3105 927 50  0000 C CNN
F 2 "" H 3100 1100 50  0001 C CNN
F 3 "" H 3100 1100 50  0001 C CNN
	1    3100 1100
	-1   0    0    1   
$EndComp
Wire Wire Line
	3100 1100 3100 1300
Text GLabel 3100 1400 0    50   Input ~ 0
BAT
Wire Notes Line
	2850 1650 4750 1650
Wire Notes Line
	4750 1650 4750 700 
Wire Notes Line
	4750 700  2850 700 
Wire Notes Line
	2850 700  2850 1650
Text Notes 4100 700  0    50   ~ 0
Linear Regulator\n
Wire Notes Line
	8700 5700 10450 5700
Wire Notes Line
	10450 700  8700 700 
Wire Notes Line
	8700 700  8700 5700
Wire Notes Line
	10450 700  10450 5700
Text Notes 9850 700  0    50   ~ 0
Control buttons
$Comp
L Mouser:SS8050-G Q1
U 1 1 62213D65
P 2150 4100
F 0 "Q1" H 2688 4146 50  0000 L CNN
F 1 "SS8050-G" H 2688 4055 50  0000 L CNN
F 2 "Mouser:SOT95P240X115-3N" H 2700 3950 50  0001 L CNN
F 3 "https://datasheet.datasheetarchive.com/originals/distributors/DKDS-12/229454.pdf" H 2700 3850 50  0001 L CNN
F 4 "Bipolar Transistors - BJT NPN TRANSISTOR 1.5A 40V" H 2700 3750 50  0001 L CNN "Description"
F 5 "1.15" H 2700 3650 50  0001 L CNN "Height"
F 6 "750-SS8050-G" H 2700 3550 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.co.uk/ProductDetail/Comchip-Technology/SS8050-G?qs=LLUE9lz1YbcHg%252BWLMAtcrQ%3D%3D" H 2700 3450 50  0001 L CNN "Mouser Price/Stock"
F 8 "Comchip Technology" H 2700 3350 50  0001 L CNN "Manufacturer_Name"
F 9 "SS8050-G" H 2700 3250 50  0001 L CNN "Manufacturer_Part_Number"
	1    2150 4100
	1    0    0    -1  
$EndComp
$Comp
L Mouser:SS8050-G Q2
U 1 1 62215693
P 2150 5050
F 0 "Q2" H 2688 5004 50  0000 L CNN
F 1 "SS8050-G" H 2688 5095 50  0000 L CNN
F 2 "Mouser:SOT95P240X115-3N" H 2700 4900 50  0001 L CNN
F 3 "https://datasheet.datasheetarchive.com/originals/distributors/DKDS-12/229454.pdf" H 2700 4800 50  0001 L CNN
F 4 "Bipolar Transistors - BJT NPN TRANSISTOR 1.5A 40V" H 2700 4700 50  0001 L CNN "Description"
F 5 "1.15" H 2700 4600 50  0001 L CNN "Height"
F 6 "750-SS8050-G" H 2700 4500 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.co.uk/ProductDetail/Comchip-Technology/SS8050-G?qs=LLUE9lz1YbcHg%252BWLMAtcrQ%3D%3D" H 2700 4400 50  0001 L CNN "Mouser Price/Stock"
F 8 "Comchip Technology" H 2700 4300 50  0001 L CNN "Manufacturer_Name"
F 9 "SS8050-G" H 2700 4200 50  0001 L CNN "Manufacturer_Part_Number"
	1    2150 5050
	1    0    0    1   
$EndComp
$Comp
L Connector_Generic:Conn_01x05 J1
U 1 1 62217FE3
P 2050 2450
F 0 "J1" V 1922 2730 50  0000 L CNN
F 1 "Conn_01x05" V 2013 2730 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x05_P2.54mm_Vertical" H 2050 2450 50  0001 C CNN
F 3 "~" H 2050 2450 50  0001 C CNN
	1    2050 2450
	0    1    1    0   
$EndComp
Text GLabel 1850 2250 1    50   Input ~ 0
5v
Text GLabel 1950 2250 1    50   Input ~ 0
Dn
Text GLabel 2050 2250 1    50   Input ~ 0
Dp
Text GLabel 2250 2250 1    50   Input ~ 0
BAT
$Comp
L power:GND #PWR02
U 1 1 6221AA73
P 2150 2100
F 0 "#PWR02" H 2150 1850 50  0001 C CNN
F 1 "GND" H 2155 1927 50  0000 C CNN
F 2 "" H 2150 2100 50  0001 C CNN
F 3 "" H 2150 2100 50  0001 C CNN
	1    2150 2100
	-1   0    0    1   
$EndComp
Wire Wire Line
	2150 2100 2150 2250
Wire Notes Line
	1600 2700 2850 2700
Wire Notes Line
	2850 1750 1600 1750
Wire Notes Line
	2850 2700 2850 1750
Wire Notes Line
	1600 1750 1600 2700
Text Notes 2250 1750 0    50   ~ 0
Battery charger
Text GLabel 8100 2600 2    50   Input ~ 0
GPIO13
Text GLabel 8100 3000 2    50   Input ~ 0
GPIO23
Text GLabel 8100 2900 2    50   Input ~ 0
GPIO22
$Comp
L Connector_Generic:Conn_01x05 J2
U 1 1 622290DC
P 3700 2500
F 0 "J2" V 3572 2780 50  0000 L CNN
F 1 "Conn_01x05" V 3663 2780 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x05_P2.54mm_Vertical" H 3700 2500 50  0001 C CNN
F 3 "~" H 3700 2500 50  0001 C CNN
	1    3700 2500
	0    1    1    0   
$EndComp
Text GLabel 3500 2300 1    50   Input ~ 0
GPIO13
Text GLabel 3600 2300 1    50   Input ~ 0
GPIO23
Text GLabel 3700 2300 1    50   Input ~ 0
GPIO22
Text GLabel 3900 2300 1    50   Input ~ 0
Vcc
$Comp
L power:GND #PWR05
U 1 1 6222A095
P 3800 2050
F 0 "#PWR05" H 3800 1800 50  0001 C CNN
F 1 "GND" H 3805 1877 50  0000 C CNN
F 2 "" H 3800 2050 50  0001 C CNN
F 3 "" H 3800 2050 50  0001 C CNN
	1    3800 2050
	-1   0    0    1   
$EndComp
Wire Wire Line
	3800 2050 3800 2300
Wire Notes Line
	3200 2700 4750 2700
Wire Notes Line
	4750 2700 4750 1750
Wire Notes Line
	4750 1750 3200 1750
Wire Notes Line
	3200 1750 3200 2700
Text Notes 4100 1750 0    50   ~ 0
Extra connectors
Wire Wire Line
	8100 3100 8100 3200
Connection ~ 8100 3200
$Comp
L Device:LED D1
U 1 1 6226620C
P 5450 4200
F 0 "D1" V 5489 4082 50  0000 R CNN
F 1 "LED" V 5398 4082 50  0000 R CNN
F 2 "Mouser:APHCM2012QBCDF01" H 5450 4200 50  0001 C CNN
F 3 "~" H 5450 4200 50  0001 C CNN
	1    5450 4200
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR0101
U 1 1 622671FE
P 5450 4350
F 0 "#PWR0101" H 5450 4100 50  0001 C CNN
F 1 "GND" H 5455 4177 50  0000 C CNN
F 2 "" H 5450 4350 50  0001 C CNN
F 3 "" H 5450 4350 50  0001 C CNN
	1    5450 4350
	1    0    0    -1  
$EndComp
Text GLabel 5450 3750 1    50   Input ~ 0
Vcc
$Comp
L Device:R R9
U 1 1 62267862
P 5450 3900
F 0 "R9" H 5520 3946 50  0000 L CNN
F 1 "0" H 5520 3855 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 5380 3900 50  0001 C CNN
F 3 "~" H 5450 3900 50  0001 C CNN
	1    5450 3900
	1    0    0    -1  
$EndComp
Wire Notes Line
	5950 3400 5000 3400
Wire Notes Line
	5950 1800 5950 4700
Text GLabel 6700 1500 0    50   Input ~ 0
Vcc
$Comp
L power:GND #PWR?
U 1 1 6222EC31
P 6650 1250
F 0 "#PWR?" H 6650 1000 50  0001 C CNN
F 1 "GND" H 6655 1077 50  0000 C CNN
F 2 "" H 6650 1250 50  0001 C CNN
F 3 "" H 6650 1250 50  0001 C CNN
	1    6650 1250
	-1   0    0    1   
$EndComp
Wire Wire Line
	6700 1400 6650 1400
Wire Wire Line
	6650 1400 6650 1250
Wire Wire Line
	6700 2800 6550 2800
Wire Wire Line
	6550 2800 6550 4000
Wire Notes Line
	6250 1800 6250 700 
Wire Notes Line
	5000 1800 6250 1800
Text Notes 5350 800  0    50   ~ 0
MCU Power Capacitors
Text Notes 5250 1900 0    50   ~ 0
Reset Stabilizing
Text Notes 5500 3500 0    50   ~ 0
Power LED
$EndSCHEMATC
