# pedestrian_tracking_laser

NOTE: You need the Eigen library to run this example!!!

This folder has the data and code for tracking a pedestrian using synthetc data collected from a laser. 
The data file has both laser and radar data but this ignores the radar data.

The tracking class uses a multi-dimensional Kalman Filter to track the pedestrian. 

g++ -I path\to\eigen\Eigen main.cpp kalman_filter.cpp tracking.cpp -o my_filter
