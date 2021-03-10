#pragma once

#include <RendererCore/RendererCoreDLL.h>

#include <Core/ResourceManager/ResourceHandle.h>
#include <Core/Utils/Blackboard.h>
#include <Foundation/Containers/DynamicArray.h>
#include <Foundation/Memory/AllocatorWrapper.h>
#include <Foundation/Types/UniquePtr.h>
#include <RendererCore/AnimationSystem/AnimGraph/AnimGraphNode.h>
#include <ozz/animation/runtime/blending_job.h>
#include <ozz/animation/runtime/sampling_job.h>
#include <ozz/base/containers/vector.h>
#include <ozz/base/maths/soa_transform.h>

class ezGameObject;
class ezStreamWriter;
class ezStreamReader;

using ezSkeletonResourceHandle = ezTypedResourceHandle<class ezSkeletonResource>;

struct ezAnimGraphBlendWeights
{
  float m_fOverallWeight = 1.0f;
  ozz::vector<ozz::math::SimdFloat4> m_ozzBlendWeights;
};

struct ezAnimGraphLocalTransforms
{
  float m_fOverallWeight = 1.0f;
  ozz::vector<ozz::math::SoaTransform> m_ozzLocalTransforms;
};

struct ezAnimGraphSamplingCache
{
  ozz::animation::SamplingCache m_ozzSamplingCache;
};

struct ezAnimGraphModelSpaceTransforms
{
  ezDynamicArray<ezMat4, ezAlignedAllocatorWrapper> m_modelSpaceTransforms;
};

class EZ_RENDERERCORE_DLL ezAnimGraph
{
  EZ_DISALLOW_COPY_AND_ASSIGN(ezAnimGraph);

public:
  ezAnimGraph();
  ~ezAnimGraph();

  void Update(ezTime tDiff);
  void SendResultTo(ezGameObject* pObject);
  const ezVec3& GetRootMotion() const { return m_vRootMotion; }

  ezDynamicArray<ezUniquePtr<ezAnimGraphNode>> m_Nodes;

  ezSkeletonResourceHandle m_hSkeleton;

  void SetExternalBlackboard(ezBlackboard* pBlackboard);
  ezBlackboard& GetBlackboard()
  {
    return *m_pBlackboard;
  }

  ezResult Serialize(ezStreamWriter& stream) const;
  ezResult Deserialize(ezStreamReader& stream);

  ezDynamicArray<ezDynamicArray<ezUInt16>> m_OutputPinToInputPinMapping[ezAnimGraphPin::ENUM_COUNT];

  // EXTEND THIS if a new type is introduced
  ezDynamicArray<ezInt8> m_TriggerInputPinStates;
  ezDynamicArray<double> m_NumberInputPinStates;
  ezDynamicArray<ezAnimGraphBlendWeights*> m_SkeletonWeightInputPinStates;
  ezDynamicArray<ezAnimGraphLocalTransforms*> m_LocalPoseInputPinStates;
  ezDynamicArray<ezAnimGraphModelSpaceTransforms*> m_FinalPoseInputPinStates;

  /// \brief To be called by ezAnimGraphNode classes every frame that they want to affect animation
  void AddFrameBlendLayer(const ozz::animation::BlendingJob::Layer& layer);

  /// \brief To be called by ezAnimGraphNode classes every frame that they want to affect the root motion
  void AddFrameRootMotion(const ezVec3& motion);

  ezAnimGraphBlendWeights* AllocateBlendWeights(const ezSkeletonResource& skeleton);
  void FreeBlendWeights(ezAnimGraphBlendWeights*& pWeights);

  ezAnimGraphLocalTransforms* AllocateLocalTransforms(const ezSkeletonResource& skeleton);
  void FreeLocalTransforms(ezAnimGraphLocalTransforms*& pTransforms);

  ezAnimGraphModelSpaceTransforms* AllocateModelSpaceTransforms(const ezSkeletonResource& skeleton);
  void FreeModelSpaceTransforms(ezAnimGraphModelSpaceTransforms*& pTransforms);

  ezAnimGraphSamplingCache* AllocateSamplingCache(const ozz::animation::Animation& animclip);
  void FreeSamplingCache(ezAnimGraphSamplingCache*& pTransforms);

  ezAnimGraphModelSpaceTransforms* m_pCurrentModelSpaceTransforms = nullptr;

private:
  ezBlackboard* m_pBlackboard = nullptr;
  ezBlackboard m_Blackboard;

  ezDynamicArray<ozz::animation::BlendingJob::Layer> m_ozzBlendLayers;
  ozz::vector<ozz::math::SoaTransform> m_ozzLocalTransforms;
  //ezDynamicArray<ezMat4, ezAlignedAllocatorWrapper> m_ModelSpaceTransform;

  ezDeque<ezAnimGraphBlendWeights> m_BlendWeights;
  ezHybridArray<ezAnimGraphBlendWeights*, 8> m_BlendWeightsFreeList;

  ezDeque<ezAnimGraphLocalTransforms> m_LocalTransforms;
  ezHybridArray<ezAnimGraphLocalTransforms*, 8> m_LocalTransformsFreeList;

  ezDeque<ezAnimGraphModelSpaceTransforms> m_ModelSpaceTransforms;
  ezHybridArray<ezAnimGraphModelSpaceTransforms*, 8> m_ModelSpaceTransformsFreeList;

  ezDeque<ezAnimGraphSamplingCache> m_SamplingCaches;
  ezHybridArray<ezAnimGraphSamplingCache*, 8> m_SamplingCachesFreeList;

  bool m_bFinalized = false;
  ezVec3 m_vRootMotion = ezVec3::ZeroVector();
  void Finalize(const ezSkeletonResource* pSkeleton);
};
