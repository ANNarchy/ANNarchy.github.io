# List of notebooks

This section provides a list of the sample models provided in the
`examples/` directory of the source code.

## Rate-coded networks

-   [Neural Field](NeuralField.ipynb): a simple model
    using [neural field](http://www.scholarpedia.org/article/Neural_fields) recurrent
    networks. This is a very simple rate-coded model without learning.
-   [Bar learning](BarLearning.ipynb): an
    implementation of the bar learning problem, illustrating synaptic
    plasticity in rate-coded networks.
-   [Image](Image.ipynb) and
    [Webcam](Webcam.ipynb): shows how to use the
    `ImagePopulation` and `VideoPopulation` classes of the `image`
    extension to clamp directly images and video streams into a
    rate-coded network. Also demonstrate the `convolution` extension.
-   [Structural Plasticity](StructuralPlasticity.ipynb): a
    dummy example using structural plasticity.
-   [Multiple Networks](MultipleNetworks.ipynb): shows how
    to use multiple networks and call `parallel_run` to run several
    networks in parallel.

## Spiking networks

**Simple networks**

-   [Izhikevich](Izhikevich.ipynb): an
    implementation of the simple pulse-coupled network described in
    (Izhikevich, 2003). It shows how to build a simple spiking network
    without synaptic plasticity.
-   [Gap Junctions](GapJunctions.ipynb): an example
    using gap junctions.
-   `example/HodgkinHuxley`{.interpreted-text role="doc"}: a single
    Hodgkin-Huxley neuron.
-   A collection of Brain/PyNN/NEST model reproductions in the folder
    `examples/pyNN`.

**Complex networks**

-   [COBA](COBA.ipynb): an implementation of
    the balanced network described in (Vogels and Abbott, 2005). It
    shows how to build a simple spiking network using integrate-and-fire
    neurons and sparse connectivity.
-   [STP](STP.ipynb): an example of
    short-term plasticity based on the model of Tsodyks, Uziel and
    Markram (2000). *Synchrony Generation in Recurrent Networks with
    Frequency-Dependent Synapses*. The Journal of Neuroscience.

**With synaptic plasticity**

-   [STDP](SimpleSTDP.ipynb): a simple example
    using spike-timing dependent plasticity (STDP).
-   [Ramp](Ramp.ipynb): an example of
    homeostatic STDP based on the model of Carlson, Richert, Dutt and
    Krichmar (2013). *Biologically plausible models of homeostasis and
    STDP: Stability and learning in spiking neural networks*. IJCNN.

## Hybrid networks

-   [Hybrid networks](Hybrid.ipynb): a simple hybrid
    network with both rate-coded and spiking parts.

## General

-   [Bayesian optimization](BayesianOptimization.ipynb): a demo
    showing how to use `hyperopt` to search for hyperparameters of a
    model.
-   [Basal Ganglia](BasalGanglia.ipynb): a simple basal
    ganglia model to show how to use the `tensorboard` extension.
-   [BOLD monitoring](BoldMonitoring.ipynb): a showcase of the `bold` extension allowing to record BOLD signals fron a network.

