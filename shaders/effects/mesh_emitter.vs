GraphicsEngine::GLSL_VERSION
GraphicsEngine::Extensions
GraphicsEngine::Settings
GraphicsEngine::MaterialType
GraphicsEngine::EmitterType

#include "glsl/material.glsl"
#include "glsl/scene.glsl"

layout (location = 0) in vec3 position;
layout (location = 3) in vec2 uv;

out vec2 fs_uv;
flat out int particle_id;

#include "glsl/mesh_particle.glsl"

void main()
{
    fs_uv = uv;

    mat4 model = particles[gl_InstanceID].model;
    vec4 vertex_position = vec4(position, 1.0);

    #ifdef CUSTOM_MATERIAL
        GraphicsEngine::CustomMaterialVertexCode
    #endif

	gl_Position = projection * view * model * vertex_position;

	particle_id = gl_InstanceID;
}



