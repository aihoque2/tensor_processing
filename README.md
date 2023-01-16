# Matrix Ops

### How to build:

to build this project please do the following in this directory:

`mkidr build && cd build`

`cmake ..`


### compiling and testing

after building, run inside `build/`:

`make`

`make test`

to ru run the local unittests




## How I would optimize more if I had more time

### Multi-threaded transpose()
the current function call of transpose() could save a lot of time by becoming a multithreaded function