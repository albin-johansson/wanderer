#pragma once

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

};

}