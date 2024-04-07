# Cracking the Coding Interview C++

![CI](https://github.com/mdanilov/cracking-coding/workflows/CI/badge.svg?branch=master)

Solutions for [Cracking the Coding Interview 6th Edition](http://www.amazon.com/Cracking-Coding-Interview-6th-Edition/dp/0984782850) by [Gayle Laakmann McDowell](http://www.gayle.com/) in C++ programming language.

## Getting Started

For each book chapter, there is a folder with the same name. Each question and solution for it located at the own CPP file inside the chapter folders. There is also a trivial test for each solution located at the end of the file. Execute the following commands to clone, build and run the tests:

``` none
git clone --recurse-submodules https://github.com/mdanilov/cracking-coding.git
cd cracking-coding
mkdir build && cd build && cmake ..
cmake --build .
ctest
```
