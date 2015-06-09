IN-HAND OBJECT LEARNING AND RECOGNITION USING 2D AND 3D INFORMATION
=====

Bachelor's Thesis

Author: 
   [Irene Sanz Nieto](https://github.com/irenesanznieto)
   
Branch: 
    hydro-devel
   
Index
-------

1.Introduction

2.Compile and run

   2.1. Dependencies
   
   2.2. Compiling
   
   2.3  Running
   
3. Doxygen documentation

4. More info



1. Introduction
--------------------
This repository contains the software developed for a Bachelor's Thesis. It is an in-hand object training and recognition using 3D and 2D features. 

The hardware used is a RGB-D camera, in this case a Kinect360 and a laptop running ubuntu 13.04. 

This project uses the Groovy distro of the Robotic Operating System (ROS). 

2. Compile and run
---------------------

2.1. Dependencies
The aditional ROS packages needed are the following: 
openni_launch
openni_tracker


Another ROS package also used is the pi_tracker (http://wiki.ros.org/pi_tracker), but it is compiled within the project since the code is slightly modified for compatibility. 

2.2 Compiling

2.2.1. Using the terminal

Open a terminal (Ctrl + Alt + t)
Enter the command : rosmake ocular

This command will build the whole project
The compilation is done using Rosbuild. 
 

2.2.1. Using QtCreator

To open the software as a QtCreator project, the only thing needed is to open the main CMakeLists.txt (sandbox/ocular/CMakeLists.txt) with QtCreator. This will parse the whole project. Afterwards, press the "build" icon to build the project.


2.3 Running

The code may be runned more easily through a launch file. In order to do so, 
enter the following command in a terminal: 

roslaunch ocular ocular.launch

This launch file will open all the executables and nodes and nodelets needed for the project. 

3. Doxygen documentation
-------------------------
 /todo
4. More info
---------------------------
/todo
