#ifndef __METIN_II_COMMON_BUILDING_H__
#define __METIN_II_COMMON_BUILDING_H__

namespace building 
{
	enum
	{
		OBJECT_MATERIAL_MAX_NUM = 5,
	};

	typedef struct SLand
	{
		uint32_t	dwID;
		int32_t	lMapIndex;
		int32_t	x, y;
		int32_t	width, height;
		uint32_t	dwGuildID;
		uint8_t	bGuildLevelLimit;
		uint32_t	dwPrice;
	} TLand;

	typedef struct SObjectMaterial
	{
		uint32_t	dwItemVnum;
		uint32_t	dwCount;
	} TObjectMaterial;

	typedef struct SObjectProto
	{
		uint32_t	dwVnum;
		uint32_t	dwPrice;

		TObjectMaterial kMaterials[OBJECT_MATERIAL_MAX_NUM];

		uint32_t	dwUpgradeVnum;
		uint32_t	dwUpgradeLimitTime;
		int32_t	lLife;
		int32_t	lRegion[4];

		uint32_t	dwNPCVnum;
		int32_t	lNPCX;
		int32_t	lNPCY;

		uint32_t	dwGroupVnum; // 같은 그룹은 하나만 건설가능
		uint32_t	dwDependOnGroupVnum; // 지어져 있어야하는 그룹
	} TObjectProto;

	typedef struct SObject
	{
		uint32_t	dwID;
		uint32_t	dwLandID;
		uint32_t	dwVnum;
		int32_t	lMapIndex;
		int32_t	x, y;

		float	xRot;
		float	yRot;
		float	zRot;
		int32_t	lLife;
	} TObject;
};

#endif
