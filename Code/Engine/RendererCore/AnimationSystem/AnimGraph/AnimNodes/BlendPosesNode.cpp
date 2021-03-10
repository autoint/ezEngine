#include <RendererCorePCH.h>

#include <RendererCore/AnimationSystem/AnimGraph/AnimGraph.h>
#include <RendererCore/AnimationSystem/AnimGraph/AnimNodes/BlendPosesNode.h>
#include <RendererCore/AnimationSystem/SkeletonResource.h>

#include <ozz/animation/runtime/animation.h>
#include <ozz/animation/runtime/local_to_model_job.h>
#include <ozz/animation/runtime/skeleton.h>
#include <ozz/animation/runtime/skeleton_utils.h>

// clang-format off
EZ_BEGIN_DYNAMIC_REFLECTED_TYPE(ezBlendPosesAnimNode, 1, ezRTTIDefaultAllocator<ezBlendPosesAnimNode>)
  {
    EZ_BEGIN_PROPERTIES
    {
      EZ_MEMBER_PROPERTY("LocalPose1", m_LocalPose1)->AddAttributes(new ezHiddenAttribute),
      EZ_MEMBER_PROPERTY("LocalPose2", m_LocalPose2)->AddAttributes(new ezHiddenAttribute),
      EZ_MEMBER_PROPERTY("LocalPose3", m_LocalPose3)->AddAttributes(new ezHiddenAttribute),
      EZ_MEMBER_PROPERTY("LocalPose4", m_LocalPose4)->AddAttributes(new ezHiddenAttribute),
      EZ_MEMBER_PROPERTY("BlendedPose", m_BlendedPose)->AddAttributes(new ezHiddenAttribute),
    }
    EZ_END_PROPERTIES;
  }
EZ_END_DYNAMIC_REFLECTED_TYPE;
// clang-format on

ezBlendPosesAnimNode::ezBlendPosesAnimNode() = default;

ezBlendPosesAnimNode::~ezBlendPosesAnimNode() = default;

ezResult ezBlendPosesAnimNode::SerializeNode(ezStreamWriter& stream) const
{
  stream.WriteVersion(1);

  EZ_SUCCEED_OR_RETURN(SUPER::SerializeNode(stream));

  EZ_SUCCEED_OR_RETURN(m_LocalPose1.Serialize(stream));
  EZ_SUCCEED_OR_RETURN(m_LocalPose2.Serialize(stream));
  EZ_SUCCEED_OR_RETURN(m_LocalPose3.Serialize(stream));
  EZ_SUCCEED_OR_RETURN(m_LocalPose4.Serialize(stream));
  EZ_SUCCEED_OR_RETURN(m_BlendedPose.Serialize(stream));

  return EZ_SUCCESS;
}

ezResult ezBlendPosesAnimNode::DeserializeNode(ezStreamReader& stream)
{
  stream.ReadVersion(1);

  EZ_SUCCEED_OR_RETURN(SUPER::DeserializeNode(stream));

  EZ_SUCCEED_OR_RETURN(m_LocalPose1.Deserialize(stream));
  EZ_SUCCEED_OR_RETURN(m_LocalPose2.Deserialize(stream));
  EZ_SUCCEED_OR_RETURN(m_LocalPose3.Deserialize(stream));
  EZ_SUCCEED_OR_RETURN(m_LocalPose4.Deserialize(stream));
  EZ_SUCCEED_OR_RETURN(m_BlendedPose.Deserialize(stream));

  return EZ_SUCCESS;
}

void ezBlendPosesAnimNode::Step(ezAnimGraph* pOwner, ezTime tDiff, const ezSkeletonResource* pSkeleton)
{
  if (!m_BlendedPose.IsConnected())
    return;
  if (!m_LocalPose1.IsConnected() && !m_LocalPose2.IsConnected() && !m_LocalPose3.IsConnected() && !m_LocalPose4.IsConnected())
    return;

  if (m_pTransform == nullptr)
  {
    m_pTransform = pOwner->AllocateLocalTransforms(*pSkeleton);
  }

  const auto pOzzSkeleton = &pSkeleton->GetDescriptor().m_Skeleton.GetOzzSkeleton();

  //{
  //  m_ozzLocalTransforms.resize(pOzzSkeleton->num_soa_joints());

  //  ozz::animation::BlendingJob job;
  //  job.threshold = 0.1f;
  //  job.layers = ozz::span<const ozz::animation::BlendingJob::Layer>(begin(m_ozzBlendLayers), end(m_ozzBlendLayers));
  //  job.bind_pose = pOzzSkeleton->joint_bind_poses();
  //  job.output = make_span(m_ozzLocalTransforms);
  //  EZ_ASSERT_DEBUG(job.Validate(), "");
  //  job.Run();
  //}


  m_BlendedPose.SetPose(*pOwner, m_pTransform);
}
