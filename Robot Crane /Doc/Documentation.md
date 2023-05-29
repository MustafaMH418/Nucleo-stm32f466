# Robot Arm ( Crane )
* A Robot Arm using the Nucleo STM32F446RE microcontroller. The aim of the project was to showcase the potential of low-cost, customizable, and precise robotic solutions using this microcontroller. The project involved designing and building the robot arm from scratch, with a focus on precision, smooth control, and customization. The project utilizes ADC and PWM in the microcontrollers, by using ADC to read the analog signals from the potentiometers and control the servoes using PWM.

### Project Overview:

* The project involved building a robot arm using the ARM Nucleo STM32F446RE microcontroller.
* The robot arm was designed and built from scratch, with a focus on precision, smooth control, and customization.
* The Nucleo STM32F446RE microcontroller allowed for precise movements and control of the arm, while the 3D printed design provided the necessary customization and cost-effectiveness.
* The project was designed to showcase the potential of low-cost, versatile, and precise robotic solutions using the ARM Nucleo STM32F446RE microcontroller.
Detailed Explanation:

In this detailed documentation, I will provide a step-by-step breakdown of the methodology used to design and build the robot arm using the ARM Nucleo STM32F446RE microcontroller. I will discuss the hardware and software components used in the project, including the Nucleo STM32F446RE microcontroller, the 3D printing technology, and the potentiometers. Additionally, Iwill present the results obtained from the project, including the range of control options and the versatility of the robot arm.

### Methodology:

* Hardware Needed & Building: how to build the robot arm. This involved 3D printing the necessary components and assembling them together, including the motors, joints, and potentiometers.
* Programming: Once the robot arm was built, the next step was to program the Nucleo STM32F446RE microcontroller. This involved using the STM32 IDE to develop the necessary code for controlling the arm's movements and reading the potentiometer inputs.
* Testing: Finally, the robot arm was tested to ensure that it was functioning correctly. This involved testing the range of movements and control options available, as well as ensuring that the arm was stable and durable.

![Intro Pic](https://github.com/MustafaMH418/Nucleo-stm32f466/blob/main/Robot%20Crane%20/Doc/Matrials/Overview%20pic.jpg)

## Step 1 : The Hardware
### 1.Circuit
![Circuit](https://github.com/MustafaMH418/Nucleo-stm32f466/blob/main/Robot%20Crane%20/Doc/Matrials/Robot%20ARM_bb.jpg)

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
1. High level initilization
2. Low level initilization
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
This includes Enabling clock the timer peripheral , Configuring the pins that is connected to the timer channels and Enabling the clock of the corresponding GPIO


