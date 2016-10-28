#include <algorithm>

#if !defined(_WIN32) && !defined(__OpenBSD__) && !defined(__FreeBSD__)
# include <alloca.h>
#endif

#if defined (__MINGW32__)
# define alloca __builtin_alloca
#endif

#include "serial.h"

#ifdef _WIN32
#include "impl/win.h"
#else
#include "impl/unix.h"
#endif

using std::invalid_argument;
using std::min;
using std::numeric_limits;
using std::vector;
using std::size_t;
using std::string;

using serial::Serial;
using serial::SerialException;
using serial::IOException;
using serial::bytesize_t;
using serial::parity_t;
using serial::stopbits_t;
using serial::flowcontrol_t;

class Serial::ScopedReadLock {
public:
  ScopedReadLock(SerialImpl *pimpl) : pimpl_(pimpl) {
    this->pimpl_->readLock();
  }
  ~ScopedReadLock() {
    this->pimpl_->readUnlock();
  }
private:
  // Disable copy constructors
  ScopedReadLock(const ScopedReadLock&);
  const ScopedReadLock& operator=(ScopedReadLock);

  SerialImpl *pimpl_;
};

class Serial::ScopedWriteLock {
public:
  ScopedWriteLock(SerialImpl *pimpl) : pimpl_(pimpl) {
    this->pimpl_->writeLock();
  }
  ~ScopedWriteLock() {
    this->pimpl_->writeUnlock();
  }
private:
  // Disable copy constructors
  ScopedWriteLock(const ScopedWriteLock&);
  const ScopedWriteLock& operator=(ScopedWriteLock);
  SerialImpl *pimpl_;
};

Serial::Serial (const string &port, uint32_t baudrate, serial::Timeout timeout,
                bytesize_t bytesize, parity_t parity, stopbits_t stopbits,
                flowcontrol_t flowcontrol)
 : pimpl_(new SerialImpl (port, baudrate, bytesize, parity,
                                           stopbits, flowcontrol))
{
  pimpl_->setTimeout(timeout);
}

Serial::~Serial ()
{
  delete pimpl_;
}

void
Serial::open ()
{
  pimpl_->open ();
}

void
Serial::close ()
{
  pimpl_->close ();
}

bool Serial::isOpen ()
{
  return pimpl_->isOpen ();
}

size_t
Serial::available ()
{
  return pimpl_->available ();
}

bool
Serial::waitReadable ()
{
  serial::Timeout timeout(pimpl_->getTimeout ());
  return pimpl_->waitReadable(timeout.read_timeout_constant);
}

void
Serial::waitByteTimes (size_t count)
{
  pimpl_->waitByteTimes(count);
}

size_t
Serial::read_ (uint8_t *buffer, size_t size)
{
  return this->pimpl_->read (buffer, size);
}

size_t
Serial::read (uint8_t *buffer, size_t size)
{
  ScopedReadLock lock(this->pimpl_);
  return this->pimpl_->read (buffer, size);
}

size_t
Serial::write (const uint8_t *data, size_t size)
{
  ScopedWriteLock lock(this->pimpl_);
  return this->write_(data, size);
}

size_t
Serial::write_ (const uint8_t *data, size_t length)
{
  return pimpl_->write (data, length);
}

void
Serial::setPort (const string &port)
{
  ScopedReadLock rlock(this->pimpl_);
  ScopedWriteLock wlock(this->pimpl_);
  bool was_open = pimpl_->isOpen ();
  if (was_open) close();
  pimpl_->setPort (port);
  if (was_open) open ();
}

string
Serial::getPort ()
{
  return pimpl_->getPort ();
}

void
Serial::setTimeout (serial::Timeout &timeout)
{
  pimpl_->setTimeout (timeout);
}

serial::Timeout
Serial::getTimeout () {
  return pimpl_->getTimeout ();
}

void
Serial::setBaudrate (uint32_t baudrate)
{
  pimpl_->setBaudrate (baudrate);
}

uint32_t
Serial::getBaudrate ()
{
  return uint32_t(pimpl_->getBaudrate ());
}

void
Serial::setBytesize (bytesize_t bytesize)
{
  pimpl_->setBytesize (bytesize);
}

bytesize_t
Serial::getBytesize ()
{
  return pimpl_->getBytesize ();
}

void
Serial::setParity (parity_t parity)
{
  pimpl_->setParity (parity);
}

parity_t
Serial::getParity ()
{
  return pimpl_->getParity ();
}

void
Serial::setStopbits (stopbits_t stopbits)
{
  pimpl_->setStopbits (stopbits);
}

stopbits_t
Serial::getStopbits ()
{
  return pimpl_->getStopbits ();
}

void
Serial::setFlowcontrol (flowcontrol_t flowcontrol)
{
  pimpl_->setFlowcontrol (flowcontrol);
}

flowcontrol_t
Serial::getFlowcontrol ()
{
  return pimpl_->getFlowcontrol ();
}

void Serial::flush ()
{
  ScopedReadLock rlock(this->pimpl_);
  ScopedWriteLock wlock(this->pimpl_);
  pimpl_->flush ();
}

void Serial::flushInput ()
{
  ScopedReadLock lock(this->pimpl_);
  pimpl_->flushInput ();
}

void Serial::flushOutput ()
{
  ScopedWriteLock lock(this->pimpl_);
  pimpl_->flushOutput ();
}

void Serial::sendBreak (int duration)
{
  pimpl_->sendBreak (duration);
}

void Serial::setBreak (bool level)
{
  pimpl_->setBreak (level);
}

void Serial::setRTS (bool level)
{
  pimpl_->setRTS (level);
}

void Serial::setDTR (bool level)
{
  pimpl_->setDTR (level);
}

bool Serial::waitForChange()
{
  return pimpl_->waitForChange();
}

bool Serial::getCTS ()
{
  return pimpl_->getCTS ();
}

bool Serial::getDSR ()
{
  return pimpl_->getDSR ();
}

bool Serial::getRI ()
{
  return pimpl_->getRI ();
}

bool Serial::getCD ()
{
  return pimpl_->getCD ();
}
