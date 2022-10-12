# Distance-Measurement-System
## Aim
Implement a system to measure the distance with Ultrasonic sensor `HC-SR04` using ***`ATmega32`*** microcontroller, 
Use ATmega32 Microcontroller with frequency 8Mhz.

![This is an image](Project%20SnapShots/Protues_Circuit.png)

## Description

1. Measure the distance using the Ultrasonic sensor HC-SR04. Check the `HC-SR04 Ultrasonic Tutorial` pdf file to understand how to interface with this 
sensor.

2. The LCD should display the distance value like that:

![This is an image](Project%20SnapShots/LCD.png)

3. The project should be design and implemented based on the layered architecture model as follow:

| Software Layered Model       | Driver Name |
| :---                         |     :---:  | 
| Application Layer (APP)               | Application.c       | 
| Hardware Abstraction Layer (HAL)     | LCD  / ULTRASONIC | 
| MicroController Abstraction Layer (MCAL)     | GPIO / ICU    | 

4. Once the calculations are done by the microcontroller according to the logic, the temperature is displayed on the LCD. 

## UltraSonic (HC-SR04)

# Programming
1. ATmega32 microcontroller needs to transmit ***at least 10*** us trigger pulse to the HC-SR04 Trigger Pin.
2. After getting a trigger pulse, HC-SR04 automatically sends eight 40 kHz sound waves and the microcontroller waits for rising edge output at the Echo pin.
3. When the rising edge capture occurs at the Echo pin which is connected to an input of ATmega32, 
Start Timer of ATmega32 and again wait for a falling edge on the Echo pin.
4. As soon as the falling edge is captured at the Echo pin, the microcontroller reads the count of the Timer. 
This time count is used to calculate the distance to an object.

        Note: Here we are using the Input Capture unit on PD6(ICP1) pin.
# Distance Calculations
Calculation (distance in cm)

     - Sound velocity = 340.00 m/s = 34000 cm/s
     - As Signal travels from HCSR04 to object and returns to the module HCSR04
       The distance of Object (in cm) = (340000 * Time)/2
                                      = 17000 * Time

	   - As an internal 8MHz oscillator frequency is selected for ATmega32, with Prescaler F_CPU/8 for timer frequency.
	     Then F(timer) = FCPU/8 = 1 MHZ ---> T(timer) = 1us.

	   - Distance = 17000 x (TIMER value) x 1 x 10^-6 cm
                = 0.017 x (TIMER value) cm

	   Note TIMER VALUE is the pulse width time calculated by the ICU
     
## Deployment

To deploy this project 

Install the Following Software:

- [Protues Simulator](https://ettron.com/proteus-8-14-download-free-with-arduino-libraries-latest-version/).
- [Eclipse IDE](https://www.eclipse.org/downloads/packages/)

## 🔗 Personal Links

[![linkedin](https://img.shields.io/badge/linkedin-0A66C2?style=for-the-badge&logo=linkedin&logoColor=white)](https://www.linkedin.com/in/mostafa-mahmoud23/)
