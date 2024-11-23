##### Task statement
Three lists of integers sorted in ascending order. Each integer appears
only once in all 3 lists, that is, if it appears in one list, it does
not appear in two other lists. So effectively we have ascending
sequence of numbers broken into three disjoint lists.

To do:
Implement iterator function GetNext() that returns next element
in the ascending sequence of numbers that is the union of these 3 lists.
Do not build the union explicitly, iterate over the three given lists.

Example of input data:
List 1: 1,8,15,16,35
List 2: 2,7,12,63
List 3: 10,13,14,42

Requirements:
- Program must be written in C++.

##### Imlementation details
* There are two files - ```main.cpp``` contains tests, and ```get_next.hpp``` contains implementation.
* C++20, GCC 14.1, Google Test as a dependency, see respective ```CMakeLists.txt```
* I understand it is a test task, but usually we use objects - structs and classes to deal with stateful entities. However, once there is a requirement to provide a function, it is reasonable to keep a state on a side of a caller - see the tests for usage examples.  
* It is a bit unclear what is hidden behind of **List**, so I have decided to tackle this requirement wide. Therefore, this implementation is complete in a sense that there is no need to modify it if there is an update in Task Statement:
  - It will work with any container, that can be thought of as ascending **Disjoint Sorted List**.
  - It will work with any number of arguments.
  - It is easily estendable for arbitrary set of containers.
* It uses Binary Heap data structure to bubble up the next element out of a arguments pack, but follows the Task Statement that requires to refrain from building up a joint set.

