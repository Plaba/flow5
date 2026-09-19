// Shim for distros (e.g. Ubuntu/Debian) whose libopenblas-dev package does not
// ship an "openblas/lapack.h" header (unlike an OpenBLAS from-source install,
// which bundles a LAPACKE-derived header under that name). The system's
// OpenBLAS shared library still exports the classic Fortran-ABI LAPACK
// symbols used by this project, so we only need to declare the small subset
// of routines actually called.
#ifndef FLOW5_COMPAT_OPENBLAS_LAPACK_H
#define FLOW5_COMPAT_OPENBLAS_LAPACK_H

typedef int lapack_int;

#ifdef __cplusplus
extern "C" {
#endif

void dgels_(char *trans, lapack_int *m, lapack_int *n, lapack_int *nrhs,
            double *a, lapack_int *lda, double *b, lapack_int *ldb,
            double *work, lapack_int *lwork, lapack_int *info);

void dgesv_(lapack_int *n, lapack_int *nrhs, double *a, lapack_int *lda,
            lapack_int *ipiv, double *b, lapack_int *ldb, lapack_int *info);

void dgetrf_(lapack_int *m, lapack_int *n, double *a, lapack_int *lda,
             lapack_int *ipiv, lapack_int *info);

void sgetrf_(lapack_int *m, lapack_int *n, float *a, lapack_int *lda,
             lapack_int *ipiv, lapack_int *info);

void dgetri_(lapack_int *n, double *a, lapack_int *lda, lapack_int *ipiv,
             double *work, lapack_int *lwork, lapack_int *info);

void dgetrs_(char *trans, lapack_int *n, lapack_int *nrhs, double *a,
             lapack_int *lda, lapack_int *ipiv, double *b, lapack_int *ldb,
             lapack_int *info);

void sgetrs_(char *trans, lapack_int *n, lapack_int *nrhs, float *a,
             lapack_int *lda, lapack_int *ipiv, float *b, lapack_int *ldb,
             lapack_int *info);

#ifdef __cplusplus
}
#endif

#endif // FLOW5_COMPAT_OPENBLAS_LAPACK_H
