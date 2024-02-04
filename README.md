Worked in a team of myself and another mechatronics student from Cal Poly. 

Mechanical Design

The tripod was almost entirely constructed out of 3D printed PLA from an FDM style 3D printer with exceptions for the fasteners, lead screws for each leg, 2 stepper and one brushed DC motors, rubber feet, and Lazy Susan mechanism for panning functionality. All parts were designed from scratch using Solidworks. The main mechanisms of the design include the Lazy Susan that is driven with a brushed DC motor coupled with a female D-shaft hole printed in the PLA and stepper motors connected with lead screws that are rotating rotationally fixed brass nuts creating linear actuators for each leg. 

Sensors

We made use of two sensors: an IMU for leveling feedback for the tripod communicating serially to the microcontroller (STM32F411CEU6) via I2C and a camera which took visual data interpreted by Open CV in Python running on an NVIDIA Jetson NANO SBC communicating serially via UART to that same microcontroller. The IMU was straight forward to set up in C and we were soon getting readings back in our PUTTY window from UAR 

We used a total of four actuators: 3 identical 14 N-cm NEMA 17 stepper motors (one for each tripod leg) and one 12V brushed DC motor (for the panning functionality). The steppers were driven using TMC 4210 motion controllers which we communicated with via SPI. The steppers were run at a voltage of 24 volts to achieve the performance level that we needed for the tripod. 


Our Custom PCB 

The PCB had a STM32F411 chip on as the main compute unit of the project. To power this and all the other peripherals and actuators required for the project, a 6s Li-Po battery was selected, the 24V was mainly for the stepper motors. The board also had a screw block connector to be able to connect to a power supply to provide power in testing environments. Because the MCU and other peripherals do not use this high of voltage this had to be regulated down to the correct voltage levels for each of the systems. The DC motor used 12v, the motor’s encoder used 5v and the mcu and other ICs used a voltage level of 3.3v. To achieve these three voltage regulators were used, one 24V to 12V, 12V to 5V and a 5V to 3.3V. All these regulators required auxiliary components, and these were added once the datasheet for each one was consulted. A reset switch and status LEDs were also added to the board to provide an easy way to reset the MCU and also an easy way to check the current status of the code running on the microcontroller. Integrated onto the board are also TMC4210 motion controllers and TMC2208 stepper drivers. The board has a motor driver as well and this takes PWM signals from the microcontroller to drive the DC motor for panning functionality. The board also includes pinouts for unused GPIO pins and also has pinouts for communications, namely I2C, SPI, and UART. There are also several Vdd and Gnd pinouts for any peripherals that need to be powered by 3.3V. 


Controllers & Other Software

An object-orientated software structure was used in the project, with classes for each of the sensors and actuators. The IMU and stepper motors were also implemented similarly, using the HAL API supplied by STM. 


The computer vision portion of the project was written using Python on the Jetson Nano. OpenCV and other Python libraries were used to take camera data and track an object of interest. The Python script also allowed for different color objects to be tracked by changing the HSV value range that was tracked by the foreground mask. Once the object was detected, a box was drawn around it and the centroid of that was found and stored for each frame. During each frame, the difference in x-coordinates between the centroid of the object and the center of the frame was calculated. This error was then used then implemented in a basic P controller which then sent the appropriate duty through UART to the microcontroller on the PCB. The values were then received by the microcontroller through an interrupt callback.
