//
// Generated file, do not edit! Created by nedtool 5.1 from src/Base/messages/TraversalAck.msg.
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
#include "TraversalAck_m.h"

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

Register_Class(TraversalAck)

TraversalAck::TraversalAck(const char *name, short kind) : ::TransmittedMessage_Base(name,kind)
{
    this->setByteLength(20);
    this->setIsControl(true);

    this->burstifierId = -1;
    this->numSeq = -1;
    this->senderId = -1;
    this->distanceDifference = 0;
    this->lastEntryId = 0;
    this->queueTime = 0;
}

TraversalAck::TraversalAck(const TraversalAck& other) : ::TransmittedMessage_Base(other)
{
    copy(other);
}

TraversalAck::~TraversalAck()
{
}

TraversalAck& TraversalAck::operator=(const TraversalAck& other)
{
    if (this==&other) return *this;
    ::TransmittedMessage_Base::operator=(other);
    copy(other);
    return *this;
}

void TraversalAck::copy(const TraversalAck& other)
{
    this->burstifierId = other.burstifierId;
    this->numSeq = other.numSeq;
    this->senderId = other.senderId;
    this->distanceDifference = other.distanceDifference;
    this->lastEntryId = other.lastEntryId;
    this->queueTime = other.queueTime;
}

void TraversalAck::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::TransmittedMessage_Base::parsimPack(b);
    doParsimPacking(b,this->burstifierId);
    doParsimPacking(b,this->numSeq);
    doParsimPacking(b,this->senderId);
    doParsimPacking(b,this->distanceDifference);
    doParsimPacking(b,this->lastEntryId);
    doParsimPacking(b,this->queueTime);
}

void TraversalAck::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::TransmittedMessage_Base::parsimUnpack(b);
    doParsimUnpacking(b,this->burstifierId);
    doParsimUnpacking(b,this->numSeq);
    doParsimUnpacking(b,this->senderId);
    doParsimUnpacking(b,this->distanceDifference);
    doParsimUnpacking(b,this->lastEntryId);
    doParsimUnpacking(b,this->queueTime);
}

int TraversalAck::getBurstifierId() const
{
    return this->burstifierId;
}

void TraversalAck::setBurstifierId(int burstifierId)
{
    this->burstifierId = burstifierId;
}

int TraversalAck::getNumSeq() const
{
    return this->numSeq;
}

void TraversalAck::setNumSeq(int numSeq)
{
    this->numSeq = numSeq;
}

int TraversalAck::getSenderId() const
{
    return this->senderId;
}

void TraversalAck::setSenderId(int senderId)
{
    this->senderId = senderId;
}

int TraversalAck::getDistanceDifference() const
{
    return this->distanceDifference;
}

void TraversalAck::setDistanceDifference(int distanceDifference)
{
    this->distanceDifference = distanceDifference;
}

int TraversalAck::getLastEntryId() const
{
    return this->lastEntryId;
}

void TraversalAck::setLastEntryId(int lastEntryId)
{
    this->lastEntryId = lastEntryId;
}

double TraversalAck::getQueueTime() const
{
    return this->queueTime;
}

void TraversalAck::setQueueTime(double queueTime)
{
    this->queueTime = queueTime;
}

class TraversalAckDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    TraversalAckDescriptor();
    virtual ~TraversalAckDescriptor();

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

Register_ClassDescriptor(TraversalAckDescriptor)

TraversalAckDescriptor::TraversalAckDescriptor() : omnetpp::cClassDescriptor("TraversalAck", "TransmittedMessage_Base")
{
    propertynames = nullptr;
}

TraversalAckDescriptor::~TraversalAckDescriptor()
{
    delete[] propertynames;
}

bool TraversalAckDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<TraversalAck *>(obj)!=nullptr;
}

const char **TraversalAckDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *TraversalAckDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int TraversalAckDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 6+basedesc->getFieldCount() : 6;
}

unsigned int TraversalAckDescriptor::getFieldTypeFlags(int field) const
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
    };
    return (field>=0 && field<6) ? fieldTypeFlags[field] : 0;
}

const char *TraversalAckDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "burstifierId",
        "numSeq",
        "senderId",
        "distanceDifference",
        "lastEntryId",
        "queueTime",
    };
    return (field>=0 && field<6) ? fieldNames[field] : nullptr;
}

int TraversalAckDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='b' && strcmp(fieldName, "burstifierId")==0) return base+0;
    if (fieldName[0]=='n' && strcmp(fieldName, "numSeq")==0) return base+1;
    if (fieldName[0]=='s' && strcmp(fieldName, "senderId")==0) return base+2;
    if (fieldName[0]=='d' && strcmp(fieldName, "distanceDifference")==0) return base+3;
    if (fieldName[0]=='l' && strcmp(fieldName, "lastEntryId")==0) return base+4;
    if (fieldName[0]=='q' && strcmp(fieldName, "queueTime")==0) return base+5;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *TraversalAckDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "int",
        "int",
        "int",
        "int",
        "double",
    };
    return (field>=0 && field<6) ? fieldTypeStrings[field] : nullptr;
}

const char **TraversalAckDescriptor::getFieldPropertyNames(int field) const
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

const char *TraversalAckDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int TraversalAckDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    TraversalAck *pp = (TraversalAck *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *TraversalAckDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    TraversalAck *pp = (TraversalAck *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string TraversalAckDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    TraversalAck *pp = (TraversalAck *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getBurstifierId());
        case 1: return long2string(pp->getNumSeq());
        case 2: return long2string(pp->getSenderId());
        case 3: return long2string(pp->getDistanceDifference());
        case 4: return long2string(pp->getLastEntryId());
        case 5: return double2string(pp->getQueueTime());
        default: return "";
    }
}

bool TraversalAckDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    TraversalAck *pp = (TraversalAck *)object; (void)pp;
    switch (field) {
        case 0: pp->setBurstifierId(string2long(value)); return true;
        case 1: pp->setNumSeq(string2long(value)); return true;
        case 2: pp->setSenderId(string2long(value)); return true;
        case 3: pp->setDistanceDifference(string2long(value)); return true;
        case 4: pp->setLastEntryId(string2long(value)); return true;
        case 5: pp->setQueueTime(string2double(value)); return true;
        default: return false;
    }
}

const char *TraversalAckDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *TraversalAckDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    TraversalAck *pp = (TraversalAck *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}


