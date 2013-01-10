#ifndef KRITI_PHYSICS__OBJECT_MOTION_STATE_H
#define KRITI_PHYSICS__OBJECT_MOTION_STATE_H

#include <vector>

#include <boost/shared_ptr.hpp>

#include <btBulletDynamicsCommon.h>

#include "ObjectFeedback.h"

namespace Kriti {
namespace Physics {

class ObjectMotionState : public btDefaultMotionState {
private:
    std::vector<boost::shared_ptr<ObjectFeedback>> m_feedbacks;
public:
    virtual ~ObjectMotionState() {}

    void addFeedback(boost::shared_ptr<ObjectFeedback> feedback) 
        { m_feedbacks.push_back(feedback); }

    virtual void setWorldTransform(const btTransform &transform);
};

}  // namespace Physics
}  // namespace Kriti

#endif
