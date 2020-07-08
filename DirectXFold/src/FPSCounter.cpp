#include "pch.h"
#include "FPSCounter.h"

FPSCounter::FPSCounter()
{
	m_fps = 0;
	m_count = 0;
	m_startTime = timeGetTime();
}

void FPSCounter::Update()
{
	m_count++;
	DWORD endTime;
	if ((endTime = timeGetTime()) >= (m_startTime + 1000))
	{
		m_frameTime = (double)(endTime - m_startTime) / m_count;
		m_fps = m_count;
		m_count = 0;

		m_startTime = timeGetTime();
	}
}

unsigned int FPSCounter::GetFPS()
{
	return m_fps;
}

double FPSCounter::GetFrameTime()
{
	return m_frameTime;
}
