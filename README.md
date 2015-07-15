# Motion_Controlled_Pong
Enables you to play the arcade game Pong with your smartphones motion captured.

#Overview
In this project you connect your smartphone to a NodeJS server, which host a website use to send the motion data of your smartphone
over a websocket to the server. You can then display a pong game on an other computer for example also connecting with the NodeJS-Server.
If you have an 32*32 LED-Matrix able to be driven with the rpi-led-matrix git project, you can also use the matrix to display the game.

#Installation

##Clone the Project:
**Important:** Because the project uses submodules, you have to clone it recursively, ```git clone --recursive git@github.com:XPerianer/Motion_Controlled_Pong.git```
or ```git clone --recursive https://github.com/XPerianer/Motion_Controlled_Pong.git```

##To use the NodeJS-Server: 
1. Install node on your device.
2. From the main directory, switch to the node directory:  ```cd node/```
3. Install the depencies with npm:  ```npm install```
4. Edit the IP-Configuration to your needs, example given with nano: ```nano pong_websocket.js```
5. Start the desired server, example given for the website version: ```sudo node pong_websocket.js```
6. Connect Smartphones and Displays by browsing to the IP of your device

##To use the LED-Matrix:
1. Install gpp on your device.
2. From the main directory, switch to the LED-Matrix directory: ```cd LED_matrix/```
3. Edit the IP-Configuration to your needs, example given with nano(It's a little hidden but you have to change `192.168.178.45` to your needs: ```nano pong.cpp```
4. Compile everything by using the makefile: ```make```
5. Meanwhile, startup the node server, **this has to be parrallel, for example in another terminal window**: ```../node/pong_tcpsocket.js```
6. Start the display: ```sudo ./pong.app```
7. Connect Smartphones by browsing to the IP of your Raspberry Pi

#Note of thanks
Thanks to Kushagra Agarwal for letting me use his javascript-pong code i adapted to work with this project.

Thanks to the developers of the rpi-led-matrix project on github I use in my project.
