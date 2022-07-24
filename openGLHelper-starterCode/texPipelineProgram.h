#include "pipelineProgram.h"

class TexPipelineProgram : public PipelineProgram
{
public:
	int Init(const char* shaderBasePath);
	void SetModelViewMatrix(const float* m);
	void SetProjectionMatrix(const float* m);

protected:
	virtual int SetShaderVariableHandles();

	GLint h_projectionMatrix;
	GLint h_modelViewMatrix;
};