# Neuron

Neurons are container objects for all information corresponding to a
special neuron type. This encapsulation allows a higher readability of
the code. Through derivation of `ANNarchy.Neuron`, the user can define
the neuron types he needs in his model.

The type of the neuron (rate-coded or spiking) depends on the presence
of the `spike` argument.

::: ANNarchy.Neuron
    selection:
      docstring_style: restructured-text
    rendering:
      show_root_heading: true
      heading_level: 2