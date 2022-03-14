#pragma once

enum class FloorTile {
  kNone, kWoodPlanks, kGrass,
};

namespace FloorTileProps {

float TextureArrayIndex(FloorTile tile);

}
