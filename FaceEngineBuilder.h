#pragma once
#include "FaceEngine.h"
#include "SDSFaceEngine.h"

class FaceEngineBuilder
{
public:
	FaceEngineBuilder();
	~FaceEngineBuilder();
	enum TYPE
	{
		SDS, NEURO
	};
	static FaceEngine& getEngine(TYPE _t);

};

