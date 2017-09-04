/*
 * QueueAssignment.h
 *
 *  Created on: Jun 26, 2016
 *      Author: Joshua
 */

#ifndef QUEUEASSIGNMENT_H_
#define QUEUEASSIGNMENT_H_

#include <omnetpp.h>
using namespace omnetpp;

class QueueAssignment : public cObject {
public:
    QueueAssignment();
    int dest;
    int outGate;
    bool inUse;
    virtual ~QueueAssignment();
};

#endif /* QUEUEASSIGNMENT_H_ */
