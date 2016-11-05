# Description

A Discrete Dynamic System Simmulation library. Based on the principles of Simulink. Operations blocks are created and stored in a pointer vector stored a simulation object. Inputs and Outputs of each block are knitted together using shared_pointers. Each block can consist of multiple sub-blocks knitted together and different operations, such as: multiplications, division, addition, subtraction, integration and saturation. The execution of each block is performed in the order they are stored in the vector.

Complex components such as pumps and engines or stored as sub-systems.

# Dependancies
* [Eigen3](http://eigen.tuxfamily.org/index.php?title=Main_Page) for Matrix piecewise calculations
* [Boost](http://www.boost.org/) for the use of shared pointers
* [qcustomplot](http://www.qcustomplot.com/) for graphs. a MTI fork can be found at [qcustomplot](http://mti.isa-geek.com/peer23peer/qcustomplot)

# Wishlist
* Build a graphical user interface [Qdissim](http://mti.isa-geek.com/AOD/Qdissim)
* Execute blocks in parallel (where possible)
* Determine order of execution for each block automatically
* Investigate CUDA execution of blocks
