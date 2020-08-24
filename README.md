# Localized Robotic Guidance System

The localized robotic guidance system uses a single Pixy-Camera for object sensing and 3 quadrature encoders to perform odometry. The robot is accurate to + - 0.05 meters.

The main algorithm that keeps track of and performs movements can be found in:

main/src/tracking.cpp
main/src/vision.cpp

