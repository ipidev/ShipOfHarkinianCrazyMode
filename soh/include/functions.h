#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "z64.h"
#include <stdarg.h>

#ifdef __cplusplus
#define this thisx
extern "C"
{
#endif

#include "luslog.h"
#include <soh/Enhancements/item-tables/ItemTableTypes.h>
#include <soh/Enhancements/randomizer/randomizer_inf.h>

#if defined(INCLUDE_GAME_PRINTF) && defined(_DEBUG)
#define osSyncPrintf(fmt, ...) lusprintf(__FILE__, __LINE__, 0, fmt, __VA_ARGS__)
#else
#define osSyncPrintf(fmt, ...) osSyncPrintfUnused(fmt, ##__VA_ARGS__)
#endif

void gSPSegment(void* value, int segNum, uintptr_t target);
void gSPSegmentLoadRes(void* value, int segNum, uintptr_t target);
void gDPSetTextureImage(Gfx* pkt, u32 f, u32 s, u32 w, uintptr_t i);
void gSPDisplayList(Gfx* pkt, Gfx* dl);
void gSPDisplayListOffset(Gfx* pkt, Gfx* dl, int offset);
void gSPVertex(Gfx* pkt, uintptr_t v, int n, int v0);
void gSPInvalidateTexCache(Gfx* pkt, uintptr_t texAddr);
void gDPSetTextureImageFB(Gfx* pkt, u32 format, u32 size, u32 width, int fb);


void cleararena(void);
void bootproc(void);
void Main_ThreadEntry(void* arg);
void Idle_ThreadEntry(void* arg);
void ViConfig_UpdateVi(u32 mode);
void ViConfig_UpdateBlack(void);
s32 DmaMgr_CompareName(const char* name1, const char* name2);
s32 DmaMgr_DmaRomToRam(uintptr_t rom, uintptr_t ram, size_t size);
s32 DmaMgr_DmaHandler(OSPiHandle* pihandle, OSIoMesg* mb, s32 direction);
void DmaMgr_Error(DmaRequest* req, const char* file, const char* errorName, const char* errorDesc);
const char* DmaMgr_GetFileNameImpl(uintptr_t vrom);
const char* DmaMgr_GetFileName(uintptr_t vrom);
void DmaMgr_ProcessMsg(DmaRequest* req);
void DmaMgr_ThreadEntry(void* arg0);
s32 DmaMgr_SendRequestImpl(DmaRequest* req, uintptr_t ram, uintptr_t vrom, size_t size, u32 unk, OSMesgQueue* queue, OSMesg msg);
s32 DmaMgr_SendRequest0(uintptr_t ram, uintptr_t vrom, size_t size);
void DmaMgr_Init(void);
s32 DmaMgr_SendRequest2(DmaRequest* req, uintptr_t ram, uintptr_t vrom, size_t size, u32 unk5, OSMesgQueue* queue, OSMesg msg,
                        const char* file, s32 line);
s32 DmaMgr_SendRequest1(void* ram0, uintptr_t vrom, size_t size, const char* file, s32 line);
void* Yaz0_FirstDMA(void);
void* Yaz0_NextDMA(void* curSrcPos);
void Yaz0_DecompressImpl(Yaz0Header* hdr, u8* dst);
void Yaz0_Decompress(uintptr_t romStart, void* dst, size_t size);
void Locale_Init(void);
void Locale_ResetRegion(void);
u32 func_80001F48(void);
u32 func_80001F8C(void);
u32 Locale_IsRegionNative(void);
#ifdef __WIIU__
void _assert(const char* exp, const char* file, s32 line);
#elif defined(__linux__)
void __assert(const char* exp, const char* file, s32 line) __THROW;
#elif !defined(__APPLE__) && !defined(__SWITCH__)
void __assert(const char* exp, const char* file, s32 line);
#endif
#if defined(__APPLE__) && defined(NDEBUG)
void __assert(const char* exp, const char* file, s32 line);
#endif
void isPrintfInit(void);
void osSyncPrintfUnused(const char* fmt, ...);
//void osSyncPrintf(const char* fmt, ...);
void rmonPrintf(const char* fmt, ...);
void* is_proutSyncPrintf(void* arg, const char* str, u32 count);
void func_80002384(const char* exp, const char* file, u32 line);
OSPiHandle* osDriveRomInit(void);
void StackCheck_Init(StackEntry* entry, void* stackTop, void* stackBottom, u32 initValue, s32 minSpace,
                     const char* name);
void StackCheck_Cleanup(StackEntry* entry);
s32 StackCheck_GetState(StackEntry* entry);
u32 StackCheck_CheckAll(void);
u32 StackCheck_Check(StackEntry* entry);
f32 LogUtils_CheckFloatRange(const char* exp, s32 line, const char* valueName, f32 value, const char* minName, f32 min,
                             const char* maxName, f32 max);
s32 LogUtils_CheckIntRange(const char* exp, s32 line, const char* valueName, s32 value, const char* minName, s32 min,
                           const char* maxName, s32 max);
void LogUtils_LogHexDump(void* ptr, ptrdiff_t size0);
void LogUtils_LogPointer(s32 value, u32 max, void* ptr, const char* name, const char* file, s32 line);
void LogUtils_CheckBoundary(const char* name, s32 value, s32 unk, const char* file, s32 line);
void LogUtils_CheckNullPointer(const char* exp, void* ptr, const char* file, s32 line);
void LogUtils_CheckValidPointer(const char* exp, void* ptr, const char* file, s32 line);
void LogUtils_LogThreadId(const char* name, s32 line);
void LogUtils_HungupThread(const char* name, s32 line);
void LogUtils_ResetHungup(void);
void __osPiCreateAccessQueue(void);
void __osPiGetAccess(void);
void __osPiRelAccess(void);
s32 osSendMesg(OSMesgQueue* mq, OSMesg mesg, s32 flag);
void osStopThread(OSThread* thread);
void osViExtendVStart(u32 arg0);
s32 osRecvMesg(OSMesgQueue* mq, OSMesg* msg, s32 flag);
void __osInitialize_common(void);
void __osInitialize_autodetect(void);
void __osExceptionPreamble();
// ? __osException(?);
void __osEnqueueAndYield(OSThread**);
void __osEnqueueThread(OSThread**, OSThread*);
OSThread* __osPopThread(OSThread**);
// ? __osNop(?);
void __osDispatchThread();
void __osCleanupThread(void);
void __osDequeueThread(OSThread** queue, OSThread* thread);
void osDestroyThread(OSThread* thread);
void osCreateThread(OSThread* thread, OSId id, void (*entry)(void*), void* arg, void* sp, OSPri pri);
void __osSetSR(u32);
u32 __osGetSR();
void osWritebackDCache(void* vaddr, s32 nbytes);
void* osViGetNextFramebuffer(void);
void osCreatePiManager(OSPri pri, OSMesgQueue* cmdQ, OSMesg* cmdBuf, s32 cmdMsgCnt);
void __osDevMgrMain(void* arg);
s32 __osPiRawStartDma(s32 dir, u32 cartAddr, void* dramAddr, size_t size);
u32 osVirtualToPhysical(void* vaddr);
void osViBlack(u8 active);
s32 __osSiRawReadIo(void* devAddr, u32* dst);
OSId osGetThreadId(OSThread* thread);
void osViSetMode(OSViMode* mode);
u32 __osProbeTLB(void*);
u32 osGetMemSize(void);
void osSetEventMesg(OSEvent e, OSMesgQueue* mq, OSMesg msg);
s32 _Printf(PrintCallback, void* arg, const char* fmt, va_list ap);
void osUnmapTLBAll(void);
s32 osEPiStartDma(OSPiHandle* handle, OSIoMesg* mb, s32 direction);
void osInvalICache(void* vaddr, s32 nbytes);
void osCreateMesgQueue(OSMesgQueue* mq, OSMesg* msg, s32 count);
void osInvalDCache(void* vaddr, s32 nbytes);
s32 __osSiDeviceBusy(void);
s32 osJamMesg(OSMesgQueue* mq, OSMesg mesg, s32 flag);
void osSetThreadPri(OSThread* thread, OSPri pri);
OSPri osGetThreadPri(OSThread* thread);
s32 __osEPiRawReadIo(OSPiHandle* handle, u32 devAddr, u32* data);
void osViSwapBuffer(void* vaddr);
s32 __osEPiRawStartDma(OSPiHandle* handle, s32 direction, u32 cartAddr, void* dramAddr, size_t size);
void __osTimerServicesInit(void);
void __osTimerInterrupt(void);
void __osSetTimerIntr(OSTime time);
OSTime __osInsertTimer(OSTimer* timer);
#ifndef __cplusplus
void __osSetGlobalIntMask(OSHWIntr mask);
#endif
void __osSetCompare(u32);
#ifndef __cplusplus
void __osResetGlobalIntMask(OSHWIntr mask);
#endif
s32 __osDisableInt(void);
void __osRestoreInt(s32);
void __osViInit(void);
void __osViSwapContext(void);
OSMesgQueue* osPiGetCmdQueue(void);
s32 osEPiReadIo(OSPiHandle* handle, u32 devAddr, u32* data);
void osViSetSpecialFeatures(u32 func);
OSPiHandle* osCartRomInit(void);
void __osSetFpcCsr(u32);
u32 __osGetFpcCsr();
s32 osEPiWriteIo(OSPiHandle* handle, u32 devAddr, u32 data);
void osMapTLBRdb(void);
void osYieldThread(void);
u32 __osGetCause();
s32 __osEPiRawWriteIo(OSPiHandle* handle, u32 devAddr, u32 data);
void _Litob(_Pft* args, u8 type);
//ldiv_t ldiv(s32 num, s32 denom);
//lldiv_t lldiv(s64 num, s64 denom);
void _Ldtob(_Pft* args, u8 type);
s32 __osSiRawWriteIo(void* devAddr, u32 val);
void osCreateViManager(OSPri pri);
OSViContext* __osViGetCurrentContext(void);
void osStartThread(OSThread* thread);
void osViSetYScale(f32 scale);
void osViSetXScale(f32 value);
void __osSetWatchLo(u32);

EnItem00* Item_DropCollectible(PlayState* play, Vec3f* spawnPos, s16 params);
EnItem00* Item_DropCollectible2(PlayState* play, Vec3f* spawnPos, s16 params);
void EnItem00_CustomItemsParticles(Actor* Parent, PlayState* play, GetItemEntry giEntry);
void Item_DropCollectibleRandom(PlayState* play, Actor* fromActor, Vec3f* spawnPos, s16 params);
void EffectBlure_ChangeType(EffectBlure* this, int type);
void EffectBlure_AddVertex(EffectBlure* this, Vec3f* p1, Vec3f* p2);
void EffectBlure_AddSpace(EffectBlure* this);
void EffectBlure_Init1(void* thisx, void* initParamsx);
void EffectBlure_Init2(void* thisx, void* initParamsx);
void EffectBlure_Destroy(void* thisx);
s32 EffectBlure_Update(void* thisx);
void EffectBlure_Draw(void* thisx, GraphicsContext* gfxCtx);
void EffectShieldParticle_Init(void* thisx, void* initParamsx);
void EffectShieldParticle_Destroy(void* thisx);
s32 EffectShieldParticle_Update(void* thisx);
void EffectShieldParticle_Draw(void* thisx, GraphicsContext* gfxCtx);
void EffectSpark_Init(void* thisx, void* initParamsx);
void EffectSpark_Destroy(void* thisx);
s32 EffectSpark_Update(void* thisx);
void EffectSpark_Draw(void* thisx, GraphicsContext* gfxCtx);
void func_80026230(PlayState* play, Color_RGBA8* color, s16 arg2, s16 arg3);
void func_80026400(PlayState* play, Color_RGBA8* color, s16 arg2, s16 arg3);
void func_80026608(PlayState* play);
void func_80026690(PlayState* play, Color_RGBA8* color, s16 arg2, s16 arg3);
void func_80026860(PlayState* play, Color_RGBA8* color, s16 arg2, s16 arg3);
void func_80026A6C(PlayState* play);
PlayState* Effect_GetPlayState(void);
void* Effect_GetByIndex(s32 index);
void Effect_InitContext(PlayState* play);
void Effect_Add(PlayState* play, s32* pIndex, s32 type, u8 arg3, u8 arg4, void* initParams);
void Effect_DrawAll(GraphicsContext* gfxCtx);
void Effect_UpdateAll(PlayState* play);
void Effect_Delete(PlayState* play, s32 index);
void Effect_DeleteAll(PlayState* play);
void EffectSs_InitInfo(PlayState* play, s32 tableSize);
void EffectSs_ClearAll(PlayState* play);
void EffectSs_Delete(EffectSs* effectSs);
void EffectSs_Reset(EffectSs* effectSs);
void EffectSs_Insert(PlayState* play, EffectSs* effectSs);
void EffectSs_Spawn(PlayState* play, s32 type, s32 priority, void* initParams);
void EffectSs_UpdateAll(PlayState* play);
void EffectSs_DrawAll(PlayState* play);
s16 func_80027DD4(s16 arg0, s16 arg1, s32 arg2);
s16 func_80027E34(s16 arg0, s16 arg1, f32 arg2);
u8 func_80027E84(u8 arg0, u8 arg1, f32 arg2);
void EffectSs_DrawGEffect(PlayState* play, EffectSs* this, void* texture);
void EffectSsDust_Spawn(PlayState* play, u16 drawFlags, Vec3f* pos, Vec3f* velocity, Vec3f* accel,
                        Color_RGBA8* primColor, Color_RGBA8* envColor, s16 scale, s16 scaleStep, s16 life,
                        u8 updateMode);
void func_8002829C(PlayState* play, Vec3f* pos, Vec3f* velocity, Vec3f* accel, Color_RGBA8* primColor,
                   Color_RGBA8* envColor, s16 scale, s16 scaleStep);
void func_80028304(PlayState* play, Vec3f* pos, Vec3f* velocity, Vec3f* accel, Color_RGBA8* primColor,
                   Color_RGBA8* envColor, s16 scale, s16 scaleStep);
void func_8002836C(PlayState* play, Vec3f* pos, Vec3f* velocity, Vec3f* accel, Color_RGBA8* primColor,
                   Color_RGBA8* envColor, s16 scale, s16 scaleStep, s16 life);
void func_800283D4(PlayState* play, Vec3f* pos, Vec3f* velocity, Vec3f* accel, Color_RGBA8* primColor,
                   Color_RGBA8* envColor, s16 scale, s16 scaleStep, s16 life);
void func_8002843C(PlayState* play, Vec3f* pos, Vec3f* velocity, Vec3f* accel, Color_RGBA8* primColor,
                   Color_RGBA8* envColor, s16 scale, s16 scaleStep, s16 life);
void func_800284A4(PlayState* play, Vec3f* pos, Vec3f* velocity, Vec3f* accel, Color_RGBA8* primColor,
                   Color_RGBA8* envColor, s16 scale, s16 scaleStep);
void func_80028510(PlayState* play, Vec3f* pos, Vec3f* velocity, Vec3f* accel, Color_RGBA8* primColor,
                   Color_RGBA8* envColor, s16 scale, s16 scaleStep);
void func_8002857C(PlayState* play, Vec3f* pos, Vec3f* velocity, Vec3f* accel);
void func_800285EC(PlayState* play, Vec3f* pos, Vec3f* velocity, Vec3f* accel);
void func_8002865C(PlayState* play, Vec3f* pos, Vec3f* velocity, Vec3f* accel, s16 scale, s16 scaleStep);
void func_800286CC(PlayState* play, Vec3f* pos, Vec3f* velocity, Vec3f* accel, s16 scale, s16 scaleStep);
void func_8002873C(PlayState* play, Vec3f* pos, Vec3f* velocity, Vec3f* accel, s16 scale, s16 scaleStep,
                   s16 life);
void func_800287AC(PlayState* play, Vec3f* pos, Vec3f* velocity, Vec3f* accel, s16 scale, s16 scaleStep,
                   s16 life);
void func_8002881C(PlayState* play, Vec3f* pos, Vec3f* velocity, Vec3f* accel, Color_RGBA8* primColor,
                   Color_RGBA8* envColor);
void func_80028858(PlayState* play, Vec3f* pos, Vec3f* velocity, Vec3f* accel, Color_RGBA8* primColor,
                   Color_RGBA8* envColor);
void func_80028990(PlayState* play, f32 randScale, Vec3f* srcPos);
void func_80028A54(PlayState* play, f32 randScale, Vec3f* srcPos);
void EffectSsKiraKira_SpawnSmallYellow(PlayState* play, Vec3f* pos, Vec3f* velocity, Vec3f* accel);
void EffectSsKiraKira_SpawnSmall(PlayState* play, Vec3f* pos, Vec3f* velocity, Vec3f* accel,
                                 Color_RGBA8* primColor, Color_RGBA8* envColor);
void EffectSsKiraKira_SpawnDispersed(PlayState* play, Vec3f* pos, Vec3f* velocity, Vec3f* accel,
                                     Color_RGBA8* primColor, Color_RGBA8* envColor, s16 scale, s32 life);
void EffectSsKiraKira_SpawnFocused(PlayState* play, Vec3f* pos, Vec3f* velocity, Vec3f* accel,
                                   Color_RGBA8* primColor, Color_RGBA8* envColor, s16 scale, s32 life);
void EffectSsBomb_Spawn(PlayState* play, Vec3f* pos, Vec3f* velocity, Vec3f* accel);
void EffectSsBomb2_SpawnFade(PlayState* play, Vec3f* pos, Vec3f* velocity, Vec3f* accel);
void EffectSsBomb2_SpawnLayered(PlayState* play, Vec3f* pos, Vec3f* velocity, Vec3f* accel, s16 scale,
                                s16 scaleStep);
void EffectSsBlast_Spawn(PlayState* play, Vec3f* pos, Vec3f* velocity, Vec3f* accel, Color_RGBA8* primColor,
                         Color_RGBA8* envColor, s16 scale, s16 scaleStep, s16 sclaeStepDecay, s16 life);
void EffectSsBlast_SpawnWhiteCustomScale(PlayState* play, Vec3f* pos, Vec3f* velocity, Vec3f* accel, s16 scale,
                                         s16 scaleStep, s16 life);
void EffectSsBlast_SpawnShockwave(PlayState* play, Vec3f* pos, Vec3f* velocity, Vec3f* accel,
                                  Color_RGBA8* primColor, Color_RGBA8* envColor, s16 life);
void EffectSsBlast_SpawnWhiteShockwave(PlayState* play, Vec3f* pos, Vec3f* velocity, Vec3f* accel);
void EffectSsGSpk_SpawnAccel(PlayState* play, Actor* actor, Vec3f* pos, Vec3f* velocity, Vec3f* accel,
                             Color_RGBA8* primColor, Color_RGBA8* envColor, s16 scale, s16 scaleStep);
void EffectSsGSpk_SpawnNoAccel(PlayState* play, Actor* actor, Vec3f* pos, Vec3f* velocity, Vec3f* accel,
                               Color_RGBA8* primColor, Color_RGBA8* envColor, s16 scale, s16 scaleStep);
void EffectSsGSpk_SpawnFuse(PlayState* play, Actor* actor, Vec3f* pos, Vec3f* velocity, Vec3f* accel);
void EffectSsGSpk_SpawnRandColor(PlayState* play, Actor* actor, Vec3f* pos, Vec3f* velocity, Vec3f* accel,
                                 s16 scale, s16 scaleStep);
void EffectSsGSpk_SpawnSmall(PlayState* play, Actor* actor, Vec3f* pos, Vec3f* velocity, Vec3f* accel,
                             Color_RGBA8* primColor, Color_RGBA8* envColor);
void EffectSsDFire_Spawn(PlayState* play, Vec3f* pos, Vec3f* velocity, Vec3f* accel, s16 scale, s16 scaleStep,
                         s16 alpha, s16 fadeDelay, s32 life);
void EffectSsDFire_SpawnFixedScale(PlayState* play, Vec3f* pos, Vec3f* velocity, Vec3f* accel, s16 alpha,
                                   s16 fadeDelay);
void EffectSsBubble_Spawn(PlayState* play, Vec3f* pos, f32 yPosOffset, f32 yPosRandScale, f32 xzPosRandScale,
                          f32 scale);
void EffectSsGRipple_Spawn(PlayState* play, Vec3f* pos, s16 radius, s16 radiusMax, s16 life);
void EffectSsGSplash_Spawn(PlayState* play, Vec3f* pos, Color_RGBA8* primColor, Color_RGBA8* envColor,
                           s16 type, s16 scale);
void EffectSsGMagma_Spawn(PlayState* play, Vec3f* pos);
void EffectSsGFire_Spawn(PlayState* play, Vec3f* pos);
void EffectSsLightning_Spawn(PlayState* play, Vec3f* pos, Color_RGBA8* primColor, Color_RGBA8* envColor,
                             s16 scale, s16 yaw, s16 life, s16 numBolts);
void EffectSsDtBubble_SpawnColorProfile(PlayState* play, Vec3f* pos, Vec3f* velocity, Vec3f* accel, s16 scale,
                                        s16 life, s16 colorProfile, s16 randXZ);
void EffectSsDtBubble_SpawnCustomColor(PlayState* play, Vec3f* pos, Vec3f* velocity, Vec3f* accel,
                                       Color_RGBA8* primColor, Color_RGBA8* envColor, s16 scale, s16 life, s16 randXZ);
void EffectSsHahen_Spawn(PlayState* play, Vec3f* pos, Vec3f* velocity, Vec3f* accel, s16 unused, s16 scale,
                         s16 objId, s16 life, Gfx* dList);
void EffectSsHahen_SpawnBurst(PlayState* play, Vec3f* pos, f32 burstScale, s16 unused, s16 scale,
                              s16 randScaleRange, s16 count, s16 objId, s16 life, Gfx* dList);
void EffectSsStick_Spawn(PlayState* play, Vec3f* pos, s16 yaw);
void EffectSsSibuki_Spawn(PlayState* play, Vec3f* pos, Vec3f* velocity, Vec3f* accel, s16 moveDelay,
                          s16 direction, s16 scale);
void EffectSsSibuki_SpawnBurst(PlayState* play, Vec3f* pos);
void EffectSsSibuki2_Spawn(PlayState* play, Vec3f* pos, Vec3f* velocity, Vec3f* accel, s16 scale);
void EffectSsGMagma2_Spawn(PlayState* play, Vec3f* pos, Color_RGBA8* primColor, Color_RGBA8* envColor,
                           s16 updateRate, s16 drawMode, s16 scale);
void EffectSsStone1_Spawn(PlayState* play, Vec3f* pos, s32 arg2);
void EffectSsHitMark_Spawn(PlayState* play, s32 type, s16 scale, Vec3f* pos);
void EffectSsHitMark_SpawnFixedScale(PlayState* play, s32 type, Vec3f* pos);
void EffectSsHitMark_SpawnCustomScale(PlayState* play, s32 type, s16 scale, Vec3f* pos);
void EffectSsFhgFlash_SpawnLightBall(PlayState* play, Vec3f* pos, Vec3f* velocity, Vec3f* accel, s16 scale,
                                     u8 param);
void EffectSsFhgFlash_SpawnShock(PlayState* play, Actor* actor, Vec3f* pos, s16 scale, u8 param);
void EffectSsKFire_Spawn(PlayState* play, Vec3f* pos, Vec3f* velocity, Vec3f* accel, s16 scaleMax, u8 type);
void EffectSsSolderSrchBall_Spawn(PlayState* play, Vec3f* pos, Vec3f* velocity, Vec3f* accel, s16 unused,
                                  s16* linkDetected);
void EffectSsKakera_Spawn(PlayState* play, Vec3f* pos, Vec3f* velocity, Vec3f* arg3, s16 gravity, s16 arg5,
                          s16 arg6, s16 arg7, s16 arg8, s16 scale, s16 arg10, s16 arg11, s32 life, s16 colorIdx,
                          s16 objId, Gfx* dList);
void EffectSsIcePiece_Spawn(PlayState* play, Vec3f* pos, f32 scale, Vec3f* velocity, Vec3f* accel, s32 life);
void EffectSsIcePiece_SpawnBurst(PlayState* play, Vec3f* refPos, f32 scale);
void EffectSsEnIce_SpawnFlyingVec3f(PlayState* play, Actor* actor, Vec3f* pos, s16 primR, s16 primG, s16 primB,
                                    s16 primA, s16 envR, s16 envG, s16 envB, f32 scale);
void EffectSsEnIce_SpawnFlyingVec3s(PlayState* play, Actor* actor, Vec3s* pos, s16 primR, s16 primG, s16 primB,
                                    s16 primA, s16 envR, s16 envG, s16 envB, f32 scale);
void EffectSsEnIce_Spawn(PlayState* play, Vec3f* pos, f32 scale, Vec3f* velocity, Vec3f* accel,
                         Color_RGBA8* primColor, Color_RGBA8* envColor, s32 life);
void EffectSsFireTail_Spawn(PlayState* play, Actor* actor, Vec3f* pos, f32 scale, Vec3f* arg4, s16 arg5,
                            Color_RGBA8* primColor, Color_RGBA8* envColor, s16 type, s16 bodyPart, s32 life);
void EffectSsFireTail_SpawnFlame(PlayState* play, Actor* actor, Vec3f* pos, f32 arg3, s16 bodyPart,
                                 f32 colorIntensity);
void EffectSsFireTail_SpawnFlameOnPlayer(PlayState* play, f32 scale, s16 bodyPart, f32 colorIntensity);
void EffectSsEnFire_SpawnVec3f(PlayState* play, Actor* actor, Vec3f* pos, s16 scale, s16 unk_12, s16 flags,
                               s16 bodyPart);
void EffectSsEnFire_SpawnVec3s(PlayState* play, Actor* actor, Vec3s* vec, s16 scale, s16 arg4, s16 flags,
                               s16 bodyPart);
void EffectSsExtra_Spawn(PlayState* play, Vec3f* pos, Vec3f* velocity, Vec3f* accel, s16 scale, s16 scoreIdx);
void EffectSsFCircle_Spawn(PlayState* play, Actor* actor, Vec3f* pos, s16 radius, s16 height);
void EffectSsDeadDb_Spawn(PlayState* play, Vec3f* pos, Vec3f* velocity, Vec3f* accel, s16 scale, s16 scaleStep,
                          s16 primR, s16 primG, s16 primB, s16 primA, s16 envR, s16 envG, s16 envB, s16 unused,
                          s32 arg14, s16 playSound);
void EffectSsDeadDd_Spawn(PlayState* play, Vec3f* pos, Vec3f* velocity, Vec3f* accel, s16 scale, s16 scaleStep,
                          s16 primR, s16 primG, s16 primB, s16 alpha, s16 envR, s16 envG, s16 envB, s16 alphaStep,
                          s32 life);
void EffectSsDeadDd_SpawnRandYellow(PlayState* play, Vec3f* pos, s16 scale, s16 scaleStep, f32 randPosScale,
                                    s32 randIter, s32 life);
void EffectSsDeadDs_Spawn(PlayState* play, Vec3f* pos, Vec3f* velocity, Vec3f* accel, s16 scale, s16 scaleStep,
                          s16 alpha, s32 life);
void EffectSsDeadDs_SpawnStationary(PlayState* play, Vec3f* pos, s16 scale, s16 scaleStep, s16 alpha,
                                    s32 life);
void EffectSsDeadSound_Spawn(PlayState* play, Vec3f* pos, Vec3f* velocity, Vec3f* accel, u16 sfxId,
                             s16 lowerPriority, s16 repeatMode, s32 life);
void EffectSsDeadSound_SpawnStationary(PlayState* play, Vec3f* pos, u16 sfxId, s16 lowerPriority,
                                       s16 repeatMode, s32 life);
void EffectSsIceSmoke_Spawn(PlayState* play, Vec3f* pos, Vec3f* velocity, Vec3f* accel, s16 scale);
void FlagSet_Update(PlayState* play);
void Overlay_LoadGameState(GameStateOverlay* overlayEntry);
void Overlay_FreeGameState(GameStateOverlay* overlayEntry);
void ActorShape_Init(ActorShape* shape, f32 yOffset, ActorShadowFunc shadowDraw, f32 shadowScale);
void ActorShadow_DrawCircle(Actor* actor, Lights* lights, PlayState* play);
void ActorShadow_DrawWhiteCircle(Actor* actor, Lights* lights, PlayState* play);
void ActorShadow_DrawHorse(Actor* actor, Lights* lights, PlayState* play);
void ActorShadow_DrawFeet(Actor* actor, Lights* lights, PlayState* play);
void Actor_SetFeetPos(Actor* actor, s32 limbIndex, s32 leftFootIndex, Vec3f* leftFootPos, s32 rightFootIndex,
                      Vec3f* rightFootPos);
void func_8002BE04(PlayState* play, Vec3f* arg1, Vec3f* arg2, f32* arg3);
void func_8002C124(TargetContext* targetCtx, PlayState* play);
s32 Flags_GetSwitch(PlayState* play, s32 flag);
void Flags_SetSwitch(PlayState* play, s32 flag);
void Flags_UnsetSwitch(PlayState* play, s32 flag);
s32 Flags_GetUnknown(PlayState* play, s32 flag);
void Flags_SetUnknown(PlayState* play, s32 flag);
void Flags_UnsetUnknown(PlayState* play, s32 flag);
s32 Flags_GetTreasure(PlayState* play, s32 flag);
void Flags_SetTreasure(PlayState* play, s32 flag);
s32 Flags_GetClear(PlayState* play, s32 flag);
void Flags_SetClear(PlayState* play, s32 flag);
void Flags_UnsetClear(PlayState* play, s32 flag);
s32 Flags_GetTempClear(PlayState* play, s32 flag);
void Flags_SetTempClear(PlayState* play, s32 flag);
void Flags_UnsetTempClear(PlayState* play, s32 flag);
s32 Flags_GetCollectible(PlayState* play, s32 flag);
void Flags_SetCollectible(PlayState* play, s32 flag);
void TitleCard_InitBossName(PlayState* play, TitleCardContext* titleCtx, void* texture, s16 x, s16 y, u8 width,
                            u8 height, s16 hasTranslation);
void TitleCard_InitPlaceName(PlayState* play, TitleCardContext* titleCtx, void* texture, s32 x, s32 y,
                             s32 width, s32 height, s32 delay);
s32 func_8002D53C(PlayState* play, TitleCardContext* titleCtx);
void Actor_Kill(Actor* actor);
void Actor_SetFocus(Actor* actor, f32 offset);
void Actor_SetScale(Actor* actor, f32 scale);
void Actor_SetObjectDependency(PlayState* play, Actor* actor);
void func_8002D7EC(Actor* actor);
void func_8002D868(Actor* actor);
void Actor_MoveForward(Actor* actor);
void func_8002D908(Actor* actor);
void func_8002D97C(Actor* actor);
void func_8002D9A4(Actor* actor, f32 arg1);
s16 Actor_WorldYawTowardActor(Actor* actorA, Actor* actorB);
s16 Actor_WorldYawTowardPoint(Actor* actor, Vec3f* refPoint);
f32 Actor_WorldDistXYZToActor(Actor* actorA, Actor* actorB);
f32 Actor_WorldDistXYZToPoint(Actor* actor, Vec3f* refPoint);
s16 Actor_WorldPitchTowardActor(Actor* actorA, Actor* actorB);
s16 Actor_WorldPitchTowardPoint(Actor* actor, Vec3f* refPoint);
f32 Actor_WorldDistXZToActor(Actor* actorA, Actor* actorB);
f32 Actor_WorldDistXZToPoint(Actor* actor, Vec3f* refPoint);
void func_8002DBD0(Actor* actor, Vec3f* result, Vec3f* arg2);
f32 Actor_HeightDiff(Actor* actorA, Actor* actorB);
f32 Player_GetHeight(Player* player);
f32 func_8002DCE4(Player* player);
s32 func_8002DD6C(Player* player);
s32 func_8002DD78(Player* player);
s32 func_8002DDE4(PlayState* play);
s32 func_8002DDF4(PlayState* play);
void func_8002DE04(PlayState* play, Actor* actorA, Actor* actorB);
void func_8002DE74(PlayState* play, Player* player);
void Actor_MountHorse(PlayState* play, Player* player, Actor* horse);
s32 func_8002DEEC(Player* player);
void func_8002DF18(PlayState* play, Player* player);
s32 func_8002DF38(PlayState* play, Actor* actor, u8 csMode);
s32 func_8002DF54(PlayState* play, Actor* actor, u8 arg2);
void func_8002DF90(DynaPolyActor* dynaActor);
void func_8002DFA4(DynaPolyActor* dynaActor, f32 arg1, s16 arg2);
s32 Player_IsFacingActor(Actor* actor, s16 angle, PlayState* play);
s32 Actor_ActorBIsFacingActorA(Actor* actorA, Actor* actorB, s16 angle);
s32 Actor_IsFacingPlayer(Actor* actor, s16 angle);
s32 Actor_ActorAIsFacingActorB(Actor* actorA, Actor* actorB, s16 angle);
s32 Actor_IsFacingAndNearPlayer(Actor* actor, f32 range, s16 angle);
s32 Actor_ActorAIsFacingAndNearActorB(Actor* actorA, Actor* actorB, f32 range, s16 angle);
void Actor_UpdateBgCheckInfo(PlayState* play, Actor* actor, f32 wallCheckHeight, f32 wallCheckRadius,
                             f32 ceilingCheckHeight, s32 flags);
Hilite* func_8002EABC(Vec3f* object, Vec3f* eye, Vec3f* lightDir, GraphicsContext* gfxCtx);
Hilite* func_8002EB44(Vec3f* object, Vec3f* eye, Vec3f* lightDir, GraphicsContext* gfxCtx);
void func_8002EBCC(Actor* actor, PlayState* play, s32 flag);
void func_8002ED80(Actor* actor, PlayState* play, s32 flag);
PosRot* Actor_GetFocus(PosRot* arg0, Actor* actor);
PosRot* Actor_GetWorld(PosRot* arg0, Actor* actor);
PosRot* Actor_GetWorldPosShapeRot(PosRot* arg0, Actor* actor);
s32 func_8002F0C8(Actor* actor, Player* player, s32 arg2);
u32 Actor_ProcessTalkRequest(Actor* actor, PlayState* play);
s32 func_8002F1C4(Actor* actor, PlayState* play, f32 arg2, f32 arg3, u32 arg4);
s32 func_8002F298(Actor* actor, PlayState* play, f32 arg2, u32 arg3);
s32 func_8002F2CC(Actor* actor, PlayState* play, f32 arg2);
s32 func_8002F2F4(Actor* actor, PlayState* play);
u32 Actor_TextboxIsClosing(Actor* actor, PlayState* play);
s8 func_8002F368(PlayState* play);
void Actor_GetScreenPos(PlayState* play, Actor* actor, s16* x, s16* y);
u32 Actor_HasParent(Actor* actor, PlayState* play);
// TODO: Rename the follwing 3 functions using whatever scheme we use when we rename func_8002F434 and func_8002F554.
s32 GiveItemEntryWithoutActor(PlayState* play, GetItemEntry getItemEntry);
s32 GiveItemEntryFromActor(Actor* actor, PlayState* play, GetItemEntry getItemEntry, f32 xzRange, f32 yRange);
void GiveItemEntryFromActorWithFixedRange(Actor* actor, PlayState* play, GetItemEntry getItemEntry);
s32 func_8002F434(Actor* actor, PlayState* play, s32 getItemId, f32 xzRange, f32 yRange);
void func_8002F554(Actor* actor, PlayState* play, s32 getItemId);
void func_8002F580(Actor* actor, PlayState* play);
u32 Actor_HasNoParent(Actor* actor, PlayState* play);
void func_8002F5C4(Actor* actorA, Actor* actorB, PlayState* play);
void func_8002F5F0(Actor* actor, PlayState* play);
s32 Actor_IsMounted(PlayState* play, Actor* horse);
u32 Actor_SetRideActor(PlayState* play, Actor* horse, s32 arg2);
s32 Actor_NotMounted(PlayState* play, Actor* horse);
void func_8002F698(PlayState* play, Actor* actor, f32 arg2, s16 arg3, f32 arg4, u32 arg5, u32 arg6);
void func_8002F6D4(PlayState* play, Actor* actor, f32 arg2, s16 arg3, f32 arg4, u32 arg5);
void func_8002F71C(PlayState* play, Actor* actor, f32 arg2, s16 arg3, f32 arg4);
void func_8002F758(PlayState* play, Actor* actor, f32 arg2, s16 arg3, f32 arg4, u32 arg5);
void func_8002F7A0(PlayState* play, Actor* actor, f32 arg2, s16 arg3, f32 arg4);
void Player_PlaySfx(Actor* actor, u16 sfxId);
void Audio_PlayActorSound2(Actor* actor, u16 sfxId);
void func_8002F850(PlayState* play, Actor* actor);
void func_8002F8F0(Actor* actor, u16 sfxId);
void func_8002F91C(Actor* actor, u16 sfxId);
void func_8002F948(Actor* actor, u16 sfxId);
void func_8002F974(Actor* actor, u16 sfxId);
void func_8002F994(Actor* actor, s32 arg1);
s32 func_8002F9EC(PlayState* play, Actor* actor, CollisionPoly* poly, s32 bgId, Vec3f* pos);
void Actor_DisableLens(PlayState* play);
void func_800304DC(PlayState* play, ActorContext* actorCtx, ActorEntry* actorEntry);
void Actor_UpdateAll(PlayState* play, ActorContext* actorCtx);
s32 func_800314D4(PlayState* play, Actor* actorB, Vec3f* arg2, f32 arg3);
void func_800315AC(PlayState* play, ActorContext* actorCtx);
void func_80031A28(PlayState* play, ActorContext* actorCtx);
void func_80031B14(PlayState* play, ActorContext* actorCtx);
void func_80031C3C(ActorContext* actorCtx, PlayState* play);
Actor* Actor_Spawn(ActorContext* actorCtx, PlayState* play, s16 actorId, f32 posX, f32 posY, f32 posZ,
                   s16 rotX, s16 rotY, s16 rotZ, s16 params, s16 canRandomize);
Actor* Actor_SpawnAsChild(ActorContext* actorCtx, Actor* parent, PlayState* play, s16 actorId, f32 posX,
                          f32 posY, f32 posZ, s16 rotX, s16 rotY, s16 rotZ, s16 params);
void Actor_SpawnTransitionActors(PlayState* play, ActorContext* actorCtx);
Actor* Actor_SpawnEntry(ActorContext* actorCtx, ActorEntry* actorEntry, PlayState* play);
Actor* Actor_Delete(ActorContext* actorCtx, Actor* actor, PlayState* play);
Actor* func_80032AF0(PlayState* play, ActorContext* actorCtx, Actor** actorPtr, Player* player);
Actor* Actor_Find(ActorContext* actorCtx, s32 actorId, s32 actorCategory);
void Enemy_StartFinishingBlow(PlayState* play, Actor* actor);
s16 func_80032CB4(s16* arg0, s16 arg1, s16 arg2, s16 arg3);
void BodyBreak_Alloc(BodyBreak* bodyBreak, s32 count, PlayState* play);
void BodyBreak_SetInfo(BodyBreak* bodyBreak, s32 limbIndex, s32 minLimbIndex, s32 maxLimbIndex, u32 count, Gfx** dList,
                       s16 objectId);
s32 BodyBreak_SpawnParts(Actor* actor, BodyBreak* bodyBreak, PlayState* play, s16 type);
void Actor_SpawnFloorDustRing(PlayState* play, Actor* actor, Vec3f* posXZ, f32 radius, s32 amountMinusOne,
                              f32 randAccelWeight, s16 scale, s16 scaleStep, u8 useLighting);
void func_80033480(PlayState* play, Vec3f* posBase, f32 randRangeDiameter, s32 amountMinusOne, s16 scaleBase,
                   s16 scaleStep, u8 arg6);
Actor* Actor_GetCollidedExplosive(PlayState* play, Collider* collider);
Actor* func_80033684(PlayState* play, Actor* explosiveActor);
Actor* Actor_GetProjectileActor(PlayState* play, Actor* refActor, f32 radius);
void Actor_ChangeCategory(PlayState* play, ActorContext* actorCtx, Actor* actor, u8 actorCategory);
void Actor_SetTextWithPrefix(PlayState* play, Actor* actor, s16 textIdLower);
s16 Actor_TestFloorInDirection(Actor* actor, PlayState* play, f32 distance, s16 angle);
s32 Actor_IsTargeted(PlayState* play, Actor* actor);
s32 Actor_OtherIsTargeted(PlayState* play, Actor* actor);
f32 func_80033AEC(Vec3f* arg0, Vec3f* arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5);
void func_80033C30(Vec3f* arg0, Vec3f* arg1, u8 alpha, PlayState* play);
void func_80033DB8(PlayState* play, s16 arg1, s16 arg2);
void func_80033E1C(PlayState* play, s16 arg1, s16 arg2, s16 arg3);
void func_80033E88(Actor* actor, PlayState* play, s16 arg2, s16 arg3);
f32 Rand_ZeroFloat(f32 f);
f32 Rand_CenteredFloat(f32 f);
void Actor_DrawDoorLock(PlayState* play, s32 arg1, s32 arg2);
void func_8003424C(PlayState* play, Vec3f* arg1);
void Actor_SetColorFilter(Actor* actor, s16 colorFlag, s16 colorIntensityMax, s16 xluFlag, s16 duration);
Hilite* func_800342EC(Vec3f* object, PlayState* play);
Hilite* func_8003435C(Vec3f* object, PlayState* play);
s32 Npc_UpdateTalking(PlayState* play, Actor* actor, s16* talkState, f32 interactRange,
                      NpcGetTextIdFunc getTextId, NpcUpdateTalkStateFunc updateTalkState);
s16 Npc_GetTrackingPresetMaxPlayerYaw(s16 presetIndex);
void Npc_TrackPoint(Actor* actor, NpcInteractInfo* interactInfo, s16 presetIndex, s16 trackingMode);
void func_80034BA0(PlayState* play, SkelAnime* skelAnime, OverrideLimbDraw overrideLimbDraw,
                   PostLimbDraw postLimbDraw, Actor* actor, s16 alpha);
void func_80034CC4(PlayState* play, SkelAnime* skelAnime, OverrideLimbDraw overrideLimbDraw,
                   PostLimbDraw postLimbDraw, Actor* actor, s16 alpha);
s16 func_80034DD4(Actor* actor, PlayState* play, s16 arg2, f32 arg3);
void Animation_ChangeByInfo(SkelAnime* skelAnime, AnimationInfo* animationInfo, s32 index);
void func_80034F54(PlayState* play, s16* arg1, s16* arg2, s32 arg3);
void Actor_Noop(Actor* actor, PlayState* play);
void Gfx_DrawDListOpa(PlayState* play, Gfx* dlist);
void Gfx_DrawDListXlu(PlayState* play, Gfx* dlist);
Actor* Actor_FindNearby(PlayState* play, Actor* refActor, s16 actorId, u8 actorCategory, f32 range);
s32 func_800354B4(PlayState* play, Actor* actor, f32 range, s16 arg3, s16 arg4, s16 arg5);
void func_8003555C(PlayState* play, Vec3f* pos, Vec3f* velocity, Vec3f* accel);
void func_800355B8(PlayState* play, Vec3f* pos);
u8 func_800355E4(PlayState* play, Collider* collider);
u8 Actor_ApplyDamage(Actor* actor);
void Actor_SetDropFlag(Actor* actor, ColliderInfo* colBody, s32 freezeFlag);
void Actor_SetDropFlagJntSph(Actor* actor, ColliderJntSph* colBody, s32 freezeFlag);
void func_80035844(Vec3f* arg0, Vec3f* arg1, Vec3s* arg2, s32 arg3);
Actor* func_800358DC(Actor* actor, Vec3f* spawnPos, Vec3s* spawnRot, f32* arg3, s32 timer, s16* unused,
                     PlayState* play, s16 params, s32 arg8);
void func_800359B8(Actor* actor, s16 arg1, Vec3s* arg2);
s32 Flags_GetEventChkInf(s32 flag);
void Flags_SetEventChkInf(s32 flag);
void Flags_UnsetEventChkInf(s32 flag);
s32 Flags_GetItemGetInf(s32 flag);
void Flags_SetItemGetInf(s32 flag);
void Flags_UnsetItemGetInf(s32 flag);
s32 Flags_GetInfTable(s32 flag);
void Flags_SetInfTable(s32 flag);
void Flags_UnsetInfTable(s32 flag);
s32 Flags_GetEventInf(s32 flag);
void Flags_SetEventInf(s32 flag);
void Flags_UnsetEventInf(s32 flag);
s32 Flags_GetRandomizerInf(RandomizerInf flag);
void Flags_SetRandomizerInf(RandomizerInf flag);
void Flags_UnsetRandomizerInf(RandomizerInf flag);
u16 func_80037C30(PlayState* play, s16 arg1);
s32 func_80037D98(PlayState* play, Actor* actor, s16 arg2, s32* arg3);
s32 func_80038290(PlayState* play, Actor* actor, Vec3s* arg2, Vec3s* arg3, Vec3f arg4);
GetItemEntry GetChestGameRandoGetItem(s8 room, s16 ogDrawId, PlayState* play);
s16 GetChestGameRandoGiDrawId(s8 room, s16 ogDrawId, PlayState* play);

// ? func_80038600(?);
u16 DynaSSNodeList_GetNextNodeIdx(DynaSSNodeList*);
void func_80038A28(CollisionPoly* poly, f32 tx, f32 ty, f32 tz, MtxF* dest);
f32 CollisionPoly_GetPointDistanceFromPlane(CollisionPoly* poly, Vec3f* point);
CollisionHeader* BgCheck_GetCollisionHeader(CollisionContext* colCtx, s32 bgId);
void CollisionPoly_GetVerticesByBgId(CollisionPoly* poly, s32 bgId, CollisionContext* colCtx, Vec3f* dest);
s32 BgCheck_CheckStaticCeiling(StaticLookup* lookup, u16 xpFlags, CollisionContext* colCtx, f32* outY, Vec3f* pos,
                               f32 checkHeight, CollisionPoly** outPoly);
s32 BgCheck_CheckLineAgainstSSList(SSList* headNodeId, CollisionContext* colCtx, u16 xpFlags1, u16 xpFlags2,
                                   Vec3f* posA, Vec3f* posB, Vec3f* outPos, CollisionPoly** outPoly, f32* outDistSq,
                                   f32 chkDist, s32 bccFlags);
void BgCheck_GetStaticLookupIndicesFromPos(CollisionContext* colCtx, Vec3f* pos, Vec3i* arg2);
void BgCheck_Allocate(CollisionContext* colCtx, PlayState* play, CollisionHeader* colHeader);
s32 BgCheck_PosInStaticBoundingBox(CollisionContext* colCtx, Vec3f* pos);
f32 BgCheck_EntityRaycastFloor1(CollisionContext* colCtx, CollisionPoly** outPoly, Vec3f* pos);
f32 BgCheck_EntityRaycastFloor2(PlayState* play, CollisionContext* colCtx, CollisionPoly** outPoly,
                                Vec3f* pos);
f32 BgCheck_EntityRaycastFloor3(CollisionContext* colCtx, CollisionPoly** outPoly, s32* bgId, Vec3f* pos);
f32 BgCheck_EntityRaycastFloor4(CollisionContext* colCtx, CollisionPoly** outPoly, s32* bgId, Actor* actor,
                                Vec3f* arg4);
f32 BgCheck_EntityRaycastFloor5(PlayState* play, CollisionContext* colCtx, CollisionPoly** outPoly, s32* bgId,
                                Actor* actor, Vec3f* pos);
f32 BgCheck_EntityRaycastFloor6(CollisionContext* colCtx, CollisionPoly** outPoly, s32* bgId, Actor* actor, Vec3f* pos,
                                f32 chkDist);
f32 BgCheck_EntityRaycastFloor7(CollisionContext* colCtx, CollisionPoly** outPoly, s32* bgId, Actor* actor, Vec3f* pos);
f32 BgCheck_AnyRaycastFloor1(CollisionContext* colCtx, CollisionPoly* outPoly, Vec3f* pos);
f32 BgCheck_AnyRaycastFloor2(CollisionContext* colCtx, CollisionPoly* outPoly, s32* bgId, Vec3f* pos);
f32 BgCheck_CameraRaycastFloor2(CollisionContext* colCtx, CollisionPoly** outPoly, s32* bgId, Vec3f* pos);
f32 BgCheck_EntityRaycastFloor8(CollisionContext* colCtx, CollisionPoly** outPoly, s32* bgId, Actor* actor, Vec3f* pos);
f32 BgCheck_EntityRaycastFloor9(CollisionContext* colCtx, CollisionPoly** outPoly, s32* bgId, Vec3f* pos);
s32 BgCheck_CheckWallImpl(CollisionContext* colCtx, u16 xpFlags, Vec3f* posResult, Vec3f* posNext, Vec3f* posPrev,
                          f32 radius, CollisionPoly** outPoly, s32* outBgId, Actor* actor, f32 checkHeight, u8 argA);
s32 BgCheck_EntitySphVsWall1(CollisionContext* colCtx, Vec3f* posResult, Vec3f* posNext, Vec3f* posPrev, f32 radius,
                             CollisionPoly** outPoly, f32 checkHeight);
s32 BgCheck_EntitySphVsWall2(CollisionContext* colCtx, Vec3f* posResult, Vec3f* posNext, Vec3f* posPrev, f32 radius,
                             CollisionPoly** outPoly, s32* outBgId, f32 checkHeight);
s32 BgCheck_EntitySphVsWall3(CollisionContext* colCtx, Vec3f* posResult, Vec3f* posNext, Vec3f* posPrev, f32 radius,
                             CollisionPoly** outPoly, s32* outBgId, Actor* actor, f32 checkHeight);
s32 BgCheck_EntitySphVsWall4(CollisionContext* colCtx, Vec3f* posResult, Vec3f* posNext, Vec3f* posPrev, f32 radius,
                             CollisionPoly** outPoly, s32* outBgId, Actor* actor, f32 checkHeight);
s32 BgCheck_AnyCheckCeiling(CollisionContext* colCtx, f32* outY, Vec3f* pos, f32 checkHeight);
s32 BgCheck_EntityCheckCeiling(CollisionContext* colCtx, f32* arg1, Vec3f* arg2, f32 arg3, CollisionPoly** outPoly,
                               s32* outBgId, Actor* actor);
s32 BgCheck_CheckLineImpl(CollisionContext* colCtx, u16 xpFlags1, u16 xpFlags2, Vec3f* posA, Vec3f* posB,
                          Vec3f* posResult, CollisionPoly** outPoly, s32* bgId, Actor* actor, f32 chkDist,
                          u32 bccFlags);
s32 BgCheck_CameraLineTest1(CollisionContext* colCtx, Vec3f* posA, Vec3f* posB, Vec3f* posResult,
                            CollisionPoly** outPoly, s32 chkWall, s32 chkFloor, s32 chkCeil, s32 chkOneFace, s32* bgId);
s32 BgCheck_CameraLineTest2(CollisionContext* colCtx, Vec3f* posA, Vec3f* posB, Vec3f* posResult,
                            CollisionPoly** outPoly, s32 chkWall, s32 chkFloor, s32 chkCeil, s32 chkOneFace, s32* bgId);
s32 BgCheck_EntityLineTest1(CollisionContext* colCtx, Vec3f* posA, Vec3f* posB, Vec3f* posResult,
                            CollisionPoly** outPoly, s32 chkWall, s32 chkFloor, s32 chkCeil, s32 chkOneFace, s32* bgId);
s32 BgCheck_EntityLineTest2(CollisionContext* colCtx, Vec3f* posA, Vec3f* posB, Vec3f* posResult,
                            CollisionPoly** outPoly, s32 chkWall, s32 chkFloor, s32 chkCeil, s32 chkOneFace, s32* bgId,
                            Actor* actor);
s32 BgCheck_EntityLineTest3(CollisionContext* colCtx, Vec3f* posA, Vec3f* posB, Vec3f* posResult,
                            CollisionPoly** outPoly, s32 chkWall, s32 chkFloor, s32 chkCeil, s32 chkOneFace, s32* bgId,
                            Actor* actor, f32 chkDist);
s32 BgCheck_ProjectileLineTest(CollisionContext* colCtx, Vec3f* posA, Vec3f* posB, Vec3f* posResult,
                               CollisionPoly** outPoly, s32 chkWall, s32 chkFloor, s32 chkCeil, s32 chkOneFace,
                               s32* bgId);
s32 BgCheck_AnyLineTest1(CollisionContext* colCtx, Vec3f* posA, Vec3f* posB, Vec3f* posResult, CollisionPoly** outPoly,
                         s32 chkOneFace);
s32 BgCheck_AnyLineTest2(CollisionContext* colCtx, Vec3f* posA, Vec3f* posB, Vec3f* posResult, CollisionPoly** outPoly,
                         s32 chkWall, s32 chkFloor, s32 chkCeil, s32 chkOneFace);
s32 BgCheck_AnyLineTest3(CollisionContext* colCtx, Vec3f* posA, Vec3f* posB, Vec3f* posResult, CollisionPoly** outPoly,
                         s32 chkWall, s32 chkFloor, s32 chkCeil, s32 chkOneFace, s32* bgId);
s32 BgCheck_SphVsFirstPoly(CollisionContext* colCtx, Vec3f* center, f32 radius);
void SSNodeList_Initialize(SSNodeList*);
void SSNodeList_Alloc(PlayState* play, SSNodeList* this, s32 tblMax, s32 numPolys);
u16 SSNodeList_GetNextNodeIdx(SSNodeList* this);
s32 DynaPoly_IsBgIdBgActor(s32 bgId);
void DynaPoly_Init(PlayState* play, DynaCollisionContext* dyna);
void DynaPoly_Alloc(PlayState* play, DynaCollisionContext* dyna);
void func_8003EBF8(PlayState* play, DynaCollisionContext* dyna, s32 bgId);
void func_8003EC50(PlayState* play, DynaCollisionContext* dyna, s32 bgId);
void func_8003ECA8(PlayState* play, DynaCollisionContext* dyna, s32 bgId);
s32 DynaPoly_SetBgActor(PlayState* play, DynaCollisionContext* dyna, Actor* actor, CollisionHeader* colHeader);
DynaPolyActor* DynaPoly_GetActor(CollisionContext* colCtx, s32 bgId);
void DynaPoly_DeleteBgActor(PlayState* play, DynaCollisionContext* dyna, s32 bgId);
void func_8003EE6C(PlayState* play, DynaCollisionContext* dyna);
void func_8003F8EC(PlayState* play, DynaCollisionContext* dyna, Actor* actor);
void DynaPoly_Setup(PlayState* play, DynaCollisionContext* dyna);
void DynaPoly_UpdateBgActorTransforms(PlayState* play, DynaCollisionContext* dyna);
f32 BgCheck_RaycastFloorDyna(DynaRaycast* dynaRaycast);
s32 BgCheck_SphVsDynaWall(CollisionContext* colCtx, u16 xpFlags, f32* outX, f32* outZ, Vec3f* pos, f32 radius,
                          CollisionPoly** outPoly, s32* outBgId, Actor* actor);
s32 BgCheck_CheckDynaCeiling(CollisionContext* colCtx, u16 xpFlags, f32* outY, Vec3f* pos, f32 chkDist,
                             CollisionPoly** outPoly, s32* outBgId, Actor* actor);
s32 BgCheck_CheckLineAgainstDyna(CollisionContext* colCtx, u16 xpFlags, Vec3f* posA, Vec3f* posB, Vec3f* posResult,
                                 CollisionPoly** outPoly, f32* distSq, s32* outBgId, Actor* actor, f32 chkDist,
                                 s32 bccFlags);
s32 BgCheck_SphVsFirstDynaPoly(CollisionContext* colCtx, u16 xpFlags, CollisionPoly** outPoly, s32* outBgId,
                               Vec3f* center, f32 radius, Actor* actor, u16 bciFlags);
void CollisionHeader_GetVirtual(void* colHeader, CollisionHeader** dest);
void func_800418D0(CollisionContext* colCtx, PlayState* play);
void BgCheck_ResetPolyCheckTbl(SSNodeList* nodeList, s32 numPolys);
u32 SurfaceType_GetCamDataIndex(CollisionContext* colCtx, CollisionPoly* poly, s32 bgId);
u16 func_80041A4C(CollisionContext* colCtx, u32 camId, s32 bgId);
u16 SurfaceType_GetCameraSType(CollisionContext* colCtx, CollisionPoly* poly, s32 bgId);
u16 SurfaceType_GetNumCameras(CollisionContext* colCtx, CollisionPoly* poly, s32 bgId);
Vec3s* func_80041C10(CollisionContext* colCtx, s32 camId, s32 bgId);
Vec3s* SurfaceType_GetCamPosData(CollisionContext* colCtx, CollisionPoly* poly, s32 bgId);
u32 SurfaceType_GetSceneExitIndex(CollisionContext* colCtx, CollisionPoly* poly, s32 bgId);
u32 func_80041D4C(CollisionContext* colCtx, CollisionPoly* poly, s32 bgId);
u32 func_80041D70(CollisionContext* colCtx, CollisionPoly* poly, s32 bgId);
u32 func_80041D94(CollisionContext* colCtx, CollisionPoly* poly, s32 bgId);
s32 func_80041DB8(CollisionContext* colCtx, CollisionPoly* poly, s32 bgId);
s32 func_80041DE4(CollisionContext* colCtx, CollisionPoly* poly, s32 bgId);
s32 func_80041E18(CollisionContext* colCtx, CollisionPoly* poly, s32 bgId);
s32 func_80041E4C(CollisionContext* colCtx, CollisionPoly* poly, s32 bgId);
s32 func_80041E80(CollisionContext* colCtx, CollisionPoly* poly, s32 bgId);
u32 func_80041EA4(CollisionContext* colCtx, CollisionPoly* poly, s32 bgId);
u32 func_80041EC8(CollisionContext* colCtx, CollisionPoly* poly, s32 bgId);
u32 SurfaceType_IsHorseBlocked(CollisionContext* colCtx, CollisionPoly* poly, s32 bgId);
u32 func_80041F10(CollisionContext* colCtx, CollisionPoly* poly, s32 bgId);
u16 SurfaceType_GetSfx(CollisionContext* colCtx, CollisionPoly* poly, s32 bgId);
u32 SurfaceType_GetSlope(CollisionContext* colCtx, CollisionPoly* poly, s32 bgId);
u32 SurfaceType_GetLightSettingIndex(CollisionContext* colCtx, CollisionPoly* poly, s32 bgId);
u32 SurfaceType_GetEcho(CollisionContext* colCtx, CollisionPoly* poly, s32 bgId);
u32 SurfaceType_IsHookshotSurface(CollisionContext* colCtx, CollisionPoly* poly, s32 bgId);
s32 SurfaceType_IsIgnoredByEntities(CollisionContext* colCtx, CollisionPoly* poly, s32 bgId);
s32 SurfaceType_IsIgnoredByProjectiles(CollisionContext* colCtx, CollisionPoly* poly, s32 bgId);
s32 SurfaceType_IsConveyor(CollisionContext* colCtx, CollisionPoly* poly, s32 bgId);
u32 SurfaceType_GetConveyorSpeed(CollisionContext* colCtx, CollisionPoly* poly, s32 bgId);
u32 SurfaceType_GetConveyorDirection(CollisionContext* colCtx, CollisionPoly* poly, s32 bgId);
u32 SurfaceType_IsWallDamage(CollisionContext* colCtx, CollisionPoly* poly, s32 bgId);
s32 WaterBox_GetSurface1(PlayState* play, CollisionContext* colCtx, f32 x, f32 z, f32* ySurface,
                         WaterBox** outWaterBox);
s32 WaterBox_GetSurface2(PlayState* play, CollisionContext* colCtx, Vec3f* pos, f32 surfaceChkDist,
                         WaterBox** outWaterBox);
s32 WaterBox_GetSurfaceImpl(PlayState* play, CollisionContext* colCtx, f32 x, f32 z, f32* ySurface,
                            WaterBox** outWaterBox);
u32 WaterBox_GetCamDataIndex(CollisionContext* colCtx, WaterBox* waterBox);
u16 WaterBox_GetCameraSType(CollisionContext* colCtx, WaterBox* waterBox);
u32 WaterBox_GetLightSettingIndex(CollisionContext* colCtx, WaterBox* waterBox);
s32 func_80042708(CollisionPoly* polyA, CollisionPoly* polyB, Vec3f* point, Vec3f* closestPoint);
s32 func_800427B4(CollisionPoly* polyA, CollisionPoly* polyB, Vec3f* pointA, Vec3f* pointB, Vec3f* closestPoint);
void BgCheck_DrawDynaCollision(PlayState*, CollisionContext*);
void BgCheck_DrawStaticCollision(PlayState*, CollisionContext*);
void func_80043334(CollisionContext* colCtx, Actor* actor, s32 bgId);
s32 func_800433A4(CollisionContext* colCtx, s32 bgId, Actor* actor);
void DynaPolyActor_Init(DynaPolyActor* dynaActor, s32 flags);
void func_800434A0(DynaPolyActor* dynaActor);
void func_800434A8(DynaPolyActor* dynaActor);
void func_800434C8(CollisionContext* colCtx, s32 floorBgId);
void func_80043508(CollisionContext* colCtx, s32 floorBgId);
void func_80043538(DynaPolyActor* dynaActor);
s32 func_80043548(DynaPolyActor* dynaActor);
s32 func_8004356C(DynaPolyActor* dynaActor);
s32 func_80043590(DynaPolyActor* dynaActor);
s32 func_800435B4(DynaPolyActor* dynaActor);
s32 func_800435D8(PlayState* play, DynaPolyActor* dynaActor, s16 arg2, s16 arg3, s16 arg4);
void Camera_Init(Camera* camera, View* view, CollisionContext* colCtx, PlayState* play);
void Camera_InitPlayerSettings(Camera* camera, Player* player);
s16 Camera_ChangeStatus(Camera* camera, s16 status);
Vec3s Camera_Update(Camera* camera);
void Camera_Finish(Camera* camera);
s32 Camera_ChangeMode(Camera* camera, s16 mode);
s32 Camera_CheckValidMode(Camera* camera, s16 mode);
s32 Camera_ChangeSetting(Camera* camera, s16 setting);
s32 Camera_ChangeDataIdx(Camera* camera, s32 camDataIdx);
s16 Camera_GetInputDirYaw(Camera* camera);
Vec3s* Camera_GetCamDir(Vec3s* dir, Camera* camera);
s16 Camera_GetCamDirPitch(Camera* camera);
s16 Camera_GetCamDirYaw(Camera* camera);
s32 Camera_AddQuake(Camera* camera, s32 arg1, s16 y, s32 countdown);
s32 Camera_SetParam(Camera* camera, s32 param, void* value);
s32 func_8005AC48(Camera* camera, s16 arg1);
s16 func_8005ACFC(Camera* camera, s16 arg1);
s16 func_8005AD1C(Camera* camera, s16 arg1);
s32 Camera_ResetAnim(Camera* camera);
s32 Camera_SetCSParams(Camera* camera, CutsceneCameraPoint* atPoints, CutsceneCameraPoint* eyePoints, Player* player,
                       s16 relativeToPlayer);
s32 Camera_ChangeDoorCam(Camera* camera, Actor* doorActor, s16 camDataIdx, f32 arg3, s16 timer1, s16 timer2,
                         s16 timer3);
s32 Camera_Copy(Camera* dstCamera, Camera* srcCamera);
Vec3f* Camera_GetSkyboxOffset(Vec3f* dst, Camera* camera);
void Camera_SetCameraData(Camera* camera, s16 setDataFlags, void* data0, void* data1, s16 data2, s16 data3,
                          UNK_TYPE arg6);
s32 func_8005B198(void);
s16 func_8005B1A4(Camera* camera);
DamageTable* DamageTable_Get(s32 index);
void DamageTable_Clear(DamageTable* table);
void Collider_DrawRedPoly(GraphicsContext* gfxCtx, Vec3f* vA, Vec3f* vB, Vec3f* vC);
void Collider_DrawPoly(GraphicsContext* gfxCtx, Vec3f* vA, Vec3f* vB, Vec3f* vC, u8 r, u8 g, u8 b);
s32 Collider_InitJntSph(PlayState* play, ColliderJntSph* collider);
s32 Collider_FreeJntSph(PlayState* play, ColliderJntSph* collider);
s32 Collider_DestroyJntSph(PlayState* play, ColliderJntSph* collider);
s32 Collider_SetJntSphToActor(PlayState* play, ColliderJntSph* dest, ColliderJntSphInitToActor* src);
s32 Collider_SetJntSphAllocType1(PlayState* play, ColliderJntSph* dest, Actor* actor,
                                 ColliderJntSphInitType1* src);
s32 Collider_SetJntSphAlloc(PlayState* play, ColliderJntSph* dest, Actor* actor, ColliderJntSphInit* src);
s32 Collider_SetJntSph(PlayState* play, ColliderJntSph* dest, Actor* actor, ColliderJntSphInit* src,
                       ColliderJntSphElement* elements);
s32 Collider_ResetJntSphAT(PlayState* play, Collider* collider);
s32 Collider_ResetJntSphAC(PlayState* play, Collider* collider);
s32 Collider_ResetJntSphOC(PlayState* play, Collider* collider);
s32 Collider_InitCylinder(PlayState* play, ColliderCylinder* collider);
s32 Collider_DestroyCylinder(PlayState* play, ColliderCylinder* collider);
s32 Collider_SetCylinderToActor(PlayState* play, ColliderCylinder* collider, ColliderCylinderInitToActor* src);
s32 Collider_SetCylinderType1(PlayState* play, ColliderCylinder* collider, Actor* actor,
                              ColliderCylinderInitType1* src);
s32 Collider_SetCylinder(PlayState* play, ColliderCylinder* collider, Actor* actor, ColliderCylinderInit* src);
s32 Collider_ResetCylinderAT(PlayState* play, Collider* collider);
s32 Collider_ResetCylinderAC(PlayState* play, Collider* collider);
s32 Collider_ResetCylinderOC(PlayState* play, Collider* collider);
s32 Collider_InitTris(PlayState* play, ColliderTris* tris);
s32 Collider_FreeTris(PlayState* play, ColliderTris* tris);
s32 Collider_DestroyTris(PlayState* play, ColliderTris* tris);
s32 Collider_SetTrisAllocType1(PlayState* play, ColliderTris* dest, Actor* actor, ColliderTrisInitType1* src);
s32 Collider_SetTrisAlloc(PlayState* play, ColliderTris* dest, Actor* actor, ColliderTrisInit* src);
s32 Collider_SetTris(PlayState* play, ColliderTris* dest, Actor* actor, ColliderTrisInit* src,
                     ColliderTrisElement* elements);
s32 Collider_ResetTrisAT(PlayState* play, Collider* collider);
s32 Collider_ResetTrisAC(PlayState* play, Collider* collider);
s32 Collider_ResetTrisOC(PlayState* play, Collider* collider);
s32 Collider_InitQuad(PlayState* play, ColliderQuad* collider);
s32 Collider_DestroyQuad(PlayState* play, ColliderQuad* collider);
s32 Collider_SetQuadType1(PlayState* play, ColliderQuad* collider, Actor* actor, ColliderQuadInitType1* src);
s32 Collider_SetQuad(PlayState* play, ColliderQuad* collider, Actor* actor, ColliderQuadInit* src);
s32 Collider_ResetQuadAT(PlayState* play, Collider* collider);
s32 Collider_ResetQuadAC(PlayState* play, Collider* collider);
s32 Collider_ResetQuadOC(PlayState* play, Collider* collider);
s32 Collider_InitLine(PlayState* play, OcLine* line);
s32 Collider_DestroyLine(PlayState* play, OcLine* line);
s32 Collider_SetLinePoints(PlayState* play, OcLine* ocLine, Vec3f* a, Vec3f* b);
s32 Collider_SetLine(PlayState* play, OcLine* dest, OcLine* src);
s32 Collider_ResetLineOC(PlayState* play, OcLine* line);
void CollisionCheck_InitContext(PlayState* play, CollisionCheckContext* colChkCtx);
void CollisionCheck_DestroyContext(PlayState* play, CollisionCheckContext* colChkCtx);
void CollisionCheck_ClearContext(PlayState* play, CollisionCheckContext* colChkCtx);
void CollisionCheck_EnableSAC(PlayState* play, CollisionCheckContext* colChkCtx);
void CollisionCheck_DisableSAC(PlayState* play, CollisionCheckContext* colChkCtx);
void Collider_Draw(PlayState* play, Collider* collider);
void CollisionCheck_DrawCollision(PlayState* play, CollisionCheckContext* colChkCtx);
s32 CollisionCheck_SetAT(PlayState* play, CollisionCheckContext* colChkCtx, Collider* collider);
s32 CollisionCheck_SetAT_SAC(PlayState* play, CollisionCheckContext* colChkCtx, Collider* collider, s32 index);
s32 CollisionCheck_SetAC(PlayState* play, CollisionCheckContext* colChkCtx, Collider* collider);
s32 CollisionCheck_SetAC_SAC(PlayState* play, CollisionCheckContext* colChkCtx, Collider* collider, s32 index);
s32 CollisionCheck_SetOC(PlayState* play, CollisionCheckContext* colChkCtx, Collider* collider);
s32 CollisionCheck_SetOC_SAC(PlayState* play, CollisionCheckContext* colChkCtx, Collider* collider, s32 index);
s32 CollisionCheck_SetOCLine(PlayState* play, CollisionCheckContext* colChkCtx, OcLine* collider);
void CollisionCheck_BlueBlood(PlayState* play, Collider* collider, Vec3f* v);
void CollisionCheck_AT(PlayState* play, CollisionCheckContext* colChkCtx);
void CollisionCheck_OC(PlayState* play, CollisionCheckContext* colChkCtx);
void CollisionCheck_InitInfo(CollisionCheckInfo* info);
void CollisionCheck_ResetDamage(CollisionCheckInfo* info);
void CollisionCheck_SetInfoNoDamageTable(CollisionCheckInfo* info, CollisionCheckInfoInit* init);
void CollisionCheck_SetInfo(CollisionCheckInfo* info, DamageTable* damageTable, CollisionCheckInfoInit* init);
void CollisionCheck_SetInfo2(CollisionCheckInfo* info, DamageTable* damageTable, CollisionCheckInfoInit2* init);
void CollisionCheck_SetInfoGetDamageTable(CollisionCheckInfo* info, s32 index, CollisionCheckInfoInit2* init);
void CollisionCheck_Damage(PlayState* play, CollisionCheckContext* colChkCtx);
s32 CollisionCheck_LineOCCheckAll(PlayState* play, CollisionCheckContext* colChkCtx, Vec3f* a, Vec3f* b);
s32 CollisionCheck_LineOCCheck(PlayState* play, CollisionCheckContext* colChkCtx, Vec3f* a, Vec3f* b,
                               Actor** exclusions, s32 numExclusions);
void Collider_UpdateCylinder(Actor* actor, ColliderCylinder* collider);
void Collider_SetCylinderPosition(ColliderCylinder* collider, Vec3s* pos);
void Collider_SetQuadVertices(ColliderQuad* collider, Vec3f* a, Vec3f* b, Vec3f* c, Vec3f* d);
void Collider_SetTrisVertices(ColliderTris* collider, s32 index, Vec3f* a, Vec3f* b, Vec3f* c);
void Collider_SetTrisDim(PlayState* play, ColliderTris* collider, s32 index, ColliderTrisElementDimInit* init);
void Collider_UpdateSpheres(s32 limb, ColliderJntSph* collider);
void CollisionCheck_SpawnRedBlood(PlayState* play, Vec3f* v);
void CollisionCheck_SpawnWaterDroplets(PlayState* play, Vec3f* v);
void CollisionCheck_SpawnShieldParticles(PlayState* play, Vec3f* v);
void CollisionCheck_SpawnShieldParticlesMetal(PlayState* play, Vec3f* v);
void CollisionCheck_SpawnShieldParticlesMetalSound(PlayState* play, Vec3f* v, Vec3f* actorPos);
void CollisionCheck_SpawnShieldParticlesMetal2(PlayState* play, Vec3f* v);
void CollisionCheck_SpawnShieldParticlesWood(PlayState* play, Vec3f* b, Vec3f* actorPos);
s32 CollisionCheck_CylSideVsLineSeg(f32 radius, f32 height, f32 offset, Vec3f* actorPos, Vec3f* itemPos,
                                    Vec3f* itemProjPos, Vec3f* out1, Vec3f* out2);
u8 CollisionCheck_GetSwordDamage(s32 dmgFlags, PlayState* play);
void SaveContext_Init(void);
s32 func_800635D0(s32);
void func_800636C0(void);
void func_8006375C(s32 arg0, s32 arg1, const char* text);
void func_8006376C(u8 x, u8 y, u8 colorId, const char* text);
// ? func_80063828(?);
void func_8006390C(Input* input);
// ? func_80063C04(?);
void func_80063D7C(GraphicsContext* gfxCtx);
void DebugDisplay_Init(void);
DebugDispObject* DebugDisplay_AddObject(f32 posX, f32 posY, f32 posZ, s16 rotX, s16 rotY, s16 rotZ, f32 scaleX,
                                        f32 scaleY, f32 scaleZ, u8 red, u8 green, u8 blue, u8 alpha, s16 type,
                                        GraphicsContext* gfxCtx);
void DebugDisplay_DrawObjects(PlayState* play);
void func_8006450C(PlayState* play, CutsceneContext* csCtx);
void func_80064520(PlayState* play, CutsceneContext* csCtx);
void func_80064534(PlayState* play, CutsceneContext* csCtx);
void func_80064558(PlayState* play, CutsceneContext* csCtx);
void func_800645A0(PlayState* play, CutsceneContext* csCtx);
void Cutscene_HandleEntranceTriggers(PlayState* play);
void Cutscene_HandleConditionalTriggers(PlayState* play);
void Cutscene_SetSegment(PlayState* play, void* segment);
void GetItem_Draw(PlayState* play, s16 drawId);
void GetItemEntry_Draw(PlayState* play, GetItemEntry getItemEntry);
void SoundSource_InitAll(PlayState* play);
void SoundSource_UpdateAll(PlayState* play);
void SoundSource_PlaySfxAtFixedWorldPos(PlayState* play, Vec3f* pos, s32 duration, u16 sfxId);
u16 ElfMessage_GetSariaText(PlayState* play);
u16 ElfMessage_GetCUpText(PlayState* play);
u16 Text_GetFaceReaction(PlayState* play, u32 reactionSet);
void Flags_UnsetAllEnv(PlayState* play);
void Flags_SetEnv(PlayState* play, s16 flag);
void Flags_UnsetEnv(PlayState* play, s16 flag);
s32 Flags_GetEnv(PlayState* play, s16 flag);
f32 func_8006C5A8(f32 target, TransformData* transData, s32 refIdx);
void SkelCurve_Clear(SkelAnimeCurve* skelCurve);
s32 SkelCurve_Init(PlayState* play, SkelAnimeCurve* skelCurve, SkelCurveLimbList* limbListSeg,
                   TransformUpdateIndex* transUpdIdx);
void SkelCurve_Destroy(PlayState* play, SkelAnimeCurve* skelCurve);
void SkelCurve_SetAnim(SkelAnimeCurve* skelCurve, TransformUpdateIndex* transUpdIdx, f32 arg2, f32 animFinalFrame,
                       f32 animCurFrame, f32 animSpeed);
s32 SkelCurve_Update(PlayState* play, SkelAnimeCurve* skelCurve);
void SkelCurve_Draw(Actor* actor, PlayState* play, SkelAnimeCurve* skelCurve,
                    OverrideCurveLimbDraw overrideLimbDraw, PostCurveLimbDraw postLimbDraw, s32 lod, void* data);
s32 func_8006CFC0(s32 scene);
void func_8006D074(PlayState* play);
void func_8006D0AC(PlayState* play);
void func_8006D0EC(PlayState* play, Player* player);
void func_8006D684(PlayState* play, Player* player);
void func_8006DC68(PlayState* play, Player* player);
void func_8006DD9C(Actor* actor, Vec3f* arg1, s16 arg2);
s32 Jpeg_Decode(void* data, void* zbuffer, void* workBuff, u32 workSize);
void KaleidoSetup_Update(PlayState* play);
void KaleidoSetup_Init(PlayState* play);
void KaleidoSetup_Destroy(PlayState* play);
void func_8006EE50(Font* font, u16 arg1, u16 arg2);
void Font_LoadChar(Font* font, u8 character, u16 codePointIndex);
void* Font_FetchCharTexture(u8 character);
void Font_LoadMessageBoxIcon(Font* font, u16 icon);
void Font_LoadOrderedFont(Font* font);
s32 func_8006F0A0(s32 arg0);
u16 Environment_GetPixelDepth(s32 x, s32 y);
void Environment_GraphCallback(GraphicsContext* gfxCtx, void* param);
void Environment_Init(PlayState* play, EnvironmentContext* envCtx, s32 unused);
u8 Environment_SmoothStepToU8(u8* pvalue, u8 target, u8 scale, u8 step, u8 minStep);
u8 Environment_SmoothStepToS8(s8* pvalue, s8 target, u8 scale, u8 step, u8 minStep);
f32 Environment_LerpWeight(u16 max, u16 min, u16 val);
f32 Environment_LerpWeightAccelDecel(u16 endFrame, u16 startFrame, u16 curFrame, u16 accelDuration, u16 decelDuration);
void Environment_UpdateSkybox(PlayState* play, u8 skyboxId, EnvironmentContext* envCtx, SkyboxContext* skyboxCtx);
void Environment_EnableUnderwaterLights(PlayState* play, s32 waterLightsIndex);
void Environment_DisableUnderwaterLights(PlayState* play);
void Environment_Update(PlayState* play, EnvironmentContext* envCtx, LightContext* lightCtx,
                        PauseContext* pauseCtx, MessageContext* msgCtx, GameOverContext* gameOverCtx,
                        GraphicsContext* gfxCtx);
void Environment_DrawSunAndMoon(PlayState* play);
void Environment_DrawSunLensFlare(PlayState* play, EnvironmentContext* envCtx, View* view,
                                  GraphicsContext* gfxCtx, Vec3f pos, s32 unused);
void Environment_DrawLensFlare(PlayState* play, EnvironmentContext* envCtx, View* view,
                               GraphicsContext* gfxCtx, Vec3f pos, s32 unused, s16 arg6, f32 arg7, s16 arg8, u8 arg9);
void Environment_DrawRain(PlayState* play, View* view, GraphicsContext* gfxCtx);
void func_80074CE8(PlayState* play, u32 arg1);
void Environment_DrawSkyboxFilters(PlayState* play);
void Environment_UpdateLightningStrike(PlayState* play);
void Environment_AddLightningBolts(PlayState* play, u8 num);
void Environment_DrawLightning(PlayState* play, s32 unused);
void Environment_PlaySceneSequence(PlayState* play);
void Environment_DrawCustomLensFlare(PlayState* play);
void Environment_InitGameOverLights(PlayState* play);
void Environment_FadeInGameOverLights(PlayState* play);
void Environment_FadeOutGameOverLights(PlayState* play);
void Environment_FillScreen(GraphicsContext* gfxCtx, u8 red, u8 green, u8 blue, u8 alpha, u8 drawFlags);
void Environment_DrawSandstorm(PlayState* play, u8 sandstormState);
void Environment_AdjustLights(PlayState* play, f32 arg1, f32 arg2, f32 arg3, f32 arg4);
s32 Environment_GetBgsDayCount(void);
void Environment_ClearBgsDayCount(void);
s32 Environment_GetTotalDays(void);
void Environment_ForcePlaySequence(u16 seqId);
s32 Environment_IsForcedSequenceDisabled(void);
void Environment_PlayStormNatureAmbience(PlayState* play);
void Environment_StopStormNatureAmbience(PlayState* play);
void Environment_WarpSongLeave(PlayState* play);
f32 Math_CosS(s16 angle);
f32 Math_SinS(s16 angle);
f32 Math_AccurateCosS(s16 angle);
f32 Math_AccurateSinS(s16 angle);
s32 Math_ScaledStepToS(s16* pValue, s16 target, s16 step);
s32 Math_StepToS(s16* pValue, s16 target, s16 step);
s32 Math_StepToF(f32* pValue, f32 target, f32 step);
s32 Math_StepUntilAngleS(s16* pValue, s16 limit, s16 step);
s32 Math_StepUntilS(s16* pValue, s16 limit, s16 step);
s32 Math_StepToAngleS(s16* pValue, s16 target, s16 step);
s32 Math_StepUntilF(f32* pValue, f32 limit, f32 step);
s32 Math_AsymStepToF(f32* pValue, f32 target, f32 incrStep, f32 decrStep);
void func_80077D10(f32* arg0, s16* arg1, Input* input);
s16 Rand_S16Offset(s16 base, s16 range);
void Math_Vec3f_Copy(Vec3f* dest, Vec3f* src);
void Math_Vec3s_ToVec3f(Vec3f* dest, Vec3s* src);
void Math_Vec3f_Sum(Vec3f* a, Vec3f* b, Vec3f* dest);
void Math_Vec3f_Diff(Vec3f* a, Vec3f* b, Vec3f* dest);
void Math_Vec3s_DiffToVec3f(Vec3f* dest, Vec3s* a, Vec3s* b);
void Math_Vec3f_Scale(Vec3f* vec, f32 scaleF);
f32 Math_Vec3f_DistXYZ(Vec3f* a, Vec3f* b);
f32 Math_Vec3f_DistXYZAndStoreDiff(Vec3f* a, Vec3f* b, Vec3f* dest);
f32 Math_Vec3f_DistXZ(Vec3f* a, Vec3f* b);
s16 Math_Vec3f_Yaw(Vec3f* a, Vec3f* b);
s16 Math_Vec3f_Pitch(Vec3f* a, Vec3f* b);
void Actor_ProcessInitChain(Actor* actor, InitChainEntry* initChain);
f32 Math_SmoothStepToF(f32* pValue, f32 target, f32 fraction, f32 step, f32 minStep);
void Math_ApproachF(f32* pValue, f32 target, f32 fraction, f32 step);
void Math_ApproachZeroF(f32* pValue, f32 fraction, f32 step);
f32 Math_SmoothStepToDegF(f32* pValue, f32 target, f32 fraction, f32 step, f32 minStep);
s16 Math_SmoothStepToS(s16* pValue, s16 target, s16 scale, s16 step, s16 minStep);
void Math_ApproachS(s16* pValue, s16 target, s16 scale, s16 step);
void Color_RGBA8_Copy(Color_RGBA8* dst, Color_RGBA8* src);
void func_80078884(u16 sfxId);
void func_800788CC(u16 sfxId);
void func_80078914(Vec3f* arg0, u16 sfxId);
s16 getHealthMeterXOffset();
s16 getHealthMeterYOffset();
void HealthMeter_Init(PlayState* play);
void HealthMeter_Update(PlayState* play);
void HealthMeter_Draw(PlayState* play);
void HealthMeter_HandleCriticalAlarm(PlayState* play);
u32 HealthMeter_IsCritical(void);
void Lights_PointSetInfo(LightInfo* info, s16 x, s16 y, s16 z, u8 r, u8 g, u8 b, s16 radius, s32 type);
void Lights_PointNoGlowSetInfo(LightInfo* info, s16 x, s16 y, s16 z, u8 r, u8 g, u8 b, s16 radius);
void Lights_PointGlowSetInfo(LightInfo* info, s16 x, s16 y, s16 z, u8 r, u8 g, u8 b, s16 radius);
void Lights_PointSetColorAndRadius(LightInfo* info, u8 r, u8 g, u8 b, s16 radius);
void Lights_DirectionalSetInfo(LightInfo* info, s8 x, s8 y, s8 z, u8 r, u8 g, u8 b);
void Lights_Reset(Lights* lights, u8 ambentR, u8 ambentG, u8 ambentB);
void Lights_Draw(Lights* lights, GraphicsContext* gfxCtx);
void Lights_BindAll(Lights* lights, LightNode* listHead, Vec3f* vec);
void LightContext_Init(PlayState* play, LightContext* lightCtx);
void LightContext_SetAmbientColor(LightContext* lightCtx, u8 r, u8 g, u8 b);
void LightContext_SetFog(LightContext* lightCtx, u8 arg1, u8 arg2, u8 arg3, s16 numLights, s16 arg5);
Lights* LightContext_NewLights(LightContext* lightCtx, GraphicsContext* gfxCtx);
void LightContext_InitList(PlayState* play, LightContext* lightCtx);
void LightContext_DestroyList(PlayState* play, LightContext* lightCtx);
LightNode* LightContext_InsertLight(PlayState* play, LightContext* lightCtx, LightInfo* info);
void LightContext_RemoveLight(PlayState* play, LightContext* lightCtx, LightNode* node);
Lights* Lights_NewAndDraw(GraphicsContext* gfxCtx, u8 ambientR, u8 ambientG, u8 ambientB, u8 numLights, u8 r, u8 g,
                          u8 b, s8 x, s8 y, s8 z);
Lights* Lights_New(GraphicsContext* gfxCtx, u8 ambientR, u8 ambientG, u8 ambientB);
void Lights_GlowCheckPrepare(PlayState* play);
void Lights_GlowCheck(PlayState* play);
void Lights_DrawGlow(PlayState* play);
void ZeldaArena_CheckPointer(void* ptr, size_t size, const char* name, const char* action);
void* ZeldaArena_Malloc(size_t size);
void* ZeldaArena_MallocDebug(size_t size, const char* file, s32 line);
void* ZeldaArena_MallocR(size_t size);
void* ZeldaArena_MallocRDebug(size_t size, const char* file, s32 line);
void* ZeldaArena_Realloc(void* ptr, size_t newSize);
void* ZeldaArena_ReallocDebug(void* ptr, size_t newSize, const char* file, s32 line);
void ZeldaArena_Free(void* ptr);
void ZeldaArena_FreeDebug(void* ptr, const char* file, s32 line);
void* ZeldaArena_Calloc(size_t num, size_t size);
void ZeldaArena_Display();
void ZeldaArena_GetSizes(u32* outMaxFree, u32* outFree, u32* outAlloc);
void ZeldaArena_Check();
void ZeldaArena_Init(void* start, size_t size);
void ZeldaArena_Cleanup();
u8 ZeldaArena_IsInitalized();
void MapMark_Init(PlayState* play);
void MapMark_ClearPointers(PlayState* play);
void MapMark_Draw(PlayState* play);
void PreNmiBuff_Init(PreNmiBuff* this);
void PreNmiBuff_SetReset(PreNmiBuff* this);
u32 PreNmiBuff_IsResetting(PreNmiBuff* this);
void MsgEvent_SendNullTask(void);
f32 OLib_Vec3fDist(Vec3f* a, Vec3f* b);
f32 OLib_Vec3fDistXZ(Vec3f* a, Vec3f* b);
f32 OLib_ClampMinDist(f32 val, f32 min);
f32 OLib_ClampMaxDist(f32 val, f32 max);
Vec3f* OLib_Vec3fDistNormalize(Vec3f* dest, Vec3f* a, Vec3f* b);
Vec3f* OLib_VecSphGeoToVec3f(Vec3f* dest, VecSph* sph);
VecSph* OLib_Vec3fToVecSph(VecSph* dest, Vec3f* vec);
VecSph* OLib_Vec3fToVecSphGeo(VecSph* arg0, Vec3f* arg1);
VecSph* OLib_Vec3fDiffToVecSphGeo(VecSph* arg0, Vec3f* a, Vec3f* b);
Vec3f* OLib_Vec3fDiffRad(Vec3f* dest, Vec3f* a, Vec3f* b);
s16 OnePointCutscene_Init(PlayState* play, s16 csId, s16 timer, Actor* actor, s16 camIdx);
s16 OnePointCutscene_EndCutscene(PlayState* play, s16 camIdx);
s32 OnePointCutscene_Attention(PlayState* play, Actor* actor);
s32 OnePointCutscene_AttentionSetSfx(PlayState* play, Actor* actor, s32 sfxId);
void OnePointCutscene_EnableAttention(void);
void OnePointCutscene_DisableAttention(void);
s32 OnePointCutscene_CheckForCategory(PlayState* play, s32 actorCategory);
void OnePointCutscene_Noop(PlayState* play, s32 arg1);
void Map_SavePlayerInitialInfo(PlayState* play);
void Map_SetFloorPalettesData(PlayState* play, s16 floor);
void Map_InitData(PlayState* play, s16 room);
void Map_InitRoomData(PlayState* play, s16 room);
void Map_Destroy(PlayState* play);
void Map_Init(PlayState* play);
void Minimap_Draw(PlayState* play);
void Map_Update(PlayState* play);
void Interface_ChangeAlpha(u16 alphaType);
void Interface_SetSceneRestrictions(PlayState* play);
void Inventory_SwapAgeEquipment(void);
void Interface_InitHorsebackArchery(PlayState* play);
void func_800849EC(PlayState* play);
void Interface_LoadItemIcon1(PlayState* play, u16 button);
void Interface_LoadItemIcon2(PlayState* play, u16 button);
void func_80084BF4(PlayState* play, u16 flag);
uint16_t Interface_DrawTextLine(GraphicsContext* gfx, char text[], int16_t x, int16_t y, uint16_t colorR, uint16_t colorG, uint16_t colorB, uint16_t colorA, float textScale, uint8_t textShadow);
u8 Item_Give(PlayState* play, u8 item);
u16 Randomizer_Item_Give(PlayState* play, GetItemEntry giEntry);
u8 Item_CheckObtainability(u8 item);
void PerformAutosave(PlayState* play, u8 item);
void Inventory_DeleteItem(u16 item, u16 invSlot);
s32 Inventory_ReplaceItem(PlayState* play, u16 oldItem, u16 newItem);
s32 Inventory_HasEmptyBottle(void);
bool Inventory_HasEmptyBottleSlot(void);
s32 Inventory_HasSpecificBottle(u8 bottleItem);
void Inventory_UpdateBottleItem(PlayState* play, u8 item, u8 cButton);
s32 Inventory_ConsumeFairy(PlayState* play);
bool Inventory_HatchPocketCucco(PlayState* play);
void Interface_SetDoAction(PlayState* play, u16 action);
void Interface_SetNaviCall(PlayState* play, u16 naviCallState);
void Interface_LoadActionLabelB(PlayState* play, u16 action);
s32 Health_ChangeBy(PlayState* play, s16 healthChange);
void Rupees_ChangeBy(s16 rupeeChange);
void Inventory_ChangeAmmo(s16 item, s16 ammoChange);
void Magic_Fill(PlayState* play);
void Magic_Reset(PlayState* play);
s32 Magic_RequestChange(PlayState* play, s16 amount, s16 type);
void func_80088AA0(s16 seconds);
void func_80088AF0(PlayState* play);
void func_80088B34(s16 arg0);
void Interface_Draw(PlayState* play);
void Interface_DrawTotalGameplayTimer(PlayState* play);
void Interface_Update(PlayState* play);
Path* Path_GetByIndex(PlayState* play, s16 index, s16 max);
f32 Path_OrientAndGetDistSq(Actor* actor, Path* path, s16 waypoint, s16* yaw);
void Path_CopyLastPoint(Path* path, Vec3f* dest);
void FrameAdvance_Init(FrameAdvanceContext* frameAdvCtx);
s32 FrameAdvance_Update(FrameAdvanceContext* frameAdvCtx, Input* input);
u8 PlayerGrounded(Player* player);
void Player_SetBootData(PlayState* play, Player* player);
s32 Player_InBlockingCsMode(PlayState* play, Player* player);
s32 Player_InCsMode(PlayState* play);
s32 func_8008E9C4(Player* player);
s32 Player_IsChildWithHylianShield(Player* player);
s32 Player_ActionToModelGroup(Player* player, s32 actionParam);
void Player_SetModelsForHoldingShield(Player* player);
void Player_SetModels(Player* player, s32 modelGroup);
void Player_SetModelGroup(Player* player, s32 modelGroup);
void func_8008EC70(Player* player);
void Player_SetEquipmentData(PlayState* play, Player* player);
void Player_UpdateBottleHeld(PlayState* play, Player* player, s32 item, s32 actionParam);
void func_80837C0C(PlayState* play, Player* this, s32 arg2, f32 arg3, f32 arg4, s16 arg5, s32 arg6);
void func_8008EDF0(Player* player);
void func_8008EE08(Player* player);
void func_8008EEAC(PlayState* play, Actor* actor);
s32 func_8008EF44(PlayState* play, s32 ammo);
s32 Player_IsBurningStickInRange(PlayState* play, Vec3f* pos, f32 radius, f32 arg3);
s32 Player_GetStrength(void);
u8 Player_GetMask(PlayState* play);
Player* Player_UnsetMask(PlayState* play);
s32 Player_HasMirrorShieldEquipped(PlayState* play);
s32 Player_HasMirrorShieldSetToDraw(PlayState* play);
s32 Player_ActionToMagicSpell(Player* player, s32 actionParam);
s32 Player_HoldsHookshot(Player* player);
s32 Player_HoldsBow(Player* player);
s32 Player_HoldsSlingshot(Player* player);
s32 func_8008F128(Player* player);
s32 Player_ActionToMeleeWeapon(s32 actionParam);
s32 Player_GetMeleeWeaponHeld(Player* player);
s32 Player_HoldsTwoHandedWeapon(Player* player);
s32 Player_HoldsBrokenKnife(Player* player);
s32 Player_ActionToBottle(Player* player, s32 actionParam);
s32 Player_GetBottleHeld(Player* player);
s32 Player_ActionToExplosive(Player* player, s32 actionParam);
s32 Player_GetExplosiveHeld(Player* player);
s32 func_8008F2BC(Player* player, s32 actionParam);
s32 Player_GetEnvironmentalHazard(PlayState* play);
void Player_DrawImpl(PlayState* play, void** skeleton, Vec3s* jointTable, s32 dListCount, s32 lod, s32 tunic,
                   s32 boots, s32 face, OverrideLimbDrawOpa overrideLimbDraw, PostLimbDrawOpa postLimbDraw, void* this);
s32 Player_OverrideLimbDrawGameplayCommon(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, void* data);
s32 Player_OverrideLimbDrawGameplayDefault(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, void* data);
s32 Player_OverrideLimbDrawGameplayFirstPerson(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, void* data);
s32 Player_OverrideLimbDrawGameplayCrawling(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, void* data);
u8 func_80090480(PlayState* play, ColliderQuad* collider, WeaponInfo* weaponDim, Vec3f* newTip,
                 Vec3f* newBase);
void Player_DrawGetItem(PlayState* play, Player* player);
void Player_PostLimbDrawGameplay(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, void* data);
u32 func_80091738(PlayState* play, u8* segment, SkelAnime* skelAnime);
void Player_DrawPause(PlayState* play, u8* segment, SkelAnime* skelAnime, Vec3f* pos, Vec3s* rot, f32 scale,
                   s32 sword, s32 tunic, s32 shield, s32 boots);
void PreNMI_Init(GameState* thisx);
Vec3f* Quake_AddVec(Vec3f* dst, Vec3f* arg1, VecSph* arg2);
void Quake_UpdateShakeInfo(QuakeRequest* req, ShakeInfo* shake, f32 y, f32 x);
s16 Quake_Callback1(QuakeRequest* req, ShakeInfo* shake);
s16 Quake_Callback2(QuakeRequest* req, ShakeInfo* shake);
s16 Quake_Callback3(QuakeRequest* req, ShakeInfo* shake);
s16 Quake_Callback4(QuakeRequest* req, ShakeInfo* shake);
s16 Quake_Callback5(QuakeRequest* req, ShakeInfo* shake);
s16 Quake_Callback6(QuakeRequest* req, ShakeInfo* shake);
s16 Quake_GetFreeIndex(void);
QuakeRequest* Quake_AddImpl(Camera* cam, u32 callbackIdx);
void Quake_Remove(QuakeRequest* req);
QuakeRequest* Quake_GetRequest(s16 idx);
QuakeRequest* Quake_SetValue(s16 idx, s16 valueType, s16 value);
u32 Quake_SetSpeed(s16 idx, s16 value);
u32 Quake_SetCountdown(s16 idx, s16 value);
s16 Quake_GetCountdown(s16 idx);
u32 Quake_SetQuakeValues(s16 idx, s16 y, s16 x, s16 zoom, s16 rotZ);
u32 Quake_SetUnkValues(s16 idx, s16 arg1, SubQuakeRequest14 arg2);
void Quake_Init(void);
s16 Quake_Add(Camera* cam, u32 callbackIdx);
u32 Quake_RemoveFromIdx(s16 idx);
s16 Quake_Calc(Camera* camera, QuakeCamCalc* camData);
Gfx* Gfx_SetFog(Gfx* gfx, s32 r, s32 g, s32 b, s32 a, s32 near, s32 far);
Gfx* Gfx_SetFogWithSync(Gfx* gfx, s32 r, s32 g, s32 b, s32 a, s32 near, s32 far);
Gfx* Gfx_SetFog2(Gfx* gfx, s32 r, s32 g, s32 b, s32 a, s32 near, s32 far);
Gfx* Gfx_SetupDL(Gfx* gfx, u32 i);
Gfx* Gfx_SetupDL_57(Gfx* gfx);
Gfx* Gfx_SetupDL_52NoCD(Gfx* gfx);
void Gfx_SetupDL_57Opa(GraphicsContext* gfxCtx);
void Gfx_SetupDL_51Opa(GraphicsContext* gfxCtx);
void Gfx_SetupDL_54Opa(GraphicsContext* gfxCtx);
void Gfx_SetupDL_26Opa(GraphicsContext* gfxCtx);
void Gfx_SetupDL_25Xlu2(GraphicsContext* gfxCtx);
void func_80093C80(PlayState* play);
void Gfx_SetupDL_25Opa(GraphicsContext* gfxCtx);
void Gfx_SetupDL_25Xlu(GraphicsContext* gfxCtx);
Gfx* Gfx_SetupDL_64(Gfx* gfx);
Gfx* Gfx_SetupDL_34(Gfx* gfx);
void Gfx_SetupDL_44Xlu(GraphicsContext* gfxCtx);
void Gfx_SetupDL_36Opa(GraphicsContext* gfxCtx);
void Gfx_SetupDL_28Opa(GraphicsContext* gfxCtx);
Gfx* Gfx_SetupDL_28(Gfx* gfx);
void Gfx_SetupDL_38Xlu(GraphicsContext* gfxCtx);
void Gfx_SetupDL_4Xlu(GraphicsContext* gfxCtx);
void Gfx_SetupDL_37Opa(GraphicsContext* gfxCtx);
Gfx* Gfx_SetupDL_39(Gfx* gfx);
void Gfx_SetupDL_39Opa(GraphicsContext* gfxCtx);
void Gfx_SetupDL_39Overlay(GraphicsContext* gfxCtx);
void Gfx_SetupDL_39Ptr(Gfx** gfxp);
void Gfx_SetupDL_40Opa(GraphicsContext* gfxCtx);
void Gfx_SetupDL_41Opa(GraphicsContext* gfxCtx);
void Gfx_SetupDL_47Xlu(GraphicsContext* gfxCtx);
Gfx* Gfx_SetupDL_20NoCD(Gfx* gfx);
Gfx* Gfx_SetupDL_66(Gfx* gfx);
Gfx* func_800947AC(Gfx* gfx);
void Gfx_SetupDL_42Opa(GraphicsContext* gfxCtx);
void Gfx_SetupDL_42Overlay(GraphicsContext* gfxCtx);
void Gfx_SetupDL_42Kal(GraphicsContext* gfxCtx);
void Gfx_SetupDL_27Xlu(GraphicsContext* gfxCtx);
void Gfx_SetupDL_60NoCDXlu(GraphicsContext* gfxCtx);
void Gfx_SetupDL_61Xlu(GraphicsContext* gfxCtx);
void Gfx_SetupDL_56Ptr(Gfx** gfxp);
void Gfx_SetupDL_39Kal(GraphicsContext* gfxp);
Gfx* Gfx_BranchTexScroll(Gfx** gfxp, u32 x, u32 y, s32 width, s32 height);
Gfx* func_80094E78(GraphicsContext* gfxCtx, u32 x, u32 y);
Gfx* Gfx_TexScroll(GraphicsContext* gfxCtx, u32 x, u32 y, s32 width, s32 height);
Gfx* Gfx_TwoTexScroll(GraphicsContext* gfxCtx, s32 tile1, u32 x1, u32 y1, s32 width1, s32 height1, s32 tile2, u32 x2,
                      u32 y2, s32 width2, s32 height2);
Gfx* Gfx_TwoTexScrollEnvColor(GraphicsContext* gfxCtx, s32 tile1, u32 x1, u32 y1, s32 width1, s32 height1, s32 tile2,
                              u32 x2, u32 y2, s32 width2, s32 height2, s32 r, s32 g, s32 b, s32 a);
Gfx* Gfx_EnvColor(GraphicsContext* gfxCtx, s32 r, s32 g, s32 b, s32 a);
void Gfx_SetupFrame(GraphicsContext* gfxCtx, u8 r, u8 g, u8 b);
void func_80095974(GraphicsContext* gfxCtx);
void func_80095AA0(PlayState* play, Room* room, Input* arg2, UNK_TYPE arg3);
void func_8009638C(Gfx** displayList, void* source, void* tlut, u16 width, u16 height, u8 fmt, u8 siz, u16 mode0,
                   u16 tlutCount, f32 frameX, f32 frameY);
void func_80096FD4(PlayState* play, Room* room);
u32 func_80096FE8(PlayState* play, RoomContext* roomCtx);
s32 func_8009728C(PlayState* play, RoomContext* roomCtx, s32 roomNum);
s32 func_800973FC(PlayState* play, RoomContext* roomCtx);
void Room_Draw(PlayState* play, Room* room, u32 flags);
void func_80097534(PlayState* play, RoomContext* roomCtx);
void Sample_Destroy(GameState* thisx);
void Sample_Init(GameState* thisx);
void Inventory_ChangeEquipment(s16 equipment, u16 value);
u8 Inventory_DeleteEquipment(PlayState* play, s16 equipment);
void Inventory_ChangeUpgrade(s16 upgrade, s16 value);
void Object_InitBank(PlayState* play, ObjectContext* objectCtx);
void Object_UpdateBank(ObjectContext* objectCtx);
s32 Object_GetIndex(ObjectContext* objectCtx, s16 objectId);
s32 Object_IsLoaded(ObjectContext* objectCtx, s32 bankIndex);
void func_800981B8(ObjectContext* objectCtx);
s32 Scene_ExecuteCommands(PlayState* play, SceneCmd* sceneCmd);
void TransitionActor_InitContext(GameState* state, TransitionActorContext* transiActorCtx);
void Scene_SetTransitionForNextEntrance(PlayState* play);
void Scene_Draw(PlayState* play);
void SkelAnime_DrawLod(PlayState* play, void** skeleton, Vec3s* jointTable,
                       OverrideLimbDrawOpa overrideLimbDraw, PostLimbDrawOpa postLimbDraw, void* arg, s32 dListIndex);
void SkelAnime_DrawFlexLod(PlayState* play, void** skeleton, Vec3s* jointTable, s32 dListCount,
                           OverrideLimbDrawOpa overrideLimbDraw, PostLimbDrawOpa postLimbDraw, void* arg,
                           s32 dListIndex);
void SkelAnime_DrawSkeletonOpa(PlayState* play, SkelAnime* skelAnime, OverrideLimbDrawOpa overrideLimbDraw,
                               PostLimbDrawOpa postLimbDraw, void* arg);
void SkelAnime_DrawOpa(PlayState* play, void** skeleton, Vec3s* jointTable,
                       OverrideLimbDrawOpa overrideLimbDraw, PostLimbDrawOpa postLimbDraw, void* arg);
void SkelAnime_DrawFlexOpa(PlayState* play, void** skeleton, Vec3s* jointTable, s32 dListCount,
                           OverrideLimbDrawOpa overrideLimbDraw, PostLimbDrawOpa postLimbDraw, void* arg);
s16 Animation_GetLength(void* animation);
s16 Animation_GetLastFrame(void* animation);
s32 SkelAnime_GetFrameDataLegacy(LegacyAnimationHeader* animation, s32 frame, Vec3s* frameTable);
s16 Animation_GetLimbCountLegacy(LegacyAnimationHeader* animation);
s16 Animation_GetLengthLegacy(LegacyAnimationHeader* animation);
s16 Animation_GetLastFrameLegacy(LegacyAnimationHeader* animation);
Gfx* SkelAnime_Draw(PlayState* play, void** skeleton, Vec3s* jointTable, OverrideLimbDraw overrideLimbDraw,
                    PostLimbDraw postLimbDraw, void* arg, Gfx* gfx);
Gfx* SkelAnime_DrawFlex(PlayState* play, void** skeleton, Vec3s* jointTable, s32 dListCount,
                        OverrideLimbDraw overrideLimbDraw, PostLimbDraw postLimbDraw, void* arg, Gfx* gfx);
void SkelAnime_InterpFrameTable(s32 limbCount, Vec3s* dst, Vec3s* start, Vec3s* target, f32 weight);
void AnimationContext_Reset(AnimationContext* animationCtx);
void AnimationContext_SetNextQueue(PlayState* play);
void AnimationContext_DisableQueue(PlayState* play);
void AnimationContext_SetLoadFrame(PlayState* play, LinkAnimationHeader* animation, s32 frame, s32 limbCount,
                                   Vec3s* frameTable);
void AnimationContext_SetCopyAll(PlayState* play, s32 vecCount, Vec3s* dst, Vec3s* src);
void AnimationContext_SetInterp(PlayState* play, s32 vecCount, Vec3s* base, Vec3s* mod, f32 weight);
void AnimationContext_SetCopyTrue(PlayState* play, s32 vecCount, Vec3s* dst, Vec3s* src, u8* copyFlag);
void AnimationContext_SetCopyFalse(PlayState* play, s32 vecCount, Vec3s* dst, Vec3s* src, u8* copyFlag);
void AnimationContext_SetMoveActor(PlayState* play, Actor* actor, SkelAnime* skelAnime, f32 arg3);
void AnimationContext_Update(PlayState* play, AnimationContext* animationCtx);
void SkelAnime_InitLink(PlayState* play, SkelAnime* skelAnime, FlexSkeletonHeader* skeletonHeaderSeg,
                        LinkAnimationHeader* animation, s32 initFlags, Vec3s* jointTable, Vec3s* morphTable,
                        s32 limbCount);
void LinkAnimation_SetUpdateFunction(SkelAnime* skelAnime);
s32 LinkAnimation_Update(PlayState* play, SkelAnime* skelAnime);
void LinkAnimation_AnimateFrame(PlayState* play, SkelAnime* skelAnime);
void Animation_SetMorph(PlayState* play, SkelAnime* skelAnime, f32 morphFrames);
void LinkAnimation_Change(PlayState* play, SkelAnime* skelAnime, LinkAnimationHeader* animation, f32 playSpeed,
                          f32 startFrame, f32 endFrame, u8 mode, f32 morphFrames);
void LinkAnimation_PlayOnce(PlayState* play, SkelAnime* skelAnime, LinkAnimationHeader* animation);
void LinkAnimation_PlayOnceSetSpeed(PlayState* play, SkelAnime* skelAnime, LinkAnimationHeader* animation,
                                    f32 playSpeed);
void LinkAnimation_PlayLoop(PlayState* play, SkelAnime* skelAnime, LinkAnimationHeader* animation);
void LinkAnimation_PlayLoopSetSpeed(PlayState* play, SkelAnime* skelAnime, LinkAnimationHeader* animation,
                                    f32 playSpeed);
void LinkAnimation_CopyJointToMorph(PlayState* play, SkelAnime* skelAnime);
void LinkAnimation_CopyMorphToJoint(PlayState* play, SkelAnime* skelAnime);
void LinkAnimation_LoadToMorph(PlayState* play, SkelAnime* skelAnime, LinkAnimationHeader* animation,
                               f32 frame);
void LinkAnimation_LoadToJoint(PlayState* play, SkelAnime* skelAnime, LinkAnimationHeader* animation,
                               f32 frame);
void LinkAnimation_InterpJointMorph(PlayState* play, SkelAnime* skelAnime, f32 frame);
void LinkAnimation_BlendToJoint(PlayState* play, SkelAnime* skelAnime, LinkAnimationHeader* animation1,
                                f32 frame1, LinkAnimationHeader* animation2, f32 frame2, f32 weight, Vec3s* blendTable);
void LinkAnimation_BlendToMorph(PlayState* play, SkelAnime* skelAnime, LinkAnimationHeader* animation1,
                                f32 frame1, LinkAnimationHeader* animation2, f32 frame2, f32 weight, Vec3s* blendTable);
void LinkAnimation_EndLoop(SkelAnime* skelAnime);
s32 LinkAnimation_OnFrame(SkelAnime* skelAnime, f32 frame);
s32 SkelAnime_Init(PlayState* play, SkelAnime* skelAnime, SkeletonHeader* skeletonHeaderSeg,
                   AnimationHeader* animation, Vec3s* jointTable, Vec3s* morphTable, s32 limbCount);
s32 SkelAnime_InitFlex(PlayState* play, SkelAnime* skelAnime, FlexSkeletonHeader* skeletonHeaderSeg,
                       AnimationHeader* animation, Vec3s* jointTable, Vec3s* morphTable, s32 limbCount);
s32 SkelAnime_InitSkin(PlayState* play, SkelAnime* skelAnime, SkeletonHeader* skeletonHeaderSeg,
                       AnimationHeader* animation);
s32 SkelAnime_Update(SkelAnime* skelAnime);
void Animation_ChangeImpl(SkelAnime* skelAnime, AnimationHeader* animation, f32 playSpeed, f32 startFrame, f32 endFrame,
                          u8 mode, f32 morphFrames, s8 taper);
void Animation_Change(SkelAnime* skelAnime, AnimationHeader* animation, f32 playSpeed, f32 startFrame, f32 endFrame,
                      u8 mode, f32 morphFrames);
void Animation_PlayOnce(SkelAnime* skelAnime, AnimationHeader* animation);
void Animation_MorphToPlayOnce(SkelAnime* skelAnime, AnimationHeader* animation, f32 morphFrames);
void Animation_PlayOnceSetSpeed(SkelAnime* skelAnime, AnimationHeader* animation, f32 playSpeed);
void Animation_PlayLoop(SkelAnime* skelAnime, AnimationHeader* animation);
void Animation_MorphToLoop(SkelAnime* skelAnime, AnimationHeader* animation, f32 morphFrames);
void Animation_PlayLoopSetSpeed(SkelAnime* skelAnime, AnimationHeader* animation, f32 playSpeed);
void Animation_EndLoop(SkelAnime* skelAnime);
void Animation_Reverse(SkelAnime* skelAnime);
void SkelAnime_CopyFrameTableTrue(SkelAnime* skelAnime, Vec3s* dst, Vec3s* src, u8* copyFlag);
void SkelAnime_CopyFrameTableFalse(SkelAnime* skelAnime, Vec3s* dst, Vec3s* src, u8* copyFlag);
void SkelAnime_UpdateTranslation(SkelAnime* skelAnime, Vec3f* pos, s16 angle);
s32 Animation_OnFrame(SkelAnime* skelAnime, f32 frame);
void SkelAnime_Free(SkelAnime* skelAnime, PlayState* play);
void SkelAnime_CopyFrameTable(SkelAnime* skelAnime, Vec3s* dst, Vec3s* src);

void Skin_UpdateVertices(MtxF* mtx, SkinVertex* skinVertices, SkinLimbModif* modifEntry, Vtx* vtxBuf, Vec3f* pos);
void Skin_DrawAnimatedLimb(GraphicsContext* gfxCtx, Skin* skin, s32 limbIndex, s32 arg3, s32 drawFlags);
void Skin_DrawLimb(GraphicsContext* gfxCtx, Skin* skin, s32 limbIndex, Gfx* dlistOverride, s32 drawFlags);
void func_800A6330(Actor* actor, PlayState* play, Skin* skin, SkinPostDraw postDraw, s32 setTranslation);
void func_800A6360(Actor* actor, PlayState* play, Skin* skin, SkinPostDraw postDraw, SkinOverrideLimbDraw overrideLimbDraw, s32 setTranslation);
void func_800A6394(Actor* actor, PlayState* play, Skin* skin, SkinPostDraw postDraw, SkinOverrideLimbDraw overrideLimbDraw, s32 setTranslation, s32 arg6);
void func_800A63CC(Actor* actor, PlayState* play, Skin* skin, SkinPostDraw postDraw, SkinOverrideLimbDraw overrideLimbDraw, s32 setTranslation, s32 arg6, s32 drawFlags);
void Skin_GetLimbPos(Skin* skin, s32 limbIndex, Vec3f* arg2, Vec3f* dst);
void Skin_Init(PlayState* play, Skin* skin, SkeletonHeader* skeletonHeader, AnimationHeader* animationHeader);
void Skin_Free(PlayState* play, Skin* skin);
s32 Skin_ApplyAnimTransformations(Skin* skin, MtxF* mf, Actor* actor, s32 setTranslation);

void SkinMatrix_Vec3fMtxFMultXYZW(MtxF* mf, Vec3f* src, Vec3f* xyzDest, f32* wDest);
void SkinMatrix_Vec3fMtxFMultXYZ(MtxF* mf, Vec3f* src, Vec3f* dest);
void SkinMatrix_MtxFMtxFMult(MtxF* mfA, MtxF* mfB, MtxF* dest);
void SkinMatrix_GetClear(MtxF** mf);
void SkinMatrix_Clear(MtxF* mf);
void SkinMatrix_MtxFCopy(MtxF* src, MtxF* dest);
s32 SkinMatrix_Invert(MtxF* src, MtxF* dest);
void SkinMatrix_SetScale(MtxF* mf, f32 x, f32 y, f32 z);
void SkinMatrix_SetRotateZYX(MtxF* mf, s16 x, s16 y, s16 z);
void SkinMatrix_SetTranslate(MtxF* mf, f32 x, f32 y, f32 z);
void SkinMatrix_SetTranslateRotateYXZScale(MtxF* dest, f32 scaleX, f32 scaleY, f32 scaleZ, s16 rotX, s16 rotY, s16 rotZ,
                                           f32 translateX, f32 translateY, f32 translateZ);
void SkinMatrix_SetTranslateRotateZYX(MtxF* dest, s16 rotX, s16 rotY, s16 rotZ, f32 translateX, f32 translateY,
                                      f32 translateZ);
Mtx* SkinMatrix_MtxFToNewMtx(GraphicsContext* gfxCtx, MtxF* src);
void SkinMatrix_SetRotateAxis(MtxF* mf, s16 angle, f32 axisX, f32 axisY, f32 axisZ);
void Sram_OpenSave();
void Sram_InitSave(FileChooseContext* fileChoose);
void Sram_InitSram(GameState* gameState);
void SsSram_ReadWrite(uintptr_t addr, void* dramAddr, size_t size, s32 direction);
void func_800A9F30(PadMgr*, s32);
void func_800A9F6C(f32, u8, u8, u8);
void func_800AA000(f32, u8, u8, u8);
void func_800AA0B4();
void func_800AA0F0(void);
u32 func_800AA148();
void func_800AA15C();
void func_800AA16C();
void func_800AA178(u32);
View* View_New(GraphicsContext* gfxCtx);
void View_Free(View* view);
void View_Init(View*, GraphicsContext*);
void func_800AA358(View* view, Vec3f* eye, Vec3f* lookAt, Vec3f* up);
void func_800AA3F0(View* view, Vec3f* eye, Vec3f* lookAt, Vec3f* up);
void View_SetScale(View* view, f32 scale);
void View_GetScale(View* view, f32* scale);
void func_800AA460(View* view, f32 fovy, f32 near, f32 far);
void func_800AA48C(View* view, f32* fovy, f32* near, f32* far);
void func_800AA4A8(View* view, f32 fovy, f32 near, f32 far);
void func_800AA4E0(View* view, f32* fovy, f32* near, f32* far);
void View_SetViewport(View* view, Viewport* viewport);
void View_GetViewport(View* view, Viewport* viewport);
void View_SetDistortionOrientation(View* view, f32 rotX, f32 rotY, f32 rotZ);
void View_SetDistortionScale(View* view, f32 scaleX, f32 scaleY, f32 scaleZ);
s32 View_SetDistortionSpeed(View* view, f32 speed);
void View_InitDistortion(View* view);
void View_ClearDistortion(View* view);
void View_SetDistortion(View* view, Vec3f orientation, Vec3f scale, f32 speed);
s32 View_StepDistortion(View* view, Mtx* projectionMtx);
void func_800AAA50(View* view, s32 arg1);
s32 func_800AAA9C(View* view);
s32 func_800AB0A8(View* view);
s32 func_800AB2C4(View* view);
s32 func_800AB560(View* view);
s32 func_800AB944(View* view);
s32 func_800AB9EC(View* view, s32 arg1, Gfx** p);
s32 func_800ABE74(f32 eyeX, f32 eyeY, f32 eyeZ);
void ViMode_LogPrint(OSViMode* viMode);
void ViMode_Configure(ViMode* viMode, s32 mode, s32 type, s32 unk_70, s32 unk_74, s32 unk_78, s32 unk_7C, s32 width,
                      s32 height, s32 unk_left, s32 unk_right, s32 unk_top, s32 unk_bottom);
void ViMode_Save(ViMode* viMode);
void ViMode_Load(ViMode* viMode);
void ViMode_Init(ViMode* viMode);
void ViMode_Destroy(ViMode* viMode);
void ViMode_ConfigureFeatures(ViMode* viMode, s32 viFeatures);
void ViMode_Update(ViMode* viMode, Input* input);
void func_800ACE70(struct_801664F0* this);
void func_800ACE90(struct_801664F0* this);
void func_800ACE98(struct_801664F0* this, Gfx** gfxp);
void VisMono_Init(VisMono* this);
void VisMono_Destroy(VisMono* this);
void VisMono_UpdateTexture(VisMono* this, u16* tex);
Gfx* VisMono_DrawTexture(VisMono* this, Gfx* gfx);
void VisMono_Draw(VisMono* this, Gfx** gfxp);
void VisMono_DrawOld(VisMono* this);
void func_800AD920(struct_80166500* this);
void func_800AD950(struct_80166500* this);
void func_800AD958(struct_80166500* this, Gfx** gfxp);
void Skybox_Init(GameState* state, SkyboxContext* skyboxCtx, s16 skyboxId);
Mtx* SkyboxDraw_UpdateMatrix(SkyboxContext* skyboxCtx, f32 x, f32 y, f32 z);
void SkyboxDraw_Draw(SkyboxContext* skyboxCtx, GraphicsContext* gfxCtx, s16 skyboxId, s16 blend, f32 x, f32 y, f32 z);
void SkyboxDraw_Update(SkyboxContext* skyboxCtx);
void PlayerCall_InitFuncPtrs(void);
void TransitionUnk_InitGraphics(TransitionUnk* this);
void TransitionUnk_InitData(TransitionUnk* this);
void TransitionUnk_Destroy(TransitionUnk* this);
TransitionUnk* TransitionUnk_Init(TransitionUnk* this, s32 row, s32 col);
void TransitionUnk_SetData(TransitionUnk* this);
void TransitionUnk_Draw(TransitionUnk* this, Gfx**);
void func_800B23E8(TransitionUnk* this);
void TransitionTriforce_Start(void* this);
void* TransitionTriforce_Init(void* this);
void TransitionTriforce_Destroy(void* this);
void TransitionTriforce_Update(void* this, s32 updateRate);
void TransitionTriforce_SetColor(void* this, u32 color);
void TransitionTriforce_SetType(void* this, s32 type);
void TransitionTriforce_Draw(void* this, Gfx** gfxP);
s32 TransitionTriforce_IsDone(void* this);
void TransitionWipe_Start(void* this);
void* TransitionWipe_Init(void* this);
void TransitionWipe_Destroy(void* this);
void TransitionWipe_Update(void* this, s32 updateRate);
void TransitionWipe_Draw(void* this, Gfx** gfxP);
s32 TransitionWipe_IsDone(void* this);
void TransitionWipe_SetType(void* this, s32 type);
void TransitionWipe_SetColor(void* this, u32 color);
void TransitionCircle_Start(void* thisx);
void* TransitionCircle_Init(void* thisx);
void TransitionCircle_Destroy(void* thisx);
void TransitionCircle_Update(void* thisx, s32 updateRate);
void TransitionCircle_Draw(void* thisx, Gfx** gfxP);
s32 TransitionCircle_IsDone(void* thisx);
void TransitionCircle_SetType(void* thisx, s32 type);
void TransitionCircle_SetColor(void* thisx, u32 color);
void TransitionCircle_SetEnvColor(void* thisx, u32 color);
void TransitionFade_Start(void* this);
void* TransitionFade_Init(void* this);
void TransitionFade_Destroy(void* this);
void TransitionFade_Update(void* this, s32 updateRate);
void TransitionFade_Draw(void* this, Gfx** gfxP);
s32 TransitionFade_IsDone(void* this);
void TransitionFade_SetColor(void* this, u32 color);
void TransitionFade_SetType(void* this, s32 type);
void ShrinkWindow_SetVal(s32 value);
u32 ShrinkWindow_GetVal(void);
void ShrinkWindow_SetCurrentVal(s32 nowVal);
u32 ShrinkWindow_GetCurrentVal(void);
void ShrinkWindow_Init(void);
void ShrinkWindow_Destroy(void);
void ShrinkWindow_Update(s32 updateRate);
// ? DbCamera_AddVecSph(?);
// ? DbCamera_CalcUpFromPitchYawRoll(?);
// ? DbCamera_SetTextValue(?);
// ? DbCamera_Vec3SToF(?);
// ? DbCamera_Vec3FToS(?);
// ? DbCamera_CopyVec3f(?);
// ? DbCamera_Vec3SToF2(?);
// ? func_800B3F94(?);
// ? func_800B3FF4(?);
// ? func_800B404C(?);
// ? func_800B4088(?);
// ? func_800B41DC(?);
// ? func_800B42C0(?);
// ? func_800B4370(?);
// ? func_800B44E0(?);
// ? DbCamera_PrintPoints(?);
// ? DbCamera_PrintF32Bytes(?);
// ? DbCamera_PrintU16Bytes(?);
// ? DbCamera_PrintS16Bytes(?);
// ? DbCamera_PrintCutBytes(?);
void DbCamera_Init(DbCamera* dbCamera, Camera* cameraPtr);
void DbgCamera_Enable(DbCamera* dbCamera, Camera* cam);
void DbCamera_Update(DbCamera* dbCamera, Camera* cam);
// ? DbCamera_GetFirstAvailableLetter(?);
// ? DbCamera_InitCut(?);
// ? DbCamera_ResetCut(?);
// ? DbCamera_CalcMempakAllocSize(?);
// ? DbCamera_GetMempakAllocSize(?);
// ? DbCamera_DrawSlotLetters(?);
// ? DbCamera_PrintAllCuts(?);
// ? func_800B91B0(?);
void DbCamera_Reset(Camera* cam, DbCamera* dbCam);
// ? DbCamera_UpdateDemoControl(?);
void func_800BB0A0(f32 u, Vec3f* pos, f32* roll, f32* viewAngle, f32* point0, f32* point1, f32* point2, f32* point3);
s32 func_800BB2B4(Vec3f* pos, f32* roll, f32* fov, CutsceneCameraPoint* point, s16* keyframe, f32* curFrame);
s32 Mempak_Init(s32 controllerNb);
s32 Mempak_GetFreeBytes(s32 controllerNb);
s32 Mempak_FindFile(s32 controllerNb, char start, char end);
s32 Mempak_Write(s32 controllerNb, char idx, void* buffer, s32 offset, ptrdiff_t size);
s32 Mempak_Read(s32 controllerNb, char idx, void* buffer, s32 offset, ptrdiff_t size);
s32 Mempak_Alloc(s32 controllerNb, char* idx, ptrdiff_t size);
s32 Mempak_DeleteFile(s32 controllerNb, char idx);
s32 Mempak_GetFileSize(s32 controllerNb, char idx);
void KaleidoManager_LoadOvl(KaleidoMgrOverlay* ovl);
void KaleidoManager_ClearOvl(KaleidoMgrOverlay* ovl);
void KaleidoManager_Init(PlayState* play);
void KaleidoManager_Destroy();
void* KaleidoManager_GetRamAddr(void* vram);
void KaleidoScopeCall_LoadPlayer();
void KaleidoScopeCall_Init(PlayState* play);
void KaleidoScopeCall_Destroy(PlayState* play);
void KaleidoScopeCall_Update(PlayState* play);
void KaleidoScopeCall_Draw(PlayState* play);
void func_800BC490(PlayState* play, s16 point);
s32 func_800BC56C(PlayState* play, s16 arg1);
void func_800BC590(PlayState* play);
void Gameplay_SetupTransition(PlayState* play, s32 arg1);
Gfx* Play_SetFog(PlayState* play, Gfx* gfx);
void Play_Destroy(GameState* thisx);
void Play_Init(GameState* thisx);
void Play_Main(GameState* thisx);
u8 CheckStoneCount();
u8 CheckMedallionCount();
u8 CheckDungeonCount();
u8 CheckBridgeRewardCount();
u8 CheckLACSRewardCount();
s32 Play_InCsMode(PlayState* play);
f32 func_800BFCB8(PlayState* play, MtxF* mf, Vec3f* vec);
void* Play_LoadFile(PlayState* play, RomFile* file);
void Play_SpawnScene(PlayState* play, s32 sceneNum, s32 spawn);
void func_800C016C(PlayState* play, Vec3f* src, Vec3f* dest);
s16 Play_CreateSubCamera(PlayState* play);
s16 Play_GetActiveCamId(PlayState* play);
s16 Play_ChangeCameraStatus(PlayState* play, s16 camId, s16 status);
void Play_ClearCamera(PlayState* play, s16 camId);
void Play_ClearAllSubCameras(PlayState* play);
Camera* Play_GetCamera(PlayState* play, s16 camId);
s32 Play_CameraSetAtEye(PlayState* play, s16 camId, Vec3f* at, Vec3f* eye);
s32 Play_CameraSetAtEyeUp(PlayState* play, s16 camId, Vec3f* at, Vec3f* eye, Vec3f* up);
s32 Play_CameraSetFov(PlayState* play, s16 camId, f32 fov);
s32 Play_SetCameraRoll(PlayState* play, s16 camId, s16 roll);
void Play_CopyCamera(PlayState* play, s16 camId1, s16 camId2);
s32 func_800C0808(PlayState* play, s16 camId, Player* player, s16 arg3);
s32 Play_CameraChangeSetting(PlayState* play, s16 camId, s16 arg2);
void func_800C08AC(PlayState* play, s16 camId, s16 arg2);
void Play_SaveSceneFlags(PlayState* play);
void Play_SetupRespawnPoint(PlayState* play, s32 respawnMode, s32 playerParams);
void Play_TriggerVoidOut(PlayState* play);
void Play_TriggerRespawn(PlayState* play);
s32 func_800C0CB8(PlayState* play);
s32 FrameAdvance_IsEnabled(PlayState* play);
s32 func_800C0D34(PlayState* play, Actor* actor, s16* yaw);
s32 func_800C0DB4(PlayState* play, Vec3f* pos);
void Play_PerformSave(PlayState* play);
void PreRender_SetValuesSave(PreRender* this, u32 width, u32 height, void* fbuf, void* zbuf, void* cvg);
void PreRender_Init(PreRender* this);
void PreRender_SetValues(PreRender* this, u32 width, u32 height, void* fbuf, void* zbuf);
void PreRender_Destroy(PreRender* this);
void func_800C0F28(PreRender* this, Gfx** gfxp, void* buf, void* bufSave);
void func_800C1258(PreRender* this, Gfx** gfxp);
void func_800C170C(PreRender* this, Gfx** gfxp, void* fbuf, void* fbufSave, u32 r, u32 g, u32 b, u32 a);
void func_800C1AE8(PreRender* this, Gfx** gfxp, void* fbuf, void* fbufSave);
void func_800C1B24(PreRender* this, Gfx** gfxp, void* fbuf, void* cvgSave);
void func_800C1E9C(PreRender* this, Gfx** gfxp);
void func_800C1F20(PreRender* this, Gfx** gfxp);
void func_800C1FA4(PreRender* this, Gfx** gfxp);
void func_800C20B4(PreRender* this, Gfx** gfxp);
void func_800C2118(PreRender* this, Gfx** gfxp);
void func_800C213C(PreRender* this, Gfx** gfxp);
void func_800C24BC(PreRender* this, Gfx** gfxp);
void func_800C24E0(PreRender* this, Gfx** gfxp);
void func_800C2500(PreRender* this, s32 x, s32 y);
void func_800C2FE4(PreRender* this);
void PreRender_Calc(PreRender* this);
void THGA_Ct(TwoHeadGfxArena* thga, Gfx* start, size_t size);
void THGA_Dt(TwoHeadGfxArena* thga);
u32 THGA_IsCrash(TwoHeadGfxArena* thga);
void THGA_Init(TwoHeadGfxArena* thga);
s32 THGA_GetSize(TwoHeadGfxArena* thga);
Gfx* THGA_GetHead(TwoHeadGfxArena* thga);
void THGA_SetHead(TwoHeadGfxArena* thga, Gfx* start);
Gfx* THGA_GetTail(TwoHeadGfxArena* thga);
Gfx* THGA_AllocStartArray8(TwoHeadGfxArena* thga, u32 count);
Gfx* THGA_AllocStart8(TwoHeadGfxArena* thga);
Gfx* THGA_AllocStart8Wrapper(TwoHeadGfxArena* thga);
Gfx* THGA_AllocEnd(TwoHeadGfxArena* thga, size_t size);
Gfx* THGA_AllocEndArray64(TwoHeadGfxArena* thga, u32 count);
Gfx* THGA_AllocEnd64(TwoHeadGfxArena* thga);
Gfx* THGA_AllocEndArray16(TwoHeadGfxArena* thga, u32 count);
Gfx* THGA_AllocEnd16(TwoHeadGfxArena* thga);
void* THA_GetHead(TwoHeadArena* tha);
void THA_SetHead(TwoHeadArena* tha, void* start);
void* THA_GetTail(TwoHeadArena* tha);
void* THA_AllocStart(TwoHeadArena* tha, size_t size);
void* THA_AllocStart1(TwoHeadArena* tha);
void* THA_AllocEnd(TwoHeadArena* tha, size_t size);
void* THA_AllocEndAlign16(TwoHeadArena* tha, size_t size);
void* THA_AllocEndAlign(TwoHeadArena* tha, size_t size, size_t mask);
s32 THA_GetSize(TwoHeadArena* tha);
u32 THA_IsCrash(TwoHeadArena* tha);
void THA_Init(TwoHeadArena* tha);
void THA_Ct(TwoHeadArena* tha, void* ptr, size_t size);
void THA_Dt(TwoHeadArena* tha);
void func_800C3C20(void);
void func_800C3C80(AudioMgr* audioMgr);
void AudioMgr_HandleRetrace(AudioMgr* audioMgr);
void AudioMgr_HandlePRENMI(AudioMgr* audioMgr);
void AudioMgr_ThreadEntry(void* arg0);
void AudioMgr_Unlock(AudioMgr* audioMgr);
void AudioMgr_Init(AudioMgr* audioMgr, void* stack, OSPri pri, OSId id, SchedContext* sched, IrqMgr* irqMgr);
void TitleSetup_InitImpl(GameState* gameState);
void TitleSetup_Destroy(GameState* gameState);
void TitleSetup_Init(GameState* gameState);
void GameState_FaultPrint(void);
void GameState_SetFBFilter(Gfx** gfx);
// ? func_800C4344(?);
void GameState_DrawInputDisplay(u16 input, Gfx** gfx);
void GameState_Draw(GameState* gameState, GraphicsContext* gfxCtx);
void GameState_SetFrameBuffer(GraphicsContext* gfxCtx);
// ? func_800C49F4(?);
void GameState_ReqPadData(GameState* gameState);
void GameState_Update(GameState* gameState);
void GameState_InitArena(GameState* gameState, size_t size);
void GameState_Realloc(GameState* gameState, size_t size);
void GameState_Init(GameState* gameState, GameStateFunc init, GraphicsContext* gfxCtx);
void GameState_Destroy(GameState* gameState);
GameStateFunc GameState_GetInit(GameState* gameState);
u32 GameState_IsRunning(GameState* gameState);
void* GameState_Alloc(GameState* gameState, size_t size, char* file, s32 line);
void func_800C55D0(GameAlloc* this);
void* GameAlloc_MallocDebug(GameAlloc* this, size_t size, const char* file, s32 line);
void* GameAlloc_Malloc(GameAlloc* this, size_t size);
void GameAlloc_Free(GameAlloc* this, void* data);
void GameAlloc_Cleanup(GameAlloc* this);
void GameAlloc_Init(GameAlloc* this);
void Graph_FaultClient();
void Graph_DisassembleUCode(Gfx* workBuf);
void Graph_UCodeFaultClient(Gfx* workBuf);
void Graph_InitTHGA(GraphicsContext* gfxCtx);
GameStateOverlay* Graph_GetNextGameState(GameState* gameState);
void Graph_Init(GraphicsContext* gfxCtx);
void Graph_Destroy(GraphicsContext* gfxCtx);
void Graph_TaskSet00(GraphicsContext* gfxCtx);
void Graph_Update(GraphicsContext* gfxCtx, GameState* gameState);
void Graph_ThreadEntry(void*);
void* Graph_Alloc(GraphicsContext* gfxCtx, size_t size);
void* Graph_Alloc2(GraphicsContext* gfxCtx, size_t size);
void Graph_OpenDisps(Gfx** dispRefs, GraphicsContext* gfxCtx, const char* file, s32 line);
void Graph_CloseDisps(Gfx** dispRefs, GraphicsContext* gfxCtx, const char* file, s32 line);
Gfx* Graph_GfxPlusOne(Gfx* gfx);
Gfx* Graph_BranchDlist(Gfx* gfx, Gfx* dst);
void* Graph_DlistAlloc(Gfx** gfx, size_t size);
ListAlloc* ListAlloc_Init(ListAlloc* this);
void* ListAlloc_Alloc(ListAlloc* this, size_t size);
void ListAlloc_Free(ListAlloc* this, void* data);
void ListAlloc_FreeAll(ListAlloc* this);
void Main_LogSystemHeap(void);
void Main(void* arg);
OSMesgQueue* PadMgr_LockSerialMesgQueue(PadMgr* padmgr);
void PadMgr_UnlockSerialMesgQueue(PadMgr* padmgr, OSMesgQueue* ctrlrqueue);
void PadMgr_LockPadData(PadMgr* padmgr);
void PadMgr_UnlockPadData(PadMgr* padmgr);
void PadMgr_RumbleControl(PadMgr* padmgr);
void PadMgr_RumbleStop(PadMgr* padmgr);
void PadMgr_RumbleReset(PadMgr* padmgr);
void PadMgr_RumbleSet(PadMgr* padmgr, u8* ctrlrRumbles);
void PadMgr_ProcessInputs(PadMgr* padmgr);
void PadMgr_HandleRetraceMsg(PadMgr* padmgr);
void PadMgr_HandlePreNMI(PadMgr* padmgr);
// This function must remain commented out, because it is called incorrectly in
// fault.c (actual bug in game), and the compiler notices and won't compile it
void PadMgr_RequestPadData(PadMgr* padmgr, Input* inputs, s32 mode);
void PadMgr_Init(PadMgr* padmgr, OSMesgQueue* siIntMsgQ, IrqMgr* irqMgr, OSId id, OSPri priority, void* stack);
void Sched_SwapFrameBuffer(CfbInfo* cfbInfo);
void func_800C84E4(SchedContext* sc, CfbInfo* cfbInfo);
void Sched_HandleReset(SchedContext* sc);
void Sched_HandleStart(SchedContext* sc);
void Sched_QueueTask(SchedContext* sc, OSScTask* task);
void Sched_Yield(SchedContext* sc);
OSScTask* func_800C89D4(SchedContext* sc, OSScTask* task);
s32 Sched_Schedule(SchedContext* sc, OSScTask** sp, OSScTask** dp, s32 state);
void func_800C8BC4(SchedContext* sc, OSScTask* task);
u32 Sched_IsComplete(SchedContext* sc, OSScTask* task);
void Sched_RunTask(SchedContext* sc, OSScTask* spTask, OSScTask* dpTask);
void Sched_HandleEntry(SchedContext* sc);
void Sched_HandleRetrace(SchedContext* sc);
void Sched_HandleRSPDone(SchedContext* sc);
void Sched_HandleRDPDone(SchedContext* sc);
void Sched_SendEntryMsg(SchedContext* sc);
void Sched_ThreadEntry(void* arg);
void Sched_Init(SchedContext* sc, void* stack, OSPri priority, UNK_TYPE arg3, UNK_TYPE arg4, IrqMgr* irqMgr);
void SpeedMeter_InitImpl(SpeedMeter* this, u32 arg1, u32 y);
void SpeedMeter_Init(SpeedMeter* this);
void SpeedMeter_Destroy(SpeedMeter* this);
void SpeedMeter_DrawTimeEntries(SpeedMeter* this, GraphicsContext* gfxCtx);
void SpeedMeter_InitAllocEntry(SpeedMeterAllocEntry* entry, u32 maxval, u32 val, u16 backColor, u16 foreColor, u32 ulx,
                               u32 lrx, u32 uly, u32 lry);
void SpeedMeter_DrawAllocEntry(SpeedMeterAllocEntry* this, GraphicsContext* gfxCtx);
void SpeedMeter_DrawAllocEntries(SpeedMeter* meter, GraphicsContext* gfxCtx, GameState* state);
void SysCfb_Init(s32 n64dd);
uintptr_t SysCfb_GetFbPtr(s32 idx);
uintptr_t SysCfb_GetFbEnd();
f32 Math_FactorialF(f32 n);
f32 Math_Factorial(s32 n);
f32 Math_PowF(f32 base, s32 exp);
f32 Math_SinF(f32 angle);
f32 Math_CosF(f32 angle);
s32 Math3D_PlaneVsLineSegClosestPoint(f32 planeAA, f32 planeAB, f32 planeAC, f32 planeADist, f32 planeBA, f32 planeBB,
                                      f32 planeBC, f32 planeBDist, Vec3f* linePointA, Vec3f* linePointB,
                                      Vec3f* closestPoint);
void Math3D_LineClosestToPoint(Linef* line, Vec3f* pos, Vec3f* closestPoint);
s32 Math3D_PlaneVsPlaneVsLineClosestPoint(f32 planeAA, f32 planeAB, f32 planeAC, f32 planeADist, f32 planeBA,
                                          f32 planeBB, f32 planeBC, f32 planeBDist, Vec3f* point, Vec3f* closestPoint);
void Math3D_LineSplitRatio(Vec3f* v0, Vec3f* v1, f32 ratio, Vec3f* ret);
f32 Math3D_Cos(Vec3f* a, Vec3f* b);
s32 Math3D_CosOut(Vec3f* a, Vec3f* b, f32* dst);
void Math3D_Vec3fReflect(Vec3f* vec, Vec3f* normal, Vec3f* reflVec);
s32 Math3D_PointInSquare2D(f32 upperLeftX, f32 lowerRightX, f32 upperLeftY, f32 lowerRightY, f32 x, f32 y);
f32 Math3D_Dist1DSq(f32 a, f32 b);
f32 Math3D_Dist2DSq(f32 x0, f32 y0, f32 x1, f32 y1);
f32 Math3D_Vec3fMagnitudeSq(Vec3f* vec);
f32 Math3D_Vec3fMagnitude(Vec3f* vec);
f32 Math3D_Vec3fDistSq(Vec3f* a, Vec3f* b);
void Math3D_Vec3f_Cross(Vec3f* a, Vec3f* b, Vec3f* ret);
void Math3D_SurfaceNorm(Vec3f* va, Vec3f* vb, Vec3f* vc, Vec3f* normal);
f32 Math3D_Vec3f_DistXYZ(Vec3f* a, Vec3f* b);
s32 Math3D_PointRelativeToCubeFaces(Vec3f* point, Vec3f* min, Vec3f* max);
s32 Math3D_PointRelativeToCubeEdges(Vec3f* point, Vec3f* min, Vec3f* max);
s32 Math3D_PointRelativeToCubeVertices(Vec3f* point, Vec3f* min, Vec3f* max);
s32 Math3D_LineVsCube(Vec3f* min, Vec3f* max, Vec3f* a, Vec3f* b);
void Math3D_RotateXZPlane(Vec3f* pointOnPlane, s16 angle, f32* a, f32* c, f32* d);
void Math3D_DefPlane(Vec3f* va, Vec3f* vb, Vec3f* vc, f32* nx, f32* ny, f32* nz, f32* originDist);
f32 Math3D_UDistPlaneToPos(f32 nx, f32 ny, f32 nz, f32 originDist, Vec3f* p);
f32 Math3D_DistPlaneToPos(f32 nx, f32 ny, f32 nz, f32 originDist, Vec3f* p);
s32 Math3D_TriChkPointParaYSlopedY(Vec3f* v0, Vec3f* v1, Vec3f* v2, f32 z, f32 x);
s32 Math3D_TriChkPointParaYIntersectDist(Vec3f* v0, Vec3f* v1, Vec3f* v2, f32 nx, f32 ny, f32 nz, f32 originDist, f32 z,
                                         f32 x, f32* yIntersect, f32 chkDist);
s32 Math3D_TriChkPointParaYIntersectInsideTri(Vec3f* v0, Vec3f* v1, Vec3f* v2, f32 nx, f32 ny, f32 nz, f32 originDist,
                                              f32 z, f32 x, f32* yIntersect, f32 chkDist);
s32 Math3D_TriChkLineSegParaYIntersect(Vec3f* v0, Vec3f* v1, Vec3f* v2, f32 nx, f32 ny, f32 nz, f32 originDist, f32 z,
                                       f32 x, f32* yIntersect, f32 y0, f32 y1);
s32 Math3D_TriChkPointParaYDist(Vec3f* v0, Vec3f* v1, Vec3f* v2, Plane* plane, f32 z, f32 x, f32 chkDist);
s32 Math3D_TriChkPointParaXIntersect(Vec3f* v0, Vec3f* v1, Vec3f* v2, f32 nx, f32 ny, f32 nz, f32 originDist, f32 y,
                                     f32 z, f32* xIntersect);
s32 Math3D_TriChkLineSegParaXIntersect(Vec3f* v0, Vec3f* v1, Vec3f* v2, f32 nx, f32 ny, f32 nz, f32 originDist, f32 y,
                                       f32 z, f32* xIntersect, f32 x0, f32 x1);
s32 Math3D_TriChkPointParaXDist(Vec3f* v0, Vec3f* v1, Vec3f* v2, Plane* plane, f32 y, f32 z, f32 chkDist);
s32 Math3D_TriChkPointParaZIntersect(Vec3f* v0, Vec3f* v1, Vec3f* v2, f32 nx, f32 ny, f32 nz, f32 originDist, f32 x,
                                     f32 y, f32* zIntersect);
s32 Math3D_TriChkLineSegParaZIntersect(Vec3f* v0, Vec3f* v1, Vec3f* v2, f32 nx, f32 ny, f32 nz, f32 originDist, f32 x,
                                       f32 y, f32* zIntersect, f32 z0, f32 z1);
s32 Math3D_TriChkLineSegParaZDist(Vec3f* v0, Vec3f* v1, Vec3f* v2, Plane* plane, f32 x, f32 y, f32 chkDist);
s32 Math3D_LineSegVsPlane(f32 nx, f32 ny, f32 nz, f32 originDist, Vec3f* linePointA, Vec3f* linePointB,
                          Vec3f* intersect, s32 fromFront);
void Math3D_TriNorm(TriNorm* tri, Vec3f* va, Vec3f* vb, Vec3f* vc);
s32 Math3D_PointDistToLine2D(f32 x0, f32 y0, f32 x1, f32 y1, f32 x2, f32 y2, f32* lineLenSq);
s32 Math3D_LineVsSph(Sphere16* sphere, Linef* line);
s32 Math3D_TriVsSphIntersect(Sphere16* sphere, TriNorm* tri, Vec3f* intersectPoint);
s32 Math3D_CylVsLineSeg(Cylinder16* cyl, Vec3f* linePointA, Vec3f* linePointB, Vec3f* intersectA, Vec3f* intersectB);
s32 Math3D_CylVsTri(Cylinder16* cyl, TriNorm* tri);
s32 Math3D_CylTriVsIntersect(Cylinder16* cyl, TriNorm* tri, Vec3f* intersect);
s32 Math3D_SphVsSph(Sphere16* sphereA, Sphere16* sphereB);
s32 Math3D_SphVsSphOverlap(Sphere16* sphereA, Sphere16* sphereB, f32* overlapSize);
s32 Math3D_SphVsSphOverlapCenter(Sphere16* sphereA, Sphere16* sphereB, f32* overlapSize, f32* centerDist);
s32 Math3D_SphVsCylOverlapDist(Sphere16* sph, Cylinder16* cyl, f32* overlapSize);
s32 Math3D_SphVsCylOverlapCenterDist(Sphere16* sph, Cylinder16* cyl, f32* overlapSize, f32* centerDist);
s32 Math3D_CylOutsideCyl(Cylinder16* ca, Cylinder16* cb, f32* deadSpace);
s32 Math3D_CylOutsideCylDist(Cylinder16* ca, Cylinder16* cb, f32* deadSpace, f32* xzDist);
s32 Math3D_TriVsTriIntersect(TriNorm* ta, TriNorm* tb, Vec3f* intersect);
s32 Math3D_XZInSphere(Sphere16* sphere, f32 x, f32 z);
s32 Math3D_XYInSphere(Sphere16* sphere, f32 x, f32 y);
s32 Math3D_YZInSphere(Sphere16* sphere, f32 y, f32 z);
void Math3D_DrawSphere(PlayState* play, Sphere16* sph);
void Math3D_DrawCylinder(PlayState* play, Cylinder16* cyl);
s16 Math_Atan2S(f32 x, f32 y);
f32 Math_Atan2F(f32 x, f32 y);
void Matrix_Init(GameState* gameState);
void Matrix_Push(void);
void Matrix_Pop(void);
void Matrix_Get(MtxF* dest);
void Matrix_Put(MtxF* src);
void Matrix_Mult(MtxF* mf, u8 mode);
void Matrix_Translate(f32 x, f32 y, f32 z, u8 mode);
void Matrix_Scale(f32 x, f32 y, f32 z, u8 mode);
void Matrix_RotateX(f32 x, u8 mode);
void Matrix_RotateY(f32 y, u8 mode);
void Matrix_RotateZ(f32 z, u8 mode);
void Matrix_RotateZYX(s16 x, s16 y, s16 z, u8 mode);
void Matrix_TranslateRotateZYX(Vec3f* translation, Vec3s* rotation);
void Matrix_SetTranslateRotateYXZ(f32 translateX, f32 translateY, f32 translateZ, Vec3s* rot);
Mtx* Matrix_MtxFToMtx(MtxF* src, Mtx* dest);
Mtx* Matrix_ToMtx(Mtx* dest, char* file, s32 line);
Mtx* Matrix_NewMtx(GraphicsContext* gfxCtx, char* file, s32 line);
Mtx* Matrix_MtxFToNewMtx(MtxF* src, GraphicsContext* gfxCtx);
void Matrix_MultVec3f(Vec3f* src, Vec3f* dest);
void Matrix_MtxFCopy(MtxF* dest, MtxF* src);
void Matrix_MtxToMtxF(Mtx* src, MtxF* dest);
void Matrix_MultVec3fExt(Vec3f* src, Vec3f* dest, MtxF* mf);
void Matrix_Transpose(MtxF* mf);
void Matrix_ReplaceRotation(MtxF* mf);
void Matrix_MtxFToYXZRotS(MtxF* mf, Vec3s* rotDest, s32 flag);
void Matrix_MtxFToZYXRotS(MtxF* mf, Vec3s* rotDest, s32 flag);
void Matrix_RotateAxis(f32 angle, Vec3f* axis, u8 mode);
MtxF* Matrix_CheckFloats(MtxF* mf, char* file, s32 line);
void Matrix_SetTranslateScaleMtx2(Mtx* mtx, f32 scaleX, f32 scaleY, f32 scaleZ, f32 translateX, f32 translateY,
                                  f32 translateZ);
uintptr_t SysUcode_GetUCodeBoot(void);
uintptr_t SysUcode_GetUCodeBootSize(void);
uintptr_t SysUcode_GetUCode(void);
uintptr_t SysUcode_GetUCodeData(void);
void func_800D2E30(UnkRumbleStruct* arg0);
void func_800D3140(UnkRumbleStruct* arg0);
void func_800D3178(UnkRumbleStruct* arg0);
void func_800D31A0(void);
void func_800D31F0(void);
void func_800D3210(void);
void IrqMgr_AddClient(IrqMgr* this, IrqMgrClient* c, OSMesgQueue* msgQ);
void IrqMgr_RemoveClient(IrqMgr* this, IrqMgrClient* c);
void IrqMgr_SendMesgForClient(IrqMgr* this, OSMesg msg);
void IrqMgr_JamMesgForClient(IrqMgr* this, OSMesg msg);
void IrqMgr_HandlePreNMI(IrqMgr* this);
void IrqMgr_CheckStack();
void IrqMgr_HandlePRENMI450(IrqMgr* this);
void IrqMgr_HandlePRENMI480(IrqMgr* this);
void IrqMgr_HandlePRENMI500(IrqMgr* this);
void IrqMgr_HandleRetrace(IrqMgr* this);
void IrqMgr_ThreadEntry(void* arg0);
void IrqMgr_Init(IrqMgr* this, void* stack, OSPri pri, u8 retraceCount);
void DebugArena_CheckPointer(void* ptr, size_t size, const char* name, const char* action);
void* DebugArena_Malloc(size_t size);
void* DebugArena_MallocDebug(size_t size, const char* file, s32 line);
void* DebugArena_MallocR(size_t size);
void* DebugArena_MallocRDebug(size_t size, const char* file, s32 line);
void* DebugArena_Realloc(void* ptr, size_t newSize);
void* DebugArena_ReallocDebug(void* ptr, size_t newSize, const char* file, s32 line);
void DebugArena_Free(void* ptr);
void DebugArena_FreeDebug(void* ptr, const char* file, s32 line);
void* DebugArena_Calloc(size_t num, size_t size);
void DebugArena_Display(void);
void DebugArena_GetSizes(u32* outMaxFree, u32* outFree, u32* outAlloc);
void DebugArena_Check(void);
void DebugArena_Init(void* start, size_t size);
void DebugArena_Cleanup(void);
u8 DebugArena_IsInitalized(void);
void Fault_SleepImpl(u32);
void Fault_ClientProcessThread(void* arg);
void Fault_ProcessClientContext(FaultClientContext*);
u32 Fault_ProcessClient(u32, u32, u32);
void Fault_AddClient(FaultClient*, void*, void*, void*);
void Fault_RemoveClient(FaultClient*);
void Fault_AddAddrConvClient(FaultAddrConvClient*, void*, void*);
void Fault_RemoveAddrConvClient(FaultAddrConvClient*);
u32 Fault_ConvertAddress(FaultAddrConvClient*);
void Fault_Sleep(u32);
void Fault_PadCallback(Input*);
void Fault_UpdatePadImpl();
u32 Fault_WaitForInputImpl();
void Fault_WaitForInput();
void Fault_DrawRec(s32, s32, s32, s32, u16);
void Fault_FillScreenBlack();
void Fault_FillScreenRed();
void Fault_DrawCornerRec(u16);
void Fault_PrintFReg(s32, f32*);
void Fault_LogFReg(s32, f32*);
void Fault_PrintFPCR(u32);
void Fault_LogFPCR(u32);
void Fault_PrintThreadContext(OSThread*);
void Fault_LogThreadContext(OSThread*);
OSThread* Fault_FindFaultedThread();
void Fault_Wait5Seconds();
void Fault_WaitForButtonCombo();
void Fault_DrawMemDumpPage(const char*, u32*, u32);
void Fault_DrawMemDump(u32, u32, u32, u32);
void Fault_WalkStack(u32* spPtr, u32* pcPtr, u32* raPtr);
void Fault_DrawStackTrace(OSThread* thread, s32 x, s32 y, s32 height);
void Fault_LogStackTrace(OSThread* thread, s32 height);
void Fault_ResumeThread(OSThread*);
void Fault_CommitFB();
void Fault_ProcessClients();
void Fault_UpdatePad();
void Fault_ThreadEntry(void*);
void Fault_SetFB(void*, u16, u16);
void Fault_Init(void);
void Fault_HangupFaultClient(const char*, const char*);
void Fault_AddHungupAndCrashImpl(const char*, const char*);
void Fault_AddHungupAndCrash(const char*, u32);
void FaultDrawer_SetOsSyncPrintfEnabled(u32);
void FaultDrawer_DrawRecImpl(s32, s32, s32, s32, u16);
void FaultDrawer_DrawChar(char);
s32 FaultDrawer_ColorToPrintColor(u16);
void FaultDrawer_UpdatePrintColor();
void FaultDrawer_SetForeColor(u16);
void FaultDrawer_SetBackColor(u16);
void FaultDrawer_SetFontColor(u16);
void FaultDrawer_SetCharPad(s8, s8);
void FaultDrawer_SetCursor(s32, s32);
void FaultDrawer_FillScreen();
void* FaultDrawer_FormatStringFunc(void*, const char*, u32);
void FaultDrawer_VPrintf(const char*, va_list);
void FaultDrawer_Printf(const char*, ...);
void FaultDrawer_DrawText(s32, s32, const char*, ...);
void FaultDrawer_SetDrawerFB(void*, u16, u16);
void FaultDrawer_SetInputCallback(void (*)());
void FaultDrawer_SetDefault();
// ? UCodeDisas_TranslateAddr(?);
// ? UCodeDisas_ParseCombineColor(?);
// ? UCodeDisas_ParseCombineAlpha(?);
void UCodeDisas_Init(UCodeDisas*);
void UCodeDisas_Destroy(UCodeDisas*);
// ? UCodeDisas_SetCurUCodeImpl(?);
// ? UCodeDisas_ParseGeometryMode(?);
// ? UCodeDisas_ParseRenderMode(?);
// ? UCodeDisas_PrintVertices(?);
//void UCodeDisas_Disassemble(UCodeDisas*, Gfx*);
void UCodeDisas_RegisterUCode(UCodeDisas* this, s32 count, UCodeInfo* ucodeArray);
void UCodeDisas_SetCurUCode(UCodeDisas*, void*);
Acmd* AudioSynth_Update(Acmd* cmdStart, s32* cmdCnt, s16* aiStart, s32 aiBufLen);
void AudioHeap_DiscardFont(s32 fontId);
void AudioHeap_DiscardSequence(s32 seqId);
void AudioHeap_WritebackDCache(void* mem, size_t size);
void* AudioHeap_AllocZeroedAttemptExternal(AudioAllocPool* pool, size_t size);
void* AudioHeap_AllocAttemptExternal(AudioAllocPool* pool, size_t size);
void* AudioHeap_AllocDmaMemory(AudioAllocPool* pool, size_t size);
void* AudioHeap_AllocDmaMemoryZeroed(AudioAllocPool* pool, size_t size);
void* AudioHeap_AllocZeroed(AudioAllocPool* pool, size_t size);
void* AudioHeap_Alloc(AudioAllocPool* pool, size_t size);
void AudioHeap_AllocPoolInit(AudioAllocPool* pool, void* mem, size_t size);
void AudioHeap_PersistentCacheClear(AudioPersistentCache* persistent);
void AudioHeap_TemporaryCacheClear(AudioTemporaryCache* temporary);
void AudioHeap_PopCache(s32 tableType);
void AudioHeap_InitMainPools(size_t sizeForAudioInitPool);
void* AudioHeap_AllocCached(s32 tableType, ptrdiff_t size, s32 cache, s32 id);
void* AudioHeap_SearchCaches(s32 tableType, s32 arg1, s32 id);
void* AudioHeap_SearchRegularCaches(s32 tableType, s32 cache, s32 id);
void AudioHeap_LoadFilter(s16* filter, s32 filter1, s32 filter2);
s32 AudioHeap_ResetStep(void);
void AudioHeap_Init(void);
void* AudioHeap_SearchPermanentCache(s32 tableType, s32 id);
void* AudioHeap_AllocPermanent(s32 tableType, s32 id, size_t size);
void* AudioHeap_AllocSampleCache(size_t size, s32 fontId, void* sampleAddr, s8 medium, s32 cache);
void AudioHeap_ApplySampleBankCache(s32 sampleBankId);
void AudioLoad_DecreaseSampleDmaTtls(void);
uintptr_t AudioLoad_DmaSampleData(uintptr_t devAddr, size_t size, s32 arg2, u8* dmaIndexRef, s32 medium);
void AudioLoad_InitSampleDmaBuffers(s32 arg0);
s32 AudioLoad_IsFontLoadComplete(s32 fontId);
s32 AudioLoad_IsSeqLoadComplete(s32 seqId);
void AudioLoad_SetFontLoadStatus(s32 fontId, s32 status);
void AudioLoad_SetSeqLoadStatus(s32 seqId, s32 status);
void AudioLoad_SyncLoadSeqParts(s32 seqId, s32 arg1);
s32 AudioLoad_SyncLoadInstrument(s32 fontId, s32 instId, s32 drumId);
void AudioLoad_AsyncLoadSeq(s32 seqId, s32 arg1, s32 retData, OSMesgQueue* retQueue);
void AudioLoad_AsyncLoadSampleBank(s32 sampleBankId, s32 arg1, s32 retData, OSMesgQueue* retQueue);
void AudioLoad_AsyncLoadFont(s32 fontId, s32 arg1, s32 retData, OSMesgQueue* retQueue);
u8* AudioLoad_GetFontsForSequence(s32 seqId, u32* arg1);
void AudioLoad_DiscardSeqFonts(s32 seqId);
s32 AudioLoad_SyncInitSeqPlayer(s32 playerIdx, s32 seqId, s32 arg2);
s32 AudioLoad_SyncInitSeqPlayerSkipTicks(s32 playerIdx, s32 seqId, s32 arg2);
void AudioLoad_ProcessLoads(s32 resetStatus);
void AudioLoad_SetDmaHandler(DmaHandler callback);
void AudioLoad_Init(void* heap, size_t heapSize);
void AudioLoad_InitSlowLoads(void);
s32 AudioLoad_SlowLoadSample(s32 arg0, s32 arg1, s8* arg2);
s32 AudioLoad_SlowLoadSeq(s32 playerIdx, u8* ramAddr, s8* arg2);
void AudioLoad_InitAsyncLoads(void);
void AudioLoad_LoadPermanentSamples(void);
void AudioLoad_ScriptLoad(s32 tableType, s32 arg1, s8* arg2);
void AudioLoad_ProcessScriptLoads(void);
void AudioLoad_InitScriptLoads(void);
AudioTask* func_800E4FE0(void);
void Audio_QueueCmdF32(u32 arg0, f32 arg1);
void Audio_QueueCmdS32(u32 arg0, s32 arg1);
void Audio_QueueCmdS8(u32 arg0, s8 arg1);
void Audio_QueueCmdU16(u32 arg0, u16 arg1);
s32 Audio_ScheduleProcessCmds(void);
u32 func_800E5E20(u32* arg0);
u8* func_800E5E84(s32 arg0, u32* arg1);
s32 func_800E5EDC(void);
s32 func_800E5F88(s32 arg0);
void Audio_PreNMIInternal(void);
s32 func_800E6680(void);
u32 Audio_NextRandom(void);
void Audio_InitMesgQueues(void);
void Audio_InvalDCache(void* buf, size_t size);
void Audio_WritebackDCache(void* mem, size_t size);
s32 osAiSetNextBuffer(void* buf, size_t size);
void Audio_InitNoteSub(Note* note, NoteSubEu* sub, NoteSubAttributes* attrs);
void Audio_NoteSetResamplingRate(NoteSubEu* noteSubEu, f32 resamplingRateInput);
void Audio_NoteInit(Note* note);
void Audio_NoteDisable(Note* note);
void Audio_ProcessNotes(void);
SoundFontSound* Audio_InstrumentGetSound(Instrument* instrument, s32 semitone);
Instrument* Audio_GetInstrumentInner(s32 fontId, s32 instId);
Drum* Audio_GetDrum(s32 fontId, s32 drumId);
SoundFontSound* Audio_GetSfx(s32 fontId, s32 sfxId);
s32 Audio_SetFontInstrument(s32 instrumentType, s32 fontId, s32 index, void* value);
void Audio_SeqLayerDecayRelease(SequenceLayer* layer, s32 target);
void Audio_SeqLayerNoteDecay(SequenceLayer* layer);
void Audio_SeqLayerNoteRelease(SequenceLayer* layer);
s32 Audio_BuildSyntheticWave(Note* note, SequenceLayer* layer, s32 waveId);
void Audio_InitSyntheticWave(Note* note, SequenceLayer* layer);
void Audio_InitNoteList(AudioListItem* list);
void Audio_InitNoteLists(NotePool* pool);
void Audio_InitNoteFreeList(void);
void Audio_NotePoolClear(NotePool* pool);
void Audio_NotePoolFill(NotePool* pool, s32 count);
void Audio_AudioListPushFront(AudioListItem* list, AudioListItem* item);
void Audio_AudioListRemove(AudioListItem* item);
Note* Audio_FindNodeWithPrioLessThan(AudioListItem* list, s32 limit);
void Audio_NoteInitForLayer(Note* note, SequenceLayer* layer);
void func_800E82C0(Note* note, SequenceLayer* layer);
void Audio_NoteReleaseAndTakeOwnership(Note* note, SequenceLayer* layer);
Note* Audio_AllocNoteFromDisabled(NotePool* pool, SequenceLayer* layer);
Note* Audio_AllocNoteFromDecaying(NotePool* pool, SequenceLayer* layer);
Note* Audio_AllocNoteFromActive(NotePool* pool, SequenceLayer* layer);
Note* Audio_AllocNote(SequenceLayer* layer);
void Audio_NoteInitAll(void);
void Audio_SequenceChannelProcessSound(SequenceChannel* channel, s32 recalculateVolume, s32 b);
void Audio_SequencePlayerProcessSound(SequencePlayer* seqPlayer);
f32 Audio_GetPortamentoFreqScale(Portamento* p);
s16 Audio_GetVibratoPitchChange(VibratoState* vib);
f32 Audio_GetVibratoFreqScale(VibratoState* vib);
void Audio_NoteVibratoUpdate(Note* note);
void Audio_NoteVibratoInit(Note* note);
void Audio_NotePortamentoInit(Note* note);
void Audio_AdsrInit(AdsrState* adsr, AdsrEnvelope* envelope, s16* volOut);
f32 Audio_AdsrUpdate(AdsrState* adsr);
void AudioSeq_SequenceChannelDisable(SequenceChannel* channel);
void AudioSeq_SequencePlayerDisableAsFinished(SequencePlayer* seqPlayer);
void AudioSeq_SequencePlayerDisable(SequencePlayer* seqPlayer);
void AudioSeq_AudioListPushBack(AudioListItem* list, AudioListItem* item);
void* AudioSeq_AudioListPopBack(AudioListItem* list);
void AudioSeq_ProcessSequences(s32 arg0);
void AudioSeq_SkipForwardSequence(SequencePlayer* seqPlayer);
void AudioSeq_ResetSequencePlayer(SequencePlayer* seqPlayer);
void AudioSeq_InitSequencePlayerChannels(s32 playerIdx);
void AudioSeq_InitSequencePlayers(void);
void func_800ECC04(u16);
void Audio_OcaSetInstrument(u8);
void Audio_OcaSetSongPlayback(s8 songIdxPlusOne, s8 playbackState);
void Audio_OcaSetRecordingState(u8);
OcarinaStaff* Audio_OcaGetRecordingStaff(void);
OcarinaStaff* Audio_OcaGetPlayingStaff(void);
OcarinaStaff* Audio_OcaGetDisplayingStaff(void);
void Audio_OcaMemoryGameStart(u8 minigameIdx);
s32 Audio_OcaMemoryGameGenNote(void);
void func_800EE824(void);
void AudioDebug_Draw(GfxPrint* printer);
void AudioDebug_ScrPrt(const s8* str, u16 num);
void func_800F3054(void);
void Audio_SetSoundProperties(u8 bankId, u8 entryIdx, u8 channelIdx);
void func_800F3F3C(u8);
void func_800F4010(Vec3f* pos, u16 sfxId, f32);
void Audio_PlaySoundRandom(Vec3f* pos, u16 baseSfxId, u8 randLim);
void func_800F4138(Vec3f* pos, u16 sfxId, f32);
void func_800F4190(Vec3f* pos, u16 sfxId);
void func_800F436C(Vec3f* pos, u16 sfxId, f32 arg2);
void func_800F4414(Vec3f* pos, u16 sfxId, f32);
void func_800F44EC(s8 arg0, s8 arg1);
void func_800F4524(Vec3f* pos, u16 sfxId, s8 arg2);
void func_800F4254(Vec3f* pos, u8 arg1);
void func_800F436C(Vec3f*, u16 sfxId, f32 arg2);
void func_800F4414(Vec3f*, u16 sfxId, f32 arg2);
void Audio_PlaySoundRiver(Vec3f* pos, f32 freqScale);
void Audio_PlaySoundWaterfall(Vec3f* pos, f32 freqScale);
void func_800F47BC(void);
void func_800F47FC(void);
void func_800F483C(u8 targetVol, u8 volFadeTimer);
void func_800F4870(u8);
void func_800F4A54(u8);
void Audio_PlaySoundIncreasinglyTransposed(Vec3f* pos, s16 sfxId, u8* semitones);
void Audio_ResetIncreasingTranspose(void);
void Audio_PlaySoundTransposed(Vec3f* pos, u16 sfxId, s8 semitone);
void func_800F4C58(Vec3f* pos, u16 sfxId, u8);
void func_800F4E30(Vec3f* pos, f32);
void Audio_ClearSariaBgm(void);
void Audio_ClearSariaBgmAtPos(Vec3f* pos);
void Audio_PlaySariaBgm(Vec3f* pos, u16 seqId, u16 distMax);
void Audio_ClearSariaBgm2(void);
void func_800F5510(u16 seqId);
void func_800F5550(u16 seqId);
void func_800F574C(f32 arg0, u8 arg2);
void func_800F5718(void);
void func_800F5918(void);
void func_800F595C(u16);
void func_800F59E8(u16);
s32 func_800F5A58(u8);
void func_800F5ACC(u16 seqId);
void PreviewSequence(u16 seqId);
void func_800F5B58(void);
void func_800F5BF0(u8 natureAmbienceId);
void Audio_PlayFanfare(u16);
void Audio_PlayFanfare_Rando(GetItemEntry getItem);
void func_800F5C2C(void);
void func_800F5E18(u8 playerIdx, u16 seqId, u8 fadeTimer, s8 arg3, s8 arg4);
void Audio_SetSequenceMode(u8 seqMode);
void Audio_SetBgmEnemyVolume(f32 dist);
void func_800F6268(f32 dist, u16);
void func_800F64E0(u8 arg0);
void func_800F6584(u8 arg0);
void Audio_SetEnvReverb(s8 reverb);
void Audio_SetCodeReverb(s8 reverb);
void func_800F6700(s8 outputMode);
void Audio_SetBaseFilter(u8);
void Audio_SetExtraFilter(u8);
void Audio_SetCutsceneFlag(s8 flag);
void Audio_PlaySoundIfNotInCutscene(u16 sfxId);
void func_800F6964(u16);
void func_800F6AB0(u16);
// ? Audio_DisableAllSeq(?);
// ? func_800F6BB8(?);
void Audio_PreNMI();
// ? func_800F6C34(?);
void Audio_SetNatureAmbienceChannelIO(u8 channelIdxRange, u8 port, u8 val);
void Audio_PlayNatureAmbienceSequence(u8 natureAmbienceId);
void Audio_Init();
void Audio_InitSound();
void func_800F7170(void);
void func_800F71BC(s32 arg0);
void Audio_SetSoundBanksMute(u16 muteMask);
void Audio_QueueSeqCmdMute(u8 channelIdx);
void Audio_ClearBGMMute(u8 channelIdx);
void Audio_PlaySoundGeneral(u16 sfxId, Vec3f* pos, u8 token, f32* freqScale, f32* a4, s8* reverbAdd);
void Audio_ProcessSoundRequest(void);
void Audio_ChooseActiveSounds(u8 bankId);
void Audio_PlayActiveSounds(u8 bankId);
void Audio_StopSfxByBank(u8 bankId);
void func_800F8884(u8, Vec3f*);
void Audio_StopSfxByPosAndBank(u8, Vec3f*);
void Audio_StopSfxByPos(Vec3f*);
void func_800F9280(u8 playerIdx, u8 seqId, u8 arg2, u16 fadeTimer);
void Audio_QueueSeqCmd(u32 bgmID);
void Audio_QueuePreviewSeqCmd(u16 seqId);
void Audio_StopSfxByPosAndId(Vec3f* pos, u16 sfxId);
void Audio_StopSfxByTokenAndId(u8, u16);
void Audio_StopSfxById(u32 sfxId);
void Audio_ProcessSoundRequests(void);
void func_800F8F88(void);
u8 Audio_IsSfxPlaying(u32 sfxId);
void Audio_ResetSounds(void);
void func_800F9474(u8, u16);
void func_800F94FC(u32);
void Audio_ProcessSeqCmd(u32);
void Audio_ProcessSeqCmds(void);
u16 func_800FA0B4(u8 a0);
s32 func_800FA11C(u32 arg0, u32 arg1);
void func_800FA174(u8);
void func_800FA18C(u8, u8);
void Audio_SetVolScale(u8 playerIdx, u8 scaleIdx, u8 targetVol, u8 volFadeTimer);
void func_800FA3DC(void);
u8 func_800FAD34(void);
void Audio_ResetActiveSequences(void);
void func_800FAEB4(void);
void GfxPrint_SetColor(GfxPrint* this, u32 r, u32 g, u32 b, u32 a);
void GfxPrint_SetPosPx(GfxPrint* this, s32 x, s32 y);
void GfxPrint_SetPos(GfxPrint* this, s32 x, s32 y);
void GfxPrint_SetBasePosPx(GfxPrint* this, s32 x, s32 y);
void GfxPrint_Init(GfxPrint* this);
void GfxPrint_Destroy(GfxPrint* this);
void GfxPrint_Open(GfxPrint* this, Gfx* dList);
Gfx* GfxPrint_Close(GfxPrint* this);
s32 GfxPrint_Printf(GfxPrint* this, const char* fmt, ...);
void func_800FBCE0();
void func_800FBFD8(void);
void* Overlay_AllocateAndLoad(uintptr_t vRomStart, uintptr_t vRomEnd, void* vRamStart, void* vRamEnd);
void MtxConv_F2L(Mtx* m1, MtxF* m2);
void MtxConv_L2F(MtxF* m1, Mtx* m2);
void Overlay_Relocate(void* allocatedVRamAddress, OverlayRelocationSection* overlayInfo, void* vRamAddress);
s32 Overlay_Load(uintptr_t vRomStart, uintptr_t vRomEnd, void* vRamStart, void* vRamEnd, void* allocatedVRamAddress);
// ? func_800FC800(?);
// ? func_800FC83C(?);
// ? func_800FCAB4(?);
void SystemHeap_Init(void* start, size_t size);
void PadUtils_Init(Input* input);
void func_800FCB70(void);
void PadUtils_ResetPressRel(Input* input);
u32 PadUtils_CheckCurExact(Input* input, u16 value);
u32 PadUtils_CheckCur(Input* input, u16 key);
u32 PadUtils_CheckPressed(Input* input, u16 key);
u32 PadUtils_CheckReleased(Input* input, u16 key);
u16 PadUtils_GetCurButton(Input* input);
u16 PadUtils_GetPressButton(Input* input);
s8 PadUtils_GetCurX(Input* input);
s8 PadUtils_GetCurY(Input* input);
void PadUtils_SetRelXY(Input* input, s32 x, s32 y);
s8 PadUtils_GetRelXImpl(Input* input);
s8 PadUtils_GetRelYImpl(Input* input);
s8 PadUtils_GetRelX(Input* input);
s8 PadUtils_GetRelY(Input* input);
void PadUtils_UpdateRelXY(Input* input);
s8 PadUtils_GetCurRX(Input* input);
s8 PadUtils_GetCurRY(Input* input);
void PadUtils_SetRelRXY(Input* input, s32 x, s32 y);
s8 PadUtils_GetRelRXImpl(Input* input);
s8 PadUtils_GetRelRYImpl(Input* input);
s8 PadUtils_GetRelRX(Input* input);
s8 PadUtils_GetRelRY(Input* input);
void PadUtils_UpdateRelRXY(Input* input);
s32 PadSetup_Init(OSMesgQueue* mq, u8* outMask, OSContStatus* status);
f32 Math_FTanF(f32 x);
f32 Math_FFloorF(f32 x);
f32 Math_FCeilF(f32 x);
f32 Math_FRoundF(f32 x);
f32 Math_FNearbyIntF(f32 x);
f32 Math_FTruncF(f32 x);
f32 Math_FAtanF(f32 x);
f32 Math_FAtan2F(f32 y, f32 x);
f32 Math_FAsinF(f32 x);
f32 Math_FAcosF(f32 x);
/*f32 ceilf(f32 x);
f32 truncf(f32 x);
f32 roundf(f32 x);
f32 nearbyintf(f32 x);*/
void SystemArena_CheckPointer(void* ptr, size_t size, const char* name, const char* action);
void* SystemArena_Malloc(size_t size);
void* SystemArena_MallocDebug(size_t size, const char* file, s32 line);
void* SystemArena_MallocR(size_t size);
void* SystemArena_MallocRDebug(size_t size, const char* file, s32 line);
void* SystemArena_Realloc(void* ptr, size_t newSize);
void* SystemArena_ReallocDebug(void* ptr, size_t newSize, const char* file, s32 line);
void SystemArena_Free(void* ptr);
void SystemArena_FreeDebug(void* ptr, const char* file, s32 line);
void* SystemArena_Calloc(size_t num, size_t size);
void SystemArena_Display(void);
void SystemArena_GetSizes(u32* outMaxFree, u32* outFree, u32* outAlloc);
void SystemArena_Check(void);
void SystemArena_Init(void* start, size_t size);
void SystemArena_Cleanup(void);
u8 SystemArena_IsInitalized(void);
u32 Rand_Next(void);
void Rand_Seed(u32 seed);
f32 Rand_ZeroOne(void);
f32 Rand_Centered(void);
void Rand_Seed_Variable(u32* rndNum, u32 seed);
u32 Rand_Next_Variable(u32* rndNum);
f32 Rand_ZeroOne_Variable(u32* rndNum);
f32 Rand_Centered_Variable(u32* rndNum);
u32 ArenaImpl_GetFillAllocBlock(Arena* arena);
u32 ArenaImpl_GetFillFreeBlock(Arena* arena);
u32 ArenaImpl_GetCheckFreeBlock(Arena* arena);
void ArenaImpl_SetFillAllocBlock(Arena* arena);
void ArenaImpl_SetFillFreeBlock(Arena* arena);
void ArenaImpl_SetCheckFreeBlock(Arena* arena);
void ArenaImpl_UnsetFillAllocBlock(Arena* arena);
void ArenaImpl_UnsetFillFreeBlock(Arena* arena);
void ArenaImpl_UnsetCheckFreeBlock(Arena* arena);
void ArenaImpl_SetDebugInfo(ArenaNode* node, const char* file, s32 line, Arena* arena);
void ArenaImpl_LockInit(Arena* arena);
void ArenaImpl_Lock(Arena* arena);
void ArenaImpl_Unlock(Arena* arena);
ArenaNode* ArenaImpl_GetNextBlock(ArenaNode* node);
ArenaNode* ArenaImpl_GetPrevBlock(ArenaNode* node);
ArenaNode* ArenaImpl_GetLastBlock(Arena* arena);
void __osMallocInit(Arena* arena, void* start, size_t size);
void __osMallocAddBlock(Arena* arena, void* start, ptrdiff_t size);
void ArenaImpl_RemoveAllBlocks(Arena* arena);
void __osMallocCleanup(Arena* arena);
u8 __osMallocIsInitalized(Arena* arena);
void __osMalloc_FreeBlockTest(Arena* arena, ArenaNode* node);
void* __osMalloc_NoLockDebug(Arena* arena, size_t size, const char* file, s32 line);
void* __osMallocDebug(Arena* arena, size_t size, const char* file, s32 line);
void* __osMallocRDebug(Arena* arena, size_t size, const char* file, s32 line);
void* __osMalloc_NoLock(Arena* arena, size_t size);
void* __osMalloc(Arena* arena, size_t size);
void* __osMallocR(Arena* arena, size_t size);
void __osFree_NoLock(Arena* arena, void* ptr);
void __osFree(Arena* arena, void* ptr);
void __osFree_NoLockDebug(Arena* arena, void* ptr, const char* file, s32 line);
void __osFreeDebug(Arena* arena, void* ptr, const char* file, s32 line);
void* __osRealloc(Arena* arena, void* ptr, size_t newSize);
void* __osReallocDebug(Arena* arena, void* ptr, size_t newSize, const char* file, s32 line);
void ArenaImpl_GetSizes(Arena* arena, u32* outMaxFree, u32* outFree, u32* outAlloc);
void __osDisplayArena(Arena* arena);
void ArenaImpl_FaultClient(Arena* arena);
u32 __osCheckArena(Arena* arena);
u8 func_800FF334(Arena* arena);
s32 PrintUtils_VPrintf(PrintCallback* pfn, const char* fmt, va_list args);
s32 PrintUtils_Printf(PrintCallback* pfn, const char* fmt, ...);
void Sleep_Cycles(OSTime cycles);
void Sleep_Nsec(u32 nsec);
void Sleep_Usec(u32 usec);
void Sleep_Msec(u32 ms);
void Sleep_Sec(u32 sec);
void JpegUtils_ProcessQuantizationTable(u8* dqt, JpegQuantizationTable* qt, u8 count);
s32 JpegUtils_ParseHuffmanCodesLengths(u8* ptr, u8* codesLengths);
s32 JpegUtils_GetHuffmanCodes(u8* codesLengths, u16* codes);
s32 JpegUtils_SetHuffmanTable(u8* data, JpegHuffmanTable* ht, u16* codes);
u32 JpegUtils_ProcessHuffmanTableImpl(u8* data, JpegHuffmanTable* ht, u8* codesLengths, u16* codes, u8 isAc);
u32 JpegUtils_ProcessHuffmanTable(u8* dht, JpegHuffmanTable* ht, u8* codesLengths, u16* codes, u8 count);
void JpegUtils_SetHuffmanTableOld(u8* data, JpegHuffmanTableOld* ht, u8* codesLengths, u16* codes, s16 count, u8 isAc);
u32 JpegUtils_ProcessHuffmanTableImplOld(u8* dht, JpegHuffmanTableOld* ht, u8* codesLengths, u16* codes);
s32 JpegDecoder_Decode(JpegDecoder* decoder, u16* mcuBuff, s32 count, u8 isFollowing, JpegDecoderState* state);
s32 JpegDecoder_ProcessMcu(JpegHuffmanTable* hTable0, JpegHuffmanTable* hTable1, u16* mcu, s16* unk);
s32 JpegDecoder_ParseNextSymbol(JpegHuffmanTable* hTable, s16* outCoeff, s8* outZeroCount);
u16 JpegDecoder_ReadBits(u8 len);
s32 osPfsFreeBlocks(OSPfs* pfs, s32* leftoverBytes);
void guScale(Mtx* m, f32 x, f32 y, f32 z);
s16 sins(u16);
OSTask* _VirtualToPhysicalTask(OSTask* intp);
void osSpTaskLoad(OSTask* task);
void osSpTaskStartGo(OSTask* task);
void __osSiCreateAccessQueue(void);
void __osSiGetAccess(void);
void __osSiRelAccess(void);
s32 osContInit(OSMesgQueue* mq, u8* ctl_present_bitfield, OSContStatus* status);
void __osContGetInitData(u8* ctl_present_bitfield, OSContStatus* status);
void __osPackRequestData(u8 poll);
s32 osContStartReadData(OSMesgQueue* mq);
void osContGetReadData(OSContPad* pad);
void __osPackReadData(void);
void guPerspectiveF(f32 mf[4][4], u16* perspNorm, f32 fovy, f32 aspect, f32 near, f32 far, f32 scale);
void guPerspective(Mtx* m, u16* perspNorm, f32 fovy, f32 aspect, f32 near, f32 far, f32 scale);
s32 __osSpRawStartDma(s32 direction, void* devAddr, void* dramAddr, size_t size);
s32 __osSiRawStartDma(s32 dir, void* addr);
void osSpTaskYield(void);
s32 __osPfsGetNextPage(OSPfs* pfs, u8* bank, __OSInode* inode, __OSInodeUnit* page);
s32 osPfsReadWriteFile(OSPfs* pfs, s32 fileNo, u8 flag, s32 offset, ptrdiff_t size, u8* data);
s32 __osPfsGetStatus(OSMesgQueue* queue, s32 channel);
void __osPfsRequestOneChannel(s32 channel, u8 poll);
void __osPfsGetOneChannelData(s32 channel, OSContStatus* contData);
void guMtxIdentF(f32 mf[4][4]);
void guLookAtF(f32 mf[4][4], f32 xEye, f32 yEye, f32 zEye, f32 xAt, f32 yAt, f32 zAt, f32 xUp, f32 yUp, f32 zUp);
void guLookAt(Mtx*, f32 xEye, f32 yEye, f32 zEye, f32 xAt, f32 yAt, f32 zAt, f32 xUp, f32 yUp, f32 zUp);
s32 osPfsAllocateFile(OSPfs* pfs, u16 companyCode, u32 gameCode, u8* gameName, u8* extName, s32 length, s32* fileNo);
s32 __osPfsDeclearPage(OSPfs* pfs, __OSInode* inode, s32 fileSizeInPages, s32* startPage, u8 bank, s32* decleared,
                       s32* finalPage);
s32 osStopTimer(OSTimer* timer);
u16 __osSumcalc(u8* ptr, s32 length);
s32 __osIdCheckSum(u16* ptr, u16* csum, u16* icsum);
s32 __osRepairPackId(OSPfs* pfs, __OSPackId* badid, __OSPackId* newid);
s32 __osCheckPackId(OSPfs* pfs, __OSPackId* check);
s32 __osGetId(OSPfs* pfs);
s32 __osCheckId(OSPfs* pfs);
s32 __osPfsRWInode(OSPfs* pfs, __OSInode* inode, u8 flag, u8 bank);
void guMtxL2F(MtxF* m1, Mtx* m2);
s32 osPfsFindFile(OSPfs* pfs, u16 companyCode, u32 gameCode, u8* gameName, u8* extName, s32* fileNo);
s32 osAfterPreNMI(void);
s32 osContStartQuery(OSMesgQueue* mq);
void osContGetQuery(OSContStatus* data);
void guLookAtHiliteF(f32 mf[4][4], LookAt* l, Hilite* h, f32 xEye, f32 yEye, f32 zEye, f32 xAt, f32 yAt, f32 zAt,
                     f32 xUp, f32 yUp, f32 zUp, f32 xl1, f32 yl1, f32 zl1, f32 xl2, f32 yl2, f32 zl2, s32 hiliteWidth,
                     s32 hiliteHeight);
void guLookAtHilite(Mtx* m, LookAt* l, Hilite* h, f32 xEye, f32 yEye, f32 zEye, f32 xAt, f32 yAt, f32 zAt, f32 xUp,
                    f32 yUp, f32 zUp, f32 xl1, f32 yl1, f32 zl1, f32 xl2, f32 yl2, f32 zl2, s32 hiliteWidth,
                    s32 hiliteHeight);
u32 __osSpDeviceBusy(void);
void guMtxIdent(Mtx*);
void guPositionF(f32 mf[4][4], f32 rot, f32 pitch, f32 yaw, f32 scale, f32 x, f32 y, f32 z);
void guPosition(Mtx*, f32, f32, f32, f32, f32, f32, f32);
OSYieldResult osSpTaskYielded(OSTask* task);
void guRotateF(f32 m[4][4], f32 a, f32 x, f32 y, f32 z);
void guRotate(Mtx*, f32 angle, f32 x, f32 y, f32 z);
s32 osAiSetFrequency(u32 frequency);
OSThread* __osGetActiveQueue(void);
void guNormalize(f32* x, f32* y, f32* z);
u32 osDpGetStatus(void);
void osDpSetStatus(u32 status);
s32 osPfsDeleteFile(OSPfs* pfs, u16 companyCode, u32 gameCode, u8* gameName, u8* extName);
s32 __osPfsReleasePages(OSPfs* pfs, __OSInode* inode, u8 initialPage, u8 bank, __OSInodeUnit* finalPage);
void guOrthoF(f32[4][4], f32, f32, f32, f32, f32, f32, f32);
void guOrtho(Mtx*, f32, f32, f32, f32, f32, f32, f32);
s16 coss(u16);
void osViSetEvent(OSMesgQueue* mq, OSMesg m, u32 retraceCount);
s32 osPfsIsPlug(OSMesgQueue* mq, u8* pattern);
void __osPfsRequestData(u8 poll);
void __osPfsGetInitData(u8* pattern, OSContStatus* contData);
#ifndef __cplusplus
void guS2DInitBg(uObjBg* bg);
#endif
s32 __osPfsSelectBank(OSPfs* pfs, u8 bank);
s32 osContSetCh(u8 ch);
s32 osPfsFileState(OSPfs* pfs, s32 fileNo, OSPfsState* state);
s32 osPfsInitPak(OSMesgQueue* mq, OSPfs* pfs, s32 channel);
s32 __osPfsCheckRamArea(OSPfs* pfs);
s32 osPfsChecker(OSPfs* pfs);
s32 func_80105788(OSPfs* pfs, __OSInodeCache* cache);
s32 func_80105A60(OSPfs* pfs, __OSInodeUnit fpage, __OSInodeCache* cache);
u32 osAiGetLength(void);
void guTranslate(Mtx* m, f32 x, f32 y, f32 z);
s32 __osContRamWrite(OSMesgQueue* mq, s32 channel, u16 address, u8* buffer, s32 force);
s32 __osContRamRead(OSMesgQueue* ctrlrqueue, s32 channel, u16 addr, u8* data);
u8 __osContAddressCrc(u16 addr);
u8 __osContDataCrc(u8* data);
s32 osSetTimer(OSTimer* timer, OSTime countdown, OSTime interval, OSMesgQueue* mq, OSMesg msg);
u32 __osSpGetStatus(void);
void __osSpSetStatus(u32 status);
void osWritebackDCacheAll(void);
OSThread* __osGetCurrFaultedThread(void);
void guMtxF2L(MtxF* m1, Mtx* m2);
// ? __d_to_ll(?);
// ? __f_to_ll(?);
// ? __d_to_ull(?);
// ? __f_to_ull(?);
// ? __ll_to_d(?);
// ? __ll_to_f(?);
// ? __ull_to_d(?);
// ? __ull_to_f(?);
u32* osViGetCurrentFramebuffer(void);
s32 __osSpSetPc(void* pc);
f32 absf(f32);
void* func_801068B0(void* dst, void* src, size_t size);
void Message_UpdateOcarinaGame(PlayState* play);
u8 Message_ShouldAdvance(PlayState* play);
u8 Message_ShouldAdvanceSilent(PlayState* play);
void Message_CloseTextbox(PlayState*);
void Message_StartTextbox(PlayState* play, u16 textId, Actor* actor);
void Message_ContinueTextbox(PlayState* play, u16 textId);
void func_8010BD58(PlayState* play, u16 arg1);
void func_8010BD88(PlayState* play, u16 arg1);
u8 Message_GetState(MessageContext* msgCtx);
void Message_Draw(PlayState* play);
void Message_Update(PlayState* play);
void Message_SetTables(void);
f32 Message_GetCharacterWidth(unsigned char characterIndex);
void GameOver_Init(PlayState* play);
void GameOver_FadeInLights(PlayState* play);
void GameOver_Update(PlayState* play);
void func_80110990(PlayState* play);
void func_801109B0(PlayState* play);
void Message_Init(PlayState* play);
void Regs_InitData(PlayState* play);

void Title_Init(GameState* thisx);
void Title_PrintBuildInfo(Gfx** gfxp);
void Title_Destroy(GameState* thisx);
void Select_Init(GameState* thisx);
void Select_Destroy(GameState* thisx);
void Opening_Init(GameState* thisx);
void Opening_Destroy(GameState* thisx);
void FileChoose_Init(GameState* thisx);
void FileChoose_Destroy(GameState* thisx);

void Heaps_Alloc(void);
void Heaps_Free(void);

CollisionHeader* BgCheck_GetCollisionHeader(CollisionContext* colCtx, s32 bgId);

// Exposing these methods to leverage them from the file select screen to render messages
void Message_OpenText(PlayState* play, u16 textId);
void Message_Decode(PlayState* play);
void Message_DrawText(PlayState* play, Gfx** gfxP);

// #region SOH [General]

void Interface_CreateQuadVertexGroup(Vtx* vtxList, s32 xStart, s32 yStart, s32 width, s32 height, u8 flippedH);
void Interface_RandoRestoreSwordless(void);

//Pause Warp
void PauseWarp_HandleSelection();
void PauseWarp_Execute();

// #endregion

//ipi: Additional general-use functions
s16 Actor_CrazyModeInitCivilianDamage(ColliderCylinder* cylinderCollider);
s16 Actor_CrazyModeCheckCivilianDamage(PlayState* play, Actor* actor, ColliderCylinder* cylinderCollider);

//ipi: Allow the player to be randomly ambushed by enemies
typedef enum {
    ENEMY_AMBUSH_STATUS_INVALID,
    ENEMY_AMBUSH_STATUS_DELAYED,
    ENEMY_AMBUSH_STATUS_READY,
} EnemyAmbushStatus;
EnemyAmbushStatus Player_GetEnemyAmbushTable(PlayState* play, CrazyModeEnemyAmbush** outTable, s32* outLength);

//ipi: Prevent further action if the shooting gallery cucco has been hit
s16 Play_HasHitShootingGalleryCucco(PlayState* play);

#ifdef __cplusplus
#undef this
};
#undef this
#endif

#endif
