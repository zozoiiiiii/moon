/************************************************************************/
/* 
@author:    junliang
@brief:     
@time:      2017-11-24
*/
/************************************************************************/
#pragma once

#include "mn_render/inc/i_batch.h"
#include "../platform.h"
#include "mn_render/inc/i_render_context.h"
#include <map>
#include <vector>

class BatchGroup : public IBatchGroup
{
    MN_BEGIN(BatchGroup, IBatchGroup);
    MN_END
public:
    virtual void OnCreate();
    virtual void OnDestroy();
    virtual void RenderAllBatch(IRender* pRender);
    virtual void ClearAllBatch();
    virtual RenderContext* GetRenderContext();

    void AddNormalBatch(RenderComponent* pBatch);
    void AddTopmostBatch(RenderComponent* pBatch);
	void AddGUIBatch(RenderComponent* pBatch);
private:
    void DrawSolidBatchs(IRender* pRender, RenderContext* pCxt);
    void DrawTopmostBatchs(IRender* pRender, RenderContext* pCxt);
	void DrawGUIBatches(IRender* pRender, RenderContext* pCxt);
private:
    RenderContext* m_pRenderContext;
    std::vector<RenderComponent*> m_SolidBatchs;
    std::vector<RenderComponent*> m_TopmostBatchs;
	std::vector<RenderComponent*> m_GUIBatches;
};
