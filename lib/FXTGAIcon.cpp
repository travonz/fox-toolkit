/********************************************************************************
*                                                                               *
*                     T A R G A   I c o n   O b j e c t                         *
*                                                                               *
*********************************************************************************
* Copyright (C) 2001,2022 by Janusz Ganczarski.   All Rights Reserved.          *
*********************************************************************************
* This library is free software; you can redistribute it and/or modify          *
* it under the terms of the GNU Lesser General Public License as published by   *
* the Free Software Foundation; either version 3 of the License, or             *
* (at your option) any later version.                                           *
*                                                                               *
* This library is distributed in the hope that it will be useful,               *
* but WITHOUT ANY WARRANTY; without even the implied warranty of                *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                 *
* GNU Lesser General Public License for more details.                           *
*                                                                               *
* You should have received a copy of the GNU Lesser General Public License      *
* along with this program.  If not, see <http://www.gnu.org/licenses/>          *
********************************************************************************/
#include "xincs.h"
#include "fxver.h"
#include "fxdefs.h"
#include "fxmath.h"
#include "FXArray.h"
#include "FXHash.h"
#include "FXMutex.h"
#include "FXStream.h"
#include "FXMemoryStream.h"
#include "FXString.h"
#include "FXSize.h"
#include "FXPoint.h"
#include "FXRectangle.h"
#include "FXStringDictionary.h"
#include "FXSettings.h"
#include "FXRegistry.h"
#include "FXEvent.h"
#include "FXWindow.h"
#include "FXApp.h"
#include "FXTGAIcon.h"


/*
  Notes:
  - Targa does not support alpha in the file format.
  - You can also let the system guess a transparancy color based on the corners.
  - If that doesn't work, you can force a specific transparency color.
  - This is just an idea at this point:

      // Compute name of image support class
      FXString name="FX"+ext.upper()+"Image";

      // Find the meta class
      const FXMetaClass *meta=FXMetaClass::getMetaClassFromName(name.text());

      // Make instance of this class
      if(meta) img=(FXImage*)meta->makeInstance();

    The above is a simplistic view; we will need to set the image's visual,
    options, and other stuff before this can work.
    Also, when linking statically, we have to convince the linker to include
    the referred image code...

*/

using namespace FX;

/*******************************************************************************/

namespace FX {


// Suggested file extension
const FXchar FXTGAIcon::fileExt[]="tga";


// Suggested mime type
const FXchar FXTGAIcon::mimeType[]="image/targa";


// Object implementation
FXIMPLEMENT(FXTGAIcon,FXIcon,nullptr,0)


// Initialize nicely
FXTGAIcon::FXTGAIcon(FXApp* a,const FXuchar *pix,FXColor clr,FXuint opts,FXint w,FXint h):FXIcon(a,nullptr,clr,opts,w,h){
  if(pix){
    FXMemoryStream ms(FXStreamLoad,const_cast<FXuchar*>(pix));
    loadPixels(ms);
    }
  }


// Save pixels to stream
FXbool FXTGAIcon::savePixels(FXStream& store) const {
  if(fxsaveTGA(store,data,width,height)){
    return true;
    }
  return false;
  }


// Load pixels from stream
FXbool FXTGAIcon::loadPixels(FXStream& store){
  FXColor *pixels; FXint w,h;
  if(fxloadTGA(store,pixels,w,h)){
    setData(pixels,IMAGE_OWNED,w,h);
    if(options&IMAGE_ALPHAGUESS) setTransparentColor(guesstransp());
    if(options&IMAGE_THRESGUESS) setThresholdValue(guessthresh());
    return true;
    }
  return false;
  }


// Clean up
FXTGAIcon::~FXTGAIcon(){
  }

}
