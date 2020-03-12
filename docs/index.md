# Boooter Documentation

This is where documentation for the project lands.

## Building

### Windows

A lot _embedded projects_ use Windows as development platform and host for build. While it's not most optimum way of work, many companies preferred them as Windows is usually their only supported OS.

#### Visual Studio 2015

In `tests\msvc\` you can find project for [Visual Studio 2015](https://www.visualstudio.com/pl/vs/older-downloads/). It's only for unit tests.

#### Qbs

[Qbs](http://doc.qt.io/qbs/index.html) is a build system from Qt, a more universal alternative to qmake.

In `tests\qbs` you can find projects that can be handled from command line or QtCreator.

If you have `qbs` executable in PATH and Visual Studio environment configured, these two commands build and run tests:
```
qbs build
qbs run
```
Qbs is platform agnostic, so can be successfully used to build on other systems. It's going to use the default compiler on that platform.

##### Troubleshooting

In case of the following error message:
```
qbs-windows-x86_64-1.15.0\share\qbs\imports\qbs\Probes\MsvcProbe.qbs:51:16 Error: Detecting the MSVC build environment failed: Cannot find 'vcvarsall.bat'.
```
Try to run `qbs-setup-toolchains --system --detect` and then use `qbs build profile:MSVC2019-x64` (or other profile matching your needs)

#### Cross compilation

The code was built using [GNU Arm Embedded Toolchain](https://developer.arm.com/open-source/gnu-toolchain/gnu-rm) with success. Doesn't apply to unit tests.

## Usage in own project

Just use files from `src` directory as you see fit.
