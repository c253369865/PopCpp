
#include "StarLayer.h"
#include "VisibleRect.h"
#include "star/StarComNode.h"
#include "util/LogUtil.h"

StarLayer::StarLayer()
{
}

StarLayer::~StarLayer()
{
	LogUtil::d("StarLayer::~StarLayer()");

	for (int i = 0; i < COW; i++)
	{
		for (int j = 0; j < COW; j++)
		{
			StarComNode* starNode = _stars[i][j];
			if (starNode)
			{
				delete starNode;
				starNode = nullptr;
			}
			_stars[i][j] = nullptr;
		}
	}

	_needCheckStarVector.clear();
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

	StarComNode *node = new StarComNode();
	Sprite* spr = node->getSprite();
	float sprWidth = spr->getContentSize().width;


	float width = visibleSize.width / COW;
	float scale = width / sprWidth;
	float x = 0;
	float y = 0;
	float beginY = 100;
	
	// 一行一行的初始化
	// 从左往右, 从下往上
	for (int j = 0; j < COW; j++)
	{
		y = j * width + width / 2 + beginY;
		for (int i = 0;i < COW;i++)
		{
			x = i * width + width / 2;

			StarComNode* starNode = addNodeAtPos(Vec2(x, y), scale);
			starNode->clickPos = ClickPos(i, j);

			// 为什么在这索引不到sprite????
			// 是由于 create方法的autorelease()方法释放了对象引起的
			_stars[i][j] = starNode;
			sprintf_s(output, "x=%.0f, y=%.0f, scale=%.2f, i=%d,j=%d, typeIdx=%d", x, y, scale, i, j, starNode->type_idx);
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
	//StarComNode *node = StarComNode::create();
	StarComNode *node = new StarComNode();
	Sprite *sprite = node->getSprite();
	sprite->setPosition(pos);
	// 为什么不要设置大小?
	// 不是不要,是设置错了,大小是45,不是72
	sprite->setScale(scale);
	addChild(sprite);

	return node;
}

void StarLayer::onTouchesEnded(const std::vector<Touch*>& touches, Event* event)
{
	// 在动画完成后设置,暂时放在这里
	// todo 对象列表初始化????
	// 访问错误是由于 create方法的autorelease()方法释放了对象引起的
	resetStarStatus();

	LogUtil::d("-------------------------------------------------");
	bool find = false;

	for (auto &touch : touches)
	{
		Vec2 location = touch->getLocation();
		char ch[255];
		sprintf_s(ch, "click x=%.2f, y=%.2f", location.x, location.y);
		LogUtil::d(ch);

		for (int j = 0; j < COW; j++)
		{
			for (int i = 0; i < COW; i++)
			{
				StarComNode* starNode = _stars[i][j];

				Sprite* sprite = starNode->getSprite();
				if (sprite)
				{
					bool isClick = sprite->getBoundingBox().containsPoint(location);
					if (isClick)
					{
						sprintf_s(ch, "click --> line=%d, cow=%d", i, j);
						LogUtil::d(ch);

						starNode->is_slected = true;
						starNode->is_check = true;
						_needCheckStarVector.clear();
						_needCheckStarVector.push_back(starNode);
						checkAllStarSelected();

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

void StarLayer::resetStarStatus()
{
	for (int j = 0; j < COW; j++)
	{
		for (int i = 0; i < COW; i++)
		{
			StarComNode* starNode = _stars[i][j];
			// 先把标记还原
			if (starNode)
			{
				starNode->is_slected = false;
				starNode->is_check = false;
			}
		}
	}
}

void StarLayer::checkAllStarSelected()
{
	StarComNode* starNode = nullptr;
	do 
	{
		starNode = _needCheckStarVector.at(0);
		// 搜索 左上右下
		if (starNode)
		{
			int idx1 = starNode->type_idx;
			ClickPos clickPos = starNode->clickPos;
			// 左
			if (clickPos.x > 0)
			{
				StarComNode* leftStar = _stars[clickPos.x - 1][clickPos.y];
				setOneStar(starNode, leftStar);
			}

			// 上
			if (clickPos.y < COW - 1)
			{
				StarComNode* upStar = _stars[clickPos.x][clickPos.y+1];
				setOneStar(starNode, upStar);
			}

			// 右
			if (clickPos.x < COW - 1)
			{
				StarComNode* rightStar = _stars[clickPos.x + 1][clickPos.y];
				setOneStar(starNode, rightStar);
			}

			// 下
			if (clickPos.y > 0)
			{
				StarComNode* downStar = _stars[clickPos.x][clickPos.y - 1];
				setOneStar(starNode, downStar);
			}
		}

		if (_needCheckStarVector.size() > 0)
		{
			std::vector<StarComNode*>::iterator it = _needCheckStarVector.begin();
			_needCheckStarVector.erase(it);
		}

	} while (_needCheckStarVector.size() > 0);

	// 遍历输出所有对象
	// 从上到下,从左到右
	char ch[1024];
	for (int j = COW - 1; j >= 0; j--)
	{
		sprintf_s(ch, "");

		for (int i = 0; i < COW; i++)
		{
			StarComNode* starNode = _stars[i][j];
			if (starNode)
			{
				char ch1[255];
				sprintf_s(ch1, "%d ", starNode->is_slected);
				strcat_s(ch, ch1);
			}
		}

		LogUtil::d(ch);
	}
}

// star1 : 被对比的
void StarLayer::setOneStar(StarComNode* star1, StarComNode* star2)
{
	
	if (star1 && star2)
	{	
		if (!star2->is_check) {
			if (star1->type_idx == star2->type_idx)
			{
				// 找到并相同,设置标记,添加到查找队列中
				star2->is_slected = true;
				_needCheckStarVector.push_back(star2);
				
				char ch[255];
				sprintf_s(ch, " same -> x=%d,y=%d ", star2->clickPos.x, star2->clickPos.y);
				LogUtil::d(ch);
			}
		}
	}

	if (star2)
	{
		star2->is_check = true;
	}
	
}