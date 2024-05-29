#ifndef __LTBASETYPES_H__
#define __LTBASETYPES_H__

    #ifndef __MATH_H__
	#include <math.h>
    #define __MATH_H__
    #endif

    #ifndef __LTINTEGER_H__
    #include "ltinteger.h"
    #endif


	// Use the new sound system in 3.1
	#ifndef USE_ABSTRACT_SOUND_INTERFACES
	#define USE_ABSTRACT_SOUND_INTERFACES 1
	#endif

/*!
Base types.
*/
	typedef unsigned int LTBOOL;
	typedef float LTFLOAT;
	typedef uint32 LTRESULT;



/*!
Base type values (enumeration emulation).
LTBOOL.
*/
	#define LTFALSE		0
	#define LTTRUE		1


/*!
LTRESULT (defined in ltcodes.h).
*/



/*!
Forward declaration of LTObject.
*/
	class LTObject;



/*!
Handles.
Object handle definition.
*/
	typedef LTObject* HOBJECT;
	typedef LTObject* HLOCALOBJ;

	#define INVALID_HOBJECT ((LTObject *)0)

/*!
Model handles.
*/
	typedef uint32 HMODELPIECE;
	#define INVALID_MODEL_PIECE ((HMODELPIECE)-1)

	typedef uint32 HMODELSOCKET;
	#define INVALID_MODEL_SOCKET ((HMODELSOCKET)-1)

	typedef uint32 HMODELNODE;
	#define INVALID_MODEL_NODE ((HMODELNODE)-1)

	typedef uint32 HMODELWEIGHTSET;
	#define INVALID_MODEL_WEIGHTSET ((HMODELWEIGHTSET)-1)

	typedef uint32 HMODELANIM;
	#define INVALID_MODEL_ANIM ((HMODELANIM)-1)

/*!
Effect Shader handles.
*/
	typedef uint32 HEFFECTPOOL;
	#define INVALID_EFFECT_POOL ((HEFFECTPOOL)-1)
	#define NO_EFFECT_POOL INVALID_EFFECT_POOL

/*!
Render Target handles
*/
	typedef uint32 HRENDERTARGET;
	#define INVALID_RENDER_TARGET ((HRENDERTARGET)-1)
	#define DEFAULT_RENDER_TARGET 0

/*!
Poly reference.
*/
	struct HPOLY
	{
		HPOLY(uint32 nWorldIndex, uint32 nPolyIndex) : m_nWorldIndex(nWorldIndex), m_nPolyIndex(nPolyIndex) {}
		HPOLY() : m_nWorldIndex(0xFFFFFFFF), m_nPolyIndex(0xFFFFFFFF) {}
		HPOLY &operator=(const HPOLY &hOther)
		{
			m_nWorldIndex = hOther.m_nWorldIndex;
			m_nPolyIndex = hOther.m_nPolyIndex;
			return *this;
		}
		bool operator==(const HPOLY &hOther)
		{
			return (m_nWorldIndex == hOther.m_nWorldIndex) && (m_nPolyIndex == hOther.m_nPolyIndex);
		}
		bool operator!=(const HPOLY &hOther)
		{
			return (m_nWorldIndex != hOther.m_nWorldIndex) || (m_nPolyIndex != hOther.m_nPolyIndex);
		}

		uint32 m_nPolyIndex, m_nWorldIndex;
	};
	#define INVALID_HPOLY HPOLY(0xFFFFFFFF, 0xFFFFFFFF)

/*!
Color types (different byte ordering for cross platform development).
*/
	struct LTRGB			{ uint8 b, g, r, a; };

/*!
Globally unique identifier.
*/
	struct _LTGUID	// the windows-ish version
	{
		uint32	a;
		uint16	b;
		uint16	c;
		uint8   d[8];
	};

	struct _LTGUID_64
	{
		uint64	a;
		uint64  b;
	};

	union LTGUID
	{
		_LTGUID guid;
		_LTGUID_64 guid_64;	   // use this for fast & easy compares

		inline
		bool operator<(const LTGUID& _X) const
		{ return (guid_64.a == _X.guid_64.a) ? (guid_64.b < _X.guid_64.b) : (guid_64.a < _X.guid_64.a); }
	
		inline
		bool operator==(const LTGUID& _X) const
		{ return (guid_64.a == _X.guid_64.a) && (guid_64.b == _X.guid_64.b); }
	};
	// macros for defining LTGUIDs a la windows...
	// Define INITLTGUID where the LTGUIDs are defined;
	// Undefine INITLTGUID where LTGUIDs are declared but not defined.
	#ifndef INITLTGUID
	#define DEFINE_LTGUID(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
		extern "C" const LTGUID name
	#else

	#define DEFINE_LTGUID(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
			extern "C" const LTGUID name \
					= { l, w1, w2, { b1, b2,  b3,  b4,  b5,  b6,  b7,  b8 } }
	#endif // INITLTGUID


/*!
More complicated types.
*/


/*!
Structures.
*/
	struct PGColor
	{
//! RGB 0-255.
		float x, y, z; 

//! Alpha 0-255.
		float a; 
	};

	struct LTFloatPt
	{
		float	x, y;
	};

	struct LTIntPt
	{
		LTIntPt(int a = 0, int b = 0) : x(a), y(b) {}
		int	x, y;
	};

	struct LTWarpPt
	{
		float source_x, source_y;
		float dest_x, dest_y;
	};

	struct ArgList
	{
		char **argv;
		int argc;
	};


/*!
This class use a position and quaternion to represent a coordinate frame.
The ILTTransform interface can be used to work with these objects.
*/



/*!
This is used to distinguish between flag types.
*/
	enum ObjFlagType
	{

//! FLAG_  #defines
		OFT_Flags = 0,	

//! FLAG2_ #defines
		OFT_Flags2,

//! User flags
		OFT_User,

//! Client flags (Not available on server objects)
		OFT_Client
	};

/*!
This is used to distinguish between different object resources
*/
	enum EObjectResource
	{

//! The main file for the object for sprites this is the sprite, for models the model
		eObjectResource_ObjectFile,

//! The texture for this object, valid indices are 0...MAX_TEXTURES
		eObjectResource_Texture,

//! The render styles associated with the object 0...MAX_RENDERSTYLES
		eObjectResource_RenderStyle,

//! The extra childmodels associated with the object 0...MAX_CHILDMODELS
		eObjectResource_ChildModel,
	};

#endif //! __LTBASETYPES_H__










