#pragma once

#include <glad/glad.h>

#include <vector>

#include <Node.h>
#include <Transform.h>

namespace graphics
{
    class Model : public Node
    {
    protected:
        unsigned int mesh = 0, material = 0;

    public:
        Model(unsigned int mesh, unsigned int material, math::Transform transform, std::vector<unsigned int> childrenNodes);

        unsigned int getMaterial() const;
        void setMaterial(GLuint programId) const;
        void drawMesh() const;
        
        void process(GLuint programId, math::Mat4 parentTransform = {});
    };
}