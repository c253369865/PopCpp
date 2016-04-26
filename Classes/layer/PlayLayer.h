
#pragma once
#include "base\BaseLayer.h"
class PlayLayer : public BaseLayer
{
public:
	PlayLayer();
	virtual ~PlayLayer();

	virtual bool init();

	void menuCloseCallback(Ref* pSender);

	CREATE_FUNC(PlayLayer);
};