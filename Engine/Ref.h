#pragma once
class Ref
{
public:
	int count;
	Ref();
	virtual ~Ref();
	void retain();
	void release();
	void autorelease();
private:
	
};
