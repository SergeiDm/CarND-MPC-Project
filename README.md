# CarND-MPC-Project
Implementation of Model Predictive Control to drive the car around the track
## Project Description
In this project a kinematic model is applied to maneuver the vehicle around the track. Using a reference trajectory (given for example by a path planning block) and a kinematic model the project calculates actuators (steering angle and throttle) for the vehicle.

## Project files
The project includes the following folder/files:
- [src](https://github.com/SergeiDm/CarND-MPC-Project/tree/master/src) - the folder with c++ files with model predictive control (MPC) implementation.
- [CMakeLists.txt](https://github.com/SergeiDm/CarND-MPC-Project/blob/master/CMakeLists.txt) - the file for building program.
- [illustrations](https://github.com/SergeiDm/CarND-MPC-Project/tree/master/illustrations) - the folder with pictures for README.md.

## Dependencies
All dependencies can be found [here](https://github.com/udacity/CarND-MPC-Project/blob/master/README.md).
OS Windows 10 users may use [Bash on Ubuntu on Windows](https://msdn.microsoft.com/en-us/commandline/wsl/about) for dependencies installation and building program.

## Project explanation
### The Model
Student describes their model in detail. This includes the state, actuators and update equations.
The model, used in this project, can be described with the following parts:
- the state of a vehicle:

  - position x
  - position y
  - orientation psi
  - velocity v

- actuators:

  - steering angle delta - [-25, 25] degrees
  - acceleration a - [-1, 1] throttle/brake
  
 - update equations (source: http://www.udacity.com/): 

<img src="https://github.com/SergeiDm/CarND-MPC-Project/blob/master/illustrations/Model.png" width="200" height="200"/>

The model defines the next position of the vehicle, but the task is to adjust the actuators in order to minimize the difference between the prediction and the given reference trajectory. For minimizing this a cost function is used, which is a sum the elements:
- 


Timestep Length and Elapsed Duration (N & dt)
Student discusses the reasoning behind the chosen N (timestep length) and dt (elapsed duration between timesteps) values. Additionally the student details the previous values tried.

Polynomial Fitting and MPC Preprocessing
A polynomial is fitted to waypoints.
If the student preprocesses waypoints, the vehicle state, and/or actuators prior to the MPC procedure it is described.

Model Predictive Control with Latency
The student implements Model Predictive Control that handles a 100 millisecond latency. Student provides details on how they deal with latency.


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
Below is the result video of this project for the following hyperparameters (used in [MPC.cpp](https://github.com/SergeiDm/CarND-MPC-Project/blob/master/src/MPC.cpp)):
- ref_cte = 0
- ref_epsi = 0
- ref_v = 85
- w_cte_diff_ref = 35
- w_epsi_diff_ref = 500
- w_v_diff_ref = 1
- w_delta = 0
- w_acc = 0
- w_cte_diff_prev = 500
- w_delta_diff_prev = 10
- w_acc_diff_prev = 0.5

<a href="https://youtu.be/RAJG77IfK-Q" target="_blank"><img src="http://img.youtube.com/vi/RAJG77IfK-Q/0.jpg" 
alt="IMAGE ALT TEXT HERE" width="400" height="300" border="10" /></a>

The results depend on PC processor and video card, so in case of a good specification higher reference velocity can be used:
- ref_v = 100
- w_cte_diff_ref = 60
- w_epsi_diff_ref = 550
