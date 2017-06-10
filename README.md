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
- square of the difference between the cross track error (CTE) and its reference value
- square of the difference between the orientation psi and its reference value
- square of the difference between the velocity and its reference value
- square of velocity
- square of steering angle
- square of the difference between the next CTE and the current one
- square of the difference between the next velocity state and the current one
- square of the difference between the next steering angle state and the current one

### Timestep Length and Elapsed Duration
For prediction of the next state of the vehicle hyperparameter T (time horizon) should be defined as a multiplication of N (number of timesteps) and elapsed duration (dt). T should be small enough (not more than a few seconds), because the environment of the vehicle changes critically fast.

In this project, N=10, dt=0.05, so T=0.5 s. N defines the number of variables, which are used by an optimizer ([Ipopt](https://projects.coin-or.org/Ipopt) and [CppAD](https://www.coin-or.org/CppAD/) are used for non-linear optimization). 
Choosing N and dt depends on certain situation, here are some points concerning choosing N and dt:
- Increasing N and/or decreasing dt leads to growing the computational cost.
- Increasing dt decreases accuracy of the prediction and this leads to trajectory which seems like periodic function.
- Decreasing N may decrease accuracy.

### Polynomial Fitting and MPC Preprocessing
A polynomial is fitted to waypoints.
If the student preprocesses waypoints, the vehicle state, and/or actuators prior to the MPC procedure it is described.

Before using the optimizer, given waypoints (the reference trajectory) were transformed from a map coordinate system into car coordinate. Here is:
https://cdn-enterprise.discourse.org/udacity/uploads/default/original/4X/3/0/f/30f3d149c4365d9c395ed6103ecf993038b3d318.png
MPC procedure 


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
