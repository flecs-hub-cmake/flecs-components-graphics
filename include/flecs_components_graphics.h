#ifndef FLECS_COMPONENTS_GRAPHICS_H
#define FLECS_COMPONENTS_GRAPHICS_H

#include <flecs-components-graphics/bake_config.h>

// Reflection system boilerplate
#undef ECS_META_IMPL
#ifndef FLECS_COMPONENTS_GRAPHICS_IMPL
#define ECS_META_IMPL EXTERN // Ensure meta symbols are only defined once
#endif

#ifdef __cplusplus
extern "C" {
#endif

FLECS_COMPONENTS_GRAPHICS_API
ECS_STRUCT(EcsCamera, {
    vec3 position;
    vec3 lookat;
    vec3 up;
    float fov;
    float near_;
    float far_;
    bool ortho;
});

FLECS_COMPONENTS_GRAPHICS_API
ECS_STRUCT(EcsDirectionalLight, {
    vec3 position;
    vec3 direction;
    vec3 color;
});

FLECS_COMPONENTS_GRAPHICS_API
ECS_STRUCT(EcsRgb, {
    float r;
    float g;
    float b;
});

typedef EcsRgb ecs_rgb_t;

FLECS_COMPONENTS_GRAPHICS_API
ECS_STRUCT(EcsRgba, {
    float r;
    float g;
    float b;
    float a;
});

typedef EcsRgba ecs_rgba_t;

FLECS_COMPONENTS_GRAPHICS_API
ECS_STRUCT(EcsSpecular, {
    float specular_power;
    float shininess;
});

FLECS_COMPONENTS_GRAPHICS_API
ECS_STRUCT(EcsEmissive, {
    float value;
});

FLECS_COMPONENTS_GRAPHICS_API
void FlecsComponentsGraphicsImport(
    ecs_world_t *world);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#ifndef FLECS_NO_CPP

namespace flecs {
namespace components {

class graphics : FlecsComponentsGraphics {
public:
    struct rgb_t : ecs_rgb_t {
        operator float*() {
            return reinterpret_cast<float*>(this);
        }
    };

    struct rgba_t : ecs_rgba_t {
        operator float*() {
            return reinterpret_cast<float*>(this);
        }
    };

    struct Camera : EcsCamera {
        Camera() {
            this->set_position(0, 0, 0);
            this->set_lookat(0, 1, 1);
            this->set_up(0, -1, 0);
            this->set_fov(30);
            this->near_ = 0.1f;
            this->far_ = 100;
        }

        void set_position(float x, float y, float z) {
            this->position[0] = x;
            this->position[1] = y;
            this->position[2] = z;
        }

        void set_lookat(float x, float y, float z) {
            this->lookat[0] = x;
            this->lookat[1] = y;
            this->lookat[2] = z;
        }

        void set_up(float x, float y, float z) {
            this->up[0] = x;
            this->up[1] = y;
            this->up[2] = z;
        }

        void set_fov(float value) {
            this->fov = value;
        }
    };

    struct DirectionalLight : EcsDirectionalLight {
        DirectionalLight() {
            this->set_position(0, 0, 0);
            this->set_direction(0, 1, 1);
            this->set_color(1, 1, 1);
        }

        void set_position(float x, float y, float z) {
            this->position[0] = x;
            this->position[1] = y;
            this->position[2] = z;
        }

        void set_direction(float x, float y, float z) {
            this->direction[0] = x;
            this->direction[1] = y;
            this->direction[2] = z;
        }

        void set_color(float r, float g, float b) {
            this->color[0] = r;
            this->color[1] = g;
            this->color[2] = b;
        }
    };

    using Rgb = EcsRgb;
    using Rgba = EcsRgba;
    using Specular = EcsSpecular;
    using Emissive = EcsEmissive;

    graphics(flecs::world& ecs) {
        FlecsComponentsGraphicsImport(ecs);

        ecs.module<flecs::components::graphics>();
        ecs.pod_component<Camera>("flecs::components::graphics::Camera");
        ecs.pod_component<DirectionalLight>("flecs::components::graphics::DirectionalLight");
        ecs.pod_component<Rgb>("flecs::components::graphics::Rgb");
        ecs.pod_component<Rgba>("flecs::components::graphics::Rgba");
        ecs.pod_component<Specular>("flecs::components::graphics::Specular");
        ecs.pod_component<Emissive>("flecs::components::graphics::Emissive");
    }
};

}
}

#endif
#endif

#endif
