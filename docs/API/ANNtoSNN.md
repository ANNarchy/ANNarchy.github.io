# ANN-to-SNN conversion

The ANN-to-SNN conversion module is part of the extensions and must be explicitely imported:

```python
from ANNarchy import *
from ANNarchy.extensions.ann_to_snn_conversion import ANNtoSNNConverter
```

## Background

The implementation of the present module is inspired by the SNNToolbox (Rueckauer et al. 2017), and is largely based on the work of Diehl et al. (2015). We provide several input encodings, as suggested in the work of Park et al. (2019) and Auge et al. (2021).

### Processing Queue

The pre-trained ANN model to be converted should be saved in keras as an h5py file (extension `.h5`). The saved model is transformed layer by layer into a feed-forward ANNarchy spiking network. The structure of the network remains the same as in the original ANN, while the weights are normalised. Please note that the current implementation focuses primarily on the correctness of the conversion. Computational performance, especially of the converted CNNs, will be improved in future releases.

!!! note

    While the neurons are conceptually spiking neurons, there is one specialty: next to the spike event (stored automatically in ANNarchy), each event will be stored in an additional *mask* array. This *mask* value decays in absence of further spike events exponentially. The decay can be controlled by the *mask_tau* parameter of the population. The projections (either dense or convolution) will use this mask as pre-synaptic input, not the generated list of spike events.

### Input Encoding

In the following we provide brief descriptions of the available input encodings. The abbreviations in brackets denote the name provided to the conversion tool constructor.

#### Intrinsically Bursting ("IB")

This encoding bases on the Izhikevich (2003) model that comprises two ODEs:

$$
\begin{cases}
  \frac{dv}{dt} = 0.04 \cdot v^2 + 5.0 \cdot v + 140.0 - u + I \\
  \\
  \frac{du}{dt} = a \cdot (b \cdot v - u) \\
\end{cases}
$$

The parameters for $a$ - $d$ are selected accordingly to Izhikevich (2003). The provided input images will be set as $I$.

#### Poisson ("CPN")

This encoding uses a Poisson distribution where the pixel values of the image will be used as probability for each individual neuron.

#### Phase Shift Oscillation ("PSO")

Based on the description by Park et al. (2019), the spiking threshold $v_\text{th}$ is modulated by a oscillation function $\Pi$, whereas the membrane potential follows simply the input current. 

$$
\begin{cases}
  \Pi(t) = 2^{-(1+ \text{mod}(t,k))}\\
  \\
  v_\text{th}(t) = \Pi(t) \, v_\text{th}(t)\\
\end{cases}
$$

#### User-defined input encodings

In addition to the pre-defined models, one can opt for individual models using the `Neuron` class of ANNarchy. Please note that a `mask` variable need to be defined, which is fed into the subsequent projections.

### Read-out Methods

In a classification task, the neuron with the highest activity corresponds corresponds to the decision to which class the presented input belongs. However, the highest activity can be determined in different ways. We support currently three methods, defined by the `read_out` parameter of the constructor:

#### Maximum Spike Count

`read_out = 'spike_count'` : the number of spikes emitted by each neuron is recorded and the index of the neuron(s) with the maximum number is returned.

#### Time to Number of Spikes

`read_out = 'time_to_first_spike'` or `read_out = 'time_to_k_spikes'`: when the first or first $k$ spikes are emitted by a single neuron, the simulation is stopped and the neuron rank(s) is returned. For the second mode, an additional $k$ argument need to be also provided.

#### Membrane potential

`read_out = 'membrane_potential'`:  pre-synaptic events are accumulated in the membrane potential of each output neuron. The index of the neuron(s) with the highest membrane potential is returned.

## Interface

::: ANNarchy.extensions.ann_to_snn_conversion.ANNtoSNNConverter
    selection:
      docstring_style: sphinx
    rendering:
      show_root_heading: true
      show_root_full_path: false
      heading_level: 2

## References

Izhikevich (2003) Simple Model of Spiking Neurons. IEEE transactions on neural networks 14(6). doi: 10.1109/TNN.2003.820440

Diehl PU, Neil D, Binas J,et al. (2015) Fast-classifying, high-accuracy spiking deep networks through weight and threshold balancing, 2015 International Joint Conference on Neural Networks (IJCNN), 1-8, doi: 10.1109/IJCNN.2015.7280696.

Rueckauer B, Lungu I, Hu Y, et al. (2017) Conversion of Continuous-Valued Deep Networks to Efficient Event-Driven Networks for Image Classification., Front. Neurosci., 2017, 11. doi: 10.3389/fnins.2017.00682

Park S, Kim S, Choe H, et al. (2019) Fast and Efficient Information Transmission with Burst Spikes in Deep Spiking Neural Networks. 

Auge D, Hille J, Mueller E et al. (2021) A Survey of Encoding Techniques for Signal Processing in Spiking Neural Networks. Neural Processing Letters. 2021; 53:4963-4710. doi:10.1007/s11063-021-10562-2