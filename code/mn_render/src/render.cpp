#include "render.h"

#define GL_GLEXT_PROTOTYPES
#include <GLES2/gl2.h>
#include <EGL/egl.h>

#include "model/mesh.h"
#include "model/anim.h"
#include "model/model_res.h"


void Render::OnCreate()
{
    m_pQuad = NULL;
    m_pResMgr = (IResMgr*)GetObjectMgr()->create("ResMgr");
    m_pResMgr->SetRender(this);
    ModelRes::Instance()->SetRender(this);

	// painter will render after all other batch groups
	m_pUIBatchGroup = (IBatchGroup*)GetObjectMgr()->create("BatchGroup");

    // this quad used for show the offscreen rt
	SetupQuad();
	GetObjectMgr()->addExcute(this);
}

void Render::OnDestroy()
{
	GetObjectMgr()->removeExcute(this);
}


void Render::OnExcute(float sec)
{
	EventMgr* pEventMgr = GetObjectMgr()->getEventMgr();
	pEventMgr->Invoke(GetID(), "AddBatch_VisObjs");	// 3d visible object
	pEventMgr->Invoke(GetID(), "AddBatch_Items");	// 2d ui item
	RenderAll();
}

IResMgr* Render::GetResMgr()
{
    return m_pResMgr;
}

void Render::SetupQuad()
{
    if(NULL!= m_pQuad)
        return;

    IModelRes* pModelRes = GetModelResMgr();
    m_pQuad = pModelRes->CreateMesh();

    MN::Vertex vertices[4] = {
        MN::Vertex(-1.0,-1.0,0.0,    0.0,0.0),
        MN::Vertex(1.0,-1.0,0.0,     1.0,0.0),
        MN::Vertex(1.0,1.0,0.0,      1.0,1.0),
        MN::Vertex(-1.0,1.0,0.0,     0.0,1.0)
    };


    MN::SubMesh sm;
    for(int i=0; i<4; i++)
    {
        const MN::Vertex& v = vertices[i];
        sm.vertices.push_back(v);
    }

    unsigned short indices[] = {0,1,2,0,2,3};

    for(int i=0; i<6; i++)
    {
        unsigned short index = indices[i];
        sm.indices.push_back(index);
    }

    m_pQuad->AddSubMesh(sm);
}

IModelRes* Render::GetModelResMgr()
{
    return ModelRes::Instance();
}

void Render::CreateDevice()
{
    // create
    glViewport(0,0,m_nDeviceWidth, m_nDeviceHeight);
}

void Render::ResetDevice()
{
    // clear

    // create
    glViewport(0,0,m_nDeviceWidth, m_nDeviceHeight);

    // ���´�������Ⱦ�ߴ�һ�µ�����
    m_pResMgr->Reset();




	// https://stackoverflow.com/questions/25416820/set-origin-to-top-left-corner-of-screen-in-opengl-es-2
	m_topLeftMatrix.Ident();
	m_topLeftMatrix.m_data[0] = 2.0f / m_nDeviceWidth;
	m_topLeftMatrix.m_data[5] = -2.0f / m_nDeviceHeight;
	m_topLeftMatrix.m_data[12] = -1;
	m_topLeftMatrix.m_data[13] = 1;
}


Mat4f Render::GetTopLeftMatrix()
{
	return m_topLeftMatrix;
}

void Render::AddGroup(IBatchGroup* pBatchGroup)
{
    m_groups.push_back(pBatchGroup);
}

void Render::RenderAll()
{
    // render all groups and clear every frame. some times the group will not add.
    ForwardRendering();

//     switch(m_nRenderType)
//     {
//     case FORWARD_SHADING:
//         ForwardRendering();
//         break;
//     case DEFERRED_SHADING:
//         throw_assert(false, "not support now");
//         //DeferredRendering();
//         break;
//     }

    m_groups.clear();
}

void Render::RenderTexture(IRenderTexture* pRes)
{
    if(NULL==m_pQuad)
        return;

    glBindFramebuffer(GL_FRAMEBUFFER,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, pRes->GetID());

    static IShader* pMeshShader = NULL;
    if(!pMeshShader)
    {
        std::string res_path = GetResPath();
        std::string vsh = res_path + "shader/quad.vsh";
        std::string fsh = res_path + "shader/quad.fsh";
        pMeshShader = GetResMgr()->LoadShader(vsh.c_str(), fsh.c_str());
    }

    IShader* pShader = pMeshShader;
    pShader->Begin();
    pShader->SetUniform1i("ColorTexture", 0);
    m_pQuad->draw(pShader);
    pShader->End();
}





//��rgba��ʽ
inline void trans_rgba(unsigned char* bits, int width, int height)
{
    int size = width*height;

    for(int i = 0; i < size; i++)
    {
        char tmp = bits[0];
        bits[0] = bits[2];
        bits[2] = tmp;
        bits += 4;
    }
}

inline void trans_rgb(unsigned char* bits, int width, int height)
{
    int size = width*height;

    for(int i = 0; i < size; i++)
    {
        char tmp = bits[0];
        bits[0] = bits[2];
        bits[2] = tmp;
        bits += 3;
    }
}


// gl es �����⺯��
inline bool TestErr(const char* ident)
{
    int err = glGetError();	
    if(err == GL_NO_ERROR)
        return true;

    //GL_INVALID_ENUM:
    //GL_INVALID_VALUE:
    //GL_INVALID_OPERATION:
    //GL_OUT_OF_MEMORY:
    return false;
}

void Render::ScreenShot(const char* name, int x, int y, int w, int h)
{
    //glBindFramebuffer(GL_FRAMEBUFFER,0);      // slow
    //m_offScreenBuffer->BindForWriting();        // fast?
// 
//     assert(name != NULL);
//     const char* dot = strrchr(name, '.');
//     throw_assert(NULL!=dot, "file check"<<name);
// 
//     FREE_IMAGE_FORMAT format;
//     if (stricmp(dot, ".bmp") == 0)
//     {
//         format = FIF_BMP;
//     }
//     else if (stricmp(dot, ".jpg") == 0)
//     {
//         format = FIF_JPEG;
//     }
//     else if (stricmp(dot, ".png") == 0)
//     {
//         format = FIF_PNG;
//     }
//     else if (stricmp(dot, ".dds") == 0)
//     {
//         format = FIF_DDS;
//     }
//     else
//     {
//         throw_assert(false, "file not support.");
//     }
// 
//     FIBITMAP * bitmap = ::FreeImage_Allocate(w, h, 32);
//     unsigned char* bits = FreeImage_GetBits(bitmap);
// 
// 
//     /* egl ������ûע�͵Ļ���imp_fmtΪ0x1907, ��GL_RBG,glReadPixels��ȡ�������ݡ�
//     ע���Ժ�Ϳ��ԣ�why?
//     //EGL_RED_SIZE,       8,    // ָ��rgb�е�r��С
//     //EGL_GREEN_SIZE,     8,    // ָ��rgb�е�g��С
//     //EGL_BLUE_SIZE,      8,    // ָ��rgb�е�b��С
//     //EGL_ALPHA_SIZE,     8,    // alhpa
//     */
//     int imp_fmt, imp_type;  
//     glGetIntegerv(GL_IMPLEMENTATION_COLOR_READ_FORMAT, &imp_fmt);  
//     glGetIntegerv(GL_IMPLEMENTATION_COLOR_READ_TYPE, &imp_type);
// 
// 
//     //BYTE* pixels = new BYTE[4 * w * h];
//     //memset(pixels, 0, sizeof(BYTE)*w*h*4);
// 
//     // http://www.zwqxin.com/archives/opengl/opengl-api-memorandum-2.html
//     // ����cpu�ڴ������ظ�ʽ����ֹ�������ݲ���4�ı���
//     glPixelStorei(GL_PACK_ALIGNMENT, 1);
// 
//     // ��gpu��ȡ���ص�cpu�ڴ���, opengl es do not support glReadBuffer, glReadPixels automatically read the currently
//     // active framebuffer.
//     ::glReadPixels(x, y, w, h, GL_RGBA, GL_UNSIGNED_BYTE, bits);
// 
//     bool result = TestErr("SaveScreenToFile");
//     if(format == FIF_JPEG)
//     {
//         FIBITMAP *old_dib = bitmap;
//         bitmap = FreeImage_ConvertTo24Bits(bitmap);
//         FreeImage_Unload(old_dib);
//         bits = FreeImage_GetBits(bitmap);
//         trans_rgb(bits, w, h);
//     }
//     else
//     {	
//         trans_rgba(bits, w, h);
//     }
// 
//     // use frameimage, must do FreeImage_DeInitialise(); or failed here.
//     result = FreeImage_Save(format, bitmap, name);
//     if(result)
//     {
//         result=true;
//     }
//     //throw_assert(FreeImage_Save(format, bitmap, name), "SaveScreenToFile error"<<name);
//     FreeImage_Unload(bitmap);
}