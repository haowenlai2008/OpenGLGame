#include "RP_IBLPreRenderPass.h"
#include "RenderManager.h"
#include "BaseManager.h"

bool RP_IBLPreRenderPass::Init()
{
    //glGenTextures(1, &RenderManager::globleTexture.environmentMapIBL);
    //glBindTexture(GL_TEXTURE_CUBE_MAP, RenderManager::globleTexture.environmentMapIBL);
    //for (unsigned int i = 0; i < 6; ++i)
    //{
    //    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, 512, 512, 0, GL_RGB, GL_FLOAT, nullptr);
    //}
    //glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    //glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    //glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    //glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); // enable pre-filter mipmap sampling (combatting visible dots artifact)
    //glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //// pbr: set up projection and view matrices for capturing data onto the 6 cubemap face directions
    //// ----------------------------------------------------------------------------------------------
    //glm::mat4 captureProjection = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 10.0f);
    //glm::mat4 captureViews[] =
    //{
    //    glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
    //    glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
    //    glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  1.0f,  0.0f), glm::vec3(0.0f,  0.0f,  1.0f)),
    //    glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f,  0.0f), glm::vec3(0.0f,  0.0f, -1.0f)),
    //    glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  0.0f,  1.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
    //    glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  0.0f, -1.0f), glm::vec3(0.0f, -1.0f,  0.0f))
    //};

    //// pbr: convert HDR equirectangular environment map to cubemap equivalent
    //// ----------------------------------------------------------------------
    //equirectangularToCubemapShader.use();
    //equirectangularToCubemapShader.setInt("equirectangularMap", 0);
    //equirectangularToCubemapShader.setMat4("projection", captureProjection);
    //glActiveTexture(GL_TEXTURE0);
    //glBindTexture(GL_TEXTURE_2D, hdrTexture);

    //glViewport(0, 0, 512, 512); // don't forget to configure the viewport to the capture dimensions.
    //glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
    //for (unsigned int i = 0; i < 6; ++i)
    //{
    //    equirectangularToCubemapShader.setMat4("view", captureViews[i]);
    //    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, RenderManager::globleTexture.environmentMapIBL, 0);
    //    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //    renderCube();
    //}
    //glBindFramebuffer(GL_FRAMEBUFFER, 0);

    //// then let OpenGL generate mipmaps from first mip face (combatting visible dots artifact)
    //glBindTexture(GL_TEXTURE_CUBE_MAP, RenderManager::globleTexture.environmentMapIBL);
    //glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

    //// pbr: create an irradiance cubemap, and re-scale capture FBO to irradiance scale.
    //// --------------------------------------------------------------------------------
    //unsigned int irradianceMap;
    //glGenTextures(1, &irradianceMap);
    //glBindTexture(GL_TEXTURE_CUBE_MAP, irradianceMap);
    //for (unsigned int i = 0; i < 6; ++i)
    //{
    //    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, 32, 32, 0, GL_RGB, GL_FLOAT, nullptr);
    //}
    //glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    //glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    //glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    //glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
    //glBindRenderbuffer(GL_RENDERBUFFER, captureRBO);
    //glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 32, 32);

    //// pbr: solve diffuse integral by convolution to create an irradiance (cube)map.
    //// -----------------------------------------------------------------------------
    //irradianceShader.use();
    //irradianceShader.setInt("environmentMap", 0);
    //irradianceShader.setMat4("projection", captureProjection);
    //glActiveTexture(GL_TEXTURE0);
    //glBindTexture(GL_TEXTURE_CUBE_MAP, RenderManager::globleTexture.environmentMapIBL);

    //glViewport(0, 0, 32, 32); // don't forget to configure the viewport to the capture dimensions.
    //glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
    //for (unsigned int i = 0; i < 6; ++i)
    //{
    //    irradianceShader.setMat4("view", captureViews[i]);
    //    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, irradianceMap, 0);
    //    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //    renderCube();
    //}
    //glBindFramebuffer(GL_FRAMEBUFFER, 0);
    return true;
}

bool RP_IBLPreRenderPass::Render()
{
    return true;
}
