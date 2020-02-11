#if !defined(VX3_FORCEFIELD_H)
#define VX3_FORCEFIELD_H

#include "VX3_MathTree.h"

struct VX3_ForceField {
    VX3_MathTreeToken token_x_forcefield[1024];
    VX3_MathTreeToken token_y_forcefield[1024];
    VX3_MathTreeToken token_z_forcefield[1024];
    VX3_ForceField() {
        token_x_forcefield[0].op = mtCONST;
        token_x_forcefield[0].value = 0;
        token_x_forcefield[1].op = mtEND;
        token_y_forcefield[0].op = mtCONST;
        token_y_forcefield[0].value = 0;
        token_y_forcefield[1].op = mtEND;
        token_z_forcefield[0].op = mtCONST;
        token_z_forcefield[0].value = 0;
        token_z_forcefield[1].op = mtEND;
    }
    bool validate() {
        return VX3_MathTree::validate(token_x_forcefield) &&
               VX3_MathTree::validate(token_y_forcefield) &&
               VX3_MathTree::validate(token_z_forcefield);
    }
    __device__ __host__ double x_forcefield(double x, double y, double z, double t) {
        return VX3_MathTree::eval(x, y, z, t, token_x_forcefield);
    }
    __device__ __host__ double y_forcefield(double x, double y, double z, double t) {
        return VX3_MathTree::eval(x, y, z, t, token_y_forcefield);
    }
    __device__ __host__ double z_forcefield(double x, double y, double z, double t) {
        return VX3_MathTree::eval(x, y, z, t, token_z_forcefield);
    }
};

#endif // VX3_FORCEFIELD_H
