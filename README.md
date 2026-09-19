# flow5
flow5 is a potential flow solver with built-in pre- and post- processing functionalities. Its purpose is to make the preliminary designs of wings, planes, hydrofoils and sails reliable, fast and user-friendly.

It is version 7 of the legacy project xflr5.


# Compilation

Full compilation instructions are maintained at
https://flow5.tech/docs/flow5_doc/Source/Compilation.html

## Linux notes

The qmake project files build with either GCC or Clang, and with
Qt5 or Qt6, but the exact set of system packages providing
OpenBLAS/LAPACK, OpenCASCADE (OCCT) and gmsh varies across Linux
distributions and versions. The build already accounts for the
following differences; if you hit something not covered here, it's
most likely another instance of the same kind of mismatch:

- **OpenBLAS**: distro packages don't always provide a multi-threaded
  "openblasp" library, and some (e.g. Debian/Ubuntu) don't install
  their headers under an `openblas/` subdirectory the way a
  from-source OpenBLAS install does. The build links against the
  plain `openblas` library and falls back to a small header shim
  under `compat/openblas/` when `openblas/lapack.h` can't be found
  on the system include path.
- **OpenCASCADE (OCCT)**: version 7.8 split STEP and other
  data-exchange support out of the older monolithic libraries
  (`TKSTEP`, `TKRWMesh`) into per-format `TKDE*` libraries. The
  `.pro` files detect which set is actually installed and link
  against the matching one.
- **gmsh**: option names can be added or removed between versions
  (e.g. `Geometry.OCCBooleanGlue`). Code that inspects gmsh options
  for diagnostic purposes tolerates an unknown option rather than
  aborting.
- **Qt5 vs Qt6**: a handful of APIs used by this project differ
  between the two (`QLibraryInfo::path()` vs `::location()`,
  `QtConcurrent::run()`'s argument order for member functions); these
  are guarded on `QT_VERSION` throughout the code.
- **Clang-only flags**: `-Wsfinae-incomplete=0` (used to silence a
  warning from OpenCASCADE/Qt headers) is only understood by Clang
  and is skipped when building with GCC.
- Some Linux linkers refuse by default to link an executable against
  a shared library that itself has unresolved symbols, even when
  those symbols are legitimately resolved through that library's own
  dependencies at load time (the case for flow5-lib.so/flow5-io-lib.so
  and their XFoil/OpenBLAS/OCCT dependencies). `flow5-app.pro` passes
  `-Wl,--allow-shlib-undefined` to accommodate this.

flow5-lib, flow5-io-lib and XFoil-lib aren't installed to a system
library directory by default, so `flow5-app`'s binary needs to find
them via `LD_LIBRARY_PATH` at run time unless you `make install`
each of them first (see their `.pro` files for the `PREFIX` used).

## API examples

The `API_examples/` directory builds separately with CMake, against
an *installed* flow5-lib/flow5-io-lib/XFoil-lib (`sudo make install`
from the qmake build, using the default `/usr/local` prefix). Each
example's `CMakeLists.txt` has Linux-specific `CACHE` variables
(`XFOIL_INCLUDE_DIR`, `FLOW5_INCLUDE_DIR`, `OCCT_INCLUDE_DIR`, ...)
that default to common distro package locations; override them with
`-D` if your system differs. To build an example:

```
cd API_examples/<ExampleName>
mkdir build && cd build
cmake ..
cmake --build . -j$(nproc)
```


# Remaining developments 
- Fix bugs and implement minor improvements depending on user requests
- ~~Either complete or remove currently inoperative features, e.g. plane optimization, advanced editors~~
- Consider adding force location to extra-drag input
- Continue to clean the code and to improve the API 
- Clean the documentation

# API 

## Implementation
Please note that the API is still in an experimental state and subject to change. 

The intent is to stabilize both the source code and the API by the end of 2026. 

Even though the main part of the intended refactoring has been completed with v7.57, deprecation or even discontinuation of interfaces are still likely until the end of the year.

## Examples
- XFoilRun: Construction of a NACA foil and calculation of a type 1 polar using XFoil.
- XFoilBatchRun: Construction of a NACA foil and multi-threaded calculation of a 2d polar mesh.
- PlaneRun1: Construction of an xfl-type plane with no fuselage and calculation of a type 2 polar with viscous drag evaluated on the fly. Shows how to use custom units.
- PlaneRun2: Construction of an xfl-type plane with a NURBS type fuselage, construction of a conforming mesh, and calculation of a type 2 polar.
- PlaneRun3: Import of an stl-type plane from a mesh file, configuration of the trailing edge and calculation of a type 1 polar.
- PlaneRun4: Import of a plane and a polar from xml files, construction of a conforming mesh, and calculation of a type 1 polar.
- PlaneRun5: Import of an STL-type fuselage into an xfl-type plane.
- PlaneRun6: Import of a fuselage from a STEP file into an xfl-type plane.
