//
//  GameScene.h
//  nyangame
//
//  Created by 矢島 新太郎 on 2013/07/25.
//
//

#ifndef __GAMESCENE_H_
#define __GAMESCENE_H_

#include "cocos2d.h"
#include "Config.h"

#define MAX_BLOCK_X 8
#define MAX_BLOCK_Y 8

#define PNG_BACKGROUND "background.png"

class GameScene : public cocos2d::CCLayer
{
protected:
  enum kTag
  {
    kTagBackground = 1,
    kTagBaseBlock = 10000,
  };
  
  enum kZOrder
  {
    kZOrderBackground,
    kZOrderBlock,
  };
  
  // 2-2-3
  cocos2d::CCSprite* m_background;
  void showBackground();
  
  // 2-2-4
  float m_blockSize;
  std::map<kBlock, std::list<int> > m_blockTags;
  void initForVariables();
  void showBlock();
  cocos2d::CCPoint getPosition(int posIndexX, int posIndexY);
  int getTag(int PosIndexX, int posIndexY);
  
  // 2-2-5
  void getTouchBlockTag(cocos2d::CCPoint touchPoint, int &tag, kBlock &blockType);
  std::list<int> getSameColorBlockTags(int baseTag, kBlock blockType);
  void removeBlock(std::list<int> blockTags, kBlock blockType);
  bool hasSameColorBlock(std::list<int> blockTagList, int searchBlockTag);
  
public:
  virtual bool init();
  static cocos2d::CCScene* scene();
  CREATE_FUNC(GameScene);
  
  virtual bool ccTouchBegan(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
  virtual void ccTouchEnded(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
};


#endif /* defined(__GameScene_H_) */