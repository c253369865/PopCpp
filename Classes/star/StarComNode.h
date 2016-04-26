


#ifndef _STAR_COM_NODE_H
#define _STAR_COM_NODE_H

#include "cocos2d.h"

USING_NS_CC;

class StarComNode : public Node
{
public:
	StarComNode();
	virtual ~StarComNode();

	virtual bool init();

	CREATE_FUNC(StarComNode);
	
	Sprite* getSprite() { return _showSprite; };

private:
	Sprite* _showSprite;
};

#endif // _STAR_COM_NODE_H