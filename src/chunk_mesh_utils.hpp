#pragma once

enum class TileObject {
  kNone,

  kFloorWoodPlanks,
  kFloorGrass,

  kPropTree,
};

enum class TileObjectMeshPart {
  kNone,

  kTreeLeaves,
  kTreeTrunk,
};

float TextureArrayIndex(TileObject, TileObjectMeshPart = TileObjectMeshPart::kNone);

struct ChunkTile {
  TileObject floor = TileObject::kNone;
  TileObject prop  = TileObject::kNone;
};
