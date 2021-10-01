// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: movable.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_movable_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_movable_2eproto

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
#include "float2.pb.h"
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_movable_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_movable_2eproto {
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
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_movable_2eproto;
namespace wanderer {
namespace proto {
class movable;
struct movableDefaultTypeInternal;
extern movableDefaultTypeInternal _movable_default_instance_;
}  // namespace proto
}  // namespace wanderer
PROTOBUF_NAMESPACE_OPEN
template<> ::wanderer::proto::movable* Arena::CreateMaybeMessage<::wanderer::proto::movable>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace wanderer {
namespace proto {

// ===================================================================

class movable final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:wanderer.proto.movable) */ {
 public:
  inline movable() : movable(nullptr) {}
  ~movable() override;
  explicit constexpr movable(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  movable(const movable& from);
  movable(movable&& from) noexcept
    : movable() {
    *this = ::std::move(from);
  }

  inline movable& operator=(const movable& from) {
    CopyFrom(from);
    return *this;
  }
  inline movable& operator=(movable&& from) noexcept {
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
  static const movable& default_instance() {
    return *internal_default_instance();
  }
  static inline const movable* internal_default_instance() {
    return reinterpret_cast<const movable*>(
               &_movable_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(movable& a, movable& b) {
    a.Swap(&b);
  }
  inline void Swap(movable* other) {
    if (other == this) return;
    if (GetOwningArena() == other->GetOwningArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(movable* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline movable* New() const final {
    return new movable();
  }

  movable* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<movable>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const movable& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom(const movable& from);
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
  void InternalSwap(movable* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "wanderer.proto.movable";
  }
  protected:
  explicit movable(::PROTOBUF_NAMESPACE_ID::Arena* arena,
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
    kVelocityFieldNumber = 2,
    kSpeedFieldNumber = 3,
  };
  // optional .wanderer.proto.float2 position = 1;
  bool has_position() const;
  private:
  bool _internal_has_position() const;
  public:
  void clear_position();
  const ::wanderer::proto::float2& position() const;
  PROTOBUF_MUST_USE_RESULT ::wanderer::proto::float2* release_position();
  ::wanderer::proto::float2* mutable_position();
  void set_allocated_position(::wanderer::proto::float2* position);
  private:
  const ::wanderer::proto::float2& _internal_position() const;
  ::wanderer::proto::float2* _internal_mutable_position();
  public:
  void unsafe_arena_set_allocated_position(
      ::wanderer::proto::float2* position);
  ::wanderer::proto::float2* unsafe_arena_release_position();

  // optional .wanderer.proto.float2 velocity = 2;
  bool has_velocity() const;
  private:
  bool _internal_has_velocity() const;
  public:
  void clear_velocity();
  const ::wanderer::proto::float2& velocity() const;
  PROTOBUF_MUST_USE_RESULT ::wanderer::proto::float2* release_velocity();
  ::wanderer::proto::float2* mutable_velocity();
  void set_allocated_velocity(::wanderer::proto::float2* velocity);
  private:
  const ::wanderer::proto::float2& _internal_velocity() const;
  ::wanderer::proto::float2* _internal_mutable_velocity();
  public:
  void unsafe_arena_set_allocated_velocity(
      ::wanderer::proto::float2* velocity);
  ::wanderer::proto::float2* unsafe_arena_release_velocity();

  // optional float speed = 3;
  bool has_speed() const;
  private:
  bool _internal_has_speed() const;
  public:
  void clear_speed();
  float speed() const;
  void set_speed(float value);
  private:
  float _internal_speed() const;
  void _internal_set_speed(float value);
  public:

  // @@protoc_insertion_point(class_scope:wanderer.proto.movable)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::internal::HasBits<1> _has_bits_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  ::wanderer::proto::float2* position_;
  ::wanderer::proto::float2* velocity_;
  float speed_;
  friend struct ::TableStruct_movable_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// movable

// optional .wanderer.proto.float2 position = 1;
inline bool movable::_internal_has_position() const {
  bool value = (_has_bits_[0] & 0x00000001u) != 0;
  PROTOBUF_ASSUME(!value || position_ != nullptr);
  return value;
}
inline bool movable::has_position() const {
  return _internal_has_position();
}
inline const ::wanderer::proto::float2& movable::_internal_position() const {
  const ::wanderer::proto::float2* p = position_;
  return p != nullptr ? *p : reinterpret_cast<const ::wanderer::proto::float2&>(
      ::wanderer::proto::_float2_default_instance_);
}
inline const ::wanderer::proto::float2& movable::position() const {
  // @@protoc_insertion_point(field_get:wanderer.proto.movable.position)
  return _internal_position();
}
inline void movable::unsafe_arena_set_allocated_position(
    ::wanderer::proto::float2* position) {
  if (GetArenaForAllocation() == nullptr) {
    delete reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(position_);
  }
  position_ = position;
  if (position) {
    _has_bits_[0] |= 0x00000001u;
  } else {
    _has_bits_[0] &= ~0x00000001u;
  }
  // @@protoc_insertion_point(field_unsafe_arena_set_allocated:wanderer.proto.movable.position)
}
inline ::wanderer::proto::float2* movable::release_position() {
  _has_bits_[0] &= ~0x00000001u;
  ::wanderer::proto::float2* temp = position_;
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
inline ::wanderer::proto::float2* movable::unsafe_arena_release_position() {
  // @@protoc_insertion_point(field_release:wanderer.proto.movable.position)
  _has_bits_[0] &= ~0x00000001u;
  ::wanderer::proto::float2* temp = position_;
  position_ = nullptr;
  return temp;
}
inline ::wanderer::proto::float2* movable::_internal_mutable_position() {
  _has_bits_[0] |= 0x00000001u;
  if (position_ == nullptr) {
    auto* p = CreateMaybeMessage<::wanderer::proto::float2>(GetArenaForAllocation());
    position_ = p;
  }
  return position_;
}
inline ::wanderer::proto::float2* movable::mutable_position() {
  ::wanderer::proto::float2* _msg = _internal_mutable_position();
  // @@protoc_insertion_point(field_mutable:wanderer.proto.movable.position)
  return _msg;
}
inline void movable::set_allocated_position(::wanderer::proto::float2* position) {
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
  // @@protoc_insertion_point(field_set_allocated:wanderer.proto.movable.position)
}

// optional .wanderer.proto.float2 velocity = 2;
inline bool movable::_internal_has_velocity() const {
  bool value = (_has_bits_[0] & 0x00000002u) != 0;
  PROTOBUF_ASSUME(!value || velocity_ != nullptr);
  return value;
}
inline bool movable::has_velocity() const {
  return _internal_has_velocity();
}
inline const ::wanderer::proto::float2& movable::_internal_velocity() const {
  const ::wanderer::proto::float2* p = velocity_;
  return p != nullptr ? *p : reinterpret_cast<const ::wanderer::proto::float2&>(
      ::wanderer::proto::_float2_default_instance_);
}
inline const ::wanderer::proto::float2& movable::velocity() const {
  // @@protoc_insertion_point(field_get:wanderer.proto.movable.velocity)
  return _internal_velocity();
}
inline void movable::unsafe_arena_set_allocated_velocity(
    ::wanderer::proto::float2* velocity) {
  if (GetArenaForAllocation() == nullptr) {
    delete reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(velocity_);
  }
  velocity_ = velocity;
  if (velocity) {
    _has_bits_[0] |= 0x00000002u;
  } else {
    _has_bits_[0] &= ~0x00000002u;
  }
  // @@protoc_insertion_point(field_unsafe_arena_set_allocated:wanderer.proto.movable.velocity)
}
inline ::wanderer::proto::float2* movable::release_velocity() {
  _has_bits_[0] &= ~0x00000002u;
  ::wanderer::proto::float2* temp = velocity_;
  velocity_ = nullptr;
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
inline ::wanderer::proto::float2* movable::unsafe_arena_release_velocity() {
  // @@protoc_insertion_point(field_release:wanderer.proto.movable.velocity)
  _has_bits_[0] &= ~0x00000002u;
  ::wanderer::proto::float2* temp = velocity_;
  velocity_ = nullptr;
  return temp;
}
inline ::wanderer::proto::float2* movable::_internal_mutable_velocity() {
  _has_bits_[0] |= 0x00000002u;
  if (velocity_ == nullptr) {
    auto* p = CreateMaybeMessage<::wanderer::proto::float2>(GetArenaForAllocation());
    velocity_ = p;
  }
  return velocity_;
}
inline ::wanderer::proto::float2* movable::mutable_velocity() {
  ::wanderer::proto::float2* _msg = _internal_mutable_velocity();
  // @@protoc_insertion_point(field_mutable:wanderer.proto.movable.velocity)
  return _msg;
}
inline void movable::set_allocated_velocity(::wanderer::proto::float2* velocity) {
  ::PROTOBUF_NAMESPACE_ID::Arena* message_arena = GetArenaForAllocation();
  if (message_arena == nullptr) {
    delete reinterpret_cast< ::PROTOBUF_NAMESPACE_ID::MessageLite*>(velocity_);
  }
  if (velocity) {
    ::PROTOBUF_NAMESPACE_ID::Arena* submessage_arena =
        ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper<
            ::PROTOBUF_NAMESPACE_ID::MessageLite>::GetOwningArena(
                reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(velocity));
    if (message_arena != submessage_arena) {
      velocity = ::PROTOBUF_NAMESPACE_ID::internal::GetOwnedMessage(
          message_arena, velocity, submessage_arena);
    }
    _has_bits_[0] |= 0x00000002u;
  } else {
    _has_bits_[0] &= ~0x00000002u;
  }
  velocity_ = velocity;
  // @@protoc_insertion_point(field_set_allocated:wanderer.proto.movable.velocity)
}

// optional float speed = 3;
inline bool movable::_internal_has_speed() const {
  bool value = (_has_bits_[0] & 0x00000004u) != 0;
  return value;
}
inline bool movable::has_speed() const {
  return _internal_has_speed();
}
inline void movable::clear_speed() {
  speed_ = 0;
  _has_bits_[0] &= ~0x00000004u;
}
inline float movable::_internal_speed() const {
  return speed_;
}
inline float movable::speed() const {
  // @@protoc_insertion_point(field_get:wanderer.proto.movable.speed)
  return _internal_speed();
}
inline void movable::_internal_set_speed(float value) {
  _has_bits_[0] |= 0x00000004u;
  speed_ = value;
}
inline void movable::set_speed(float value) {
  _internal_set_speed(value);
  // @@protoc_insertion_point(field_set:wanderer.proto.movable.speed)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace proto
}  // namespace wanderer

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_movable_2eproto