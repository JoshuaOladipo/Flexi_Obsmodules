//
// Generated file, do not edit! Created by nedtool 5.1 from src/Base/messages/Flexi_OBS_BurstControlPacket.msg.
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
#include "Flexi_OBS_BurstControlPacket_m.h"

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

Register_Class(Flexi_OBS_BurstControlPacket)

Flexi_OBS_BurstControlPacket::Flexi_OBS_BurstControlPacket(const char *name, short kind) : ::TransmittedMessage_Base(name,kind)
{
    this->setByteLength(150);
    this->setIsControl(true);

    this->srcAddr = -1;
    this->destAddr = -1;
    this->assignedSpectrumCenter = -1;
    this->assignedSpectrumLowerBound = -1;
    this->assignedSpectrumUpperBound = -1;
    this->burstifierId = -1;
    this->numSeq = -1;
    this->burstOffset = -1;
    this->burstSize = -1;
    this->datarate = 0;
    this->hasSetupTransmitter = false;
    this->distTravelled = 0;
    this->shortestPathCost = 0;
    this->nodeCounter = 0;
    this->routePos = 0;
    this->entryId = -1;
    entryIds_arraysize = 0;
    this->entryIds = 0;
    this->recordPath = false;
    this->pathPos = 0;
    componentIds_arraysize = 0;
    this->componentIds = 0;
    this->compPos = 0;
    this->reservedChannelIndex = 0;
    this->percentFreeWavelengths = 1;
    this->killTime = 0;
}

Flexi_OBS_BurstControlPacket::Flexi_OBS_BurstControlPacket(const Flexi_OBS_BurstControlPacket& other) : ::TransmittedMessage_Base(other)
{
    entryIds_arraysize = 0;
    this->entryIds = 0;
    componentIds_arraysize = 0;
    this->componentIds = 0;
    copy(other);
}

Flexi_OBS_BurstControlPacket::~Flexi_OBS_BurstControlPacket()
{
    delete [] this->entryIds;
    delete [] this->componentIds;
}

Flexi_OBS_BurstControlPacket& Flexi_OBS_BurstControlPacket::operator=(const Flexi_OBS_BurstControlPacket& other)
{
    if (this==&other) return *this;
    ::TransmittedMessage_Base::operator=(other);
    copy(other);
    return *this;
}

void Flexi_OBS_BurstControlPacket::copy(const Flexi_OBS_BurstControlPacket& other)
{
    this->srcAddr = other.srcAddr;
    this->destAddr = other.destAddr;
    this->assignedSpectrumCenter = other.assignedSpectrumCenter;
    this->assignedSpectrumLowerBound = other.assignedSpectrumLowerBound;
    this->assignedSpectrumUpperBound = other.assignedSpectrumUpperBound;
    this->burstifierId = other.burstifierId;
    this->numSeq = other.numSeq;
    this->burstOffset = other.burstOffset;
    this->burstSize = other.burstSize;
    this->datarate = other.datarate;
    this->hasSetupTransmitter = other.hasSetupTransmitter;
    this->distTravelled = other.distTravelled;
    this->shortestPathCost = other.shortestPathCost;
    this->nodeCounter = other.nodeCounter;
    this->route = other.route;
    this->routePos = other.routePos;
    this->entryId = other.entryId;
    delete [] this->entryIds;
    this->entryIds = (other.entryIds_arraysize==0) ? nullptr : new int[other.entryIds_arraysize];
    entryIds_arraysize = other.entryIds_arraysize;
    for (unsigned int i=0; i<entryIds_arraysize; i++)
        this->entryIds[i] = other.entryIds[i];
    this->recordPath = other.recordPath;
    this->pathPos = other.pathPos;
    delete [] this->componentIds;
    this->componentIds = (other.componentIds_arraysize==0) ? nullptr : new int[other.componentIds_arraysize];
    componentIds_arraysize = other.componentIds_arraysize;
    for (unsigned int i=0; i<componentIds_arraysize; i++)
        this->componentIds[i] = other.componentIds[i];
    this->compPos = other.compPos;
    this->reservedChannelIndex = other.reservedChannelIndex;
    this->percentFreeWavelengths = other.percentFreeWavelengths;
    this->killTime = other.killTime;
}

void Flexi_OBS_BurstControlPacket::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::TransmittedMessage_Base::parsimPack(b);
    doParsimPacking(b,this->srcAddr);
    doParsimPacking(b,this->destAddr);
    doParsimPacking(b,this->assignedSpectrumCenter);
    doParsimPacking(b,this->assignedSpectrumLowerBound);
    doParsimPacking(b,this->assignedSpectrumUpperBound);
    doParsimPacking(b,this->burstifierId);
    doParsimPacking(b,this->numSeq);
    doParsimPacking(b,this->burstOffset);
    doParsimPacking(b,this->burstSize);
    doParsimPacking(b,this->datarate);
    doParsimPacking(b,this->hasSetupTransmitter);
    doParsimPacking(b,this->distTravelled);
    doParsimPacking(b,this->shortestPathCost);
    doParsimPacking(b,this->nodeCounter);
    doParsimPacking(b,this->route);
    doParsimPacking(b,this->routePos);
    doParsimPacking(b,this->entryId);
    b->pack(entryIds_arraysize);
    doParsimArrayPacking(b,this->entryIds,entryIds_arraysize);
    doParsimPacking(b,this->recordPath);
    doParsimPacking(b,this->pathPos);
    b->pack(componentIds_arraysize);
    doParsimArrayPacking(b,this->componentIds,componentIds_arraysize);
    doParsimPacking(b,this->compPos);
    doParsimPacking(b,this->reservedChannelIndex);
    doParsimPacking(b,this->percentFreeWavelengths);
    doParsimPacking(b,this->killTime);
}

void Flexi_OBS_BurstControlPacket::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::TransmittedMessage_Base::parsimUnpack(b);
    doParsimUnpacking(b,this->srcAddr);
    doParsimUnpacking(b,this->destAddr);
    doParsimUnpacking(b,this->assignedSpectrumCenter);
    doParsimUnpacking(b,this->assignedSpectrumLowerBound);
    doParsimUnpacking(b,this->assignedSpectrumUpperBound);
    doParsimUnpacking(b,this->burstifierId);
    doParsimUnpacking(b,this->numSeq);
    doParsimUnpacking(b,this->burstOffset);
    doParsimUnpacking(b,this->burstSize);
    doParsimUnpacking(b,this->datarate);
    doParsimUnpacking(b,this->hasSetupTransmitter);
    doParsimUnpacking(b,this->distTravelled);
    doParsimUnpacking(b,this->shortestPathCost);
    doParsimUnpacking(b,this->nodeCounter);
    doParsimUnpacking(b,this->route);
    doParsimUnpacking(b,this->routePos);
    doParsimUnpacking(b,this->entryId);
    delete [] this->entryIds;
    b->unpack(entryIds_arraysize);
    if (entryIds_arraysize==0) {
        this->entryIds = 0;
    } else {
        this->entryIds = new int[entryIds_arraysize];
        doParsimArrayUnpacking(b,this->entryIds,entryIds_arraysize);
    }
    doParsimUnpacking(b,this->recordPath);
    doParsimUnpacking(b,this->pathPos);
    delete [] this->componentIds;
    b->unpack(componentIds_arraysize);
    if (componentIds_arraysize==0) {
        this->componentIds = 0;
    } else {
        this->componentIds = new int[componentIds_arraysize];
        doParsimArrayUnpacking(b,this->componentIds,componentIds_arraysize);
    }
    doParsimUnpacking(b,this->compPos);
    doParsimUnpacking(b,this->reservedChannelIndex);
    doParsimUnpacking(b,this->percentFreeWavelengths);
    doParsimUnpacking(b,this->killTime);
}

int Flexi_OBS_BurstControlPacket::getSrcAddr() const
{
    return this->srcAddr;
}

void Flexi_OBS_BurstControlPacket::setSrcAddr(int srcAddr)
{
    this->srcAddr = srcAddr;
}

int Flexi_OBS_BurstControlPacket::getDestAddr() const
{
    return this->destAddr;
}

void Flexi_OBS_BurstControlPacket::setDestAddr(int destAddr)
{
    this->destAddr = destAddr;
}

double Flexi_OBS_BurstControlPacket::getAssignedSpectrumCenter() const
{
    return this->assignedSpectrumCenter;
}

void Flexi_OBS_BurstControlPacket::setAssignedSpectrumCenter(double assignedSpectrumCenter)
{
    this->assignedSpectrumCenter = assignedSpectrumCenter;
}

double Flexi_OBS_BurstControlPacket::getAssignedSpectrumLowerBound() const
{
    return this->assignedSpectrumLowerBound;
}

void Flexi_OBS_BurstControlPacket::setAssignedSpectrumLowerBound(double assignedSpectrumLowerBound)
{
    this->assignedSpectrumLowerBound = assignedSpectrumLowerBound;
}

double Flexi_OBS_BurstControlPacket::getAssignedSpectrumUpperBound() const
{
    return this->assignedSpectrumUpperBound;
}

void Flexi_OBS_BurstControlPacket::setAssignedSpectrumUpperBound(double assignedSpectrumUpperBound)
{
    this->assignedSpectrumUpperBound = assignedSpectrumUpperBound;
}

int Flexi_OBS_BurstControlPacket::getBurstifierId() const
{
    return this->burstifierId;
}

void Flexi_OBS_BurstControlPacket::setBurstifierId(int burstifierId)
{
    this->burstifierId = burstifierId;
}

int Flexi_OBS_BurstControlPacket::getNumSeq() const
{
    return this->numSeq;
}

void Flexi_OBS_BurstControlPacket::setNumSeq(int numSeq)
{
    this->numSeq = numSeq;
}

::omnetpp::simtime_t Flexi_OBS_BurstControlPacket::getBurstOffset() const
{
    return this->burstOffset;
}

void Flexi_OBS_BurstControlPacket::setBurstOffset(::omnetpp::simtime_t burstOffset)
{
    this->burstOffset = burstOffset;
}

int Flexi_OBS_BurstControlPacket::getBurstSize() const
{
    return this->burstSize;
}

void Flexi_OBS_BurstControlPacket::setBurstSize(int burstSize)
{
    this->burstSize = burstSize;
}

double Flexi_OBS_BurstControlPacket::getDatarate() const
{
    return this->datarate;
}

void Flexi_OBS_BurstControlPacket::setDatarate(double datarate)
{
    this->datarate = datarate;
}

bool Flexi_OBS_BurstControlPacket::getHasSetupTransmitter() const
{
    return this->hasSetupTransmitter;
}

void Flexi_OBS_BurstControlPacket::setHasSetupTransmitter(bool hasSetupTransmitter)
{
    this->hasSetupTransmitter = hasSetupTransmitter;
}

int Flexi_OBS_BurstControlPacket::getDistTravelled() const
{
    return this->distTravelled;
}

void Flexi_OBS_BurstControlPacket::setDistTravelled(int distTravelled)
{
    this->distTravelled = distTravelled;
}

int Flexi_OBS_BurstControlPacket::getShortestPathCost() const
{
    return this->shortestPathCost;
}

void Flexi_OBS_BurstControlPacket::setShortestPathCost(int shortestPathCost)
{
    this->shortestPathCost = shortestPathCost;
}

int Flexi_OBS_BurstControlPacket::getNodeCounter() const
{
    return this->nodeCounter;
}

void Flexi_OBS_BurstControlPacket::setNodeCounter(int nodeCounter)
{
    this->nodeCounter = nodeCounter;
}

pathPtr& Flexi_OBS_BurstControlPacket::getRoute()
{
    return this->route;
}

void Flexi_OBS_BurstControlPacket::setRoute(const pathPtr& route)
{
    this->route = route;
}

int Flexi_OBS_BurstControlPacket::getRoutePos() const
{
    return this->routePos;
}

void Flexi_OBS_BurstControlPacket::setRoutePos(int routePos)
{
    this->routePos = routePos;
}

int Flexi_OBS_BurstControlPacket::getEntryId() const
{
    return this->entryId;
}

void Flexi_OBS_BurstControlPacket::setEntryId(int entryId)
{
    this->entryId = entryId;
}

void Flexi_OBS_BurstControlPacket::setEntryIdsArraySize(unsigned int size)
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

unsigned int Flexi_OBS_BurstControlPacket::getEntryIdsArraySize() const
{
    return entryIds_arraysize;
}

int Flexi_OBS_BurstControlPacket::getEntryIds(unsigned int k) const
{
    if (k>=entryIds_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", entryIds_arraysize, k);
    return this->entryIds[k];
}

void Flexi_OBS_BurstControlPacket::setEntryIds(unsigned int k, int entryIds)
{
    if (k>=entryIds_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", entryIds_arraysize, k);
    this->entryIds[k] = entryIds;
}

bool Flexi_OBS_BurstControlPacket::getRecordPath() const
{
    return this->recordPath;
}

void Flexi_OBS_BurstControlPacket::setRecordPath(bool recordPath)
{
    this->recordPath = recordPath;
}

int Flexi_OBS_BurstControlPacket::getPathPos() const
{
    return this->pathPos;
}

void Flexi_OBS_BurstControlPacket::setPathPos(int pathPos)
{
    this->pathPos = pathPos;
}

void Flexi_OBS_BurstControlPacket::setComponentIdsArraySize(unsigned int size)
{
    int *componentIds2 = (size==0) ? nullptr : new int[size];
    unsigned int sz = componentIds_arraysize < size ? componentIds_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        componentIds2[i] = this->componentIds[i];
    for (unsigned int i=sz; i<size; i++)
        componentIds2[i] = 0;
    componentIds_arraysize = size;
    delete [] this->componentIds;
    this->componentIds = componentIds2;
}

unsigned int Flexi_OBS_BurstControlPacket::getComponentIdsArraySize() const
{
    return componentIds_arraysize;
}

int Flexi_OBS_BurstControlPacket::getComponentIds(unsigned int k) const
{
    if (k>=componentIds_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", componentIds_arraysize, k);
    return this->componentIds[k];
}

void Flexi_OBS_BurstControlPacket::setComponentIds(unsigned int k, int componentIds)
{
    if (k>=componentIds_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", componentIds_arraysize, k);
    this->componentIds[k] = componentIds;
}

int Flexi_OBS_BurstControlPacket::getCompPos() const
{
    return this->compPos;
}

void Flexi_OBS_BurstControlPacket::setCompPos(int compPos)
{
    this->compPos = compPos;
}

int Flexi_OBS_BurstControlPacket::getReservedChannelIndex() const
{
    return this->reservedChannelIndex;
}

void Flexi_OBS_BurstControlPacket::setReservedChannelIndex(int reservedChannelIndex)
{
    this->reservedChannelIndex = reservedChannelIndex;
}

double Flexi_OBS_BurstControlPacket::getPercentFreeWavelengths() const
{
    return this->percentFreeWavelengths;
}

void Flexi_OBS_BurstControlPacket::setPercentFreeWavelengths(double percentFreeWavelengths)
{
    this->percentFreeWavelengths = percentFreeWavelengths;
}

::omnetpp::simtime_t Flexi_OBS_BurstControlPacket::getKillTime() const
{
    return this->killTime;
}

void Flexi_OBS_BurstControlPacket::setKillTime(::omnetpp::simtime_t killTime)
{
    this->killTime = killTime;
}

class Flexi_OBS_BurstControlPacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    Flexi_OBS_BurstControlPacketDescriptor();
    virtual ~Flexi_OBS_BurstControlPacketDescriptor();

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

Register_ClassDescriptor(Flexi_OBS_BurstControlPacketDescriptor)

Flexi_OBS_BurstControlPacketDescriptor::Flexi_OBS_BurstControlPacketDescriptor() : omnetpp::cClassDescriptor("Flexi_OBS_BurstControlPacket", "TransmittedMessage_Base")
{
    propertynames = nullptr;
}

Flexi_OBS_BurstControlPacketDescriptor::~Flexi_OBS_BurstControlPacketDescriptor()
{
    delete[] propertynames;
}

bool Flexi_OBS_BurstControlPacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Flexi_OBS_BurstControlPacket *>(obj)!=nullptr;
}

const char **Flexi_OBS_BurstControlPacketDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *Flexi_OBS_BurstControlPacketDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int Flexi_OBS_BurstControlPacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 25+basedesc->getFieldCount() : 25;
}

unsigned int Flexi_OBS_BurstControlPacketDescriptor::getFieldTypeFlags(int field) const
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
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISARRAY | FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISARRAY | FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<25) ? fieldTypeFlags[field] : 0;
}

const char *Flexi_OBS_BurstControlPacketDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "srcAddr",
        "destAddr",
        "assignedSpectrumCenter",
        "assignedSpectrumLowerBound",
        "assignedSpectrumUpperBound",
        "burstifierId",
        "numSeq",
        "burstOffset",
        "burstSize",
        "datarate",
        "hasSetupTransmitter",
        "distTravelled",
        "shortestPathCost",
        "nodeCounter",
        "route",
        "routePos",
        "entryId",
        "entryIds",
        "recordPath",
        "pathPos",
        "componentIds",
        "compPos",
        "reservedChannelIndex",
        "percentFreeWavelengths",
        "killTime",
    };
    return (field>=0 && field<25) ? fieldNames[field] : nullptr;
}

int Flexi_OBS_BurstControlPacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='s' && strcmp(fieldName, "srcAddr")==0) return base+0;
    if (fieldName[0]=='d' && strcmp(fieldName, "destAddr")==0) return base+1;
    if (fieldName[0]=='a' && strcmp(fieldName, "assignedSpectrumCenter")==0) return base+2;
    if (fieldName[0]=='a' && strcmp(fieldName, "assignedSpectrumLowerBound")==0) return base+3;
    if (fieldName[0]=='a' && strcmp(fieldName, "assignedSpectrumUpperBound")==0) return base+4;
    if (fieldName[0]=='b' && strcmp(fieldName, "burstifierId")==0) return base+5;
    if (fieldName[0]=='n' && strcmp(fieldName, "numSeq")==0) return base+6;
    if (fieldName[0]=='b' && strcmp(fieldName, "burstOffset")==0) return base+7;
    if (fieldName[0]=='b' && strcmp(fieldName, "burstSize")==0) return base+8;
    if (fieldName[0]=='d' && strcmp(fieldName, "datarate")==0) return base+9;
    if (fieldName[0]=='h' && strcmp(fieldName, "hasSetupTransmitter")==0) return base+10;
    if (fieldName[0]=='d' && strcmp(fieldName, "distTravelled")==0) return base+11;
    if (fieldName[0]=='s' && strcmp(fieldName, "shortestPathCost")==0) return base+12;
    if (fieldName[0]=='n' && strcmp(fieldName, "nodeCounter")==0) return base+13;
    if (fieldName[0]=='r' && strcmp(fieldName, "route")==0) return base+14;
    if (fieldName[0]=='r' && strcmp(fieldName, "routePos")==0) return base+15;
    if (fieldName[0]=='e' && strcmp(fieldName, "entryId")==0) return base+16;
    if (fieldName[0]=='e' && strcmp(fieldName, "entryIds")==0) return base+17;
    if (fieldName[0]=='r' && strcmp(fieldName, "recordPath")==0) return base+18;
    if (fieldName[0]=='p' && strcmp(fieldName, "pathPos")==0) return base+19;
    if (fieldName[0]=='c' && strcmp(fieldName, "componentIds")==0) return base+20;
    if (fieldName[0]=='c' && strcmp(fieldName, "compPos")==0) return base+21;
    if (fieldName[0]=='r' && strcmp(fieldName, "reservedChannelIndex")==0) return base+22;
    if (fieldName[0]=='p' && strcmp(fieldName, "percentFreeWavelengths")==0) return base+23;
    if (fieldName[0]=='k' && strcmp(fieldName, "killTime")==0) return base+24;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *Flexi_OBS_BurstControlPacketDescriptor::getFieldTypeString(int field) const
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
        "double",
        "double",
        "double",
        "int",
        "int",
        "simtime_t",
        "int",
        "double",
        "bool",
        "int",
        "int",
        "int",
        "pathPtr",
        "int",
        "int",
        "int",
        "bool",
        "int",
        "int",
        "int",
        "int",
        "double",
        "simtime_t",
    };
    return (field>=0 && field<25) ? fieldTypeStrings[field] : nullptr;
}

const char **Flexi_OBS_BurstControlPacketDescriptor::getFieldPropertyNames(int field) const
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

const char *Flexi_OBS_BurstControlPacketDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int Flexi_OBS_BurstControlPacketDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    Flexi_OBS_BurstControlPacket *pp = (Flexi_OBS_BurstControlPacket *)object; (void)pp;
    switch (field) {
        case 17: return pp->getEntryIdsArraySize();
        case 20: return pp->getComponentIdsArraySize();
        default: return 0;
    }
}

const char *Flexi_OBS_BurstControlPacketDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Flexi_OBS_BurstControlPacket *pp = (Flexi_OBS_BurstControlPacket *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Flexi_OBS_BurstControlPacketDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Flexi_OBS_BurstControlPacket *pp = (Flexi_OBS_BurstControlPacket *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getSrcAddr());
        case 1: return long2string(pp->getDestAddr());
        case 2: return double2string(pp->getAssignedSpectrumCenter());
        case 3: return double2string(pp->getAssignedSpectrumLowerBound());
        case 4: return double2string(pp->getAssignedSpectrumUpperBound());
        case 5: return long2string(pp->getBurstifierId());
        case 6: return long2string(pp->getNumSeq());
        case 7: return simtime2string(pp->getBurstOffset());
        case 8: return long2string(pp->getBurstSize());
        case 9: return double2string(pp->getDatarate());
        case 10: return bool2string(pp->getHasSetupTransmitter());
        case 11: return long2string(pp->getDistTravelled());
        case 12: return long2string(pp->getShortestPathCost());
        case 13: return long2string(pp->getNodeCounter());
        case 14: {std::stringstream out; out << pp->getRoute(); return out.str();}
        case 15: return long2string(pp->getRoutePos());
        case 16: return long2string(pp->getEntryId());
        case 17: return long2string(pp->getEntryIds(i));
        case 18: return bool2string(pp->getRecordPath());
        case 19: return long2string(pp->getPathPos());
        case 20: return long2string(pp->getComponentIds(i));
        case 21: return long2string(pp->getCompPos());
        case 22: return long2string(pp->getReservedChannelIndex());
        case 23: return double2string(pp->getPercentFreeWavelengths());
        case 24: return simtime2string(pp->getKillTime());
        default: return "";
    }
}

bool Flexi_OBS_BurstControlPacketDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    Flexi_OBS_BurstControlPacket *pp = (Flexi_OBS_BurstControlPacket *)object; (void)pp;
    switch (field) {
        case 0: pp->setSrcAddr(string2long(value)); return true;
        case 1: pp->setDestAddr(string2long(value)); return true;
        case 2: pp->setAssignedSpectrumCenter(string2double(value)); return true;
        case 3: pp->setAssignedSpectrumLowerBound(string2double(value)); return true;
        case 4: pp->setAssignedSpectrumUpperBound(string2double(value)); return true;
        case 5: pp->setBurstifierId(string2long(value)); return true;
        case 6: pp->setNumSeq(string2long(value)); return true;
        case 7: pp->setBurstOffset(string2simtime(value)); return true;
        case 8: pp->setBurstSize(string2long(value)); return true;
        case 9: pp->setDatarate(string2double(value)); return true;
        case 10: pp->setHasSetupTransmitter(string2bool(value)); return true;
        case 11: pp->setDistTravelled(string2long(value)); return true;
        case 12: pp->setShortestPathCost(string2long(value)); return true;
        case 13: pp->setNodeCounter(string2long(value)); return true;
        case 15: pp->setRoutePos(string2long(value)); return true;
        case 16: pp->setEntryId(string2long(value)); return true;
        case 17: pp->setEntryIds(i,string2long(value)); return true;
        case 18: pp->setRecordPath(string2bool(value)); return true;
        case 19: pp->setPathPos(string2long(value)); return true;
        case 20: pp->setComponentIds(i,string2long(value)); return true;
        case 21: pp->setCompPos(string2long(value)); return true;
        case 22: pp->setReservedChannelIndex(string2long(value)); return true;
        case 23: pp->setPercentFreeWavelengths(string2double(value)); return true;
        case 24: pp->setKillTime(string2simtime(value)); return true;
        default: return false;
    }
}

const char *Flexi_OBS_BurstControlPacketDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 14: return omnetpp::opp_typename(typeid(pathPtr));
        default: return nullptr;
    };
}

void *Flexi_OBS_BurstControlPacketDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    Flexi_OBS_BurstControlPacket *pp = (Flexi_OBS_BurstControlPacket *)object; (void)pp;
    switch (field) {
        case 14: return (void *)(&pp->getRoute()); break;
        default: return nullptr;
    }
}


