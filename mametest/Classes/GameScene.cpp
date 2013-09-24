//
//  GameScene.cpp
//  nyangame
//
//  Created by 矢島 新太郎 on 2013/07/25.
//
//

#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "BlockSprite.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;

// 変数初期化
void GameScene::initForVariables()
{
  // 乱数
  srand((unsigned)time(NULL));
  
  // こま一辺の長さを取得
  BlockSprite* pBlock = BlockSprite::createWithBlockType(kBlockRed);
  m_blockSize = pBlock->getContentSize().height;
}

// 位置取得
CCPoint GameScene::getPosition(int posIndexX, int posIndexY)
{
  float offsetX = m_background->getContentSize().width * 0.168;
  float offsetY = m_background->getContentSize().height * 0.029;
  return CCPoint((posIndexX + 0.5) * m_blockSize + offsetX, (posIndexY + 0.5) * m_blockSize + offsetY);
}

CCScene* GameScene::scene()
{
  CCScene* scene = CCScene::create();
  GameScene* layer = GameScene::create();
  scene->addChild(layer);
  return scene;
}

// 初期化
bool GameScene::init()
{
  if (!CCLayer::init())
  {
    return false;
  }
  
  // 背景を表示
  showBackground();
  return true;
}

// background view
void GameScene::showBackground()
{
  CCSize winSize = CCDirector::sharedDirector()->getWinSize();
  
  // 背景を生成
  m_background = CCSprite::create(PNG_BACKGROUND);
  m_background->setPosition(ccp(winSize.width / 2, winSize.height / 2));
  addChild(m_background, kZOrderBackground, kTagBackground);
}