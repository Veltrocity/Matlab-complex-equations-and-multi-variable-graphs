

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Thu Jul 30 19:10:13 2015
 */
/* Compiler settings for win64\mwcomutil.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=IA64 7.00.0555 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, IID_IMWUtil,0xC47EA90E,0x56D1,0x11d5,0xB1,0x59,0x00,0xD0,0xB7,0xBA,0x75,0x44);


MIDL_DEFINE_GUID(IID, LIBID_MWComUtil,0xA49FA65F,0xBF26,0x4B8C,0xB2,0x7D,0x8D,0xF6,0xF8,0xBE,0x71,0xD8);


MIDL_DEFINE_GUID(CLSID, CLSID_MWField,0x3A4F8CC5,0x6612,0x499D,0x83,0x50,0xC4,0x2E,0xB0,0x03,0x10,0x92);


MIDL_DEFINE_GUID(CLSID, CLSID_MWStruct,0xF8EE2515,0xF8D1,0x4661,0x8F,0x50,0x47,0xEB,0xEA,0x4B,0xC2,0x05);


MIDL_DEFINE_GUID(CLSID, CLSID_MWComplex,0x8C0E9370,0x6437,0x4B21,0xA4,0x76,0x21,0x80,0x2A,0xD9,0x38,0x64);


MIDL_DEFINE_GUID(CLSID, CLSID_MWSparse,0x7B479181,0x9D92,0x4802,0x8D,0x2C,0x22,0x63,0x9F,0x60,0x9F,0x73);


MIDL_DEFINE_GUID(CLSID, CLSID_MWArg,0xD683D8B2,0x0CF2,0x4BE3,0x91,0x99,0x2B,0x1D,0xF3,0x02,0x5F,0x03);


MIDL_DEFINE_GUID(CLSID, CLSID_MWArrayFormatFlags,0xE6A2FC05,0x5312,0x4F2D,0x8C,0x4E,0xE4,0xD3,0x19,0xEC,0xFA,0xB1);


MIDL_DEFINE_GUID(CLSID, CLSID_MWDataConversionFlags,0xE3B08CDD,0x959F,0x4E53,0xB7,0x09,0xC6,0xFB,0xE1,0x9A,0x99,0xAB);


MIDL_DEFINE_GUID(CLSID, CLSID_MWUtil,0xC42C9239,0x0225,0x4450,0x89,0xE2,0x06,0xD9,0x39,0x43,0xDF,0x98);


MIDL_DEFINE_GUID(CLSID, CLSID_MWFlags,0x416C6FC3,0x2F31,0x4ED2,0x86,0x50,0x59,0x4A,0xD1,0xB9,0x78,0x42);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



