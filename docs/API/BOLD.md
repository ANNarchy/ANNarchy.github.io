# BOLD monitoring

BOLD monitoring utilities are provided in the module `ANNarchy.extensions.bold`, which must be explicitly imported:

```python
from ANNarchy import *
from ANNarchy.extensions.bold import BoldMonitor
```

::: ANNarchy.extensions.bold.BoldMonitor
    options:
      heading_level: 2

## BOLD models

The provided BOLD models follow the Balloon model (Buxton et al., 1998) with the different variations studied in (Stephan et al., 2007). Those models all compute the vascular response to neural activity through a dampened oscillator:

$$
    \frac{ds}{dt} = \phi \, I_\text{CBF} - \kappa \, s - \gamma \, (f_{in} - 1)
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

This makes a total of four different BOLD model (RN, RL, CN, CL) which are provided by the extension. The different parameters can be modified in the constructor. Additionally, we also provide the model that was used in (Maith et al., 2021) and the two-inputs model of (Maith et al, 2022).


::: ANNarchy.extensions.bold.BoldModel
    options:
      heading_level: 3

::: ANNarchy.extensions.bold.balloon_RN
    options:
      heading_level: 3

::: ANNarchy.extensions.bold.balloon_RL
    options:
      heading_level: 3

::: ANNarchy.extensions.bold.balloon_CL
    options:
      heading_level: 3

::: ANNarchy.extensions.bold.balloon_CN
    options:
      heading_level: 3

::: ANNarchy.extensions.bold.balloon_maith2021
    options:
      heading_level: 3

::: ANNarchy.extensions.bold.balloon_two_inputs
    options:
      heading_level: 3

## References

> Buxton, R. B., Wong, E. C., and Frank, L. R. (1998). Dynamics of blood flow and oxygenation changes during brain activation: the balloon model. Magnetic resonance in medicine 39, 855–864. doi:10.1002/mrm.1910390602

> Friston et al. (2000). Nonlinear responses in fMRI: the balloon model, volterra kernels, and other hemodynamics. NeuroImage 12, 466–477

> Buxton et al. (2004). Modeling the hemodynamic response to brain activation. Neuroimage 23, S220–S233. doi:10.1016/j.neuroimage.2004.07.013

> Stephan et al. (2007). Comparing hemodynamic models with DCM. Neuroimage 38, 387–401. doi:10.1016/j.neuroimage.2007.07.040

> Maith et al. (2021) A computational model-based analysis of basal ganglia pathway changes in Parkinson’s disease inferred from resting-state fMRI. European Journal of Neuroscience. 2021; 53: 2278– 2295. doi:10.1111/ejn.14868 

> Maith et al. (2022) BOLD monitoring in the neural simulator ANNarchy. Frontiers in Neuroinformatics 16. doi:10.3389/fninf.2022.790966.
