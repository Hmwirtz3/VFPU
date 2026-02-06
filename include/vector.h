#include <pspgum.h>
#include <pspgu.h>
#include <psptypes.h>


static inline ScePspVector4* VFPUMulVec4(ScePspVector4 *v0, const ScePspVector4 *v1, const ScePspVector4 *v2) // v0 v1 and v2 must be 16 byte aligned. Otherwise a baby panda dies :(
{
    asm volatile(
    
        "lv.q   C000, 0(%1)\n"
        "lv.q   C010, 0(%2)\n"
        "vmul.q C000, C000, C010\n"
        "sv.q   C000, 0(%0)\n"
        :
        : "r"(v0), "r"(v1), "r"(v2)
        : "memory"
    );

    return v0;
}

static inline ScePspVector4* VFPUAddVec4(ScePspVector4 *v0, const ScePspVector4 *v1, const ScePspVector4 *v2) // align that shit by 16 (this is a psp)
{
    asm volatile(
        
        "lv.q   C000, 0(%1)\n"
        "lv.q   C010, 0(%2)\n"
        "vadd.q C000, C000, C010\n"
        "sv.q   C000, 0(%0)\n"

        :
        : "r"(v0), "r"(v1), "r"(v2)
        : "memory"
    );

    return v0;
}

static inline ScePspVector4* VFPUSubVec4(ScePspVector4 *v0, ScePspVector4 *v1, ScePspVector4 *v2) // keep that shit aligned already
{
    asm volatile 
    (
        "lv.q C000, 0(%1)\n"
        "lv.q C010, 0(%2)\n"
        "vsub.q C000, C000, C010\n"
        "sv.q C000, 0(%0)\n"

        :
        :"r"(v0), "r"(v1), "r"(v2)
        :"memory"

    );
}

