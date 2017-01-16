#include "stdafx.h"
#include "FaceEngineBuilder.h"

FaceEngineBuilder::FaceEngineBuilder()
{
}


FaceEngineBuilder::~FaceEngineBuilder()
{
}
FaceEngine& FaceEngineBuilder::getEngine(TYPE _t)
{
	static SDSFaceEngine engine;
	if (_t == TYPE::SDS)
	{
		return engine;
	}
	else if (_t == TYPE::NEURO)
	{

	}
	return engine;
}