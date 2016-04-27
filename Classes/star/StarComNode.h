


#ifndef _STAR_COM_NODE_H
#define _STAR_COM_NODE_H

#include "cocos2d.h"

USING_NS_CC;

enum class StarType {
	
	
};

typedef struct _clickPos
{
	int x;
	int y;

	_clickPos(int i, int j)
	{
		this->x = i;
		this->y = j;
	}
}ClickPos;

class StarComNode
{
public:
	StarComNode();
	virtual ~StarComNode();

	virtual bool init();

	//CREATE_FUNC(StarComNode);
	
	Sprite* getSprite() { return _showSprite; };

	// 是否被选中
	bool is_slected;
	// 是否已经遍历过
	bool is_check;
	// 类型索引
	int type_idx;
	// 在界面的位置
	Vec2 location;
	ClickPos clickPos;
private:
	Sprite* _showSprite;
};

#endif // _STAR_COM_NODE_H