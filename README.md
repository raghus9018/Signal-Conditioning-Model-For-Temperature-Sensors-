\# Signal Conditioning Model for Temperature Sensors



\## Project Overview



This project presents an Arduino-based temperature measurement and signal conditioning model designed to interface with multiple temperature sensors.



The system acquires temperature signals from different sensors, processes the signals using Arduino, and displays the measured temperature on a 16×2 I2C LCD. The temperature readings are also transmitted through the Serial Monitor for monitoring and analysis.



\## Sensors Used



\- Thermistor

\- Thermocouple

\- PT100 RTD

\- LM35



\## Hardware Used



\- Arduino

\- 16×2 I2C LCD

\- Thermistor

\- Thermocouple

\- PT100 RTD

\- LM35

\- Resistors and signal-conditioning components

\- Connecting wires

\- Breadboard / prototype setup



\## Sensor Connections



| Sensor | Arduino Analog Pin |

|---|---|

| Thermistor | A0 |

| Thermocouple | A1 |

| PT100 RTD | A2 |

| LM35 | A3 |



\## Working Principle



1\. Temperature sensors generate electrical signals corresponding to temperature.

2\. The sensor signals are connected to the Arduino analog input channels.

3\. The Arduino's ADC converts the analog signals into digital values.

4\. Sensor-specific calculations are performed to estimate temperature.

5\. The measured temperature is displayed on the 16×2 I2C LCD.

6\. The readings are also transmitted through the Serial Monitor.

7\. The LCD automatically rotates between the four sensor readings every two seconds.



\## Signal Processing



\### Thermistor



The thermistor is implemented using a voltage-divider circuit. Its resistance is calculated from the measured voltage, and the Steinhart-Hart approximation using the Beta parameter is used to estimate temperature.



\### Thermocouple



The thermocouple input is converted into a temperature value based on the output of its signal-conditioning amplifier. The conversion factor in the Arduino program can be adjusted according to the amplifier and thermocouple interface used.



\### PT100 RTD



The PT100 resistance is calculated from the measured voltage using the assumed voltage-divider configuration. The resistance-to-temperature relationship is then used to estimate temperature.



\### LM35



The LM35 provides an analog voltage proportional to temperature. The Arduino ADC reading is converted into temperature using the LM35 sensitivity.



\## Software



\- Arduino IDE

\- Embedded C/C++

\- Arduino libraries:

&#x20; - Wire

&#x20; - LiquidCrystal\_I2C



\## Features



\- Supports four different temperature sensors

\- Analog signal acquisition using Arduino ADC

\- 16×2 I2C LCD interface

\- Automatic display rotation

\- Serial Monitor output

\- Sensor-specific temperature calculations

\- Simple and low-cost prototype



\## Applications



This model can be used for:



\- Temperature measurement systems

\- Sensor interfacing demonstrations

\- Instrumentation laboratory experiments

\- Embedded systems projects

\- Signal conditioning studies

\- Educational temperature monitoring systems



\## Future Improvements



\- Improve thermocouple signal conditioning and calibration

\- Add sensor calibration and error compensation

\- Add data logging

\- Add graphical monitoring

\- Implement wireless monitoring

\- Improve accuracy using dedicated sensor interface circuits



\## Project Structure



```text

Signal-Conditioning-Model-for-Temperature-Sensors/

│

├── SCM/

│   └── SCM.ino

│

└── README.md

