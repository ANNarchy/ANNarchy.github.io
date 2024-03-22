# Installation of ANNarchy

ANNarchy is designed to run on GNU/Linux and OSX. It relies mostly on a C++ compiler (g++ or clang++), Cython (C for Python extension) and Python (Numpy, Sympy) libraries. Installation on Windows is not possible.

## Download


The source code of ANNarchy can be downloaded on github:

```bash
git clone https://github.com/ANNarchy/ANNarchy.git
```

## Installation on GNU/Linux

### Dependencies

ANNarchy depends on a number of packages that should be easily accessible on recent GNU/Linux distributions. The classical way to install these dependencies is through your package manager, or using full Python distributions such as Anaconda. Older versions of these packages may work but have not been tested.

-   python \>= 3.8 (with the development files, e.g. `python-dev` or `python-devel`)
-   g++ \>= 7.4 or clang++ \>= 3.4
-   make \>= 3.0
-   cython \>= 3.0
-   numpy \>= 1.13
-   sympy \>= 1.11
-   scipy \>= 1.9
-   matplotlib \>= 3.0

Additionally, the following packages are optional but strongly recommended:

-   pyqtgraphc(to visualize some of the provided examples. The OpenGL backend can also be needed).
-   lxml (to save the networks in .xml format).
-   pandoc (for reporting).
-   tensorboardX (for the logging extension).

To use the CUDA backend:

-   the CUDA-SDK is available on the official [website](https://developer.nvidia.com/cuda-downloads) (we recommend to use at least a SDK version \> 6.x). For further details on installation etc., please consider the corresponding Quickstart guides ([Quickstart_8.0](https://developer.nvidia.com/compute/cuda/8.0/prod/docs/sidebar/CUDA_Quick_Start_Guide-pdf) for the SDK 8.x).

ANNarchy works with full Python distributions such as Anaconda, as well as in virtual environments and Jupyter notebooks.

!!! note

    On a fresh install of Ubuntu 22.04, here are the minimal system packages to install before ANNarchy:

    ```bash
    sudo apt install build-essential git python3-dev python3-setuptools python3-pip 
    ```

    The minimal Python packages can be installed with:

    ```
    pip install numpy scipy matplotlib cython sympy
    ```

### Installation

#### Using pip

Stable releases of ANNarchy are available on PyPi:

```bash
pip install ANNarchy
```

or:

```bash
pip install ANNarchy --user
```

if you do not have administrator permissions. Omit `--user` in a virtual environment.

You may also install directly the latest commit in the `master` (stable) or `develop` branches with:

```bash
pip install git+https://github.com/ANNarchy/ANNarchy.git@master
```

#### Using the source code

Installation of ANNarchy from source is possible using `pip` in the top-level directory:

```bash
pip install .
```

or in development mode:

```bash
pip install -e .
```

Using `python setup.py install` is deprecated, but still works.

#### C++ compiler

By default, ANNarchy will use the GNU C++ compiler `g++`, which should be in your PATH. If you want to use another compiler (clang++, icc), you can edit the configuration file located at `$HOME/.config/ANNarchy/annarchy.json` (created during installation) accordingly. By default, it is:

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

The (path to the) compiler can be changed in the `openmp` section (ignore the `cuda` section if you do not have a GPU).

You can also change the compiler flags if you know what you are doing. `-O3` does not always lead to faster simulation times, but it is worth a shot.

#### CUDA

If ANNarchy detects the CUDA SDK during installation, it will prepare the required modules. You need to make sure that the CUDA compiler `nvcc` is accessible in your path.

The main problem with CUDA is that the binaries, headers and libraries are installed at different locations depending on the version: `/usr/local/cuda`, `/usr/local/cuda-7.0` or `/usr/local/cuda-8.0`. There is unfortunately no way for ANNarchy to guess the installation path.

A first thing to help ANNarchy find the CUDA libraries is to define the `LD_LIBRARY_PATH` environment variable and have point at the `lib64/` subfolder:

```bash
export LD_LIBRARY_PATH=/usr/local/cuda-8.0/lib64/:$LD_LIBRARY_PATH
```

This should in most cases work if you have only one CUDA installation. Otherwise, it is needed that you indicate where the CUDA libraries are, by modifying the ANNarchy configuration file located at `$HOME/.config/ANNarchy/annarchy.json`:

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

Simply point the `['cuda']['path']` field to the right location (without `lib64/`). If the nvcc compiler binary is at a different location, the absolute path to the nvcc can be provided by `['cuda']['compiler']` field.

It can happen that the detection of CUDA fails during installation, as some environment variables are not set. In this case try:

```bash
env "PATH=$PATH" "LIBRARY_PATH=$LIBRARY_PATH" pip install .
```

## Installation on MacOS X

Installation on MacOS X is in principle similar to GNU/Linux:

```bash
pip install ANNarchy
```

We strongly advise using a full Python distribution like [Miniforge](https://github.com/conda-forge/miniforge), or a package manager like [Homebrew](https://brew.sh/) rather than the default python provided by Apple.

The main issue if the choice of the C++ compiler:

### Using Apple's LLVM/clang

If not done already, you should first install the [Xcode Command Line Tools](https://developer.apple.com/), either through Apple's website or through [Homebrew](https://brew.sh/) (see <https://mac.install.guide/commandlinetools/> for a guide) to get the LLVM clang++ compiler.

The major drawback is that Apple's clang++ still does not support OpenMP for parallel computing. Any attempt to use OpenMP with ANNarchy using this compiler will crash.

If you have a M1 arm64 processor, it might be beneficial to tell clang++ to use optimizations for that hardware. Open the configuration file at `$HOME/.config/ANNarchy/annarchy.json` and add the following compiler flag (Xcode > 13.0):

``` {.json}
{
    "openmp": {
        "compiler": "clang++",
        "flags": "-mcpu=apple-m1 -O2"
    },
    "cuda": {
        "compiler": "nvcc",
        "flags": "",
        "device": 0,
        "path": "/usr/local/cuda"
    }
}
```

### Using gcc

In order to benefit from OpenMP parallelization, you should install `gcc`, the GNU C compiler, using [Homebrew](https://brew.sh/):

```bash
brew install gcc
```

You will get the command-line C++ compiler with a **version number**, e.g.:

```bash
g++-11
```
The `g++` executable is a symlink to Apple's clang++, do not use it...

You now have to tell ANNarchy which compiler to use, even if it is in your PATH. After installing ANNarchy, a config file is created in `$HOME/.config/ANNarchy/annarchy.json`. Open it and change the `openmp` entry to:

``` {.json}
{
    "openmp": {
        "compiler": "g++-11",
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

!!! note

    A potential problem with Anaconda/miniforge is that the compiler will use by default the
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

    The CUDA backend is not available on OS X.

