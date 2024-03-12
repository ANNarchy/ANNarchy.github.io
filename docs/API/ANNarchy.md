# Top-level methods

These methods are directly available in the main namespace when importing ANNarchy:

```python
from ANNarchy import *
```

Note that numpy is automatically imported as:

```python
import numpy as np
```

## Configuration and compilation

Contrary to other simulators, ANNarchy is entirely based on code generation. It provides a set of first-level functions to ensure the network is correctly created. It is **important** to call these functions in the right order.

::: ANNarchy.setup
    options:
      heading_level: 3

::: ANNarchy.compile
    options:
      heading_level: 3

::: ANNarchy.clear
    options:
      heading_level: 3

## Simulation

Different methods are available to run the simulation:

::: ANNarchy.simulate
    options:
      heading_level: 3

::: ANNarchy.simulate_until
    options:
      heading_level: 3

::: ANNarchy.step
    options:
      heading_level: 3

::: ANNarchy.every
    options:
      heading_level: 3

::: ANNarchy.enable_callbacks
    options:
      heading_level: 3

::: ANNarchy.disable_callbacks
    options:
      heading_level: 3

::: ANNarchy.clear_all_callbacks
    options:
      heading_level: 3

## Reset the network

If you want to run multiple experiments with the same network, or if your experiment setup requires a pre-learning phase, you can reset selectively neural or synaptic variables to their initial values.

::: ANNarchy.reset
    options:
      heading_level: 3

## Access to populations

::: ANNarchy.get_population
    options:
      heading_level: 3

::: ANNarchy.get_projection
    options:
      heading_level: 3

## Functions

::: ANNarchy.add_function
    options:
      heading_level: 3

::: ANNarchy.functions
    options:
      heading_level: 3

## Constants

::: ANNarchy.Constant
    options:
      heading_level: 3
      members:
          - __init__
          - set

## Learning

::: ANNarchy.enable_learning
    options:
      heading_level: 3


::: ANNarchy.disable_learning
    options:
      heading_level: 3

## Access to simulation times


::: ANNarchy.get_time
    options:
      heading_level: 3

::: ANNarchy.set_time
    options:
      heading_level: 3


::: ANNarchy.get_current_step
    options:
      heading_level: 3

::: ANNarchy.set_current_step
    options:
      heading_level: 3

::: ANNarchy.dt
    options:
      heading_level: 3

