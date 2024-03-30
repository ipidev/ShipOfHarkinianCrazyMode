/*
 * File: z_en_vase.c
 * Overlay: ovl_En_Vase
 * Description: An unused, orange pot based on ALTTP. Lacks collision.
 */

#include "z_en_vase.h"
#include "objects/object_vase/object_vase.h"

//ipi: Make this unused actor into an ice block instead
#include "objects/gameplay_dangeon_keep/gameplay_dangeon_keep.h"
#include "objects/object_spot08_obj/object_spot08_obj.h"
#include <string.h> // memcpy

#define FLAGS ACTOR_FLAG_UPDATE_WHILE_CULLED

void EnVase_Init(Actor* thisx, PlayState* play);
void EnVase_Update(Actor* thisx, PlayState* play);
void EnVase_Destroy(Actor* thisx, PlayState* play);
void EnVase_Draw(Actor* thisx, PlayState* play);

const ActorInit En_Vase_InitVars = {
    ACTOR_EN_VASE,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_VASE,
    sizeof(EnVase),
    (ActorFunc)EnVase_Init,
    (ActorFunc)EnVase_Destroy,
    (ActorFunc)EnVase_Update,
    (ActorFunc)EnVase_Draw,
    NULL,
};

//ipi: Make this unused actor into an ice block instead
static InitChainEntry sInitChain[] = {
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 1800, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 500, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 1500, ICHAIN_STOP),
};

enum
{
    VASE_PHASE_GROW,
    VASE_PHASE_WAIT,
    VASE_PHASE_MELT,
};

#define EN_VASE_FINAL_SCALE 0.1f
#define EN_VASE_MODEL_SIZE 256.0f

//From z_obj_ice_poly.c
static Color_RGBA8 sColorWhite = { 250, 250, 250, 255 };
static Color_RGBA8 sColorGray = { 180, 180, 180, 255 };

void EnVase_Init(Actor* thisx, PlayState* play) {
    EnVase* this = (EnVase*)thisx;

    //ipi: Make this unused actor into an ice block instead
    static CollisionHeader sColHeader;
    static u8 sHasInitalizedColHeader = false;
    if (!sHasInitalizedColHeader) {
        sHasInitalizedColHeader = true;

        //Should take the shape of the push block
        CollisionHeader* pushBlockColHeader;
        CollisionHeader_GetVirtual(&gPushBlockCol, &pushBlockColHeader);
        memcpy(&sColHeader, pushBlockColHeader, sizeof(CollisionHeader));

        //Copy the ice properties from the Zora's Fountain icebergs
        CollisionHeader* icebergColHeader;
        CollisionHeader_GetVirtual(&gZorasFountainIcebergCol, &icebergColHeader);
        sColHeader.surfaceTypeList = icebergColHeader->surfaceTypeList;
    }

    DynaPolyActor_Init(&this->dyna, 0);
    this->dyna.bgId = DynaPoly_SetBgActor(play, &play->colCtx.dyna, &this->dyna.actor, &sColHeader);
    Actor_ProcessInitChain(&this->dyna.actor, sInitChain);

    //Start small and grow
    Actor_SetScale(&this->dyna, 0.001f);
    this->timer = 0;
    this->phase = VASE_PHASE_GROW;

    Audio_PlayActorSound2(&this->dyna.actor, NA_SE_EV_ICE_FREEZE);
}

void EnVase_Destroy(Actor* thisx, PlayState* play) {
    EnVase* this = (EnVase*)thisx;
    DynaPoly_DeleteBgActor(play, &play->colCtx.dyna, this->dyna.bgId);
}

void EnVase_Update(Actor* thisx, PlayState* play) {
    EnVase* this = (EnVase*)thisx;
    f32 scale = this->dyna.actor.scale.y;

    switch (this->phase) {
        case VASE_PHASE_GROW:
            Math_SmoothStepToF(&scale, EN_VASE_FINAL_SCALE, 0.25f, 0.025f, 0.001f);
            Actor_SetScale(&this->dyna, scale);
            if (scale >= EN_VASE_FINAL_SCALE) {
                this->phase = VASE_PHASE_WAIT;
                Audio_StopSfxById(NA_SE_EV_ICE_FREEZE);
            }
            break;
        
        case VASE_PHASE_WAIT:
            this->timer++;
            if (this->timer >= 200) {
                Audio_PlayActorSound2(&this->dyna.actor, NA_SE_EV_ICE_MELT);
                this->phase = VASE_PHASE_MELT;
            }
            break;

        case VASE_PHASE_MELT:
            Math_StepToF(&scale, 0.0f, 0.00333f);
            this->dyna.actor.scale.y = scale;

            //Spawn melt effects
            Vec3f velocity;
            VEC_SET(velocity, 0.0f, this->dyna.actor.scale.y * 10.0f, 0.0f);
            Vec3f pos;
            Math_Vec3f_Copy(&pos, &this->dyna.actor.world.pos);

            pos.x += 2.0f * Rand_Centered() * (EN_VASE_FINAL_SCALE * EN_VASE_MODEL_SIZE);
            pos.y += 2.0f * Rand_ZeroOne() * (scale * EN_VASE_MODEL_SIZE);
            pos.z += 2.0f * Rand_Centered() * (EN_VASE_FINAL_SCALE * EN_VASE_MODEL_SIZE);
            func_8002829C(play, &pos, &velocity, &velocity, &sColorWhite, &sColorGray,
                      (scale + 0.2f) * Rand_S16Offset(0xC00, 0x100), 15);
            break;
    }
    
    //Update position based on scale
    this->dyna.actor.world.pos.y = this->dyna.actor.home.pos.y - (EN_VASE_MODEL_SIZE * scale);

    //Destroy when fully melted
    if (scale <= 0.0f) {
        Actor_Kill(&this->dyna.actor);
    }
}

void EnVase_Draw(Actor* thisx, PlayState* play) {
    //ipi: Make this unused actor into an ice block instead
    EnVase* this = (EnVase*)thisx;

    OPEN_DISPS(play->state.gfxCtx);

    Gfx_SetupDL_25Opa(play->state.gfxCtx);
    func_8002ED80(&this->dyna.actor, play, 0); //Does this do anything?

    gSPSegment(POLY_OPA_DISP++, 0x08, SEGMENTED_TO_VIRTUAL(gZorasFountainIcebergSideTex));
    gSPMatrix(POLY_OPA_DISP++, MATRIX_NEWMTX(play->state.gfxCtx),
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0x80, 192, 224, 255, 128);
    gDPSetEnvColor(POLY_OPA_DISP++, 192, 224, 255, 128);
    gSPDisplayList(POLY_OPA_DISP++, gPushBlockDL);

    CLOSE_DISPS(play->state.gfxCtx);
}
