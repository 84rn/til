#pragma once
#include <queue>
#include <vector>
#include "SDL/SDL.h"

template<typename T>
class CThreadQueue {
public:
	CThreadQueue();
	~CThreadQueue();

	void push(T);
	T pop();
	void push(std::vector<T>);
	bool empty();

private:
	void start();
	void stop();

	SDL_mutex* mutex;
	std::queue<T> _queue;
};

