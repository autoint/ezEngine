#include <RendererCorePCH.h>

#include <RendererCore/AnimationSystem/AnimGraph/AnimGraph.h>
#include <RendererCore/AnimationSystem/AnimGraph/AnimNodes/ToModelSpaceNode.h>
#include <RendererCore/AnimationSystem/SkeletonResource.h>

#include <ozz/animation/runtime/animation.h>
#include <ozz/animation/runtime/skeleton.h>
#include <ozz/animation/runtime/skeleton_utils.h>

// clang-format off
EZ_BEGIN_DYNAMIC_REFLECTED_TYPE(ezToModelSpaceAnimNode, 1, ezRTTIDefaultAllocator<ezToModelSpaceAnimNode>)
  {
    EZ_BEGIN_PROPERTIES
    {
      EZ_MEMBER_PROPERTY("LocalPose", m_LocalPose)->AddAttributes(new ezHiddenAttribute),
      EZ_MEMBER_PROPERTY("FinalPose", m_FinalPose)->AddAttributes(new ezHiddenAttribute),
    }
    EZ_END_PROPERTIES;
  }
EZ_END_DYNAMIC_REFLECTED_TYPE;
// clang-format on

ezToModelSpaceAnimNode::ezToModelSpaceAnimNode() = default;

ezToModelSpaceAnimNode::~ezToModelSpaceAnimNode() = default;

ezResult ezToModelSpaceAnimNode::SerializeNode(ezStreamWriter& stream) const
{
  stream.WriteVersion(1);

  EZ_SUCCEED_OR_RETURN(SUPER::SerializeNode(stream));

  EZ_SUCCEED_OR_RETURN(m_LocalPose.Serialize(stream));
  EZ_SUCCEED_OR_RETURN(m_FinalPose.Serialize(stream));

  return EZ_SUCCESS;
}

ezResult ezToModelSpaceAnimNode::DeserializeNode(ezStreamReader& stream)
{
  stream.ReadVersion(1);

  EZ_SUCCEED_OR_RETURN(SUPER::DeserializeNode(stream));

  EZ_SUCCEED_OR_RETURN(m_LocalPose.Deserialize(stream));
  EZ_SUCCEED_OR_RETURN(m_FinalPose.Deserialize(stream));

  return EZ_SUCCESS;
}

void ezToModelSpaceAnimNode::Step(ezAnimGraph* pOwner, ezTime tDiff, const ezSkeletonResource* pSkeleton)
{
  if (!m_LocalPose.IsConnected())
    return;
  //if (!m_FinalPose.IsConnected())
  //  return;

  //const auto pOzzSkeleton = &pSkeleton->GetDescriptor().m_Skeleton.GetOzzSkeleton();

  //m_Weights.SetWeights(*pOwner, m_pPartialBlendingMask);
}
