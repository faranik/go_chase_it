# Project Description

This is a project as part of the robotics course offered by Udacity. It is about ROS and Gazebo usage for the robotics simulation environments.

## Summary of Tasks
In this project, two ROS packages are created: the drive_bot and the ball_chaser. Here are the caracteristics of the designed robot and its environment:

* drive_bot:

	* A ROS package, named *my_robot* to hold the robot, a white ball, and the world.
	* Design a differential drive robot with the Unified Robot Description Format with two sensors: a lidar and a camera. Add Gazebo plugins for the robot’s differential drive, lidar, and camera.
	* The robot is housed inside a world representing an office.
	* A white-colored ball is added to the Gazebo world.
	* The world.launch file launches the world with the white-colored ball and the robot.

* ball_chaser:

	* A ball_chaser ROS package to hold your C++ nodes.
	* A drive_bot C++ node that will provide a ball_chaser/command_robot service to drive the robot by controlling its linear x and angular z velocities.
	* A process_image C++ node that reads the robot’s camera image and analyzes it to determine the presence and position of a white ball.
	* The ball_chaser.launch should run both the drive_bot and the process_image nodes.

## Directory structure
```
    src                                # Go Chase It Project
    ├── my_robot                       # my_robot package
    │   ├── launch                     # launch folder for launch files
    │   │   ├── robot_description.launch
    │   │   ├── world.launch
    │   ├── meshes                     # meshes folder for sensors
    │   │   ├── hokuyo.dae
    │   ├── urdf                       # urdf folder for xarco files
    │   │   ├── my_robot.gazebo
    │   │   ├── my_robot.xacro
    │   ├── world                      # world folder for world files
    │   │   ├── <yourworld>.world
    │   ├── CMakeLists.txt             # compiler instructions
    │   ├── package.xml                # package info
    ├── ball_chaser                    # ball_chaser package
    │   ├── launch                     # launch folder for launch files
    │   │   ├── ball_chaser.launch
    │   ├── src                        # source folder for C++ scripts
    │   │   ├── drive_bot.cpp
    │   │   ├── process_images.cpp
    │   ├── srv                        # service folder for ROS services
    │   │   ├── DriveToTarget.srv
    │   ├── CMakeLists.txt             # compiler instructions
    │   ├── package.xml                # package info
```

## How to run it
Execute these two commands into two different terminals:
```
roslaunch my_robot world.launch
```
and 
```
roslaunch ball_chaser ball_chaser.launch
```
Off course these two command can be combined into single launch file.
