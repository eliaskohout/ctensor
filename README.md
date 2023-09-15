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
├── tensoriter.c
├── tensoriter.h
└── tests
    ├── main.c
    ├── main.h
    ├── tensor_assert.h
    ├── tensor_test.c
    ├── tensor_test.h
    ├── tensoriter_test.c
    └── tensoriter_test.h
```

`dtype.h` _The file that defines the data type for the contents of the tensor. The default is float._

`tensor.c` _The file that contains the main functions. This includes functions for creating, destroying, comparing, copying, mathematical operations and more._

`tensor.h` _The header file for tensor.c containing among ohter the definition of the tensor struct._

`tensorarray.c` _The file for array utility functions._

`tensorarray.h` _The header file for tensorarray.c._

`tensoriter.c` _The file for iterators over tensors and map functions._

`tensoriter.h` _The header file for tensoriter.c._

`tests` _The directory containing the unit tests._


## TODOs

- [ ] Adding DTYPE_COPY macro
- [ ] Make elementwise operations run in parallel
- [ ] Making all functions work with random strides
- [ ] Adding a function for normalising strides
- [ ] Implementing dot product
- [ ] Implementing cross product
- [ ] Adding error codes
- [ ] Adding ability for persistently saving tensors to disk and loading them
- [ ] Adding views of tensor
- [ ] Implementing functions for transposing tensors
