# CubismZ: Lossy wavelet-based and Lossless HPC data compression of 3D scientific data


## Design

CubismZ performs _two_ compression stages on the input dataset.  The first
stage makes use of (lossy) floating point compression algorithms.  In the
second stage, general-purpose lossless methods are applied to the compressed
data of the first stage.  A more detailed description can be found in the
paper.

#### Substage 1: floating point compression

Available compressors for this stage are:

- Wavelets (CSELAB)
- FPZIP (LLNL)
- ZFP (LLNL)
- SZ (ANL)


#### Substage 2: general-purpose lossless compression

Available compression techniques for this stage are:

- ZLIB
- LZ4
- data shuffling, bit zeroing can be applied first (for wavelets)


## Compilation

#### Basic options

- Conversion to the CZ format without data compression
  ```
  make clean; make
  ```

- Wavelets + ZLIB
  ```
  make clean; make wavz=1 zlib=1
  ```

- ZFP
  ```
  make clean; make zfp=1
  ```

- FPZIP
  ```
  make clean; make fpzip=1
  ```

- SZ
  ```
  make clean; make sz=1
  ```


#### Additional options

- Wavelets + Shuffling + ZLIB
  ```
  make clean;make wavz=1 shuffle3=1 zlib=1
  ```

- Wavelets + LZ4
  ```
  make clean; make wavz=1 lz4=1
  ```


## Runtime arguments of the basic CubismZ tools:

#### The `hdf2cz` tool

Compression of HDF5 files to CZ format.

###### Runtime arguments

```
hdf2cz -bpdx <nbx> -bpdy <nby> -bpdz <nbz> -simdata <hdf5 file> -outdata <compressed file> -threshold <e> [-wtype <wt>]
```

- The HDF5 file consists of `nbx * nby * nbz` 3D blocks
- The input HDF5 file is compressed and stored to `<compressed file>`
- The threshold specifies how lossy the compression will be TODO: need to
  specify the range of threshold
- The wavelet type can optionally be specified using the `-wtype` option

###### Compile time arguments

- Block dimension (typically `32 * 32 * 32` data elements).  The block
  dimension can be set with
  ```
  make clean; make blocksize=32 [other options]
  ```
- Compression methods for the first and second substages.  See
  [Compilation](#compilation)


#### The `ch2hdf` tool

Decompression of CZ files and conversion to HDF5 format

###### Runtime arguments

```
cz2hdf -simdata <compressed file> -h5file <h5 file>
```

- Decompress and store in HDF5 format
- The output file can be visualized with ParaView
- Compile time options (`blocksize`, compression scheme) must agree with those
  used for the compression phase.  See [compile time
  arguments](#compile-time-arguments) of the previous section


#### The `cz2diff` tool

Decompress and compare two CZ files

###### Runtime arguments

```
cz2diff -simdata1 <compressed file 1> -simdata2 <compressed file 2>
```

- The second CZ file is used as the reference dataset and must have been generated
  by the default configuration of the `hdf2cz` tool, i.e. without any
  [compression method enabled](#basic-options)
- Useful for quality assessment of the compression


## Examples

TODO

#### Testing

1. Build the executables for the [basic options](#basic-options)

2. Tests/Test1:
	generate a reference CZ file for an input HDF5 file using the default compilation option (no compression)
	for each of the rest four basic options
		- compress the HDF5 file using the corresponding hdf2cz tool
		- compute the compression statistics (ratio, errors, PSNR value) using the corresponding cz2diff tool

3. Tests/Test2:
	compress an input HDF5 file using the hdf2cz tool and the wavelets + zlib compression scheme
	decompress and convert back the compressed CZ file to HDF5 format
	visualize the generated HDF5 file
