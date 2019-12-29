#pragma once

#include "MouseEventListener.h"

class EventListener
{
public:
	EventListener() = delete;
	~EventListener();

	EventListener(const EventListener&) = delete;
	EventListener(EventListener&&) = delete;
	EventListener& operator=(const EventListener&) = delete;
	EventListener& operator=(EventListener&&) = delete;

	static void Update();
};

