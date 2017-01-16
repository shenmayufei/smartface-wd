#pragma once

#include <mutex>
#include <queue>

#define IMG_WIDTH 640
#define IMG_HEIGHT 480

template<class T> class Buffer
{
public:
	Buffer(int size);
	~Buffer();

	void add(const T& data, bool dropIfull = false);
	T get();
	int size();
	int maxSize();
	bool isFull();
	bool isEmpty();
	bool clear();

private:
	std::mutex queueProtect;

	std::queue<T> mData;
	int mSize;
};
#include "stdafx.h"
#include "Buffer.h"


template<class T> Buffer<T>::Buffer(int size)
{
	mSize = size;


}


template<class T> Buffer<T>::~Buffer()
{
}

template<class T> void Buffer<T>::add(const T& data, bool dropIfull = false)
{
	queueProtect.lock();
	mData.push(data);
	queueProtect.unlock();
}
template<class T> T Buffer<T>::get()
{
	T data;
	queueProtect.lock();

	data = cv::Mat::zeros(IMG_HEIGHT, IMG_WIDTH, CV_8UC3);
	if (!mData.empty())
	{
		data = mData.front();
		//mData.pop();
	}
	queueProtect.unlock();
	return data;
}
template<class T> int Buffer<T>::size()
{
	return mSize;
}
template<class T> int Buffer<T>::maxSize()
{
	return 1000;
}
template<class T> bool Buffer<T>::isFull()
{
	return false;
}
template<class T> bool Buffer<T>::isEmpty()
{
	return false;
}
template<class T> bool Buffer<T>::clear()
{

	return false;
}

