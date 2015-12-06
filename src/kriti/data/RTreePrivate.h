#ifndef KRITI_DATA__RTREE_PRIVATE_H
#define KRITI_DATA__RTREE_PRIVATE_H

#include <iostream>
#include <cstring>

#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/assume_abstract.hpp>

#include "Bound.h"

namespace Kriti {
namespace Data {
namespace RTreePrivate {

template<typename DataType, typename BoundType, int MaximumFactor>
class InternalNode;
template<typename DataType, typename BoundType, int MaximumFactor>
class LeafNode;

template<typename DataType, typename BoundType, int MaximumFactor>
class Node {
private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive &ar, const unsigned version) {
        ar & m_parent;
        ar & m_bounds;
        ar & m_branchCount;
    }
private:
    Node *m_parent;
    BoundType m_bounds[MaximumFactor+1];
    int m_branchCount;
public:
    Node() : m_parent(NULL), m_branchCount(0) { }
    virtual ~Node() { }
    
    virtual int depth() const { return -1; }
    
    BoundType overallBound() const {
        BoundType bound;
        for(int i = 0; i < m_branchCount; i ++) {
            bound.cover(m_bounds[i]);
        }
        return bound;
    }
    
    bool isLeaf() const { return depth() == 0; }
    
    int branchCount() const { return m_branchCount; }
    void setBranchCount(int newCount) { m_branchCount = newCount; }
    
    BoundType &branchBound(int branch) { return m_bounds[branch]; }
    const BoundType &branchBound(int branch) const { return m_bounds[branch]; }
    void setBranchBound(int branch, const BoundType &bound)
        { m_bounds[branch] = bound; }
    
    Node *parent() const { return m_parent; }
    void setParent(Node *newParent) { m_parent = newParent; }
    
    InternalNode<DataType, BoundType, MaximumFactor> *asInternalNode() {
        return static_cast<InternalNode<DataType, BoundType, MaximumFactor> *>(
                this);
    }
    LeafNode<DataType, BoundType, MaximumFactor> *asLeafNode() {
        return
            static_cast<LeafNode<DataType, BoundType, MaximumFactor> *>(this);
    }
};

template<typename DataType, typename BoundType, int MaximumFactor>
class InternalNode : public Node<DataType, BoundType, MaximumFactor> {
private:
    friend class boost::serialization::access;

    template<typename Archive>
    void serialize(Archive &ar, const unsigned version) {
        ar & boost::serialization::base_object<
            Node<DataType, BoundType, MaximumFactor> >(*this);
        ar & m_branches;
        ar & m_depth;
    }
private:
    Node<DataType, BoundType, MaximumFactor> *m_branches[MaximumFactor+1];
    int m_depth;
public:
    InternalNode() : Node<DataType, BoundType, MaximumFactor>()
        { std::memset(m_branches, 0, sizeof(m_branches)); }
    virtual ~InternalNode() {}
    
    virtual int depth() const { return m_depth; }
    void setDepth(int depth) { m_depth = depth; }
    
    Node<DataType, BoundType, MaximumFactor> *branch(int which) const
        { return m_branches[which]; }
    void setBranch(int which, Node<DataType, BoundType, MaximumFactor> *node)
        { m_branches[which] = node; }
    
    int branch(Node<DataType, BoundType, MaximumFactor> *which) const {
        for(int i = 0; i < branchCount(); i ++) {
            if(m_branches[i] == which) return i;
        }
        return -1;
    }
    
    using Node<DataType, BoundType, MaximumFactor>::branchCount;
    using Node<DataType, BoundType, MaximumFactor>::branchBound;
    using Node<DataType, BoundType, MaximumFactor>::setBranchCount;
    using Node<DataType, BoundType, MaximumFactor>::setBranchBound;
    
    /**
        Adds a branch to the internal node.
        
        @return True if the node could be added; false if the maximum number of
            nodes has already been reached.
    */
    bool addBranch(const BoundType &bound, Node<DataType, BoundType,
        MaximumFactor> *node) {

        int branch = branchCount();
        
        setBranchBound(branch, bound);
        setBranch(branch, node);
        
        node->setParent(this);
        
        setBranchCount(branch+1);
        return branch != MaximumFactor;
    }
    
    /**
        Removes a branch from the internal node.
    */
    void removeBranch(int which) {
        int lastBranch;
        if((lastBranch = branchCount()) != 1 && which != lastBranch-1) {
            m_branches[which] = m_branches[lastBranch-1];
            setBranchBound(which, branchBound(lastBranch-1));
        }
        setBranchCount(lastBranch-1);
    }
};

template<typename DataType, typename BoundType, int MaximumFactor>
class LeafNode : public Node<DataType, BoundType, MaximumFactor> {
private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive &ar, const unsigned version) {
        ar & boost::serialization::base_object<
            Node<DataType, BoundType, MaximumFactor> >(*this);
        ar & m_branches;
    }

private:
    DataType m_branches[MaximumFactor+1];
public:
    LeafNode() : Node<DataType, BoundType, MaximumFactor>()
        { std::memset(m_branches, 0, sizeof(m_branches)); }
    virtual ~LeafNode() {}
    
    virtual int depth() const { return 0; }
    /** Dummy function, does nothing. */
    void setDepth(int) { }
    
    const DataType &branch(int which) const { return m_branches[which]; }
    void setBranch(int which, const DataType &data)
        { m_branches[which] = data; }
    
    using Node<DataType, BoundType, MaximumFactor>::branchCount;
    using Node<DataType, BoundType, MaximumFactor>::branchBound;
    using Node<DataType, BoundType, MaximumFactor>::setBranchCount;
    using Node<DataType, BoundType, MaximumFactor>::setBranchBound;
    
    /**
        Adds a branch to the leaf node.
        
        @return True if the node could be added; false if the maximum number of
            nodes has already been reached.
    */
    bool addBranch(const BoundType &bound, const DataType &data) {
        int branch = branchCount();
        
        setBranchBound(branch, bound);
        setBranch(branch, data);
        
        setBranchCount(branch+1);
        return branch != MaximumFactor;
    }
    
    /**
        Removes a branch from the leaf node.
    */
    void removeBranch(int which) {
        int lastBranch;
        if((lastBranch = branchCount()) != 1 && which != lastBranch-1) {
            m_branches[which] = m_branches[lastBranch-1];
            setBranchBound(which, branchBound(lastBranch-1));
        }
        setBranchCount(lastBranch-1);
    }
};

template<typename DataType, typename BoundType, typename PointType>
class SearchVisitor {
public:
    virtual ~SearchVisitor() {}
    
    virtual void visit(const BoundType &bound, DataType data) = 0;
    virtual void visit(const PointType &point, DataType data) = 0;
};

}  // namespace RTreePrivate
}  // namespace Data
}  // namespace Kriti

#endif
