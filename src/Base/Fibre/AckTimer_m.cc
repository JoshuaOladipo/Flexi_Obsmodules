//
// Generated file, do not edit! Created by nedtool 5.1 from src/Base/Fibre/AckTimer.msg.
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
#include "AckTimer_m.h"

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

Register_Class(AckTimer)

AckTimer::AckTimer(const char *name, short kind) : ::omnetpp::cMessage(name,kind)
{
    this->creationTime = 0;
    this->burstifierId = 0;
    this->numSeq = 0;
    this->senderId = 0;
    this->entryId = 0;
    this->routePos = 0;
    this->shortestPathCost = 0;
    this->distTravelled = 0;
    entryIds_arraysize = 0;
    this->entryIds = 0;
}

AckTimer::AckTimer(const AckTimer& other) : ::omnetpp::cMessage(other)
{
    entryIds_arraysize = 0;
    this->entryIds = 0;
    copy(other);
}

AckTimer::~AckTimer()
{
    delete [] this->entryIds;
}

AckTimer& AckTimer::operator=(const AckTimer& other)
{
    if (this==&other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void AckTimer::copy(const AckTimer& other)
{
    this->creationTime = other.creationTime;
    this->burstifierId = other.burstifierId;
    this->numSeq = other.numSeq;
    this->senderId = other.senderId;
    this->entryId = other.entryId;
    this->routePos = other.routePos;
    this->shortestPathCost = other.shortestPathCost;
    this->distTravelled = other.distTravelled;
    delete [] this->entryIds;
    this->entryIds = (other.entryIds_arraysize==0) ? nullptr : new int[other.entryIds_arraysize];
    entryIds_arraysize = other.entryIds_arraysize;
    for (unsigned int i=0; i<entryIds_arraysize; i++)
        this->entryIds[i] = other.entryIds[i];
    this->route = other.route;
}

void AckTimer::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->creationTime);
    doParsimPacking(b,this->burstifierId);
    doParsimPacking(b,this->numSeq);
    doParsimPacking(b,this->senderId);
    doParsimPacking(b,this->entryId);
    doParsimPacking(b,this->routePos);
    doParsimPacking(b,this->shortestPathCost);
    doParsimPacking(b,this->distTravelled);
    b->pack(entryIds_arraysize);
    doParsimArrayPacking(b,this->entryIds,entryIds_arraysize);
    doParsimPacking(b,this->route);
}

void AckTimer::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->creationTime);
    doParsimUnpacking(b,this->burstifierId);
    doParsimUnpacking(b,this->numSeq);
    doParsimUnpacking(b,this->senderId);
    doParsimUnpacking(b,this->entryId);
    doParsimUnpacking(b,this->routePos);
    doParsimUnpacking(b,this->shortestPathCost);
    doParsimUnpacking(b,this->distTravelled);
    delete [] this->entryIds;
    b->unpack(entryIds_arraysize);
    if (entryIds_arraysize==0) {
        this->entryIds = 0;
    } else {
        this->entryIds = new int[entryIds_arraysize];
        doParsimArrayUnpacking(b,this->entryIds,entryIds_arraysize);
    }
    doParsimUnpacking(b,this->route);
}

::omnetpp::simtime_t AckTimer::getCreationTime() const
{
    return this->creationTime;
}

void AckTimer::setCreationTime(::omnetpp::simtime_t creationTime)
{
    this->creationTime = creationTime;
}

int AckTimer::getBurstifierId() const
{
    return this->burstifierId;
}

void AckTimer::setBurstifierId(int burstifierId)
{
    this->burstifierId = burstifierId;
}

int AckTimer::getNumSeq() const
{
    return this->numSeq;
}

void AckTimer::setNumSeq(int numSeq)
{
    this->numSeq = numSeq;
}

int AckTimer::getSenderId() const
{
    return this->senderId;
}

void AckTimer::setSenderId(int senderId)
{
    this->senderId = senderId;
}

int AckTimer::getEntryId() const
{
    return this->entryId;
}

void AckTimer::setEntryId(int entryId)
{
    this->entryId = entryId;
}

int AckTimer::getRoutePos() const
{
    return this->routePos;
}

void AckTimer::setRoutePos(int routePos)
{
    this->routePos = routePos;
}

int AckTimer::getShortestPathCost() const
{
    return this->shortestPathCost;
}

void AckTimer::setShortestPathCost(int shortestPathCost)
{
    this->shortestPathCost = shortestPathCost;
}

int AckTimer::getDistTravelled() const
{
    return this->distTravelled;
}

void AckTimer::setDistTravelled(int distTravelled)
{
    this->distTravelled = distTravelled;
}

void AckTimer::setEntryIdsArraySize(unsigned int size)
{
    int *entryIds2 = (size==0) ? nullptr : new int[size];
    unsigned int sz = entryIds_arraysize < size ? entryIds_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        entryIds2[i] = this->entryIds[i];
    for (unsigned int i=sz; i<size; i++)
        entryIds2[i] = 0;
    entryIds_arraysize = size;
    delete [] this->entryIds;
    this->entryIds = entryIds2;
}

unsigned int AckTimer::getEntryIdsArraySize() const
{
    return entryIds_arraysize;
}

int AckTimer::getEntryIds(unsigned int k) const
{
    if (k>=entryIds_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", entryIds_arraysize, k);
    return this->entryIds[k];
}

void AckTimer::setEntryIds(unsigned int k, int entryIds)
{
    if (k>=entryIds_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", entryIds_arraysize, k);
    this->entryIds[k] = entryIds;
}

pathPtr& AckTimer::getRoute()
{
    return this->route;
}

void AckTimer::setRoute(const pathPtr& route)
{
    this->route = route;
}

class AckTimerDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    AckTimerDescriptor();
    virtual ~AckTimerDescriptor();

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

Register_ClassDescriptor(AckTimerDescriptor)

AckTimerDescriptor::AckTimerDescriptor() : omnetpp::cClassDescriptor("AckTimer", "omnetpp::cMessage")
{
    propertynames = nullptr;
}

AckTimerDescriptor::~AckTimerDescriptor()
{
    delete[] propertynames;
}

bool AckTimerDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<AckTimer *>(obj)!=nullptr;
}

const char **AckTimerDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *AckTimerDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int AckTimerDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 10+basedesc->getFieldCount() : 10;
}

unsigned int AckTimerDescriptor::getFieldTypeFlags(int field) const
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
        FD_ISARRAY | FD_ISEDITABLE,
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<10) ? fieldTypeFlags[field] : 0;
}

const char *AckTimerDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "creationTime",
        "burstifierId",
        "numSeq",
        "senderId",
        "entryId",
        "routePos",
        "shortestPathCost",
        "distTravelled",
        "entryIds",
        "route",
    };
    return (field>=0 && field<10) ? fieldNames[field] : nullptr;
}

int AckTimerDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='c' && strcmp(fieldName, "creationTime")==0) return base+0;
    if (fieldName[0]=='b' && strcmp(fieldName, "burstifierId")==0) return base+1;
    if (fieldName[0]=='n' && strcmp(fieldName, "numSeq")==0) return base+2;
    if (fieldName[0]=='s' && strcmp(fieldName, "senderId")==0) return base+3;
    if (fieldName[0]=='e' && strcmp(fieldName, "entryId")==0) return base+4;
    if (fieldName[0]=='r' && strcmp(fieldName, "routePos")==0) return base+5;
    if (fieldName[0]=='s' && strcmp(fieldName, "shortestPathCost")==0) return base+6;
    if (fieldName[0]=='d' && strcmp(fieldName, "distTravelled")==0) return base+7;
    if (fieldName[0]=='e' && strcmp(fieldName, "entryIds")==0) return base+8;
    if (fieldName[0]=='r' && strcmp(fieldName, "route")==0) return base+9;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *AckTimerDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "simtime_t",
        "int",
        "int",
        "int",
        "int",
        "int",
        "int",
        "int",
        "int",
        "pathPtr",
    };
    return (field>=0 && field<10) ? fieldTypeStrings[field] : nullptr;
}

const char **AckTimerDescriptor::getFieldPropertyNames(int field) const
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

const char *AckTimerDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int AckTimerDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    AckTimer *pp = (AckTimer *)object; (void)pp;
    switch (field) {
        case 8: return pp->getEntryIdsArraySize();
        default: return 0;
    }
}

const char *AckTimerDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    AckTimer *pp = (AckTimer *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string AckTimerDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    AckTimer *pp = (AckTimer *)object; (void)pp;
    switch (field) {
        case 0: return simtime2string(pp->getCreationTime());
        case 1: return long2string(pp->getBurstifierId());
        case 2: return long2string(pp->getNumSeq());
        case 3: return long2string(pp->getSenderId());
        case 4: return long2string(pp->getEntryId());
        case 5: return long2string(pp->getRoutePos());
        case 6: return long2string(pp->getShortestPathCost());
        case 7: return long2string(pp->getDistTravelled());
        case 8: return long2string(pp->getEntryIds(i));
        case 9: {std::stringstream out; out << pp->getRoute(); return out.str();}
        default: return "";
    }
}

bool AckTimerDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    AckTimer *pp = (AckTimer *)object; (void)pp;
    switch (field) {
        case 0: pp->setCreationTime(string2simtime(value)); return true;
        case 1: pp->setBurstifierId(string2long(value)); return true;
        case 2: pp->setNumSeq(string2long(value)); return true;
        case 3: pp->setSenderId(string2long(value)); return true;
        case 4: pp->setEntryId(string2long(value)); return true;
        case 5: pp->setRoutePos(string2long(value)); return true;
        case 6: pp->setShortestPathCost(string2long(value)); return true;
        case 7: pp->setDistTravelled(string2long(value)); return true;
        case 8: pp->setEntryIds(i,string2long(value)); return true;
        default: return false;
    }
}

const char *AckTimerDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 9: return omnetpp::opp_typename(typeid(pathPtr));
        default: return nullptr;
    };
}

void *AckTimerDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    AckTimer *pp = (AckTimer *)object; (void)pp;
    switch (field) {
        case 9: return (void *)(&pp->getRoute()); break;
        default: return nullptr;
    }
}


