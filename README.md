## ctensor
A simple C library implementing tensors. Still in development. Currently it only utilizes the CPU to enable mathematical operations with tensors.

## Structure
```
├── LICENSE
├── Makefile
├── README.md
├── dtype.h
├── tensor.c
├── tensor.h
├── tensorarray.c
├── tensorarray.h
├── tensorfunc.c
├── tensorfunc.h
└── tests
    ├── main.c
    ├── main.h
    ├── tensor_assert.h
    ├── tensor_test.c
    ├── tensor_test.h
    ├── tensorfunc_test.c
    └── tensorfunc_test.h
```

`dtype.h` _The file that defines the data type for the contents of the tensor. The default is float._

`tensor.c` _The file that contains the main functions. This includes functions for creating, destroying, comparing, copying, mathematical operations and more._

`tensor.h` _The header file for tensor.c containing among ohter the definition of the tensor struct._

`tensorarray.c` _The file for array utility functions._

`tensorarray.h` _The header file for tensorarray.c._

`tensorfunc.c` _The file for iterators over tensors and map functions._

`tensorfunc.h` _The header file for tensorfunc.c._

`tests` _The directory containing the unit tests._


## TODOs

- [ ] Adding DTYPE_COPY macro
- [ ] Make elementwise operations run in parallel
- [ ] Making all functions work with random strides (print too)
- [ ] Adding a function for normalising strides
- [ ] Implementing dot product
- [ ] Implementing cross product
- [ ] Adding error codes
- [ ] Testing error handling for all functions
- [ ] Adding ability for persistently saving tensors to disk and loading them
- [ ] Adding views of tensor and test them for all functions
- [ ] Implementing functions for transposing tensors
