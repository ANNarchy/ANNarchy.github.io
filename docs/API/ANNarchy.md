# Top-level methods

These methods are directly available in the main namespace when importing ANNarhcy:

```python
from ANNarchy import *
```

Note that numpy is automatically imported as:

```python
import numpy as np
```

## Configuration and compilation

Contrary to other simulators, ANNarchy is entirely based on code
generation. It provides a set of first level functions to ensure the
network is correctly created. It is **important** to call these
functions in the right order.

::: ANNarchy.setup
    selection:
      docstring_style: restructured-text
    rendering:
      show_root_heading: true
      show_root_full_path: false
      heading_level: 3


::: ANNarchy.compile
    selection:
      docstring_style: restructured-text
    rendering:
      show_root_heading: true
      show_root_full_path: false
      heading_level: 3

::: ANNarchy.clear
    selection:
      docstring_style: restructured-text
    rendering:
      show_root_heading: true
      show_root_full_path: false
      heading_level: 3

## Simulation

Different methods are available to run the simulation:

::: ANNarchy.simulate
    selection:
      docstring_style: restructured-text
    rendering:
      show_root_heading: true
      show_root_full_path: false
      heading_level: 3

::: ANNarchy.simulate_until
    selection:
      docstring_style: restructured-text
    rendering:
      show_root_heading: true
      show_root_full_path: false
      heading_level: 3

::: ANNarchy.step
    selection:
      docstring_style: restructured-text
    rendering:
      show_root_heading: true
      show_root_full_path: false
      heading_level: 3

::: ANNarchy.every
    selection:
      docstring_style: restructured-text
    rendering:
      show_root_heading: true
      show_root_full_path: false
      heading_level: 3

::: ANNarchy.enable_callbacks
    selection:
      docstring_style: restructured-text
    rendering:
      show_root_heading: true
      show_root_full_path: false
      heading_level: 3

::: ANNarchy.disable_callbacks
    selection:
      docstring_style: restructured-text
    rendering:
      show_root_heading: true
      show_root_full_path: false
      heading_level: 3

::: ANNarchy.clear_all_callbacks
    selection:
      docstring_style: restructured-text
    rendering:
      show_root_heading: true
      show_root_full_path: false
      heading_level: 3

## Reset the network

If you want to run multiple experiments with the same network, or if
your experiment setup requires a pre learning phase, you can reset
selectively neural or synaptic variables to their initial values.

::: ANNarchy.reset
    selection:
      docstring_style: restructured-text
    rendering:
      show_root_heading: true
      show_root_full_path: false
      heading_level: 3

## Access to populations

::: ANNarchy.get_population
    selection:
      docstring_style: restructured-text
    rendering:
      show_root_heading: true
      show_root_full_path: false
      heading_level: 3

::: ANNarchy.get_projection
    selection:
      docstring_style: restructured-text
    rendering:
      show_root_heading: true
      show_root_full_path: false
      heading_level: 3

## Functions

::: ANNarchy.add_function
    selection:
      docstring_style: restructured-text
    rendering:
      show_root_heading: true
      show_root_full_path: false
      heading_level: 3

::: ANNarchy.functions
    selection:
      docstring_style: restructured-text
    rendering:
      show_root_heading: true
      show_root_full_path: false
      heading_level: 3

## Constants

::: ANNarchy.Constant
    selection:
      docstring_style: restructured-text
    rendering:
      show_root_heading: true
      show_root_full_path: false
      heading_level: 3

## Learning

::: ANNarchy.enable_learning
    selection:
      docstring_style: restructured-text
    rendering:
      show_root_heading: true
      show_root_full_path: false
      heading_level: 3


::: ANNarchy.disable_learning
    selection:
      docstring_style: restructured-text
    rendering:
      show_root_heading: true
      show_root_full_path: false
      heading_level: 3

## Access to simulation times


::: ANNarchy.get_time
    selection:
      docstring_style: restructured-text
    rendering:
      show_root_heading: true
      show_root_full_path: false
      heading_level: 3

::: ANNarchy.set_time
    selection:
      docstring_style: restructured-text
    rendering:
      show_root_heading: true
      show_root_full_path: false
      heading_level: 3


::: ANNarchy.get_current_step
    selection:
      docstring_style: restructured-text
    rendering:
      show_root_heading: true
      show_root_full_path: false
      heading_level: 3

::: ANNarchy.set_current_step
    selection:
      docstring_style: restructured-text
    rendering:
      show_root_heading: true
      show_root_full_path: false
      heading_level: 3

::: ANNarchy.dt
    selection:
      docstring_style: restructured-text
    rendering:
      show_root_heading: true
      show_root_full_path: false
      heading_level: 3

