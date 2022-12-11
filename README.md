

## Utility C++ classes, types and functions not available in std library


-----------------

### Input file
These files are a group of independent source files, each aiming at specific tasks:

[InputFile.h] is a input text file format. We use a relaxed Json
format, which aims to be user friendly to non-technical users of our
codes.  It servers as the slightly advanced input parser for Sir.h code
described below (the alternative being a simple text stream). It also
maintains compatibility with .mhd image headers and is used in our 3D
image manipulation codes.
The file defines two classes
 - InputFile: main class
 - mstream: a utility class used for duplicating messages into std::cout and an log file.

-------

### C++ additional types
[typses.h] this file defines classes primarily for dealing with scientific data:

  var3<T>  is a template class which is used with alias names dbl3, float3 and int3, which represent 3D variants of double, float and int. For more general vector/tensor data types I use  [VMMLib].

 -  var2<T> is 2D version of var3<T>.

 -  piece<T> is a simpler alternative to std::slice.  It serves the same job that std::string_view serves in relation with std::string, but for std::vector. Essentially it an efficient wrapper around continuous data, and is used to do arithmetic operations on data stored as std::vector.

 - Vars<T>, used with alias names dbls, floats, dbl3s, is similar to piece<T>, but keeps its own copy of the data rather than being a wrapper around other data.  we use this primarily as an alternative to std::valarray which has an ugly syntax.

 - varsOr<T> This is only used in svplot library. It  but is meant to serve as a container for optional data (with a default value) and contains a name for the data as well as a transform function.  This is not an essential feature and needs further development and testing.

Some basic functions for statistical analysis of scalar data are also stored here.

-------

[globals.h] Macros and utility functions for debugging, testing and calibration of C++ codes.
