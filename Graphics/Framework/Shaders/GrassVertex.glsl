#version 150 core
     
in vec4 Gpu_Vertex;   
in vec2 Gpu_MultiTexCoord[2]; 
in vec3 Gpu_Normal;
  

uniform mat4 mProjection;   
uniform mat4 mView;   
uniform vec2 mPosition; //< Current grass cell position
uniform vec2 mGrassLod; //< Grass LOD variables from application (could be also 2x const float or const vec2)
uniform vec4 mCameraPos;   
uniform sampler2D mHeightMap; //< Height map sampler


out vec3 Vert_Normal;    //< Vertex normals
out vec2 Vert_TexCoord; //< Vertex texture coordinates

const float mHeightMapSize = 500.0; //< Height map scale (XZ dimension)
const float mHeightScale = 75.0;  //< Height map scale (Y dimension)

/* Main! */
void main()
{
  // Just store vertex normals and texcoords (flipped y???)
  Vert_Normal = Gpu_Normal.xyz;
  Vert_TexCoord = vec2(Gpu_MultiTexCoord[0].x, 1.0 - Gpu_MultiTexCoord[0].y);

  // Distance from current vertex to camera
  float mDist = length(vec3(Gpu_Vertex.x + mPosition.x, 0.0, Gpu_Vertex.z + mPosition.y) - vec3(mCameraPos.x, 0.0,  mCameraPos.z));

  // Height multiplier (makes transition from grass to terrain a little more smooth)
  // computes white circle fading at its borders - ideal to multiply with grass height
  float mMult = 1.0 - pow(min(mDist / mGrassLod.w, 1.0), 10.0);

  // On which texcoord is current position in height map? - compute it
  // It's just simple transformation from world space to height map texture space ( replace with a single matrix ???) 
  vec2 mSamplePos = vec2(Gpu_Vertex.x + mPosition.x, Gpu_Vertex.z + mPosition.y);
  mSamplePos -= mHeightMapSize;
  mSamplePos /= mHeightMapSize;
  mSamplePos += 0.5;

  // Heightmaps height at current vertex position
  float mHeight = textureLod(mHeightMap, mSamplePos, 0.0).x * mHeightScale;

  // Output position - multiplying to get smooth transition and adding height of current vertex and position of current cell
  gl_Position = mProjection * mView * vec4(Gpu_Vertex.xyz * vec3(1.0, mMult, 1.0) + vec3(mPosition.x, mHeight, mPosition.y), 1.0);
}