# Random Distributions

## Introduction

Random number generators can be used at several places:

-   while initializing parameters or variables,
-   while creating connection patterns,
-   when injecting noise into a neural or synaptic variable.

ANNarchy provides several random distribution objects, implementing the
following distributions:

-   Uniform
-   DiscreteUniform
-   Normal
-   LogNormal
-   Gamma
-   Exponential

!!! warning

    DiscreteUniform, Gamma and Exponential distributions are not available if the CUDA paradigm is used.


They can be used in the Python code, as a normal object:

```python
dist = Uniform(-1.0, 1.0)
values = dist.get_values(100)
```

or inside mathematical expressions:

```python
tau * dv/dt + v = g_exc + Normal(0.0, 20.0)
``````

The Python objects rely on the `numpy.random` library, while the C++ values are based on the standard library of C++11.

The seed of the underlying random number generator (Mersenne twister, mt19937 in C++11) can be set globally, by defining its value in `setup()`:

```python
setup(seed=187348768237)
```

All random distribution objects (Python or C++) will use this seed. By
default, the global seed is taken to be `time(NULL)`.

The seed can also be set individually for each RandomDistribution object
as a last argument:

```python
dist = Uniform(-1.0, 1.0, 36875937346)
```

as well as in a mathematical expression:

```python
tau * dv/dt + v = g_exc + Normal(0.0, 20.0, 497536526)
```

## Implementation details

ANNarchy uses default implementations for random number generation: STL methods of C++11 for OpenMP and the device API of the curand library for CUDA.

As engines, we use mt19937 on openMP side and XORWOW on CUDA. The latter is subject to changes in future releases.

It may be important to know that the drawing mechanisms differ between openMP and CUDA slightly:

-   openMP: all distribution objects draw the numbers from one source in a single thread.
-   CUDA: each distribution object has its own source, the random numbers are drawn in a parallel way.

For further details on random numbers on GPUs please refer to the curand documentation:

<http://docs.nvidia.com/cuda/curand/device-api-overview.html#device-api-overview>

::: ANNarchy.core.Random.Uniform
    options:
      heading_level: 2
      members:
        - __init__
        - get_values

::: ANNarchy.core.Random.DiscreteUniform
    options:
      heading_level: 2
      members:
        - __init__
        - get_values


::: ANNarchy.core.Random.Normal
    options:
      heading_level: 2
      members:
        - __init__
        - get_values


::: ANNarchy.core.Random.LogNormal
    options:
      heading_level: 2
      members:
        - __init__
        - get_values


::: ANNarchy.core.Random.Gamma
    options:
      heading_level: 2
      members:
        - __init__
        - get_values

::: ANNarchy.core.Random.Exponential
    options:
      heading_level: 2
      members:
        - __init__
        - get_values

