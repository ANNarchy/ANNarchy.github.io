# List of notebooks

This section provides a list of the sample models provided in the
`examples/` directory of the source code. 

The Jupyter notebooks can be downloaded from:

<https://github.com/ANNarchy/ANNarchy.github.io/tree/master/docs/example>

## Rate-coded networks

-   [Neural Field](NeuralField.ipynb): a simple model using [neural field](http://www.scholarpedia.org/article/Neural_fields) recurrent networks. This is a very simple rate-coded model without learning.
-   [Bar learning](BarLearning.ipynb): an implementation of the bar learning problem, illustrating synaptic plasticity in rate-coded networks.
-   [Structural Plasticity](StructuralPlasticity.ipynb): a dummy example using structural plasticity.

## Spiking networks

**Simple networks**

-   [Izhikevich](Izhikevich.ipynb): an implementation of the simple pulse-coupled network described in (Izhikevich, 2003). It shows how to build a simple spiking network without synaptic plasticity.
-   [Gap Junctions](GapJunctions.ipynb): an example using gap junctions.
-   [HodgkinHuxley](HodgkinHuxley.ipynb): a single Hodgkin-Huxley neuron.

**Complex networks**

-   [COBA](COBA.ipynb): an implementation of the balanced network described in (Vogels and Abbott, 2005). It
    shows how to build a simple spiking network using integrate-and-fire neurons and sparse connectivity.
-   [STP](STP.ipynb): an example of short-term plasticity based on the model of Tsodyks, Uziel and Markram (2000). 

**With synaptic plasticity**

-   [STDP](SimpleSTDP.ipynb): a simple example using spike-timing dependent plasticity (STDP).
-   [Ramp](Ramp.ipynb): an example of homeostatic STDP based on the model of Carlson, Richert, Dutt and
    Krichmar (2013)
    
## Hybrid networks

-   [Hybrid networks](Hybrid.ipynb): a simple hybrid network with both rate-coded and spiking sub-parts.

## Extensions

-   [Image](Image.ipynb) and [Webcam](Webcam.ipynb): shows how to use the `ImagePopulation` and `VideoPopulation` classes of the `image` extension to clamp directly images and video streams into a rate-coded network. Also demonstrates the `convolution` extension.
-   [Parallel simulations](MultipleNetworks.ipynb): shows how to call `parallel_run` to run several networks in parallel.
-   [Bayesian optimization](BayesianOptimization.ipynb): a demo showing how to use `hyperopt` to search for hyperparameters of a  model.
-   [Logging with tensorboard](BasalGanglia.ipynb): a simple basal ganglia model to show how to use the `tensorboard` extension.
-   [BOLD monitoring](BoldMonitoring.ipynb): a showcase of the `bold` extension allowing to record BOLD signals fron a network.

