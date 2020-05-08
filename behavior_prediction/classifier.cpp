#include "classifier.h"
#include <math.h>
#include <string>
#include <vector>
#include <iostream>

using Eigen::ArrayXd;
using std::string;
using std::vector;

// Initializes GNB
GNB::GNB() {
  /**
   * TODO: Initialize GNB, if necessary. May depend on your implementation.
   */
  
  // Zero Initialize all the means, stddevs and priors 
  left_mean = ArrayXd::Zero(4);
  left_stddev = ArrayXd::Zero(4);
  left_prior = 0.0;
  
  right_mean = ArrayXd::Zero(4);
  right_stddev = ArrayXd::Zero(4);
  right_prior = 0.0;
  
  keep_mean = ArrayXd::Zero(4);
  keep_stddev = ArrayXd::Zero(4);
  keep_prior = 0.0;
  
}

GNB::~GNB() {}

void GNB::train(const vector<vector<double>> &data, 
                const vector<string> &labels) {
  /**
   * Trains the classifier with N data points and labels.
   * @param data - array of N observations
   *   - Each observation is a tuple with 4 values: s, d, s_dot and d_dot.
   *   - Example : [[3.5, 0.1, 5.9, -0.02],
   *                [8.0, -0.3, 3.0, 2.2],
   *                 ...
   *                ]
   * @param labels - array of N labels
   *   - Each label is one of "left", "keep", or "right".
   *
   * TODO: Implement the training function for your classifier.
   */
   
  // To count the number of instances of each label
  float num_left=0,num_right=0,num_keep=0;
  
  // Add up the respective features for each label to compute means
  for (int i=0; i<data.size(); ++i){
      if(labels[i]=="left"){
          ++num_left;
          left_mean += ArrayXd::Map(data[i].data(),data[i].size());
      }
      else if(labels[i]=="right"){
          ++num_right;
          right_mean += ArrayXd::Map(data[i].data(),data[i].size());
      }
      else{
          ++num_keep;
          keep_mean += ArrayXd::Map(data[i].data(),data[i].size());
      }
  }
   
  // Compute means
  left_mean /= num_left;
  right_mean /= num_right;
  keep_mean /= num_keep;
   
  // Compute the stddevs for the features for each label
  for (int i=0; i<data.size(); ++i){
      if(labels[i]=="left"){
          left_stddev += (ArrayXd::Map(data[i].data(),data[i].size()) - left_mean).square();
      }
      else if(labels[i]=="right"){
          right_stddev += (ArrayXd::Map(data[i].data(),data[i].size()) - right_mean).square();
      }
      else{
          keep_stddev += (ArrayXd::Map(data[i].data(),data[i].size()) - keep_mean).square();
      }
  }
  left_stddev = (left_stddev/num_left).sqrt();
  right_stddev = (right_stddev/num_right).sqrt();
  keep_stddev = (keep_stddev/num_keep).sqrt();
  
  // Compute priors
  float total = num_left+num_right+num_keep;
  left_prior = num_left/total;
  right_prior = num_right/total;
  keep_prior = num_keep/total;
  
}

string GNB::predict(const vector<double> &sample) {
  /**
   * Once trained, this method is called and expected to return 
   *   a predicted behavior for the given observation.
   * @param observation - a 4 tuple with s, d, s_dot, d_dot.
   *   - Example: [3.5, 0.1, 8.5, -0.2]
   * @output A label representing the best guess of the classifier. Can
   *   be one of "left", "keep" or "right".
   *
   * TODO: Complete this function to return your classifier's prediction
   */
  
  // Convert to Eigen::ArrayXd for easy manipulation
  ArrayXd x = ArrayXd::Map(sample.data(), sample.size());
  
  // Compute likelihoods of each label
  float left_likelihood=0, right_likelihood=0, keep_likelihood=0;
  
  left_likelihood = ((1/(2*M_PI*left_stddev.square()).sqrt()) * 
                        exp(-0.5*(x-left_mean).square() / left_stddev.square())).prod();
                        
  right_likelihood = ((1/(2*M_PI*right_stddev.square()).sqrt()) * 
                        exp(-0.5*(x-right_mean).square() / right_stddev.square())).prod();
                        
  keep_likelihood = ((1/(2*M_PI*keep_stddev.square()).sqrt()) * 
                        exp(-0.5*(x-keep_mean).square() / keep_stddev.square())).prod();                        
  
  
  left_likelihood *= left_prior;
  right_likelihood *= right_prior;
  keep_likelihood *= keep_prior;
  
  // Find the maximum likilihood label
  string label;
  if(left_likelihood>=right_likelihood && left_likelihood>=keep_likelihood){
      label = "left";
  }
  
  else if(keep_likelihood>=right_likelihood && keep_likelihood>=left_likelihood){
      label = "keep";
  }
  
  else if(right_likelihood>=left_likelihood && right_likelihood>=keep_likelihood){
      label = "right";
  }
  
  return label;
}