#pragma once
#ifndef __TARGET__
#define __TARGET__

#include "DisplayObject.h"

class Target final : public DisplayObject {
public:
	Target();
	~Target();

	// Inherited via GameObject
	virtual void draw() override;
	virtual void update(float deltaTime) override;
	virtual void clean() override;

private:
	void m_move(float deltaTime);
	void m_checkBounds();
	void m_reset();
};


#endif /* defined (__TARGET__) */