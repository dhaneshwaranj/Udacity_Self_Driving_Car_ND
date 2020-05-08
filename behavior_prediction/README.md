# behavior_prediction

This is a program to predict behavior of a car (change lane to the left or right or maintain lane) 
given its state (longitudinal position and speed, lateral position and speed).

This uses previous data and build a Naive Bayes Classifier. 

You need Eigen library to compile this. To build and run:

```
g++ -I "/path/to/eigen/Eigen" behavior_prediction.cpp classifier.cpp -o pred.o
./pred.o
```
