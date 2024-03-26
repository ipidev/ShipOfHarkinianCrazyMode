/*
 * File: z_en_tg.c
 * Overlay: ovl_En_Tg
 * Description: Dancing Couple
 */

#include "z_en_tg.h"
#include "objects/object_mu/object_mu.h"

//ipi: To explode
#include "overlays/actors/ovl_En_Bom/z_en_bom.h"

//ipi: Update while offscreen
#define FLAGS (ACTOR_FLAG_TARGETABLE | ACTOR_FLAG_FRIENDLY | ACTOR_FLAG_UPDATE_WHILE_CULLED)

void EnTg_Init(Actor* thisx, PlayState* play);
void EnTg_Destroy(Actor* thisx, PlayState* play);
void EnTg_Update(Actor* thisx, PlayState* play);
void EnTg_Draw(Actor* thisx, PlayState* play);

void EnTg_SpinIfNotTalking(EnTg* this, PlayState* play);

//ipi: Extra behaviour for launching into the air
void EnTg_BlastOff(EnTg* this, PlayState* play);
void EnTg_CrashDown(EnTg* this, PlayState* play);

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_NONE,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_2,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0x00000000, 0x00, 0x00 },
        TOUCH_NONE,
        BUMP_NONE,
        OCELEM_ON,
    },
    { 20, 64, 0, { 0, 0, 0 } },
};

//ipi: Used when crashing down
static ColliderCylinderInit sCylinderInit2 = {
    {
        COLTYPE_NONE,
        AT_ON | AT_TYPE_ENEMY,
        AC_NONE,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_2,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x20000000, 0x00, 0x08 },
        { 0xFFCFFFFF, 0x00, 0x00 },
        TOUCH_ON | TOUCH_SFX_NONE,
        BUMP_NONE,
        OCELEM_ON,
    },
    { 20, 64, 0, { 0, 0, 0 } },
};

static CollisionCheckInfoInit2 sColChkInfoInit = { 0, 0, 0, 0, MASS_IMMOVABLE };

const ActorInit En_Tg_InitVars = {
    ACTOR_EN_TG,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_MU,
    sizeof(EnTg),
    (ActorFunc)EnTg_Init,
    (ActorFunc)EnTg_Destroy,
    (ActorFunc)EnTg_Update,
    (ActorFunc)EnTg_Draw,
    NULL,
};

u16 EnTg_GetTextId(PlayState* play, Actor* thisx) {
    EnTg* this = (EnTg*)thisx;
    u16 temp;
    u32 phi;

    // If the player is wearing a mask, return a special reaction text
    temp = Text_GetFaceReaction(play, 0x24);
    if (temp != 0) {
        return temp;
    }
    // Use a different set of dialogue in Kakariko Village (Adult)
    if (play->sceneNum == SCENE_KAKARIKO_VILLAGE) {
        if (this->nextDialogue % 2 != 0) {
            phi = 0x5089;
        } else {
            phi = 0x508A;
        }
        return phi;
    } else {
        if (this->nextDialogue % 2 != 0) {
            phi = 0x7025;
        } else {
            phi = 0x7026;
        }
        return phi;
    }
}

s16 EnTg_UpdateTalkState(PlayState* play, Actor* thisx) {
    EnTg* this = (EnTg*)thisx;

    switch (Message_GetState(&play->msgCtx)) {
        case TEXT_STATE_NONE:
        case TEXT_STATE_DONE_HAS_NEXT:
        case TEXT_STATE_DONE_FADING:
        case TEXT_STATE_CHOICE:
        case TEXT_STATE_EVENT:
        case TEXT_STATE_DONE:
        case TEXT_STATE_SONG_DEMO_DONE:
        case TEXT_STATE_8:
        case TEXT_STATE_9:
            return 1;
        case TEXT_STATE_CLOSING:
            switch (this->actor.textId) {
                case 0x5089:
                case 0x508A:
                    this->nextDialogue++;
                    break;
                case 0x7025:
                case 0x7026:
                    this->actor.params ^= 1;
                    this->nextDialogue++;
                    break;
            }
            return 0;
        default:
            return 1;
    }
}

void EnTg_Init(Actor* thisx, PlayState* play) {
    EnTg* this = (EnTg*)thisx;

    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 28.0f);
    SkelAnime_InitFlex(play, &this->skelAnime, &gDancingCoupleSkel, &gDancingCoupleAnim, NULL, NULL, 0);
    Collider_InitCylinder(play, &this->collider);
    Collider_SetCylinder(play, &this->collider, &this->actor, &sCylinderInit);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, NULL, &sColChkInfoInit);
    this->actor.targetMode = 6;
    Actor_SetScale(&this->actor, 0.01f);
    this->nextDialogue = play->state.frames % 2;
    this->actionFunc = EnTg_SpinIfNotTalking;
    this->spinCounter = 0;
}

void EnTg_Destroy(Actor* thisx, PlayState* play) {
    EnTg* this = (EnTg*)thisx;

    SkelAnime_Free(&this->skelAnime, play);
    Collider_DestroyCylinder(play, &this->collider);
}

void EnTg_SpinIfNotTalking(EnTg* this, PlayState* play) {
    if (!this->interactInfo.talkState) {
        this->actor.shape.rot.y += 0x800;

        //ipi: Start spinning faster while the player is nearby
        if (CVarGetInteger("gIpiCrazyMode", 0)) {
            if (this->actor.xzDistToPlayer <= 150.0f) {
                this->spinCounter++;
            } else if (this->spinCounter > 0) {
                this->spinCounter--;
            }

            this->actor.shape.rot.y += 0x100 * this->spinCounter;

            //Take off once spinning fast enough
            if (this->spinCounter >= 30) {
                this->spinCounter = 0;
                this->actor.targetMode = 0;
                this->actor.sfx = NA_SE_EV_FIRE_PILLAR;
                this->actionFunc = EnTg_BlastOff;
            }
        }
    }
}

//ipi: Extra behaviour for launching into the air
void EnTg_BlastOff(EnTg* this, PlayState* play) {
    this->actor.shape.rot.y += 0x2600;

    //Create smoke trail
    this->spinCounter++;
    if (this->spinCounter & 1) {
        Vec3f velocity;
        VEC_SET(velocity, 0.0f, 0.0f, 0.0f);
        EffectSsBomb2_SpawnLayered(play, &this->actor.world, &velocity, &velocity, 80, 10);
    }

    //Accelerate upwards
    Math_StepToF(&this->actor.velocity.y, 5.0f, 0.25f);
    Actor_MoveForward(&this->actor);

    //Once high enough, crash onto the player
    if (this->actor.world.pos.y - this->actor.home.pos.y >= 400.0f) {
        Player* player = GET_PLAYER(play);
        this->actor.world.pos.x = player->actor.world.pos.x;
        this->actor.world.pos.z = player->actor.world.pos.z;

        //Turn upside down
        this->actor.shape.rot.x = 0x8000;
        this->actor.shape.yOffset = 6000.0f;

        //Enable collisions with the player
        Collider_SetCylinder(play, &this->collider, &this->actor, &sCylinderInit2);

        //Whee!
        this->actor.velocity.y = -15.0f;
        this->actor.sfx = NA_SE_EV_OBJECT_FALL;
        this->actionFunc = EnTg_CrashDown;
    }
}

//ipi: Extra behaviour for launching into the air
void EnTg_CrashDown(EnTg* this, PlayState* play) {
    this->actor.shape.rot.y += 0x3000;
    Actor_MoveForward(&this->actor);

    //Damage the player if we hit them - DOESN'T WORK!!! WHY!!
    if (this->collider.base.atFlags & AT_HIT) {
        this->collider.base.atFlags &= ~AT_HIT;
        play->damagePlayer(play, -8);
        Player* player = GET_PLAYER(play);
        Audio_PlayActorSound2(&player->actor, NA_SE_PL_BODY_HIT);
        //Knockback?
        func_8002F71C(play, &this->actor, 4.0f, this->actor.yawTowardsPlayer, 6.0f);
    }

    //Explode once we hit the ground
    if (this->actor.world.pos.y <= this->actor.floorHeight) {
        EnBom* bomb = (EnBom*)Actor_Spawn(&play->actorCtx, play, ACTOR_EN_BOM, this->actor.world.pos.x,
            this->actor.floorHeight + 10.0f, this->actor.world.pos.z, 0, 0, 0, BOMB_BODY, false);
        if (bomb != NULL) {
            bomb->timer = 0;
        }

        Actor_Kill(&this->actor);
    }
}

void EnTg_Update(Actor* thisx, PlayState* play) {
    EnTg* this = (EnTg*)thisx;
    s32 pad;
    f32 temp;
    Vec3s sp2C;

    sp2C.x = this->actor.world.pos.x;
    sp2C.y = this->actor.world.pos.y;
    sp2C.z = (s16)this->actor.world.pos.z + 3;
    this->collider.dim.pos = sp2C;
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
    //ipi: Enable AT collision
    CollisionCheck_SetAT(play, &play->colChkCtx, &this->collider.base);
    SkelAnime_Update(&this->skelAnime);
    Actor_UpdateBgCheckInfo(play, &this->actor, 0.0f, 0.0f, 0.0f, 4);
    this->actionFunc(this, play);
    //ipi: Ensure talking can only occur while not blasting off
    if (this->actionFunc == EnTg_SpinIfNotTalking) {
        temp = this->collider.dim.radius + 30.0f;
        Npc_UpdateTalking(play, &this->actor, &this->interactInfo.talkState, temp, EnTg_GetTextId, EnTg_UpdateTalkState);
    }
}

s32 EnTg_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, void* thisx) {
    return false;
}

void EnTg_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, void* thisx) {
    EnTg* this = (EnTg*)thisx;
    Vec3f targetOffset = { 0.0f, 800.0f, 0.0f };

    if (limbIndex == 9) {
        // Place the target point at the guy's head instead of the center of the actor
        Matrix_MultVec3f(&targetOffset, &this->actor.focus.pos);
    }
}

Gfx* EnTg_SetColor(GraphicsContext* gfxCtx, u8 r, u8 g, u8 b, u8 a) {
    Gfx* displayList = Graph_Alloc(gfxCtx, 2 * sizeof(Gfx));

    gDPSetEnvColor(displayList, r, g, b, a);
    gSPEndDisplayList(displayList + 1);
    return displayList;
}

void EnTg_Draw(Actor* thisx, PlayState* play) {
    EnTg* this = (EnTg*)thisx;

    OPEN_DISPS(play->state.gfxCtx);
    Matrix_Translate(0.0f, 0.0f, -560.0f, MTXMODE_APPLY);

    // Set the guy's shoes and shirt to royal blue
    gSPSegment(POLY_OPA_DISP++, 0x08, EnTg_SetColor(play->state.gfxCtx, 0, 50, 160, 0));

    // Set the girl's shirt to white
    gSPSegment(POLY_OPA_DISP++, 0x09, EnTg_SetColor(play->state.gfxCtx, 255, 255, 255, 0));

    SkelAnime_DrawSkeletonOpa(play, &this->skelAnime, EnTg_OverrideLimbDraw, EnTg_PostLimbDraw, this);
    CLOSE_DISPS(play->state.gfxCtx);
}
