#ifndef SIGNAL_H
#define SIGNAL_H

#include "generateKeys.h"
#include "globalContext.h"
#include <sodium.h>

class Signal : public generateKeys {
public:
  // Constructor: creates a GlobalContext for this Signal instance.
  explicit Signal(void *userData = nullptr) {
    context_ = createGlobalContext(userData);
    // Optionally, configure context_ here if needed.
  }

  ~Signal() { destroyGlobalContext(context_); }

  // Expose an accessor if external configuration is needed.
  GlobalContext *getContext() const { return context_; }

  // This member function uses the cryptoProvider from the context.
  void initializeKeys() {
    if (context_ && context_->cryptoProvider) {
      context_->cryptoProvider->generateKeys();
      // You might call storeKeys() or other functions here.
    }
  }

private:
  GlobalContext *context_; // Each Signal instance owns its own GlobalContext.
};

#endif // SIGNAL_H

