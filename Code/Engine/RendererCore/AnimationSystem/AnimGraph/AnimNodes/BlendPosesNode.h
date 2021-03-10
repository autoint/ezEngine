#pragma once

#include <RendererCore/AnimationSystem/AnimGraph/AnimGraphNode.h>

class ezSkeletonResource;
class ezStreamWriter;
class ezStreamReader;

class EZ_RENDERERCORE_DLL ezBlendPosesAnimNode : public ezAnimGraphNode
{
  EZ_ADD_DYNAMIC_REFLECTION(ezBlendPosesAnimNode, ezAnimGraphNode);

  //////////////////////////////////////////////////////////////////////////
  // ezAnimGraphNode

protected:
  virtual ezResult SerializeNode(ezStreamWriter& stream) const override;
  virtual ezResult DeserializeNode(ezStreamReader& stream) override;

  virtual void Step(ezAnimGraph* pOwner, ezTime tDiff, const ezSkeletonResource* pSkeleton) override;

  //////////////////////////////////////////////////////////////////////////
  // ezToModelSpaceAnimNode

public:
  ezBlendPosesAnimNode();
  ~ezBlendPosesAnimNode();


private:
  ezAnimGraphLocalPoseInputPin m_LocalPose1;   // [ property ]
  ezAnimGraphLocalPoseInputPin m_LocalPose2;   // [ property ]
  ezAnimGraphLocalPoseInputPin m_LocalPose3;   // [ property ]
  ezAnimGraphLocalPoseInputPin m_LocalPose4;   // [ property ]
  ezAnimGraphLocalPoseOutputPin m_BlendedPose; // [ property ]

  ezAnimGraphLocalTransforms* m_pTransform = nullptr;
};
