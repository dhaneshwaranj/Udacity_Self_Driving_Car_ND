#ifndef CLASSIFIER_H
#define CLASSIFIER_H

#include <string>
#include <vector>
#include "Dense"

using Eigen::ArrayXd;
using std::string;
using std::vector;

class GNB {
 public:
  /**
   * Constructor
   */
  GNB();

  /**
   * Destructor
   */
  virtual ~GNB();

  /**
   * Train classifier
   */
  void train(const vector<vector<double>> &data, 
             const vector<string> &labels);

  /**
   * Predict with trained classifier
   */
  string predict(const vector<double> &sample);
  
  // Adding variables for means and std devs for all 
  // features. Also, variables for the prior probability 
  // for all the labels.
  private:
    ArrayXd left_mean;
    ArrayXd left_stddev;
    float left_prior;
      
    ArrayXd right_mean;
    ArrayXd right_stddev;
    float right_prior;
      
    ArrayXd keep_mean;
    ArrayXd keep_stddev;
    float keep_prior;
      
    vector<string> possible_labels = {"left","keep","right"};
};

#endif  // CLASSIFIER_H