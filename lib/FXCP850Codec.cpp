#include "xincs.h"
#include "fxver.h"
#include "fxdefs.h"
#include "FXArray.h"
#include "FXHash.h"
#include "FXStream.h"
#include "FXTextCodec.h"
#include "FXCP850Codec.h"

namespace FX {

FXIMPLEMENT(FXCP850Codec,FXTextCodec,NULL,0)


//// Created by codec tool on 03/25/2005 from: CP850.TXT ////
static const unsigned short forward_data[256]={
   0,    1,    2,    3,    4,    5,    6,    7,    8,    9,    10,   11,   12,   13,   14,   15,
   16,   17,   18,   19,   20,   21,   22,   23,   24,   25,   26,   27,   28,   29,   30,   31,
   32,   33,   34,   35,   36,   37,   38,   39,   40,   41,   42,   43,   44,   45,   46,   47,
   48,   49,   50,   51,   52,   53,   54,   55,   56,   57,   58,   59,   60,   61,   62,   63,
   64,   65,   66,   67,   68,   69,   70,   71,   72,   73,   74,   75,   76,   77,   78,   79,
   80,   81,   82,   83,   84,   85,   86,   87,   88,   89,   90,   91,   92,   93,   94,   95,
   96,   97,   98,   99,   100,  101,  102,  103,  104,  105,  106,  107,  108,  109,  110,  111,
   112,  113,  114,  115,  116,  117,  118,  119,  120,  121,  122,  123,  124,  125,  126,  127,
   199,  252,  233,  226,  228,  224,  229,  231,  234,  235,  232,  239,  238,  236,  196,  197,
   201,  230,  198,  244,  246,  242,  251,  249,  255,  214,  220,  248,  163,  216,  215,  402,
   225,  237,  243,  250,  241,  209,  170,  186,  191,  174,  172,  189,  188,  161,  171,  187,
   9617, 9618, 9619, 9474, 9508, 193,  194,  192,  169,  9571, 9553, 9559, 9565, 162,  165,  9488,
   9492, 9524, 9516, 9500, 9472, 9532, 227,  195,  9562, 9556, 9577, 9574, 9568, 9552, 9580, 164,
   240,  208,  202,  203,  200,  305,  205,  206,  207,  9496, 9484, 9608, 9604, 166,  204,  9600,
   211,  223,  212,  210,  245,  213,  181,  254,  222,  218,  219,  217,  253,  221,  175,  180,
   173,  177,  8215, 190,  182,  167,  247,  184,  176,  168,  183,  185,  179,  178,  9632, 160,
  };


static const unsigned char reverse_plane[17]={
  0, 10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,
  };

static const unsigned char reverse_pages[74]={
  0,  26, 26, 26, 26, 26, 26, 26, 89, 137,26, 26, 26, 26, 26, 26,
  26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26,
  26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26,
  26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26,
  26, 26, 26, 26, 26, 26, 26, 26, 26, 26,
  };

static const unsigned short reverse_block[201]={
  0,   16,  32,  48,  64,  80,  96,  112, 128, 128, 144, 160, 176, 192, 208, 224,
  128, 128, 128, 240, 128, 128, 128, 128, 128, 254, 128, 128, 128, 128, 128, 128,
  128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
  128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
  128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
  128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 263, 128, 128, 128, 128, 128,
  128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
  128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
  128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
  128, 128, 128, 128, 128, 128, 128, 128, 128, 279, 295, 308, 321, 128, 337, 353,
  128, 369, 384, 400, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
  128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
  128, 128, 128, 128, 128, 128, 128, 128, 128,
  };

static const unsigned char reverse_data[416]={
   0,    1,    2,    3,    4,    5,    6,    7,    8,    9,    10,   11,   12,   13,   14,   15,
   16,   17,   18,   19,   20,   21,   22,   23,   24,   25,   26,   27,   28,   29,   30,   31,
   32,   33,   34,   35,   36,   37,   38,   39,   40,   41,   42,   43,   44,   45,   46,   47,
   48,   49,   50,   51,   52,   53,   54,   55,   56,   57,   58,   59,   60,   61,   62,   63,
   64,   65,   66,   67,   68,   69,   70,   71,   72,   73,   74,   75,   76,   77,   78,   79,
   80,   81,   82,   83,   84,   85,   86,   87,   88,   89,   90,   91,   92,   93,   94,   95,
   96,   97,   98,   99,   100,  101,  102,  103,  104,  105,  106,  107,  108,  109,  110,  111,
   112,  113,  114,  115,  116,  117,  118,  119,  120,  121,  122,  123,  124,  125,  126,  127,
   26,   26,   26,   26,   26,   26,   26,   26,   26,   26,   26,   26,   26,   26,   26,   26,
   255,  173,  189,  156,  207,  190,  221,  245,  249,  184,  166,  174,  170,  240,  169,  238,
   248,  241,  253,  252,  239,  230,  244,  250,  247,  251,  167,  175,  172,  171,  243,  168,
   183,  181,  182,  199,  142,  143,  146,  128,  212,  144,  210,  211,  222,  214,  215,  216,
   209,  165,  227,  224,  226,  229,  153,  158,  157,  235,  233,  234,  154,  237,  232,  225,
   133,  160,  131,  198,  132,  134,  145,  135,  138,  130,  136,  137,  141,  161,  140,  139,
   208,  164,  149,  162,  147,  228,  148,  246,  155,  151,  163,  150,  129,  236,  231,  152,
   26,   213,  26,   26,   26,   26,   26,   26,   26,   26,   26,   26,   26,   26,   26,   26,
   159,  26,   26,   26,   26,   26,   26,   26,   26,   26,   26,   26,   26,   26,   242,  26,
   26,   26,   26,   26,   26,   26,   26,   196,  26,   179,  26,   26,   26,   26,   26,   26,
   26,   26,   26,   218,  26,   26,   26,   191,  26,   26,   26,   192,  26,   26,   26,   217,
   26,   26,   26,   195,  26,   26,   26,   26,   180,  26,   26,   26,   26,   26,   26,   26,
   194,  26,   26,   26,   26,   193,  26,   26,   26,   26,   26,   26,   26,   197,  26,   26,
   26,   205,  186,  26,   26,   201,  26,   26,   187,  26,   26,   200,  26,   26,   188,  26,
   26,   204,  26,   26,   185,  26,   26,   203,  26,   26,   202,  26,   26,   206,  26,   26,
   26,   223,  26,   26,   26,   220,  26,   26,   26,   219,  26,   26,   26,   26,   26,   26,
   26,   176,  177,  178,  26,   26,   26,   26,   26,   26,   26,   26,   26,   26,   26,   26,
   254,  26,   26,   26,   26,   26,   26,   26,   26,   26,   26,   26,   26,   26,   26,   26,
  };


FXint FXCP850Codec::mb2wc(FXwchar& wc,const FXchar* src,FXint nsrc) const {
  if(nsrc<1) return -1;
  wc=forward_data[(FXuchar)src[0]];
  return 1;
  }


FXint FXCP850Codec::wc2mb(FXchar* dst,FXint ndst,FXwchar wc) const {
  if(ndst<1) return -1;
  dst[0]=reverse_data[reverse_block[reverse_pages[reverse_plane[wc>>16]+((wc>>10)&63)]+((wc>>4)&63)]+(wc&15)];
  return 1;
  }

FXint FXCP850Codec::mibEnum() const {
  return 2009;
  }


const FXchar* FXCP850Codec::name() const {
  return "IBM850";
  }


const FXchar* FXCP850Codec::mimeName() const {
  return "IBM850";
  }


const FXchar* const* FXCP850Codec::aliases() const {
  static const FXchar *const list[]={"microsoft-cp850","IBM850","cp850","850","csPC850Multilingual",NULL};
  return list;
  }

}
