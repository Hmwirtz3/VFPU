#include <pspuser.h>
#include <pspdebug.h>
#include <pspdisplay.h>
#include <psptypes.h>
#include "vector.h"

PSP_MODULE_INFO("VFPU Vec4 Test", 0, 1, 0);
PSP_MAIN_THREAD_ATTR(PSP_THREAD_ATTR_USER | THREAD_ATTR_VFPU);


// Exit handling
int exit_callback(int arg1, int arg2, void *common) {
    sceKernelExitGame();
    return 0;
}

int callback_thread(SceSize args, void *argp) {
    int cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
    sceKernelRegisterExitCallback(cbid);
    sceKernelSleepThreadCB();
    return 0;
}

int setup_callbacks(void) {
    int thid = sceKernelCreateThread("update_thread", callback_thread, 0x11, 0xFA0, 0, 0);
    if (thid >= 0)
        sceKernelStartThread(thid, 0, 0);
    return thid;
}

int main(void) {
    setup_callbacks();
    pspDebugScreenInit();

    ScePspVector4 a = { .f = { 2.0f, 3.0f, 6.0f, 7.0f } };
    ScePspVector4 b = { .f = { 4.0f, 5.0f, 8.0f, 9.0f } };
    ScePspVector4 addResult;
    ScePspVector4 mulResult;
    ScePspVector4 subResult;

    VFPUAddVec4(&addResult, &a, &b);
    VFPUMulVec4(&mulResult, &a, &b);
    VFPUSubVec4(&subResult, &a, &b);

    pspDebugScreenPrintf(
        "A = (%f, %f, %f, %f)\n",
        a.f[0], a.f[1], a.f[2], a.f[3]
    );

    pspDebugScreenPrintf(
        "B = (%f, %f, %f, %f)\n\n",
        b.f[0], b.f[1], b.f[2], b.f[3]
    );

    pspDebugScreenPrintf(
        "Add Result = (%f, %f, %f, %f)\n",
        addResult.f[0], addResult.f[1],
        addResult.f[2], addResult.f[3]
    );

    pspDebugScreenPrintf(
        "Mul Result = (%f, %f, %f, %f)\n",
        mulResult.f[0], mulResult.f[1],
        mulResult.f[2], mulResult.f[3]
    );

    pspDebugScreenPrintf
    (
        "Sub Result = (%f, %f, %f, %f)", 
        subResult.f[0], subResult.f[1],
        subResult.f[2], subResult.f[3]
    );

    while (1) {
        sceDisplayWaitVblankStart();
    }

    return 0;
}
