#include "render.h"

void Render::ForwardRendering()
{
    int nSize = m_groups.size();
    for(int i=0; i<nSize; i++)
    {
        IBatchGroup* pGroup = m_groups[i];

        // geometry pass
        ForwardRenderPass(pGroup);

        // post pass

		pGroup->ClearAllBatch();
    }

	// gui render on the default fbo:0
	//RenderContext* pRenderContext = m_pUIBatchGroup->GetRenderContext();

	// RenderSceneToTexture
	//pRenderContext->pFBO->BindForWriting();

	if(NULL == m_pQuad)
        return;

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	m_pUIBatchGroup->RenderAllBatch(this);
	m_pUIBatchGroup->ClearAllBatch();

}

void Render::ForwardRenderPass(IBatchGroup* pGroup)
{
    RenderContext* pRenderContext = pGroup->GetRenderContext();

    // RenderSceneToTexture
    pRenderContext->pFBO->BindForWriting();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    pGroup->RenderAllBatch(this);

    // post process pass
    // 	m_offScreenBuffer->BindForWriting();
    // 	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // 
    // 	ColorTexture* pColorTexture = m_offScreenBuffer->GetColorTexture();
    // 	glActiveTexture(GL_TEXTURE0);
    // 	glBindTexture(GL_TEXTURE_2D, pColorTexture->GetTextureID());

    // 1, 高亮提取
    // 2, 高斯模糊
    // 3, 和正常渲染的纹理叠加就达到bloom
    //pickBright();


    RenderTexture(pRenderContext->pRenderTexture);
}