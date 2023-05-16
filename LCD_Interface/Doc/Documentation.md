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

## First : What is LCD 1602 How does it work 

* The LCD 1602 is a commonly used alphanumeric liquid crystal display (LCD) module. It consists of 2 rows and 16 columns of characters, hence the name 1602. The module has a built-in controller that allows it to display characters, symbols, and even simple graphics.

* The LCD 1602 is widely used in various electronic applications, including embedded systems, hobby projects, and educational projects. Its low power consumption and ease of use make it a popular choice for displaying information.

* To interface with the LCD 1602, a microcontroller or other external device must send commands and data to the module through its pins. The module typically requires a voltage of 5 volts to operate, but some models can operate at lower voltages.

* Overall, the LCD 1602 is a versatile and useful display module that is commonly used in electronic projects for displaying information in a clear and easy-to-read format.

* The LCD 1602 display module typically has 16 pins, which are used to provide power, ground, and data connections. Here's a brief overview of the function of each pin:

  1.***VSS (Ground)***:<br />
This pin is connected to ground (0V) and is used to provide a reference voltage for the module.

  2.***VDD (Power)***:<br />
This pin is connected to a positive voltage (usually 5V) and is used to power the module.

  3.***V0 (Contrast)*** :<br />
  This pin is used to adjust the contrast of the display. By varying the voltage applied to this pin, the contrast of the display can be adjusted.

  4.***RS (Register Select)***:<br />
This pin is used to select whether data or command is being sent to the module. When this pin is low (0), the module expects a command. When it is high (1), the module expects data.

  5.***RW (Read/Write)***: <br />
This pin is used to select whether data is being read from or written to the module. When it is low (0), data is being written to the module. When it is high (1), data is being read from the module.

  6.***E (Enable)***: <br />
This pin is used to enable the module to receive commands or data.

  7-14. ***D0-D7 (Data)***: <br /> 
These pins are used to send data to the module. When the RS pin is high, the data sent to these pins is displayed on the screen. When the RS pin is low, the data sent to these pins is interpreted as a command.

  15.***A (Anode)***: <br />
This pin is used to backlight the display. It can be connected to a positive voltage to enable the backlight.

  16.***K (Cathode)***:<br />
This pin is the ground connection for the backlight.

* The LCD 1602 display module can work with either a 4-bit (4 wires) parallel or 8-bit (8 wires) parallel interface. Here's a brief overview of how each interface works:

  1. ****4-bit (4 wires) parallel interface****:\
  The 4-bit parallel interface is a simplified version of the 8-bit interface that uses fewer wires. The interface uses 4 data pins (D4-D7) instead of 8 to send data to the module, along with the RS, RW, and E control pins. To send data, the controller sends the higher 4 bits of the data to the module on the D4-D7 lines, followed by a pulse on the E pin. Then, the controller sends the lower 4 bits of the data on the same lines, followed by another pulse on the E pin. This allows the controller to send a full 8-bit command or data to the module using only 4 wires.

  2. ****8-bit (8 wires) parallel interface****:\
  The 8-bit parallel interface uses 8 data pins (D0-D7) to send data to the module, along with the RS, RW, and E control pins. To send data, the controller sends all 8 bits of the data to the module on the D0-D7 lines, followed by a pulse on the E pin.

  In general, the 8-bit parallel interface is faster than the 4-bit interface because it can send data in a single operation, while the 4-bit interface requires two operations to send a full 8-bit command or data. However, the 4-bit interface requires fewer wires, which can be useful in applications where wiring space is limited.

  It's important to note that the initialization sequence for the LCD 1602 display module is different for the 4-bit and 8-bit interfaces. When using the 4-bit interface, the initialization sequence typically involves setting the module to operate in 4-bit mode, while the initialization sequence for the 8-bit interface assumes that the module is already in 8-bit mode.

## Second : How can we use it 
if we refer to the datasheet of LCD 1602 we can find that we need to intilize the lcd module first in order to have data showen on it
the intilization sequence will consist of diffrenet steps of sending commands
Wait at least 15ms after the module power up to allow the power to stabilize.
  
  1. Wait at least 15ms after the module power up to allow the power to stabilize.
  2. Send the command 0x03 (0011b) to the module. This sets the module to 8-bit mode.
  3. Wait at least 4.1ms for the module to process the command.
  4. Send the command 0x03 (0011b) again. This ensures that the module is still in 8-bit mode.
  5. Wait at least 100us for the module to process the command.
  6. Send the command 0x03 (0011b) a third time. This confirms that the module is still in 8-bit mode.
  7. Send the command 0x02 (0010b) to the module. This sets the module to 4-bit mode.
  8. Wait for the module to process the command.
  9. Send the command 0x28 (0010 1000b) to the module. This sets the module to 2-line display mode, 5x8 dot font, and 4-bit interface mode.
  10. Send the command 0x08 (0000 1000b) to the module. This turns off the display, turns off the cursor, and turns off the blink.
  11. Send the command 0x01 (0000 0001b) to the module. This clears the display and sets the cursor to the home position.
  12 Send the command 0x06 (0000 0110b) to the module. This sets the entry mode to increment the cursor and not shift the display.
  13 Send the command 0x0C (0000 1100b) to the module. This turns on the display, turns off the cursor, and turns off the blink.
  
 This can be seen in the code by 
 ```c
    HAL_Delay(50);
	Lcd_Write(0x03,0);
	HAL_Delay(5);
	Lcd_Write(0x3, 0);
	HAL_Delay(2);
	Lcd_Write(0x3, 0);
	HAL_Delay(2);

	Lcd_Write(0x02,0);
	HAL_Delay(2);

	Lcd_Send_Cmd(0x28);
	HAL_Delay(2);
	Lcd_Send_Cmd(0x08);
	HAL_Delay(2);
	Lcd_Send_Cmd(0x01);
	HAL_Delay(2);
	Lcd_Send_Cmd(0x06);
	HAL_Delay(2);
	Lcd_Send_Cmd(0x0C);
	HAL_Delay(2);
```

After this initialization sequence, the module is ready to receive commands and data from the controller to display characters and other information on the screen.


