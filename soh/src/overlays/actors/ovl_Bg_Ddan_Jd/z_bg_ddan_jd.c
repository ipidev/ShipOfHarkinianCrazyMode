/*
 * File: z_bg_ddan_jd.c
 * Overlay: ovl_Bg_Ddan_Jd
 * Description: Rising stone platform (Dodongo's Cavern)
 */

#include "z_bg_ddan_jd.h"
#include "objects/object_ddan_objects/object_ddan_objects.h"

#define FLAGS (ACTOR_FLAG_UPDATE_WHILE_CULLED | ACTOR_FLAG_DRAW_WHILE_CULLED)

void BgDdanJd_Init(Actor* thisx, PlayState* play);
void BgDdanJd_Destroy(Actor* thisx, PlayState* play);
void BgDdanJd_Update(Actor* thisx, PlayState* play);
void BgDdanJd_Draw(Actor* thisx, PlayState* play);

void BgDdanJd_Idle(BgDdanJd* this, PlayState* play);
void BgDdanJd_Move(BgDdanJd* this, PlayState* play);

const ActorInit Bg_Ddan_Jd_InitVars = {
    ACTOR_BG_DDAN_JD,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_DDAN_OBJECTS,
    sizeof(BgDdanJd),
    (ActorFunc)BgDdanJd_Init,
    (ActorFunc)BgDdanJd_Destroy,
    (ActorFunc)BgDdanJd_Update,
    (ActorFunc)BgDdanJd_Draw,
    NULL,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};

typedef enum {
    /* 0 */ STATE_GO_BOTTOM,
    /* 1 */ STATE_GO_MIDDLE_FROM_BOTTOM,
    /* 2 */ STATE_GO_MIDDLE_FROM_TOP,
    /* 3 */ STATE_GO_TOP
} BgDdanJdState;

#define MOVE_HEIGHT_MIDDLE 140.0f
#define MOVE_HEIGHT_TOP 700.0f

#define IDLE_FRAMES 100

// Since ySpeed is used to determine if the platform should rise to the top of the dungeon, these must be assigned
// different values in order for the shortcut to work correctly
#define DEFAULT_Y_SPEED 1
#define SHORTCUT_Y_SPEED 5

void BgDdanJd_Init(Actor* thisx, PlayState* play) {
    s32 pad;
    BgDdanJd* this = (BgDdanJd*)thisx;
    CollisionHeader* colHeader = NULL;

    Actor_ProcessInitChain(&this->dyna.actor, sInitChain);
    DynaPolyActor_Init(&this->dyna, DPM_PLAYER);
    CollisionHeader_GetVirtual(&gDodongoRisingPlatformCol, &colHeader);
    this->dyna.bgId = DynaPoly_SetBgActor(play, &play->colCtx.dyna, &this->dyna.actor, colHeader);
    this->idleTimer = IDLE_FRAMES;
    this->state = STATE_GO_BOTTOM;

    // Missing check for actor.params < 0x40. This will cause inconsistent behavior if params >= 0x40 and the bound
    // switch state is turned on while in the same room, as the shortcut behavior won't become enabled until the actor
    // is reloaded.
    if (Flags_GetSwitch(play, this->dyna.actor.params)) {
        this->ySpeed = SHORTCUT_Y_SPEED;
    } else {
        this->ySpeed = DEFAULT_Y_SPEED;
    }
    this->actionFunc = BgDdanJd_Idle;
}

void BgDdanJd_Destroy(Actor* thisx, PlayState* play) {
    BgDdanJd* this = (BgDdanJd*)thisx;

    DynaPoly_DeleteBgActor(play, &play->colCtx.dyna, this->dyna.bgId);
}

void BgDdanJd_Idle(BgDdanJd* this, PlayState* play) {
    if (this->idleTimer != 0) {
        this->idleTimer--;
    }

    // if this is the platform that rises all the way to the top, and the switch state has just changed to on
    if (this->ySpeed == DEFAULT_Y_SPEED && this->dyna.actor.params < 0x40 &&
        Flags_GetSwitch(play, this->dyna.actor.params)) {
        this->ySpeed = SHORTCUT_Y_SPEED;
        this->state = STATE_GO_MIDDLE_FROM_BOTTOM;
        this->idleTimer = 0;
        this->dyna.actor.world.pos.y = this->dyna.actor.home.pos.y + MOVE_HEIGHT_MIDDLE;
        OnePointCutscene_Init(play, 3060, -99, &this->dyna.actor, MAIN_CAM);
    }
    if (this->idleTimer == 0) {
        this->idleTimer = IDLE_FRAMES;
        if (this->state == STATE_GO_BOTTOM) {
            this->state = STATE_GO_MIDDLE_FROM_BOTTOM;
            this->targetY = this->dyna.actor.home.pos.y + MOVE_HEIGHT_MIDDLE;
        } else if (this->state == STATE_GO_MIDDLE_FROM_BOTTOM) {
            // If the platform has been activated as a shortcut
            if (this->ySpeed != DEFAULT_Y_SPEED) {
                this->state = STATE_GO_TOP;
                this->targetY = this->dyna.actor.home.pos.y + MOVE_HEIGHT_TOP;
            } else {
                this->state = STATE_GO_BOTTOM;
                this->targetY = this->dyna.actor.home.pos.y;
            }
        } else if (this->state == STATE_GO_MIDDLE_FROM_TOP) {
            // If the platform has been activated as a shortcut
            if (this->ySpeed != DEFAULT_Y_SPEED) {
                this->state = STATE_GO_TOP;
                this->targetY = this->dyna.actor.home.pos.y + MOVE_HEIGHT_TOP;
            } else {
                this->state = STATE_GO_BOTTOM;
                this->targetY = this->dyna.actor.home.pos.y;
            }
        } else if (this->state == STATE_GO_TOP) {
            this->state = STATE_GO_MIDDLE_FROM_TOP;
            this->targetY = this->dyna.actor.home.pos.y + MOVE_HEIGHT_MIDDLE;
        }
        this->actionFunc = BgDdanJd_Move;
    }
}

// Handles dust particles and sfx when moving
void BgDdanJd_MoveEffects(BgDdanJd* this, PlayState* play) {
    Vec3f dustPos;

    // Generate random dust particles at the platform's base.
    dustPos.y = this->dyna.actor.home.pos.y;
    if (play->gameplayFrames & 1) {
        dustPos.x = this->dyna.actor.world.pos.x + 65.0f;
        dustPos.z = Rand_CenteredFloat(110.0f) + this->dyna.actor.world.pos.z;
        func_80033480(play, &dustPos, 5.0f, 1, 20, 60, 1);
        dustPos.x = this->dyna.actor.world.pos.x - 65.0f;
        dustPos.z = Rand_CenteredFloat(110.0f) + this->dyna.actor.world.pos.z;
        func_80033480(play, &dustPos, 5.0f, 1, 20, 60, 1);
    } else {
        dustPos.x = Rand_CenteredFloat(110.0f) + this->dyna.actor.world.pos.x;
        dustPos.z = this->dyna.actor.world.pos.z + 65.0f;
        func_80033480(play, &dustPos, 5.0f, 1, 20, 60, 1);
        dustPos.x = Rand_CenteredFloat(110.0f) + this->dyna.actor.world.pos.x;
        dustPos.z = this->dyna.actor.world.pos.z - 65.0f;
        func_80033480(play, &dustPos, 5.0f, 1, 20, 60, 1);
    }
    if (this->ySpeed == SHORTCUT_Y_SPEED) {
        func_8002F974(&this->dyna.actor, NA_SE_EV_ELEVATOR_MOVE - SFX_FLAG);
    }
}

// Implements the platform's movement state
void BgDdanJd_Move(BgDdanJd* this, PlayState* play) {
    // if this is the platform that rises all the way to the top, and the switch state has just changed to on
    if (this->ySpeed == DEFAULT_Y_SPEED && this->dyna.actor.params < 0x40 &&
        Flags_GetSwitch(play, this->dyna.actor.params)) {
        this->ySpeed = SHORTCUT_Y_SPEED;
        this->state = STATE_GO_MIDDLE_FROM_BOTTOM;
        this->dyna.actor.world.pos.y = this->dyna.actor.home.pos.y + MOVE_HEIGHT_MIDDLE;
        this->idleTimer = 0;
        this->actionFunc = BgDdanJd_Idle;
        OnePointCutscene_Init(play, 3060, -99, &this->dyna.actor, MAIN_CAM);
    } else {
        //ipi: Accelerate when moving from the middle to the top
        u8 acceleratingToTop = CVarGetInteger("gIpiCrazyMode", 0) && this->state == STATE_GO_TOP;
        f32 speed = this->ySpeed;
        if (acceleratingToTop && this->dyna.actor.world.pos.y >= this->dyna.actor.home.pos.y + MOVE_HEIGHT_MIDDLE) {
            this->idleTimer++;
            speed += this->idleTimer - IDLE_FRAMES;
            this->dyna.actor.sfxFreqScale = 1.0f + (this->idleTimer - IDLE_FRAMES) * 0.025f;
        }
        //ipi: Use our possibly-adjusted speed instead
        if (Math_StepToF(&this->dyna.actor.world.pos.y, this->targetY, speed)) {
            Audio_PlayActorSound2(&this->dyna.actor, NA_SE_EV_PILLAR_MOVE_STOP);
            this->actionFunc = BgDdanJd_Idle;
            //ipi: Upon reaching the top, throw the player off
            if (acceleratingToTop) {
                Player* player = GET_PLAYER(play);
                if (this->dyna.actor.xzDistToPlayer < 95.0f && (player->actor.bgCheckFlags & 1) != 0 &&
                    player->actor.world.pos.y >= this->dyna.actor.world.pos.y) {
                    func_8002F71C(play, &this->dyna.actor, 9.0f, 0x2000, 14.0f);
                }
                //Play a louder sound that won't get overwritten by the movement sound
                SoundSource_PlaySfxAtFixedWorldPos(play, &this->dyna.actor.world.pos, 40, NA_SE_EV_STONE_BOUND/*NA_SE_EV_STONEDOOR_STOP*/);
                //Spawn a shockwave
                static Vec3f sZero = { 0.0f, 0.0f, 0.0f };
                Vec3f shockwavePos;
                Math_Vec3f_Copy(&shockwavePos, &this->dyna.actor.home.pos);
                shockwavePos.y += 10.0f;
                EffectSsBlast_SpawnWhiteCustomScale(play, &shockwavePos, &sZero, &sZero, 500, 200, 10);
                //Return to the lower height immediately
                this->idleTimer = 0;
                this->dyna.actor.sfxFreqScale = 1.0f;
            }
        }
    }
    BgDdanJd_MoveEffects(this, play);
}

void BgDdanJd_Update(Actor* thisx, PlayState* play) {
    BgDdanJd* this = (BgDdanJd*)thisx;

    this->actionFunc(this, play);
}

void BgDdanJd_Draw(Actor* thisx, PlayState* play) {
    Gfx_DrawDListOpa(play, gDodongoRisingPlatformDL);
}
