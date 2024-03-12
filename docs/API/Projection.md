# Projection

The class `ANNarchy.Projection` defines projections at the population
level. A projection is an ensemble of connections (or synapses) between
a subset of a population (called the pre-synaptic population) and a
subset of another population (the post-synaptic population), with a
specific connection type. The pre- and post-synaptic populations may be
the same.

The connectors are methods of the projections, for example:

```python
proj = Projection(pop, pop, 'exc)
proj.connect_all_to_all(weights=Normal(0, 1))
```

::: ANNarchy.core.Projection.Projection
    options:
      heading_level: 2
      members:
        - dendrites
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
        - start_creating
        - start_pruning
        - stop_creating
        - stop_pruning
        - synapse

## Connectors

::: ANNarchy.core.ConnectorMethods.connect_one_to_one
    options:
      heading_level: 3

::: ANNarchy.core.ConnectorMethods.connect_all_to_all
    options:
      heading_level: 3

::: ANNarchy.core.ConnectorMethods.connect_fixed_probability
    options:
      heading_level: 3

::: ANNarchy.core.ConnectorMethods.connect_fixed_number_pre
    options:
      heading_level: 3

::: ANNarchy.core.ConnectorMethods.connect_fixed_number_post
    options:
      heading_level: 3

::: ANNarchy.core.ConnectorMethods.connect_gaussian
    options:
      heading_level: 3

::: ANNarchy.core.ConnectorMethods.connect_dog
    options:
      heading_level: 3

::: ANNarchy.core.ConnectorMethods.connect_with_func
    options:
      heading_level: 3

::: ANNarchy.core.ConnectorMethods.connect_from_matrix
    options:
      heading_level: 3

::: ANNarchy.core.ConnectorMethods.connect_from_sparse
    options:
      heading_level: 3

::: ANNarchy.core.ConnectorMethods.connect_from_file
    options:
      heading_level: 3