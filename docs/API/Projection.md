# Projection class

The class `ANNarchy.Projection` defines projections at the population
level. A projection is an ensemble of connections (or synapses) between
a subset of a population (called the pre-synaptic population) and a
subset of another population (the post-synaptic population), with a
specific connection type. The pre- and post-synaptic populations may be
the same.


::: ANNarchy.core.Projection.Projection
    options:
      heading_level: 2
      members:
        -  dendrites
        - nb_synapses
        - size
        - __init__
        - connectivity_matrix
        - dendrite
        - disable_learning
        - enable_learning
        - get
        - load
        - nb_efferent_synapses
        - nb_synapses_per_dendrite
        - receptive_fields
        - reset
        - save
        - save_connectivity
        - set
        - size_in_bytes
        - start_creating
        - start_pruning
        - stop_creating
        - stop_pruning
        - synapse

