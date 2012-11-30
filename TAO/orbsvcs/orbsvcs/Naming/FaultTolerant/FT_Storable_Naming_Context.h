// -*- C++ -*-

//=============================================================================
/**
 *  @file   FT_Storable_Naming_Context.h
 *
 *  $Id$
 *
 *  @author Kevin Stanley <stanleyk@ociweb.com>
 */
//=============================================================================


#ifndef TAO_FT_STORABLE_NAMING_CONTEXT_H
#define TAO_FT_STORABLE_NAMING_CONTEXT_H
#include /**/ "ace/pre.h"

#include "orbsvcs/Naming/Storable_Naming_Context.h"
#include "orbsvcs/Naming/FaultTolerant/ftnaming_export.h"
#include "orbsvcs/orbsvcs/PortableGroupC.h"
#include "orbsvcs/Naming/FaultTolerant/FT_Naming_Manager.h"
#include "orbsvcs/Naming/FaultTolerant/FT_NamingReplicationC.h"

TAO_BEGIN_VERSIONED_NAMESPACE_DECL

/**
 * @class FT_TAO_Storable_Naming_Context
 *
 * @brief This class specializes the TAO_Storable_Naming_Context
 * 'ConcreteImplementor' in the Bridge pattern architecture of the
 * CosNaming::NamingContext implementation.
 *
 */
class TAO_FtNaming_Export TAO_FT_Storable_Naming_Context : public TAO_Storable_Naming_Context
{
public:
  // = Initialization and termination methods.

  /**
   * Constructor that takes in preallocated data structure and takes
   * ownership of it.  Derived class from TAO_Persistent_Naming_Context
   * provides specialization of the resolve operation to support
   * load balancing.
   */
  TAO_FT_Storable_Naming_Context (CORBA::ORB_ptr orb,
                                  PortableServer::POA_ptr poa,
                                  const char *poa_id,
                                  TAO_Storable_Naming_Context_Factory *cxt_factory,
                                  TAO_Naming_Service_Persistence_Factory *factory,
                                  const ACE_TCHAR *persistence_directory);

  /// Destructor.
  virtual ~TAO_FT_Storable_Naming_Context (void);

  /**
   * Override the resolve operation to support load balancing using
   * the object group manager and associated strategy.
   */
  virtual CORBA::Object_ptr resolve (const CosNaming::Name &n);

  /**
   * Override the bind operation to support replication through the
   * FT_Naming_Replication_Manager.
   */
  virtual void bind (const CosNaming::Name &n,
                     CORBA::Object_ptr obj);

  /**
   * Override the bind_new_context operation to support replication through the
   * FT_Naming_Replication_Manager.
   */
  virtual CosNaming::NamingContext_ptr bind_new_context (
                                const CosNaming::Name &n);

  // Set the Naming Manager as a static so that it is available for all
  // naming context implementations.
  static void set_naming_manager (TAO_FT_Naming_Manager *mgr_impl);

  bool is_object_group (const CORBA::Object_ptr obj) const;

 /**
  * Tell the peer replica that this context has been updated.
  * Returns 0 if successfully reported.  Returns 1 if no peer
  * has been registered. Returns -1 on failure to communicate
  * with the peer.
  */
  int propagate_update_notification (FT_Naming::ChangeType change_type);

 /**
  * Find the indicated context below this context.  Returns 0
  * if it cannot be found.
  */
  TAO_FT_Storable_Naming_Context* find_relative_context (
                              const CosNaming::Name &n);

  /**
   * Mark the implementation as dirty for replicated persistence support.
   */
  virtual void mark_dirty (CORBA::Boolean is_dirty = 0);

  /**
   * An internal utility used to signal that this context was updated.
   * Check the last_changed_ attribute for the time of the write.
   */
  void context_written (void);

  virtual CORBA::Boolean is_dirty (void);
protected:
  static TAO_FT_Naming_Manager *naming_manager_;
  CORBA::Boolean is_dirty_;
};

TAO_END_VERSIONED_NAMESPACE_DECL

#include /**/ "ace/post.h"
#endif /* TAO_FT_STORABLE_NAMING_CONTEXT_H */
