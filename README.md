# CarND-MPC-Project
Implementation of Model Predictive Control to drive the car around the track
## Project Description
In this project a kinematic model is applied to maneuver the vehicle around the track. Using a reference trajectory (for example by a path planning block) and the following kinematic model (source: http://www.udacity.com/):

<img src="https://github.com/SergeiDm/CarND-MPC-Project/blob/master/illustrations/Model.png" width="400" height="300"/>

the project calculates actuators (steering angle and throttle) for the vehicle.

## Project files
The project includes the following folder/files:
- [src](https://github.com/SergeiDm/CarND-MPC-Project/tree/master/src) - the folder with c++ files with model predictive control (MPC) implementation.
- CMakeLists.txt - the file for building program.
- illustrations - the folder with pictures for README.md.

## Dependencies
For communication between the car simulator and the project, [uWebSockets](https://github.com/uWebSockets/uWebSockets/blob/master/README.md) should be installed and in lines of [CMakeLists.txt](https://github.com/SergeiDm/CarND-PID-Controller/blob/master/CMakeLists.txt):

`if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")`

`include_directories("pathtovckpg/vcpkg/installed/x86-windows/include/uWS")`

`endif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")`

"pathtovckpg" should be changed into corresponding path (for OS Windows).


## Project explanation
In this project 2 PID controllers were applied:
- for steering angle. This PID is directly proprotional:

  - CTE
  - CTE change rate
  - Sum (integral) of CTE over time

It means the more CTE, the more steering angle.

- for speed (velocity). The PID is inversely proportional absolute values of the same things mentioned in previous PID. So, the more CTE, the less velocity. This is because a big value of CTE means increasing steering angle, so for staying on the track the velocity should be decreased.



P component creates periodic fluctuations, D component decreases them. At the same time I component is used for overcoming biases (for example a steering wheel has inappropriate adjustment).

In this project, manual series tuning was used for finding appropriate hyperparameters for PID components. Firstly for P component, after   testing that steering angle values were anough for keeping the vehicle on the track, hyperparameter for D was tuned in order to decrease periodic fluctuations. Finally, hyperparameter for I component was chosen according to making better staying the vehicle on the track. The final hyperparameters values are 0.06, 0.05, 0.06.

Hyperparameters for PID controller for speed were chosen according to the results how fast the vehicle can move on the track.
The final values are 0.4, 0, 0.1.

## Project result
Here is the result video of this project:

<a href="https://youtu.be/2VPTpG9AUoQ" target="_blank"><img src="http://img.youtube.com/vi/2VPTpG9AUoQ/0.jpg" 
alt="IMAGE ALT TEXT HERE" width="400" height="300" border="10" /></a>
