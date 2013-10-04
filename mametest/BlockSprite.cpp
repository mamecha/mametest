//
//  BlockSprite.cpp
//  mametest
//
//  Created by 矢島 新太郎 on 2013/08/01.
//
//
#include "BlockSprite.h"

BlockSprite::BlockSprite()
{
}

BlockSprite::~BlockSprite()
{
}

BlockSprite* BlockSprite::createWithBlockType(kBlock blockType)
{
  BlockSprite *pRet = new BlockSprite();
  if (pRet && pRet->initWithBlockType(blockType))
  {
    pRet->autorelease();
    return pRet;
  }
  else
  {
    CC_SAFE_DELETE(pRet);
    return NULL;
  }
}

bool BlockSprite::initWithBlockType(kBlock blockType)
{
  return true;
}

const char* BlockSprite::getBlockImageFileName(kBlock blockType)
{
  switch (blockType) {

    case kBlockRed:
      return "red.png";
      
    case kBlockBlue:
      return "blue.png";

    case kBlockYellow:
      return "yellow.png";

    case kBlockGreen:
      return "green.png";

    case kBlockGray:
      return "gray.png";

    default:
      CCAssert(false, "invalid blockType");
      return "";
  }
}
