# Smart Home System Project

This project is designed to create a smart home system using Atmega32 and embedded systems components such as sensors, an LCD, a keypad, and Bluetooth communication. The system allows users and admins to control various features, including lighting and door management.

## Main Features

- **Login System**: The system allows users to log in either as a user or as an admin.
    - **User Login**: Users can log in using a user ID and password. They can control the lighting system once logged in.
    - **Admin Login**: Admins can log in using an admin password. Admins have the ability to:
        - Add new users.
        - Control the door (open/close).
        - Control the lighting system.
  
- **Failed Login Attempts**: 
    - The system allows **three failed login attempts** for both users and admins.
    - After three failed attempts, the system **locks** and **activates a buzzer** to alert the user.
    - The system will remain in this locked state until it is reset.

## Control Mechanism

The primary control interface is Bluetooth serial communication and UART. 

- **Users**: 
    - Users can control the lighting system via:
        - **keypad & LCD**: By pressing the keypad control button.
        - **bluetooth terminal**: Using their phone or any other device with Bluetooth.

- **Admins**:
    - Admins can control:
        - **User Management**: Add new users to the system.
        - **Door Control**: Open or close the door.
        - **Lighting Control**: Control the lighting system.

## Components

- **Bluetooth Module (UART)**: Used for communication between the system and a mobile device or computer.
- **LCD Display**: Displays the system status, user login prompts, and other information.
- **Keypad**: Used for user input for login and lighting control.
- **Sensors**: Used for monitoring the environment and controlling the system.
- **Motor/Servo**: Used to control the door mechanism.
- **LEDs**: Used for lighting control with dimming functionality.
- **Buzzer**: Used to alert the user when the system is locked due to failed login attempts.

## How It Works

1. **Login**:
    - The user or admin logs in through the Bluetooth terminal using their credentials.
    - Admins have additional privileges such as adding users and controlling the door.
   
2. **User Control**:
    - Once logged in, users can control the lighting system either by pressing the keypad-control button or using the Bluetooth terminal.

3. **Admin Control**:
    - Admins can add new users and manage system functionalities (lighting, door control) through the terminal interface.

4. **Failed Login Attempts**:
    - The system allows up to **three failed login attempts**.
    - After three failed attempts, the system **locks** and the **buzzer activates** to notify the user.
    - The system will remain locked until a reset occurs.

## Setup Instructions

1. **Hardware Setup**:
    - Connect the Bluetooth module to the microcontroller.
    - Connect the LCD and keypad to the microcontroller.
    - Set up the motor/servo for door control and LEDs for lighting.
    - Ensure sensors are connected to monitor environmental data.
    - Connect the buzzer to alert when the system is locked.

2. **Software Setup**:
    - Upload the provided code ("smartHome.hex" file "debug" floder) to the microcontroller.
    - Pair the Bluetooth module with your terminal (mobile or computer).
    - Use the terminal to log in as a user or admin.

##simulation

https://drive.google.com/drive/folders/1BSXaU3nJvvAWekFE2lT64p9C5QtACedc?usp=sharing

![Image](https://github.com/user-attachments/assets/99009592-19db-490d-8406-f387fd2c37b4)


