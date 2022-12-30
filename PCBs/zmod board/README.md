![zmod_board](https://user-images.githubusercontent.com/103308852/208645880-7c158b78-f799-4b2e-a300-6ff5e76d431d.jpg)


This board connects to the Arduino nano that handles the gripper at the end of the Z axis. The board implements RS-485 for the UART communication between the
modules with a SN75176B ic, 3 relay channels for outputing signals to the Gripper, 3 optocoupler inputs for feedback and a mosfet for controlling the brake of the Z axis servo.
