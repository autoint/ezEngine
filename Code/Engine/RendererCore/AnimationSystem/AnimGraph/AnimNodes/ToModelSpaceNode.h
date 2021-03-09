#pragma once

#include <RendererCore/AnimationSystem/AnimGraph/AnimGraphNode.h>

class ezSkeletonResource;
class ezStreamWriter;
class ezStreamReader;

class EZ_RENDERERCORE_DLL ezToModelSpaceAnimNode : public ezAnimGraphNode
{
  EZ_ADD_DYNAMIC_REFLECTION(ezToModelSpaceAnimNode, ezAnimGraphNode);

  //////////////////////////////////////////////////////////////////////////
  // ezAnimGraphNode

protected:
  virtual ezResult SerializeNode(ezStreamWriter& stream) const override;
  virtual ezResult DeserializeNode(ezStreamReader& stream) override;

  virtual void Step(ezAnimGraph* pOwner, ezTime tDiff, const ezSkeletonResource* pSkeleton) override;

  //////////////////////////////////////////////////////////////////////////
  // ezToModelSpaceAnimNode

public:
  ezToModelSpaceAnimNode();
  ~ezToModelSpaceAnimNode();


private:
  ezAnimGraphLocalPoseInputPin m_LocalPose;  // [ property ]
  ezAnimGraphFinalPoseOutputPin m_FinalPose; // [ property ]
};
