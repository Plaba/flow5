// Shim for distros (e.g. Ubuntu/Debian) whose libopenblas-dev package does not
// install its headers under an "openblas/" subdirectory. The system cblas.h
// is otherwise identical to the one shipped by an OpenBLAS from-source install.
#include <cblas.h>
