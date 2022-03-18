#include "chunk_mesh_utils.hpp"

float TextureArrayIndex(TileObject t, TileObjectMeshPart m) {
  switch (t) {
    case TileObject::kFloorGrass:      return 1.0f;
    case TileObject::kFloorWoodPlanks: return 2.0f;

    case TileObject::kPropTree:        return m == TileObjectMeshPart::kTreeTrunk ? 4.0f : 3.0f;

    default:                           return 0.0f;
  }
}