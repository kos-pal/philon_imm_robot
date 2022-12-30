Cartesian Robot for Injection Molding Machines




https://user-images.githubusercontent.com/103308852/210091041-ee0badd0-2c9d-4444-b48f-976184723d4a.mp4




This is a 3 axis robot for Euromap 12 compatible injection molding machines.<br/><br/>
It consists of a Raspberry Pi running a Python script that acts as the master to the system and individual Arduino Nanos that handle specific operations. There are currently 3 Arduino modules (out of 6 supported by the hardware) providing the following functionalities:<br/><br/>
A) Interfacing between the robot and the injection molding machine.<br/>
B) Operating the servo motors driving the robot.<br/>
C) Handling the attachment at the end of the robotic arm (either a gripper or a suction cup).<br/><br/>

The robot uses 36V, 180W, 3000RPM integrated servo motors coupled with gearboxes to move the 3 axes. The Z (vertical) axis servo motor also comes with an integrated brake. The Y and Z gearboxes use a 10:1 reduction, and the X gearbox uses 20:1. The 3 axes are belt driven and each rotation of the gearbox results in 200mm movement. This works out to 1m/s movement speed for Y and Z axes , and 0.5m/s speed for the X axis. The servos are set up for 100 pulses per revolution, so the move resolution is  0.1mm for the X axis and 0.2mm for the 2 others. Axes lengths on this specific robot are: X 1100mm , Y 300mm , Z 900mm. <br/><br/>


The robot uses RS-485 for UART communication between the Raspberry and the Arduinos, aswell as signaling lines allowing the Arduinos to request permition to talk over the bus without polling from the Raspberry. A custom protocol is used for the messages exchanged, according to the com_protocol.pdf file. <br/><br/>

In order to interact with the robot the user has to connect to the Raspberry Pi through a VNC viewer, either with a computer in the network or with a smartphone. The Python script provides a User Interface that allows the user to manually control the robot and program an automatic sequence that will run in conjuction with the injection molding machine.



![ui](https://user-images.githubusercontent.com/103308852/207932978-0d07eb8d-04f7-4d12-91de-9ff63a304d39.PNG)



The robot is currently being used as a sprue picker on an injection molding machine, with further functionalities such as data logging being developed.



![robot_on_imm](https://user-images.githubusercontent.com/103308852/208426568-cf705c8c-a273-4379-b24e-f85fd6920383.jpg)

