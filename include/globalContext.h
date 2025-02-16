#ifndef GLOBAL_CONTEXT_H
#define GLOBAL_CONTEXT_H

#include <cstdint>
#include <functional>
#include <memory>
#include <vector>

/**
 * @brief Abstract interface for cryptographic operations.
 *
 * This interface defines the cryptographic functions needed for the
 * signal protocol. Implementations should provide the actual cryptographic
 * algorithms and manage keys appropriately.
 */
class CryptoProvider {
public:
  virtual ~CryptoProvider() = default;

  virtual void generateKeys() = 0;
  virtual void storeKeys() = 0;


  virtual void x3dh() = 0;
  virtual void doubleRatchet() = 0;
  virtual void sessionManager() = 0;

};

// Define types for locking functions.
using LockFunction = std::function<void(void*)>;
using UnlockFunction = std::function<void(void*)>;

/**
 * @brief GlobalContext holds shared configuration and dependencies.
 *
 * This structure encapsulates global state for the signal protocol
 * implementation. It includes pointers to cryptographic providers,
 * user-specific data, and locking functions for thread safety.
 */
struct GlobalContext {
  void* userData;  ///< Application-specific data.
  std::unique_ptr<CryptoProvider> cryptoProvider; ///< Cryptographic operations.
  LockFunction lockFunction;   ///< Function to lock shared resources.
  UnlockFunction unlockFunction; ///< Function to unlock shared resources.
};

/**
 * @brief Creates a new GlobalContext.
 * @param userData Pointer to user-specific data.
 * @return Pointer to the newly created GlobalContext.
 */
GlobalContext* createGlobalContext(void* userData);

/**
 * @brief Destroys a previously created GlobalContext.
 * @param context Pointer to the GlobalContext to destroy.
 */
void destroyGlobalContext(GlobalContext* context);

/**
 * @brief Sets the CryptoProvider for the GlobalContext.
 * @param context The GlobalContext instance.
 * @param provider Pointer to a CryptoProvider (ownership is transferred).
 */
void setCryptoProvider(GlobalContext* context, CryptoProvider* provider);

/**
 * @brief Sets the locking functions for the GlobalContext.
 * @param context The GlobalContext instance.
 * @param lockFn Function to lock shared resources.
 * @param unlockFn Function to unlock shared resources.
 */
void setLockingFunctions(GlobalContext* context, LockFunction lockFn,
                         UnlockFunction unlockFn);

#endif // GLOBAL_CONTEXT_H
