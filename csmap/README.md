# csmap

This directory contains a Visual Studio solution that builds a single `csmap.exe` wrapper
around the individual ericw map tools (`qbsp`, `light`, `vis`, `bspinfo`, `bsputil`).

## Layout

```
csmap/
  csmap.sln               # Visual Studio solution
  csmap/
    csmap.vcxproj         # Aggregated console application project
    csmap.vcxproj.filters # IDE filters for easier navigation
    dispatcher.cc         # Command dispatcher with pipeline support
    tool_shims/           # Small wrappers that redirect each tool's main()
```

The project compiles the original tool sources directly from the repository.  Each shim
redefines `main` to expose the upstream entry point as `*_main`, allowing the dispatcher
to select the implementation at runtime without modifying the upstream code.

## Third-party libraries

The project expects the same third-party dependencies as the CMake build (fmt, jsoncpp,
pareto, Intel TBB and Embree).  Configure the library and include directories by setting
the MSBuild properties `EmbreeIncludeDir`, `EmbreeLibDir`, `TbbIncludeDir`, `TbbLibDir`,
`FmtLibDir`, `JsonCppLibDir` and `ParetoLibDir` (for example via a user property sheet or
environment-specific `.user` file).  When these properties are empty the include paths
fall back to the in-tree headers, but the linker still requires the compiled libraries.

## Usage

Build the solution to produce `csmap.exe`, then invoke it as:

```
csmap qbsp <args...>
csmap light <args...>
csmap vis <args...>
csmap bspinfo <args...>
csmap bsputil <args...>
```

Multiple stages can be chained with `--`, e.g.

```
csmap qbsp map.map -- light map.bsp -- vis map.bsp
```

Arguments are forwarded verbatim to the upstream parsers so existing command lines
continue to work as before.
