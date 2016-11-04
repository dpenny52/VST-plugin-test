//-----------------------------------------------------------------------------
// Project     : SDK Core
//
// Category    : SDK Core Interfaces
// Filename    : pluginterfaces/base/funknown.h
// Created by  : Steinberg, 01/2004
// Description : Basic Interface
//
//-----------------------------------------------------------------------------
// LICENSE
// (c) 2016, Steinberg Media Technologies GmbH, All Rights Reserved
//-----------------------------------------------------------------------------
// This Software Development Kit may not be distributed in parts or its entirety
// without prior written agreement by Steinberg Media Technologies GmbH.
// This SDK must not be used to re-engineer or manipulate any technology used
// in any Steinberg or Third-party application or software module,
// unless permitted by law.
// Neither the name of the Steinberg Media Technologies nor the names of its
// contributors may be used to endorse or promote products derived from this
// software without specific prior written permission.
//
// THIS SDK IS PROVIDED BY STEINBERG MEDIA TECHNOLOGIES GMBH "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
// IN NO EVENT SHALL STEINBERG MEDIA TECHNOLOGIES GMBH BE LIABLE FOR ANY DIRECT,
// INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
// BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
// OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
// OF THE POSSIBILITY OF SUCH DAMAGE.
//------------------------------------------------------------------------------

#ifndef __funknown__
#define __funknown__

#include "pluginterfaces/base/ftypes.h"
#include "pluginterfaces/base/smartpointer.h"
#include <string.h>

//------------------------------------------------------------------------
/*! \defgroup pluginBase Basic Interfaces
*/
//------------------------------------------------------------------------

//------------------------------------------------------------------------
//  Unique Identifier macros
//------------------------------------------------------------------------

#if COM_COMPATIBLE
#define INLINE_UID(l1, l2, l3, l4) \
{ \
	(::Steinberg::int8)((l1 & 0x000000FF)      ), (::Steinberg::int8)((l1 & 0x0000FF00) >>  8), \
	(::Steinberg::int8)((l1 & 0x00FF0000) >> 16), (::Steinberg::int8)((l1 & 0xFF000000) >> 24), \
	(::Steinberg::int8)((l2 & 0x00FF0000) >> 16), (::Steinberg::int8)((l2 & 0xFF000000) >> 24), \
	(::Steinberg::int8)((l2 & 0x000000FF)      ), (::Steinberg::int8)((l2 & 0x0000FF00) >>  8), \
	(::Steinberg::int8)((l3 & 0xFF000000) >> 24), (::Steinberg::int8)((l3 & 0x00FF0000) >> 16), \
	(::Steinberg::int8)((l3 & 0x0000FF00) >>  8), (::Steinberg::int8)((l3 & 0x000000FF)      ), \
	(::Steinberg::int8)((l4 & 0xFF000000) >> 24), (::Steinberg::int8)((l4 & 0x00FF0000) >> 16), \
	(::Steinberg::int8)((l4 & 0x0000FF00) >>  8), (::Steinberg::int8)((l4 & 0x000000FF)      )  \
}
#else
#define INLINE_UID(l1, l2, l3, l4) \
{ \
	(::Steinberg::int8)((l1 & 0xFF000000) >> 24), (::Steinberg::int8)((l1 & 0x00FF0000) >> 16), \
	(::Steinberg::int8)((l1 & 0x0000FF00) >>  8), (::Steinberg::int8)((l1 & 0x000000FF)      ), \
	(::Steinberg::int8)((l2 & 0xFF000000) >> 24), (::Steinberg::int8)((l2 & 0x00FF0000) >> 16), \
	(::Steinberg::int8)((l2 & 0x0000FF00) >>  8), (::Steinberg::int8)((l2 & 0x000000FF)      ), \
	(::Steinberg::int8)((l3 & 0xFF000000) >> 24), (::Steinberg::int8)((l3 & 0x00FF0000) >> 16), \
	(::Steinberg::int8)((l3 & 0x0000FF00) >>  8), (::Steinberg::int8)((l3 & 0x000000FF)      ), \
	(::Steinberg::int8)((l4 & 0xFF000000) >> 24), (::Steinberg::int8)((l4 & 0x00FF0000) >> 16), \
	(::Steinberg::int8)((l4 & 0x0000FF00) >>  8), (::Steinberg::int8)((l4 & 0x000000FF)      )  \
}
#endif

//------------------------------------------------------------------------
#define DECLARE_UID(name, l1, l2, l3, l4) \
	::Steinberg::TUID name = INLINE_UID (l1, l2, l3, l4);

//------------------------------------------------------------------------
#define EXTERN_UID(name) \
	extern const ::Steinberg::TUID name;


#ifdef INIT_CLASS_IID
#define DECLARE_CLASS_IID(ClassName, l1, l2, l3, l4) static const ::Steinberg::TUID ClassName##_iid = INLINE_UID (l1, l2, l3, l4); \
const ::Steinberg::FUID ClassName::iid (ClassName##_iid);
#else
#define DECLARE_CLASS_IID(ClassName, l1, l2, l3, l4) static const ::Steinberg::TUID ClassName##_iid = INLINE_UID (l1, l2, l3, l4);
#endif
#define DEF_CLASS_IID(ClassName) const ::Steinberg::FUID ClassName::iid (ClassName##_iid);

#define INLINE_UID_OF(ClassName) ClassName##_iid

#define INLINE_UID_FROM_FUID(x) INLINE_UID(x.getLong1 (), x.getLong2 (), x.getLong3 (), x.getLong4 ())

//------------------------------------------------------------------------
//  FUnknown implementation macros
//------------------------------------------------------------------------

#define DECLARE_FUNKNOWN_METHODS                                                                      \
public:	                                                                                              \
	virtual ::Steinberg::tresult PLUGIN_API queryInterface (const ::Steinberg::TUID _iid, void** obj); \
	virtual ::Steinberg::uint32 PLUGIN_API addRef ();                                                 \
	virtual ::Steinberg::uint32 PLUGIN_API release ();                                                \
protected :                                                                                           \
	::Steinberg::int32 __funknownRefCount;                                                            \
public:

//------------------------------------------------------------------------

#define DELEGATE_REFCOUNT(ClassName)											        \
public:																			        \
	virtual ::Steinberg::uint32 PLUGIN_API addRef ()  { return ClassName::addRef ();  }	\
	virtual ::Steinberg::uint32 PLUGIN_API release () { return ClassName::release (); }

//------------------------------------------------------------------------
#define IMPLEMENT_REFCOUNT(ClassName)                                          \
::Steinberg::uint32 PLUGIN_API ClassName::addRef ()                            \
{                                                                              \
	return ::Steinberg::FUnknownPrivate::atomicAdd (__funknownRefCount, 1);    \
}                                                                              \
::Steinberg::uint32 PLUGIN_API ClassName::release ()                           \
{                                                                              \
	if (::Steinberg::FUnknownPrivate::atomicAdd (__funknownRefCount, -1) == 0) \
	{                                                                          \
		delete this;                                                           \
		return 0;                                                              \
	}                                                                          \
	return __funknownRefCount;                                                 \
}

//------------------------------------------------------------------------
#define FUNKNOWN_CTOR	{ __funknownRefCount = 1; }
#define FUNKNOWN_DTOR

//------------------------------------------------------------------------
#define QUERY_INTERFACE(iid, obj, InterfaceIID, InterfaceName)  \
if (::Steinberg::FUnknownPrivate::iidEqual (iid, InterfaceIID)) \
{                                                               \
	addRef ();                                                  \
	*obj = static_cast< InterfaceName* >(this);                 \
	return ::Steinberg::kResultOk;                              \
}

//------------------------------------------------------------------------
#define IMPLEMENT_QUERYINTERFACE(ClassName, InterfaceName, ClassIID)                                \
::Steinberg::tresult PLUGIN_API ClassName::queryInterface (const ::Steinberg::TUID _iid, void** obj) \
{                                                                                                   \
	QUERY_INTERFACE (_iid, obj, ::Steinberg::FUnknown::iid, InterfaceName)                           \
	QUERY_INTERFACE (_iid, obj, ClassIID, InterfaceName)                                             \
	*obj = NULL;                                                                                       \
	return ::Steinberg::kNoInterface;                                                               \
}

//------------------------------------------------------------------------
#define IMPLEMENT_FUNKNOWN_METHODS(ClassName,InterfaceName,ClassIID) \
	IMPLEMENT_REFCOUNT (ClassName)                                   \
	IMPLEMENT_QUERYINTERFACE (ClassName, InterfaceName, ClassIID)

//------------------------------------------------------------------------
//  Result Codes
//------------------------------------------------------------------------

namespace Steinberg {

//------------------------------------------------------------------------
#if COM_COMPATIBLE
#if WINDOWS
enum
{
	kNoInterface		= static_cast<tresult>(0x80004002L),	// E_NOINTERFACE
	kResultOk			= static_cast<tresult>(0x00000000L),	// S_OK
	kResultTrue			= kResultOk,
	kResultFalse		= static_cast<tresult>(0x00000001L),	// S_FALSE
	kInvalidArgument	= static_cast<tresult>(0x80070057L),	// E_INVALIDARG
	kNotImplemented		= static_cast<tresult>(0x80004001L),	// E_NOTIMPL
	kInternalError		= static_cast<tresult>(0x80004005L),	// E_FAIL
	kNotInitialized		= static_cast<tresult>(0x8000FFFFL),	// E_UNEXPECTED
	kOutOfMemory		= static_cast<tresult>(0x8007000EL)		// E_OUTOFMEMORY
};
#else
enum
{
	kNoInterface		= static_cast<tresult>(0x80000004L),	// E_NOINTERFACE
	kResultOk			= static_cast<tresult>(0x00000000L),	// S_OK
	kResultTrue			= kResultOk,
	kResultFalse		= static_cast<tresult>(0x00000001L),	// S_FALSE
	kInvalidArgument	= static_cast<tresult>(0x80000003L),	// E_INVALIDARG
	kNotImplemented		= static_cast<tresult>(0x80000001L),	// E_NOTIMPL
	kInternalError		= static_cast<tresult>(0x80000008L),	// E_FAIL
	kNotInitialized		= static_cast<tresult>(0x8000FFFFL),	// E_UNEXPECTED
	kOutOfMemory		= static_cast<tresult>(0x80000002L)		// E_OUTOFMEMORY
};
#endif
#else
enum
{
	kNoInterface = -1,
	kResultOk,
	kResultTrue = kResultOk,
	kResultFalse,
	kInvalidArgument,
	kNotImplemented,
	kInternalError,
	kNotInitialized,
	kOutOfMemory
};
#endif

//------------------------------------------------------------------------
typedef int64 LARGE_INT; // obsolete

//------------------------------------------------------------------------
//	FUID class declaration
//------------------------------------------------------------------------
typedef int8 TUID[16]; ///< plain UID type

//------------------------------------------------------------------------
/* FUnknown private */
namespace FUnknownPrivate {
SMTG_ALWAYS_INLINE bool iidEqual (const void* iid1, const void* iid2)
{
	const uint64* p1 = reinterpret_cast<const uint64*> (iid1);
	const uint64* p2 = reinterpret_cast<const uint64*> (iid2);
	return p1[0] == p2[0] && p1[1] == p2[1];
}

int32 PLUGIN_API atomicAdd (int32& value, int32 amount);
}

//------------------------------------------------------------------------
/** Handling 16 Byte Globaly Unique Identifiers.
\ingroup pluginBase

Each interface declares its identifier as static member inside the interface
namespace (e.g. FUnknown::iid).
*/
//------------------------------------------------------------------------
class FUID
{
public:
//------------------------------------------------------------------------
	FUID ();
	inline FUID (const TUID uid);
	FUID (uint32 l1, uint32 l2, uint32 l3, uint32 l4);
	FUID (const FUID&);
	virtual ~FUID () {}

	/** Generates a new Unique Identifier (UID).
	    Will return true for success. If the return value is false, either no
	    UID is generated or the UID is not guaranteed to be unique worldwide. */
	bool generate ();

	/** Checks if the UID data is valid.
		The default constructor initializes the memory with zeros. */
	bool isValid () const;

	FUID& operator = (const FUID& f);
	FUID& operator = (FIDString uid);
	FUID& operator = (TUID uid);

	bool operator == (const FUID& f) const { return ::Steinberg::FUnknownPrivate::iidEqual (data, f.data); }
	bool operator == (FIDString uid) const { return ::Steinberg::FUnknownPrivate::iidEqual (data, uid); }
	bool operator == (TUID uid) const { return ::Steinberg::FUnknownPrivate::iidEqual (data, uid); }

	bool operator < (const FUID& f) const { return memcmp (data, f.data, sizeof (TUID)) < 0; }
	bool operator < (FIDString uid) const { return memcmp (data, uid, sizeof (TUID)) < 0; }
	bool operator < (TUID uid) const { return memcmp (data, uid, sizeof (TUID)) < 0; }

	bool operator != (const FUID& f) const   { return !::Steinberg::FUnknownPrivate::iidEqual (data, f.data); }
	bool operator != (FIDString uid) const { return !::Steinberg::FUnknownPrivate::iidEqual (data, uid); }
	bool operator != (TUID uid) const { return !::Steinberg::FUnknownPrivate::iidEqual (data, uid); }

	operator FIDString () const { return data; }
	operator char* () { return data; }

 	uint32 getLong1 () const;
 	uint32 getLong2 () const;
 	uint32 getLong3 () const;
 	uint32 getLong4 () const;

	void from4Int (uint32 d1, uint32 d2, uint32 d3, uint32 d4);
	void to4Int (uint32& d1, uint32& d2, uint32& d3, uint32& d4) const;

	typedef char8 String [64];

	/** Converts UID to a string.
		The string will be 32 characters long, representing the hexadecimal values
		of each data byte (e.g. "9127BE30160E4BB69966670AA6087880"). */
	void toString (char8* string) const;

	/** Sets the UID data from a string.
		The string has to be 32 characters long, where each character-pair is
		the ASCII-encoded hexadecimal value of the corresponding data byte. */
	bool fromString (const char8* string);

	/** Converts UID to a string in Microsoft� OLE format.
	(e.g. "{c200e360-38c5-11ce-ae62-08002b2b79ef}") */
	void toRegistryString (char8* string) const;

	/** Sets the UID data from a string in Microsoft� OLE format. */
	bool fromRegistryString (const char8* string);

	enum UIDPrintStyle
	{
		kINLINE_UID,  ///< "INLINE_UID (0x00000000, 0x00000000, 0x00000000, 0x00000000)"
		kDECLARE_UID, ///< "DECLARE_UID (0x00000000, 0x00000000, 0x00000000, 0x00000000)"
		kFUID,        ///< "FUID (0x00000000, 0x00000000, 0x00000000, 0x00000000)"
		kCLASS_UID    ///< "DECLARE_CLASS_IID (Interface, 0x00000000, 0x00000000, 0x00000000, 0x00000000)"
	};
	/** Prints the UID to a string (or debug output if string is NULL).
		\param string is the output string if not NULL.
		\param style can be chosen from the FUID::UIDPrintStyle enumeration. */
	void print (char8* string = 0, int32 style = kINLINE_UID) const;

	void toTUID (TUID result) const;

	inline const TUID& toTUID () const
	{
		return data;
	}

//------------------------------------------------------------------------
protected:
	TUID data;
};

//------------------------------------------------------------------------
inline FUID::FUID (const TUID uid)
{
	memset (data, 0, sizeof (TUID));
	if (uid)
		memcpy (data, uid, sizeof (TUID));
}

//------------------------------------------------------------------------
// FUnknown
//------------------------------------------------------------------------
/**	The basic interface of all interfaces.
\ingroup pluginBase

- The FUnknown::queryInterface method is used to retrieve pointers to other
  interfaces of the object.
- FUnknown::addRef and FUnknown::release manage the lifetime of the object.
  If no more references exist, the object is destroyed in memory.

Interfaces are identified by 16 byte Globally Unique Identifiers.
The SDK provides a class called FUID for this purpose.

\sa \ref howtoClass */
//------------------------------------------------------------------------
class FUnknown
{
public:
//------------------------------------------------------------------------
	/** Query for a pointer to the specified interface.
	Returns kResultOk on success or kNoInterface if the object does not implement the interface.
	The object has to call addRef when returning an interface.
	\param _iid : (in) 16 Byte interface identifier (-> FUID)
	\param obj : (out) On return, *obj points to the requested interface */
	virtual tresult PLUGIN_API queryInterface (const TUID _iid, void** obj) = 0;

	/** Adds a reference and return the new reference count.
	\par Remarks:
		The initial reference count after creating an object is 1. */
	virtual uint32 PLUGIN_API addRef () = 0;

	/** Releases a reference and return the new reference count.
	If the reference count reaches zero, the object will be destroyed in memory. */
	virtual uint32 PLUGIN_API release () = 0;

//------------------------------------------------------------------------
	static const FUID iid;
//------------------------------------------------------------------------
};

DECLARE_CLASS_IID (FUnknown, 0x00000000, 0x00000000, 0xC0000000, 0x00000046)

//------------------------------------------------------------------------
// FUnknownPtr
//------------------------------------------------------------------------
/** FUnknownPtr - automatic interface conversion and smart pointer in one.
    This template class can be used for interface conversion like this:
					\code
	IPtr<IPath> path = owned (FHostCreate (IPath, hostClasses));
	FUnknownPtr<IPath2> path2 (path); // does a query interface for IPath2
	if (path2)
		...
					\endcode
*/
//------------------------------------------------------------------------
template <class I>
class FUnknownPtr : public IPtr<I>
{
public:
//------------------------------------------------------------------------
	inline FUnknownPtr (FUnknown* unknown); // query interface
	inline FUnknownPtr (const FUnknownPtr& p) : IPtr<I> (p) {}
	inline FUnknownPtr () {}

	inline FUnknownPtr& operator=(const FUnknownPtr& p) {IPtr<I>::operator=(p); return *this;}
	inline I* operator=(FUnknown* unknown);
	inline I* getInterface () { return this->ptr; }
};

//------------------------------------------------------------------------
template <class I>
inline FUnknownPtr<I>::FUnknownPtr (FUnknown* unknown)
{
	if (unknown && unknown->queryInterface (I::iid, (void**)&this->ptr) != kResultOk)
		this->ptr = 0;
}

//------------------------------------------------------------------------
template <class I>
inline I* FUnknownPtr<I>::operator=(FUnknown* unknown)
{
	I* newPtr = 0;
	if (unknown && unknown->queryInterface (I::iid, (void**)&newPtr) == kResultOk)
	{
		OPtr<I> rel (newPtr);
		return IPtr<I>::operator=(newPtr);
	}

	return IPtr<I>::operator=(0);
}


//------------------------------------------------------------------------
// FReleaser (obsolete)
//------------------------------------------------------------------------
/** Release an interface using automatic object (obsolete).
This class is obsolete and is only kept for compatibility.
The replacement for FReleaser is OPtr.

Usage example with FReleaser:
										\code
	void someFunction ()
	{
		IPath* path = pathCreateMethod ();
		FReleaser releaser (path);
		.... do something with path...
		.... path not used anymore, releaser will destroy it when leaving function scope
	}
										\endcode
Usage example with OPtr:
										\code
	void someFunction ()
	{
		OPtr<IPath> path = pathCreateMethod ();
		.... do something with path...
		.... path not used anymore, OPtr will destroy it when leaving function scope
	}
										\endcode
*/
//------------------------------------------------------------------------
struct FReleaser
{
	FReleaser (FUnknown* u): u (u) {}
	~FReleaser () { if (u) u->release (); }

	FUnknown* u;
};

}

#endif
