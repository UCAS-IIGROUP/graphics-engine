GraphicsEngine::GLSL_VERSION
GraphicsEngine::Extensions
GraphicsEngine::Settings
GraphicsEngine::MaterialType
GraphicsEngine::EmitterType

#include "glsl/material.glsl"
#include "glsl/scene.glsl"

in vec2 fs_uv;
flat in int particle_id;

#include "glsl/mesh_particle.glsl"

out vec4 color;

void main()
{
    vec2 uv = fs_uv;

    vec3 p_position = particles[particle_id].position;
    vec4 p_color = particles[particle_id].color;
    vec3 p_rotation = particles[particle_id].rotation;
    vec3 p_velocity = particles[particle_id].velocity;
    vec3 p_acceleration = particles[particle_id].acceleration;
    float p_lifetime = particles[particle_id].lifetime;
    float p_size = particles[particle_id].size;
    vec4 p_subUV = particles[particle_id].subUV;
    vec4 p_properties = particles[particle_id].properties;

    #ifdef SubUV_MODULE
        uv = uv * p_subUV.xy + p_subUV.zw;
    #endif

    #include "glsl/material_variables.glsl"

    #ifdef CUSTOM_MATERIAL
        GraphicsEngine::CustomMaterialFragmentCode
    #endif

     // computing final color
    vec4 fragment_color = vec4(1.0);
    #ifdef InitialColor_MODULE
          fragment_color *= p_color;
    #endif

    #ifdef MATERIAL_COLOR
        fragment_color *= material_color;
    #endif

    #ifdef MATERIAL_DIFFUSE
        fragment_color *= mat_diffuse;
    #endif

    #ifdef MATERIAL_BLENDMASK
        if (mat_blend_mask == 0.0) discard;
        fragment_color.a *= mat_blend_mask;
    #endif

    #ifdef MATERIAL_EMISSIVEMASK
        if (mat_emissivemask != vec3(0.0))
        {
            fragment_color.rgb *= mat_emissive_mask;

            #ifdef MATERIAL_EMISSIVE_COLOR
                fragment_color.rgb *= mat_emissive_color;
            #endif
        }
    #else
        #ifdef MATERIAL_EMISSIVE_COLOR
            fragment_color.rgb *= mat_emissive_color;
        #endif
    #endif

    color = fragment_color;
}