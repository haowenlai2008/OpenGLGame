#include "RP_SSAOPass.h"
#include "RenderManager.h"
#include "BaseManager.h"
#include "Material.h"
#include "Entity.h"
#include "MaterialManager.h"
#include "VertexFactory.h"
#include "Mesh.h"
#include <random>

static std::vector<glm::vec3> ssaoKernel;
static std::vector<glm::vec3> ssaoNoise;;
bool RP_SSAOPass::Init()
{
    auto bmp = BaseManager::getInstance();
    std::uniform_real_distribution<GLfloat> randomFloats(0.0, 1.0); // 随机浮点数，范围0.0 - 1.0
    std::default_random_engine generator;
    ssaoKernel = std::vector<glm::vec3>();
    for (GLuint i = 0; i < 64; ++i)
    {
        glm::vec3 sample(
            randomFloats(generator) * 2.0 - 1.0,
            randomFloats(generator) * 2.0 - 1.0,
            randomFloats(generator)
        );
        sample = glm::normalize(sample);
        sample *= randomFloats(generator);

        GLfloat scale = GLfloat(i) / 64.0;
        scale = 0.1f + scale * scale * (1.0f - 0.1f);   // lerp(0.1f, 1.0f, scale * scale);
        sample *= scale;
        ssaoKernel.push_back(sample);
    }

    ssaoNoise = std::vector<glm::vec3>();
    for (GLuint i = 0; i < 16; i++)
    {
        glm::vec3 noise(
            randomFloats(generator) * 2.0 - 1.0,
            randomFloats(generator) * 2.0 - 1.0,
            0.0f);
        ssaoNoise.push_back(noise);
    }

    // 随机旋转向量贴图生成
    glGenTextures(1, &RenderManager::globleTexture.ssao_noise);
    glBindTexture(GL_TEXTURE_2D, RenderManager::globleTexture.ssao_noise);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, 4, 4, 0, GL_RGB, GL_FLOAT, &ssaoNoise[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // ssao FrameBuffer
    glGenFramebuffers(1, &RenderManager::globalBuffer.ssaoFrameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, RenderManager::globalBuffer.ssaoFrameBuffer);


    glGenTextures(1, &RenderManager::globleTexture.ssao_Texture);
    glBindTexture(GL_TEXTURE_2D, RenderManager::globleTexture.ssao_Texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, bmp->screenWidth, bmp->screenHeight, 0, GL_RGB, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, RenderManager::globleTexture.ssao_Texture, 0);

    return true;
}

bool RP_SSAOPass::Render()
{

    BaseManager* baseManager = BaseManager::getInstance();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBindFramebuffer(GL_FRAMEBUFFER, RenderManager::globalBuffer.ssaoFrameBuffer);
    //glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDepthFunc(GL_LESS);
    glCullFace(GL_BACK);
    baseManager->colorClear();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    auto mat = MaterialManager::getInstance()->getUserMaterialRef("Deferred_SSAO");
    auto shader = mat.m_Shader.lock();
    shader->use();
    shader->setInt("texNoise", 2);
    glActiveTexture(GL_TEXTURE0 + 2);
    glBindTexture(GL_TEXTURE_2D, RenderManager::globleTexture.ssao_noise);
    mat.bindUniform();
    shader->setVec2("screenSize", vec2(baseManager->screenWidth, baseManager->screenHeight));
    shader->setMat4("projection", baseManager->getProjMat4());
    for (GLuint i = 0; i < 64; ++i)
        shader->setVec3("samples[" + std::to_string(i) + "]", ssaoKernel[i]);

    VertexFactory::getQuadData()->draw();

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    return true;
}

bool RP_SSAOPass::Release()
{
    return true;
}
