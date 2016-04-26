
#pragma once
#include "base\BaseLayer.h"
#include "star\StarComNode.h"

#define COW 10

class StarLayer : public BaseLayer
{
public:
	StarLayer();
	virtual ~StarLayer();

	virtual bool init();

	StarComNode* addNodeAtPos(Vec2 pos, float scale);

	void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);

	CREATE_FUNC(StarLayer);

protected:
	StarComNode* _stars[COW][COW];
	Sprite* _starSprs[COW][COW];
	StarComNode* _starsList[COW*COW];
	std::vector<std::vector<StarComNode*>> _starsVector;
};