#include <Uniform.h>
#include <glad/glad.h>
#include <TextureUnitManager.h>

void UniformSampler2D::set(GLuint programId) const
{
    size_t textureLocation;
    glUniform1i(glGetUniformLocation(programId, &name[0]), textureLocation = graphics::TextureUnitManager::requestTextureUnit());
    glBindTexture(GL_TEXTURE_2D, textureLocation);
}

void UniformSampler3D::set(GLuint programId) const
{
    size_t textureLocation;
    glUniform1i(glGetUniformLocation(programId, &name[0]), textureLocation = graphics::TextureUnitManager::requestTextureUnit());
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureLocation);    
}

void Uniform1f::set(GLuint programId) const
{
    glUniform1f(glGetUniformLocation(programId, &name[0]), scalar);
}

void UniformVec2f::set(GLuint programId) const
{
    glUniform2f(glGetUniformLocation(programId, &name[0]), vector.x, vector.y);
}

void UniformVec3f::set(GLuint programId) const
{
    glUniform3f(glGetUniformLocation(programId, &name[0]), vector.x, vector.y, vector.z);
}

void UniformVec4f::set(GLuint programId) const
{
    glUniform4f(glGetUniformLocation(programId, &name[0]), vector.x, vector.y, vector.z, vector.w);
}

void UniformMat4f::set(GLuint programId) const
{
    glUniformMatrix4fv(glGetUniformLocation(programId, &name[0]), 1, GL_FALSE, matrix.elements);
}