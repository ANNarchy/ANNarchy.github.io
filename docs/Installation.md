# Installation of ANNarchy

ANNarchy is designed to run on GNU/Linux and OSX. It relies mostly on a
C++ compiler (g++ or clang++), Cython (C for Python extension) and Python (Numpy, Sympy)
libraries. Installation on Windows is not possible.

## Download

The source code of ANNarchy can be downloaded on Bitbucket:

```bash
git clone http://bitbucket.org/annarchy/annarchy.git
```

## Installation on GNU/Linux

### Dependencies

ANNarchy depends on a number of packages which should be easily
accessible on recent GNU/Linux distributions. The classical way to
install these dependencies is through your package manager, or using
full Python distributions such as Anaconda. Older versions of these
packages may work but have not been tested.

-   g++ \>= 4.8
-   make \>= 3.0
-   python \>= 3.6 (with the development files, e.g. `python-dev` or
    `python-devel`)
-   cython \>= 0.19
-   setuptools \>= 0.6
-   numpy \>= 1.8
-   sympy \>= 0.7.4
-   scipy \>= 0.12
-   matplotlib \>= 2.0

Additionally, the following packages are optional but strongly
recommended:

-   pyqtgraph \>= 0.9.8 (to visualize some of the provided examples. The
    OpenGL backend can also be needed).
-   lxml \>= 3.0 (to save the networks in .xml format).
-   pandoc \>= 2.0 (for reporting).
-   tensorboardX (for the logging extension).

To use the CUDA backend:

-   the CUDA-SDK is available on the official
    [website](https://developer.nvidia.com/cuda-downloads) (we recommend
    to use at least a SDK version \> 6.x). For further details on
    installation etc., please consider the corresponding Quickstart
    guides (
    [Quickstart_8.0](https://developer.nvidia.com/compute/cuda/8.0/prod/docs/sidebar/CUDA_Quick_Start_Guide-pdf)
    for the SDK 8.x).

ANNarchy works with full Python distributions such as Anaconda, as well
as in virtual environments.

On a fresh install of Ubuntu 18.10, here are the minimal packages to
install before ANNarchy (using python 3):

```bash
sudo apt install build-essential git python3-dev python3-setuptools python3-scipy python3-matplotlib python3-sympy cython3
sudo apt install python3-pyqtgraph python3-pyqt4.qtopengl python3-lxml
```

### Installation

#### Using pip

Stable releases of ANNarchy are available on PyPi:

```bash
sudo pip install ANNarchy
```

or:

```bash
pip install ANNarchy --user
```

if you do not have administrator permissions. Omit `--user` in a virtual environment.

#### Using the source code

Installation of ANNarchy is possible using one of the three following
methods:

**Local installation in home directory**

If you want to install ANNarchy in your home directory, type:

```bash
python setup.py install --user
```

The ANNarchy code will be installed in `$HOME/.local/lib/pythonx.y/site-packages/` (replace \'x.y\' with your
Python version) and automatically added to your `PYTHONPATH`.

**Global installation**

If you have administrator permissions, you can install ANNarchy in
`/usr/local` by typing in the top-level directory:

```bash
sudo python setup.py install
```

This simply installs the code in `/usr/local/lib/pythonx.y/dist-packages/`.

**Specific installation**

If you want to install ANNarchy in another directory (let's say in
`/path/to/repertory`), you should first set your Python path to this
directory:

```bash
export PYTHONPATH=$PYTHONPATH:/path/to/repertory/lib/pythonx.y/site-packages
```

Again, replace \'x.y\' with your Python version. If this directory does
not exist, you should create it now. Don\'t forget to set this value in
your `~/.bash_profile` or `~/.bashrc` to avoid typing this command
before every session. You can then install ANNarchy by typing:


```bash
python setup.py install --prefix=/path/to/repertory
```

If you have multiple Python installations on your system (e.g. through
Anaconda), you should update your `LD_LIBRARY_PATH` environment variable
in `.bashrc` or `bash_profile` to point at the location of
`libpython3.6.so` (or whatever version):


```bash
export LD_LIBRARY_PATH=$HOME/anaconda3/lib:$LD_LIBRARY_PATH
```

ANNarchy normally detects which python installation you are currently
using, but helping it does not hurt\...

#### CUDA

If ANNarchy detects the CUDA SDK during installation, it will prepare
the required modules. You need to make sure that the CUDA compiler
`nvcc` is accessible in your path.

The main problem with CUDA is that the binaries, headers and libraries
are installed at different locations depending on the version:
`/usr/local/cuda`, `/usr/local/cuda-7.0` or `/usr/local/cuda-8.0`. There
is unfortunately no way for ANNarchy to guess the installation path.

A first thing to help ANNarchy find the CUDA libraries is to define the
LD_LIBRARY_PATH environment variable and have point at the `lib64/`
subfolder:

```bash
export LD_LIBRARY_PATH=/usr/local/cuda-8.0/lib64/:$LD_LIBRARY_PATH
```

This should in most cases work if you have only one CUDA installation.
Otherwise, it is needed that you indicate where the CUDA libraries are,
by modifying the ANNarchy configuration file located at
`~/.config/ANNarchy/annarchy.json`:

``` {.json}
{
    "openmp": {
        "compiler": "g++",
        "flags": "-march=native -O2"
    },
    "cuda": {
        "compiler": "nvcc",
        "flags": "",
        "device": 0,
        "path": "/usr/local/cuda"
    }
}
```

Simply point the `['cuda']['path']` field to the right location (without
`lib64/`). If the nvcc compiler binary is at a different location, the
absolute path to the nvcc can be provided by `['cuda']['compiler']`
field.

It can happen that the detection of CUDA fails during installation, as
some environment variables are not set. In this case try:

```bash
sudo env "PATH=$PATH" "LIBRARY_PATH=$LIBRARY_PATH" python setup.py install
```

## Installation on MacOS X

Installation on MacOS X is in principle similar to GNU/Linux:

```bash
python setup.py install (--user or --prefix)
```

We advise using a full Python distribution such as
[Anaconda](https://www.continuum.io/why-anaconda), which installs
automatically all dependencies of ANNarchy, rather than using the old
python provided by Apple.

The only problem with Anaconda (and potentially other Python
distributions, not tested) is that the compiler will use by default the
Python shared library provided by Apple, leading to the following crash
when simulating:

    Fatal Python error: PyThreadState_Get: no current thread
    Abort trap: 6

The solution is to set the environment variable
`DYLD_FALLBACK_LIBRARY_PATH` to point at the correct library
`libpython3.6.dylib` in your `.bash_profile`. For a standard Anaconda
installation, this should be:

```bash
export DYLD_FALLBACK_LIBRARY_PATH=$HOME/anaconda/lib:$DYLD_FALLBACK_LIBRARY_PATH
```

!!! note

    The default compiler on OS X is clang-llvm. You should install the *command_line_tools* together with XCode in order to use it.

    For some reasons, this compiler is not compatible with OpenMP, so the models will only run sequentially.

    The CUDA backend is not available on OS X.

