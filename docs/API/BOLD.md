# BOLD monitoring

BOLD monitoring utilities are provided in the module `ANNarchy.extensions.bold`, which must be explicitely imported:

```python
from ANNarchy import *
from ANNarchy.extensions.bold import BoldMonitor
```

::: ANNarchy.extensions.bold.BoldMonitor
    selection:
      docstring_style: restructured-text
    rendering:
      show_root_heading: true
      show_root_full_path: false
      heading_level: 2

## BOLD models

The provided BOLD models follow the Balloon model (Buxton et al., 1998) with the different variations studied in (Stephan et al., 2007). Those models all compute the vascular response to neural activity through a dampened oscillator:

$$
    \frac{ds}{dt} = \phi \, I - \kappa \, s - \gamma \, (f_{in} - 1)
$$

$$
    \frac{df_{in}}{dt} = s
$$

This allows to compute the oxygen extraction fraction:

$$
    E = 1 - (1 - E_{0})^{ \frac{1}{f_{in}} }
$$

The (normalized) venous blood volume is computed as:

$$
    \tau_0 \, \frac{dv}{dt} = (f_{in} - f_{out})
$$

$$
    f_{out} = v^{\frac{1}{\alpha}}
$$

The level of deoxyhemoglobin into the venous compartment is computed by:

$$
    \tau_0 \, \frac{dq}{dt} = f_{in} \, \frac{E}{E_0} - \frac{q}{v} \, f_{out}
$$

Using the two signals $v$ and $q$, there are two ways to compute the corresponding BOLD signal:

* **N:** Non-linear BOLD equation:

$$
    BOLD = v_0 \, ( k_1 \, (1-q) + k_2 \, (1- \dfrac{q}{v}) + k_3 \, (1 - v) )
$$

* **L:** Linear BOLD equation:

$$
    BOLD = v_0 \, ((k_1 + k_2) \, (1 - q) + (k_3 - k_2) \, (1 - v)) 
$$

Additionally, the three coefficients $k_1$, $k_2$, $k_3$ can be computed in two different ways:

* **C:** classical coefficients from (Buxton et al., 1998):

$$k_1            = (1 - v_0) \, 4.3 \, v_0 \, E_0 \, \text{TE}$$

$$k_2            = 2 \, E_0$$

$$k_3            = 1 - \epsilon$$

* **R:** revised coefficients from (Obata et al., 2004):

$$k_1            = 4.3 \, v_0 \, E_0 \, \text{TE}$$

$$k_2            = \epsilon \, r_0 \, E_0 \, \text{TE}$$

$$k_3            = 1 - \epsilon$$

This makes a total of four different BOLD model (RN, RL, CN, CL) which are provided by the extension. The different parameters can be modified in the constructor. Additionally, we also provide the model that was used in (Maith et al., 2021) and the two-inputs model of (Buxton et al., 2004).


::: ANNarchy.extensions.bold.BoldModel
    selection:
      docstring_style: restructured-text
    rendering:
      show_root_heading: true
      show_root_full_path: false
      heading_level: 3

::: ANNarchy.extensions.bold.balloon_RN
    selection:
      docstring_style: restructured-text
    rendering:
      show_root_heading: true
      show_root_full_path: false
      heading_level: 3

::: ANNarchy.extensions.bold.balloon_RL
    selection:
      docstring_style: restructured-text
    rendering:
      show_root_heading: true
      show_root_full_path: false
      heading_level: 3

::: ANNarchy.extensions.bold.balloon_CL
    selection:
      docstring_style: restructured-text
    rendering:
      show_root_heading: true
      show_root_full_path: false
      heading_level: 3

::: ANNarchy.extensions.bold.balloon_CN
    selection:
      docstring_style: restructured-text
    rendering:
      show_root_heading: true
      show_root_full_path: false
      heading_level: 3

::: ANNarchy.extensions.bold.balloon_maith2021
    selection:
      docstring_style: restructured-text
    rendering:
      show_root_heading: true
      show_root_full_path: false
      heading_level: 3

::: ANNarchy.extensions.bold.balloon_two_inputs
    selection:
      docstring_style: restructured-text
    rendering:
      show_root_heading: true
      show_root_full_path: false
      heading_level: 3

