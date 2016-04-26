

#include "StarLayer.h"
#include "VisibleRect.h"
#include "star/SimpleStar.h"
#include "star/StarComNode.h"
#include "util/LogUtil.h"

StarLayer::StarLayer()
{
}

StarLayer::~StarLayer()
{

}

bool StarLayer::init()
{
	if (!BaseLayer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	char output[255];
	sprintf_s(output, "width=%.0f, height=%.0f", visibleSize.width, visibleSize.height);
	LogUtil::d(output);

	StarComNode *node = StarComNode::create();
	Sprite* spr = node->getSprite();
	float sprWidth = spr->getContentSize().width;

	float cow = 10;
	float width = visibleSize.width / cow;
	float scale = width / sprWidth;
	float x = 0;
	float y = 0;
	float beginY = 100;
	for (int i = 0; i < cow; i++)
	{
		x = i * width + width / 2;
		for (int j = 0; j < cow; j++)
		{
			y = j * width + width / 2 + beginY;

			StarComNode* starNode = addNodeAtPos(Vec2(x, y), scale);
			Sprite* spr = starNode->getSprite();
			//spr->retain();
			// 为什么在这索引不到sprite????
			//_stars[i][j] = starNode;
			_starSprs[i][j] = spr;
			//_starsList[i*COW+j*COW] = starNode;
			sprintf_s(output, "x=%.0f, y=%.0f, scale=%.2f, i=%d,j=%d", x, y, scale, i, j);
			LogUtil::d(output);
		}
	}

	// 添加点击
	auto listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesEnded = CC_CALLBACK_2(StarLayer::onTouchesEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

StarComNode* StarLayer::addNodeAtPos(Vec2 pos, float scale)
{
	StarComNode *node = StarComNode::create();
	Sprite *sprite = node->getSprite();
	sprite->setPosition(pos);
	// 为什么不要设置大小
	sprite->setScale(scale);
	addChild(sprite);

	return node;
}

void StarLayer::onTouchesEnded(const std::vector<Touch*>& touches, Event* event)
{
	LogUtil::d("-------------------------------------------------");
	bool find = false;

	for (auto &touch : touches)
	{
		Vec2 location = touch->getLocation();
		char ch[255];
		sprintf_s(ch, "click x=%.2f, y=%.2f", location.x, location.y);
		LogUtil::d(ch);

		for (int i = 0; i < COW; i++)
		{
			for (int j = 0;j < COW;j++)
			{
				/*sprintf_s(ch, "line=%d, cow=%d", i, j);
				LogUtil::d(ch);*/

				//StarComNode* starNode = _stars[i][j];
				Sprite* sprite = _starSprs[i][j];
				if (sprite)
				{
					bool isClick = sprite->getBoundingBox().containsPoint(location);
					if (isClick)
					{
						sprintf_s(ch, "click --> line=%d, cow=%d", i, j);
						LogUtil::d(ch);
						find = true;
						break;
					}
				}

				if (find)
				{
					break;
				}
			}

			if (find)
			{
				break;
			}
		}
		
		if (find)
		{
			break;
		}
	}
}