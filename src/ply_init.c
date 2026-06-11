#include "common.h"

void ply_collect_textures(Player *player) {
    model_collect_textures(player->obj, TRUE);
}
