#pragma once

#include <RendererCore/AnimationSystem/AnimGraph/AnimGraphNode.h>

class ezSkeletonResource;
class ezStreamWriter;
class ezStreamReader;

class EZ_RENDERERCORE_DLL ezPoseOutputAnimNode : public ezAnimGraphNode
{
  EZ_ADD_DYNAMIC_REFLECTION(ezPoseOutputAnimNode, ezAnimGraphNode);

  //////////////////////////////////////////////////////////////////////////
  // ezAnimGraphNode

protected:
  virtual ezResult SerializeNode(ezStreamWriter& stream) const override;
  virtual ezResult DeserializeNode(ezStreamReader& stream) override;

  virtual void Step(ezAnimGraph* pOwner, ezTime tDiff, const ezSkeletonResource* pSkeleton) override;

  //////////////////////////////////////////////////////////////////////////
  // ezPoseOutputAnimNode

public:
  ezPoseOutputAnimNode();
  ~ezPoseOutputAnimNode();

private:
  ezAnimGraphFinalPoseInputPin m_FinalPose; // [ property ]
};
