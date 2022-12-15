# Configuration

The `setup()` function can be used at the beginning of a script to configure the numerical behavior of ANNarchy.

## Setting the discretization step

An important value for the simulation is the discretization step `dt`.
Its default value is 1 ms, which is usually fine for rate-coded
networks, but may be too high for spiking networks, as the equations are
stiffer. Taken too high, it can lead to high numerical errors. Too low,
and the simulation will take an unnecessary amount of time.

To set the discretization step, just pass the desired value to `setup()`
at the beginning of the script, or at any rate before the call to
`compile()`:

    setup(dt=0.1)

Changing its value after calling `compile()` will not have any effect.

## Setting the seed of the random number generators

By default, the random number generators are seeded with `time(NULL)`,
so each simulation will be different. If you want to have deterministic
simulations, you simply need to provide a fixed seed to `setup()`:

    setup(seed=62756)

Note that this also sets the seed of Numpy, so you can also reproduce
random initialization values produced by `numpy.random`.

!!! note

    Using the same seed with the OpenMP and CUDA backends will not lead to the same sequences of numbers!

## Cleaning the compilation directory

When calling `compile()` for the first time, a subfolder `annarchy/`
will be created in the current directory, where the generated code will
be compiled. The first compilation may last a couple of seconds, but
further modifications to the script are much faster. If no modification
to the network has been made except for parameter values, it will not be
recompiled, sparing us this overhead.

ANNarchy tracks the changes in the script and re-generates the
corresponding code. In some cases (a new version of ANNarchy has been
installed, bugs), it may be necessary to perform a fresh compilation of
the network. You can either delete the `annarchy/` subfolder and restart
the script:

    $ rm -rf annarchy/
    $ python MyNetwork.py

or pass the `--clean` flag to Python:

    $ python MyNetwork.py --clean 

## Selecting the compiler

ANNarchy requires a C++ compiler. On GNU/Linux, the default choice is
`g++`, while on MacOS it is `clang++`. You can change the compiler (and
its flags) to use either during the call to `compile()` in your script:

    compile(compiler="clang++", compiler_flags="-march=native -O3")

or globally by modifying the configuration file located at
`~/.config/ANNarchy/annarchy.json`:

``` {.json}
{
    "openmp": {
        "compiler": "clang++",
        "flags": "-march=native -O3"
    }
}
```

Be careful with the flags: for example, the optimization level `-O3`
does not obligatorily produce faster code. But this is the case for most models, therefore
it is the default in the ANNarchy 4.7.x releases.

Even more caution is required when using the `-ffast-math` flag. It can
increase the performance, in particular in combination with SIMD. However,
the application of `-ffast-math` enables a set of optimizations which might
violate IEEE 754 compliance (which might be okay in many cases, but it is
important that the user verifies the result). For more details, see the
g++ documentation: https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html

!!! note

    In rare cases, it may occur that the CPU architecture is not detectable for the used g++ compiler (e.g. Intel's Tigerlake and g++ <= 9.4). This will result in a compiler error which can be fixed by removing the '-march=native' flag. To get access to AVX-512 SIMD instructions, you need to add `-mavx512f` instead, as well as `-ftree-vectorize` if `-O3` is not already used.

## Parallel computing with OpenMP

The default paradigm for an ANNarchy simulation is through openMP, which
distributes automatically the computations over the available CPU cores.

By default, OpenMP would use all the available cores for your
simulation, even if it is not optimal: small networks in particular tend
to run faster with a small amount of cores (for the provided example
with Neural Fields, it is for example 2). For this reason, the
`OMP_NUM_THREADS` environment variable has no effect in ANNarchy. You
can control the number of cores by passing the `-j` flag to the Python
command:

    user@machine:~$ python NeuralField.py -j2

It is the responsability of the user to find out which number of cores
is optimal for his network, by comparing simulation times. When this
optimal number is found, it can be hard-coded in the script by setting
the `num_threads` argument to `ANNarchy.setup()`:

```python
from ANNarchy import *
setup(num_threads=2)
```

## Parallel computing with CUDA

To run your network on GPUs, you need to declare to ANNarchy that you
want to use CUDA. One way to do so is to pass the `--gpu` flag to the
command line:

    user@machine:~$ python NeuralField.py --gpu

You can also set the `paradigm` argument of `ANNarchy.setup()` to make
it permanent:

```python
from ANNarchy import *
setup(paradigm="cuda")
```

If there are multiple GPUs on your machine, you can select the ID of the
device by specifying it to the `--gpu` flag on the command line:

    user@machine:~$ python NeuralField.py --gpu=2

You can also pass the `cuda_config` dictionary argument to `compile()`:

```python
compile(cuda_config={'device': 2})
```

The default GPU is defined in the configuration file
`~/.config/ANNarchy/annarchy.json` (0 unless you modify it).

``` {.json}
{
    "cuda": {
        "device": 0,
        "path": "/usr/local/cuda"
    }
}
```

!!! hint

    As the current implementation is a development version, some of the
    features provided by ANNarchy are not supported yet with CUDA:

    -   weight sharing (convolutions),
    -   non-uniform synaptic delays,
    -   structural plasticity,
    -   spiking neurons: a) with mean firing rate and b) continous
        integration of inputs,
    -   `SpikeSourceArray`.

