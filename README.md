# Rendering  & Physics Engine with OpenGL 4.3.

The current project consists of a graphics framework developed in C++, OpenGL 4.3., and GLEW as the foundation. On top of this framework the physics engine was developed using C++ and CUDA. 

## Table of contents

- [Graphics engine] (#graphics-engine)
- [Physics engine] (#physics-engine)
- [Tools used] (#dev-tools)
- [Available demos] (#available-demos)
- [Getting started] (#getting-started)
- [Documentation] (#documentation)
- [About the creator] (#about-creator)
- [Copyright and license] (#copyright)

## Graphics engine
 Built from the ground up without relying on GLU/GLUT, and features only OpenGL 4.3 pipeline.
### Structure:
 The Graphics Framework is modular: it presents core functionality (mesh readers, camera definitions, height map generation, etc.) along with a set of projects to test each of these features incrementally. An overview follows:
 
 
```
GraphicsFramework/
├── Core/
│   ├── Mesh.cpp
│   ├── OGLRenderer.cpp
│   ├── Shaders.cpp
|   ├── Camera.cpp
|   ├── Light.cpp
|   ├── Frustum.cpp
|   ├── Foliage.cpp
|   ├── GenericInput.cpp
|   ├── MD5Animation.cpp
|   ├── MD5FileData.cpp
|   ├── MD5Mesh.cpp
|   ├── MD5Node.cpp
|   ├── Matrix4.cpp
|   ├── OBJMesh.cpp
|   ├── Plane.cpp
|   ├── Quaternion.cpp
|   ├── SceneNode.cpp
|   ├── Vector2.h
|   ├── Vector3.h
|   ├── Vector4.h
|   ├── Window.cpp
│   └── HeightMap.cpp
├── Tests/
│   ├── HelloWorldTriangle
|   ├── Matrix Transformations
|   ├── Texturing
|   ├── Depth & Transparency
|   ├── Stencils & Scissors
|   ├── Scene Management Graph
|   ├── Index Buffers
|   ├── Skeletal Animation
|   ├── Post Processing
|   ├── Per pixel lighting
|   ├── Shadow Mapping
|   ├── Deffered rendering
|   ├── Conversion 2D to 3D
|   ├── Text
|   ├── Geometry Shaders
|   ├── Texture Atlas
│   └── Signal To Terrain
└── Shader Types/
    ├── Cartoon
    ├── Transparent
    ├── Reflective
    └── Particle
```

##Physics Engine
The framework describes physics and real-time algorithms mathematically. The real-time collision detection simulates solid body interaction.
```
PhysicsFramework/
├── Core/
│   ├── RigidBodies
│   ├── SoftBodies
│   ├── Patricles
|   ├── NumericalIntegration
|   ├── AngularMotion
|   ├── CollisionDetection
|   ├── CollisionResponse
|   ├── Broadphase
|   ├── Narrowphase
|   ├── Impulse
|   ├── Penalty
|   ├── Torque
│   └── FluidDynamics
├── Tests/
│   ├── SimpleCollision
|   ├── CollisionDetectResponse
|   ├── Damping
│   └── PenaltyTest
└── CUDAIntegration/
```
 



