//
// Generated file, do not edit! Created by nedtool 5.1 from src/Base/messages/OBS_Burst.msg.
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
#include "OBS_Burst_m.h"

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

OBS_Burst_Base::OBS_Burst_Base(const char *name, short kind) : ::TransmittedMessage_Base(name,kind)
{
    take(&(this->messages));
    this->numPackets = -1;
    this->minOffset = -1;
    this->maxOffset = -1;
    this->burstifierId = -1;
    this->numSeq = -1;
    this->senderId = -1;
    this->hasBeenTransmitted = false;
}

OBS_Burst_Base::OBS_Burst_Base(const OBS_Burst_Base& other) : ::TransmittedMessage_Base(other)
{
    take(&(this->messages));
    copy(other);
}

OBS_Burst_Base::~OBS_Burst_Base()
{
    drop(&(this->messages));
}

OBS_Burst_Base& OBS_Burst_Base::operator=(const OBS_Burst_Base& other)
{
    if (this==&other) return *this;
    ::TransmittedMessage_Base::operator=(other);
    copy(other);
    return *this;
}

void OBS_Burst_Base::copy(const OBS_Burst_Base& other)
{
    this->messages = other.messages;
    this->messages.setName(other.messages.getName());
    this->numPackets = other.numPackets;
    this->minOffset = other.minOffset;
    this->maxOffset = other.maxOffset;
    this->burstifierId = other.burstifierId;
    this->numSeq = other.numSeq;
    this->senderId = other.senderId;
    this->hasBeenTransmitted = other.hasBeenTransmitted;
}

void OBS_Burst_Base::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::TransmittedMessage_Base::parsimPack(b);
    doParsimPacking(b,this->messages);
    doParsimPacking(b,this->numPackets);
    doParsimPacking(b,this->minOffset);
    doParsimPacking(b,this->maxOffset);
    doParsimPacking(b,this->burstifierId);
    doParsimPacking(b,this->numSeq);
    doParsimPacking(b,this->senderId);
    doParsimPacking(b,this->hasBeenTransmitted);
}

void OBS_Burst_Base::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::TransmittedMessage_Base::parsimUnpack(b);
    doParsimUnpacking(b,this->messages);
    doParsimUnpacking(b,this->numPackets);
    doParsimUnpacking(b,this->minOffset);
    doParsimUnpacking(b,this->maxOffset);
    doParsimUnpacking(b,this->burstifierId);
    doParsimUnpacking(b,this->numSeq);
    doParsimUnpacking(b,this->senderId);
    doParsimUnpacking(b,this->hasBeenTransmitted);
}

cQueue& OBS_Burst_Base::getMessages()
{
    return this->messages;
}

void OBS_Burst_Base::setMessages(const cQueue& messages)
{
    this->messages = messages;
}

int OBS_Burst_Base::getNumPackets() const
{
    return this->numPackets;
}

void OBS_Burst_Base::setNumPackets(int numPackets)
{
    this->numPackets = numPackets;
}

::omnetpp::simtime_t OBS_Burst_Base::getMinOffset() const
{
    return this->minOffset;
}

void OBS_Burst_Base::setMinOffset(::omnetpp::simtime_t minOffset)
{
    this->minOffset = minOffset;
}

::omnetpp::simtime_t OBS_Burst_Base::getMaxOffset() const
{
    return this->maxOffset;
}

void OBS_Burst_Base::setMaxOffset(::omnetpp::simtime_t maxOffset)
{
    this->maxOffset = maxOffset;
}

int OBS_Burst_Base::getBurstifierId() const
{
    return this->burstifierId;
}

void OBS_Burst_Base::setBurstifierId(int burstifierId)
{
    this->burstifierId = burstifierId;
}

int OBS_Burst_Base::getNumSeq() const
{
    return this->numSeq;
}

void OBS_Burst_Base::setNumSeq(int numSeq)
{
    this->numSeq = numSeq;
}

int OBS_Burst_Base::getSenderId() const
{
    return this->senderId;
}

void OBS_Burst_Base::setSenderId(int senderId)
{
    this->senderId = senderId;
}

bool OBS_Burst_Base::getHasBeenTransmitted() const
{
    return this->hasBeenTransmitted;
}

void OBS_Burst_Base::setHasBeenTransmitted(bool hasBeenTransmitted)
{
    this->hasBeenTransmitted = hasBeenTransmitted;
}

class OBS_BurstDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    OBS_BurstDescriptor();
    virtual ~OBS_BurstDescriptor();

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

Register_ClassDescriptor(OBS_BurstDescriptor)

OBS_BurstDescriptor::OBS_BurstDescriptor() : omnetpp::cClassDescriptor("OBS_Burst", "TransmittedMessage_Base")
{
    propertynames = nullptr;
}

OBS_BurstDescriptor::~OBS_BurstDescriptor()
{
    delete[] propertynames;
}

bool OBS_BurstDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<OBS_Burst_Base *>(obj)!=nullptr;
}

const char **OBS_BurstDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = { "customize",  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *OBS_BurstDescriptor::getProperty(const char *propertyname) const
{
    if (!strcmp(propertyname,"customize")) return "true";
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int OBS_BurstDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 8+basedesc->getFieldCount() : 8;
}

unsigned int OBS_BurstDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND | FD_ISCOBJECT | FD_ISCOWNEDOBJECT,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<8) ? fieldTypeFlags[field] : 0;
}

const char *OBS_BurstDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "messages",
        "numPackets",
        "minOffset",
        "maxOffset",
        "burstifierId",
        "numSeq",
        "senderId",
        "hasBeenTransmitted",
    };
    return (field>=0 && field<8) ? fieldNames[field] : nullptr;
}

int OBS_BurstDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='m' && strcmp(fieldName, "messages")==0) return base+0;
    if (fieldName[0]=='n' && strcmp(fieldName, "numPackets")==0) return base+1;
    if (fieldName[0]=='m' && strcmp(fieldName, "minOffset")==0) return base+2;
    if (fieldName[0]=='m' && strcmp(fieldName, "maxOffset")==0) return base+3;
    if (fieldName[0]=='b' && strcmp(fieldName, "burstifierId")==0) return base+4;
    if (fieldName[0]=='n' && strcmp(fieldName, "numSeq")==0) return base+5;
    if (fieldName[0]=='s' && strcmp(fieldName, "senderId")==0) return base+6;
    if (fieldName[0]=='h' && strcmp(fieldName, "hasBeenTransmitted")==0) return base+7;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *OBS_BurstDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "cQueue",
        "int",
        "simtime_t",
        "simtime_t",
        "int",
        "int",
        "int",
        "bool",
    };
    return (field>=0 && field<8) ? fieldTypeStrings[field] : nullptr;
}

const char **OBS_BurstDescriptor::getFieldPropertyNames(int field) const
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

const char *OBS_BurstDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int OBS_BurstDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    OBS_Burst_Base *pp = (OBS_Burst_Base *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *OBS_BurstDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    OBS_Burst_Base *pp = (OBS_Burst_Base *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string OBS_BurstDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    OBS_Burst_Base *pp = (OBS_Burst_Base *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getMessages(); return out.str();}
        case 1: return long2string(pp->getNumPackets());
        case 2: return simtime2string(pp->getMinOffset());
        case 3: return simtime2string(pp->getMaxOffset());
        case 4: return long2string(pp->getBurstifierId());
        case 5: return long2string(pp->getNumSeq());
        case 6: return long2string(pp->getSenderId());
        case 7: return bool2string(pp->getHasBeenTransmitted());
        default: return "";
    }
}

bool OBS_BurstDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    OBS_Burst_Base *pp = (OBS_Burst_Base *)object; (void)pp;
    switch (field) {
        case 1: pp->setNumPackets(string2long(value)); return true;
        case 2: pp->setMinOffset(string2simtime(value)); return true;
        case 3: pp->setMaxOffset(string2simtime(value)); return true;
        case 4: pp->setBurstifierId(string2long(value)); return true;
        case 5: pp->setNumSeq(string2long(value)); return true;
        case 6: pp->setSenderId(string2long(value)); return true;
        case 7: pp->setHasBeenTransmitted(string2bool(value)); return true;
        default: return false;
    }
}

const char *OBS_BurstDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 0: return omnetpp::opp_typename(typeid(cQueue));
        default: return nullptr;
    };
}

void *OBS_BurstDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    OBS_Burst_Base *pp = (OBS_Burst_Base *)object; (void)pp;
    switch (field) {
        case 0: return (void *)static_cast<omnetpp::cObject *>(&pp->getMessages()); break;
        default: return nullptr;
    }
}


