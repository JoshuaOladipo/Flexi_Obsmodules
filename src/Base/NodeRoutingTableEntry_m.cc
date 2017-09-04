//
// Generated file, do not edit! Created by nedtool 5.1 from C:/Users/s210036575/Documents/Omnetpp/obsmodules/src/Base/NodeRoutingTableEntry.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include "NodeRoutingTableEntry_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp


// forward
template<typename T, typename A>
std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec);

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// operator<< for std::vector<T>
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');
    
    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

Register_Class(NodeRoutingTableEntry)

NodeRoutingTableEntry::NodeRoutingTableEntry() : ::omnetpp::cObject()
{
    this->pheromoneConc = 0;
    this->entry_Id = 0;
    this->responseReceived = true;
    this->source = 0;
    this->destination = 0;
    this->assignedSpectrumCenter = 0;
    this->assignedSpectrumLowerBound = 0;
    this->assignedSpectrumUpperBound = 0;
    this->inputPort = 0;
    this->outputPort = 0;
    this->usedCounter = 0;
    this->failedCounter = 0;
    this->successCounter = 0;
    this->numberOfCoreNodes = 0;
}

NodeRoutingTableEntry::NodeRoutingTableEntry(const NodeRoutingTableEntry& other) : ::omnetpp::cObject(other)
{
    copy(other);
}

NodeRoutingTableEntry::~NodeRoutingTableEntry()
{
}

NodeRoutingTableEntry& NodeRoutingTableEntry::operator=(const NodeRoutingTableEntry& other)
{
    if (this==&other) return *this;
    ::omnetpp::cObject::operator=(other);
    copy(other);
    return *this;
}

void NodeRoutingTableEntry::copy(const NodeRoutingTableEntry& other)
{
    this->pheromoneConc = other.pheromoneConc;
    this->entry_Id = other.entry_Id;
    this->responseReceived = other.responseReceived;
    this->source = other.source;
    this->destination = other.destination;
    this->assignedSpectrumCenter = other.assignedSpectrumCenter;
    this->assignedSpectrumLowerBound = other.assignedSpectrumLowerBound;
    this->assignedSpectrumUpperBound = other.assignedSpectrumUpperBound;
    this->inputPort = other.inputPort;
    this->outputPort = other.outputPort;
    this->route = other.route;
    this->usedCounter = other.usedCounter;
    this->failedCounter = other.failedCounter;
    this->successCounter = other.successCounter;
    this->numberOfCoreNodes = other.numberOfCoreNodes;
}

void NodeRoutingTableEntry::parsimPack(omnetpp::cCommBuffer *b) const
{
    doParsimPacking(b,this->pheromoneConc);
    doParsimPacking(b,this->entry_Id);
    doParsimPacking(b,this->responseReceived);
    doParsimPacking(b,this->source);
    doParsimPacking(b,this->destination);
    doParsimPacking(b,this->assignedSpectrumCenter);
    doParsimPacking(b,this->assignedSpectrumLowerBound);
    doParsimPacking(b,this->assignedSpectrumUpperBound);
    doParsimPacking(b,this->inputPort);
    doParsimPacking(b,this->outputPort);
    doParsimPacking(b,this->route);
    doParsimPacking(b,this->usedCounter);
    doParsimPacking(b,this->failedCounter);
    doParsimPacking(b,this->successCounter);
    doParsimPacking(b,this->numberOfCoreNodes);
}

void NodeRoutingTableEntry::parsimUnpack(omnetpp::cCommBuffer *b)
{
    doParsimUnpacking(b,this->pheromoneConc);
    doParsimUnpacking(b,this->entry_Id);
    doParsimUnpacking(b,this->responseReceived);
    doParsimUnpacking(b,this->source);
    doParsimUnpacking(b,this->destination);
    doParsimUnpacking(b,this->assignedSpectrumCenter);
    doParsimUnpacking(b,this->assignedSpectrumLowerBound);
    doParsimUnpacking(b,this->assignedSpectrumUpperBound);
    doParsimUnpacking(b,this->inputPort);
    doParsimUnpacking(b,this->outputPort);
    doParsimUnpacking(b,this->route);
    doParsimUnpacking(b,this->usedCounter);
    doParsimUnpacking(b,this->failedCounter);
    doParsimUnpacking(b,this->successCounter);
    doParsimUnpacking(b,this->numberOfCoreNodes);
}

double NodeRoutingTableEntry::getPheromoneConc() const
{
    return this->pheromoneConc;
}

void NodeRoutingTableEntry::setPheromoneConc(double pheromoneConc)
{
    this->pheromoneConc = pheromoneConc;
}

int NodeRoutingTableEntry::getEntry_Id() const
{
    return this->entry_Id;
}

void NodeRoutingTableEntry::setEntry_Id(int entry_Id)
{
    this->entry_Id = entry_Id;
}

bool NodeRoutingTableEntry::getResponseReceived() const
{
    return this->responseReceived;
}

void NodeRoutingTableEntry::setResponseReceived(bool responseReceived)
{
    this->responseReceived = responseReceived;
}

int NodeRoutingTableEntry::getSource() const
{
    return this->source;
}

void NodeRoutingTableEntry::setSource(int source)
{
    this->source = source;
}

int NodeRoutingTableEntry::getDestination() const
{
    return this->destination;
}

void NodeRoutingTableEntry::setDestination(int destination)
{
    this->destination = destination;
}

double NodeRoutingTableEntry::getAssignedSpectrumCenter() const
{
    return this->assignedSpectrumCenter;
}

void NodeRoutingTableEntry::setAssignedSpectrumCenter(double assignedSpectrumCenter)
{
    this->assignedSpectrumCenter = assignedSpectrumCenter;
}

double NodeRoutingTableEntry::getAssignedSpectrumLowerBound() const
{
    return this->assignedSpectrumLowerBound;
}

void NodeRoutingTableEntry::setAssignedSpectrumLowerBound(double assignedSpectrumLowerBound)
{
    this->assignedSpectrumLowerBound = assignedSpectrumLowerBound;
}

double NodeRoutingTableEntry::getAssignedSpectrumUpperBound() const
{
    return this->assignedSpectrumUpperBound;
}

void NodeRoutingTableEntry::setAssignedSpectrumUpperBound(double assignedSpectrumUpperBound)
{
    this->assignedSpectrumUpperBound = assignedSpectrumUpperBound;
}

int NodeRoutingTableEntry::getInputPort() const
{
    return this->inputPort;
}

void NodeRoutingTableEntry::setInputPort(int inputPort)
{
    this->inputPort = inputPort;
}

int NodeRoutingTableEntry::getOutputPort() const
{
    return this->outputPort;
}

void NodeRoutingTableEntry::setOutputPort(int outputPort)
{
    this->outputPort = outputPort;
}

pathPtr& NodeRoutingTableEntry::getRoute()
{
    return this->route;
}

void NodeRoutingTableEntry::setRoute(const pathPtr& route)
{
    this->route = route;
}

int NodeRoutingTableEntry::getUsedCounter() const
{
    return this->usedCounter;
}

void NodeRoutingTableEntry::setUsedCounter(int usedCounter)
{
    this->usedCounter = usedCounter;
}

int NodeRoutingTableEntry::getFailedCounter() const
{
    return this->failedCounter;
}

void NodeRoutingTableEntry::setFailedCounter(int failedCounter)
{
    this->failedCounter = failedCounter;
}

int NodeRoutingTableEntry::getSuccessCounter() const
{
    return this->successCounter;
}

void NodeRoutingTableEntry::setSuccessCounter(int successCounter)
{
    this->successCounter = successCounter;
}

int NodeRoutingTableEntry::getNumberOfCoreNodes() const
{
    return this->numberOfCoreNodes;
}

void NodeRoutingTableEntry::setNumberOfCoreNodes(int numberOfCoreNodes)
{
    this->numberOfCoreNodes = numberOfCoreNodes;
}

class NodeRoutingTableEntryDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    NodeRoutingTableEntryDescriptor();
    virtual ~NodeRoutingTableEntryDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(NodeRoutingTableEntryDescriptor)

NodeRoutingTableEntryDescriptor::NodeRoutingTableEntryDescriptor() : omnetpp::cClassDescriptor("NodeRoutingTableEntry", "omnetpp::cObject")
{
    propertynames = nullptr;
}

NodeRoutingTableEntryDescriptor::~NodeRoutingTableEntryDescriptor()
{
    delete[] propertynames;
}

bool NodeRoutingTableEntryDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<NodeRoutingTableEntry *>(obj)!=nullptr;
}

const char **NodeRoutingTableEntryDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *NodeRoutingTableEntryDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int NodeRoutingTableEntryDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 15+basedesc->getFieldCount() : 15;
}

unsigned int NodeRoutingTableEntryDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<15) ? fieldTypeFlags[field] : 0;
}

const char *NodeRoutingTableEntryDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "pheromoneConc",
        "entry_Id",
        "responseReceived",
        "source",
        "destination",
        "assignedSpectrumCenter",
        "assignedSpectrumLowerBound",
        "assignedSpectrumUpperBound",
        "inputPort",
        "outputPort",
        "route",
        "usedCounter",
        "failedCounter",
        "successCounter",
        "numberOfCoreNodes",
    };
    return (field>=0 && field<15) ? fieldNames[field] : nullptr;
}

int NodeRoutingTableEntryDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='p' && strcmp(fieldName, "pheromoneConc")==0) return base+0;
    if (fieldName[0]=='e' && strcmp(fieldName, "entry_Id")==0) return base+1;
    if (fieldName[0]=='r' && strcmp(fieldName, "responseReceived")==0) return base+2;
    if (fieldName[0]=='s' && strcmp(fieldName, "source")==0) return base+3;
    if (fieldName[0]=='d' && strcmp(fieldName, "destination")==0) return base+4;
    if (fieldName[0]=='a' && strcmp(fieldName, "assignedSpectrumCenter")==0) return base+5;
    if (fieldName[0]=='a' && strcmp(fieldName, "assignedSpectrumLowerBound")==0) return base+6;
    if (fieldName[0]=='a' && strcmp(fieldName, "assignedSpectrumUpperBound")==0) return base+7;
    if (fieldName[0]=='i' && strcmp(fieldName, "inputPort")==0) return base+8;
    if (fieldName[0]=='o' && strcmp(fieldName, "outputPort")==0) return base+9;
    if (fieldName[0]=='r' && strcmp(fieldName, "route")==0) return base+10;
    if (fieldName[0]=='u' && strcmp(fieldName, "usedCounter")==0) return base+11;
    if (fieldName[0]=='f' && strcmp(fieldName, "failedCounter")==0) return base+12;
    if (fieldName[0]=='s' && strcmp(fieldName, "successCounter")==0) return base+13;
    if (fieldName[0]=='n' && strcmp(fieldName, "numberOfCoreNodes")==0) return base+14;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *NodeRoutingTableEntryDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "double",
        "int",
        "bool",
        "int",
        "int",
        "double",
        "double",
        "double",
        "int",
        "int",
        "pathPtr",
        "int",
        "int",
        "int",
        "int",
    };
    return (field>=0 && field<15) ? fieldTypeStrings[field] : nullptr;
}

const char **NodeRoutingTableEntryDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *NodeRoutingTableEntryDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int NodeRoutingTableEntryDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    NodeRoutingTableEntry *pp = (NodeRoutingTableEntry *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *NodeRoutingTableEntryDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NodeRoutingTableEntry *pp = (NodeRoutingTableEntry *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string NodeRoutingTableEntryDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NodeRoutingTableEntry *pp = (NodeRoutingTableEntry *)object; (void)pp;
    switch (field) {
        case 0: return double2string(pp->getPheromoneConc());
        case 1: return long2string(pp->getEntry_Id());
        case 2: return bool2string(pp->getResponseReceived());
        case 3: return long2string(pp->getSource());
        case 4: return long2string(pp->getDestination());
        case 5: return double2string(pp->getAssignedSpectrumCenter());
        case 6: return double2string(pp->getAssignedSpectrumLowerBound());
        case 7: return double2string(pp->getAssignedSpectrumUpperBound());
        case 8: return long2string(pp->getInputPort());
        case 9: return long2string(pp->getOutputPort());
        case 10: {std::stringstream out; out << pp->getRoute(); return out.str();}
        case 11: return long2string(pp->getUsedCounter());
        case 12: return long2string(pp->getFailedCounter());
        case 13: return long2string(pp->getSuccessCounter());
        case 14: return long2string(pp->getNumberOfCoreNodes());
        default: return "";
    }
}

bool NodeRoutingTableEntryDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    NodeRoutingTableEntry *pp = (NodeRoutingTableEntry *)object; (void)pp;
    switch (field) {
        case 0: pp->setPheromoneConc(string2double(value)); return true;
        case 1: pp->setEntry_Id(string2long(value)); return true;
        case 2: pp->setResponseReceived(string2bool(value)); return true;
        case 3: pp->setSource(string2long(value)); return true;
        case 4: pp->setDestination(string2long(value)); return true;
        case 5: pp->setAssignedSpectrumCenter(string2double(value)); return true;
        case 6: pp->setAssignedSpectrumLowerBound(string2double(value)); return true;
        case 7: pp->setAssignedSpectrumUpperBound(string2double(value)); return true;
        case 8: pp->setInputPort(string2long(value)); return true;
        case 9: pp->setOutputPort(string2long(value)); return true;
        case 11: pp->setUsedCounter(string2long(value)); return true;
        case 12: pp->setFailedCounter(string2long(value)); return true;
        case 13: pp->setSuccessCounter(string2long(value)); return true;
        case 14: pp->setNumberOfCoreNodes(string2long(value)); return true;
        default: return false;
    }
}

const char *NodeRoutingTableEntryDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 10: return omnetpp::opp_typename(typeid(pathPtr));
        default: return nullptr;
    };
}

void *NodeRoutingTableEntryDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    NodeRoutingTableEntry *pp = (NodeRoutingTableEntry *)object; (void)pp;
    switch (field) {
        case 10: return (void *)(&pp->getRoute()); break;
        default: return nullptr;
    }
}


