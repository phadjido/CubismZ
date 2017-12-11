# CubismZ: A Parallel Data Compression Framework for Large Scale 3D Scientific Data


## Design

CubismZ performs two compression stages on the input dataset.  The first stage
makes use of (lossy) floating point compression algorithms.  In the second
stage, general-purpose lossless methods are applied to the compressed data of
the first stage.  A more detailed description can be found in the paper.

#### Substage 1: Floating point compression

Available compressors for this stage are:

- 3D wavelets ([CSELAB][linklab])
- FPZIP ([LLNL][linkllnl])
- ZFP ([LLNL][linkllnl])
- SZ ([ANL][linkanl])

#### Substage 2: General-purpose lossless compression

Available compression techniques for this stage are:

- [ZLIB][linkzlib]
- [LZ4][linklz4]

Before lossless compression, data (byte) shuffling and bit zeroing can be optionally applied to the output of the wavelet-based compression scheme.


## Compilation

#### External software dependencies

- MPI library (Tested platforms: MPICH, OpenMPI, MVAPICH2)
- Parallel HDF5 (Compatible with one of the above MPI libraries)  
- ZLIB compression library

#### Configured compilation

The default set of executables required to reproduce the included test cases
can be generated by invoking `make` in the root directory.

The `C++` and `C` MPI wrappers can be set using the `MPICC` and `mpicc` flags, respectively.
They default to `MPICC=mpic++` and `mpicc=mpicc`. 

The software has been tested with the [GCC][gcclink], [Intel][intellink] and [Clang][clanglink] compilers.

OpenMP is enabled by default, except for the Clang compiler.  It can be enabled
for a Clang installation that supports OpenMP by passing `extra=-fopenmp` to
the `make` command.

In order to compile the software, a parallel build of the [HDF5](http://www.hdfgroup.org) library is required.
The path to the HDF5 `include` and `lib` directories can be specified using the `hdf-incdir` and
`hdf-libdir` variables respectively.  See the [Makefile](./Makefile) for
further details.

Successful execution of the build chain generates a set of executables in the `CubismZ/Tools/bin` directory.
 The configuration for these binaries is as follows:

##### No compression (default)

Conversion to the CZ format without data compression.  No special flags are
required for this build at compile time.  This target can be built individually
inside the `CubismZ/Tools` directory with:
```
make
```

##### Wavelets and ZLIB

Generates a build using the CubismZ wavelet compression scheme for the first
compression stage (floating point compression) and applies [ZLIB][linkzlib] in
the second compression stage.  This target can be built individually inside the
`CubismZ/Tools` directory with:
```
make wavz=1 zlib=1
```

##### ZFP

Generates a build using the [ZFP][linkllnl] floating point compressor for the
first compression stage.  No further compression is applied for the second
stage.  This target can be built individually inside the `CubismZ/Tools` directory
with:
```
make zfp=1
```

##### FPZIP

Generates a build using the [FPZIP][linkllnl] floating point compressor for the
first compression stage.  No further compression is applied for the second
stage.  This target can be built individually inside the `CubismZ/Tools` directory
with:
```
make fpzip=1
```

##### SZ

Generates a build using the [SZ][linkanl] floating point compressor for the
first compression stage.  No further compression is applied for the second
stage.  This target can be built individually inside the `CubismZ/Tools` directory
with:
```
make sz=1
```


#### Custom compilation

Custom user defined configurations are possible as well.  Any of the
combinations described in the [design](#design) section are possible.  Custom
builds require that the `CubismZ/ThirdParty` dependencies are compiled first.  In order
to do so, the command
```
make thirdparty-libs
```
must be executed from the _root directory_.  Custom builds can then be
generated by using the `CubismZ/Tools/Makefile`.  Assuming the working directory is
`CubismZ/Tools`, example custom builds can be generated with:

##### Wavelets, shuffling and ZLIB
```
make install dir=mycustom1 wavz=1 shuffle3=1 zlib=1
```

##### Wavelets and LZ4
```
make install dir=mycustom2 wavz=1 lz4=1
```

Additional compile time flags may be required for compiler specification and
HDF5 library paths.  See the [configured compilation](#configured-compilation)
section for more details.


#### Blocksize

The block dimension can be specified at compile time.  The default value is
`blocksize=32`, which translates to cubic blocks with `32 * 32 * 32` data
elements.  The `blocksize` argument can be passed to the make command.  Its
value must be a power of two.


## Runtime arguments of CubismZ tools for HDF5 datasets:

#### The `hdf2cz` tool

Compression of HDF5 files to CZ format.
```
hdf2cz -bpdx <nbx> -bpdy <nby> -bpdz <nbz> -h5file <hdf5 file> -czfile <cz file> -threshold <e> [-wtype <wt>]
```

- The HDF5 file consists of `nbx * nby * nbz` 3D blocks
- The input HDF5 file is compressed and stored to `<cz file>`
- The threshold specifies how lossy the compression will be TODO: need to
  specify the range of threshold (?)
- The wavelet type can optionally be specified using the `-wtype` option.
  The following options / wavelet types are supported
  - 1: 4th order average interpolating wavelets
  - 2: 4th order lifted interpolating wavelets
  - 3: 3rd order average interpolating wavelets (default)


#### The `ch2hdf` tool

Decompression of CZ files and conversion to HDF5 format
```
cz2hdf -czfile <cz file> -h5file <h5 file> [-wtype <wt>]
```

- The output file can be visualized with ParaView
- Compile time options (`blocksize`, compression scheme) must agree with those
  used for the compression phase.  See the [blocksize](#blocksize) section for
  more information.
- The optional parameter specified by `wtype` must agree with the type of wavelets
  used in the compressed file.


#### The `cz2diff` tool

Decompress and compare two CZ files
```
cz2diff -czfile1 <cz file1> [-wtype <wt>] -czfile2 <cz reference file2>
```

- The second CZ file is used as the reference dataset and must have been generated
  by the default configuration of the `hdf2cz` tool, i.e., without any
  [compression method enabled](#no-compression-default)
- Useful for quality assessment of the compression


## Example: Fluid dynamics data

#### Dataset

The software release includes a set of basic tests to demonstrate the
capabilities of the CubismZ compression techniques.  The test data consists of
the 3D pressure field of a cloud cavitation collapse simulation.  The initial
configuration is composed of 70 air bubbles (dispersed phase, non-condensible
gas) submerged in liquid water (continuous phase) and is discretized in a cubic
domain with `512 * 512 * 512` cells.  Note that the simulation is
under-resolved.  Nevertheless, the degree of variation in the quantity of
interest (3D pressure field) is sufficient to test the compression algorithms.
The snapshot of the test data is taken at iteration 5000.  A visualization of
the gas volume fraction as well as the pressure in a plane through the cloud
center for this iteration is shown below.

![](.images/pressure_alpha2_5000.png)

Additionally, the mean pressure over all iteration steps is shown in the next
figure.  Plus/minus one standard deviation is indicated by the shaded region.

![](.images/mean_pressure.png)

The pressure test data at iteration 5000 can be downloaded at the following
link (287MB):

[data_005000.tar][datadl]


#### Compression performance tests

The compression performance tests are located in `CubismZ/Tests/Test1`.  The test
scripts require that the simulation HDF5 data `data_005000-p.h5` has been
[downloaded][datadl] and is located in the `CubismZ/Tests/Data` directory.  The
complete test chain can be run by executing `CubismZ/Tests/Test1/run_all.sh`.  The
script requires that the [configured compilation](#configured-compilation) has
been performed previously.  The `run_all.sh` script generates a `run_all.txt`
file with the output of the compressor test configurations.
The script can be run with the syntax:
```
./run_all.sh [<n processors>]
```
where `<n processors>` is the number of MPI processes to be used.  The default
is 1.  Reference output from [CSELAB][linklab] can be found in
`cselab_ref_run_all.txt`.  The script executes the following tasks:

1. `genref.sh`: Generates a reference CZ file without compression, based on
   the HDF5 input data.  The script can also be executed individually with the
   syntax:
   ```
   ./genref.sh
   ```

2. `test_wavz.sh`: Runs the [wavelets and zlib](#wavelets-and-zlib) compressor.
   If no reference file exists, the script will generate it automatically.  The
   test can be run individually with the syntax:
   ```
   ./test_wavz.sh [<n processors> [<error threshold>]]
   ```
   Parameter in square brackets are optional. `<n processors>` sets the number
   of MPI processes.  Defaults to 1 if not specified.  The `<error threshold>`
   parameter is specific to the wavelet compressor.  The default is 0.01.

3. `test_zfp.sh`: Runs the [ZFP](#zfp) compressor.  If no reference file
   exists, the script will generate it automatically.  The test can be run
   individually with the syntax:
   ```
   ./test_zfp.sh [<n processors> [<error threshold>]]
   ```
   Parameter in square brackets are optional. `<n processors>` sets the number
   of MPI processes.  Defaults to 1 if not specified.  The `<error threshold>`
   parameter is specific to the ZFP compressor.  The default is 0.5.

4. `test_fpzip.sh`: Runs the [FPZIP](#fpzip) compressor.  If no reference file
   exists, the script will generate it automatically.  The test can be run
   individually with the syntax:
   ```
   ./test_fpzip.sh [<n processors> [<n bits>]]
   ```
   Parameter in square brackets are optional. `<n processors>` sets the number
   of MPI processes.  Defaults to 1 if not specified.  The `<n bits>`
   parameter is specific to the FPZIP compressor.  The default is 22.

5. `test_sz.sh`: Runs the [SZ](#sz) compressor.  If no reference file exists,
   the script will generate it automatically.  The test can be run individually
   with the syntax:
   ```
   ./test_sz.sh [<n processors> [<error threshold>]]
   ```
   Parameter in square brackets are optional. `<n processors>` sets the number
   of MPI processes.  Defaults to 1 if not specified.  The `<error threshold>`
   parameter is specific to the SZ compressor.  The default is 0.01.  The SZ
   compressor can be further configured using the provided
   `CubismZ/Tests/Test1/sz.config` file.

The performance metrics (compression ratio, errors, PSNR value) are written to
the standard output or into the file `run_all.txt` if the batch script is used.
The PSNR value is computed based on the reference CZ file generated with the
`genref.sh` script.


##### Testing custom builds

Custom builds can be tested against the reference using the `test_custom.sh`
script.  The execution syntax for this script is:
```
./test_custom.sh <path to binaries> <error threshold> [<n processors>]
```
where

* `<path to binaries>`: Path to the directory that contains the custom build.
  For example, if `dir=mycustom` has been passed to the `make` command, the
  path is `../../Tools/bin/mycustom` (assuming the current working directory is
  `CubismZ/Tests/Test1`.

* `<error threshold>`: Error threshold that corresponds to the chosen floating
  point compressor (substage1 compressor).

* `<n processors>`: Number of MPI processes to be used.  Optional, defaults to 1.


#### Visual assessment for lossy compressors

An example of compression and decompression cycle is provided in `CubismZ/Tests/Test2`.
The `run_all.sh` script can be executed to run the test chain.
The script can be run with the syntax:
```
./run_all.sh [<n processors>]
```
where `<n processors>` is the number of MPI processes to be used.  The default
is 1.  The input HDF5 data is compressed to the CZ format using the `hdf2cz`
tool with wavelets and ZLIB compression substages.  The compressed data is then
converted back to HDF5 using the `cz2hdf` tool and can be used for
visualization using a capable tool such as ParaView, for example.


## Quick Testing

#### Configure 

- Edit `CubismZ/Makefile` and set the following options 
   - `MPICC`, `mpicc`: MPI-aware C++ and C compiler, respectively
   - `hdf-incdir`, `hdf-libdir`: location of the parallel HDF5 library 

#### Compile

- Issue `make`. This will
  - configure and build the third-party libraries and install them in the `CubismZ/ThirdParty/build` directory. 
  - build the CubismZ tools (hdf2cz, cz2hdf, cz2diff) for each of the basic configurations and put the executable into the corresponding subdirectories of the `CubimZ/Tools/bin` directory. 

#### Download the example dataset

#### Run the tests



[linklab]:http://www.cse-lab.ethz.ch "http://www.cse-lab.ethz.ch"
[linkllnl]:https://computation.llnl.gov/projects/floating-point-compression "https://computation.llnl.gov/projects/floating-point-compression"
[linkanl]:https://collab.cels.anl.gov/display/ESR/SZ "https://collab.cels.anl.gov/display/ESR/SZ"
[linkzlib]:https://zlib.net/ "https://zlib.net/"
[linklz4]:https://lz4.github.io/lz4/ "https://lz4.github.io/lz4/"
[datadl]:https://polybox.ethz.ch/index.php/s/a3454aSFG5qDe9a/download "https://polybox.ethz.ch/index.php/s/a3454aSFG5qDe9a/download"
[gcclink]:https://gcc.gnu.org/ "https://gcc.gnu.org/"
[intellink]:https://software.intel.com/en-us/c-compilers "https://software.intel.com/en-us/c-compilers"
[clanglink]:http://www.llvm.org/ "http://www.llvm.org/"
