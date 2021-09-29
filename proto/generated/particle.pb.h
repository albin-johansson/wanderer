// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: particle.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_particle_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_particle_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3018000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3018000 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
#include "color.pb.h"
#include "float3.pb.h"
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_particle_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_particle_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxiliaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[1]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_particle_2eproto;
namespace wanderer {
namespace protobuf {
class particle;
struct particleDefaultTypeInternal;
extern particleDefaultTypeInternal _particle_default_instance_;
}  // namespace protobuf
}  // namespace wanderer
PROTOBUF_NAMESPACE_OPEN
template<> ::wanderer::protobuf::particle* Arena::CreateMaybeMessage<::wanderer::protobuf::particle>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace wanderer {
namespace protobuf {

// ===================================================================

class particle final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:wanderer.protobuf.particle) */ {
 public:
  inline particle() : particle(nullptr) {}
  ~particle() override;
  explicit constexpr particle(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  particle(const particle& from);
  particle(particle&& from) noexcept
    : particle() {
    *this = ::std::move(from);
  }

  inline particle& operator=(const particle& from) {
    CopyFrom(from);
    return *this;
  }
  inline particle& operator=(particle&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const particle& default_instance() {
    return *internal_default_instance();
  }
  static inline const particle* internal_default_instance() {
    return reinterpret_cast<const particle*>(
               &_particle_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(particle& a, particle& b) {
    a.Swap(&b);
  }
  inline void Swap(particle* other) {
    if (other == this) return;
    if (GetOwningArena() == other->GetOwningArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(particle* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline particle* New() const final {
    return new particle();
  }

  particle* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<particle>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const particle& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom(const particle& from);
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to, const ::PROTOBUF_NAMESPACE_ID::Message& from);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(particle* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "wanderer.protobuf.particle";
  }
  protected:
  explicit particle(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kPositionFieldNumber = 1,
    kAccelerationFieldNumber = 2,
    kColorFieldNumber = 5,
    kNowFieldNumber = 3,
    kDurationFieldNumber = 4,
  };
  // optional .wanderer.protobuf.float3 position = 1;
  bool has_position() const;
  private:
  bool _internal_has_position() const;
  public:
  void clear_position();
  const ::wanderer::protobuf::float3& position() const;
  PROTOBUF_MUST_USE_RESULT ::wanderer::protobuf::float3* release_position();
  ::wanderer::protobuf::float3* mutable_position();
  void set_allocated_position(::wanderer::protobuf::float3* position);
  private:
  const ::wanderer::protobuf::float3& _internal_position() const;
  ::wanderer::protobuf::float3* _internal_mutable_position();
  public:
  void unsafe_arena_set_allocated_position(
      ::wanderer::protobuf::float3* position);
  ::wanderer::protobuf::float3* unsafe_arena_release_position();

  // optional .wanderer.protobuf.float3 acceleration = 2;
  bool has_acceleration() const;
  private:
  bool _internal_has_acceleration() const;
  public:
  void clear_acceleration();
  const ::wanderer::protobuf::float3& acceleration() const;
  PROTOBUF_MUST_USE_RESULT ::wanderer::protobuf::float3* release_acceleration();
  ::wanderer::protobuf::float3* mutable_acceleration();
  void set_allocated_acceleration(::wanderer::protobuf::float3* acceleration);
  private:
  const ::wanderer::protobuf::float3& _internal_acceleration() const;
  ::wanderer::protobuf::float3* _internal_mutable_acceleration();
  public:
  void unsafe_arena_set_allocated_acceleration(
      ::wanderer::protobuf::float3* acceleration);
  ::wanderer::protobuf::float3* unsafe_arena_release_acceleration();

  // optional .wanderer.protobuf.color color = 5;
  bool has_color() const;
  private:
  bool _internal_has_color() const;
  public:
  void clear_color();
  const ::wanderer::protobuf::color& color() const;
  PROTOBUF_MUST_USE_RESULT ::wanderer::protobuf::color* release_color();
  ::wanderer::protobuf::color* mutable_color();
  void set_allocated_color(::wanderer::protobuf::color* color);
  private:
  const ::wanderer::protobuf::color& _internal_color() const;
  ::wanderer::protobuf::color* _internal_mutable_color();
  public:
  void unsafe_arena_set_allocated_color(
      ::wanderer::protobuf::color* color);
  ::wanderer::protobuf::color* unsafe_arena_release_color();

  // optional float now = 3;
  bool has_now() const;
  private:
  bool _internal_has_now() const;
  public:
  void clear_now();
  float now() const;
  void set_now(float value);
  private:
  float _internal_now() const;
  void _internal_set_now(float value);
  public:

  // optional float duration = 4;
  bool has_duration() const;
  private:
  bool _internal_has_duration() const;
  public:
  void clear_duration();
  float duration() const;
  void set_duration(float value);
  private:
  float _internal_duration() const;
  void _internal_set_duration(float value);
  public:

  // @@protoc_insertion_point(class_scope:wanderer.protobuf.particle)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::internal::HasBits<1> _has_bits_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  ::wanderer::protobuf::float3* position_;
  ::wanderer::protobuf::float3* acceleration_;
  ::wanderer::protobuf::color* color_;
  float now_;
  float duration_;
  friend struct ::TableStruct_particle_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// particle

// optional .wanderer.protobuf.float3 position = 1;
inline bool particle::_internal_has_position() const {
  bool value = (_has_bits_[0] & 0x00000001u) != 0;
  PROTOBUF_ASSUME(!value || position_ != nullptr);
  return value;
}
inline bool particle::has_position() const {
  return _internal_has_position();
}
inline const ::wanderer::protobuf::float3& particle::_internal_position() const {
  const ::wanderer::protobuf::float3* p = position_;
  return p != nullptr ? *p : reinterpret_cast<const ::wanderer::protobuf::float3&>(
      ::wanderer::protobuf::_float3_default_instance_);
}
inline const ::wanderer::protobuf::float3& particle::position() const {
  // @@protoc_insertion_point(field_get:wanderer.protobuf.particle.position)
  return _internal_position();
}
inline void particle::unsafe_arena_set_allocated_position(
    ::wanderer::protobuf::float3* position) {
  if (GetArenaForAllocation() == nullptr) {
    delete reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(position_);
  }
  position_ = position;
  if (position) {
    _has_bits_[0] |= 0x00000001u;
  } else {
    _has_bits_[0] &= ~0x00000001u;
  }
  // @@protoc_insertion_point(field_unsafe_arena_set_allocated:wanderer.protobuf.particle.position)
}
inline ::wanderer::protobuf::float3* particle::release_position() {
  _has_bits_[0] &= ~0x00000001u;
  ::wanderer::protobuf::float3* temp = position_;
  position_ = nullptr;
#ifdef PROTOBUF_FORCE_COPY_IN_RELEASE
  auto* old =  reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(temp);
  temp = ::PROTOBUF_NAMESPACE_ID::internal::DuplicateIfNonNull(temp);
  if (GetArenaForAllocation() == nullptr) { delete old; }
#else  // PROTOBUF_FORCE_COPY_IN_RELEASE
  if (GetArenaForAllocation() != nullptr) {
    temp = ::PROTOBUF_NAMESPACE_ID::internal::DuplicateIfNonNull(temp);
  }
#endif  // !PROTOBUF_FORCE_COPY_IN_RELEASE
  return temp;
}
inline ::wanderer::protobuf::float3* particle::unsafe_arena_release_position() {
  // @@protoc_insertion_point(field_release:wanderer.protobuf.particle.position)
  _has_bits_[0] &= ~0x00000001u;
  ::wanderer::protobuf::float3* temp = position_;
  position_ = nullptr;
  return temp;
}
inline ::wanderer::protobuf::float3* particle::_internal_mutable_position() {
  _has_bits_[0] |= 0x00000001u;
  if (position_ == nullptr) {
    auto* p = CreateMaybeMessage<::wanderer::protobuf::float3>(GetArenaForAllocation());
    position_ = p;
  }
  return position_;
}
inline ::wanderer::protobuf::float3* particle::mutable_position() {
  ::wanderer::protobuf::float3* _msg = _internal_mutable_position();
  // @@protoc_insertion_point(field_mutable:wanderer.protobuf.particle.position)
  return _msg;
}
inline void particle::set_allocated_position(::wanderer::protobuf::float3* position) {
  ::PROTOBUF_NAMESPACE_ID::Arena* message_arena = GetArenaForAllocation();
  if (message_arena == nullptr) {
    delete reinterpret_cast< ::PROTOBUF_NAMESPACE_ID::MessageLite*>(position_);
  }
  if (position) {
    ::PROTOBUF_NAMESPACE_ID::Arena* submessage_arena =
        ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper<
            ::PROTOBUF_NAMESPACE_ID::MessageLite>::GetOwningArena(
                reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(position));
    if (message_arena != submessage_arena) {
      position = ::PROTOBUF_NAMESPACE_ID::internal::GetOwnedMessage(
          message_arena, position, submessage_arena);
    }
    _has_bits_[0] |= 0x00000001u;
  } else {
    _has_bits_[0] &= ~0x00000001u;
  }
  position_ = position;
  // @@protoc_insertion_point(field_set_allocated:wanderer.protobuf.particle.position)
}

// optional .wanderer.protobuf.float3 acceleration = 2;
inline bool particle::_internal_has_acceleration() const {
  bool value = (_has_bits_[0] & 0x00000002u) != 0;
  PROTOBUF_ASSUME(!value || acceleration_ != nullptr);
  return value;
}
inline bool particle::has_acceleration() const {
  return _internal_has_acceleration();
}
inline const ::wanderer::protobuf::float3& particle::_internal_acceleration() const {
  const ::wanderer::protobuf::float3* p = acceleration_;
  return p != nullptr ? *p : reinterpret_cast<const ::wanderer::protobuf::float3&>(
      ::wanderer::protobuf::_float3_default_instance_);
}
inline const ::wanderer::protobuf::float3& particle::acceleration() const {
  // @@protoc_insertion_point(field_get:wanderer.protobuf.particle.acceleration)
  return _internal_acceleration();
}
inline void particle::unsafe_arena_set_allocated_acceleration(
    ::wanderer::protobuf::float3* acceleration) {
  if (GetArenaForAllocation() == nullptr) {
    delete reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(acceleration_);
  }
  acceleration_ = acceleration;
  if (acceleration) {
    _has_bits_[0] |= 0x00000002u;
  } else {
    _has_bits_[0] &= ~0x00000002u;
  }
  // @@protoc_insertion_point(field_unsafe_arena_set_allocated:wanderer.protobuf.particle.acceleration)
}
inline ::wanderer::protobuf::float3* particle::release_acceleration() {
  _has_bits_[0] &= ~0x00000002u;
  ::wanderer::protobuf::float3* temp = acceleration_;
  acceleration_ = nullptr;
#ifdef PROTOBUF_FORCE_COPY_IN_RELEASE
  auto* old =  reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(temp);
  temp = ::PROTOBUF_NAMESPACE_ID::internal::DuplicateIfNonNull(temp);
  if (GetArenaForAllocation() == nullptr) { delete old; }
#else  // PROTOBUF_FORCE_COPY_IN_RELEASE
  if (GetArenaForAllocation() != nullptr) {
    temp = ::PROTOBUF_NAMESPACE_ID::internal::DuplicateIfNonNull(temp);
  }
#endif  // !PROTOBUF_FORCE_COPY_IN_RELEASE
  return temp;
}
inline ::wanderer::protobuf::float3* particle::unsafe_arena_release_acceleration() {
  // @@protoc_insertion_point(field_release:wanderer.protobuf.particle.acceleration)
  _has_bits_[0] &= ~0x00000002u;
  ::wanderer::protobuf::float3* temp = acceleration_;
  acceleration_ = nullptr;
  return temp;
}
inline ::wanderer::protobuf::float3* particle::_internal_mutable_acceleration() {
  _has_bits_[0] |= 0x00000002u;
  if (acceleration_ == nullptr) {
    auto* p = CreateMaybeMessage<::wanderer::protobuf::float3>(GetArenaForAllocation());
    acceleration_ = p;
  }
  return acceleration_;
}
inline ::wanderer::protobuf::float3* particle::mutable_acceleration() {
  ::wanderer::protobuf::float3* _msg = _internal_mutable_acceleration();
  // @@protoc_insertion_point(field_mutable:wanderer.protobuf.particle.acceleration)
  return _msg;
}
inline void particle::set_allocated_acceleration(::wanderer::protobuf::float3* acceleration) {
  ::PROTOBUF_NAMESPACE_ID::Arena* message_arena = GetArenaForAllocation();
  if (message_arena == nullptr) {
    delete reinterpret_cast< ::PROTOBUF_NAMESPACE_ID::MessageLite*>(acceleration_);
  }
  if (acceleration) {
    ::PROTOBUF_NAMESPACE_ID::Arena* submessage_arena =
        ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper<
            ::PROTOBUF_NAMESPACE_ID::MessageLite>::GetOwningArena(
                reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(acceleration));
    if (message_arena != submessage_arena) {
      acceleration = ::PROTOBUF_NAMESPACE_ID::internal::GetOwnedMessage(
          message_arena, acceleration, submessage_arena);
    }
    _has_bits_[0] |= 0x00000002u;
  } else {
    _has_bits_[0] &= ~0x00000002u;
  }
  acceleration_ = acceleration;
  // @@protoc_insertion_point(field_set_allocated:wanderer.protobuf.particle.acceleration)
}

// optional float now = 3;
inline bool particle::_internal_has_now() const {
  bool value = (_has_bits_[0] & 0x00000008u) != 0;
  return value;
}
inline bool particle::has_now() const {
  return _internal_has_now();
}
inline void particle::clear_now() {
  now_ = 0;
  _has_bits_[0] &= ~0x00000008u;
}
inline float particle::_internal_now() const {
  return now_;
}
inline float particle::now() const {
  // @@protoc_insertion_point(field_get:wanderer.protobuf.particle.now)
  return _internal_now();
}
inline void particle::_internal_set_now(float value) {
  _has_bits_[0] |= 0x00000008u;
  now_ = value;
}
inline void particle::set_now(float value) {
  _internal_set_now(value);
  // @@protoc_insertion_point(field_set:wanderer.protobuf.particle.now)
}

// optional float duration = 4;
inline bool particle::_internal_has_duration() const {
  bool value = (_has_bits_[0] & 0x00000010u) != 0;
  return value;
}
inline bool particle::has_duration() const {
  return _internal_has_duration();
}
inline void particle::clear_duration() {
  duration_ = 0;
  _has_bits_[0] &= ~0x00000010u;
}
inline float particle::_internal_duration() const {
  return duration_;
}
inline float particle::duration() const {
  // @@protoc_insertion_point(field_get:wanderer.protobuf.particle.duration)
  return _internal_duration();
}
inline void particle::_internal_set_duration(float value) {
  _has_bits_[0] |= 0x00000010u;
  duration_ = value;
}
inline void particle::set_duration(float value) {
  _internal_set_duration(value);
  // @@protoc_insertion_point(field_set:wanderer.protobuf.particle.duration)
}

// optional .wanderer.protobuf.color color = 5;
inline bool particle::_internal_has_color() const {
  bool value = (_has_bits_[0] & 0x00000004u) != 0;
  PROTOBUF_ASSUME(!value || color_ != nullptr);
  return value;
}
inline bool particle::has_color() const {
  return _internal_has_color();
}
inline const ::wanderer::protobuf::color& particle::_internal_color() const {
  const ::wanderer::protobuf::color* p = color_;
  return p != nullptr ? *p : reinterpret_cast<const ::wanderer::protobuf::color&>(
      ::wanderer::protobuf::_color_default_instance_);
}
inline const ::wanderer::protobuf::color& particle::color() const {
  // @@protoc_insertion_point(field_get:wanderer.protobuf.particle.color)
  return _internal_color();
}
inline void particle::unsafe_arena_set_allocated_color(
    ::wanderer::protobuf::color* color) {
  if (GetArenaForAllocation() == nullptr) {
    delete reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(color_);
  }
  color_ = color;
  if (color) {
    _has_bits_[0] |= 0x00000004u;
  } else {
    _has_bits_[0] &= ~0x00000004u;
  }
  // @@protoc_insertion_point(field_unsafe_arena_set_allocated:wanderer.protobuf.particle.color)
}
inline ::wanderer::protobuf::color* particle::release_color() {
  _has_bits_[0] &= ~0x00000004u;
  ::wanderer::protobuf::color* temp = color_;
  color_ = nullptr;
#ifdef PROTOBUF_FORCE_COPY_IN_RELEASE
  auto* old =  reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(temp);
  temp = ::PROTOBUF_NAMESPACE_ID::internal::DuplicateIfNonNull(temp);
  if (GetArenaForAllocation() == nullptr) { delete old; }
#else  // PROTOBUF_FORCE_COPY_IN_RELEASE
  if (GetArenaForAllocation() != nullptr) {
    temp = ::PROTOBUF_NAMESPACE_ID::internal::DuplicateIfNonNull(temp);
  }
#endif  // !PROTOBUF_FORCE_COPY_IN_RELEASE
  return temp;
}
inline ::wanderer::protobuf::color* particle::unsafe_arena_release_color() {
  // @@protoc_insertion_point(field_release:wanderer.protobuf.particle.color)
  _has_bits_[0] &= ~0x00000004u;
  ::wanderer::protobuf::color* temp = color_;
  color_ = nullptr;
  return temp;
}
inline ::wanderer::protobuf::color* particle::_internal_mutable_color() {
  _has_bits_[0] |= 0x00000004u;
  if (color_ == nullptr) {
    auto* p = CreateMaybeMessage<::wanderer::protobuf::color>(GetArenaForAllocation());
    color_ = p;
  }
  return color_;
}
inline ::wanderer::protobuf::color* particle::mutable_color() {
  ::wanderer::protobuf::color* _msg = _internal_mutable_color();
  // @@protoc_insertion_point(field_mutable:wanderer.protobuf.particle.color)
  return _msg;
}
inline void particle::set_allocated_color(::wanderer::protobuf::color* color) {
  ::PROTOBUF_NAMESPACE_ID::Arena* message_arena = GetArenaForAllocation();
  if (message_arena == nullptr) {
    delete reinterpret_cast< ::PROTOBUF_NAMESPACE_ID::MessageLite*>(color_);
  }
  if (color) {
    ::PROTOBUF_NAMESPACE_ID::Arena* submessage_arena =
        ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper<
            ::PROTOBUF_NAMESPACE_ID::MessageLite>::GetOwningArena(
                reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(color));
    if (message_arena != submessage_arena) {
      color = ::PROTOBUF_NAMESPACE_ID::internal::GetOwnedMessage(
          message_arena, color, submessage_arena);
    }
    _has_bits_[0] |= 0x00000004u;
  } else {
    _has_bits_[0] &= ~0x00000004u;
  }
  color_ = color;
  // @@protoc_insertion_point(field_set_allocated:wanderer.protobuf.particle.color)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace protobuf
}  // namespace wanderer

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_particle_2eproto
