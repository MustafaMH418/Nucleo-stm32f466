# LCD Interface
Interfacing LCD 1602 using Nucleo STM32F446RE Board is a project that aims to display information on an LCD screen using an ARM controller. The project involves interfacing an LCD 1602 with a Nucleo STM32F446RE board using GPIO pins. The ARM controller sends data to the LCD screen through these GPIO pins, which is then displayed on the LCD screen.

The project is designed to help understand the working of GPIO pins and how they can be used to interface with external devices. The project uses the stm32 IDE to program the ARM controller.

The successful completion of this project demonstrates the ability to interface an LCD 1602 with an ARM controller using a Nucleo STM32F446RE board. The project can be extended to include more complex applications such as displaying sensor data on the LCD screen.

In this Documentation, we will discuss the methodology used to interface the LCD 1602 with the ARM controller, the hardware and software components of the project, and the results obtained. We will also discuss the potential applications of the project and its significance in the field of embedded systems.

## List of Components
| Parts        |
| ------------- |
|Nucleo STM32F446RE Board  | 
| LCD 1602      |
| Potentiometer | 
| BreadBoard |
| Jumper Wires |

## Circuit
![project circuit](https://github.com/MustafaMH418/Nucleo-stm32f466/blob/main/LCD_Interface/Doc/Materials/LCD1602_bb.jpg)

## Circuit Pinout
| Pins | To |
|:-----:|:------:|
| VSS | GND |
| VDD | +5V|
| V0 | Potinometer |
| RS | PB8|
| R/W | GND |
| EN | PB9|
| DB4 | PA5|
| DB5 | PA6 |
| DB6 | PA7|
| DB7 | PB6 |
| Anode | +5V |
| Cathode | GND |


