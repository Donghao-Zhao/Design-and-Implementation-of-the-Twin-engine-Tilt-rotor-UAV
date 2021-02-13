# Design-and-Implementation-of-the-Twin-engine-Tilt-rotor-UAV

Sorry that annotations are in Chinese, I'll translate them as soon as possible.

Visit my website for details:

http://donghao.tech/uav-undergraduate-thesis-uav/

Design and Implementation of the Twin-engine Tilt-rotor UAV

Project Description:

  Duration: Jul 2018 – May 2019

  This is my undergraduate thesis.

Purpose:

To design a flight control system that controls a Twin-engine Tilt-rotor UAV, including the design of the hardware and embedded system of the flight controller, self-stabilizing and basic movement control program, and telecommunication and remote-control software.

Workload:

1. Hardware: Built the flight control system of the UAV based on the ARM Cortex-M4 microcontroller. Programmed the MCU to obtain the data delivered through IIC from gyroscope, acceleration sensor and ultrasonic ranging sensor; used PWM signal to manipulate the speed and the vector direction of the propellers that is attached with brushless motors and servo gear.

2. Control: Developed the attitude calculation program based on the quaternion algorithm; developed the self-stabilizing, altitude control, and basic space movement control program based on the PID algorithm.

3. Software: Developed network-based telecommunication software in the Linux system. Programmed a Raspberry Pi Zero to translate and relay the data of the two-way communication between the data from wireless network and the MCU’s data from UART; deployed a cloud server as the network transmission relay; developed a crude ground control software on computer using QT to control the UAV through self-designed control protocol and to monitor the UAV through network.

Results:

A UAV model was assembled to obtain experimental data and to verify the feasibility of the software and algorithm to improve the design, and my thesis was rated as excellent graduation thesis of my campus.
