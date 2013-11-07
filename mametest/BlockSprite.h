//
//  BlockSprite.h
//  mametest
//
//  Created by 矢島 新太郎 on 2013/08/01.
//
//

#ifndef __BLOCKSPRITE__H__
#define __BLOCKSPRITE__H__

#include "cocos2d.h"
#include "Config.h"

class BlockSprite : public cocos2d::CCSprite
{
protected:
  const char* getBlockImageFileName(kBlock blockType);
  
public:
  CC_SYNTHESIZE_READONLY(kBlock, m_blockType, BlockType);
  CC_SYNTHESIZE_READONLY(int, m_nextPosX, NextPosX);
  CC_SYNTHESIZE_READONLY(int, m_nextPosY, NextPosY);
 
  void initNextPos();
  void setNextPos(int nextPosX, int nextPosY);
  
  BlockSprite();
  virtual ~BlockSprite();
  virtual bool initWithBlockType(kBlock blockType);
  static BlockSprite* createWithBlockType(kBlock blockType);
  
};
#endif // __BLOCLSPRITE_H__