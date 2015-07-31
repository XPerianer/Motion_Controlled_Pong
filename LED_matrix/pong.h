//Motion_Controlled_Pong to play Pong with your Smartphone and a Raspberry Pi.
//Copyright (C) 2015  Dominik Meier (XPerianer) <hiscore.pressthebutton@hotmail.de>

//This program is free software: you can redistribute it and/or modify
//the Free Software Foundation, either version 3 of the License, or
//it under the terms of the GNU General Public License as published by
//(at your option) any later version.

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

//You should have received a copy of the GNU General Public License
//along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "game.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <thread>

#include <chrono>

//Used for Socket communication
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define PORT "1337" // the port client will be connecting to
#define MAXDATASIZE 100 // max number of bytes we can get at once
