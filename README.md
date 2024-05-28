# 3*1 modes ATmega32

This project is developed for embedded systems using the ATMEGA32 microcontroller. The project has features three main modes: Calculator, Timer, and Stopwatch. Additionally, it utilizes a keypad for numeric inputs and push buttons to switch between modes.



**Features**

•	Operational modes
1.	Calculator Mode: Allows users to perform basic arithmetic calculations with two numbers and various operators (+, -, /, *, =). Inputs are obtained through a keypad, and the LCD displays the numbers, operator, and the result.
2.	Timer Mode: Enables users to set a countdown timer using the keypad. The timer starts when the 'D' button is pressed and triggers a led when it reaches zero. The LCD displays the timer in the format "MM:SS."
3.	Stopwatch Mode: Provides a stopwatch functionality with start, pause, and reset buttons. The stopwatch increments and displays the time in "HH:MM:SS" format on the LCD.






**Hardware**


•	ATMEGA32 microcontroller

•	Keypad

•	LCD 

•	Push buttons






**Operations Instructions**

1-	Calculator Mode

o	Enter two numbers using the keypad.

o	Select an operator (+, -, /, *, =) using the keypad buttons **on hardware** (A, B, C, D, *).

o	The LCD will display the numbers, operator, and the result.

2-	Timer Mode

o	Initially, "00:00" is displayed on the LCD.

o	Enter minutes and seconds using the keypad.

o	Press the '=' button to start the countdown for the timer.

o	When the timer reaches zero, a LED will be triggered.

3- Stopwatch Mode

o	Initially, "00:00:00" is displayed on the LCD.

o	Use the Interrupt buttons to start, pause,or reset the stopwatch.





