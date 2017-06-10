#ifndef MPC_H
#define MPC_H

#include <vector>
#include "Eigen-3.3/Eigen/Core"

using namespace std;

// Structure for recording solver results
struct Result {
 public:
  double angle;
  double throttle;
  vector<double> px;
  vector<double> py;
};

class MPC {
 public:
  
  // Constructor
  MPC();

  // Destructor
  virtual ~MPC();

  // Solve the model given an initial state and polynomial coefficients.
  // Return the first actuatotions.
  Result Solve(Eigen::VectorXd state, Eigen::VectorXd coeffs);
};

#endif /* MPC_H */
