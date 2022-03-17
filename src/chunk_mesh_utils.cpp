#include "chunk_mesh_utils.hpp"

namespace FloorTileProps {

float TextureArrayIndex(FloorTile tile) {
  switch (tile) {
    case FloorTile::kWoodPlanks: return 0;
    case FloorTile::kGrass:      return 1;
    default:                     return 0;
  }
}

}
