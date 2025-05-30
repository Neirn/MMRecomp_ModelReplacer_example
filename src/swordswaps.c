#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "recompconfig.h"
#include "modelreplacer_api.h"
#include "globalobjects_api.h"
#include "assets/objects/object_link_child/object_link_child.h"
#include "assets/objects/object_link_boy/object_link_boy.h"
#include "assets/objects/object_boss01/object_boss01.h"

// make sure the sword can be replaced w/o an object reload
RECOMP_CALLBACK(YAZMT_Z64_MODEL_REPLACER_MOD_NAME, ZModelReplacer_onReady)
void preregGFS() {
    ZModelReplacer_preregisterDL(OBJECT_LINK_CHILD, gLinkHumanGreatFairysSwordDL);
}

// Mod options
enum LONGSWORD_OPTIONS {
    LONGSWORD_OPT_GFS,
    LONGSWORD_OPT_FD,
    LONGSWORD_OPT_ODOLWA
};

// make sure longSword replacement runs first time
u32 gCurrentLongSword = 999;

RECOMP_HOOK("Player_Update")
void updateSword_on_Player_Update(Actor *thisx, PlayState *play) {
    u32 longSword = recomp_get_config_u32("longsword_choice");

    if (gCurrentLongSword != longSword) {
        Gfx *newSwordDL = NULL;

        if (longSword == LONGSWORD_OPT_GFS) {
            ZModelReplacer_removeCustomDL(OBJECT_LINK_CHILD, gLinkHumanGreatFairysSwordDL);
        } else if (longSword == LONGSWORD_OPT_FD) {
            newSwordDL = ZGlobalObj_getGlobalGfxPtr(OBJECT_LINK_BOY, gLinkFierceDeitySwordDL);
        } else if (longSword == LONGSWORD_OPT_ODOLWA) {
            newSwordDL = ZGlobalObj_getGlobalGfxPtr(OBJECT_BOSS01, gOdolwaSwordDL);
        }

        if (newSwordDL != NULL) {
            ZModelReplacer_setCustomDL(OBJECT_LINK_CHILD, gLinkHumanGreatFairysSwordDL, newSwordDL);
        }

        gCurrentLongSword = longSword;
    }
}
