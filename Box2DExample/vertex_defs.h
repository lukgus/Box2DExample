#ifndef vertex_defs_HG
#define vertex_defs_HG

typedef struct sFloat4
{
	float x, y, z, w;
} sFloat4;

typedef struct sUint4
{
	unsigned int x, y, z, w;
} sUint4;

typedef struct sInt4
{
	int x, y, z, w;
} sInt4;

typedef struct sVertex_p4t4n4
{
	sFloat4 Pos;
	sFloat4 TexUVx2;
	sFloat4 Normal;
} sVertex_p4t4n4;

typedef struct sVertex_p4t4n4b4
{
	sFloat4 Pos;
	sFloat4 TexUVx2;
	sFloat4 Normal;
	sFloat4 BoneWeights;
} sVertex_p4t4n4b4;

typedef struct sVertex_p4t4n4b4i4
{
	sFloat4 Pos;
	sFloat4 TexUVx2;
	sFloat4 Normal;
	sFloat4 BoneIDs;
	sFloat4 BoneWeights;
} sVertex_p4t4n4b4i4;

#endif
