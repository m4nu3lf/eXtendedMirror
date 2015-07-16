## Introduction ##

 eXtendedMirror is a reflection system for C++ with the following features:

- Compiler Independent
- Non intrusive
- No mandatory parser required
- Variant based interface
- Dry-est possible interface

It supports almost all the construct of the language (with some limitations) such as:

- Primitive Types
- Pointer Types
- References
- C Array Types
- Classes
- Multiple Inheritance
- Abstract Classes
- Methods
- Static Functions
- Namespaces
- Class Templates
- Constants
- Enumerators

## Dependencies ##

The code only depends on the c++11 standard library, but the build system depends on [CMake](http://www.cmake.org/) and [Python](https://www.python.org/)

## Building ##

To build the library you first have to run CMake from the project directory


```
#!bash

cmake -DCMAKE_BUILD_TYPE=Debug .
```


You can change Debug with Release if you want, and you can set some other parameters such as

- FUNC_PARAM_MAX: maximum number of supported function parameters (defaults to 8).
- GET_N_SET_EXTR_PARAM_MAX: Maximum number of supported extra parameters for getters and setters, that is the maximum number of parameters for getters, and the maximum number of parameters for setters, beyond the first (i.e. the value to set) (defaults to 3).
- TEMPL_PARAM_MAX: Maximum number of supported template parameters, for class templates (defaults to 4).

After running CMake, you can build the library and the tests by running


```
#!bash

make
```
To install on your system type


```
#!bash

make install
```

## Using the library ##

To use the library include the header XM/xMirror.hpp in your compile units and link to the libxMirror library

## Roadmap ##
- Primitive types casting
- Pointer to reference casting
- General Type casters
- Template value parameter support
- Multiple constructors
- Reflect the standard library
- Parser (?)