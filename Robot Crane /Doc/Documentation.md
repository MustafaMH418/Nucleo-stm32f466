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
