#include "xincs.h"
#include "fxver.h"
#include "fxdefs.h"
#include "FXArray.h"
#include "FXHash.h"
#include "FXStream.h"
#include "FXTextCodec.h"
#include "FXCP1252Codec.h"

namespace FX {

FXIMPLEMENT(FXCP1252Codec,FXTextCodec,nullptr,0)


//// Created by codec tool on 03/25/2005 from: CP1252.TXT ////
static const unsigned short forward_data[256]={
   0,    1,    2,    3,    4,    5,    6,    7,    8,    9,    10,   11,   12,   13,   14,   15,
   16,   17,   18,   19,   20,   21,   22,   23,   24,   25,   26,   27,   28,   29,   30,   31,
   32,   33,   34,   35,   36,   37,   38,   39,   40,   41,   42,   43,   44,   45,   46,   47,
   48,   49,   50,   51,   52,   53,   54,   55,   56,   57,   58,   59,   60,   61,   62,   63,
   64,   65,   66,   67,   68,   69,   70,   71,   72,   73,   74,   75,   76,   77,   78,   79,
   80,   81,   82,   83,   84,   85,   86,   87,   88,   89,   90,   91,   92,   93,   94,   95,
   96,   97,   98,   99,   100,  101,  102,  103,  104,  105,  106,  107,  108,  109,  110,  111,
   112,  113,  114,  115,  116,  117,  118,  119,  120,  121,  122,  123,  124,  125,  126,  127,
   8364, 65533, 8218, 402,  8222, 8230, 8224, 8225, 710,  8240, 352,  8249, 338,  65533, 381,  65533,
   65533, 8216, 8217, 8220, 8221, 8226, 8211, 8212, 732,  8482, 353,  8250, 339,  65533, 382,  376,
   160,  161,  162,  163,  164,  165,  166,  167,  168,  169,  170,  171,  172,  173,  174,  175,
   176,  177,  178,  179,  180,  181,  182,  183,  184,  185,  186,  187,  188,  189,  190,  191,
   192,  193,  194,  195,  196,  197,  198,  199,  200,  201,  202,  203,  204,  205,  206,  207,
   208,  209,  210,  211,  212,  213,  214,  215,  216,  217,  218,  219,  220,  221,  222,  223,
   224,  225,  226,  227,  228,  229,  230,  231,  232,  233,  234,  235,  236,  237,  238,  239,
   240,  241,  242,  243,  244,  245,  246,  247,  248,  249,  250,  251,  252,  253,  254,  255,
  };


static const unsigned char reverse_plane[17]={
  0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
  };

static const unsigned char reverse_pages[73]={
  0,  46, 46, 46, 46, 46, 46, 46, 109,46, 46, 46, 46, 46, 46, 46,
  46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46,
  46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46,
  46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46,
  46, 46, 46, 46, 46, 46, 46, 46, 46,
  };

static const unsigned short reverse_block[173]={
  0,   16,  32,  48,  64,  80,  96,  112, 128, 128, 144, 160, 176, 192, 208, 224,
  128, 128, 128, 128, 128, 240, 256, 264, 128, 279, 128, 128, 128, 128, 128, 128,
  128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 289, 296, 128, 128,
  128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
  128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
  128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
  128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 309, 325,
  341, 128, 128, 128, 128, 128, 128, 352, 128, 128, 128, 128, 128, 128, 128, 366,
  128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
  128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
  128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
  };

static const unsigned char reverse_data[382]={
   0,    1,    2,    3,    4,    5,    6,    7,    8,    9,    10,   11,   12,   13,   14,   15,
   16,   17,   18,   19,   20,   21,   22,   23,   24,   25,   26,   27,   28,   29,   30,   31,
   32,   33,   34,   35,   36,   37,   38,   39,   40,   41,   42,   43,   44,   45,   46,   47,
   48,   49,   50,   51,   52,   53,   54,   55,   56,   57,   58,   59,   60,   61,   62,   63,
   64,   65,   66,   67,   68,   69,   70,   71,   72,   73,   74,   75,   76,   77,   78,   79,
   80,   81,   82,   83,   84,   85,   86,   87,   88,   89,   90,   91,   92,   93,   94,   95,
   96,   97,   98,   99,   100,  101,  102,  103,  104,  105,  106,  107,  108,  109,  110,  111,
   112,  113,  114,  115,  116,  117,  118,  119,  120,  121,  122,  123,  124,  125,  126,  127,
   26,   26,   26,   26,   26,   26,   26,   26,   26,   26,   26,   26,   26,   26,   26,   26,
   160,  161,  162,  163,  164,  165,  166,  167,  168,  169,  170,  171,  172,  173,  174,  175,
   176,  177,  178,  179,  180,  181,  182,  183,  184,  185,  186,  187,  188,  189,  190,  191,
   192,  193,  194,  195,  196,  197,  198,  199,  200,  201,  202,  203,  204,  205,  206,  207,
   208,  209,  210,  211,  212,  213,  214,  215,  216,  217,  218,  219,  220,  221,  222,  223,
   224,  225,  226,  227,  228,  229,  230,  231,  232,  233,  234,  235,  236,  237,  238,  239,
   240,  241,  242,  243,  244,  245,  246,  247,  248,  249,  250,  251,  252,  253,  254,  255,
   26,   26,   140,  156,  26,   26,   26,   26,   26,   26,   26,   26,   26,   26,   26,   26,
   138,  154,  26,   26,   26,   26,   26,   26,   26,   26,   26,   26,   26,   26,   26,   26,
   159,  26,   26,   26,   26,   142,  158,  26,   26,   131,  26,   26,   26,   26,   26,   26,
   26,   26,   26,   26,   26,   26,   26,   136,  26,   26,   26,   26,   26,   26,   26,   26,
   26,   26,   26,   26,   152,  26,   26,   26,   150,  151,  26,   26,   26,   145,  146,  130,
   26,   147,  148,  132,  26,   134,  135,  149,  26,   26,   26,   133,  26,   26,   26,   26,
   26,   26,   26,   26,   26,   137,  26,   26,   26,   26,   26,   26,   26,   26,   139,  155,
   26,   26,   26,   26,   26,   26,   26,   26,   26,   26,   26,   26,   128,  26,   26,   26,
   153,  26,   26,   26,   26,   26,   26,   26,   26,   26,   26,   26,   26,   26,
  };


FXint FXCP1252Codec::mb2wc(FXwchar& wc,const FXchar* src,FXint nsrc) const {
  if(nsrc<1) return -1;
  wc=forward_data[(FXuchar)src[0]];
  return 1;
  }


FXint FXCP1252Codec::wc2mb(FXchar* dst,FXint ndst,FXwchar wc) const {
  if(ndst<1) return -1;
  dst[0]=reverse_data[reverse_block[reverse_pages[reverse_plane[wc>>16]+((wc>>10)&63)]+((wc>>4)&63)]+(wc&15)];
  return 1;
  }

FXint FXCP1252Codec::mibEnum() const {
  return 2252;
  }


const FXchar* FXCP1252Codec::name() const {
  return "windows-1252";
  }


const FXchar* FXCP1252Codec::mimeName() const {
  return "windows-1252";
  }


const FXchar* const* FXCP1252Codec::aliases() const {
  static const FXchar *const list[]={"microsoft-cp1252","windows-1252","cp1252",nullptr};
  return list;
  }

}

