# Robot Arm ( Crane )
* A Robot Arm using the Nucleo STM32F446RE microcontroller. The aim of the project was to showcase the potential of low-cost, customizable, and precise robotic solutions using this microcontroller. The project involved designing and building the robot arm from scratch, with a focus on precision, smooth control, and customization. The project utilizes ADC and PWM in the microcontrollers, by using ADC to read the analog signals from the potentiometers and control the servoes using PWM.

### Project Overview:

* The project involved building a robot arm using the ARM Nucleo STM32F446RE microcontroller.
* The robot arm was designed and built from scratch, with a focus on precision, smooth control, and customization.
* The Nucleo STM32F446RE microcontroller allowed for precise movements and control of the arm, while the 3D printed design provided the necessary customization and cost-effectiveness.
* The project was designed to showcase the potential of low-cost, versatile, and precise robotic solutions using the ARM Nucleo STM32F446RE microcontroller.
Detailed Explanation:

In this detailed documentation, I will provide a step-by-step breakdown of the methodology used to design and build the robot arm using the ARM Nucleo STM32F446RE microcontroller. I will discuss the hardware and software components used in the project, including the Nucleo STM32F446RE microcontroller, the 3D printing technology, and the potentiometers. Additionally, I will present the results obtained from the project, including the range of control options and the versatility of the robot arm.

### Methodology:

* Hardware Needed & Building: how to build the robot arm. This involved 3D printing the necessary components and assembling them together, including the motors, joints, and potentiometers.
* Programming: Once the robot arm was built, the next step was to program the Nucleo STM32F446RE microcontroller. This involved using the STM32 IDE to develop the necessary code for controlling the arm's movements and reading the potentiometer inputs.
* Testing: Finally, the robot arm was tested to ensure that it was functioning correctly. This involved testing the range of movements and control options available, as well as ensuring that the arm was stable and durable.

![Intro Pic](https://github.com/MustafaMH418/Nucleo-stm32f466/blob/main/Robot%20Crane%20/Doc/Matrials/Overview%20pic.jpg)

## Step 1 : The Hardware
### 1.Circuit
![Circuit](https://github.com/MustafaMH418/Nucleo-stm32f466/blob/main/Robot%20Crane%20/Doc/Matrials/Robot%20ARM_bb.jpg)

>***Note*** </br>
> * I added an external power supply with 5V - 2A to give the servos a little more power to work with the strucre of the arm </br>
> * It is very important to connect the ground of the power supply to the ground of the microcontroller as showen in the circuit above as we are working with PWM signal which is a relative signal and needs a common ground reference.

### 2. List of Components
| Part Type | Amount | 
|:---------:|:--------:|
| Nucleo STM32f446RE | 1 |
| TowerPro MG90s Servo Motor | 3|
| TowerPro SG90 Servo Motor | 1|
| potentiometer 100K   | 3 |
| 5V Power Supply | 1 |

### 3. Arm Structre
* All the 3d files needed to be printed to assemble the robot arm can be found [here](https://github.com/MustafaMH418/Nucleo-stm32f466/tree/main/Robot%20Crane%20/Doc/Matrials/3D%20desings)
* All the 3d files are designed by Carlo Franciscone Aka. daGHIZmo 
* To print the parts you can seek a company that provide 3d printing services.
* If you have a 3d printer , you can print the parts yourself using a 3d printing software like Ultimaker Cura which will take about 170-200 grams and about 18 hours ***depending on your quality settings and speed***


![cura](https://github.com/MustafaMH418/Nucleo-stm32f466/blob/main/Robot%20Crane%20/Doc/Matrials/Capture.PNG)

> ***Note***
> Weight and Time will differ from a printer to another depending on the various parts of the 3D printer , the settings of printing , the speed of printing and mainly the way the parts are layed on the bed which play a important role in air distance travel between parts

### 4. Assembly
* You can find a step by step assembly instructions [here](https://www.instructables.com/EEZYbotARM/) done by the designer

## Step 2 : Programming
we are going to talk about the code and the programming of the project using multiple prespectives . 
* First we need to know how can we control a servo and how a servo work
* Second we need to generate a PWM signal that can control the servo
* Third how can we use ADC to read the analog signal that will control the servo
* Finally we are going to link all of this together to have a functional Robot

## 1. The Servo
### What is servo motor ?
A servo motor is a type of motor that is commonly used in robotics and other applications that require precise control of angular position. Servo motors are designed to rotate to a specific angle and hold that position, allowing them to be used in a wide range of applications where precise control is needed.

A servo motor consists of a rotor, a stator, and a control circuit. The rotor is a permanent magnet that rotates around a central axis, while the stator is a series of coils that generate a magnetic field when an electrical current is passed through them. The control circuit is responsible for receiving commands from an external source and adjusting the position of the rotor accordingly.

### Servo pinout

![servoPins](https://github.com/MustafaMH418/Nucleo-stm32f466/blob/main/Robot%20Crane%20/Doc/Matrials/servo_pinout.png)

1. ***Power***:This wire provides power to the servo motor, typically in the range of 4.8 to 6 volts.
3. ***Ground***: This wire is connected to ground and completes the electrical circuit.
5. ***Signal***: This wire carries the control signal from the microcontroller or other control device to the servo motor. The signal is typically a PWM (Pulse Width Modulation) signal that controls the position of the servo motor.

### How to control the servo motor ?
To control a servo , you need to send a series of pulses to the servo motor, with the width of each pulse determining the position of the servo.


![ServoPWM](https://github.com/MustafaMH418/Nucleo-stm32f466/blob/main/Robot%20Crane%20/Doc/Matrials/servo-control-2.png)


Here are the basic steps for controlling a servo using PWM:</br>
1. Determine the PWM frequency: The first step is to determine the PWM frequency you want to use. This will depend on the specific servo motor you are working with, but a common frequency is 50 Hz.</br>
2. Determine the pulse width range: The next step is to determine the pulse width range for the servo motor. This will also depend on the specific servo motor, but a common range is 1000 to 2000 microseconds.</br>
3. Calculate the pulse width for the desired position: Once you know the pulse width range, you can calculate the pulse width for the desired position. For example, if you want the servo to be at 90 degrees, you would use a pulse width of 1500 microseconds (the midpoint of the pulse width range).</br>
4. Send the PWM signal: Finally, you can send the PWM signal to the servo motor using a microcontroller or other control device. This involves sending a series of pulses at the chosen frequency, with the width of each pulse corresponding to the desired position of the servo.

****So we reach to the point that we have to generate a PWM signal with specific duty cycle to give the servo a specific angle , how can we generate a PWM ?****

## 2. PWM Generation 
### What is PWM ?
* PWM stands for Pulse Width Modulation. It is a technique used in electronics to control the amount of power delivered to a load by varying the width of a pulse of electrical power. PWM is commonly used to control the speed of DC motors, the position of servo motors, and the brightness of LEDs.

* In a PWM signal, the power is turned on and off at a high frequency, typically in the range of several kilohertz to several megahertz. The percentage of time that the power is on (the duty cycle) determines the average power delivered to the load. For example, if the power is on for 50% of the time and off for 50% of the time, the average power delivered to the load will be half of the maximum power.

* By varying the duty cycle of the PWM signal, you can control the amount of power delivered to the load and thus control its behavior. For example, in a DC motor, increasing the duty cycle of the PWM signal will increase the speed of the motor, while decreasing the duty cycle will decrease the speed. In a servo motor, the duty cycle is used to control the position of the motor, with different duty cycles corresponding to different angles.
* The STM32F446RE microcontroller features a number of advanced peripheral devices, including timers with PWM (pulse width modulation) functionality. These timers can be used to generate PWM signals for controlling servo motors, DC motors, and other devices that require precise control of their output.

### How to generate PWM signals on STM32F446 Microcontroller ?
* PWM signals are typically generated using timers in microcontrollers. A timer is a peripheral device that can be used to generate precise timing signals with specific frequencies and duty cycles
* ARM microcontrollers typically have multiple types of timers with different features and capabilities. some of the common types of timers are:
1. General-purpose timers: These timers are the most basic type of timers found in ARM microcontrollers. They typically have multiple channels and can be used to generate timing signals and trigger interrupts at specific intervals. General-purpose timers are commonly used in applications like motor control, robotics, and real-time systems.
2. Advanced-control timers: These timers are designed for more complex applications like motor control and power conversion. They typically have more advanced features like dead-time insertion, PWM generation, and synchronization.

****So we need to initlize a timer that can produce a PWM ( Advanced timer ) , in nucleo stm32f446re we can use timer2****
To initilize the timer we need to do some steps 
1. High level Initilization
2. Low level Initilization
3. Starting the timer

### 1. High Level Initilization
This includes defining a handler for the timer and configuring the channels of the timer
```c
  TIM_HandleTypeDef htim2;
  htim2.Instance = TIM2;        // Base Address of the Timer 
	htim2.Init.Prescaler = 160;
	htim2.Init.Period = 1000-1;
	
	if(HAL_TIM_PWM_Init(&htim2) != HAL_OK)
		Error_Handler();
    
```

In this part of the code we define a handler for the timer peripherial & initilizing its parameters 
> ***Note***
> In this project i am using HSE as the driving oscillator for all clocks and in nucleo stm32f446re , HSE is bypassed from the oscillator of the debugging circuit with 8MHz

As from the explaination in the servo section above we concluded that the servo will need a signal of `50Hz` , As we getting an `8Mhz` clock dividing that by a prescalar of `160` will lead to `50Khz` clock to the timer , by setting the period to `1000` , the timer will give a signal of exactly `50Hz`

Now we need to configure the channels of the timers 

```c
TIM_OC_InitTypeDef pwm_config = {0};
	pwm_config.Pulse = 25;
	pwm_config.OCMode = TIM_OCMODE_PWM1;
	pwm_config.OCPolarity = TIM_OCPOLARITY_HIGH;

	if(HAL_TIM_PWM_ConfigChannel(&htim2, &pwm_config, TIM_CHANNEL_1 ) != HAL_OK)
		Error_Handler();

	if(HAL_TIM_PWM_ConfigChannel(&htim2, &pwm_config, TIM_CHANNEL_2) != HAL_OK)
		Error_Handler();

	if(HAL_TIM_PWM_ConfigChannel(&htim2, &pwm_config, TIM_CHANNEL_3) != HAL_OK)
		Error_Handler();

	if(HAL_TIM_PWM_ConfigChannel(&htim2, &pwm_config, TIM_CHANNEL_4 ) != HAL_OK)
		Error_Handler();

```

> ***Note***
> We need four PWM signals to control the four motors , since all the PWM signals will use the same base counting `50Hz` we can define 4 channels to supply the 4 signals

Here we defined a structure that holds the parameters of channel configurations and set it to `0` to default any settings before initilizing 

We need to roll back for a second to understand why we have a pulse of 25
We concluded that to get the servo to be in the default state " 0 degree " we have to supply a signal with only 1ms ON and the rest of the 20ms will be OFF
``` Math
Duty Cycle = 1ms / 20ms = 0.05 
```
so we need a duty cycle of 5%, Since we have a period of 1000 , The pulse will be `1000 * 0.05 = 50`
***Thats the number of ticks the timer need to count will making a high signal and after this number is counted he will count the rest of the signal (rest of 1000) will giving low signal***

so the result is `50` ?? , why the pulse is 25 above ?
As mentioned in the servo section some servo might have a different range than 1ms to 2ms , in my case with my servo it is 0.5ms to 2.5ms which gave a full 180 degree rotate
So if we repeated the above steps with 0.5ms and 2.ms to find the margins of the pulse we are going to give we find the margins are 25 to 125

### 2. Low Level Initilization
This includes Enabling clock to the timer peripheral , Configuring the pins that is connected to the timer channels and Enabling the clock of the corresponding GPIO


1.Enable Clock :</br>
This can be done in `HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)` which is called inside `HAL_TIM_PWM_Init` and is defined as weak to give the ability to overwrite it in `msp.c` file

```c
 void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim){
	__HAL_RCC_TIM2_CLK_ENABLE();
}
```
2. Pins Configurations : </br>
We can include all the code needed for enabling clock of GPIO and configuring pins in a function called `TIM_MspPostInit()` which can be called after all the highlevel Initilization 
```c
void TIM_MspPostInit(){
	__HAL_RCC_GPIOA_CLK_ENABLE();	// Enabling clock for GPIOA
	__HAL_RCC_GPIOB_CLK_ENABLE();	// Enabling clock for GPIOB
	
	GPIO_InitTypeDef sPins = {0};
	sPins.Pin = GPIO_PIN_2 | GPIO_PIN_9 | GPIO_PIN_10;	// TIM Channels in GPIOB
	sPins.Mode = GPIO_MODE_AF_PP;				// Defined in Alternate function mode to connect it to the TIM2 Channels
	sPins.Alternate = GPIO_AF1_TIM2;			// Configuring the Alternate function to TIM2
	HAL_GPIO_Init(GPIOB, &sPins);

	sPins.Pin = GPIO_PIN_15;				// TIM Channel pin in GPIOA
	HAL_GPIO_Init(GPIOA, &sPins);

	HAL_NVIC_SetPriority(TIM2_IRQn, 15, 0);			// Setting the NVIC Priority of TIM2
	HAL_NVIC_EnableIRQ(TIM2_IRQn);				// Enabling the interrupt of TIM2

}
```

3. Starting The Timer : </br>
Now that we finished all the initlization all we need to start the timer with `HAL_TIM_PWM_START(&htim2,TIM_CHANNEL_x)` and this function return the state of the operation(starting timer) if it succeded or failed so we need to compare the return with `HAL_OK`

```c
	if(HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1) != HAL_OK)
			Error_Handler();

	if(HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2) != HAL_OK)
			Error_Handler();

	if(HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3) != HAL_OK)
			Error_Handler();

	if(HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4) != HAL_OK)
			Error_Handler();
			
```

>***Note***
> We need four starting functions as we are using four different channels

## 3. ADC
* ADC stands for Analog-to-Digital Converter. It is an electronic device that converts an analog signal, such as a voltage or current, into a digital representation that can be processed by a computer or other digital system.
* Analog signals are continuous and can take on any value within a certain range. In order to process an analog signal using a digital system, it must first be converted into a digital representation that consists of a series of discrete numbers. This is where an ADC comes in.
* An ADC works by sampling the analog signal at regular intervals and converting each sample into a digital value that represents the amplitude of the signal at that point in time. The number of bits used to represent each sample determines the resolution of the ADC and the accuracy of the digital representation.
* ADCs are used in a wide range of applications, including audio and video processing, data acquisition and control systems, communication systems, and measurement and instrumentation systems. They are an essential component in many electronic systems, allowing analog signals to be processed and analyzed using digital techniques.

![ADC](https://github.com/MustafaMH418/Nucleo-stm32f466/blob/main/Robot%20Crane%20/Doc/Matrials/G3Mgs.png)

There are three main modes of operation for ADC sampling: single, scan, and continuous.</br>
* ***Single mode*** : </br>
In single mode, the ADC samples a single input channel once and produces a single output value. This mode is useful for applications that require occasional or infrequent sampling of a single channel.

* ***Scan mode*** : </br>
In scan mode, the ADC samples a predetermined set of input channels in a sequential manner and produces a corresponding set of output values. This mode is useful for applications that require periodic sampling of multiple channels, such as monitoring multiple sensors.

* ***Continuous mode*** : </br>
In continuous mode, the ADC samples a single input channel repeatedly at a fixed rate and produces a continuous stream of output values. This mode is useful for applications that require real-time monitoring of a single channel, such as audio or video processing.

Each of these modes has its own advantages and disadvantages. Single mode is simple and efficient, but it may not be suitable for applications that require frequent sampling of multiple channels. Scan mode is useful for monitoring multiple channels, but it may introduce delays between samples and may not provide real-time data. Continuous mode provides real-time data, but it may consume more power than other modes and may introduce noise due to the constant sampling.

The choice of mode depends on the specific requirements of the application, including the desired sampling rate, number of channels, power consumption, and data processing requirements.</br>

***Same as the PWM Initilization we are going to need to do a High Level Initlization , Low Level Initlization and Start the ADC***

### 1. High Level Initilization
This includes defining a handler for the timer and configuring the channels of the ADC

```c
void ADC_Init(){
ADC_HandleTypeDef sADC = {0};
	sADC.Instance = ADC1;							// Base Address of ADC1
	sADC.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;			// a prescalar which will divide the incoming clock by 2
	sADC.Init.Resolution = ADC_RESOLUTION_12B;				// Setting the resolution of the ADC to 12-bits which is the highest resolution in stm32f446re
	sADC.Init.ScanConvMode = DISABLE;					// Disabling the Scan mode of the adc
	sADC.Init.ContinuousConvMode = DISABLE;					// Disabling the continous mode of the adc
	sADC.Init.DiscontinuousConvMode = DISABLE;				// Disabling the discontinous mode of the adc
	sADC.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;		// Setting the External trigger for conversation to NONE as the external trigger depends on a software start 
	sADC.Init.ExternalTrigConv = ADC_SOFTWARE_START;			// Setting The External trigger for conversation to a software start
	sADC.Init.DataAlign = ADC_DATAALIGN_RIGHT;				// Setting Data Align to the Right
	sADC.Init.NbrOfConversion = 1;						// Number of conversation is set to 1 as we are doing a channel by channel conversation
	sADC.Init.DMAContinuousRequests = DISABLE;				// Disabling DMA requests as we are not using DMA in this project to take values from ADC
	sADC.Init.EOCSelection = ADC_EOC_SINGLE_CONV;				// ADC will generate an end of conversion (EOC) flag after a single conversion is completed.
	  
	  if (HAL_ADC_Init(&sADC) != HAL_OK)
	  	    Error_Handler();
}
```
In configuring channels we come to a little different approach. To Read from Multiple Channels in ADC it is best to do a Scan mode with DMA , but to simplify the project a little as the DMA will require its own initilizations with a timer to be a trigger for scanning we are gonna use the single conversation mode while switching between channels to get values. this can done by having four functions , each function will have a job of just redefinig the working channel to the next channel to be scanned ( This can be done also with a single function and giving the channel as argument to switch to it ) while stopping the ADC after each channel value is read and starting back after the channel is redefined to the next channel

```c
void ADC_SET_CH0(){
	ADC_ChannelConfTypeDef CHConf = {0};
	CHConf.Channel = ADC_CHANNEL_0;
	CHConf.Rank = 1;
	CHConf.SamplingTime = ADC_SAMPLETIME_84CYCLES;
	
	if(HAL_ADC_ConfigChannel(&sADC, &CHConf) != HAL_OK)
		Error_Handler();
}

void ADC_SET_CH1(){
	ADC_ChannelConfTypeDef CHConf = {0};
	CHConf.Channel = ADC_CHANNEL_1;
	CHConf.Rank = 1;
	CHConf.SamplingTime = ADC_SAMPLETIME_84CYCLES;
	
	if(HAL_ADC_ConfigChannel(&sADC, &CHConf) != HAL_OK)
		Error_Handler();
}

void ADC_SET_CH4(){
	ADC_ChannelConfTypeDef CHConf = {0};
	CHConf.Channel = ADC_CHANNEL_4;
	CHConf.Rank = 1;
	CHConf.SamplingTime = ADC_SAMPLETIME_84CYCLES;
	
	if(HAL_ADC_ConfigChannel(&sADC, &CHConf) != HAL_OK)
		Error_Handler();
}

```

### 2. Low Level Initilization
This includes Enabling clock to the ADC peripheral , Configuring the pins that is connected to the ADC channels and Enabling the clock of the corresponding GPIO

This can be done in `HAL_ADC_MspInit(ADC_HandleTypeDef* hadc)` which is called inside `HAL_ADC_Init` and is defined as weak to give the ability to overwrite it in `msp.c` file

```c
void HAL_ADC_MspInit(ADC_HandleTypeDef* hadc){
	__HAL_RCC_ADC1_CLK_ENABLE();	// Enabling Clock for the ADC1
	
	GPIO_InitTypeDef sPins = {0};
	sPins.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_4;	// Pins that is connecte to ADC Channels 0,1,4
	sPins.Mode = GPIO_MODE_ANALOG;				// Setting Mode to Analog
	sPins.Pull = GPIO_PULLDOWN;
	HAL_GPIO_Init(GPIOA, &sPins);

	HAL_NVIC_SetPriority(ADC_IRQn, 15, 0);			// Setting NVIC Priority for the ADC Interrupt
	HAL_NVIC_EnableIRQ(ADC_IRQn);				// Enabling ADC Interrupt

}
```

### 3. Starting ADC




