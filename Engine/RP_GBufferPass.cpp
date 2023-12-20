#include "RP_GBufferPass.h"
#include "RenderManager.h"
#include "BaseManager.h"
#include "Shader.h"
#include "MaterialManager.h"
#include "Entity.h"

bool RP_GBufferPass::Init()
{
    auto bmp = BaseManager::getInstance();
    glGenFramebuffers(1, &RenderManager::globalBuffer.gBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, RenderManager::globalBuffer.gBuffer);

    // - 位置颜色缓冲
    glGenTextures(1, &RenderManager::globleTexture.gBuffer_Position);
    glBindTexture(GL_TEXTURE_2D, RenderManager::globleTexture.gBuffer_Position);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, bmp->screenWidth, bmp->screenHeight, 0, GL_RGB, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, RenderManager::globleTexture.gBuffer_Position, 0);

    // - 法线颜色缓冲
    glGenTextures(1, &RenderManager::globleTexture.gBuffer_Normal);
    glBindTexture(GL_TEXTURE_2D, RenderManager::globleTexture.gBuffer_Normal);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, bmp->screenWidth, bmp->screenHeight, 0, GL_RGB, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, RenderManager::globleTexture.gBuffer_Normal, 0);

    // - 金属度-粗糙度
    glGenTextures(1, &RenderManager::globleTexture.gBuffer_MetallicRoughness);
    glBindTexture(GL_TEXTURE_2D, RenderManager::globleTexture.gBuffer_MetallicRoughness);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bmp->screenWidth, bmp->screenHeight, 0, GL_RGB,  GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, RenderManager::globleTexture.gBuffer_MetallicRoughness, 0);

    // - 反照率Albedo
    glGenTextures(1, &RenderManager::globleTexture.gBuffer_Albedo);
    glBindTexture(GL_TEXTURE_2D, RenderManager::globleTexture.gBuffer_Albedo);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bmp->screenWidth, bmp->screenHeight, 0, GL_RGBA, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT3, GL_TEXTURE_2D, RenderManager::globleTexture.gBuffer_Albedo, 0);

    // - 光源空间坐标
    glGenTextures(1, &RenderManager::globleTexture.gBuffer_PosLightSpace);
    glBindTexture(GL_TEXTURE_2D, RenderManager::globleTexture.gBuffer_PosLightSpace);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, bmp->screenWidth, bmp->screenHeight, 0, GL_RGBA, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT4, GL_TEXTURE_2D, RenderManager::globleTexture.gBuffer_PosLightSpace, 0);

    GLuint attachments[5] = {
        GL_COLOR_ATTACHMENT0,
        GL_COLOR_ATTACHMENT1,
        GL_COLOR_ATTACHMENT2,
        GL_COLOR_ATTACHMENT3,
        GL_COLOR_ATTACHMENT4
    };
    glDrawBuffers(5, attachments);

    GLuint rboDepth;
    glGenRenderbuffers(1, &rboDepth);
    glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, bmp->screenWidth, bmp->screenHeight);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);

    // - Finally check if framebuffer is complete
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "Framebuffer not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    return true;
}

bool RP_GBufferPass::Render()
{
    glBindFramebuffer(GL_FRAMEBUFFER, RenderManager::globalBuffer.gBuffer);
    glDepthFunc(GL_LESS);
    glCullFace(GL_BACK);

    vec4 clearColor = BaseManager::getInstance()->clearColor;
    glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //glBindFramebuffer(GL_FRAMEBUFFER, 0);
    BaseManager* baseManager = BaseManager::getInstance();
    MaterialManager* matManager = MaterialManager::getInstance();
    glm::mat4 projection = baseManager->getProjMat4();
    glm::mat4 view = baseManager->getViewMat4();
    glm::mat4 lightSpace = baseManager->getLightSpaceMat4();
    glm::vec3 viewPos = baseManager->getViewPos();
    glm::vec3 lightPos = baseManager->getLightPos();

    // 需要用一个gbuffer材质
    auto gbufferMaterial = matManager->getUserMaterialRef("Deferred_GBuffer");
    auto gbufferShader = gbufferMaterial.m_Shader.lock();
    
    // 渲染场景内物体，天空盒不走GBuffer
    for (auto p : RenderManager::getInstance()->drawObjects)
    {
        if (p != nullptr && p->count != 0)
        {
            auto ent_ptr = dynamic_cast<Entity*>(p);
            auto& material = *ent_ptr->GetMaterial().lock();
            
            // 设置临时材质的参数，albedo，metallic, roughness
            auto albedoOpt = material.getTexture("material.diffuse");
            if (albedoOpt.has_value())
            {
                gbufferMaterial.setTexture("material.diffuse", albedoOpt.value(), 0);
            }
            auto metallicOpt = material.getFloat("material.metallic");
            if (metallicOpt.has_value())
            {
                gbufferMaterial.setFloat("material.metallic", metallicOpt.value());
            }
            auto roughnessOpt = material.getFloat("material.roughness");
            if (roughnessOpt.has_value())
            {
                gbufferMaterial.setFloat("material.roughness", roughnessOpt.value());
            }

            glm::mat4 model = p->getModelMatrix();
            gbufferShader->use();
            gbufferMaterial.bindUniform();
            gbufferShader->setMat4("projection", projection);
            gbufferShader->setMat4("view", view);
            gbufferShader->setMat4("model", model);
            gbufferShader->setMat4("lightSpaceMatrix", lightSpace);
            p->draw();
        }
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    return true;
}

RP_GBufferPass::~RP_GBufferPass()
{
}
