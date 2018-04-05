# OSRandom [![TravisCI_badge]][TravisCI_link] [![AppVeyor_badge]][AppVeyor_link]

[TravisCI_badge]: https://travis-ci.org/Chocobo1/OSRandom.svg?branch=master
[TravisCI_link]: https://travis-ci.org/Chocobo1/OSRandom
[AppVeyor_badge]: https://ci.appveyor.com/api/projects/status/github/Chocobo1/OSRandom?branch=master&svg=true
[AppVeyor_link]: https://ci.appveyor.com/project/Chocobo1/OSRandom

C++11 header-only OS Random Layer

A header-only random layer that expose cryptographically secure pseudorandom number generators (CSPRNG) provided by OS:
* Windows: [MSDN](https://msdn.microsoft.com/en-us//library/windows/desktop/aa387694(v=vs.85).aspx)
* Linux: [man7](http://man7.org/linux/man-pages/man4/random.4.html)
* FreeBSD: [man](https://www.freebsd.org/cgi/man.cgi?query=random&sektion=4)

## Prerequisites
* Linux, *nix, BSD ...
  * C++11 compiler
  * `/dev/random` is available to read<br />
    This means API will block when there are not enough entropy in system
* Windows
  * C++11 compiler
  * Warning: `NOMINMAX` is already defined and included before Windows.h header<br />
    I.e. If you include Windows.h before this library, make sure `NOMINMAX` is defined before Windows.h
* Run tests
  * [doctest C++ testing framework](https://github.com/onqtam/doctest)


## Usage
To use this header in your project:

1. [Download osrandom.hpp](https://raw.githubusercontent.com/Chocobo1/OSRandom/master/osrandom.hpp)

2. Use it like:
    ```c++
    #include <random>
    #include "osrandom.hpp"

    void example()
    {
      // Specify distribution of outputs
      std::uniform_int_distribution<> dist;

      // Get an instance...
      Chocobo1::OSRandom osRandom;

      // Voilà!
      int number = dist(osRandom);

      // Or you prefer accessing it directly
      int number2 = osRandom();
    }
    ```


## Run Tests
To run tests, execute:
```shell
git submodule update --init --remote --recursive

cd test

# linux
make
./run_tests

# Windows
build.bat
run_tests.exe
```


## License
See [LICENSE](./LICENSE) file
