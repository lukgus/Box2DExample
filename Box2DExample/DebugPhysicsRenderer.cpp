#include "DebugPhysicsRenderer.h"

#include <GL/freeglut.h>

DebugPhysicsRenderer::DebugPhysicsRenderer()
{

}

DebugPhysicsRenderer::~DebugPhysicsRenderer()
{

}

void DebugPhysicsRenderer::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
}

void DebugPhysicsRenderer::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)				 
{
}

void DebugPhysicsRenderer::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)							 
{

}

void DebugPhysicsRenderer::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)	 
{
}

void DebugPhysicsRenderer::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)							 
{
}

void DebugPhysicsRenderer::DrawTransform(const b2Transform& xf)																 
{
}

void DebugPhysicsRenderer::DrawPoint(const b2Vec2& p, float32 size, const b2Color& color)									 
{
}
