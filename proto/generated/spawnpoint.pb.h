// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: spawnpoint.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_spawnpoint_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_spawnpoint_2eproto

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
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
#include "float2.pb.h"
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_spawnpoint_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_spawnpoint_2eproto {
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
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_spawnpoint_2eproto;
namespace wanderer {
namespace proto {
class Spawnpoint;
struct SpawnpointDefaultTypeInternal;
extern SpawnpointDefaultTypeInternal _Spawnpoint_default_instance_;
}  // namespace proto
}  // namespace wanderer
PROTOBUF_NAMESPACE_OPEN
template<> ::wanderer::proto::Spawnpoint* Arena::CreateMaybeMessage<::wanderer::proto::Spawnpoint>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace wanderer {
namespace proto {

enum SpawnpointType : int {
  PLAYER = 0,
  SKELETON = 1,
  SpawnpointType_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::min(),
  SpawnpointType_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::max()
};
bool SpawnpointType_IsValid(int value);
constexpr SpawnpointType SpawnpointType_MIN = PLAYER;
constexpr SpawnpointType SpawnpointType_MAX = SKELETON;
constexpr int SpawnpointType_ARRAYSIZE = SpawnpointType_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* SpawnpointType_descriptor();
template<typename T>
inline const std::string& SpawnpointType_Name(T enum_t_value) {
  static_assert(::std::is_same<T, SpawnpointType>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function SpawnpointType_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    SpawnpointType_descriptor(), enum_t_value);
}
inline bool SpawnpointType_Parse(
    ::PROTOBUF_NAMESPACE_ID::ConstStringParam name, SpawnpointType* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<SpawnpointType>(
    SpawnpointType_descriptor(), name, value);
}
// ===================================================================

class Spawnpoint final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:wanderer.proto.Spawnpoint) */ {
 public:
  inline Spawnpoint() : Spawnpoint(nullptr) {}
  ~Spawnpoint() override;
  explicit constexpr Spawnpoint(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  Spawnpoint(const Spawnpoint& from);
  Spawnpoint(Spawnpoint&& from) noexcept
    : Spawnpoint() {
    *this = ::std::move(from);
  }

  inline Spawnpoint& operator=(const Spawnpoint& from) {
    CopyFrom(from);
    return *this;
  }
  inline Spawnpoint& operator=(Spawnpoint&& from) noexcept {
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
  static const Spawnpoint& default_instance() {
    return *internal_default_instance();
  }
  static inline const Spawnpoint* internal_default_instance() {
    return reinterpret_cast<const Spawnpoint*>(
               &_Spawnpoint_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(Spawnpoint& a, Spawnpoint& b) {
    a.Swap(&b);
  }
  inline void Swap(Spawnpoint* other) {
    if (other == this) return;
    if (GetOwningArena() == other->GetOwningArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(Spawnpoint* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline Spawnpoint* New() const final {
    return new Spawnpoint();
  }

  Spawnpoint* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<Spawnpoint>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const Spawnpoint& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom(const Spawnpoint& from);
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
  void InternalSwap(Spawnpoint* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "wanderer.proto.Spawnpoint";
  }
  protected:
  explicit Spawnpoint(::PROTOBUF_NAMESPACE_ID::Arena* arena,
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
    kPositionFieldNumber = 2,
    kTypeFieldNumber = 1,
  };
  // optional .wanderer.proto.float2 position = 2;
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

  // optional .wanderer.proto.SpawnpointType type = 1;
  bool has_type() const;
  private:
  bool _internal_has_type() const;
  public:
  void clear_type();
  ::wanderer::proto::SpawnpointType type() const;
  void set_type(::wanderer::proto::SpawnpointType value);
  private:
  ::wanderer::proto::SpawnpointType _internal_type() const;
  void _internal_set_type(::wanderer::proto::SpawnpointType value);
  public:

  // @@protoc_insertion_point(class_scope:wanderer.proto.Spawnpoint)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::internal::HasBits<1> _has_bits_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  ::wanderer::proto::float2* position_;
  int type_;
  friend struct ::TableStruct_spawnpoint_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// Spawnpoint

// optional .wanderer.proto.SpawnpointType type = 1;
inline bool Spawnpoint::_internal_has_type() const {
  bool value = (_has_bits_[0] & 0x00000002u) != 0;
  return value;
}
inline bool Spawnpoint::has_type() const {
  return _internal_has_type();
}
inline void Spawnpoint::clear_type() {
  type_ = 0;
  _has_bits_[0] &= ~0x00000002u;
}
inline ::wanderer::proto::SpawnpointType Spawnpoint::_internal_type() const {
  return static_cast< ::wanderer::proto::SpawnpointType >(type_);
}
inline ::wanderer::proto::SpawnpointType Spawnpoint::type() const {
  // @@protoc_insertion_point(field_get:wanderer.proto.Spawnpoint.type)
  return _internal_type();
}
inline void Spawnpoint::_internal_set_type(::wanderer::proto::SpawnpointType value) {
  _has_bits_[0] |= 0x00000002u;
  type_ = value;
}
inline void Spawnpoint::set_type(::wanderer::proto::SpawnpointType value) {
  _internal_set_type(value);
  // @@protoc_insertion_point(field_set:wanderer.proto.Spawnpoint.type)
}

// optional .wanderer.proto.float2 position = 2;
inline bool Spawnpoint::_internal_has_position() const {
  bool value = (_has_bits_[0] & 0x00000001u) != 0;
  PROTOBUF_ASSUME(!value || position_ != nullptr);
  return value;
}
inline bool Spawnpoint::has_position() const {
  return _internal_has_position();
}
inline const ::wanderer::proto::float2& Spawnpoint::_internal_position() const {
  const ::wanderer::proto::float2* p = position_;
  return p != nullptr ? *p : reinterpret_cast<const ::wanderer::proto::float2&>(
      ::wanderer::proto::_float2_default_instance_);
}
inline const ::wanderer::proto::float2& Spawnpoint::position() const {
  // @@protoc_insertion_point(field_get:wanderer.proto.Spawnpoint.position)
  return _internal_position();
}
inline void Spawnpoint::unsafe_arena_set_allocated_position(
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
  // @@protoc_insertion_point(field_unsafe_arena_set_allocated:wanderer.proto.Spawnpoint.position)
}
inline ::wanderer::proto::float2* Spawnpoint::release_position() {
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
inline ::wanderer::proto::float2* Spawnpoint::unsafe_arena_release_position() {
  // @@protoc_insertion_point(field_release:wanderer.proto.Spawnpoint.position)
  _has_bits_[0] &= ~0x00000001u;
  ::wanderer::proto::float2* temp = position_;
  position_ = nullptr;
  return temp;
}
inline ::wanderer::proto::float2* Spawnpoint::_internal_mutable_position() {
  _has_bits_[0] |= 0x00000001u;
  if (position_ == nullptr) {
    auto* p = CreateMaybeMessage<::wanderer::proto::float2>(GetArenaForAllocation());
    position_ = p;
  }
  return position_;
}
inline ::wanderer::proto::float2* Spawnpoint::mutable_position() {
  ::wanderer::proto::float2* _msg = _internal_mutable_position();
  // @@protoc_insertion_point(field_mutable:wanderer.proto.Spawnpoint.position)
  return _msg;
}
inline void Spawnpoint::set_allocated_position(::wanderer::proto::float2* position) {
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
  // @@protoc_insertion_point(field_set_allocated:wanderer.proto.Spawnpoint.position)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace proto
}  // namespace wanderer

PROTOBUF_NAMESPACE_OPEN

template <> struct is_proto_enum< ::wanderer::proto::SpawnpointType> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::wanderer::proto::SpawnpointType>() {
  return ::wanderer::proto::SpawnpointType_descriptor();
}

PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_spawnpoint_2eproto
