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
 void LCD_Init(){
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
	}
```

After this initialization sequence, the module is ready to receive commands and data from the controller to display characters and other information on the screen.

> **Note**
> Until the command (0x02) is sent the Lcd module will be working in 8-Bit mode but code is sending only 4-bits on the D4-D7 only but after sending the command (0x02) code must send the full 8-bit data on two steps as explained above

> **HAL_Delay**
> In the code, the ```HAL_Delay``` function is utilized as a wait command, instead of configuring a dedicated timer for this purpose. It should be noted, however, that ```HAL_Delay``` relies on the Systick timer to achieve its functionality. The Systick timer must tick every 1ms with accuracy in order for ```HAL_Delay``` to work as intended. If the clock in the program is changed or reconfigured, it may be necessary to reconfigure the Systick timer to ensure proper functioning of the ```HAL_Delay``` function. 
> I found Systick clock configure using this to be very helpful 
```c
HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);
HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
 ```
 
## Third : Writing on LCD

To send data and commands to the LCD module, two steps are required:\
	1.  GPIO pins used for communication with the LCD module must be configured properly.\
	2. A set of functions must be written that utilize these pins to send data and commands to the module.\


### 1.GPIO Configuration
Configuring a GPIO pin needs 3 Steps
1. Enabling the Clock to GPIO\
	We can do that using the Macro
	```c
	__HAL_RCC_GPIOA_CLK_ENABLE();
	```
	but since we are using pins from both GPIOA and GPIOB we will also need to enable the clock for GPIOB
	```c
	__HAL_RCC_GPIOB_CLK_ENABLE();
	```
	<br />
2. Defining a typedef which will have the parameters of the pin
	There is a typedef also provided by the HAL Layer ```GPIO_InitTypeDef``` that we can use to define the parameters of each pin and we see that in 
	```c
	GPIO_InitTypeDef GPIO_init;
	```
	we can define the Pins from each GPIO in one process as they will have the same parameters
	```c
	GPIO_init.Pin = rs_pin | en_pin | D7_pin;
	GPIO_init.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_init.Pull = GPIO_PULLDOWN;
	```
	and for pins from GPIOA
	```c
	GPIO_init.Pin = D6_pin | D5_pin | D4_pin;
	GPIO_init.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_init.Pull = GPIO_PULLDOWN;
	```
> ***Note***
> All the Pins are defined by Macros in the header file which is inclueded in the project and you can refer to
<br />

3. Initilizing the GPIO with the dedicated typedef
	To initilize GPIO we can use ```HAL_GPIO_Init()``` Which is also Implemented in the HAL Layer , This function takes two arguments which are The base address of the GPIO and a pointer to the ```GPIO_InitTypedef``` and return nothing. The function can be used as following
	```c
	HAL_GPIO_Init(GPIOB, &GPIO_init);
	```
	Which will used be after defining parameters of pins related to GPIOB since we are using the same structure to hold data of both pins sequentially
	```c
	HAL_GPIO_Init(GPIOA, &GPIO_init);
	```
	Which will be used after defining parameters of pins related to GPIOA
By now we finished all the configurations needed for the GPIO Pins
> ***Warning***
> All GPIO Pins Configurations needed must be done BEFORE initilizing the lcd or any communications with the lcd module 
<br />
<br />

### 2. Functions to Transfer data to LCD
1. ***Write Function*** <br />
	This will be the base function that will break down command or data and send it on the parallel 4 lines, The function will take 2 arguments which will be the data or command to send and the value of RS. RS value will be ```1``` in case of data and will be ```0``` in case of commands
	
```c
void Lcd_Write(char data, uint8_t rs){
	HAL_GPIO_WritePin(rs_port, rs_pin, rs);

	HAL_GPIO_WritePin(D7_port, D7_pin, (data>>3)&0x01);
	HAL_GPIO_WritePin(D6_port, D6_pin, (data>>2)&0x01);
	HAL_GPIO_WritePin(D5_port, D5_pin, (data>>1)&0x01);
	HAL_GPIO_WritePin(D4_port, D4_pin, (data>>0)&0x01);

	HAL_GPIO_WritePin(en_port, en_pin, GPIO_PIN_SET);
	HAL_Delay(10);
	HAL_GPIO_WritePin(en_port, en_pin, GPIO_PIN_RESET);
	HAL_Delay(10);

}
```
the function have to set and reset the ```EN``` pin as this signals the LCD module that the data on the line now is the data it needs to read and the next Pin set will mean that the next segment is ready
>***Note***
> I added a delay of 10ms between setting ```EN``` and Resetting it just to give the LCD module a time to read the sent data 
<br />

2. ***Data Send Function***
A function that will break any 8-bit data it recieves and give it to the Write function as two parts (4-bit) while giving value of ```RS``` of ```1```
```c
void Lcd_Send_Data(char data){
	char data_to_send = 0;
	data_to_send = (data >> 4) & 0x0f ;
	Lcd_Write(data_to_send,1);
	data_to_send = data & 0x0f ;
	Lcd_Write(data_to_send,1);
}
```

with the same concept we can make a function that instead of taking 1 byte and break it into 4-bit we can make a function that can take a whole string and break it with the help of the above function
```c
void Lcd_Send_String(char *str){
	while(*str != '\0')
		Lcd_Send_Data(*str++);
}
```

