#include "modding.h"
#include "global.h"

#include "gLinkHumanSkel.h"

// Original set of DLs and Textures we're replacing
extern Gfx* gPlayerWaistDLs[2 * PLAYER_FORM_MAX];
extern TexturePtr sPlayerMouthTextures[PLAYER_MOUTH_MAX];
extern TexturePtr sPlayerEyesTextures[PLAYER_EYES_MAX];

// Custom eyes
void* sEyeTextures[] = {
    gLinkChildEyesOpenTex,
    gLinkChildEyesHalfTex,
    gLinkChildEyesClosedfTex,
    gLinkChildEyesRollLeftTex,
    gLinkChildEyesRollRightTex,
    gLinkChildEyesShockTex,
    gLinkChildEyesUnk1Tex,
    gLinkChildEyesUnk2Tex
};

// Custom mouth
void* sMouthTextures[] = {
    gLinkHumanSkel_gLinkChildMouth1Tex_rgba16,
    gLinkHumanSkel_gLinkChildMouth2Tex_rgba16,
    gLinkHumanSkel_gLinkChildMouth3Tex_rgba16,
    gLinkHumanSkel_gLinkChildMouth4Tex_rgba16,
};

// rough fix for replacing eye/mouth textures by applying the original ones again
extern u64 gLinkGoronEyesOpenTex[];
extern u64 gLinkGoronEyesHalfTex[];
extern u64 gLinkGoronEyesClosedTex[];
extern u64 gLinkGoronEyesSurprisedTex[];

TexturePtr sGoronEyesTextures[PLAYER_EYES_MAX] = {
    gLinkGoronEyesOpenTex,      // PLAYER_EYES_OPEN
    gLinkGoronEyesHalfTex,      // PLAYER_EYES_HALF
    gLinkGoronEyesClosedTex,    // PLAYER_EYES_CLOSED
    gLinkGoronEyesSurprisedTex, // PLAYER_EYES_ROLL_RIGHT
    gLinkGoronEyesSurprisedTex, // PLAYER_EYES_ROLL_LEFT
    gLinkGoronEyesSurprisedTex, // PLAYER_EYES_ROLL_UP
    gLinkGoronEyesSurprisedTex, // PLAYER_EYES_ROLL_DOWN
    gLinkGoronEyesSurprisedTex, // PLAYER_EYES_7
};

extern u64 gLinkZoraEyesOpenTex[];
extern u64 gLinkZoraEyesHalfTex[];
extern u64 gLinkZoraEyesClosedTex[];
extern u64 gLinkZoraEyesRollRightTex[];
extern u64 gLinkZoraEyesRollLeftTex[];
extern u64 gLinkZoraEyesRollUpTex[];
extern u64 gLinkZoraEyesRollDownTex[];
extern u64 object_link_zora_Tex_003800[];

TexturePtr sZoraEyesTextures[PLAYER_EYES_MAX] = {
    gLinkZoraEyesOpenTex,        // PLAYER_EYES_OPEN
    gLinkZoraEyesHalfTex,        // PLAYER_EYES_HALF
    gLinkZoraEyesClosedTex,      // PLAYER_EYES_CLOSED
    gLinkZoraEyesRollRightTex,   // PLAYER_EYES_ROLL_RIGHT
    gLinkZoraEyesRollLeftTex,    // PLAYER_EYES_ROLL_LEFT
    gLinkZoraEyesRollUpTex,      // PLAYER_EYES_ROLL_UP
    gLinkZoraEyesRollDownTex,    // PLAYER_EYES_ROLL_DOWN
    object_link_zora_Tex_003800, // PLAYER_EYES_7
};

extern u64 gLinkZoraMouthClosedTex[];
extern u64 object_link_zora_Tex_004400[];
extern u64 gLinkZoraMouthAngryTex[];
extern u64 gLinkZoraMouthHappyTex[];

TexturePtr sZoraMouthTextures[PLAYER_MOUTH_MAX] = {
    gLinkZoraMouthClosedTex,        // PLAYER_MOUTH_CLOSED
    object_link_zora_Tex_004400,    // PLAYER_MOUTH_TEETH
    gLinkZoraMouthAngryTex,         // PLAYER_MOUTH_ANGRY
    gLinkZoraMouthHappyTex,         // PLAYER_MOUTH_HAPPY
};


// Basic Human Link replacement (only skeleton and waist)
RECOMP_HOOK("Player_Init") void on_Player_Init(Actor* thisx, PlayState* play) {
    gPlayerSkeletons[PLAYER_FORM_HUMAN] = &gLinkHumanSkel;

    gPlayerWaistDLs[PLAYER_FORM_HUMAN * 2 + 0] = gLinkHumanSkel_bone001_gLinkHumanWaistLimb_mesh_layer_Opaque;
    gPlayerWaistDLs[PLAYER_FORM_HUMAN * 2 + 1] = gLinkHumanSkel_bone001_gLinkHumanWaistLimb_mesh_layer_Opaque;
}

// Apply new eyes and mouth
RECOMP_HOOK("Player_Update") void on_Player_Update(Actor* thisx, PlayState* play) {
    Player* player = GET_PLAYER(play);

    switch (player->transformation) {
        case PLAYER_FORM_HUMAN:
            for (int i = 0; i < PLAYER_MOUTH_MAX; i++) {
                sPlayerMouthTextures[i] = sMouthTextures[i];
            }
            for (int i = 0; i < PLAYER_EYES_MAX; i++) {
                sPlayerEyesTextures[i] = sEyeTextures[i];
            }
            break;
        // Include zora link and goron link's flipbooks to prevent mouth and eyes texture errors for them
        case PLAYER_FORM_ZORA:
            for (int i = 0; i < PLAYER_MOUTH_MAX; i++) {
                sPlayerMouthTextures[i] = sZoraMouthTextures[i];
            }
            for (int i = 0; i < PLAYER_EYES_MAX; i++) {
                sPlayerEyesTextures[i] = sZoraEyesTextures[i];
            }
        case PLAYER_FORM_GORON:
            for (int i = 0; i < PLAYER_EYES_MAX; i++) {
                sPlayerEyesTextures[i] = sGoronEyesTextures[i];
            }
        default:
            break;
    }
}