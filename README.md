# moineau
`moineau` can be executed locally to help the developper compare the
results from its IP and the `moineau` results, at every state of the
program. The two implementation are behaving the same way.

## How to

Respect the following steps to compile and launch `moineau`:
* `make frames` to generate the `frames.c` file from MNIST data
* `make parse NEURONS=x` to generate the `net.c` file in `moineau/src`,
`x` must be `100` or `200` (`100` by default) to select the number of
neurons of the first layer
* `make NEURONS=x`, `x` must be the same as the first `make parse` command
(`100` by default)
* `./moineau` to execute

You can also generate less than the 1000 frames and use another MNIST data
file. Check in `extra/frames.py` for options.
