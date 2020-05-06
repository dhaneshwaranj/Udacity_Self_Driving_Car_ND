// This program computes the Jacobian of the measurement function
// of a Radar measuring the range,bearing, and velocity of a 
// pedestrian in 2D.

#include <iostream>
#include <vector>
#include "Dense"

using Eigen::MatrixXd;
using Eigen::VectorXd;
using std::cout;
using std::endl;

MatrixXd CalculateJacobian(const VectorXd& x_state);

int main() {
  /**
   * Compute the Jacobian Matrix
   */

  // predicted state example
  // px = 1, py = 2, vx = 0.2, vy = 0.4
  VectorXd x_predicted(4);
  x_predicted << 1, 2, 0.2, 0.4;

  MatrixXd Hj = CalculateJacobian(x_predicted);

  cout << "Hj:" << endl << Hj << endl;

  return 0;
}

MatrixXd CalculateJacobian(const VectorXd& x_state) {

  MatrixXd Hj(3,4);
  // recover state parameters
  float px = x_state(0);
  float py = x_state(1);
  float vx = x_state(2);
  float vy = x_state(3);

  // TODO: YOUR CODE HERE 
  
  float dist_2 = px*px + py*py;
  float dist = sqrt(dist_2);
  
  // check division by zero
  if(dist==0){
      return Hj;
  }
  
  // compute the Jacobian matrix
  Hj << px/dist, py/dist, 0, 0,
        -py/dist_2, px/dist_2, 0, 0,
        py*(vx*py-vy*px)/pow(dist,3), px*(vy*px-vx*py)/pow(dist,3), px/dist, py/dist;
        
  return Hj;
}