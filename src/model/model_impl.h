#pragma once
#include "model.h"
#include "level/world.h"
#include <memory>

namespace wanderer::model {

/**
 * The ModelImpl class is an implementation of the IModel interface.
 *
 * @since 0.1.0
 */
class ModelImpl final : public IModel {
 private:
  World_uptr world;

  ModelImpl();

 public:
  ~ModelImpl() override = default;

  ModelImpl(const ModelImpl& model) = delete;

  ModelImpl& operator=(const ModelImpl& model) = delete;

  /**
   * Creates and returns a unique pointer to an IModel instance.
   *
   * \return a unique pointer to an IModel instance.
   * @since 0.1.0
   */
  friend IModel_uptr CreateModel();

  /**
   * Updates the state of the model.
   *
   * @param delta the delta time that will be used.
   * @since 0.1.0
   */
  void Update(double delta) override;
};

} // namespace wanderer::model