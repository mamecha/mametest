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

// background view
void GameScene::showBackground()
{
  CCSize winSize = CCDirector::sharedDirector()->getWinSize();
  
  // 背景を生成
  m_background = CCSprite::create(PNG_BACKGROUND);
  m_background->setPosition(ccp(winSize.width / 2, winSize.height / 2));
  addChild(m_background, kZOrderBackground, kTagBackground);
}

// タグ取得
int GameScene::getTag(int posIndexX, int posIndexY)
{
  return kTagBaseBlock * posIndexX * 100 + posIndexY;
}

// コマ表示
void GameScene::showBlock()
{
  // 8 * 8
  for (int x=0; x < MAX_BLOCK_X; x++)
  {
    for (int y=0; y < MAX_BLOCK_Y; y++)
    {
      // ランダムでコマ生成
      kBlock blockType = (kBlock)(rand() % kBlockCount);
      
      // 対応するコマ配列にタグを追加
      int tag = getTag(x, y);
      m_blockTags[blockType].push_back(tag);

      // コマ作成
      BlockSprite* pBlock = BlockSprite::createWithBlockType(blockType);
      pBlock->setPosition(getPosition(x, y));
      m_background->addChild(pBlock, kZOrderBlock, tag);
    }
  }
}
bool GameScene::ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent)
{
  return true;
}
// touch
void GameScene::getTouchBlockTag(CCPoint touchPoint, int &tag, kBlock &blockType)
{
  for (int x = 0; x < MAX_BLOCK_X; x++)
  {
    for (int y = 0; y < MAX_BLOCK_Y; y++)
    {
      int currentTag = getTag(x, y);
      CCNode* node = m_background->getChildByTag(currentTag);
      if (node && node->boundingBox().containsPoint(touchPoint))
      {
        tag = currentTag;
        blockType = ((BlockSprite*)node)->getBlockType();
        
        return;
      }
    }
  }
}
// コマが配列にあるか検索
bool GameScene::hasSameColorBlock(list<int> blockTagList, int searchBlockTag)
{
  list<int>::iterator it;
  for (it = blockTagList.begin(); it != blockTagList.end(); ++it)
  {
    if (*it == searchBlockTag)
    {
      return true;
    }
  }
  return false;
}
// タップされたコマと同色で勝つ接しているコマの配列を返す
list<int> GameScene::getSameColorBlockTags(int baseTag, kBlock blockType)
{
  // 同色のコマを格納する配列のしょきか
  list<int> sameColorBlockTags;
  sameColorBlockTags.push_back(baseTag);
  
  list<int>::iterator it = sameColorBlockTags.begin();
  while (it != sameColorBlockTags.end())
  {
    int tags[] = {
      *it +  100,// right block
      *it - 100,//   left block
      *it + 1,// up block
      *it - 1, // down block
    };
    
    for (int i = 0; i < sizeof(tags) / sizeof(tags[0]); i++)
    {
      // 既にリストがあるか検索
      if (!hasSameColorBlock(sameColorBlockTags, tags[i]))
      {
        // コマ配列にあるか
        if (!hasSameColorBlock(m_blockTags[blockType], tags[i]))
        {
          sameColorBlockTags.push_back(tags[i]);
        }
      }
    }
    it++;
  }
  return sameColorBlockTags;
}
// コマ削除
void GameScene::removeBlock(list<int> blockTags, kBlock blockType)
{
  list<int>::iterator it = blockTags.begin();
  while (it != blockTags.end())
  {
    // 既存配列から該当コマを削除
    m_blockTags[blockType].remove(*it);
    
    // 対象となるコマ取得
    CCNode* block = m_background->getChildByTag(*it);
    if (block)
    {
      block->removeFromParentAndCleanup(true);
    }
    it++;
  }
}

// タッチイベント終了
void GameScene::ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent)
{
  // タップポイント取得
  CCPoint touchPoint = m_background->convertTouchToNodeSpace(pTouch);
  
  // タップしたコマのTagとコマの種類を取得
  int tag = 0;
  kBlock blockType;
  getTouchBlockTag(touchPoint, tag, blockType);
  
  if (tag != 0){
    // 隣接するコマを検索
    list<int> sameColorBlockTags = getSameColorBlockTags(tag, blockType);
    
    if (sameColorBlockTags.size() > 1)
    {
      // 隣接するコマを削除
      removeBlock(sameColorBlockTags, blockType);
    }
  }
}

// 初期化
bool GameScene::init()
{
  if (!CCLayer::init())
  {
    return false;
  }
  
  // get touch Event
  setTouchEnabled(true);
  setTouchMode(kCCTouchesOneByOne);
  
  // 変数初期化
  initForVariables();
  
  // 背景表示
  showBackground();
  
  // コマ表示
  showBlock();
  
  return true;
}