# Hybrid networks

Converting a rate-coded population to a spiking population requires
connecting a `PoissonPopulation` with the rate-coded
one.

Converting a spiking population with a rate-coded one requires the use
of a `DecodingProjection`, which can connected using any connector
method available for `Projection`.

::: ANNarchy.DecodingProjection
    selection:
      docstring_style: sphinx
    rendering:
      show_root_heading: true
      show_root_full_path: false
      heading_level: 2
