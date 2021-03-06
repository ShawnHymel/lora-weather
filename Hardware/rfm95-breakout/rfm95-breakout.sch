EESchema Schematic File Version 4
EELAYER 29 0
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
$EndDescr
$Comp
L RFM95W-868S2:RFM95W-868S2 U1
U 1 1 5CB4D65F
P 6300 3700
F 0 "U1" H 6300 4367 50  0000 C CNN
F 1 "RFM95W-868S2" H 6300 4276 50  0000 C CNN
F 2 "RFM95W-868S2:XCVR_RFM95W-868S2" H 6300 3700 50  0001 L BNN
F 3 "" H 6300 3700 50  0001 L BNN
F 4 "SMD-16 Hope Microelectronics" H 6300 3700 50  0001 L BNN "Field4"
F 5 "RFM95W-868S2" H 6300 3700 50  0001 L BNN "Field5"
F 6 "" H 6300 3700 50  0001 L BNN "Field6"
F 7 "Unavailable" H 6300 3700 50  0001 L BNN "Field7"
F 8 "None" H 6300 3700 50  0001 L BNN "Field8"
	1    6300 3700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0101
U 1 1 5CB4E001
P 7100 4300
F 0 "#PWR0101" H 7100 4050 50  0001 C CNN
F 1 "GND" H 7105 4127 50  0000 C CNN
F 2 "" H 7100 4300 50  0001 C CNN
F 3 "" H 7100 4300 50  0001 C CNN
	1    7100 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	7000 4000 7100 4000
Wire Wire Line
	7100 4000 7100 4100
Wire Wire Line
	7000 4100 7100 4100
Connection ~ 7100 4100
Wire Wire Line
	7100 4100 7100 4200
Wire Wire Line
	7000 4200 7100 4200
Connection ~ 7100 4200
Wire Wire Line
	7100 4200 7100 4300
$Comp
L Connector:Conn_01x01_Male J3
U 1 1 5CB4EEA3
P 7300 3500
F 0 "J3" H 7272 3432 50  0000 R CNN
F 1 "Conn_01x01_Male" H 7272 3523 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 7300 3500 50  0001 C CNN
F 3 "~" H 7300 3500 50  0001 C CNN
	1    7300 3500
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x06_Male J2
U 1 1 5CB4FED9
P 4250 4350
F 0 "J2" H 4358 4731 50  0000 C CNN
F 1 "Conn_01x06_Male" H 4358 4640 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x06_P2.54mm_Vertical" H 4250 4350 50  0001 C CNN
F 3 "~" H 4250 4350 50  0001 C CNN
	1    4250 4350
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x07_Male J1
U 1 1 5CB515F1
P 4250 3300
F 0 "J1" H 4358 3781 50  0000 C CNN
F 1 "Conn_01x07_Male" H 4358 3690 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x07_P2.54mm_Vertical" H 4250 3300 50  0001 C CNN
F 3 "~" H 4250 3300 50  0001 C CNN
	1    4250 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	7100 2950 7100 3300
Wire Wire Line
	7100 3300 7000 3300
Wire Wire Line
	4450 4150 4800 4150
Wire Wire Line
	4800 4150 4800 3800
Wire Wire Line
	4800 3800 5600 3800
Wire Wire Line
	4450 4250 4900 4250
Wire Wire Line
	4900 4250 4900 3900
Wire Wire Line
	4900 3900 5600 3900
Wire Wire Line
	4450 4350 4700 4350
Wire Wire Line
	4700 4350 4700 3900
Wire Wire Line
	4450 4450 5000 4450
Wire Wire Line
	5000 4450 5000 4000
Wire Wire Line
	5000 4000 5600 4000
Wire Wire Line
	4450 4550 5100 4550
Wire Wire Line
	5100 4550 5100 4100
Wire Wire Line
	5100 4100 5600 4100
Wire Wire Line
	4450 4650 5200 4650
Wire Wire Line
	5200 4650 5200 4200
Wire Wire Line
	5200 4200 5600 4200
$Comp
L power:VCC #PWR0102
U 1 1 5CB57DAE
P 7100 2950
F 0 "#PWR0102" H 7100 2800 50  0001 C CNN
F 1 "VCC" H 7117 3123 50  0000 C CNN
F 2 "" H 7100 2950 50  0001 C CNN
F 3 "" H 7100 2950 50  0001 C CNN
	1    7100 2950
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR0103
U 1 1 5CB586A0
P 4700 3900
F 0 "#PWR0103" H 4700 3750 50  0001 C CNN
F 1 "VCC" H 4717 4073 50  0000 C CNN
F 2 "" H 4700 3900 50  0001 C CNN
F 3 "" H 4700 3900 50  0001 C CNN
	1    4700 3900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0104
U 1 1 5CB59EAE
P 4550 3700
F 0 "#PWR0104" H 4550 3450 50  0001 C CNN
F 1 "GND" H 4555 3527 50  0000 C CNN
F 2 "" H 4550 3700 50  0001 C CNN
F 3 "" H 4550 3700 50  0001 C CNN
	1    4550 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	4450 3600 4550 3600
Wire Wire Line
	4550 3600 4550 3700
Wire Wire Line
	4450 3500 4900 3500
Wire Wire Line
	4900 3500 4900 3700
Wire Wire Line
	4900 3700 5600 3700
Wire Wire Line
	4450 3400 5000 3400
Wire Wire Line
	5000 3400 5000 3600
Wire Wire Line
	5000 3600 5600 3600
Wire Wire Line
	4450 3300 5100 3300
Wire Wire Line
	5100 3300 5100 3500
Wire Wire Line
	5100 3500 5600 3500
Wire Wire Line
	4450 3200 5200 3200
Wire Wire Line
	5200 3200 5200 3400
Wire Wire Line
	5200 3400 5600 3400
Wire Wire Line
	4450 3000 5300 3000
Wire Wire Line
	5300 3000 5300 3300
Wire Wire Line
	5300 3300 5600 3300
Wire Wire Line
	7000 3500 7100 3500
Wire Wire Line
	4450 3100 4550 3100
Text Label 4550 3100 0    50   ~ 0
MOSI
Wire Wire Line
	7000 3800 7100 3800
Text Label 7100 3800 0    50   ~ 0
MOSI
$EndSCHEMATC
