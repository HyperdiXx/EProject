#include <world/ecomponents.h>

using namespace EProject;

const glm::mat4& TransformComponent::getModelMatrixWorld() const
{
    // RightHanded Matrix Order Mul. transpose... Keep in my mind VULKAN!!!
    m_modelMatrix = glm::translate(m_modelMatrix, mPos) * glm::toMat4(mRot) * glm::scale(m_modelMatrix, mScale);
    m_modelMatrix = glm::transpose(m_modelMatrix);

    return m_modelMatrix;
}

const glm::mat4 TransformComponent::getInverseModelMatrixWorld() const
{
    return glm::inverse(m_modelMatrix);
}