

#include "StarComNode.h"
#include "util/LogUtil.h"

#define random(x) (rand()%x)

StarComNode::StarComNode()
{

}

StarComNode::~StarComNode()
{
	//_showSprite->release();
}

bool StarComNode::init()
{
	if (!Node::init())
	{
		return false;
	}

	char fileName[255];
	sprintf_s(fileName, "star/star_%d.png", random(5) + 1);
	//LogUtil::d(fileName);

	_showSprite = Sprite::create(fileName);
	//_showSprite->retain();

	return true;
}