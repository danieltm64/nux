# Hello C#

This example showcases using Nux from C#.

# Build and Run

1. Clone the repo to a directory of your choice. For this example, we'll call it *nux*.
2. Create a build directory outside of *nux*. For this example, we'll call it *build*.
3. Run `cmake -G (pick a generator) ../nux -DNUX_BUILD_CS=1` in the build directory.
4. Run `cmake --build .` in the build directory.
5. Run `cd examples/hellocs/hellocs`
5. Run `dotnet run`.
6. This is what you'll get, depending on your platform:

<img alt="Nux example running on Windows" src="../../screenshots/windows-cs.png" width="250px">
<img alt="Nux example running on macOS" src="../../screenshots/macos-cs.png" width="250px">
<img alt="Nux example running on Linux" src="../../screenshots/linux-cs.png" width="250px">
