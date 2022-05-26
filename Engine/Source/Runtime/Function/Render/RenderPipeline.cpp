#include "RenderPipeline.h"


NAMESPACE_BEGIN(Engine)
CullMode RenderPipeline::cullMode				= CullMode::Back;
FillMode RenderPipeline::fillMode				= FillMode::Solid;
DepthTestMode RenderPipeline::depthTestMode		= DepthTestMode::Less;
DepthWriteMode RenderPipeline::depthWriteMode	= DepthWriteMode::Enable;
BlendMode RenderPipeline::blendMode				= BlendMode::Disable;

Bool RenderPipeline::backface	= false;
Bool RenderPipeline::discarded	= false;

RenderPipeline::VertexShader RenderPipeline::VS	= nullptr;
RenderPipeline::PixelShader RenderPipeline::PS	= nullptr;
NAMESPACE_END(Engine)