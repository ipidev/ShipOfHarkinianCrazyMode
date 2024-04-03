#include "z_en_heishi4.h"
#include "objects/object_sd/object_sd.h"
#include "vt.h"

#define FLAGS (ACTOR_FLAG_TARGETABLE | ACTOR_FLAG_FRIENDLY)

void EnHeishi4_Init(Actor* thisx, PlayState* play);
void EnHeishi4_Destroy(Actor* thisx, PlayState* play);
void EnHeishi4_Update(Actor* thisx, PlayState* play);
void EnHeishi4_Draw(Actor* thisx, PlayState* play);

void func_80A56544(EnHeishi4* this, PlayState* play);
void func_80A5673C(EnHeishi4* this, PlayState* play);
void func_80A56328(EnHeishi4* this, PlayState* play);
void func_80A563BC(EnHeishi4* this, PlayState* play);
void func_80A56B40(EnHeishi4* this, PlayState* play);
void func_80A56614(EnHeishi4* this, PlayState* play);
void func_80A56874(EnHeishi4* this, PlayState* play);
void func_80A56900(EnHeishi4* this, PlayState* play);
void func_80A56994(EnHeishi4* this, PlayState* play);
void func_80A56A50(EnHeishi4* this, PlayState* play);
void func_80A56ACC(EnHeishi4* this, PlayState* play);
void EnHeishi4_MarketSneak(EnHeishi4* this, PlayState* play);

//ipi: Extra functions to retaliate against the player attacking a guard
void EnHeishi4_InitializeRetaliation(EnHeishi4* this);
void EnHeishi4_SetupTargetPlayer(EnHeishi4* this);
void EnHeishi4_TargetPlayer(EnHeishi4* this, PlayState* play);
void EnHeishi4_SetupAttackGround(EnHeishi4* this);
void EnHeishi4_AttackGround(EnHeishi4* this, PlayState* play);

const ActorInit En_Heishi4_InitVars = {
    ACTOR_EN_HEISHI4,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_SD,
    sizeof(EnHeishi4),
    (ActorFunc)EnHeishi4_Init,
    (ActorFunc)EnHeishi4_Destroy,
    (ActorFunc)EnHeishi4_Update,
    (ActorFunc)EnHeishi4_Draw,
    NULL,
};

static u32 sFaceReactionSets[] = { 6, 7 };

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
    { 33, 40, 0, { 0, 0, 0 } },
};

//ipi: Extra cylinder for shockwave hitbox
static ColliderCylinderInit sCrazyModeShockwaveCylinderInit = {
    {
        COLTYPE_NONE,
        AT_ON | AT_TYPE_ENEMY,
        AC_NONE,
        OC1_NONE,
        OC2_TYPE_2,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0xFFCFFFFF, 0x04, 0x10 },
        { 0x00000000, 0x00, 0x00 },
        TOUCH_ON | TOUCH_SFX_NONE,
        BUMP_NONE,
        OCELEM_NONE,
    },
    { 60, 20, 0, { 0, 0, 0 } },
};

void EnHeishi4_Init(Actor* thisx, PlayState* play) {
    EnHeishi4* this = (EnHeishi4*)thisx;

    Actor_SetScale(thisx, 0.01f);
    this->type = thisx->params & 0xFF;
    thisx->colChkInfo.mass = MASS_IMMOVABLE;
    this->pos = thisx->world.pos;
    thisx->targetMode = 6;
    if (this->type == HEISHI4_AT_MARKET_DYING) {
        this->height = 30.0f;
        ActorShape_Init(&thisx->shape, 0.0f, NULL, 30.0f);
        SkelAnime_Init(play, &this->skelAnime, &gEnHeishiSkel, &gEnHeishiDyingGuardAnim_00C444, this->jointTable,
                       this->morphTable, 17);
    } else {
        this->height = 60.0f;
        ActorShape_Init(&thisx->shape, 0.0f, ActorShadow_DrawCircle, 30.0f);
        SkelAnime_Init(play, &this->skelAnime, &gEnHeishiSkel, &gEnHeishiIdleAnim, this->jointTable,
                       this->morphTable, 17);
    }
    Collider_InitCylinder(play, &this->collider);
    Collider_SetCylinder(play, &this->collider, thisx, &sCylinderInit);
    this->collider.dim.yShift = 0;
    this->collider.dim.radius = 15;
    this->collider.dim.height = 70;
    switch (this->type) {
        case HEISHI4_AT_KAKRIKO_ENTRANCE:
        case HEISHI4_AT_IMPAS_HOUSE:
            this->actionFunc = func_80A56328;
            break;
        case HEISHI4_AT_MARKET_DYING:
            this->collider.dim.radius = 28;
            this->collider.dim.height = 5;
            this->actionFunc = func_80A5673C;
            break;
        case HEISHI4_AT_MARKET_NIGHT:
            this->actionFunc = func_80A56544;
            break;
    }
    this->unk_27C = ((thisx->params >> 8) & 0xFF);
    osSyncPrintf("\n\n");
    osSyncPrintf(VT_FGCOL(GREEN) " ☆☆☆☆☆ 兵士２セット完了！ ☆☆☆☆☆ %d\n" VT_RST, thisx->params);
    osSyncPrintf(VT_FGCOL(YELLOW) " ☆☆☆☆☆ 識別完了！\t    ☆☆☆☆☆ %d\n" VT_RST, this->type);
    osSyncPrintf(VT_FGCOL(PURPLE) " ☆☆☆☆☆ メッセージ完了！   ☆☆☆☆☆ %x\n\n" VT_RST, (thisx->params >> 8) & 0xF);
    osSyncPrintf("\n\n");
    //ipi: Guards are damagable
    if (CVarGetInteger("gIpiCrazyMode", 0) && this->type != HEISHI4_AT_MARKET_DYING) {
        Actor_CrazyModeInitCivilianDamage(&this->collider);
        //Also create shockwave hitbox
        Collider_InitCylinder(play, &this->shockwaveCollider);
        Collider_SetCylinder(play, &this->shockwaveCollider, thisx, &sCrazyModeShockwaveCylinderInit);
    }

    //ipi: Use unused fields to represent retaliation state
    this->unk_2B6[0] = 0; //Is retaliating?
    this->unk_2B6[1] = 0; //Retaliation action timer
    this->unk_2B6[2] = 0; //Activating shockwave hitbox
}

void EnHeishi4_Destroy(Actor* thisx, PlayState* play) {
    EnHeishi4* this = (EnHeishi4*)thisx;

    Collider_DestroyCylinder(play, &this->collider);

    ResourceMgr_UnregisterSkeleton(&this->skelAnime);
}

void func_80A56328(EnHeishi4* this, PlayState* play) {
    f32 frames = Animation_GetLastFrame(&gEnHeishiIdleAnim);

    Animation_Change(&this->skelAnime, &gEnHeishiIdleAnim, 1.0f, 0.0f, (s16)frames, ANIMMODE_LOOP, -10.0f);
    this->actionFunc = func_80A563BC;
}

void func_80A563BC(EnHeishi4* this, PlayState* play) {
    s16 reactionOffset;

    this->unk_2B4 = 0;
    reactionOffset = this->type - 4;
    if (reactionOffset < 0) {
        reactionOffset = 0;
    }
    if (reactionOffset >= 3) {
        reactionOffset = 1;
    }
    if (Text_GetFaceReaction(play, sFaceReactionSets[reactionOffset]) != 0) {
        this->actor.textId = Text_GetFaceReaction(play, sFaceReactionSets[reactionOffset]);
        this->unk_2B4 = 1;
        this->actionFunc = func_80A56B40;
    } else {
        if (Flags_GetEventChkInf(EVENTCHKINF_ZELDA_FLED_HYRULE_CASTLE)) {
            this->actor.textId = 0x5065;
            this->actionFunc = func_80A56B40;
            return;
        }
        if (Flags_GetEventChkInf(EVENTCHKINF_PULLED_MASTER_SWORD_FROM_PEDESTAL)) {
            this->actor.textId = 0x5068;
            this->actionFunc = func_80A56B40;
            return;
        }
        if (this->type == HEISHI4_AT_IMPAS_HOUSE) {
            if (this->unk_284 == 0) {
                this->actor.textId = 0x5079;
            } else {
                this->actor.textId = 0x507A;
            }
        } else if (IS_DAY) {
            if (this->unk_284 == 0) {
                this->actor.textId = 0x5063;
            } else {
                this->actor.textId = 0x5064;
            }
        } else if (this->unk_284 == 0) {
            this->actor.textId = 0x5066;
        } else {
            this->actor.textId = 0x5067;
        }

        this->actionFunc = func_80A56B40;
    }
}

void func_80A56544(EnHeishi4* this, PlayState* play) {
    f32 frames = Animation_GetLastFrame(&gEnHeishiIdleAnim);

    Animation_Change(&this->skelAnime, &gEnHeishiIdleAnim, 1.0f, 0.0f, (s16)frames, ANIMMODE_LOOP, -10.0f);
    if (LINK_AGE_IN_YEARS != YEARS_CHILD) {
        osSyncPrintf(VT_FGCOL(GREEN) " ☆☆☆☆☆ ぎゃぁ！オトナだー ☆☆☆☆☆ \n" VT_RST);
        Actor_Kill(&this->actor);
    } else {
        this->actionFunc = func_80A56614;
    }
}

void func_80A56614(EnHeishi4* this, PlayState* play) {
    s16 reactionOffset;

    reactionOffset = this->type - 4;
    this->unk_2B4 = 0;
    if (reactionOffset < 0) {
        reactionOffset = 0;
    }
    if (reactionOffset >= 3) {
        reactionOffset = 1;
    }
    if (Text_GetFaceReaction(play, sFaceReactionSets[reactionOffset]) != 0) {
        this->actor.textId = Text_GetFaceReaction(play, sFaceReactionSets[reactionOffset]);
        this->unk_2B4 = 1;
        this->actionFunc = func_80A56B40;
        return;
    }
    if (play->sceneNum == SCENE_MARKET_GUARD_HOUSE) {
        if (IS_DAY) {
            this->actor.textId = 0x7004;
        } else {
            this->actor.textId = 0x709A;
        }
    } else if (play->sceneNum != SCENE_MARKET_NIGHT) {
        if (IS_DAY) {
            this->actor.textId = 0x7002;
        } else {
            this->actor.textId = 0x7003;
        }
    } else {
        this->actor.textId = 0x7003;
    }

    this->actionFunc = func_80A56B40;
}

void func_80A5673C(EnHeishi4* this, PlayState* play) {
    //ipi: Allow the dying guard to always spawn
    if (Flags_GetEventChkInf(EVENTCHKINF_PULLED_MASTER_SWORD_FROM_PEDESTAL) && !CVarGetInteger("gIpiCrazyMode", 0)) {
        osSyncPrintf(VT_FGCOL(YELLOW) " ☆☆☆☆☆ マスターソード祝入手！ ☆☆☆☆☆ \n" VT_RST);
        Actor_Kill(&this->actor);
        return;
    }
    this->unk_284 = 0;
    //ipi: Allow the dying guard to always spawn
    if (Flags_GetEventChkInf(EVENTCHKINF_ZELDA_FLED_HYRULE_CASTLE) || CVarGetInteger("gIpiCrazyMode", 0)) {
        if (!Flags_GetInfTable(INFTABLE_6C)) {
            f32 frames = Animation_GetLastFrame(&gEnHeishiDyingGuardAnim_00C444);
            Animation_Change(&this->skelAnime, &gEnHeishiDyingGuardAnim_00C444, 1.0f, 0.0f, (s16)frames, ANIMMODE_LOOP,
                             -10.0f);
            this->actor.textId = 0x7007;
            this->unk_282 = TEXT_STATE_EVENT;
            this->unk_284 = 1;
            osSyncPrintf(VT_FGCOL(YELLOW) " ☆☆☆☆☆ デモ開始！ ☆☆☆☆☆ \n" VT_RST);
        } else {
            //ipi: Explode if already spawned, otherwise remove the guard
            if (CVarGetInteger("gIpiCrazyMode", 0)) {
                //Set to different value if guard is alive upon entering scene
                if (this->unk_282 != TEXT_STATE_NONE) {
                    static Vec3f sZero = { 0.0f, 0.0f, 0.0f };
                    EffectSsBomb2_SpawnLayered(play, &this->actor.world.pos, &sZero, &sZero, 100, 20);
                    EffectSsDeadSound_SpawnStationary(play, &this->actor.world.pos, NA_SE_IT_BOMB_EXPLOSION,
                        true, 1, 20);
                }
                Actor_Kill(&this->actor);
            } else {
                this->actor.textId = 0x7008;
                this->unk_282 = TEXT_STATE_DONE;
                osSyncPrintf(VT_FGCOL(BLUE) " ☆☆☆☆☆ 返事なし ☆☆☆☆☆ \n" VT_RST);
            }
        }
        this->actionFunc = func_80A56874;
    } else {
        Actor_Kill(&this->actor);
    }
}

void func_80A56874(EnHeishi4* this, PlayState* play) {
    if (this->unk_284 != 0) {
        SkelAnime_Update(&this->skelAnime);
    }
    if (Actor_ProcessTalkRequest(&this->actor, play)) {
        if (this->unk_284 == 0) {
            this->actionFunc = func_80A5673C;

        } else {
            this->actionFunc = func_80A56900;
        }
    } else {
        func_8002F2CC(&this->actor, play, 100.0f);
    }
}

void func_80A56900(EnHeishi4* this, PlayState* play) {
    f32 frames = Animation_GetLastFrame(&gEnHeishiDyingGuardTalkAnim);

    Animation_Change(&this->skelAnime, &gEnHeishiDyingGuardTalkAnim, 1.0f, 0.0f, (s16)frames, ANIMMODE_LOOP, -10.0f);
    this->actionFunc = func_80A56994;
}

void func_80A56994(EnHeishi4* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);
    func_80038290(play, &this->actor, &this->unk_260, &this->unk_266, this->actor.focus.pos);
    //ipi: Text replacement causes Message_GetState to return TEXT_STATE_DONE instead of TEXT_STATE_EVENT
    u8 hasFinishedText;
    if (CVarGetInteger("gIpiCrazyMode", 0)) {
        hasFinishedText = (Message_GetState(&play->msgCtx) == TEXT_STATE_DONE && Message_ShouldAdvance(play));
    } else {
        hasFinishedText = (this->unk_282 == Message_GetState(&play->msgCtx) && Message_ShouldAdvance(play));
    }
    if (hasFinishedText) {
        Message_CloseTextbox(play);
        Flags_SetInfTable(INFTABLE_6C);
        func_8002DF54(play, NULL, 8);
        this->actionFunc = func_80A56A50;
    }
}

void func_80A56A50(EnHeishi4* this, PlayState* play) {
    f32 frames = Animation_GetLastFrame(&gEnHeishiDyingGuardDieAnim);

    this->unk_288 = frames;
    Animation_Change(&this->skelAnime, &gEnHeishiDyingGuardDieAnim, 1.0f, 0.0f, frames, ANIMMODE_ONCE, -10.0f);
    this->actionFunc = func_80A56ACC;
}

void func_80A56ACC(EnHeishi4* this, PlayState* play) {
    f32 currentFrame = this->skelAnime.curFrame;

    SkelAnime_Update(&this->skelAnime);
    if (this->unk_288 <= currentFrame) {
        func_8002DF54(play, NULL, 7);
        this->actionFunc = func_80A5673C;
    }

    //ipi: Jack's having a piss!
    if (CVarGetInteger("gIpiCrazyMode", 0)) {
        static Vec3f sGravity = { 0.0f, -0.5f, 0.0f };
        static Color_RGBA8 sPrimColor = { 255, 200, 0, 255 };
        static Color_RGBA8 sEnvColor = { 255, 200, 0, 255 };

        //Speed is based on animation progress
        f32 strengthScalar = Math_SinF((currentFrame / this->unk_288) * M_PI);
        f32 speed = 8.0f * strengthScalar;
        speed = CLAMP(speed, 1.0f, 6.0f);
        Vec3f velocity;
        velocity.x = 0.0f;
        velocity.y = speed * (1.0f + Rand_CenteredFloat(0.1f));
        velocity.z = speed * (1.0f + Rand_CenteredFloat(0.1f));
        EffectSsDtBubble_SpawnCustomColor(play, &this->actor.world.pos, &velocity, &sGravity,
            &sPrimColor, &sEnvColor, 75, 30, 0);
    }
}

void func_80A56B40(EnHeishi4* this, PlayState* play) {
    s16 reactionOffset;

    SkelAnime_Update(&this->skelAnime);
    reactionOffset = (this->type - 4);
    if (reactionOffset < 0) {
        reactionOffset = 0;
    }
    if (reactionOffset >= 3) {
        reactionOffset = 1;
    }
    if (Text_GetFaceReaction(play, sFaceReactionSets[reactionOffset]) != 0) {
        if (this->unk_2B4 == 0) {
            if ((this->type == HEISHI4_AT_KAKRIKO_ENTRANCE) || (this->type == HEISHI4_AT_IMPAS_HOUSE)) {
                this->actionFunc = func_80A563BC;
                return;
            }
            if (this->type == HEISHI4_AT_MARKET_NIGHT) {
                this->actionFunc = func_80A56614;
                return;
            }
        }
    } else {
        if (this->unk_2B4 != 0) {
            if ((this->type == HEISHI4_AT_KAKRIKO_ENTRANCE) || (this->type == HEISHI4_AT_IMPAS_HOUSE)) {
                this->actionFunc = func_80A563BC;
                return;
            }
            if (this->type == HEISHI4_AT_MARKET_NIGHT) {
                this->actionFunc = func_80A56614;
                return;
            }
        }
    }
    if (Actor_ProcessTalkRequest(&this->actor, play)) {
        if ((this->type == HEISHI4_AT_KAKRIKO_ENTRANCE) || (this->type == HEISHI4_AT_IMPAS_HOUSE)) {
            this->unk_284 = 1;
            this->actionFunc = func_80A563BC;
            return;
        }
        if (this->type == HEISHI4_AT_MARKET_NIGHT) {
            Player* player = GET_PLAYER(play);
            // Only allow sneaking when not wearing a mask as that triggers different dialogue. MM Bunny hood disables
            // these interactions, so bunny hood is fine in that case.
            if (CVarGetInteger("gMarketSneak", 0) &&
                (player->currentMask == PLAYER_MASK_NONE ||
                 (player->currentMask == PLAYER_MASK_BUNNY && CVarGetInteger("gMMBunnyHood", 0)))) {
                this->actionFunc = EnHeishi4_MarketSneak;
            } else {
                this->actionFunc = func_80A56614;
                return;
            }
        }
    }
    func_8002F2F4(&this->actor, play);
}

/*Function that allows child Link to exit from Market entrance to Hyrule Field
at night.
*/
void EnHeishi4_MarketSneak(EnHeishi4* this, PlayState* play) {
    if (Message_GetState(&play->msgCtx) == TEXT_STATE_CHOICE && Message_ShouldAdvance(play)) {
        switch (play->msgCtx.choiceIndex) {
            case 0: //yes
                if (IS_RANDO && Randomizer_GetSettingValue(RSK_SHUFFLE_OVERWORLD_ENTRANCES) != RO_GENERIC_OFF){
                    play->nextEntranceIndex = Entrance_OverrideNextIndex(ENTR_HYRULE_FIELD_7); // Market Entrance -> HF
                } else {
                    play->nextEntranceIndex = ENTR_HYRULE_FIELD_0; // HF Near bridge (OoT cutscene entrance) to not fall in the water
                } 
                play->transitionTrigger = TRANS_TRIGGER_START;
                play->transitionType = TRANS_TYPE_CIRCLE(TCA_STARBURST, TCC_WHITE, TCS_FAST);
                gSaveContext.nextTransitionType = TRANS_TYPE_CIRCLE(TCA_STARBURST, TCC_WHITE, TCS_FAST);
                this->actionFunc = func_80A56614;
                break;
            case 1: //no
                this->actionFunc = func_80A56614;
                break;
        }
    }
}

//ipi: Extra functions to retaliate against the player attacking a guard
void EnHeishi4_SetupInitializeRetaliation(EnHeishi4* this) {
    this->actor.flags &= ~ACTOR_FLAG_FRIENDLY;
    this->actor.flags |= ACTOR_FLAG_HOSTILE;
    this->unk_2B6[0] = 1; //Now retaliating
    this->unk_2B6[1] = 30; //Timer to shockwave attack
    //Setup attack
    this->collider.base.atFlags = AT_ON | AT_TYPE_ENEMY;
    this->collider.info.toucherFlags = TOUCH_ON;
    this->collider.info.toucher.dmgFlags = 0xFFCFFFFF;
    this->collider.info.toucher.damage = 0x10;
    this->collider.info.toucher.effect = 0;
    //Play miniboss music if not already playing
    if (func_800FA0B4(SEQ_PLAYER_BGM_MAIN) != NA_BGM_MINI_BOSS) {
        func_800F5ACC(NA_BGM_MINI_BOSS);
    }
    func_80078884(NA_SE_SY_FOUND);
    EnHeishi4_SetupTargetPlayer(this);
}

void EnHeishi4_SetupTargetPlayer(EnHeishi4* this) {
    f32 frameCount = Animation_GetLastFrame(&gEnHeishiWalkAnim);
    Animation_Change(&this->skelAnime, &gEnHeishiWalkAnim, 1.0f, 0.0f, (s16)frameCount, ANIMMODE_LOOP, -10.0f);

    this->actor.speedXZ = 0.0f;
    this->actor.gravity = -2.0f;
    this->unk_2B6[1] = 35; //Timer to shockwave attack
    this->unk_2B6[2] = 0; //Shockwave hitbox is not active
    this->actionFunc = EnHeishi4_TargetPlayer;
}

void EnHeishi4_TargetPlayer(EnHeishi4* this, PlayState* play) {
    //Accelerate towards player
    SkelAnime_Update(&this->skelAnime);
    Math_StepToF(&this->actor.speedXZ, 5.0f, 0.5f);
    Math_ApproachS(&this->actor.world.rot.y, this->actor.yawTowardsPlayer, 3, 0x1000);

    //Play walking sounds
    if (Animation_OnFrame(&this->skelAnime, 1.0f) || Animation_OnFrame(&this->skelAnime, 17.0f)) {
        Audio_PlayActorSound2(&this->actor, NA_SE_EV_KNIGHT_WALK);
    }

    if (this->unk_2B6[1] > 0) {
        this->unk_2B6[1]--;
    } else {
        //Attack if the player is within range
        if (this->actor.xzDistToPlayer < 150.0f && ABS(this->actor.yDistToPlayer) < 30.0f &&
            this->actor.bgCheckFlags & 1) {
            EnHeishi4_SetupAttackGround(this);
        }
    }
}

void EnHeishi4_SetupAttackGround(EnHeishi4* this) {
    f32 frameCount = Animation_GetLastFrame(&gEnHeishiSlamSpearAnim);
    Animation_Change(&this->skelAnime, &gEnHeishiSlamSpearAnim, 1.0f, 0.0f, frameCount, ANIMMODE_ONCE, -10.0f);

    this->actor.speedXZ = 0.0f;
    this->actor.velocity.y = 8.0f;
    this->actor.gravity = -1.0f;
    this->unk_2B6[2] = 0; //Shockwave hitbox is not active
    this->actionFunc = EnHeishi4_AttackGround;
}

void EnHeishi4_AttackGround(EnHeishi4* this, PlayState* play) {
    static Vec3f sZero;
    //Create shockwave
    if (this->skelAnime.curFrame >= 12.0f) {
        if (this->unk_2B6[2] == 0) {
            Audio_PlayActorSound2(&this->actor, NA_SE_EV_STONE_BOUND);
            //Create effect
            Vec3f effectPos;
            effectPos.x = this->actor.world.pos.x;
            effectPos.y = this->actor.world.pos.y + 20.0f;
            effectPos.z = this->actor.world.pos.z;
            EffectSsBlast_SpawnWhiteShockwave(play, &effectPos, &sZero, &sZero);
            //Shake camera
            s16 quake = Quake_Add(GET_ACTIVE_CAM(play), 3);
            Quake_SetSpeed(quake, -0x3CB0);
            Quake_SetQuakeValues(quake, 3, 0, 0, 0);
            Quake_SetCountdown(quake, 0xC);
        }
        this->unk_2B6[2]++;
        //Activate and modify shockwave hitbox
        if (this->unk_2B6[2] <= 5) {
            this->shockwaveCollider.dim.radius = 60 + (this->unk_2B6[2] * 20);
        }
    }
    //Return to running at the player
    if (SkelAnime_Update(&this->skelAnime)) {
        EnHeishi4_SetupTargetPlayer(this);
    }
}

void EnHeishi4_Update(Actor* thisx, PlayState* play) {
    EnHeishi4* this = (EnHeishi4*)thisx;
    s32 pad;
    Player* player = GET_PLAYER(play);

    //ipi: Don't force world position if we're retaliating
    if (this->unk_2B6[0] == 0) {
        thisx->world.pos.x = this->pos.x;
        thisx->world.pos.y = this->pos.y;
        thisx->world.pos.z = this->pos.z;
    }
    Actor_SetFocus(thisx, this->height);
    if (this->type != HEISHI4_AT_MARKET_DYING) {
        this->interactInfo.trackPos = player->actor.world.pos;
        if (!LINK_IS_ADULT) {
            this->interactInfo.trackPos.y = player->actor.world.pos.y - 10.0f;
        }
        Npc_TrackPoint(thisx, &this->interactInfo, 2, NPC_TRACKING_FULL_BODY);
        this->unk_260 = this->interactInfo.headRot;
        this->unk_266 = this->interactInfo.torsoRot;
        //ipi: Retaliate upon being damaged by the player
        if (CVarGetInteger("gIpiCrazyMode", 0) && this->unk_2B6[0] == 0 &&
            this->collider.base.acFlags & AC_HIT && Message_GetState(&play->msgCtx) == TEXT_STATE_NONE) {
            this->collider.base.acFlags &= ~AC_HIT;
            EnHeishi4_SetupInitializeRetaliation(this);
        }
    }
    this->unk_27E += 1;
    this->actionFunc(this, play);
    Actor_MoveForward(thisx);
    //ipi: Needs to be higher, otherwise guard always thinks he's stuck in a wall
    f32 wallCheckHeight = this->unk_2B6[0] ? 20.0f : 10.0f;
    Actor_UpdateBgCheckInfo(play, thisx, wallCheckHeight, 10.0f, 30.0f, 0x1D);
    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
    //ipi: Also check for attacks and attack colliders
    if (CVarGetInteger("gIpiCrazyMode", 0)) {
        if (this->unk_2B6[0] != 0) {
            CollisionCheck_SetAT(play, &play->colChkCtx, &this->collider.base);
        }
        CollisionCheck_SetAC(play, &play->colChkCtx, &this->collider.base);
        //Only update shockwave collision if needed
        if (this->unk_2B6[2] != 0) {
            Collider_UpdateCylinder(&this->actor, &this->shockwaveCollider);
            CollisionCheck_SetAT(play, &play->colChkCtx, &this->shockwaveCollider.base);
        }
    }
}

s32 EnHeishi_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                              void* thisx) {
    EnHeishi4* this = (EnHeishi4*)thisx;

    if (limbIndex == 9) {
        rot->x += this->unk_266.y;
    }
    if (limbIndex == 16) {
        rot->x += this->unk_260.y;
        rot->z += this->unk_260.z;
    }
    return false;
}

void EnHeishi4_Draw(Actor* thisx, PlayState* play) {
    EnHeishi4* this = (EnHeishi4*)thisx;

    Gfx_SetupDL_25Opa(play->state.gfxCtx);
    SkelAnime_DrawSkeletonOpa(play, &this->skelAnime, EnHeishi_OverrideLimbDraw, NULL, this);
}
