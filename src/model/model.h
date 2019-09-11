#pragma once
#include <memory>

namespace wanderer::model {

/**
 * The IModel class is an interface that specifies the facade for the model component of the
 * application.
 *
 * \since 0.1.0
 */
class IModel {
 protected:
  IModel() = default;

 public:
  virtual ~IModel() = default;

  virtual void Update(double delta) = 0;

};

using IModel_uptr = std::unique_ptr<IModel>;
using IModel_sptr = std::shared_ptr<IModel>;
using IModel_wptr = std::weak_ptr<IModel>;

}