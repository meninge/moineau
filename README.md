# moineau
Reference program to check neural network outputs

## Compilation

* `make frames` to generate the `frames.c` file from MNIST data
* `make parse NEURONS=x` to generate the `net.c` file in `moineau/src`,
`x` must be `100` or `200` (`100` by default) to select the number of
neurons of the first layer
* `make NEURONS=x`, `x` must be the same as the first `make parse` command
(`100` by default)
* `./moineau` to execute
