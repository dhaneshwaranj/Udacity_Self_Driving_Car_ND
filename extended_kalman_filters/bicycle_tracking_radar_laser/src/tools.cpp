#include "tools.h"
#include <iostream>

using Eigen::VectorXd;
using Eigen::MatrixXd;
using std::vector;

Tools::Tools() {}

Tools::~Tools() {}

VectorXd Tools::CalculateRMSE(const vector<VectorXd> &estimations,
                              const vector<VectorXd> &ground_truth) {
  /**
   * TODO: Calculate the RMSE here.
   */
  VectorXd rmse(4);
  rmse << 0,0,0,0;

  // check the validity of the following inputs:
  //  * the estimation vector size should not be zero
  //  * the estimation vector size should equal ground truth vector size
  if(estimations.size()==0 || estimations.size()!=ground_truth.size()){
      std::cout<<"Dimension mismatch between ground truth and the estimates\n";
      return rmse;
  }

  // accumulate squared residuals
  for (int i=0; i < estimations.size(); ++i) {
    VectorXd residue = estimations[i] - ground_truth[i];
    residue = residue.array().square();
    
    rmse += residue; 
  }

  // calculate the mean
  rmse = rmse/estimations.size();

  // calculate the square root
  rmse = rmse.array().sqrt();

  // return the result
  return rmse;
}

MatrixXd Tools::CalculateJacobian(const VectorXd& x_state) {
  /**
   * TODO:
   * Calculate a Jacobian here.
   */
  
  MatrixXd Hj(3,4);
  
  // recover state parameters
  float px = x_state(0);
  float py = x_state(1);
  float vx = x_state(2);
  float vy = x_state(3);
  
  float dist_2 = px*px + py*py;
  float dist = sqrt(dist_2);
  float dist_3 = pow(dist,3);
  
  // check division by zero
  if(dist==0){
    std::cout<<"Division by zero in Jacobian matrix calculation\n"; 
    return Hj;
  }
  
  // compute the Jacobian matrix
  Hj << px/dist, py/dist, 0, 0,
        -py/dist_2, px/dist_2, 0, 0,
        py*(vx*py-vy*px)/dist_3, px*(vy*px-vx*py)/dist_3, px/dist, py/dist;
        
  return Hj;
}
